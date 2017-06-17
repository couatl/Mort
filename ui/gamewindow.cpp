#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QMessageBox>
#include <QFontDatabase>
#include <QFont>
#include <QTextStream>
#include <QFile>
#include <QMouseEvent>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QColor>
#include <QThread>

#include "aboutdialog.h"

#include <QDebug>

QThread *workerThread;

QGraphicsDropShadowEffect* ShadowEffect(QGraphicsDropShadowEffect* eff)
{
    eff->setOffset(0, 0);
    eff->setBlurRadius(10.0);
    eff->setColor(QColor(24, 148, 197));
    return eff;
}

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    user(User()),
    id_selected(-1),
    clock_timers(QVector<Timer*>(3)),
    clocks(QVector<Clock*>(3)),
    times(QVector<QLabel*>(3)),
    timer_message(new Timer(nullptr, 60, 300)),
    loading(new QLabel(this))
{
    ui->setupUi(this);
    this->setWindowTitle("Mort");

    ui->stackedWidget->setCurrentIndex(0);

    int id = QFontDatabase::addApplicationFont(":/rsc/resources/ITCBLKAD.TTF");
    QString font_name = QFontDatabase::applicationFontFamilies(id).at(0);
    font = QFont(font_name, 38, QFont::Normal);

    times[0] = ui->time_1;
    times[1] = ui->time_2;
    times[2] = ui->time_3;

    QPixmap background(":/rsc/images/start_window2.png");
    background = background.scaled(ui->background->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->background->setPixmap(background);
    ui->background->lower();

    connect(ui->actionAbout, &QAction::triggered, this, &GameWindow::about);
    connect(this, &GameWindow::clicked_1, this, &GameWindow::launchGame_1);
    //connect(scene, &LevelScene::levelComplete, this, &GameWindow::completedGame_1);
    //connect(scene, &LevelScene::levelFail, this, &GameWindow::failedGame_1);

    drawBackground();
    drawLoading();

    // for firstPage
    ui->userLineEdit->setFont(font);
    ui->message->setFont(font);
    ui->pushButton->setFont(font);

    // for level page
    QFont fontLabel = QFont(font_name, 52, QFont::Normal);
    ui->timerLabel->setFont(fontLabel);
    QGraphicsDropShadowEffect *effTimer = new QGraphicsDropShadowEffect(this);
    ui->timerLabel->setGraphicsEffect(ShadowEffect(effTimer));
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    ui->timerLabel->setPalette(palette);

    if (!user.exist())
    {
        connect(timer_message, &Timer::timeout, this, &GameWindow::writeMessage);
    }
    else
    {
        clockRead(!user.exist());
        drawClocks();
        drawShelf();
        drawLoading();
        ui->stackedWidget->setCurrentIndex(1);
    }

}

GameWindow::~GameWindow()
{
    delete ui->timerLabel->graphicsEffect();
    delete ui->score->graphicsEffect();
    delete ui->label->graphicsEffect();

    if(user.getUsername() != "")
        clockWrite();

    delete loading;
    delete timer_message;
    delete scene;

    for (auto i = clock_timers.begin(); i != clock_timers.end(); ++i) {
        delete *i;
    }

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

void GameWindow::launchGame_1()
{
    qDebug() << "launch game 1";

    clock_timers[0]->stop();
    scene = new LevelScene(ui->view, ui->timerLabel, clock_timers[0], &user);

    startLoading();
}

void GameWindow::completedGame_1()
{

}

void GameWindow::failedGame_1()
{
    clocks[0]->setState(Clock::failed);
    clock_timers[0]->setTime(0);
    ui->time_1->setText("0:00");

}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    if (ui->stackedWidget->currentIndex() == 0)
        return;

    if (clocks[0]->underMouse() || clocks[1]->underMouse() || clocks[2]->underMouse()){
        for(int i = 0; i < 3; ++i){
            if (clocks[i]->underMouse() && clocks[i]->isNormal()) {
                if(clocks[i]->isFocused())
                    emit clicked_1();
                else if(id_selected == -1) {
                    clocks[i]->setFocused();
                    id_selected = i;
                }
                else {
                    clocks[id_selected]->deleteFocus();
                    id_selected = i;
                    clocks[i]->setFocused();
                }
                }
        }
    } else {
        for(int i = 0; i < 3; ++i)
           clocks[i]->deleteFocus();
    }
}

void GameWindow::drawClocks()
{
    for (int i = 0; i < 3; i++) {
        clocks[i]->setVisible(true);
    }

    clocks[0]->setGeometry(230, 150, 145, 237);
    clocks[1]->setGeometry(410, 150, 145, 237);
    clocks[2]->setGeometry(590, 150, 145, 237);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);

    for (int i = 0; i < 3; i++) {
        times[i]->setFont(font);
        times[i]->setPalette(palette);
        QString minutes = QString::number(clock_timers[i]->getTime() / 60);
        QString seconds = "0";
        if (clock_timers[i]->getTime() % 60 >= 10)
        {
            seconds = QString::number(clock_timers[i]->getTime() % 60);
        }
        else
        {
            seconds += QString::number(clock_timers[i]->getTime() % 60);
        }

        times[i]->setText(minutes + ":" + seconds);
        if (clock_timers[i]->getTime() <= 10)
            times[i]->setStyleSheet("QLabel { color : red; }");
    }

    //TODO: delete
    QGraphicsDropShadowEffect *effLabel = new QGraphicsDropShadowEffect(this);
    QGraphicsDropShadowEffect *effScore = new QGraphicsDropShadowEffect(this);
    ui->label->setGraphicsEffect(ShadowEffect(effLabel));
    ui->score->setGraphicsEffect(ShadowEffect(effScore));

    ui->label->setFont(font);
    ui->label->setPalette(palette);
    ui->score->setFont(font);
    ui->score->setPalette(palette);

    ui->label->setText("Good night, " + user.getUsername() + ". They're waiting.");
    ui->score->setText("Score: " + QString::number(user.getScore()));
}

