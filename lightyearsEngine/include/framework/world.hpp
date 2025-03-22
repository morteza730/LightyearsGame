#pragma once

#include "framework/core.hpp"
#include "framework/object.hpp"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Application;
    class Actor;
    class GameStage;
    class HUD;
    class World : public Object
    {
    public:
        World(Application *application);
        virtual ~World();
        void beginPlayInternal();
        void tickInternal(float deltaTime);
        void render(sf::RenderWindow &window);
        sf::Vector2u getWindowSize() const;
        void cleanCycle();
        void addStage(const shared<GameStage> &newStage);
        bool dispatchEvent(const sf::Event& event);

        template <typename actorType, typename... Args>
        weak<actorType> spawnAcotr(Args... args);

        template <typename hudType, typename... Args>
        weak<hudType> spawnHUD(Args... args);

        Application *getApplication() {return m_owningApp;}
        const Application *getApplication() const {return m_owningApp;}
        
    private:
        virtual void beginPlay();
        virtual void tick(float deltaTime);
        virtual void initGameStages();
        void nextGameStage();
        virtual void allGameStageFinished();
        void startStages();
        virtual void renderHud(sf::RenderWindow &window);
        Application *m_owningApp;
        bool m_beginPlay;
        List<shared<Actor>> m_pendingActors;
        List<shared<Actor>> m_actors;
        List<shared<GameStage>> m_gameStages;
        List<shared<GameStage>>::iterator m_currentStage;
        shared<HUD> m_hud;
    };

    template <typename actorType, typename... Args>
    weak<actorType> World::spawnAcotr(Args... args)
    {
        shared<actorType> newActor{new actorType{this, args...}};
        m_pendingActors.push_back(newActor);
        return newActor;
    }

    template <typename hudType, typename... Args>
    weak<hudType> World::spawnHUD(Args... args)
    {
        shared<hudType> newHUD{new hudType{args...}};
        m_hud = newHUD;
        return newHUD;
    }
}