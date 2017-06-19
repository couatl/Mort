#ifndef CLOCK_H
#define CLOCK_H

#include <QLabel>

#include <QPixmap>
#include <QFile>
#include <QTextStream>

#define _normal 1
#define _hover 2
#define _succeed 3
#define _failed 4

class Clock: public QLabel{
private:
    class State* _state;
public:
    inline Clock(QWidget* parent, class State * state = nullptr);
    inline void MakeNormal( );

    inline void MakeHover( );

    inline void MakeSucceed( );

    inline void MakeFailed( );

    inline bool IsFocused();

    inline bool IsNormal();

    inline int GetState();

    inline void setState(State *s)
        {
            _state = s;
        }
};

class State {
public:
    inline virtual void makeNormal( Clock*){}
    inline virtual void makeHover( Clock*){}
    inline virtual void makeSucceed( Clock*){}
    inline virtual void makeFailed( Clock*){}
    inline virtual bool isFocused(){
        return false;
    }
    inline virtual bool isNormal(){
        return true;
    }
    inline virtual int getState(){
        return _failed;
    }
    inline virtual void drawClock( Clock* ){}
};

class NormalState: public State {
public:
    inline void makeHover( Clock* clock);
    inline void makeSucceed( Clock* clock);
    inline void makeFailed( Clock* clock);
    inline bool isFocused(){
        return false;
    }
    inline bool isNormal(){
        return true;
    }
    inline int getState(){
        return _normal;
    }
    void drawClock( Clock* clck ){
        QPixmap clock;
        clock.load(":/rsc/images/clock.png");
        clock = clock.scaled(clck->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        clck->setPixmap(clock);
    }
};

class HoverState: public State {
public:
    inline void makeNormal( Clock* clock);
    inline void makeSucceed( Clock* clock);
    inline void makeFailed( Clock* clock);
    inline bool isFocused(){
    return true;
    }
    inline bool isNormal(){
    return false;
    }
    inline int getState(){
        return _hover;
    }
    inline void drawClock( Clock* clck ){
        QPixmap clock;
        clock.load(":/rsc/images/clock_hover.png");
        clock = clock.scaled(clck->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        clck->setPixmap(clock);
    }
};

class SucceedState: public State {
public:
    inline bool isFocused(){
        return false;
    }
    inline bool isNormal(){
        return false;
    }
    inline int getState(){
        return _succeed;
    }
    inline void drawClock( Clock* clck ){
        QPixmap clock;
        clock.load(":/rsc/images/clock_suc.png");
        clock = clock.scaled(clck->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        clck->setPixmap(clock);
    }
};

class FailedState: public State {
public:
    inline bool isFocused(){
        return false;
    }
    inline bool isNormal(){
        return false;
    }
    inline int getState(){
        return _failed;
    }
    inline void drawClock( Clock* clck ){
        QPixmap clock;
        clock.load(":/rsc/images/clock_fail.png");
        clock = clock.scaled(clck->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        clck->setPixmap(clock);
    }
};


inline void NormalState::makeHover( Clock* clock){
    clock->setState(new HoverState());
}
inline void NormalState::makeSucceed( Clock* clock){
    clock->setState(new SucceedState());
}
inline void NormalState::makeFailed( Clock* clock){
    clock->setState(new FailedState());
}

inline void HoverState::makeNormal( Clock* clock){
    clock->setState(new NormalState());
}
void HoverState::makeSucceed( Clock* clock){
    clock->setState(new SucceedState());
}
inline void HoverState::makeFailed( Clock* clock){
    clock->setState(new FailedState());
}

inline Clock::Clock(QWidget* parent, State *state):
        QLabel(parent), _state(state){
    this->setVisible(false);
    this->setFixedSize(145, 237);
    this->setMouseTracking(true);
    _state->drawClock(this);
}

inline void Clock::MakeNormal( ){
    _state->makeNormal( this );
    _state->drawClock( this );
}

inline void Clock::MakeHover( ){
    _state->makeHover( this );
    _state->drawClock( this );
}

inline void Clock::MakeSucceed( ){
    _state->makeSucceed( this );
    _state->drawClock( this );
}

inline void Clock::MakeFailed( ){
    _state->makeFailed( this );
    _state->drawClock( this );
}

inline bool Clock::IsFocused(){
    return _state->isFocused();
}

inline bool Clock::IsNormal(){
    return _state->isNormal();
}

inline int Clock::GetState(){
    return _state->getState();
}

#endif // CLOCK_H
