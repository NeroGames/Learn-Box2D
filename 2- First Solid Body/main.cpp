////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
//Box2D
#include <Box2D/Box2D.h>
////////////////////////////////////////////////////////////
int main()
{
    //let's create a box

        //Step 1 : create the physical world
    //gravity
    b2Vec2 gravity(0.f, -9.8f);
    //create the physical world
    b2World physicWorld(gravity);

        //Step 1 : create an empty body
    b2BodyDef bodyDef;
    bodyDef.position      = b2Vec2(0.f, 0.f);
    bodyDef.angle         = 0.f;
    bodyDef.allowSleep    = true;
    bodyDef.fixedRotation = false;
    bodyDef.gravityScale  = 1.f;

    b2Body* boxBody       = physicWorld.CreateBody(&bodyDef);

        //Step 2 : create a box shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1, 1); //values are in meter not pixel

        //Step 3 : create a fixture and provide the shape to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape        = &boxShape;
    fixtureDef.isSensor     = false;
    fixtureDef.density      = 1.f;
    fixtureDef.friction     = 0.1f;
    fixtureDef.restitution  = 0.1f;

    boxBody->CreateFixture(&fixtureDef);

     //Step 4 : clean everything
    boxBody = nullptr;

    //print the world in console
    physicWorld.Dump();

    return 0;
}
