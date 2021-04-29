////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef GAMEPAD_H
#define GAMEPAD_H
///////////////////////////HEADERS//////////////////////////
//Nero Games
#include <GamepadUtil.h>
//SFML
#include <SFML/System/Vector2.hpp>
////////////////////////////////////////////////////////////
namespace ng
{
    class Gamepad
    {
        public:
            enum ID {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NONE};
            static const float AXIS_SENSIVITY;
            static const float AXIS_BUTTON_THRESHOLD;

        public:
                                    Gamepad();

            void                    setId(const ID& gamepadId);
            void                    setButtonMapping(const JSButtonMapping& mapping);
            void                    setAxisMapping(const JSAxisMapping& mapping);

            const ID                getId() const;
            bool                    isConnected() const;
            JSButton                getButton(const unsigned int& buttonId);
            JSButton                getButton(const sf::Joystick::Axis& axisId, const float& position);
            JSButton                getButton(const sf::Joystick::Axis& axisId, const float& position, bool& isPressed);
            JSAxis                  getAxis(const sf::Joystick::Axis& axisId);

            //Global inputs
            bool                    isButtonPressed(const JSButton& button);
            float                   getAxisPosition(const JSAxis& axis);

        private:
            bool                    isAxisButtonPressed(const JSButton& button);


        protected:
            ID                      m_GamepadId;
            JSButtonMapping         m_ButtonMapping;
            JSButton                m_PreviousAxisButton;
            JSButtonMappingReverse  m_ButtonMappingReverse;
            JSAxisMappingReverse    m_AxisMappingReverse;
            JSAxisMapping           m_AxisMapping;
    };
}

#endif // GAMEPAD_H
