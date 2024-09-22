#pragma once

#include "framework/core.hpp"
#include <sfml/Graphics.hpp>

namespace ly{
    class AssetManager{
        public:
            static AssetManager& get();
            shared<sf::Texture> loadTexture(const std::string path); 
            void cleanCycle();

        protected:
            AssetManager(); // normal constructor
            AssetManager(const AssetManager &instance); // copy constructor
            AssetManager(const AssetManager &&instance); // move constructor

        private:
            static unique<AssetManager> asset_manager;
            Dictionary<std::string,shared<sf::Texture>> m_texture_map;
    };
}