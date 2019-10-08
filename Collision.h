/*
 * File:   collision.h
 * Authors: Nick Koirala (original version), ahnonay (SFML2 compatibility)
 *
 * Collision Detection and handling class
 * For SFML2.
 *
 * Created on 30 January 2009, 11:02
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>

namespace Collision {
    bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename);
}

#endif	/* COLLISION_H */