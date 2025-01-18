#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace ly{
    sf::Vector2f rotation2vector(float rotation);
    float vector2rotation(sf::Vector2f vector);
    float degree2raduis(float degree);
    float radius2degree(float raduis);

    template<typename T>
    float getVectorLength(const sf::Vector2<T>& vector){
        return std::sqrt(std::pow(vector.x,2) + std::pow(vector.y,2));
    }

    template<typename T>
    sf::Vector2<T>& scaleVector(sf::Vector2<T>& vector,T scale){
        vector.x *= scale;
        vector.y *= scale;
        return vector;
    }

    template<typename T>
    sf::Vector2<T>& normalize(sf::Vector2<T>& vector){
        float vectorLenght = getVectorLength<T>(vector);
        if (vectorLenght == 0.f) return vector;
        scaleVector<T>(vector,1/vectorLenght);
        return vector;
    }

    float lerpFloat(float a,float b, float alpha);
    sf::Vector2f lerpVector(const sf::Vector2f& a,const sf::Vector2f b, float alpha);
    sf::Color lerpColor(const sf::Color& a, const sf::Color& b, float alpha);

    float randomRange(float min,float max);
    sf::Vector2f randomUnitVector();
}