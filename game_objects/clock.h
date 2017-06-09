#ifndef CLOCK_H
#define CLOCK_H

#include <QLabel>

// TODO: Clock + timer widget
// ->

class Clock : public QLabel
{
    Q_OBJECT
public:
    enum State {
        normal,
        hover,
        succeed,
        failed
    };

    Clock(QWidget* parent = nullptr, State _state = normal);

    State getState() const {
        return state;
    }

    void draw();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    State state;
};

#endif // CLOCK_H
