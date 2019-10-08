#include "Rocket.h"
#include <iostream>
#include <cmath>

using namespace sf;


Rocket::Rocket(const Texture* texture, FloatRect border) {

    model.setTexture(*texture);
    model.setScale(scale, scale);

    width = model.getGlobalBounds().width;
    height = model.getGlobalBounds().height;
    moveX = 0;
    moveY = 0;
    speed = 250;

    this->border = border;
}

void Rocket::updatePosition(float timeElapsed) {

    float tmpX = round(speed * moveX * timeElapsed);
    float tmpY = round(speed * moveY * timeElapsed);

    if ((posX + tmpX) > border.left && 
        (posX + tmpX + width) < (border.left + border.width)) {
        posX += tmpX;
    }
    if ((posY + tmpY) > border.top && 
        (posY + tmpY + height) < (border.top + border.height)) {
        posY += tmpY;
    }

    model.setPosition(posX, posY);
}

void Rocket::setPosition(float posX, float posY) {
    this->posX = posX;
    this->posY = posY;
   // model.setPosition(posX, posY);
}
