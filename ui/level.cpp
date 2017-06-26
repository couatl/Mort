#include "level.h"
#include "levelscene.h"
#include <QFile>

Level::Level(LevelScene* _scene) :
    scene(_scene)
{

}

Level::~Level()
{
    for (auto i: blocks)
        delete i;

    delete goal;
    delete player;
}

void Level::loadLevel(int level)
{
    //loading all data from xml file
    QFile file(filepath + QString::number(level)+".xml");

    if(file.exists()) {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            xmlReader.setDevice(&file);
            while (!xmlReader.atEnd() && !xmlReader.hasError())
            {
                QXmlStreamReader::TokenType token = xmlReader.readNext();
                if (token == QXmlStreamReader::StartDocument)
                    continue;
                if (token == QXmlStreamReader::StartElement)
                {
                    if (xmlReader.name() == "sources")
                        continue;
                    if (xmlReader.name() == "counts")
                        parseCounts();
                    if (xmlReader.name() == "elements")
                        parseElements();
                }
            }
            file.close();
        }
    }

    //adding items on scene
    for (auto i : blocks)
    {
        scene->addItem(i);
    }
}

void Level::parseCounts()
{
    while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "counts"))
    {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "blocks")
            {
                countBlocks = xmlReader.readElementText().toInt();
            }
            if (xmlReader.name() == "brokenBlocks")
                countBrokenBlocks = xmlReader.readElementText().toInt();
        }
        xmlReader.readNext();
    }
}

void Level::parseElements()
{
    while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "elements"))
    {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "element")
                parseElement();
        }
        xmlReader.readNext();
    }
}

void Level::parseElement()
{
    int x=0, y=0;
    QString type="";
    while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "element"))
    {
        if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "type")
                type = xmlReader.readElementText();
            if (xmlReader.name() == "x")
                x = xmlReader.readElementText().toInt();
            if (xmlReader.name() == "y")
                y = xmlReader.readElementText().toInt();
        }
        if (xmlReader.tokenType() == QXmlStreamReader::EndElement)
        {
            if (xmlReader.name() == "y")
            {
                if (type == "Block")
                {
                    waiter.setBlockBuilder(&builder);
                    waiter.constructBlock(x,y);
                    blocks.append(waiter.getBlock().first());
                }
                if (type == "BrokenBlock")
                {
                    waiter.setBlockBuilder(&builder_2);
                    waiter.constructBlock(x,y);
                    QList<AbstractBlock*> blockList = waiter.getBlock();
                    blocks.append(blockList.first());
                    blocks.append(blockList.last());
                }
                if (type == "Player")
                    player = new Player(x,y);
                if (type == "Goal")
                    goal = new Goal(x, y);
                if (type == "Key")
                    key = new Key(x, y);
            }
        }
        xmlReader.readNext();
    }
}
