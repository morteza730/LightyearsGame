#pragma once

#include "framework/core.hpp"
#include "framework/object.hpp"
#include <SFML/Graphics.hpp>

namespace ly{
    class Application;
    class Actor;
    class GameStage;
    class World: public Object
    {
        public:
            World(Application *application);
            virtual ~World();
            void beginPlayInternal();
            void tickInternal(float deltaTime);
            void render(sf::RenderWindow &window);
            template<typename actorType,typename... Args>
            weak<actorType> spawnAcotr(Args... args);
            sf::Vector2u getWindowSize() const;
            void cleanCycle();
            void addStage(const shared<GameStage>& newStage);

        private:
            virtual void beginPlay();
            virtual void tick(float deltaTime);
            Application *owningApp;
            bool m_beginPlay;
            List<shared<Actor>> m_pendingActors;
            List<shared<Actor>> m_actors;
            List<shared<GameStage>> m_gameStages;
            List<shared<GameStage>>::iterator m_currentStage;
            virtual void initGameStages();
            void nextGameStage();
            virtual void allGameStageFinished();
            void startStages();
    };
    template<typename actorType,typename... Args>
    weak<actorType> World::spawnAcotr(Args... args){
        shared<actorType> newActor{new actorType{this,args...}};
        m_pendingActors.push_back(newActor);
        return newActor;
    }
}