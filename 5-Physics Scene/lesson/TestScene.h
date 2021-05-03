////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef TESTSCENE_H_INCLUDED
#define TESTSCENE_H_INCLUDED
///////////////////////////HEADERS//////////////////////////
//Nero Games
#include "Box2DScene.h"
//Box2D
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
////////////////////////////////////////////////////////////
class TestScene : public ng::Box2DScene
{
    public:
        typedef std::unique_ptr<TestScene> ptr;

        TestScene()
        {
            setSceneName("Test Scene v0.1");
        }

        void init()
        {
            //create a rigid floor
            createFloorBody();
        }

        void onMouseButton(const sf::Mouse::Button& button, const bool& isPressed, const sf::Vector2f& position)
        {
            if(isPressed)
            {
                if (button == sf::Mouse::Left && ng::CTRL())
                {
                    createBody(ng::sf_to_b2(position, ng::SCALE));
                }
            }
        }

        void createBody(b2Vec2 position = b2Vec2(0.f, 0.f))
        {
            //create an empty body
            b2BodyDef bodyDef;
            bodyDef.position      = position;
            bodyDef.angle         = 0.f;
            bodyDef.allowSleep    = true;
            bodyDef.fixedRotation = false;
            bodyDef.gravityScale  = 1.f;
            bodyDef.type          = b2_dynamicBody;

            b2Body* boxBody       = m_PhysicWorld.getWorld().CreateBody(&bodyDef);

            //create a box shape
            b2PolygonShape boxShape;
            boxShape.SetAsBox(1, 1); //values are in meter not pixel

            //create a fixture and provide the shape to the body
            b2FixtureDef fixtureDef;
            fixtureDef.shape        = &boxShape;
            fixtureDef.isSensor     = false;
            fixtureDef.density      = 1.f;
            fixtureDef.friction     = 0.1f;
            fixtureDef.restitution  = 0.1f;

            boxBody->CreateFixture(&fixtureDef);

             //clean everything
            boxBody = nullptr;
        }

        void createFloorBody()
        {
            b2Vec2 point1 = ng::sf_to_b2(sf::Vector2f(0.f, 600.f), ng::SCALE);
            b2Vec2 point2 = ng::sf_to_b2(sf::Vector2f(1080.f, 600.f), ng::SCALE);

             //create an empty body
            b2BodyDef bodyDef;
            bodyDef.position      = b2Vec2(0.f, 0.f);
            bodyDef.angle         = 0.f;
            bodyDef.allowSleep    = true;
            bodyDef.fixedRotation = false;
            bodyDef.gravityScale  = 1.f;
            bodyDef.type          = b2_staticBody;

            b2Body* boxBody       = m_PhysicWorld.getWorld().CreateBody(&bodyDef);

            //create a box shape
            b2EdgeShape edgeshape;
            edgeshape.Set(point1, point2);

            //create a fixture and provide the shape to the body
            b2FixtureDef fixtureDef;
            fixtureDef.shape        = &edgeshape;
            fixtureDef.isSensor     = false;
            fixtureDef.density      = 1.f;
            fixtureDef.friction     = 0.1f;
            fixtureDef.restitution  = 0.1f;

            boxBody->CreateFixture(&fixtureDef);

             //clean everything
            boxBody = nullptr;
        }
};

#endif // TESTSCENE_H_INCLUDED
