////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
#ifndef BOX2DSCENE_H
#define BOX2DSCENE_H
///////////////////////////HEADERS//////////////////////////
//Nero Games
#include "KeyboardUtil.h"
#include "PhysicWorld.h"
//SFML
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
//CPP
#include <memory>
////////////////////////////////////////////////////////////
namespace ng
{
    class Box2DScene
    {
        public:
            typedef std::unique_ptr<Box2DScene> Ptr;

        public:
                                        Box2DScene();
            virtual                    ~Box2DScene();

        public:
            virtual void                init();
            virtual void                handleEvent(const sf::Event& event);
            virtual void                update(const sf::Time& timeStep);
            virtual void                clear();
            virtual void                render();
            virtual void                destroy();

        public:
            //getter
            std::string                 getSceneName() const;
            sf::Vector2f                getSceneResolution() const;
            sf::RenderWindow&           getRenderWindow() const;
            //frame rate
            float                       getFrameRate() const;
            float                       getFrameTime() const;
            //setter
            void                        setSceneName(const std::string& name);

        private:
            //events callbacks
                //window
            virtual void                onWindowClosed();
            virtual void                onWindowResized(const sf::Vector2u& size);
            virtual void                onWindowFocusChanged(const bool& gainedFocus);
                //keyboard
            virtual void                onKeyboardButton(const sf::Keyboard::Key& key, const bool& isPressed, const ModifierKey& modifier);
            virtual void                onTextEntered(const std::string& c);
                //mouse
            virtual void                onMouseMoved(const sf::Vector2f& position);
            virtual void                onMouseButton(const sf::Mouse::Button& button, const bool& isPressed, const sf::Vector2f& position);
            virtual void                onMouseWheel(const sf::Mouse::Wheel& wheel, const float& delta, const sf::Vector2f& position);
            virtual void                onMouseWindowSurface(const bool& mouseEntered);
            //joystick
            virtual void                onJoystickConnection(const unsigned int& joystickId, const bool& connected);
            virtual void                onJoystickButton(const unsigned int& joystickId, const unsigned int& button, const bool& isPressed);
            virtual void                onJoystickAxis(const unsigned int& joystickId, const sf::Joystick::Axis& axis, const float& position);

        protected:
            friend class                Engine;
            std::string                 m_SceneName;
            sf::Vector2f                m_Resolution;
            sf::RenderWindow*           m_RenderWindow;
            //frame rate
            float                       m_FrameRate;
            float                       m_FrameTime;
            //physics
            PhysicWorld                 m_PhysicWorld;
    };
}

#endif // BOX2DSCENE_H
