////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
#include "MouseQueryCallback.h"
////////////////////////////////////////////////////////////
namespace ng
{
    MouseQueryCallback::MouseQueryCallback(const b2Vec2& point)
    {
        m_Point     = point;
        m_Fixture   = nullptr;
    }

    MouseQueryCallback::~MouseQueryCallback()
    {
        m_Fixture = nullptr;
    }

    bool MouseQueryCallback::ReportFixture(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();

        if (body->GetType() == b2_dynamicBody)
        {
            bool inside = fixture->TestPoint(m_Point);

            if (inside)
            {
                m_Fixture = fixture;

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
}
