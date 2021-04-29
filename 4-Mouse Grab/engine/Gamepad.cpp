////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
#include "Gamepad.h"
#include <cmath>
#include <Nero/utility/Utility.h>
////////////////////////////////////////////////////////////
namespace ng
{
    //
    const float Gamepad::AXIS_SENSIVITY         = 6.f;
    const float Gamepad::AXIS_BUTTON_THRESHOLD  = 90.f;

    Gamepad::Gamepad():
         m_GamepadId(Gamepad::NONE)
        ,m_ButtonMapping()
        ,m_AxisMapping()
        ,m_ButtonMappingReverse()
        ,m_AxisMappingReverse()
        ,m_PreviousAxisButton(JSButton::NONE)
    {
        //ctor
    }

    void Gamepad::setId(const Gamepad::ID& gamepadId)
    {
        m_GamepadId = gamepadId;
    }

    void Gamepad::setButtonMapping(const JSButtonMapping& mapping)
    {
        m_ButtonMapping = mapping;

        for (auto const& item : mapping)
        {
            m_ButtonMappingReverse[item.second] = item.first;

        }
    }

    void Gamepad::setAxisMapping(const JSAxisMapping& mapping)
    {
        m_AxisMapping = mapping;

        for (auto const& item : mapping)
        {
            m_AxisMappingReverse[item.second] = item.first;
        }
    }

    const Gamepad::ID Gamepad::getId() const
    {
        return m_GamepadId;
    }

    bool Gamepad::isConnected() const
    {
        return sf::Joystick::isConnected(getId());
    }

    JSButton Gamepad::getButton(const unsigned int& buttonId)
    {
        return m_ButtonMapping.at(buttonId);
    }

    JSAxis Gamepad::getAxis(const sf::Joystick::Axis& axisId)
    {
        return m_AxisMapping.at(axisId);
    }

    JSButton Gamepad::getButton(const sf::Joystick::Axis& axisId, const float& position)
    {
        JSAxis axis     = m_AxisMapping.at(axisId);
        float threshold = AXIS_BUTTON_THRESHOLD;

        switch(axis)
        {
            case JSAxis::DPadX:
            {
                if(position == -100.f) return JSButton::DPadLeft;
                if(position == 100.f) return JSButton::DPadRight;
            };

            case JSAxis::DPadY:
            {
                if(position ==  100.f) return JSButton::DPadUp;
                if(position == -100.f) return JSButton::DPadDown;
            };

            case JSAxis::LeftAnalogX:
            {
                if(position < -threshold) return JSButton::LeftAnalogLeft;
                if(position >  threshold) return JSButton::LeftAnalogRight;
            };

            case JSAxis::LeftAnalogY:
            {
                if(position >  threshold) return JSButton::LeftAnalogDown;
                if(position < -threshold) return JSButton::LeftAnalogUp;
            };

            case JSAxis::RightAnalogX:
            {
                if(position < -threshold) return JSButton::RightAnalogLeft;
                if(position >  threshold) return JSButton::RightAnalogRight;
            };

            case JSAxis::RightAnalogY:
            {
                if(position >  threshold) return JSButton::RightAnalogDown;
                if(position < -threshold) return JSButton::RightAnalogUp;
            };

            default: return JSButton::NONE;
        }
    }

    JSButton Gamepad::getButton(const sf::Joystick::Axis& axisId, const float& position, bool& isPressed)
    {
        JSButton button = getButton(axisId, position);
        JSAxis   axis   = m_AxisMapping.at(axisId);

        if(axis == JSAxis::DPadX || axis == JSAxis::DPadY)
        {
            isPressed = std::abs(position) == 100.f;
        }
        else
        {
            isPressed = std::abs(position) > AXIS_BUTTON_THRESHOLD;

        }

        if(isPressed)
        {
            m_PreviousAxisButton = button;
        }
        else
        {
            button              = m_PreviousAxisButton;
            m_PreviousAxisButton = JSButton::NONE;
        }

        return button;
    }

    bool Gamepad::isButtonPressed(const JSButton& button)
    {
        if(m_ButtonMappingReverse.find(button) != m_ButtonMappingReverse.end())
        {
            return sf::Joystick::isButtonPressed(getId(), m_ButtonMappingReverse.at(button));
        }
        else
        {
            return isAxisButtonPressed(button);
        }
    }

    bool Gamepad::isAxisButtonPressed(const JSButton& button)
    {
        float threshold = AXIS_BUTTON_THRESHOLD;

        switch(button)
        {
            case JSButton::DPadLeft : return (getAxisPosition(JSAxis::DPadX) == -100.f);
            case JSButton::DPadRight : return (getAxisPosition(JSAxis::DPadX) == 100.f);
            case JSButton::DPadUp : return (getAxisPosition(JSAxis::DPadY) == -100.f);
            case JSButton::DPadDown : return (getAxisPosition(JSAxis::DPadY) == 100.f);
            case JSButton::LeftAnalogLeft : return (getAxisPosition(JSAxis::LeftAnalogX) < -threshold);
            case JSButton::LeftAnalogRight : return (getAxisPosition(JSAxis::LeftAnalogX) >  threshold);
            case JSButton::LeftAnalogUp : return (getAxisPosition(JSAxis::LeftAnalogY) < -threshold);
            case JSButton::LeftAnalogDown : return (getAxisPosition(JSAxis::LeftAnalogY) >  threshold);
            case JSButton::RightAnalogLeft : return (getAxisPosition(JSAxis::RightAnalogX) < -threshold);
            case JSButton::RightAnalogRight : return (getAxisPosition(JSAxis::RightAnalogX) >  threshold);
            case JSButton::RightAnalogUp : return (getAxisPosition(JSAxis::RightAnalogY) < -threshold);
            case JSButton::RightAnalogDown : return (getAxisPosition(JSAxis::RightAnalogY) >  threshold);
            default: return false;
        }
    }

    float Gamepad::getAxisPosition(const JSAxis& axis)
    {
        switch(axis)
        {
            case JSAxis::DPadX: return sf::Joystick::getAxisPosition(getId(), m_AxisMappingReverse.at(JSAxis::DPadX));
            case JSAxis::DPadY: return sf::Joystick::getAxisPosition(getId(), m_AxisMappingReverse.at(JSAxis::DPadY));
            case JSAxis::LeftAnalogX: return sf::Joystick::getAxisPosition(getId(), m_AxisMappingReverse.at(JSAxis::LeftAnalogX));
            case JSAxis::LeftAnalogY: return sf::Joystick::getAxisPosition(getId(), m_AxisMappingReverse.at(JSAxis::LeftAnalogY));
            case JSAxis::RightAnalogX: return sf::Joystick::getAxisPosition(getId(), m_AxisMappingReverse.at(JSAxis::RightAnalogX));
            case JSAxis::RightAnalogY: return sf::Joystick::getAxisPosition(getId(), m_AxisMappingReverse.at(JSAxis::RightAnalogY));
            case JSAxis::ShoulderX: return sf::Joystick::getAxisPosition(getId(), m_AxisMappingReverse.at(JSAxis::ShoulderX));
            case JSAxis::ShoulderY: return sf::Joystick::getAxisPosition(getId(), m_AxisMappingReverse.at(JSAxis::ShoulderY));
            default: 0.f;
        }
    }
}
