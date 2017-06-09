#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QMessageBox>
#include <QFontDatabase>
#include <QFont>
#include "aboutdialog.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow),
    user(User())
{
    ui->setupUi(this);

    this->setWindowTitle("Mort");

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

//    QPixmap clock("C:/Mort/Mort/images/clock.png");
    QPixmap clock(":/rsc/images/clock.png");
    clock = clock.scaled(ui->clock_1->size());
    ui->clock_1->setPixmap(clock);
    ui->clock_2->setPixmap(clock);
    ui->clock_3->setPixmap(clock);

    int id = QFontDatabase::addApplicationFont(":/rsc/resources/ITCBLKAD.TTF");
//    int id = QFontDatabase::addApplicationFont("C:/Mort/Mort/resources/ITCBLKAD.TTF");
    QString font_name = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(font_name, 32, QFont::Normal);
    ui->time_1->setFont(font);
    palette.setColor(QPalette::WindowText, Qt::white);
    ui->time_1->setPalette(palette);

    timer = new Timer();

    connect(timer, &Timer::timeout, this, &GameWindow::update);
    connect(ui->actionAbout, &QAction::triggered, this, &GameWindow::about);
}

GameWindow::~GameWindow()
{
    user.write();
    delete ui;
}

void GameWindow::about()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void GameWindow::update()
{
     timer->decrease();
    if ( timer->getTime() > 0)
    {
        QString time = QString::number(timer->getTime());
        ui->time_1->setText(time);
    }
    else
    {
        timer->stop();
    }
}
