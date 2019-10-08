#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>
#include <string>
#include "Rocket.h"
#include "Meteor.h"

class GameObjects {

private:
    int width;
    int height;
    const float spacing = 60.0f;
    std::vector<sf::Text*> textLines;

    sf::RectangleShape mainBox;
    sf::RectangleShape endGameBox;
    sf::Texture* texRocket;
    sf::Texture* texBackground;
    sf::Texture* texMeteor;
    sf::Font* font;
    Rocket* rocket;

    std::list<Meteor> meteors;

    void init();
    void loadFiles();

public:
    GameObjects(int ,int);
    ~GameObjects();

    Rocket* getRocket() { return rocket; }
    void drawGame(sf::RenderWindow&, const int&, const bool&);

    GameObjects& operator+=(const sf::Vector2f&);

    void clearMeteors();
    bool isSpawnPossible(const int&, const float&);

    friend class GameContainer;
};

#endif