void GameWindow::drawLoading()
{
    QPixmap _loading(":/rsc/images/loading.png");
    loading->setGeometry(0, 0, 960, 540);
    _loading = _loading.scaled(960, 540,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    loading->setPixmap(_loading);
    loading->raise();
    loading->setDisabled(true);
    loading->hide();
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
    QFile file(filepath + "clocks.xml");

    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("resources");
    for( int i = 0; i < 3; ++i )  {
        xmlWriter.writeStartElement("clock");
        switch(clocks[i]->getState()) {
                case Clock::normal:
                    xmlWriter.writeCharacters("normal");
                    break;
                case Clock::hover:
                    xmlWriter.writeCharacters("normal");
                    break;
                case Clock::succeed:
                    xmlWriter.writeCharacters("succeed");
                    break;
                case Clock::failed:
                    xmlWriter.writeCharacters("failed");
                    break;
                }
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("timer");
        xmlWriter.writeCharacters(QString::number(clock_timers[i]->getTime()));
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
}

void GameWindow::clockRead(bool first_input)
{
    if (first_input) {
        clocks[0] = new Clock(this);
        clocks[1] = new Clock(this);
        clocks[2] = new Clock(this);

        clock_timers[0] = new Timer(this);
        clock_timers[1] = new Timer(this, 143);
        clock_timers[2] = new Timer(this, 243);
        return;
    } else  {

    QFile file(filepath + "clocks.xml");

    file.open(QIODevice::ReadOnly | QFile::Text);
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);
    xmlReader.readNext();
    int i = 0;
    while(!xmlReader.atEnd()){
        if(xmlReader.isStartElement()){
            if(xmlReader.name() == "clock"){
                QString state = xmlReader.readElementText();
                if(state ==  "normal") {
                    clocks[i] = new Clock(this, Clock::State::normal);
                }
                if(state ==  "hover") {
                    clocks[i] = new Clock(this, Clock::State::hover);
                }
                if(state ==  "succeed") {
                    clocks[i] = new Clock(this, Clock::State::succeed);
                }
                if(state ==  "failed") {
                    clocks[i] = new Clock(this, Clock::State::failed);
                }
            }
            if(xmlReader.name() == "timer"){
            clock_timers[i++] = new Timer(this, xmlReader.readElementText().toInt());
            }

        }
            xmlReader.readNext();
        }

    file.close();
    }
}

void GameWindow::writeMessage()  {
    QString message = "Hello, bla bla bla \n\n\n\n\n Enter your name";

        if (ui->message->text().length() == message.length())
        {
            timer_message->stop();
        }
        else
        {
            ui->message->setText(ui->message->text() + message[ui->message->text().length()]);
        }
}

void GameWindow::endLoading()
{
    // "затухание"
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    loading->setGraphicsEffect(eff);
    animationEnd = new QPropertyAnimation(eff, "opacity");
    animationEnd->setDuration(1700);
    animationEnd->setStartValue(1);
    animationEnd->setEndValue(0);
    animationEnd->setEasingCurve(QEasingCurve::OutBack);
    workerThread = new QThread(this);
    animationEnd->moveToThread(workerThread);

    connect(workerThread, &QThread::started, this, &GameWindow::processLoading);
    connect(animationEnd, &QPropertyAnimation::finished, workerThread, &QThread::quit);
    connect(workerThread, &QThread::finished, animationEnd, &QPropertyAnimation::deleteLater);

    workerThread->start();

    switch(ui->stackedWidget->currentIndex()){
         case 0:
             qDebug() << "case 0";
             clockRead(!user.exist());
             ui->stackedWidget->setCurrentIndex(1);
             drawBackground();
             drawShelf();
             drawClocks();
             break;
         case 1:
             qDebug() << "case 1";
             clearAll();
             ui->stackedWidget->setCurrentIndex(2);
             ui->view->setScene(scene);
             ui->view->setFocus();
             break;
         case 2:
             qDebug() << "case 2";
             //clearScene();
             ui->stackedWidget->setCurrentIndex(1);
             break;
         }

    qDebug() << workerThread->isRunning() << " " << workerThread->isFinished();
    qDebug() << animationEnd->state();
}

void GameWindow::startLoading()
{
    // "появление"
    loading->show();
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    loading->setGraphicsEffect(eff);
    animationStart = new QPropertyAnimation(eff,"opacity");
    animationStart->setDuration(1700);
    animationStart->setStartValue(0);
    animationStart->setEndValue(1);
    animationStart->setEasingCurve(QEasingCurve::InBack);
    animationStart->start(QPropertyAnimation::DeleteWhenStopped);
    qDebug() << "start loading";
    connect(animationStart, &QPropertyAnimation::finished, this, &GameWindow::endLoading);
}

void GameWindow::clearAll()
{
    for (int i = 0; i < 3; i++) {
        clocks[i]->hide();
    }
    ui->clock_1->hide();
    ui->clock_2->hide();
    ui->clock_3->hide();
    ui->time_1->hide();
    ui->time_2->hide();
    ui->time_3->hide();
    ui->label->hide();
    ui->score->hide();
    ui->shelf->hide();
}

void GameWindow::showAll()
{
   for (int i=0;i<3;i++){
       clocks[i]->hide();
   }
    ui->clock_1->show();
    ui->clock_2->show();
    ui->clock_3->show();
    ui->time_1->show();
    ui->time_2->show();
    ui->time_3->show();
    ui->label->show();
    ui->score->show();
    ui->shelf->show();
}

void GameWindow::processLoading()
{
   animationEnd->start(QPropertyAnimation::DeleteWhenStopped);
   while (animationEnd->state() != QPropertyAnimation::Stopped)
     QCoreApplication::processEvents();
}

void GameWindow::on_pushButton_clicked()
{
    if (ui->userLineEdit->text() == "")
        {
            ui->errorLabel->setText("You MUST have name!");
        }
    // TODO : регулярное выражение для всех форматов вида
    else if (ui->userLineEdit->text() == "death" || ui->userLineEdit->text() == "Death")
        {
            ui->errorLabel->setText("You MUST have name!");
        }
    else {
            user.setUsername(ui->userLineEdit->text());
            startLoading();
    }
}
