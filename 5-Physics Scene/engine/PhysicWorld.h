////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef PHYSICWORLD_H
#define PHYSICWORLD_H
///////////////////////////HEADERS//////////////////////////
//Box2D
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Joints/b2MouseJoint.h>
//SFML
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
//Nero Games
#include "DebugDraw.h"
////////////////////////////////////////////////////////////
namespace ng
{
    class PhysicWorld
    {
        public:
                                    PhysicWorld(const b2Vec2& gravity = b2Vec2(0.f, 9.8f));
            virtual                ~PhysicWorld();
            void                    setRenderWindow(sf::RenderWindow*  renderWindow);

            void                    init();
            void                    handleEvent(const sf::Event& event);
            void                    update(const sf::Time& timeStep);
            void                    render();
            void                    destroy();

            b2World&                getWorld();

        private:
            //mouse callback
            void                    onMouseMoved(const sf::Vector2f& position);
            void                    onMouseButton(const sf::Mouse::Button& button, const bool& isPressed, const sf::Vector2f& position);
            //grab and drop
            void                    onMouseGrabObject(const b2Vec2& position);
            void                    onMouseMoveObject(const b2Vec2& position);
            void                    onMouseDropObject();




        private:
            //window
            sf::RenderWindow*       m_RenderWindow;
            //world
            b2World                 m_PhysicWorld;
            DebugDraw               m_DebugDraw;
            //grab and drop
            b2MouseJoint*           m_MouseJoint;
            b2Body*                 m_MouseGround;
    };
}


#endif // PHYSICWORLD_H
