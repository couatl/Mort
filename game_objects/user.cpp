#include "user.h"

#include "user.h"
#include <QDir>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

User::User()  {
//    QFile file("user.xml");
    QFile file("/Users/sharlina/Documents/coding/Mort/Mort/docs/user.xml");

    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly)){
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(&file);
            xmlReader.readNext();
            while(!xmlReader.atEnd()){
                if(xmlReader.isStartElement()){
                    if(xmlReader.name() == "username"){
                        _username = xmlReader.readElementText();
                    }
                    if(xmlReader.name() == "score"){
                        _score = xmlReader.readElementText().toInt();
                    }
                }
                    xmlReader.readNext();
                }
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
    if (_username != "")
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

//    QFile file("user.xml");
    QFile file("/Users/sharlina/Documents/coding/Mort/Mort/docs/user.xml");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){     
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("username");
        xmlWriter.writeCharacters(_username);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("score");
        xmlWriter.writeCharacters(QString::number(_score));
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}

void User::setScore(unsigned score){
    _score = score;

//    QFile file("user.xml");
    QFile file("/Users/sharlina/Documents/coding/Mort/Mort/docs/user.xml");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){ 
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("username");
        xmlWriter.writeCharacters(_username);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("score");
        xmlWriter.writeCharacters(QString::number(_score));
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}
