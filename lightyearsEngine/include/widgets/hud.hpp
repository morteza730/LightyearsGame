#pragma once

#include "framework/object.hpp"
#include <sfml/Graphics.hpp>

namespace ly
{
    class HUD: public Object
    {
        public:
            virtual void draw(sf::RenderWindow& windowRef)=0;
            void nativeInit(const sf::RenderWindow& windowRef);
            bool hasInit(){return alreadyInit;}
            virtual bool handleEvent(const sf::Event& event);
            virtual void tick(float deltaTime);

        protected:
            HUD();

        private:
            virtual void init(const sf::RenderWindow& windowRef);
            bool alreadyInit;
    };
}