////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef GAMEPADUTIL_H_INCLUDED
#define GAMEPADUTIL_H_INCLUDED
///////////////////////////HEADERS//////////////////////////
//SFML
#include <SFML/Window/Joystick.hpp>
//CPP
#include <map>
////////////////////////////////////////////////////////////
namespace ng
{
    enum class JSButton
    {
        //Action
         Square
        ,Cross
        ,Circle
        ,Triangle
        //
        ,Option
        ,Share
        ,Start
        ,Touchpad
        //
        ,L1
        ,L2
        ,L3
        ,R1
        ,R2
        ,R3
        //DPad
        ,DPadLeft
        ,DPadRight
        ,DPadUp
        ,DPadDown
        //LeftAnalog
        ,LeftAnalogLeft
        ,LeftAnalogRight
        ,LeftAnalogUp
        ,LeftAnalogDown
         //RightAnalog
        ,RightAnalogLeft
        ,RightAnalogRight
        ,RightAnalogUp
        ,RightAnalogDown

        ,NONE
    };

    enum class JSAxis
    {
         DPadX
        ,DPadY
        ,LeftAnalogX
        ,LeftAnalogY
        ,RightAnalogX
        ,RightAnalogY
        ,ShoulderX
        ,ShoulderY

        ,NONE
    };


    inline std::string JString(const JSButton& button)
    {
        switch(button)
        {
            case JSButton::DPadLeft: return "DPadLeft";
            case JSButton::DPadRight: return "DPadRight";
            case JSButton::DPadUp: return "DPadUp";
            case JSButton::DPadDown: return "DPadDown";
            case JSButton::LeftAnalogLeft: return "LeftAnalogLeft";
            case JSButton::LeftAnalogRight: return "LeftAnalogRight";
            case JSButton::LeftAnalogUp: return "LeftAnalogUp";
            case JSButton::LeftAnalogDown: return "LeftAnalogDown";
            case JSButton::RightAnalogLeft: return "LeftAnalogLeft";
            case JSButton::RightAnalogRight: return "LeftAnalogRight";
            case JSButton::RightAnalogUp: return "LeftAnalogUp";
            case JSButton::RightAnalogDown: return "LeftAnalogDown";
            case JSButton::Square: return "Square";
            case JSButton::Cross: return "Cross";
            case JSButton::Circle: return "Circle";
            case JSButton::Triangle: return "Triangle";
            case JSButton::Option: return "Option";
            case JSButton::Share: return "Share";
            case JSButton::Start: return "Start";
            case JSButton::Touchpad: return "Touchpad";
            case JSButton::L1: return "L1";
            case JSButton::L2: return "L2";
            case JSButton::L3: return "L3";
            case JSButton::R1: return "R1";
            case JSButton::R2: return "R2";
            case JSButton::R3: return "R3";
            default : return "Unknown JSButton";
        }
    }

    inline std::string JString(const JSAxis& axis)
    {
        switch(axis)
        {
            case JSAxis::DPadX: return "DPadX";
            case JSAxis::DPadY: return "DPadY";
            case JSAxis::LeftAnalogX: return "LeftAnalogX";
            case JSAxis::LeftAnalogY: return "LeftAnalogY";
            case JSAxis::RightAnalogX: return "RightAnalogX";
            case JSAxis::RightAnalogY: return "RightAnalogY";
            case JSAxis::ShoulderX: return "ShoulderX";
            case JSAxis::ShoulderY: return "ShoulderY";
            default : return "Unknown JSAxis";
        }
    }

    //Mapping
    typedef std::map<unsigned int, JSButton>        JSButtonMapping;
    typedef std::map<sf::Joystick::Axis, JSAxis>    JSAxisMapping;
    typedef std::map<JSButton, unsigned int>        JSButtonMappingReverse;
    typedef std::map<JSAxis, sf::Joystick::Axis>    JSAxisMappingReverse;

    //PS4 Button Mapping
    const JSButtonMapping JSPs4ButtonMapping
    {{0,    JSButton::Square},
     {1,    JSButton::Cross},
     {2,    JSButton::Circle},
     {3,    JSButton::Triangle},
     {4,    JSButton::L1},
     {5,    JSButton::R1},
     {6,    JSButton::L2},
     {7,    JSButton::R2},
     {8,    JSButton::Share},
     {9,    JSButton::Option},
     {10,   JSButton::L3},
     {11,   JSButton::R3},
     {12,   JSButton::Start},
     {13,   JSButton::Touchpad}};

    const JSAxisMapping JSPs4AxisMapping
    {{sf::Joystick::X,      JSAxis::LeftAnalogX},
     {sf::Joystick::Y,      JSAxis::LeftAnalogY},
     {sf::Joystick::Z,      JSAxis::RightAnalogX},
     {sf::Joystick::R,      JSAxis::RightAnalogY},
     {sf::Joystick::PovX,   JSAxis::DPadX},
     {sf::Joystick::PovY,   JSAxis::DPadY},
     {sf::Joystick::U,      JSAxis::ShoulderX},
     {sf::Joystick::V,      JSAxis::ShoulderY}};
}

#endif // GAMEPADUTIL_H_INCLUDED

