////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
//Nero Games
#include "PhysicWorld.h"
#include "KeyboardUtil.h"
#include "MouseQueryCallback.h"
//Box2D
#include <Box2D/Dynamics/b2Body.h>
////////////////////////////////////////////////////////////
namespace ng
{
    PhysicWorld::PhysicWorld(const b2Vec2& gravity):
         m_PhysicWorld(gravity)
        ,m_RenderWindow(nullptr)
        ,m_MouseJoint(nullptr)
        ,m_MouseGround(nullptr)
    {

    }

    PhysicWorld::~PhysicWorld()
    {
        m_RenderWindow  = nullptr;
        m_MouseJoint    = nullptr;
        m_MouseGround   = nullptr;
    }

    void PhysicWorld::setRenderWindow(sf::RenderWindow*  renderWindow)
    {
        m_RenderWindow = renderWindow;
    }

    void PhysicWorld::init()
    {
        //setup the DebugDraw
        m_DebugDraw.setRenderWindow(m_RenderWindow);
        m_DebugDraw.SetFlags(b2Draw::e_shapeBit);
        m_PhysicWorld.SetDebugDraw(&m_DebugDraw);

        //mouse grabbing
        b2BodyDef bodyDef;
        m_MouseGround = m_PhysicWorld.CreateBody(&bodyDef);
    }

    void PhysicWorld::destroy()
    {

    }

    void PhysicWorld::update(const sf::Time& timeStep)
    {
        m_PhysicWorld.Step(timeStep.asSeconds(), 8.f, 3.f);
    }

    void PhysicWorld::render()
    {
        m_PhysicWorld.DrawDebugData();
    }

    void PhysicWorld::handleEvent(const sf::Event& event)
    {
        switch(event.type)
        {
            //Mouse
            case sf::Event::MouseMoved:
                onMouseMoved(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)); break;
            case sf::Event::MouseButtonPressed:
                onMouseButton(event.mouseButton.button, true, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); break;
            case sf::Event::MouseButtonReleased:
                onMouseButton(event.mouseButton.button, false, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); break;
        }
    }

    void PhysicWorld::onMouseButton(const sf::Mouse::Button& button, const bool& isPressed, const sf::Vector2f& position)
    {
        if(isPressed)
        {
            if (button == sf::Mouse::Left && !ng::CTRL())
            {
                onMouseGrabObject(ng::sf_to_b2(position, ng::SCALE));
            }
        }
        else
        {
            if(button == sf::Mouse::Left && !ng::CTRL())
            {
                onMouseDropObject();
            }
        }
    }

    void PhysicWorld::onMouseMoved(const sf::Vector2f& position)
    {
        onMouseMoveObject(ng::sf_to_b2(position, ng::SCALE));
    }

    void PhysicWorld::onMouseGrabObject(const b2Vec2& position)
    {
        if(m_MouseJoint != nullptr) return;

        // Make a small box.
        b2AABB aabb;
        b2Vec2 distance;
        distance.Set(0.001f, 0.001f);
        aabb.lowerBound = position - distance;
        aabb.upperBound = position + distance;

        // Query the world for overlapping shapes.
        MouseQueryCallback callback(position);
        m_PhysicWorld.QueryAABB(&callback, aabb);

        if (callback.m_Fixture)
        {
            b2Body* body        = callback.m_Fixture->GetBody();

            b2MouseJointDef jointDef;
            jointDef.bodyA      = m_MouseGround;
            jointDef.bodyB      = body;
            jointDef.target     = position;
            jointDef.maxForce   = 1000.0f * body->GetMass();

            m_MouseJoint        = (b2MouseJoint*)m_PhysicWorld.CreateJoint(&jointDef);

            body->SetAwake(true);

            body = nullptr;
        }
    }

    void PhysicWorld::onMouseMoveObject(const b2Vec2& position)
    {
        if (m_MouseJoint)
        {
            m_MouseJoint->SetTarget(position);
        }
    }

    void PhysicWorld::onMouseDropObject()
    {
        if(m_MouseJoint)
        {
            m_PhysicWorld.DestroyJoint(m_MouseJoint);
            m_MouseJoint = nullptr;
        }
    }

    b2World& PhysicWorld::getWorld()
    {
        return m_PhysicWorld;
    }
}

