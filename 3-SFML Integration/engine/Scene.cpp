////////////////////////////////////////////////////////////
// Nero Game Engine - SFML Tutorials
// Copyright (c) 2021 Sanou A. K. Landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
//SFML
#include <SFML/Window/Event.hpp>
//Nero Games
#include "Scene.h"
////////////////////////////////////////////////////////////
namespace ng
{
    Scene::Scene():
         m_SceneName("Empty Scene")
        ,m_RenderWindow(nullptr)
    {
        //ctor
    }

    Scene::~Scene()
    {
        //dtor
    }

    void Scene::init()
    {

    }

    void Scene::handleEvent(const sf::Event& event)
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

    void Scene::update(const sf::Time& timeStep)
    {

    }

    void Scene::render()
    {

    }

    void Scene::destroy()
    {
        m_RenderWindow = nullptr;
    }

    void Scene::clear()
    {
        m_RenderWindow->clear();
    }

    std::string Scene::getSceneName() const
    {
        return m_SceneName;
    }

    void Scene::setSceneName(const std::string& name)
    {
        m_SceneName = name;
    }

    sf::Vector2f Scene::getSceneResolution() const
    {
        return m_Resolution;
    }

    sf::RenderWindow& Scene::getRenderWindow() const
    {
        return *m_RenderWindow;
    }

    float Scene::getFrameRate() const
    {
        return m_FrameRate;
    }

    float Scene::getFrameTime() const
    {
        return m_FrameTime;
    }

    void Scene::onWindowClosed()
    {
        getRenderWindow().close();
    }

    void Scene::onWindowResized(const sf::Vector2u& size)
    {

    }

    void Scene::onWindowFocusChanged(const bool& gainedFocus)
    {

    }

    void Scene::onKeyboardButton(const sf::Keyboard::Key& key, const bool& isPressed, const ModifierKey& modifier)
    {

    }

    void Scene::onTextEntered(const std::string& c)
    {

    }

    void Scene::onMouseMoved(const sf::Vector2f& position)
    {

    }

    void Scene::onMouseButton(const sf::Mouse::Button& button, const bool& sPressed, const sf::Vector2f& position)
    {

    }

    void Scene::onMouseWheel(const sf::Mouse::Wheel& wheel, const float& delta, const sf::Vector2f& position)
    {

    }

    void Scene::onMouseWindowSurface(const bool& mouseEntered)
    {

    }

    void Scene::onJoystickConnection(const unsigned int& joystickId, const bool& connected)
    {

    }

    void Scene::onJoystickButton(const unsigned int& joystickId, const unsigned int& button, const bool& isPressed)
    {

    }

    void Scene::onJoystickAxis(const unsigned int& joystickId, const sf::Joystick::Axis& axis, const float& position)
    {

    }
}




