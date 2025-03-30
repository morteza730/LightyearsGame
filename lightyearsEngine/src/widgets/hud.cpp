#include "widgets/hud.hpp"

ly::HUD::HUD()
    : alreadyInit{false}
{
}

void ly::HUD::nativeInit(const sf::RenderWindow &windowRef)
{
    if (alreadyInit)
        return;

    alreadyInit = true;
    init(windowRef);
}

bool ly::HUD::handleEvent(const sf::Event &event)
{
    return false;
}

void ly::HUD::tick(float deltaTime)
{
}

void ly::HUD::init(const sf::RenderWindow &windowRef)
{
}
