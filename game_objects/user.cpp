#include "user.h"

#include "user.h"
#include <QDir>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

User::User()  {
    qDebug() << filepath;
//    QFile file("user.xml");
    QFile file(filepath + "user.xml");

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
                        QString tmp = xmlReader.readElementText();
                        _score = tmp.toInt();
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

    QFile file(filepath + "user.xml");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){     
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("sources");
        xmlWriter.writeStartElement("username");
        xmlWriter.writeCharacters(_username);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("score");
        xmlWriter.writeCharacters(QString::number(_score));
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }
}

void User::setScore(unsigned score){
    _score = score;

    QFile file(filepath + "user.xml");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){ 
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("sources");
        xmlWriter.writeStartElement("username");
        xmlWriter.writeCharacters(_username);
        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("score");
        xmlWriter.writeCharacters(QString::number(_score));
        xmlWriter.writeEndElement();
        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();
    }


}
