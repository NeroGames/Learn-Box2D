////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef MOUSEQUERYCALLBACK_H
#define MOUSEQUERYCALLBACK_H
///////////////////////////HEADERS//////////////////////////
//Box2D
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
////////////////////////////////////////////////////////////
namespace ng
{
    class MouseQueryCallback : public b2QueryCallback
    {
        public:
                            MouseQueryCallback(const b2Vec2& point);
            virtual        ~MouseQueryCallback();

            bool            ReportFixture(b2Fixture* fixture) override;

        public:
            b2Vec2          m_Point;
            b2Fixture*      m_Fixture;
    };
}

#endif // MOUSEQUERYCALLBACK_H
