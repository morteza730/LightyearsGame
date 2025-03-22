#include "framework/assetmanager.hpp"

ly::unique<ly::AssetManager> ly::AssetManager::asset_manager{nullptr};

ly::AssetManager::AssetManager() : m_rootDir{""}
{
}

ly::AssetManager::AssetManager(const AssetManager &instance) : m_rootDir{""}
{
}

ly::AssetManager::AssetManager(const AssetManager &&instance) : m_rootDir{""}
{
}

ly::AssetManager &ly::AssetManager::get()
{
    if (!asset_manager)
    {
        asset_manager = unique<AssetManager>(new AssetManager());
    }
    return *asset_manager;
}

ly::shared<sf::Texture> ly::AssetManager::loadTexture(const std::string &path)
{
    return loadAsset(path,mTextureMap);
}

ly::shared<sf::Font> ly::AssetManager::loadFont(const std::string &path)
{
    return loadAsset(path,mFontMap);
}

void ly::AssetManager::cleanCycle()
{
    cleanUniqueRef(mTextureMap);
    cleanUniqueRef(mFontMap);
}

void ly::AssetManager::setAssetRootDir(const std::string &directory)
{
    m_rootDir = directory;
}
