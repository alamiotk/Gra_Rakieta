/*
 * File:   collision.cpp
 * Author: Nick (original version), ahnonay (SFML2 compatibility)
 */
#include <SFML/Graphics.hpp>
#include <map>
#include "Collision.h"


namespace Collision {
    class BitmaskManager {
    private:
        std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
    public:

        sf::Uint8* CreateMask(const sf::Texture* tex, const sf::Image& img) {
            sf::Uint8* mask = new sf::Uint8[tex->getSize().y*tex->getSize().x];

            for (unsigned int y = 0; y < tex->getSize().y; y++) {
                for (unsigned int x = 0; x < tex->getSize().x; x++)
                    mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
            }

            Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex, mask));

            return mask;
        }
    };

    BitmaskManager Bitmasks;

    bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename)
    {
        sf::Image img;
        if (!img.loadFromFile(Filename))
            return false;
        if (!LoadInto.loadFromImage(img))
            return false;

        Bitmasks.CreateMask(&LoadInto, img);
        return true;
    }
}