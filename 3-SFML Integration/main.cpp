////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
#include "engine/Engine.h"
#include "lesson/Box2DScene.h"
////////////////////////////////////////////////////////////
int main()
{
    //create new Engine instance
    ng::Engine engine(1080, 720, 60);
        //provide Scene to Engine
        engine.setScene(Box2DScene::Ptr(new Box2DScene()));
    //run the Engine
    engine.run();

    return 0;
}
