////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef ENGINE_H
#define ENGINE_H
///////////////////////////HEADERS//////////////////////////
//SFML
#include <SFML/Graphics/RenderWindow.hpp>
//Nero Games
#include "Scene.h"
////////////////////////////////////////////////////////////
namespace ng
{
    class Engine
    {
        public:
                                        Engine(const unsigned int& windowWidth  = 1080,
                                               const unsigned int& windowHeight = 720,
                                               const float& frameRate           = 60.f);
            virtual                    ~Engine();
            void                        run();
            void                        setScene(Scene::Ptr scene);

        private:
            void                        init();
            void                        handleEvent();
            void                        update(const sf::Time& timeStep);
            void                        render();
            void                        destroy();
            void                        computeFrameRate(const sf::Time& timeStep);

        protected:
            //window
            sf::RenderWindow            m_RenderWindow;
            sf::Vector2f                m_WindowResolution;
            sf::Time                    m_FrameRate;
            //Scene
            Scene::Ptr                  m_Scene;
            //Frame rate
            sf::Time			        m_ElapsedTime;
            int 	                    m_FrameCount;
            float                       m_FramePerSecond;
            float                       m_TimePerFrame;
    };
}


#endif // ENGINE_H
