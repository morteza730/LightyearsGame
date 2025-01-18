#include "framework/mathutility.hpp"
#include <random>

namespace ly
{
    const float PI = 3.1416;

    sf::Vector2f rotation2vector(float rotation)
    {
        float raduis = degree2raduis(rotation);
        return sf::Vector2f(std::cos(raduis), std::sin(raduis));
    }

    float vector2rotation(sf::Vector2f vector)
    {
        float rotation = std::atan2(vector.y, vector.x);
        return radius2degree(rotation);
    }

    float degree2raduis(float degree)
    {
        return degree * (PI / 180);
    }

    float radius2degree(float raduis)
    {
        return raduis * (180 / PI);
    }
}

float ly::lerpFloat(float a, float b, float alpha)
{
    alpha = (alpha > 1) ? 1 : alpha;
    alpha = (alpha < 0) ? 0 : alpha;
    return a + (b - a) * alpha;
}

sf::Vector2f ly::lerpVector(const sf::Vector2f &a, const sf::Vector2f b, float alpha)
{
    float lerpX = lerpFloat(a.x, b.x, alpha);
    float lerpY = lerpFloat(a.y, b.y, alpha);

    return sf::Vector2f(lerpX,lerpY);
}

sf::Color ly::lerpColor(const sf::Color &a, const sf::Color &b, float alpha)
{
    float lerpR = lerpFloat(a.r, b.r, alpha);
    float lerpG = lerpFloat(a.g, b.g, alpha);
    float lerpB = lerpFloat(a.b, b.b, alpha);
    float lerpA = lerpFloat(a.a, b.a, alpha);

    return sf::Color(lerpR,lerpG,lerpB,lerpA);
}

float ly::randomRange(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution{min,max};
    return distribution(gen);
}

sf::Vector2f ly::randomUnitVector()
{
    float randomX = randomRange(-1,1);
    float randomY = randomRange(-1,1);
    sf::Vector2f randomVector = sf::Vector2f(randomX,randomY);
    normalize(randomVector);
    return randomVector;
}
