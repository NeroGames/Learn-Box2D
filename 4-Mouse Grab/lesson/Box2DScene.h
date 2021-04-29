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
#include "MouseQueryCallback.h"
////////////////////////////////////////////////////////////
class Box2DScene : public ng::Scene
{
     private:
        b2World                 mPhysicWorld;
        DebugDraw               mDebugDraw;
        //mouse grabbing
        b2MouseJoint*           mMouseJoint;
        b2Body*                 mMouseGround;

    public:
        typedef std::unique_ptr<Box2DScene> ptr;

        Box2DScene(): mPhysicWorld(b2Vec2(0.f, 9.8f))
        {
            setSceneName("Box2D Scene v0.2");
        }

        void init()
        {
            //setup the DebugDraw
            mDebugDraw.setRenderWindow(&getRenderWindow());
            mDebugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_centerOfMassBit);
            mPhysicWorld.SetDebugDraw(&mDebugDraw);

            //mouse grabbing
            b2BodyDef bodyDef;
            mMouseGround = mPhysicWorld.CreateBody(&bodyDef);


            //create a rigid floor
            createFloorBody();
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
            if(isPressed)
            {
                if (button == sf::Mouse::Left)
                {
                    if(ng::CTRL())
                    {
                        createBody(ng::sf_to_b2(position, ng::SCALE));
                    }
                    else
                    {
                         mouseGrabObject(ng::sf_to_b2(position, ng::SCALE));
                    }
                }
            }
            else
            {
                if(button == sf::Mouse::Left && !ng::CTRL())
                {
                    mouseDropObject();
                }
            }
        }

        void onMouseMoved(const sf::Vector2f& position)
        {
            mouseMoveObject(ng::sf_to_b2(position, ng::SCALE));
        }


        void mouseGrabObject(const b2Vec2& position)
        {
            if(mMouseJoint != nullptr) return;

            // Make a small box.
            b2AABB aabb;
            b2Vec2 distance;
            distance.Set(0.001f, 0.001f);
            aabb.lowerBound = position - distance;
            aabb.upperBound = position + distance;

            // Query the world for overlapping shapes.
            MouseQueryCallback callback(position);
            mPhysicWorld.QueryAABB(&callback, aabb);

            if (callback.mFixture)
            {
                b2Body* body        = callback.mFixture->GetBody();

                b2MouseJointDef jointDef;
                jointDef.bodyA      = mMouseGround;
                jointDef.bodyB      = body;
                jointDef.target     = position;
                jointDef.maxForce   = 1000.0f * body->GetMass();

                mMouseJoint         = (b2MouseJoint*)mPhysicWorld.CreateJoint(&jointDef);

                body->SetAwake(true);

                body = nullptr;
            }
        }

        void mouseMoveObject(const b2Vec2& position)
        {
            if (mMouseJoint)
            {
                mMouseJoint->SetTarget(position);
            }
        }

        void mouseDropObject()
        {
            if(mMouseJoint)
            {
                mPhysicWorld.DestroyJoint(mMouseJoint);
                mMouseJoint = nullptr;
            }
        }

        b2Joint* getMouseJoint()
        {
            return mMouseJoint;
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

            b2Body* boxBody       = mPhysicWorld.CreateBody(&bodyDef);

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

#endif // BOX2DSCENE_H_INCLUDED
