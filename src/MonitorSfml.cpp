/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** MonitorSfml.hpp
*/

#include "MonitorSfml.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

MonitorSfml::MonitorSfml()
{
    this->_font->loadFromFile("ressources/UbuntuMono.ttf");
}

sf::RenderWindow *MonitorSfml::getWindow()
{
    return (_window);
}

void MonitorSfml::init_window()
{
    _window = new sf::RenderWindow(sf::VideoMode(_manager->getColumnCount() * 400 + 300, _manager->getMaxColumnHeight()), "SFML window");
}

void MonitorSfml::drawModules()
{
    sf::Color c(205, 196, 208);
    sf::Vector2f s(400, 1);
    sf::RectangleShape line(s);
    line.setFillColor(c);
    drawMenu();
    sf::Vector2i offset(300, 0);
    for (std::vector<IMonitorModule *> v : _manager->getModules()) {
        offset.y = 0;
        for (IMonitorModule *module : v) {
            if (module->getDisp()) {
                module->drawSFML(*_window, offset);
                offset.y += module->getHeightSFML();
                line.setPosition(offset.x, offset.y - 1);
                _window->draw(line);
            }
        }
        offset.x += 400;
    }
}

sf::Mouse MonitorSfml::getMouse()
{
    return (_mouse);
}

bool MonitorSfml::getIsMousePressed()
{
    return (_isMousePressed);
}

void MonitorSfml::setIsMousePressed(bool d)
{
    _isMousePressed = d;
}

void MonitorSfml::drawMenu()
{
    sf::Color c(205, 196, 208);
    sf::Vector2f size(300, 60 * _manager->getTotalModuleCount());
    sf::Vector2f size1(20, 20);
    sf::Vector2f s(1, 3000);
    sf::Vector2f s1(300, 1);
    sf::RectangleShape back(size);
    sf::RectangleShape linev(s);
    sf::RectangleShape lineh(s1);
    sf::RectangleShape but(size1);
    lineh.setFillColor(c);
    linev.setFillColor(c);
    linev.setPosition(299, 0);
    lineh.setPosition(0, 60);
    sf::Rect<int> input(0, 0, 300, 60);
    sf::Text t;
    sf::Vector2i offset(0, 0);
    back.setFillColor(sf::Color::White);
    t.setFont(*_font);
    t.setCharacterSize(18);
    // t.setFillColor(sf::Color::Black);
    t.setColor(sf::Color::Black);
    _window->draw(back);
    for (std::vector<IMonitorModule *> v : _manager->getModules()) {
        for (IMonitorModule *module : v) {
            t.setString(module->getName());
            t.setPosition(offset.x + 10, offset.y + 20);
            but.setFillColor(module->getDisp() ? sf::Color::Green : sf::Color::Red);
            but.setPosition(offset.x + 270, offset.y + 20);
            if (input.contains(getMouse().getPosition(*_window).x, getMouse().getPosition(*_window).y) && getMouse().isButtonPressed(sf::Mouse::Left) && !getIsMousePressed()) {
                module->setDisp(module->getDisp() ? false : true);
                setIsMousePressed(true);
            }
            _window->draw(lineh);
            _window->draw(t);
            _window->draw(but);
            lineh.move(0, 60);
            offset.y += 60;
            input.top += 60;
        }
    }
    _window->draw(linev);
}
