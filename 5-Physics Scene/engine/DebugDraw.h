////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H
///////////////////////////HEADERS//////////////////////////
//Box2D
#include <Box2D/Common/b2Draw.h>
#include <Box2D/Collision/b2Collision.h>
//SFML
#include <SFML/Graphics.hpp>
//Nero Games
#include <PhysicsUtil.h>
////////////////////////////////////////////////////////////
namespace ng
{
    class DebugDraw : public b2Draw
    {
        public:
                            DebugDraw(const float& thickness = -2.f, const int& tranparency = 50.f);
            virtual        ~DebugDraw();
            void            setRenderWindow(sf::RenderWindow*  renderWindow);

        public:
            //b2DRraw original methods
            void            DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
            void            DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
            void            DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;
            void            DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;
            void            DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
            void            DrawTransform(const b2Transform& xf) override;
            //Additional draw method
            void            DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
            void            DrawAABB(b2AABB* aabb, const b2Color& color);

        private:
            sf::RenderWindow*   m_RenderWindow;
            float               m_Thickness;
            int                 m_Tranparency;
    };
}

#endif // DEBUGDRAW_H
