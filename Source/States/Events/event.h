#ifndef EVENT_H
#define EVENT_H

struct Event
{
    enum Type
    {
        generic,
        mouseMoveEvent,
        keyboardInput,
    };

    Type type = generic;
};

struct MouseMoveEvent : public Event
{
    double xPos;
    double yPos;

    MouseMoveEvent(double x, double y) : xPos( x ), yPos(y)
    {        type = mouseMoveEvent;   }
};

#endif // EVENT_H
