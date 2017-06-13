#include "user.h"

#include "user.h"
#include <QDir>
#include <QDebug>

User::User()  {
//    QFile file("./user.qml");
    QFile file("/Users/sharlina/Documents/coding/Mort/Mort/docs/user.qml");

    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly)){
            QString tmp = QString(file.readAll());
            _username = tmp.left(tmp.indexOf(" "));
            tmp = tmp.right(tmp.size() - tmp.indexOf(" "));
            _score = tmp.toInt();
            _exist = true;
            file.close();
        }
    } else {
        _username = "";
        _score = 0;
        _exist = false;
    }
}

User::~User()
{
    setUsername(this->_username);
}

QString User::getUsername() const {
    return _username;
}

unsigned User::getScore() const {
    return _score;
}

bool User::exist() const
{
    return _exist;
}

void User::setUsername(QString name)  {
    _username = name;

//    QFile file("./user.qml");
    QFile file("/Users/sharlina/Documents/coding/Mort/Mort/docs/user.qml");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream (&file);
        stream << _username << " " << _score;
        file.close();
    }
}

void User::setScore(unsigned score){
    _score = score;

//    QFile file("./user.qml");
    QFile file("/Users/sharlina/Documents/coding/Mort/Mort/docs/user.qml");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream (&file);
        stream << _username << " " << _score;
        file.close();
    }
}
