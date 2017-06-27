#include "levelscene.h"

#include <QPalette>
#include <QThread>
#include <QFontDatabase>
#include <QFont>
#include <QPushButton>
#include <QCoreApplication>
#include <QGraphicsSimpleTextItem>

#include <QDebug>

LevelScene::LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    timer(_timer),
    user(_user),
    isWin(false),
    hasKey(false),
    firstInput(false),
    view(_view),
    timerLabel(_timerLabel),
    yAnimation(0),
    upAnimation(true),
    timerAnimation(new Timer(nullptr, 100, 25, false)),
    countMoved(10)
{
    // ширина равна 86 (ширина 1 блока) * 24
    this->setSceneRect(0, 0, 2064, 540);
    QPixmap _background(":/rsc/images/bg.png");
    _background = _background.scaled(543, 540, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(_background));
      
    // Загрузка уровня
    level = new Level(this);
    level->loadLevel(1);

    goal = level->getGoal();
    goal->hide();
    house = new House(goal->boundingRect().x(), goal->boundingRect().bottom() - 240);
    this->addItem(house);
    this->addItem(goal);

    player = level->getPlayer();
    this->addItem(player);

    int id = QFontDatabase::addApplicationFont(":/rsc/resources/ITCBLKAD.TTF");
    QString font_name = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font = QFont(font_name, 52, QFont::Normal);

    // Загрузка таймера отсчета
    timerText = new QGraphicsSimpleTextItem(timerLabel->text());
    timerText->setGraphicsEffect(timerLabel->graphicsEffect());
    timerText->setPos(410, 20);
    timerText->setFont(font);
    this->addItem(timerText);

    timerText->setText(timer->getDecoratedTime());
    if (timer->getTime() <= 10)
        timerText->setBrush(QBrush(Qt::red));
    else
        timerText->setBrush(QBrush(Qt::white));

    QPixmap _key(":/rsc/images/key.png");
    _key = _key.scaled(50, 38, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    keyLabel = new QGraphicsPixmapItem();
    keyLabel->setPixmap(_key);
    keyLabel->setPos(425 + timerText->boundingRect().width(), 40);
    this->addItem(keyLabel);
    keyLabel->hide();

    key = level->getKey();
    this->addItem(key);

    keyPlayer = new QMediaPlayer();
    keyPlayer->setMedia(QUrl("qrc:/music/resources/3.mp3"));


    // коннектим сигналы-слоты
    connect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
    connect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
    connect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);

    connect(player, &Player::jumpFactorChanged, this, &LevelScene::playerJump);
    connect(player, &Player::signalJump, timerAnimation, &Timer::stop);
    connect(player->jumpAnimation, SIGNAL(finished()), timerAnimation, SLOT(start()));
}

LevelScene::~LevelScene() {
    delete level;
    delete timerAnimation;
    delete keyPlayer;
}

void LevelScene::PlayerAnimation()
{
    QCoreApplication::processEvents();

    //Следовать за пользователем
    if (player->isEnabled()) {
        view->ensureVisible(player, 400);
    }

    timerText->setPos(view->mapToScene(view->rect()).boundingRect().x()+410, timerText->pos().y());
    if (hasKey)
        keyLabel->setPos(view->mapToScene(view->rect()).boundingRect().x() + 425 + timerText->boundingRect().width(), keyLabel->pos().y());

    // Провалился за экран
    if (player->pos().y() >= (540 - 132) / 2)
    {
        displayGameOverWindow("I am disappointed.");
    }

    //  falling
    int playerState = player->getState();
    int isFall = player->getState() == Player::falling ? 2 : 0;

    //  flying animation
    if (playerState == Player::normal)
    {
        if (yAnimation == 7 || yAnimation == -7)
        {
            upAnimation = !upAnimation;
        }
        if (upAnimation)
        {
            yAnimation++;
        }
        else
        {
            yAnimation--;
        }
        player->setYAnimation(yAnimation);
    }

    //  apply changes
    player->setPos(
                player->getX() == player->pos().x() ?
                    player->pos().x() :
                    player->pos().x() + player->getDirection(),
                (player->getY() + yAnimation + isFall));

    if (player->collidingItems().isEmpty())
    {
        player->setState(Player::falling);
    }
    else if (player->getState() != Player::normal)
    {
        if (intersect(player, player->collidingItems()))
           player->setState(Player::normal);
    }
    else if (player->collidesWithItem(key) && !hasKey)
    {
        hasKey = true;
        this->removeItem(key);
        keyLabel->show();
        goal->show();
        keyPlayer->play();
    }
    else if (player->collidesWithItem(goal) && hasKey) {
        isWin = true;
        displayGameOverWindow("Good job, oh sweet child.");
    }
}

void LevelScene::timerStart()
{
    timer->start(1000);
    disconnect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);
}

void LevelScene::finishLevel()
{
    if (isWin)
    {
        emit levelComplete();
    }
    else
    {
        emit levelFail();
    }
}

