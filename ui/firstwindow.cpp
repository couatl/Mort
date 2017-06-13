#include "firstwindow.h"
#include <QPalette>
#include <QFontDatabase>

FirstWindow::FirstWindow(View* _view, QWidget *parent, User* _user) :
    QGraphicsScene(parent),
//    ui(new Ui::FirstWindow),
    user(_user),
    view(_view)
{
//    ui->setupUi(this);

//    QPixmap background(":/rsc/images/start_window2.png");
//    background = background.scaled(ui->background->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
//    ui->background->setPixmap(background);
//    ui->background->lower();

    QPixmap _background(":/rsc/images/start_window2.png");
    _background = _background.scaled(780, 439, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    background = new QGraphicsPixmapItem(_background);
    this->addItem(background);
    this->setSceneRect(90, 30, 780, 439);

    view->sceneSet(this);

    timer_message = new Timer(nullptr, 60, 300);
    connect(timer_message, &Timer::timeout, this, &FirstWindow::writeMessage);

    int id = QFontDatabase::addApplicationFont(":/rsc/resources/ITCBLKAD.TTF");
    QString font_name = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(font_name, 38, QFont::Normal);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);

    labelMessage = new QLabel(view);
    labelMessage->setFont(font);
    labelMessage->setPalette(palette);
    labelMessage->setObjectName(QString("labelMessage"));
    labelMessage->setGeometry(470, 270, 80, 34);

    errorMessage = new QLabel(view);
    errorMessage->setFont(font);
    errorMessage->setPalette(palette);
    errorMessage->setObjectName(QString("errorMessage"));
    errorMessage->setGeometry(340, 310, 220, 40);

    usernameLine = new QLineEdit(view);
    usernameLine->setFont(font);
    usernameLine->setGeometry(340, 270, 120, 34);

    okButton = new QPushButton(view);
    okButton->setFont(font);
    okButton->setPalette(palette);
    okButton->setObjectName(QString("okButton"));
    okButton->setGeometry(470, 270, 80, 34);
    connect(okButton, &QPushButton::clicked, this, &FirstWindow::ok_clicked);
}

FirstWindow::~FirstWindow()
{

}

void FirstWindow::ok_clicked()
{
    if (usernameLine->text() == "")
    {
        errorMessage->setText("You MUST have name!");
    }
    else {
        user->setUsername(usernameLine->text());
        emit ok_click();
    }
    emit destroy();
}

void FirstWindow::writeMessage()
{
    QString message = "Hello, bla bla bla";

    if (labelMessage->text().length() == message.length())
    {
        timer_message->stop();
    }
    else
    {
        labelMessage->setText(labelMessage->text() + message[labelMessage->text().length()]);
    }
}
