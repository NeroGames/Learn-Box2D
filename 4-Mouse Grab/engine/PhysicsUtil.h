////////////////////////////////////////////////////////////
// Nero Game Engine - Box2D Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef PHYSICSUTIL_H_INCLUDED
#define PHYSICSUTIL_H_INCLUDED
///////////////////////////HEADERS//////////////////////////
#include <SFML/Graphics/Color.hpp>
////////////////////////////////////////////////////////////
namespace ng
{
    const float SCALE   = 30.f;

    inline sf::Color b2_to_sf(const b2Color& color, int transparency = 255)
    {
        return sf::Color(color.r * 255, color.g * 255, color.b * 255, transparency);
    }

    inline sf::Vector2f b2_to_sf(b2Vec2 vect, float scale = 1.f)
    {
        return sf::Vector2f(vect.x * scale, vect.y * scale);
    }

    inline sf::Vector2f b2_to_sf(float x, float y, float scale = 1.f)
    {
        return sf::Vector2f(x * scale, y * scale);
    }

    inline b2Color sf_to_b2(const sf::Color& color)
    {
        return b2Color(color.r / 255, color.g / 255, color.b / 255);
    }

    inline b2Vec2 sf_to_b2(const sf::Vector2f& vect, float scale = 1.f)
    {
        return b2Vec2(vect.x / scale, vect.y / scale);
    }

    inline b2Vec2 sf_to_b2(float x, float y, float scale = 1.f)
    {
        return b2Vec2(x / scale, y / scale);
    }


    inline float vectLength(sf::Vector2f vect)
    {
        return std::sqrt(vect.x * vect.x + vect.y * vect.y);
    }

    inline float vectLength(b2Vec2 vect)
    {
        return std::sqrt(vect.x * vect.x + vect.y * vect.y);
    }

    inline float distance(sf::Vector2f vect1, sf::Vector2f vect2)
    {
        return vectLength(vect2 - vect1);
    }

    inline float distance(b2Vec2 vect1, b2Vec2 vect2)
    {
        return vectLength(vect2 - vect1);
    }

    float toDegree (float radian)
    {
        return 180.f / 3.141592653589793238462643383f * radian;
    }

    float toRadian(float degree)
    {
        return 3.141592653589793238462643383f / 180.f * degree;
    }
}

#endif // PHYSICSUTIL_H_INCLUDED