void LevelScene::playerJump(qreal factor)
{
    //qDebug() << player->jumpAnimation->currentValue() << player->jumpAnimation->endValue() << player->jumpAnimation->state() << player->getState();

    if(player->getState() != Player::jumping) {
        player->jumpAnimation->setCurrentTime(900);
    }
    qreal jumpHeight = 90;

    //Следовать за пользователем
    if (player->isEnabled()) {
        view->ensureVisible(player, 400);
    }

    const qreal y = (groundLevel - player->boundingRect().height() - factor * jumpHeight) / 2;
    player->setPos(player->getX() == player->pos().x() ?
                       player->pos().x() :
                       player->pos().x() + 2 * player->getDirection(), y);

    if (player->getState() != Player::normal)
    {
        if (intersect(player, player->collidingItems()))
        {
            player->setState(Player::normal);
        }
    }

    timerText->setPos(view->mapToScene(view->rect()).boundingRect().x()+410, timerText->pos().y());
    if (hasKey)
        keyLabel->setPos(view->mapToScene(view->rect()).boundingRect().x()+425 + timerText->boundingRect().width(), keyLabel->pos().y());
}

void LevelScene::keyPressEvent(QKeyEvent *event)
{
    QCoreApplication::processEvents();

    if (!firstInput)  {
        firstInput = true;
        emit didFirstInput();
    }

    if(player->isEnabled())
    {
        switch (event->key()) {
        case Qt::Key_Right:
        case Qt::Key_D:
            if (player->getDirection() == -1)
                player->rotate();
            player->walk(true);
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            if (player->getDirection() == 1)
                player->rotate();
            player->walk(false);
            break;
        case Qt::Key_Space:
        case Qt::Key_Up:
            if (event->isAutoRepeat())
                break;
            if(player->getState() == Player::falling || player->getState() == Player::jumping
                    || player->jumpAnimation->state() != QPropertyAnimation::Stopped) {
//                qDebug() << "exited";
                break;
            }
            groundLevel = player->boundingRect().y() * 2 + player->boundingRect().height();
            player->jump();
            break;
        }
    }
    // Отключает скролл клавишами после смерти персонажа
    else {
        if(event->isAutoRepeat()) {
            return;
        }
        else {
            finishLevel();
        }
    }
}

void LevelScene::displayGameOverWindow(QString textToDisplay)
{
    // Отключаем все объекты уровня
    disconnect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
    disconnect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
    for (size_t i = 0, n = this->items().size(); i < n; i++){
        this->items()[i]->setEnabled(false);
    }
    this->removeItem(player);
    //this->removeItem(goal);

    // Затемняем игру
    QGraphicsRectItem* panel = new QGraphicsRectItem(0,0,960,540);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    panel->setBrush(brush);
    panel->setOpacity(0.65);
    this->addItem(panel);

    view->centerOn(400,0);

    // Отрисовка картинки письма
    QLabel* label = new QLabel();
    label->resize(600,273);
    label->move(180,130);
    QPixmap background(":/rsc/images/death_message.png");
    background = background.scaled(label->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    label->setPixmap(background);
    label->raise();
    this->addWidget(label);

    // Подключение шрифта
    int id = QFontDatabase::addApplicationFont(":/rsc/resources/ITCBLKAD.TTF");
    QString font_name = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font = QFont(font_name, 43, QFont::Normal);

    // Заключительное сообщение
    QGraphicsSimpleTextItem* overText = new QGraphicsSimpleTextItem(textToDisplay);
    overText->setPos(300,175);
    overText->setFont(font);
    this->addItem(overText);

    QGraphicsSimpleTextItem* logText = new QGraphicsSimpleTextItem("Press any button to continue");
    logText->setPos(390,410);
    logText->setBrush(QBrush(Qt::white));
    QFont font_2 = QFont("Arial", 16, QFont::Cursive);
    font_2.setItalic(true);
    logText->setFont(font_2);
    this->addItem(logText);
}

void LevelScene::timeUpdate()
{
    if (timer->getTime() == 0) {
        timerText->setBrush(QBrush(Qt::red));
        timerText->setText("0:00");
        timer->stop();
        displayGameOverWindow("I am disappointed");
        return;
    }

    timer->decrease();
    if(timer->getTime() > 0) {
        timerText->setText(timer->getDecoratedTime());
        if (timer->getTime() <= 10)
            timerText->setBrush(QBrush(Qt::red));
        return;
    }
    else if(timer->getTime() == 0)
    {
        timerText->setBrush(QBrush(Qt::red));
        timerText->setText("0:00");
        timer->stop();
        displayGameOverWindow("I am disappointed");
        return;
    }

}

bool LevelScene::intersect(Player* player, QList<QGraphicsItem*> list)
{
    for (auto i: list)
    {
        qDebug() << player->boundingRect().y() * 2 + player->boundingRect().height() << i->boundingRect().top();
        if (player->boundingRect().y() * 2 + player->boundingRect().height() - i->boundingRect().top() <= 4)
        {
            return true;
        }
    }
    return false;
}
