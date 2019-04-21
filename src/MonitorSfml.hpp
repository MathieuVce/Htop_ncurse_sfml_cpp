/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** MonitorSfml.hpp
*/

#ifndef MONITORSFML_HPP_
# define MONITORSFML_HPP_

#include "IMonitorDisplay.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class MonitorSfml : public IMonitorDisplay {
public:
    MonitorSfml();
    sf::RenderWindow *getWindow();
    void init_window() override;
    void drawModules();
    sf::Mouse getMouse();
    bool getIsMousePressed();
    void setIsMousePressed(bool);
private:
    void drawMenu();
    sf::Font *_font = new sf::Font;
    sf::RenderWindow *_window;
    sf::Mouse _mouse;
    bool _isMousePressed;
};

#endif
