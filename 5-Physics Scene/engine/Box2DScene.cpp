////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
//SFML
#include <SFML/Window/Event.hpp>
//Nero Games
#include "Box2DScene.h"
////////////////////////////////////////////////////////////
namespace ng
{
    Box2DScene::Box2DScene():
         m_SceneName("Empty Box2D Scene")
        ,m_RenderWindow(nullptr)
    {
        //ctor
    }

    Box2DScene::~Box2DScene()
    {
        //dtor
    }

    void Box2DScene::init()
    {

    }

    void Box2DScene::handleEvent(const sf::Event& event)
    {
        switch(event.type)
        {
            //Window
            case sf::Event::Closed:
                onWindowClosed(); break;
            case sf::Event::Resized:
                onWindowResized(sf::Vector2u(event.size.width, event.size.height)); break;
            case sf::Event::GainedFocus:
                onWindowFocusChanged(true); break;
            case sf::Event::LostFocus:
                onWindowFocusChanged(false); break;

            //Keyboard
            case sf::Event::KeyPressed:
            {
                ModifierKey modifier;
                modifier.alt        = event.key.alt;
                modifier.control    = event.key.control;
                modifier.shift      = event.key.shift;
                modifier.system     = event.key.system;

                onKeyboardButton(event.key.code, true, modifier);
            }break;
            case sf::Event::KeyReleased:
            {
                ModifierKey modifier;
                modifier.alt        = event.key.alt;
                modifier.control    = event.key.control;
                modifier.shift      = event.key.shift;
                modifier.system     = event.key.system;

                onKeyboardButton(event.key.code, false, modifier);
            }break;
            case sf::Event::TextEntered:
            {
                if (event.text.unicode < 128)
                {
                    onTextEntered(std::string(1, (static_cast<char>(event.text.unicode))));
                }
            }break;

            //Mouse
            case sf::Event::MouseMoved:
                onMouseMoved(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)); break;
            case sf::Event::MouseButtonPressed:
                onMouseButton(event.mouseButton.button, true, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); break;
            case sf::Event::MouseButtonReleased:
                onMouseButton(event.mouseButton.button, false, sf::Vector2f(event.mouseButton.x, event.mouseButton.y)); break;
            case sf::Event::MouseWheelScrolled:
                onMouseWheel(event.mouseWheelScroll.wheel, event.mouseWheelScroll.delta,sf::Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y)); break;
            case sf::Event::MouseEntered:
                onMouseWindowSurface(true); break;
            case sf::Event::MouseLeft:
                onMouseWindowSurface(false); break;

            //Joystick
            case sf::Event::JoystickConnected:
                onJoystickConnection(event.joystickConnect.joystickId, true); break;
            case sf::Event::JoystickDisconnected:
                onJoystickConnection(event.joystickConnect.joystickId, false); break;
            case sf::Event::JoystickButtonPressed:
                onJoystickButton(event.joystickButton.joystickId, event.joystickButton.button, true); break;
            case sf::Event::JoystickButtonReleased:
                onJoystickButton(event.joystickButton.joystickId, event.joystickButton.button, false); break;
            case sf::Event::JoystickMoved:
                onJoystickAxis(event.joystickMove.joystickId, event.joystickMove.axis, event.joystickMove.position); break;
        }

    }

    void Box2DScene::update(const sf::Time& timeStep)
    {

    }

    void Box2DScene::render()
    {

    }

    void Box2DScene::destroy()
    {
        m_RenderWindow = nullptr;
    }

    void Box2DScene::clear()
    {
        m_RenderWindow->clear();
    }

    std::string Box2DScene::getSceneName() const
    {
        return m_SceneName;
    }

    void Box2DScene::setSceneName(const std::string& name)
    {
        m_SceneName = name;
    }

    sf::Vector2f Box2DScene::getSceneResolution() const
    {
        return m_Resolution;
    }

    sf::RenderWindow& Box2DScene::getRenderWindow() const
    {
        return *m_RenderWindow;
    }

    float Box2DScene::getFrameRate() const
    {
        return m_FrameRate;
    }

    float Box2DScene::getFrameTime() const
    {
        return m_FrameTime;
    }

    void Box2DScene::onWindowClosed()
    {
        getRenderWindow().close();
    }

    void Box2DScene::onWindowResized(const sf::Vector2u& size)
    {

    }

    void Box2DScene::onWindowFocusChanged(const bool& gainedFocus)
    {

    }

    void Box2DScene::onKeyboardButton(const sf::Keyboard::Key& key, const bool& isPressed, const ModifierKey& modifier)
    {

    }

    void Box2DScene::onTextEntered(const std::string& c)
    {

    }

    void Box2DScene::onMouseMoved(const sf::Vector2f& position)
    {

    }

    void Box2DScene::onMouseButton(const sf::Mouse::Button& button, const bool& sPressed, const sf::Vector2f& position)
    {

    }

    void Box2DScene::onMouseWheel(const sf::Mouse::Wheel& wheel, const float& delta, const sf::Vector2f& position)
    {

    }

    void Box2DScene::onMouseWindowSurface(const bool& mouseEntered)
    {

    }

    void Box2DScene::onJoystickConnection(const unsigned int& joystickId, const bool& connected)
    {

    }

    void Box2DScene::onJoystickButton(const unsigned int& joystickId, const unsigned int& button, const bool& isPressed)
    {

    }

    void Box2DScene::onJoystickAxis(const unsigned int& joystickId, const sf::Joystick::Axis& axis, const float& position)
    {

    }
}




