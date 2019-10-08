#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <SFML/Graphics.hpp>

class BaseObject {
protected:
    float posX;
    float posY;
    int speed;

public:
    float getPosX() { return posX; }
    float getPosY() { return posY; }
    virtual void updatePosition(float) = 0;

};

#endif

