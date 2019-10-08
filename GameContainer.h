#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>
#include <random>
#include "GameObjects.h"


class GameContainer {
private:
    const static int BASE_RADIUS = 50;
    const static int SPAWNRATE = 600;

    sf::RenderWindow window;
    GameObjects objects;

    int elapsedInMillis;
    int rockets;
    int cooldown;
    int flicker;
    int flickState;
    bool collided;
    bool runGame;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

    void readInputs();
    void updateGame(const sf::Time&);
    void checkCollisions();
    void handleCollision(const sf::Time&, int&, int&, int&);
    bool isSimpleCollision(const sf::Vector2f&, const float&, const sf::FloatRect&) const;
    void resetGame();
public:
    GameContainer(int, int);
    void startGame();

};

#endif
