////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef DEBUGDRAW_H_INCLUDED
#define DEBUGDRAW_H_INCLUDED
///////////////////////////HEADERS//////////////////////////
//Box2D
#include <Box2D/Common/b2Draw.h>
//SFML
#include <SFML/Graphics.hpp>
//Nero Games
#include <PhysicsUtil.h>
////////////////////////////////////////////////////////////
class DebugDraw : public b2Draw
{
    private:
        sf::RenderWindow*   mRenderWindow;
        float               mThickness = -2.f;
        int                 mTranparency = 50.f;

    public:
        DebugDraw()
        {

        }

        ~DebugDraw()
        {
            mRenderWindow = nullptr;
        }

        void setRenderWindow(sf::RenderWindow*  renderWindow)
        {
            mRenderWindow = renderWindow;
        }

        void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            sf::ConvexShape polygon;
            polygon.setOutlineThickness(mThickness);
            polygon.setOutlineColor(ng::b2_to_sf(color));
            polygon.setFillColor(sf::Color::Transparent);

            polygon.setPointCount(vertexCount);
            for(int32 i = 0; i < vertexCount; i++)
            {
                polygon.setPoint(i, ng::b2_to_sf(vertices[i], ng::SCALE));
            }

            mRenderWindow->draw(polygon);
        }

        void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            sf::ConvexShape solidPolygon;
            solidPolygon.setOutlineThickness(mThickness);
            solidPolygon.setOutlineColor(ng::b2_to_sf(color));
            solidPolygon.setFillColor(ng::b2_to_sf(color, mTranparency));

            solidPolygon.setPointCount(vertexCount);
            for(int32 i = 0; i < vertexCount; i++)
            {
                solidPolygon.setPoint(i, ng::b2_to_sf(vertices[i], ng::SCALE));
            }

            mRenderWindow->draw(solidPolygon);
        }

        void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
        {

            sf::CircleShape circle;
            circle.setOutlineThickness(mThickness);
            circle.setOutlineColor(ng::b2_to_sf(color));
            circle.setFillColor(sf::Color::Transparent);

            float rad = radius * ng::SCALE;
            circle.setPosition(ng::b2_to_sf(center, ng::SCALE));
            circle.setRadius(rad);
            circle.setOrigin(sf::Vector2f(rad, rad));

            mRenderWindow->draw(circle);
        }

        void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
        {
            sf::CircleShape solidCircle;
            solidCircle.setOutlineThickness(mThickness);
            solidCircle.setOutlineColor(ng::b2_to_sf(color));
            solidCircle.setFillColor(ng::b2_to_sf(color, mTranparency));

            float rad = radius * ng::SCALE;
            solidCircle.setPosition(ng::b2_to_sf(center, ng::SCALE));
            solidCircle.setRadius(rad);
            solidCircle.setOrigin(sf::Vector2f(rad, rad));

            mRenderWindow->draw(solidCircle);

            b2Vec2 p = center + radius * axis;
            DrawSegment(center, p, color);
        }

        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
        {
            sf::RectangleShape line;
            float length = ng::distance(ng::b2_to_sf(p1, ng::SCALE), ng::b2_to_sf(p2, ng::SCALE));
            line.setSize(sf::Vector2f(length, mThickness));
            line.setPosition(ng::b2_to_sf(p1, ng::SCALE));
            line.setFillColor(ng::b2_to_sf(color));
            line.setOrigin(sf::Vector2f(line.getOrigin().x, mThickness/2.f));


            float delta_x = p2.x - p1.x;
            float delta_y = p2.y - p1.y;
            float angle = atan2(delta_y, delta_x);
            line.setRotation(ng::toDegree(angle));

            mRenderWindow->draw(line);
        }

        void DrawTransform(const b2Transform& xf)
        {
            const float32 k_axisScale  = 0.4f;

            b2Vec2 p1, p2;
            p1 = xf.p;
            p2 = p1 + k_axisScale * xf.q.GetXAxis();
            DrawSegment(p1, p2, b2Color(1.0f, 0.0f, 0.0f));

            p2 = p1 + k_axisScale * xf.q.GetYAxis();
            DrawSegment(p1, p2, b2Color(0.0f, 1.0f, 0.0f));
        }

        void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
        {
            float s = size*1.5f;
            sf::RectangleShape point;
            point.setFillColor(ng::b2_to_sf(color));
            point.setPosition(ng::b2_to_sf(p, ng::SCALE));
            point.setSize(sf::Vector2f(s, s));
            point.setOrigin(sf::Vector2f(s/2, s/2));

            mRenderWindow->draw(point);
        }

        void DrawAABB(b2AABB* aabb, const b2Color& color)
        {
            sf::ConvexShape aabb_shape;
            aabb_shape.setOutlineColor(ng::b2_to_sf(color));
            aabb_shape.setPointCount(4);

            aabb_shape.setPoint(0, ng::b2_to_sf(aabb->lowerBound, ng::SCALE));
            aabb_shape.setPoint(1, sf::Vector2f(aabb->upperBound.x * ng::SCALE, aabb->lowerBound.y * ng::SCALE));
            aabb_shape.setPoint(2, ng::b2_to_sf(aabb->upperBound, ng::SCALE));
            aabb_shape.setPoint(3, sf::Vector2f(aabb->lowerBound.x * ng::SCALE, aabb->upperBound.y * ng::SCALE));

            mRenderWindow->draw(aabb_shape);
        }
};

#endif // DEBUGDRAW_H_INCLUDED
