#ifndef CLOCK_H
#define CLOCK_H

#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QTextStream>

//      State pattern

#define _normal 1
#define _hover 2
#define _succeed 3
#define _failed 4

class Clock: public QLabel{
private:
    class State* _state;
public:
    inline Clock(QWidget*);
    inline Clock(QWidget* , class State *);
    inline void MakeNormal();
    inline void MakeHover();
    inline void MakeSucceed();
    inline void MakeFailed();
    inline bool IsFocused();
    inline bool IsNormal();
    inline int GetState();
    inline void setState(State *s);
};

class State {
public:
    inline virtual void makeNormal( Clock*) = 0;
    inline virtual void makeHover( Clock*) = 0;
    inline virtual void makeSucceed( Clock*) = 0;
    inline virtual void makeFailed( Clock*) = 0;
    inline virtual bool isFocused() = 0;
    inline virtual bool isNormal() = 0;
    inline virtual int getState() = 0;
    inline virtual void drawClock( Clock* ) = 0;
};

class NormalState: public State {
    inline virtual void makeNormal( Clock*);
    inline virtual void makeHover( Clock*);
    inline virtual void makeSucceed( Clock*);
    inline virtual void makeFailed( Clock*);
    inline virtual bool isFocused();
    inline virtual bool isNormal();
    inline virtual int getState();
    inline virtual void drawClock( Clock* );
};
class HoverState: public State {
    inline virtual void makeNormal( Clock*);
    inline virtual void makeHover( Clock*);
    inline virtual void makeSucceed( Clock*);
    inline virtual void makeFailed( Clock*);
    inline virtual bool isFocused();
    inline virtual bool isNormal();
    inline virtual int getState();
    inline virtual void drawClock( Clock* );
};
class SucceedState: public State {
    inline virtual void makeNormal( Clock*);
    inline virtual void makeHover( Clock*);
    inline virtual void makeSucceed( Clock*);
    inline virtual void makeFailed( Clock*);
    inline virtual bool isFocused();
    inline virtual bool isNormal();
    inline virtual int getState();
    inline virtual void drawClock( Clock* );
};
class FailedState: public State {
    inline virtual void makeNormal( Clock*);
    inline virtual void makeHover( Clock*);
    inline virtual void makeSucceed( Clock*);
    inline virtual void makeFailed( Clock*);
    inline virtual bool isFocused();
    inline virtual bool isNormal();
    inline virtual int getState();
    inline virtual void drawClock( Clock* );
};

//NormalState
inline void NormalState::makeHover( Clock* clock){
    clock->setState(new HoverState());
}
inline void NormalState::makeSucceed( Clock* clock){
    clock->setState(new SucceedState());
}
inline void NormalState::makeFailed( Clock* clock){
    clock->setState(new FailedState());
}
inline void NormalState::makeNormal(Clock * clock){
    Q_UNUSED(clock)
}
inline bool NormalState::isFocused(){
    return false;
}
inline bool NormalState::isNormal(){
    return true;
}
inline int NormalState::getState(){
    return _normal;
}
inline void NormalState::drawClock( Clock* clck ){
    QPixmap clock;
    clock.load(":/rsc/images/clock.png");
    clock = clock.scaled(clck->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    clck->setPixmap(clock);
}

//HoverState
inline void HoverState::makeHover( Clock* clock){
    Q_UNUSED(clock)
}
inline void HoverState::makeSucceed( Clock* clock){
    clock->setState(new SucceedState());
}
inline void HoverState::makeFailed( Clock* clock){
    clock->setState(new FailedState());
}
inline void HoverState::makeNormal(Clock * clock){
    clock->setState(new NormalState());
}
inline bool HoverState::isFocused(){
    return true;
}
inline bool HoverState::isNormal(){
    return false;
}
inline int HoverState::getState(){
    return _hover;
}
inline void HoverState::drawClock( Clock* clck ){
    QPixmap clock;
    clock.load(":/rsc/images/clock_hover.png");
    clock = clock.scaled(clck->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    clck->setPixmap(clock);
}

//SucceedState
inline void SucceedState::makeHover( Clock* clock){
    Q_UNUSED(clock)
}
inline void SucceedState::makeSucceed( Clock* clock){
    Q_UNUSED(clock)
}
inline void SucceedState::makeFailed( Clock* clock){
    Q_UNUSED(clock)
}
inline void SucceedState::makeNormal(Clock * clock){
    Q_UNUSED(clock)
}
inline bool SucceedState::isFocused(){
    return false;
}
inline bool SucceedState::isNormal(){
    return false;
}
inline int SucceedState::getState(){
    return _succeed;
}
inline void SucceedState::drawClock( Clock* clck ){
    QPixmap clock;
    clock.load(":/rsc/images/clock_suc.png");
    clock = clock.scaled(clck->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    clck->setPixmap(clock);
}

//FailedState
inline void FailedState::makeHover( Clock* clock){
    Q_UNUSED(clock)
}
inline void FailedState::makeSucceed( Clock* clock){
    Q_UNUSED(clock)
}
inline void FailedState::makeFailed( Clock* clock){
    Q_UNUSED(clock)
}
inline void FailedState::makeNormal(Clock * clock){
    Q_UNUSED(clock)
}
inline bool FailedState::isFocused(){
    return false;
}
inline bool FailedState::isNormal(){
    return false;
}
inline int FailedState::getState(){
    return _failed;
}
inline void FailedState::drawClock( Clock* clck ){
    QPixmap clock;
    clock.load(":/rsc/images/clock_fail.png");
    clock = clock.scaled(clck->size(), Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    clck->setPixmap(clock);
}

//Clock
inline Clock::Clock(QWidget* parent):
QLabel(parent){
    _state = new NormalState();
    this->setVisible(false);
    this->setFixedSize(145, 237);
    this->setMouseTracking(true);
    _state->drawClock(this);
}

inline Clock::Clock(QWidget* parent, State *state):
QLabel(parent), _state(state){
    this->setVisible(false);
    this->setFixedSize(145, 237);
    this->setMouseTracking(true);
    _state->drawClock(this);
}
inline void Clock::setState(State *s) {
    _state = s;
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
