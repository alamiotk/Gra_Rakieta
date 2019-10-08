#include "Meteor.h"

Meteor::Meteor(float posX, float scale, const sf::Texture* texture) {

    setTexture(*texture);
    setScale(scale, scale);

    float width = getGlobalBounds().width;

    radius = width / 2;
    this->posX = posX;
    posY = -radius;

    setPosition(posX, posY);

    speed = 300;
}

void Meteor::updatePosition(float timeElapsed) {
    posY += round(speed * timeElapsed);
    setPosition(posX, posY);
}

float Meteor::calcDistSquared(int posX, int posY) {
    return pow(this->posX - posX, 2) + pow(this->posY - posY, 2);
}
