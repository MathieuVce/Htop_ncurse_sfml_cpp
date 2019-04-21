/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** Graph.cpp
*/
#include <iostream>
#include "Graph.hpp"

Graph::Graph(std::string name, uint height, uint max, uint maxBars, uint barWidth): _name(name), _height(height), _max(max), _maxBars(maxBars), _barWidth(barWidth)
{
    _font->loadFromFile("ressources/UbuntuMono.ttf");
}

void Graph::push_data(uint data)
{
    if (_data.size() > _maxBars) {
        _data.erase(_data.begin());
    }
    _data.push_back(data);
}

void Graph::draw(sf::Vector2i offset, sf::RenderWindow *window)
{
    static sf::RectangleShape rect;
    static sf::Color color = sf::Color::Black;
    static uint realHeight = (_height > 10) ? _height - 10 : 0;
    static bool isInit = false;
    sf::Text name(_name, *_font);
    const unsigned short margin = 5;
    const unsigned short colWidth = _barWidth;

    rect.setFillColor(color);
    rect.setPosition(offset.x + 380, offset.y + _height - margin);
    if (!isInit) {
        rect.rotate(180.0);
        isInit = true;
    }
    //name.setFillColor(sf::Color::Black);
    name.setColor(sf::Color::Black);
    name.setCharacterSize(13);
    name.setPosition(offset.x + 380 - (colWidth * _maxBars / 2 + (name.getLocalBounds().width / 2)) , offset.y + _height - 7);
    for (int i = static_cast<int>( _data.size() - 1); i >= 0; i--) {
        rect.setSize(sf::Vector2<float>(colWidth, realHeight * ((float)(_data[i]) / (float)_max)));
        window->draw(rect);
        rect.move(-1 * (colWidth), 0);
    }
    window->draw(name);

}