#ifndef ROCKET_H
#define ROCKET_H

#include "BaseObject.h"


class Rocket : public BaseObject {
private:
    float width;
    float height;
    int moveX;
    int moveY;
    sf::Sprite model;
    sf::FloatRect border;
    float scale = 0.30f;

public:
    Rocket(const sf::Texture*, sf::FloatRect);

    sf::Sprite& getBox() { return model; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    void setMoveX(int move) { moveX = move; }
    void setMoveY(int move) { moveY = move; }

    void updatePosition(float);
    void setPosition(float posX, float posY);
};

#endif
