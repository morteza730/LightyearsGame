#pragma once

#include "framework/core.hpp"
#include <sfml/Graphics.hpp>

namespace ly
{
    class AssetManager
    {
    public:
        static AssetManager &get();
        shared<sf::Texture> loadTexture(const std::string &path);
        shared<sf::Font> loadFont(const std::string &path);
        void cleanCycle();
        void setAssetRootDir(const std::string &directory);

    protected:
        AssetManager();                              // normal constructor
        AssetManager(const AssetManager &instance);  // copy constructor
        AssetManager(const AssetManager &&instance); // move constructor

    private:
        template <typename T>
        void cleanUniqueRef(Dictionary<std::string, shared<T>> &container);
        template <typename T>
        shared<T> loadAsset(const std::string &path, Dictionary<std::string, shared<T>> &container);
        static unique<AssetManager> asset_manager;
        Dictionary<std::string, shared<sf::Texture>> mTextureMap;
        Dictionary<std::string, shared<sf::Font>> mFontMap;
        std::string m_rootDir;
    };

    template <typename T>
    inline void AssetManager::cleanUniqueRef(Dictionary<std::string, shared<T>> &container)
    {
        for (auto itr = container.begin(); itr != container.end();)
        {
            if (itr->second.unique())
            {
                LOG("cleaning: %s", itr->first.c_str());
                itr = container.erase(itr);
            }
            else
            {
                itr++;
            }
        }
    }

    template <typename T>
    inline shared<T> AssetManager::loadAsset(const std::string &path, Dictionary<std::string, shared<T>> &container)
    {
        auto itr = container.find(path);
        if (itr != container.end())
        {
            return itr->second;
        }
        shared<T> newAsset{new T};
        if (newAsset->loadFromFile(m_rootDir + path))
        {
            container.insert({path, newAsset});
            return newAsset;
        }
        return shared<T>{nullptr};
    }
}