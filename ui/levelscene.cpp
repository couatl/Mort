#include "levelscene.h"
#include "button.h"

#include <QPalette>
#include <QThread>
#include <QFontDatabase>
#include <QFont>
#include <QPushButton>

#include <QDebug>

#define PLAYER_START_X 10
#define PLAYER_START_Y 150

LevelScene::LevelScene(QGraphicsView* _view, QLabel* _timerLabel, Timer *_timer, User *_user, QWidget *parent):
    QGraphicsScene(parent),
    timer(_timer),
    user(_user),
    isWin(false),
    hasKey(false),
    firstInput(false),
    startBlocks(QVector<AbstractBlock*>(24)),
    view(_view),
    timerLabel(_timerLabel),
    yAnimation(0),
    upAnimation(true),
    timerAnimation(new Timer(this, 100, 25)),
    countMoved(10)
{
    // ширина равна 86 (ширина 1 блока) * 24
    this->setSceneRect(0, 0, 2064, 520);
    QPixmap _background(":/rsc/images/bg.png");
    _background = _background.scaled(543, 540, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setBackgroundBrush(QBrush(_background));
      
    player = new Player(PLAYER_START_X, PLAYER_START_Y);
    this->addItem(player);

    goal = new Goal(800, 155);
    this->addItem(goal);

    // Block Building
    BlockWaiter waiter;
    BlockBuilder builder;
    waiter.setBlockBuilder(&builder);
    for (int i = 0; i < 8; i++)  {
        waiter.constructBlock(i*86, 453);
        startBlocks[i] = waiter.getBlock().first();
        addItem(startBlocks[i]);
    }

    BrokenBlockBuilder builder_2;
    waiter.setBlockBuilder(&builder_2);
    waiter.constructBlock(8*86, 453);
    QList<AbstractBlock*> blockList = waiter.getBlock();
    startBlocks[8] = blockList.first();
    startBlocks[9] = blockList.last();
    addItem(startBlocks[8]);
    addItem(startBlocks[9]);
    waiter.setBlockBuilder(&builder);
    for (int i = 11; i < 24; i++)  {
        waiter.constructBlock(i*86, 453);
        startBlocks[i] = waiter.getBlock().first();
        addItem(startBlocks[i]);
    }

    timerLabel->setText(timer->getDecoratedTime());
    if (timer->getTime() <= 10)
        timerLabel->setStyleSheet("QLabel { color : red; }");

    timerAnimation->moveToThread(QThread::currentThread());

    connect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
    connect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
    connect(this, &LevelScene::didFirstInput, this, &LevelScene::timerStart);

    connect(player, &Player::jumpFactorChanged, this, &LevelScene::playerJump);
    connect(player, &Player::signalJump, timerAnimation, &Timer::stop);
    connect(player->jumpAnimation, SIGNAL(finished()), timerAnimation, SLOT(start()));
}

LevelScene::~LevelScene() {
    delete player;
    delete goal;
    for (int i = 0; i < 4; i++)  {
        delete startBlocks[i];
    }
    delete timerAnimation;
}

void LevelScene::PlayerAnimation()
{
    if (player->pos().y() >= (540 - 132) / 2)
    {
        disconnect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
        disconnect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
        displayGameOverWindow("I am disappointed.");
    }

    //  falling
    int playerState = player->getState();
    int isFall = player->getState() == Player::falling ? 2 : 0;

    //  flying animation
    if (playerState == Player::normal)
    {
        if (yAnimation == 14 || yAnimation == -14)
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

//    if (playerState == Player::jumping)
//    {
//        if (yAnimation == -40)
//        {
//            player->setState(Player::falling);
//        }
//        else {
//            yAnimation--;
//        }
//        player->setYAnimation(yAnimation);
//    }

    //  apply changes
    player->setPos(
                player->getX() == player->pos().x() ?
                    player->pos().x() :
                    player->pos().x() + player->getDirection(),
                (player->getY() + yAnimation + isFall));

    countMoved = player->pos().x();

    if (player->collidingItems().isEmpty())
    {
        player->setState(Player::falling);
    }
    else if (player->getState() != Player::normal)
    {
        if (intersect(player, player->collidingItems()))
           player->setState(Player::normal);
    }
    else if (player->collidesWithItem(goal)) {
        isWin = true;
        disconnect(timer, &Timer::timeout, this, &LevelScene::timeUpdate);
        disconnect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
        displayGameOverWindow("Good job, oh sweet child.");
    }
}

void LevelScene::timerStart()
{
    timer->start();
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
    int groundLevel = startBlocks.first()->boundingRect().top();
    int jumpHeight = 130;
    const qreal y = (groundLevel - player->boundingRect().height() - factor * jumpHeight) / 2;
    player->setPos(player->getX() == player->pos().x() ?
                       player->pos().x() :
                       player->pos().x() + ( player->getDirection() == -1 ? -2 : 2), y);
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
            if (event->isAutoRepeat())
                return;
            player->jump();
            break;
        }
    }
    else
        event->ignore();
}

