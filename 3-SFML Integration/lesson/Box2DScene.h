////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef BOX2DSCENE_H_INCLUDED
#define BOX2DSCENE_H_INCLUDED
///////////////////////////HEADERS//////////////////////////
//Box2D
#include <Box2D/Box2D.h>
//Nero Games
#include "DebugDraw.h"
////////////////////////////////////////////////////////////
class Box2DScene : public ng::Scene
{
     private:
        b2World     mPhysicWorld;
        DebugDraw   mDebugDraw;

    public:
        typedef std::unique_ptr<Box2DScene> ptr;

        Box2DScene(): mPhysicWorld(b2Vec2(0.f, 9.8f))
        {
            setSceneName("Box2D Scene v0.1");
        }

        void init()
        {
            //setup the DebugDraw
            mDebugDraw.setRenderWindow(&getRenderWindow());
            mDebugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
            mPhysicWorld.SetDebugDraw(&mDebugDraw);

            //create a rigid body
            createBody();
        }

        void update(const sf::Time& timeStep)
        {
            mPhysicWorld.Step(timeStep.asSeconds(), 8.f, 3.f);
        }

        void render()
        {
            mPhysicWorld.DrawDebugData();
        }

        void onMouseButton(const sf::Mouse::Button& button, const bool& isPressed, const sf::Vector2f& position)
        {
            if(isPressed && button == sf::Mouse::Left)
            {
                createBody(ng::sf_to_b2(position, ng::SCALE));
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

            b2Body* boxBody       = mPhysicWorld.CreateBody(&bodyDef);

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
};

#endif // BOX2DSCENE_H_INCLUDED
