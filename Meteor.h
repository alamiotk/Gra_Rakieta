#include "BaseObject.h"
#include <cmath>


class Meteor : public BaseObject, public sf::Sprite {
private:
    float radius;

public:
    Meteor(float, float, const sf::Texture*);

    void updatePosition(float);
    float calcDistSquared(int, int);
    float getRadius() const { return radius; }
};

