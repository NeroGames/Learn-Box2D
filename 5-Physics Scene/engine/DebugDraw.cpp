////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
#include "DebugDraw.h"
////////////////////////////////////////////////////////////
namespace ng
{
    DebugDraw::DebugDraw(const float& thickness, const int& tranparency):
         b2Draw()
        ,m_RenderWindow(nullptr)
        ,m_Thickness(thickness)
        ,m_Tranparency(tranparency)
    {

    }

    DebugDraw::~DebugDraw()
    {
        m_RenderWindow = nullptr;
    }

    void DebugDraw::setRenderWindow(sf::RenderWindow*  renderWindow)
    {
        m_RenderWindow = renderWindow;
    }

    void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        sf::ConvexShape polygon;
        polygon.setOutlineThickness(m_Thickness);
        polygon.setOutlineColor(ng::b2_to_sf(color));
        polygon.setFillColor(sf::Color::Transparent);

        polygon.setPointCount(vertexCount);
        for(int32 i = 0; i < vertexCount; i++)
        {
            polygon.setPoint(i, ng::b2_to_sf(vertices[i], ng::SCALE));
        }

        m_RenderWindow->draw(polygon);
    }

    void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        sf::ConvexShape solidPolygon;
        solidPolygon.setOutlineThickness(m_Thickness);
        solidPolygon.setOutlineColor(ng::b2_to_sf(color));
        solidPolygon.setFillColor(ng::b2_to_sf(color, m_Tranparency));

        solidPolygon.setPointCount(vertexCount);
        for(int32 i = 0; i < vertexCount; i++)
        {
            solidPolygon.setPoint(i, ng::b2_to_sf(vertices[i], ng::SCALE));
        }

        m_RenderWindow->draw(solidPolygon);
    }

    void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
    {

        sf::CircleShape circle;
        circle.setOutlineThickness(m_Thickness);
        circle.setOutlineColor(ng::b2_to_sf(color));
        circle.setFillColor(sf::Color::Transparent);

        float rad = radius * ng::SCALE;
        circle.setPosition(ng::b2_to_sf(center, ng::SCALE));
        circle.setRadius(rad);
        circle.setOrigin(sf::Vector2f(rad, rad));

        m_RenderWindow->draw(circle);
    }

    void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
    {
        sf::CircleShape solidCircle;
        solidCircle.setOutlineThickness(m_Thickness);
        solidCircle.setOutlineColor(ng::b2_to_sf(color));
        solidCircle.setFillColor(ng::b2_to_sf(color, m_Tranparency));

        float rad = radius * ng::SCALE;
        solidCircle.setPosition(ng::b2_to_sf(center, ng::SCALE));
        solidCircle.setRadius(rad);
        solidCircle.setOrigin(sf::Vector2f(rad, rad));

        m_RenderWindow->draw(solidCircle);

        b2Vec2 p = center + radius * axis;
        DrawSegment(center, p, color);
    }

    void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
    {
        sf::RectangleShape line;
        float length = ng::distance(ng::b2_to_sf(p1, ng::SCALE), ng::b2_to_sf(p2, ng::SCALE));
        line.setSize(sf::Vector2f(length, m_Thickness));
        line.setPosition(ng::b2_to_sf(p1, ng::SCALE));
        line.setFillColor(ng::b2_to_sf(color));
        line.setOrigin(sf::Vector2f(line.getOrigin().x, m_Thickness/2.f));


        float delta_x = p2.x - p1.x;
        float delta_y = p2.y - p1.y;
        float angle = atan2(delta_y, delta_x);
        line.setRotation(ng::toDegree(angle));

        m_RenderWindow->draw(line);
    }

    void DebugDraw::DrawTransform(const b2Transform& xf)
    {
        const float32 k_axisScale  = 0.4f;

        b2Vec2 p1, p2;
        p1 = xf.p;
        p2 = p1 + k_axisScale * xf.q.GetXAxis();
        DrawSegment(p1, p2, b2Color(1.0f, 0.0f, 0.0f));

        p2 = p1 + k_axisScale * xf.q.GetYAxis();
        DrawSegment(p1, p2, b2Color(0.0f, 1.0f, 0.0f));
    }

    void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
    {
        float s = size*1.5f;
        sf::RectangleShape point;
        point.setFillColor(ng::b2_to_sf(color));
        point.setPosition(ng::b2_to_sf(p, ng::SCALE));
        point.setSize(sf::Vector2f(s, s));
        point.setOrigin(sf::Vector2f(s/2, s/2));

        m_RenderWindow->draw(point);
    }

    void DebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
    {
        sf::ConvexShape aabb_shape;
        aabb_shape.setOutlineColor(ng::b2_to_sf(color));
        aabb_shape.setPointCount(4);

        aabb_shape.setPoint(0, ng::b2_to_sf(aabb->lowerBound, ng::SCALE));
        aabb_shape.setPoint(1, sf::Vector2f(aabb->upperBound.x * ng::SCALE, aabb->lowerBound.y * ng::SCALE));
        aabb_shape.setPoint(2, ng::b2_to_sf(aabb->upperBound, ng::SCALE));
        aabb_shape.setPoint(3, sf::Vector2f(aabb->lowerBound.x * ng::SCALE, aabb->upperBound.y * ng::SCALE));

        m_RenderWindow->draw(aabb_shape);
    }
}
