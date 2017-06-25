#ifndef ABSTRACTBLOCK_H
#define ABSTRACTBLOCK_H

#include <QGraphicsItem>

class AbstractBlock : public QGraphicsItem
{
public:
    enum BlockType {
        Block = UserType + 30,
        BrokenBlock = UserType + 31
    };

    AbstractBlock(int _x = 0, int _y = 0, QGraphicsItem *parent = 0, int _width = 86, const QString& path = "");
    virtual ~AbstractBlock() {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void setImage(const QString& path, int _width);
    void setXY(int _x, int _y);
    void setType(BlockType _type);

    int type() const {
        return m_type;
    }

protected:
    QPixmap blockImage;

    int width;

    int x;
    int y;

    BlockType m_type;
};

#endif // ABSTRACTBLOCK_H
