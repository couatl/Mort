#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QMessageBox>
#include <QFontDatabase>
#include <QFont>
#include <QTextStream>
#include <QFile>
#include "aboutdialog.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    user(User()),
    timers(QVector<Timer*>(3)),
    clocks(QVector<Clock*>(3)),
    times(QVector<QLabel*>(3))
{
    ui->setupUi(this);
    this->setWindowTitle("Mort");

    times[0] = ui->time_1;
    times[1] = ui->time_2;
    times[2] = ui->time_3;

    clockRead(true);
    drawClocks();
    drawBackground();

    connect(ui->actionAbout, &QAction::triggered, this, &GameWindow::about);
}

GameWindow::~GameWindow()
{
    for (auto i = timers.begin(); i != timers.end(); ++i) {
        delete *i;
    }
    delete ui;
}

void GameWindow::about()
{
    AboutDialog dialog(this);
    dialog.exec();
}


void GameWindow::update()
{
    for (int i = 0; i < 3; i++) {
        timers[i]->decrease();
        if ( timers[i]->getTime() > 0 )
        {
            QString time = QString::number(timers[i]->getTime());
            times[i]->setText(time);
        }
        else {
            timers[i]->stop();
        }
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

    int id = QFontDatabase::addApplicationFont(":/rsc/resources/ITCBLKAD.TTF");
//    int id = QFontDatabase::addApplicationFont("C:/Mort/Mort/resources/ITCBLKAD.TTF");
    QString font_name = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(font_name, 32, QFont::Normal);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);

    for (int i = 0; i < 3; i++) {
        times[i]->setFont(font);
        times[i]->setPalette(palette);
        QString time = QString::number(timers[i]->getTime());
        times[i]->setText(time);
    }

//    connect(timers[0], &Timer::timeout, this, &GameWindow::update);
}

void GameWindow::drawBackground()
{
    QPixmap background(":/rsc/images/bg960x540.png");
//    QPixmap background("C:/Mort/Mort/images/bg960x540.png");
    background = background.scaled(this->size());
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
    this->setFixedSize(960, 540);
//    QPixmap shelf("C:/Mort/Mort/images/shelf.png");

    QPixmap shelf(":/rsc/images/shelf.png");
    shelf = shelf.scaled(ui->shelf->size());
    ui->shelf->setPixmap(shelf);
}

void GameWindow::clockWrite()
{

}

void GameWindow::clockRead(bool first_input)
{
    if (first_input) {
        clocks[0] = new Clock(this);
        clocks[1] = new Clock(this);
        clocks[2] = new Clock(this);

        timers[0] = new Timer(this);
        timers[1] = new Timer(this, 143);
        timers[2] = new Timer(this, 243);
        return;
    }

    QFile inputFile("../docs/clocks.txt");

    if (!inputFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", inputFile.errorString());
    }

    //normal 61
    QTextStream in(&inputFile);
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(" ");

    }

}

