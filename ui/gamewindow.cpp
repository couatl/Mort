#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QMessageBox>
#include <QFontDatabase>
#include <QFont>
#include <QTextStream>
#include <QFile>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include "aboutdialog.h"
#include "firstwindow.h"

#include <QDebug>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    user(User()),/*
    id_selected(-1),
    mode(-1),*/
    clocks(QVector<Clock*>(3))
{
    ui->setupUi(this);
    this->setWindowTitle("Mort");

    QPixmap loading(":/rsc/images/loading.png");
    loading = loading.scaled(ui->loading->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->loading->setPixmap(loading);
    ui->loading->hide();
    ui->loading->raise();

    connect(ui->actionAbout, &QAction::triggered, this, &GameWindow::about);
    connect(this, &GameWindow::clicked_1, this, &GameWindow::launchGame_1);
    connect(this, &GameWindow::loadingEnd, this, &GameWindow::afterLoading);

    drawBackground();
    createScene();

    this->setCentralWidget(view);

//    if (!user.exist()) {
//        clearAll();
//        firstWindow();
//    }
//    else {
//        clockRead(!user.exist());
//        drawClocks();
//    }
}

GameWindow::~GameWindow()
{
//    clockWrite();
//    for (auto i = timers.begin(); i != timers.end(); ++i) {
//        delete *i;
//    }
    for (auto i = clocks.begin(); i != clocks.end(); ++i) {
        delete *i;
    }
    delete ui;
}

void GameWindow::about()
{
    AboutDialog dialog(this);
    dialog.exec();
}

//              ***     Update for timer     ***
void GameWindow::update()
{
    /*
    for (int i = 0; i < 3; i++) {
        timers[i]->decrease();
        if ( timers[i]->getTime() > 0)
        {
            QString minutes = QString::number(timers[i]->getTime() / 60);
            QString seconds = "0";
            if (timers[i]->getTime() % 60 >= 10)
            {
                seconds = QString::number(timers[i]->getTime() % 60);
            }
            else
            {
                seconds += QString::number(timers[i]->getTime() % 60);
            }

            times[i]->setText(minutes + ":" + seconds);
            if (timers[i]->getTime() <= 10)
                times[i]->setStyleSheet("QLabel { color : red; }");
        }
        else
        {
            times[i]->setText("0:00");
            timers[i]->stop();
        }
    }
    */
}

void GameWindow::launchGame_1()
{
    qDebug() << "launch game 1";
    startLoading();
}

void GameWindow::firstWindow()
{
    /*
    mode = 1;
    first = new FirstWindow(this, &user);
    ui->firstLayout->addWidget(first);

    connect(first, &FirstWindow::ok_clicked, this, &GameWindow::firstWindowClosed);
    */
}

void GameWindow::firstWindowClosed()
{
//    qDebug() << "removing";
//    ui->firstLayout->removeWidget(first);
//    delete first;
//    qDebug() << "loading";
    startLoading();
}

/*
void GameWindow::mousePressEvent(QMouseEvent *event)
{
    GameWindow::mousePressEvent(event);

    if (event->button() != Qt::LeftButton)
        return;

    if (mode == 1)
        return;

    if (clocks[0]->underMouse()) {

        if(clocks[0]->isFocused())
            emit clicked_1();
        else if(id_selected == -1) {
            clocks[0]->setFocused();
            id_selected = 0;
        }
        else {
            clocks[id_selected]->deleteFocus();
            id_selected = 0;
            clocks[0]->setFocused();
        }
    }   else if (clocks[1]->underMouse()) {

        if(clocks[1]->isFocused())
            emit clicked_2();
        else if(id_selected == -1) {
            clocks[1]->setFocused();
            id_selected = 1;
        }
        else {
            clocks[id_selected]->deleteFocus();
            id_selected = 1;
            clocks[1]->setFocused();
        }
    }    else if (clocks[2]->underMouse()) {

        if(clocks[2]->isFocused())
            emit clicked_3();
        else if(id_selected == -1) {
            clocks[2]->setFocused();
            id_selected = 2;
        }
        else {
            clocks[id_selected]->deleteFocus();
            id_selected = 2;
            clocks[2]->setFocused();
        }
    }
}
*/

void GameWindow::createScene()
{
    view = new View;
    first = new FirstWindow(view);
    connect(first, &FirstWindow::destroyed, this, &GameWindow::firstWindowClosed);
/*
    if (!user.exist()) {
        first = new FirstWindow(view);
    }
    else {
        main = new MainScene(view);
//        clockRead(!user.exist());
//        drawClocks();
    }
*/
    // in FirstWindow/MainScene classes view will be set

}

void GameWindow::drawClocks()
{
    /*
    for (int i = 0; i < 3; i++) {
        clocks[i]->setVisible(true);
    }

    clocks[0]->setGeometry(230, 150, 145, 237);
    clocks[1]->setGeometry(410, 150, 145, 237);
    clocks[2]->setGeometry(590, 150, 145, 237);

    int id = QFontDatabase::addApplicationFont(":/rsc/resources/ITCBLKAD.TTF");
//    int id = QFontDatabase::addApplicationFont("C:/Mort/Mort/resources/ITCBLKAD.TTF");
    QString font_name = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(font_name, 38, QFont::Normal);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);

    for (int i = 0; i < 3; i++) {
        times[i]->setFont(font);
        times[i]->setPalette(palette);
        QString minutes = QString::number(timers[i]->getTime() / 60);
        QString seconds = "0";
        if (timers[i]->getTime() % 60 >= 10)
        {
            seconds = QString::number(timers[i]->getTime() % 60);
        }
        else
        {
            seconds += QString::number(timers[i]->getTime() % 60);
        }

        times[i]->setText(minutes + ":" + seconds);
        if (timers[i]->getTime() <= 10)
            times[i]->setStyleSheet("QLabel { color : red; }");
    }
    ui->label->setFont(font);
    ui->label->setPalette(palette);
    ui->score->setFont(font);
    ui->score->setPalette(palette);

    ui->label->setText("Good night, " + user.getUsername() + ". They're waiting.");
    ui->score->setText("Score: " + QString::number(user.getScore()));
    */
}


void GameWindow::drawBackground()
{
    QPixmap background(":/rsc/images/bg960x540.png");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
    this->setFixedSize(960, 540);
}

void GameWindow::drawShelf()
{
    QPixmap shelf(":/rsc/images/shelf.png");
    shelf = shelf.scaled(ui->shelf->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->shelf->setPixmap(shelf);
}


void GameWindow::clockWrite()
{
    /*
//    QFile File("clocks.qml");
    QFile File("/Users/sharlina/Documents/coding/Mort/Mort/docs/clocks.qml");


    if (!File.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(0, "error", File.errorString());
    }
    QTextStream stream (&File);
    for( int i = 0; i < 3; ++i){
        switch(clocks[i]->getState()) {
        case Clock::normal:
            stream << "normal" << " ";
            break;
        case Clock::hover:
            stream << "normal" << " ";
            break;
        case Clock::succeed:
            stream << "succeed" << " ";
            break;
        case Clock::failed:
            stream << "failed" << " ";
            break;
        }
        stream << timers[i]->getTime() << "\n";
    }
    File.close();
    */
}

void GameWindow::clockRead(bool first_input)
{
    /*
    if (first_input) {
        clocks[0] = new Clock(this);
        clocks[1] = new Clock(this);
        clocks[2] = new Clock(this);

        timers[0] = new Timer(this);
        timers[1] = new Timer(this, 143);
        timers[2] = new Timer(this, 243);
        return;
    }

//    QFile inputFile("clocks.qml");
    QFile inputFile("/Users/sharlina/Documents/coding/Mort/Mort/docs/clocks.qml");

    if (!inputFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", inputFile.errorString());
    }

    QTextStream in(&inputFile);
    for(int i = 0; i < 3; ++i) {
        QString line = in.readLine();
        QString check = line.left(line.indexOf(" "));
        if(check ==  "normal") {
            clocks[i] = new Clock(this, Clock::State::normal);
        }
        if(check ==  "succeed") {
            clocks[i] = new Clock(this, Clock::State::succeed);
        }
        if(check ==  "failed") {
            clocks[i] = new Clock(this, Clock::State::failed);
        }
        line = line.right(line.size() - line.indexOf(" "));
        timers[i] = new Timer(this, line.toInt());
    }
    inputFile.close();
    */
}

void GameWindow::endLoading()
{
    qDebug() << "end loading";
    clearAll();
    // "затухание"
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    ui->loading->setGraphicsEffect(eff);
    QPropertyAnimation *animation = new QPropertyAnimation(eff,"opacity");
    animation->setDuration(1700);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    emit loadingEnd();
}

void GameWindow::startLoading()
{
    // "появление"
    ui->loading->show();
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    ui->loading->setGraphicsEffect(eff);
    QPropertyAnimation *animation = new QPropertyAnimation(eff,"opacity");
    animation->setDuration(1700);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InBack);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    qDebug() << "start loading";
    connect(animation, &QPropertyAnimation::finished, this, &GameWindow::endLoading);
}

void GameWindow::clearAll()
{
    /*
    ui->clock_1->hide();
    ui->clock_2->hide();
    ui->clock_3->hide();
    ui->time_1->hide();
    ui->time_2->hide();
    ui->time_3->hide();
    ui->label->hide();
    ui->score->hide();
    ui->shelf->hide();
    */
}

void GameWindow::showAll()
{
    /*
    ui->clock_1->show();
    ui->clock_2->show();
    ui->clock_3->show();
    ui->time_1->show();
    ui->time_2->show();
    ui->time_3->show();
    ui->label->show();
    ui->score->show();
    ui->shelf->show();
    */
}
