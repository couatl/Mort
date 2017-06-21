#include "clockfacade.h"

ClockFacade::ClockFacade():
    clock_timers(QVector<Timer*>(3)),
    clocks(QVector<Clock*>(3))
{ }

ClockFacade::~ClockFacade()
{
    for (auto i = clock_timers.begin(); i != clock_timers.end(); ++i) {
        delete *i;
    }

    for (auto i = clocks.begin(); i != clocks.end(); ++i) {
        delete *i;
    }
}

void ClockFacade::read(QWidget *widget)
{
    QFile file(filepath + "clocks.xml");
    if (!file.exists()) {
        clocks[0] = new Clock(widget);
        clocks[1] = new Clock(widget);
        clocks[2] = new Clock(widget);

        clock_timers[0] = new Timer(widget);
        clock_timers[1] = new Timer(widget, 143);
        clock_timers[2] = new Timer(widget, 243);
        return;
    } else  {

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
                    clocks[i] = new Clock(widget, new NormalState());
                }
                if(state ==  "hover") {
                    clocks[i] = new Clock(widget, new HoverState());
                }
                if(state ==  "succeed") {
                    clocks[i] = new Clock(widget, new SucceedState());
                }
                if(state ==  "failed") {
                    clocks[i] = new Clock(widget, new FailedState());
                }
            }
            if(xmlReader.name() == "timer"){
                clock_timers[i++] = new Timer(widget, xmlReader.readElementText().toInt());
            }

        }
            xmlReader.readNext();
        }

    file.close();
    }
}

void ClockFacade::write()
{
    QFile file(filepath + "clocks.xml");

    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("resources");
    for( int i = 0; i < 3; ++i )  {
        xmlWriter.writeStartElement("clock");
        switch(clocks[i]->GetState()) {
                case _normal:
                    xmlWriter.writeCharacters("normal");
                    break;
                case _hover:
                    xmlWriter.writeCharacters("normal");
                    break;
                case _succeed:
                    xmlWriter.writeCharacters("succeed");
                    break;
                case _failed:
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

void ClockFacade::hide()
{
    for (int i=0; i < 3; i++){
        clocks[i]->hide();
    }
}

void ClockFacade::show()
{
    for (int i=0; i < 3; i++){
        clocks[i]->show();
    }
}

void ClockFacade::draw()
{
    for (int i = 0; i < 3; i++) {
        clocks[i]->setVisible(true);
    }

    clocks[0]->setGeometry(230, 150, 145, 237);
    clocks[1]->setGeometry(410, 150, 145, 237);
    clocks[2]->setGeometry(590, 150, 145, 237);
}

int ClockFacade::press(int &id_selected)
{
    if (clocks[0]->underMouse() || clocks[1]->underMouse() || clocks[2]->underMouse()){
        for(int i = 0; i < 3; ++i){
            if (clocks[i]->underMouse() && (clocks[i]->IsNormal() || clocks[i]->IsFocused())) {
                if(clocks[i]->IsFocused())
                    return i;
                else if(id_selected == -1) {
                    clocks[i]->MakeHover();
                    id_selected = i;
                }
                else {
                    clocks[id_selected]->MakeNormal();
                    id_selected = i;
                    clocks[i]->MakeHover();
                }
                }
        }
    } else {
        for(int i = 0; i < 3; ++i)
           clocks[i]->MakeNormal();
    }
    return -1;
}

void ClockFacade::fail(int index)
{
    clocks[index]->MakeFailed();
    clock_timers[index]->setTime(0);
}

void ClockFacade::succeed(int index)
{
    clocks[index]->MakeSucceed();
    clock_timers[index]->stop();
}

void ClockFacade::stop(int index)
{
    clock_timers[index]->stop();
}

int ClockFacade::time(int index)
{
    return clock_timers[index]->getTime();
}
