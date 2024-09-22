#include "framework/mathutility.hpp"
#include <cmath>

namespace ly{
    const float PI = 3.1416;

    sf::Vector2f rotation2vector(float rotation){
        float raduis = degree2raduis(rotation);
        return sf::Vector2f(std::cos(raduis),std::sin(raduis));
    }

    float vector2rotation(sf::Vector2f vector){
        float rotation = std::atan2(vector.y,vector.x);
        return radius2degree(rotation);
    }

    float degree2raduis(float degree){
        return degree*(PI/180);
    }

    float radius2degree(float raduis){
        return raduis*(180/PI);
    }
}