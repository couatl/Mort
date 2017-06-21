#include "levelscene.h"
#include "button.h"

#include <QPalette>
#include <QFontDatabase>
#include <QFont>
#include <QDebug>

LevelScene::LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    timer(_timer),
    user(_user),
    isWin(false),
    firstInput(false),
    view(_view),
    timerLabel(_timerLabel),
    yAnimation(0),
    upAnimation(true),
    timerAnimation(new Timer(nullptr, 60, 20))
{
    // ширина равна 86 (ширина 1 блока) * 24
    this->setSceneRect(0, 0, 2064, 540);
    QPixmap _background(":/rsc/images/bg.png");
    _background = _background.scaled(543, 540, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(_background));

    // Загрузка уровня
    level = new Level(this);
    level->loadLevel(1);

    player = level->getPlayer();
    this->addItem(player);

    goal = level->getGoal();
    this->addItem(goal);

    //Загрузка таймера отсчета
    QString minutes = QString::number(timer->getTime() / 60);
    QString seconds = "0";
    if (timer->getTime() % 60 >= 10)
    {
        seconds = QString::number(timer->getTime() % 60);
    }
    else
    {
        seconds += QString::number(timer->getTime() % 60);
    }

    timerLabel->setText(minutes + ":" + seconds);
    if (timer->getTime() <= 10)
        timerLabel->setStyleSheet("QLabel { color : red; }");

    //коннектим сигналы-слоты
    connect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
    connect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
    connect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);
}

LevelScene::~LevelScene() {
    delete level;
    delete timerAnimation;

    qDebug() << this->items();

    for (auto item : this->items())
        delete item;
}

void LevelScene::PlayerAnimation()
{
    //провалился за экран
    if (player->pos().y()>=204)
    {
        displayGameOverWindow("I am disappointed");
    }

    //falling
    int isFall = player->getState()==Player::falling ? 2 : 0;

    //flying animation
    if (!isFall)
    {
        if (yAnimation==14 || yAnimation==-14)
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

    //apply changes
    player->setPos(player->getX()==player->pos().x() ? player->pos().x() : player->pos().x()+player->getDirection(), (player->getY()+yAnimation+isFall));

    if (player->collidingItems().isEmpty())
    {
        player->setState(Player::falling);
    }
    else if (player->collidesWithItem(goal))
    {
        isWin = true;
        displayGameOverWindow("Good job, oh sweet child.");
    }
    else if (player->getState() == Player::falling)
    {
        if (intersect(player, player->collidingItems()))
           player->setState(Player::normal);
    }
}

void LevelScene::timerStart()
{
    timer->start();
    disconnect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);
}

void LevelScene::keyPressEvent(QKeyEvent *event)
{
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
            //jump()
            break;
        }
    }
    else
    {
        switch (event->key()) {
        case Qt::Key_Right:
        case Qt::Key_D:
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            break;
        case Qt::Key_Space:
        case Qt::Key_Up:
            //jump()
            break;
        }
    }
}

void LevelScene::timeUpdate()
{
    timer->decrease();
    if(timer->getTime() > 0)
    {
        QString minutes = QString::number(timer->getTime() / 60);
        QString seconds = "0";
        if (timer->getTime() % 60 >= 10)
        {
            seconds = QString::number(timer->getTime() % 60);
        }
        else
        {
            seconds += QString::number(timer->getTime() % 60);
        }

        timerLabel->setText(minutes + ":" + seconds);
        if (timer->getTime() <= 10)
            timerLabel->setStyleSheet("QLabel { color : red; }");
    }
    else
    {
        timerLabel->setStyleSheet("QLabel { color : red; }");
        timerLabel->setText("0:00");
        timer->stop();
        timer->setTime(0);
        displayGameOverWindow("I am disappointed");
    }
}

bool LevelScene::intersect(Player* player,QList<QGraphicsItem*> list)
{
    for (auto i: list)
    {
        if (player->boundingRect().y()*2+player->boundingRect().height() - i->boundingRect().top() <= 4)
        {
            //qDebug() << player->boundingRect() << i->boundingRect().top();
            return true;
        }
    }
    return false;
}

void LevelScene::displayGameOverWindow(QString textToDisplay){
    // Отключаем все объекты уровня
    disconnect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
    disconnect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
    for (size_t i = 0, n = this->items().size(); i < n; i++){
        this->items()[i]->setEnabled(false);
    }
    this->removeItem(player);
    this->removeItem(goal);

    // Затемняем игру
    QGraphicsRectItem* panel = new QGraphicsRectItem(0,0,960,540);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    panel->setBrush(brush);
    panel->setOpacity(0.65);
    this->addItem(panel);

    // Отрисовка картинки письма
    QLabel* label = new QLabel();
    label->resize(600,273);
    label->move(180,133);
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
    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    overText->setPos(300,175);
    overText->setFont(font);
    this->addItem(overText);

    Button* MainMenu = new Button(QString("ok"), font);
    MainMenu->setPos(422,410);
    this->addItem(MainMenu);
    connect(MainMenu,&Button::clicked,this,&LevelScene::finishLevel);
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