void LevelScene::drawPanel(int x, int y, int width, int height, QColor color, double opacity, int flag)
{
    // Рисует панель на x, y с параметрами-свойствами
    if (flag == 0)
    {
        QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(color);
        panel->setBrush(brush);
        panel->setOpacity(opacity);
        this->addItem(panel);
    }
    else
    {
        QLabel* label = new QLabel();
        label->resize(width,height);
        label->move(x,y);
        QPixmap background(":/rsc/images/death_message.png");
        background = background.scaled(label->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        label->setPixmap(background);
        label->raise();
        this->addWidget(label);
    }
}

void LevelScene::displayGameOverWindow(QString textToDisplay)
{
    // Отключаем все объекты уровня
    disconnect(timerAnimation, &Timer::timeout, this, &LevelScene::PlayerAnimation);
    for (size_t i = 0, n = this->items().size(); i < n; i++){
        this->items()[i]->setEnabled(false);
    }
    this->removeItem(player);
    this->removeItem(goal);

    // Затемняем игру
    drawPanel(0,0,960,540,Qt::black,0.65,0);

    // Рисуем панельку
    drawPanel(180,133,600,273,Qt::lightGray,0.75,1);

    // Рисуем окно с текстом
    int id = QFontDatabase::addApplicationFont(":/rsc/resources/ITCBLKAD.TTF");
    QString font_name = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font = QFont(font_name, 43, QFont::Normal);

    QGraphicsTextItem* overText = new QGraphicsTextItem(textToDisplay);
    overText->setPos(300,175);
    overText->setFont(font);

    this->addItem(overText);

    Button* MainMenu = new Button(QString("ok"), font);
    MainMenu->setPos(422,410);
    this->addItem(MainMenu);
    connect(MainMenu, &Button::clicked, this, &LevelScene::finishLevel);
}

void LevelScene::timeUpdate()
{
    if (timer->getTime() == 0) {
        timerLabel->setStyleSheet("QLabel { color : red; }");
        timerLabel->setText("0:00");
        timer->stop();
        displayGameOverWindow("I am disappointed");
        //emit levelFail();
        return;
    }

    timer->decrease();
    if(timer->getTime() > 0) {
        timerLabel->setText(timer->getDecoratedTime());
        if (timer->getTime() <= 10)
            timerLabel->setStyleSheet("QLabel { color : red; }");
        return;
    }
    else if(timer->getTime() == 0)
    {
        timerLabel->setStyleSheet("QLabel { color : red; }");
        timerLabel->setText("0:00");
        timer->stop();
        displayGameOverWindow("I am disappointed");
        //emit levelFail();
        return;
    }
}

bool LevelScene::intersect(Player* player,QList<QGraphicsItem*> list)
{
    for (auto i: list)
    {
        if (player->boundingRect().y()*2+player->boundingRect().height() - i->boundingRect().top() <= 3)
        {
            qDebug() << player->boundingRect() << i->boundingRect().top();
            return true;
        }
    }
    return false;
}
