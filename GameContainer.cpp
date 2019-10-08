#include <iostream>
#include <chrono>
#include <string>
#include "GameContainer.h"

using namespace sf;
using namespace std;

GameContainer::GameContainer(int width, int height) : distribution(0, width), objects(width, height) {
    
    window.create(VideoMode(width, height), "Rocket world");
    generator.seed((int) chrono::system_clock::now().time_since_epoch().count());
}

void GameContainer::startGame() {

    Clock clock;
    Time time;
    resetGame();

    while (window.isOpen()) {

        readInputs();

        time = clock.restart();
        if (runGame) {
            updateGame(time);

            if (!collided)
                checkCollisions();
            else {
                handleCollision(time, flicker, cooldown, flickState);
            }
        }

        if (rockets < 0) {
            runGame = false;
            rockets = 0;
            objects.rocket->getBox().setColor(Color::Transparent);
        }

        objects.drawGame(window, rockets, runGame);
    }
}

void GameContainer::readInputs() {
    Event event;

    while (window.pollEvent(event)) {
        
        Rocket* rocket = objects.getRocket();
        if (event.type == Event::Closed)
            window.close();

        else if (event.type == Event::KeyPressed) {
            switch (event.key.code)
            {
            case Keyboard::Left:
                rocket->setMoveX(-1);
                break;
            case Keyboard::Right:
                rocket->setMoveX(1);
                break;
            case Keyboard::Up:
                rocket->setMoveY(-1);
                break;
            case Keyboard::Down:
                rocket->setMoveY(1);
            }
        }
        else if (event.type == Event::KeyReleased) {
            switch (event.key.code)
            {
            case Keyboard::Left:
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    rocket->setMoveX(1);
                else
                    rocket->setMoveX(0);
                break;
            case Keyboard::Right:
                if (Keyboard::isKeyPressed(Keyboard::Left))
                    rocket->setMoveX(-1);
                else
                    rocket->setMoveX(0);
                break;
            case Keyboard::Up:
                if (Keyboard::isKeyPressed(Keyboard::Down))
                    rocket->setMoveY(1);
                else
                    rocket->setMoveY(0);
                break;
            case Keyboard::Down:
                if (Keyboard::isKeyPressed(Keyboard::Up))
                    rocket->setMoveY(-1);
                else
                    rocket->setMoveY(0);
            }
        }
    }
}

void GameContainer::updateGame(const Time& time) {

    elapsedInMillis += time.asMilliseconds();

    for (Meteor& meteor : objects.meteors)
        meteor.updatePosition(time.asSeconds());

    if (elapsedInMillis > SPAWNRATE) {
        int dice_roll = distribution(generator);
        float scale = (dice_roll % 3 * 25 + BASE_RADIUS) * 0.01f;
        while (!objects.isSpawnPossible(dice_roll, scale)) {
            dice_roll = distribution(generator);
        }
        objects += Vector2f((float) dice_roll, scale);
        elapsedInMillis -= SPAWNRATE;
    }

    objects.rocket->updatePosition(time.asSeconds());
}

bool GameContainer::isSimpleCollision(const Vector2f& meteor, const float& radius, const FloatRect& rckt) const {

    float distX = abs(rckt.left + rckt.width / 2 - meteor.x);
    float distY = abs(rckt.top + rckt.height / 2 - meteor.y);

    if (distX > rckt.width / 2 + radius)
        return false;
    if (distY > rckt.height / 2 + radius)
        return false;
    if (distX <= rckt.width / 2)
        return true;
    if (distY <= rckt.height / 2)
        return true;

    float cornerDist = pow(distX - rckt.width / 2, 2) + pow(distY - rckt.height / 2, 2);
    return cornerDist <= pow(radius, 2);
}

void GameContainer::checkCollisions() {
    for (const Meteor& meteor : objects.meteors) {
        if (isSimpleCollision(meteor.getPosition(), meteor.getRadius(), objects.rocket->getBox().getGlobalBounds())) {

                collided = true;
                rockets--;
                return;
        }
    }
}

void GameContainer::handleCollision(const Time& time, int& flicker, int& cooldown, int& flickState) {
    objects.rocket->getBox().setColor(Color(255, 255, 255, 140 - flickState * 80));
    if (flicker < 0) {
        flickState *= -1;
        flicker = 50;
    }

    if (cooldown < 0) {
        collided = false;
        cooldown = 2000;
        objects.rocket->getBox().setColor(Color::White);
    }
    cooldown -= time.asMilliseconds();
    flicker -= time.asMilliseconds();
}

void GameContainer::resetGame() {
    runGame = true;
    Rocket* rocket = objects.rocket;
    objects.clearMeteors();
    rocket->setPosition(window.getSize().x / 2 - rocket->getWidth() / 2, window.getSize().y - rocket->getHeight() - 30);
    collided = false;
    rockets = 3;
    elapsedInMillis = SPAWNRATE+1;
    cooldown = 2000;
    flicker = 100;
    flickState = 1;
}

