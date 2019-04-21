/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** Graph.hpp
*/
#ifndef GRAPH_HPP_
# define GRAPH_HPP_

#include <def.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Graph {
public:
    explicit Graph(std::string name, uint height, uint max, uint maxBars, uint barWidth);
    void push_data(uint);
    void draw(sf::Vector2i offset, sf::RenderWindow *window);

private:
    const std::string _name;
    const uint _height;
    const uint _max;
    const uint _barWidth;
    std::vector<uint> _data;
    const uint _maxBars;
    sf::Font *_font = new sf::Font;
};


#endif //GRAPH_HPP_
