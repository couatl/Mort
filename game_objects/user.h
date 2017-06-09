#ifndef USER_H
#define USER_H

#include <QString>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

class User
{
public:
    User();
    ~User();

    void setUsername(QString name);
    void setScore(unsigned score);

    QString getUsername() const;
    unsigned getScore() const;

    bool exist() const;

private:
    QString _username;
    unsigned _score;
    bool _exist;
};

#endif // USER_H
