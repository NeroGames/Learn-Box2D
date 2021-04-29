////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
//SFML
#include <SFML/Window/Event.hpp>
//Nero Games
#include "Engine.h"
////////////////////////////////////////////////////////////
namespace ng
{
    Engine::Engine(const unsigned int& windowWidth, const unsigned int& windowHeight, const float& frameRate):
         m_WindowResolution(windowWidth, windowHeight)
        ,m_FrameRate(sf::seconds(1.f/frameRate))
        ,m_RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Simple Engine")
        ,m_Scene(Scene::Ptr(new Scene()))
        ,m_ElapsedTime()
        ,m_FrameCount(0)
        ,m_FramePerSecond(0.f)
        ,m_TimePerFrame(0.f)
    {
        //constructor
    }

    Engine::~Engine()
    {
        //destructor
    }

    void Engine::setScene(Scene::Ptr scene)
    {
        m_Scene = std::move(scene);
        m_RenderWindow.setTitle(m_Scene->m_SceneName);
        m_Scene->m_Resolution   = m_WindowResolution;
        m_Scene->m_RenderWindow = &m_RenderWindow;
    }

    void Engine::run()
    {
        //Initialize game
        init();

        //Variable to store the time that passes
        sf::Time timePassed = sf::Time::Zero;
        //Create a clock, the clock starts automatically
        sf::Clock clock;
        //Entering the game loop
        while(m_RenderWindow.isOpen())
        {
            //Retrieve the clock time and reset the clock at the same time
            sf::Time clockTime = clock.restart();
            //Accumulate the time passing in our variable (this happens at each cycle of the while loop)
            timePassed += clockTime;

            //When the time passing is over our Fixed Time only Capture Inputs and Update the Game
            while(timePassed > m_FrameRate)
            {
                //Remove (0.0166) seconds from the passing time
                //Only the overflow will remain for the next frame
                timePassed -= m_FrameRate;

                //capture the user inputs using SFML Events
                handleEvent();
                //update the game at the fixed time frame of (0.0166 second)
                update(m_FrameRate);
            }

            //Compute Frame rate
            computeFrameRate(clockTime);
            //Render the game
            //We do not render the game at 60 FPS, only the update happens at 60 FPS
            render();
        }

        destroy();
    }

    void Engine::init()
    {
        m_Scene->init();
    }

    void Engine::handleEvent()
    {
        sf::Event event;
        while(m_RenderWindow.pollEvent(event))
        {
           m_Scene->handleEvent(event);
        }
    }

    void Engine::update(const sf::Time& timeStep)
    {
        m_Scene->update(m_FrameRate);
    }

    void Engine::render()
    {
        m_Scene->clear();
        m_Scene->render();

        m_RenderWindow.display();
    }

    void Engine::destroy()
    {
        m_Scene->destroy();
    }

    void Engine::computeFrameRate(const sf::Time& timeStep)
    {
        //Accumulate data for on 1 second
        m_ElapsedTime       += timeStep;
        m_FrameCount        += 1;

        //Then compute the frame rate
        if(m_ElapsedTime >= sf::seconds(1.0f))
        {
            m_FramePerSecond    = m_FrameCount;
            m_TimePerFrame      = m_ElapsedTime.asSeconds() / m_FrameCount;

            m_ElapsedTime      -= sf::seconds(1.0f);
            m_FrameCount        = 0;

            //provide new data to the Scene class
            m_Scene->m_FrameRate = m_FramePerSecond;
            m_Scene->m_FrameTime = m_TimePerFrame;
        }
    }
}

