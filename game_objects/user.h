#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();
    void write();
    void read();

private:
    unsigned score;
    QString username;
};

#endif // USER_H
