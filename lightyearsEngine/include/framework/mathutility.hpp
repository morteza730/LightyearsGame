#pragma once

#include <SFML/Graphics.hpp>

namespace ly{
    sf::Vector2f rotation2vector(float rotation);
    float vector2rotation(sf::Vector2f vector);
    float degree2raduis(float degree);
    float radius2degree(float raduis);
}