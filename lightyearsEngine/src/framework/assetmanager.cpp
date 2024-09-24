#include "framework/assetmanager.hpp"

ly::unique<ly::AssetManager> ly::AssetManager::asset_manager{nullptr};

ly::AssetManager::AssetManager():
    m_rootDir{""}
{}

ly::AssetManager::AssetManager(const AssetManager &instance):
    m_rootDir{""}
{}

ly::AssetManager::AssetManager(const AssetManager &&instance):
    m_rootDir{""}
{}

ly::AssetManager &ly::AssetManager::get()
{
    if (!asset_manager){
        asset_manager = unique<AssetManager>(new AssetManager());
    }
    return *asset_manager;
}

ly::shared<sf::Texture> ly::AssetManager::loadTexture(const std::string path)
{
    auto itr = m_texture_map.find(path);
    if (itr != m_texture_map.end()){
        return itr->second;
    }
    shared<sf::Texture> new_texture{new sf::Texture};
    if (new_texture->loadFromFile(m_rootDir+path)){
        m_texture_map.insert({path,new_texture});
        return new_texture;
    }
    return shared<sf::Texture>{nullptr};
}

void ly::AssetManager::cleanCycle()
{
    for(auto itr=m_texture_map.begin(); itr!=m_texture_map.end();){
        if (itr->second.unique()){
            LOG("cleaning texture: %s",itr->first.c_str());
            itr = m_texture_map.erase(itr);
        }else{
            itr++;
        }
    }
}

void ly::AssetManager::setAssetRootDir(const std::string &directory)
{
    m_rootDir = directory;
}
