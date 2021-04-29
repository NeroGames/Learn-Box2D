////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef MOUSEQUERYCALLBACK_H_INCLUDED
#define MOUSEQUERYCALLBACK_H_INCLUDED
///////////////////////////HEADERS//////////////////////////
//Box2D
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
////////////////////////////////////////////////////////////
class MouseQueryCallback : public b2QueryCallback
{
    public:
        b2Vec2          mPoint;
        b2Fixture*      mFixture;

    public:

        MouseQueryCallback(const b2Vec2& point)
        {
            mPoint     = point;
            mFixture   = nullptr;
        }

        ~MouseQueryCallback()
        {
            mFixture = nullptr;
        }

        bool ReportFixture(b2Fixture* fixture)
        {
            b2Body* body = fixture->GetBody();

            if (body->GetType() == b2_dynamicBody)
            {
                bool inside = fixture->TestPoint(mPoint);

                if (inside)
                {
                    mFixture = fixture;

                    //Clean pointer
                    body = nullptr;

                    //We are done, terminate the query.
                    return false;
                }
            }

            //Clean pointer
            body = nullptr;

            //Continue the query.
            return true;
        }
};

#endif // MOUSEQUERYCALLBACK_H_INCLUDED
