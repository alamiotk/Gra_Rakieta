#include "GameObjects.h"
#include "Collision.h"

using namespace sf;

GameObjects::GameObjects(int width, int height) {
    this->width = width;
    this->height = height;

    texBackground = new Texture();
    texMeteor = new Texture();
    texRocket = new Texture();

    mainBox.setSize(Vector2f((float)width, (float)height));

    font = new Font();
    for (int i = 0; i < 3; i++) {
        Text* text = new Text();
        text->setFont(*font);
        text->setFillColor(Color::White);
        text->setStyle(Text::Bold);
        textLines.push_back(text);
    }

    loadFiles();
    rocket = new Rocket(texRocket, mainBox.getGlobalBounds());
    init();
}


GameObjects::~GameObjects() {
    delete texBackground, texMeteor, texRocket;
    delete rocket;
}

void GameObjects::drawGame(RenderWindow& window, const int& rockets, const bool& runGame) {
    window.clear();

    window.draw(mainBox);
    for (const Meteor& meteor : meteors) {
        window.draw(meteor);
    }

    window.draw(rocket->getBox());

    if (!runGame) {
        window.draw(endGameBox);
        window.draw(*textLines[1]);
    }

    window.display();
}

bool GameObjects::isSpawnPossible(const int& posX, const float& scale) {
    std::list<Meteor>::reverse_iterator itr = meteors.rbegin();
    bool possible = true;
    float radius = texMeteor->getSize().y / 2 * scale;
    while (itr != meteors.rend() &&
        (itr->getPosY() - itr->getRadius() - spacing) < 0) {
        possible &= itr->calcDistSquared(posX, -radius) > pow((spacing + itr->getRadius() + radius), 2);
        itr++;
    }
    return possible;
}

GameObjects& GameObjects::operator+=(const Vector2f& vctr2f) {
    meteors.push_back(Meteor(vctr2f.x, vctr2f.y, texMeteor));
    return *this;
}

void GameObjects::clearMeteors() {
    meteors.clear();
}

void GameObjects::loadFiles() {

    texBackground->loadFromFile("/home/ala/Desktop/rocket_src/img/space.png");
    Collision::CreateTextureAndBitmask(*texMeteor, "/home/ala/Desktop/rocket_src/img/meteorekc.png");
    Collision::CreateTextureAndBitmask(*texRocket, "/home/ala/Desktop/rocket_src/img/rocket.png");
    font->loadFromFile("/home/ala/Desktop/rocket_src/font/bobcayge.ttf");
}

void GameObjects::init() {
    mainBox.setTexture(texBackground);

    textLines[1]->setString("GAME OVER");
    textLines[1]->setCharacterSize(40);
    FloatRect textBounds = textLines[1]->getGlobalBounds();
    textLines[1]->setOrigin(textBounds.width / 2, textBounds.height);
    textLines[1]->setPosition(width / 2, height / 2);

    endGameBox.setSize(Vector2f(width, height));
    endGameBox.setFillColor(Color(26, 26, 26, 170));
}
