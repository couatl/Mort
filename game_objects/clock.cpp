#include "clock.h"

#include <QPixmap>
#include <QFile>
#include <QTextStream>

Clock::Clock(QWidget* parent, State _state):
    QLabel(parent), state(_state)
{
    this->setVisible(false);
    this->setFixedSize(145, 237);
    this->setMouseTracking(true);

    draw();
}

void Clock::draw()
{
    QPixmap clock;
    switch(state) {
    case normal:
        clock.load(":/rsc/images/clock.png");
        break;
    case hover:
        clock.load(":/rsc/images/clock_hover.png");
        break;
    case succeed:
        clock.load(":/rsc/images/clock_suc.png");
        break;
    case failed:
        clock.load(":/rsc/images/clock_fail.png");
        break;
    }
    clock = clock.scaled(this->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    this->setPixmap(clock);
}

void Clock::setFocused()
{
    state = hover;
    draw();
}

void Clock::deleteFocus()
{
    state = normal;
    draw();
}

bool Clock::isFocused()
{
    return (state == hover);
}
