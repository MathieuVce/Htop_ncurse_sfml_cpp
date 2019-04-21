/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** DateModule
*/

#include "DateModule.hpp"
#include "../MonitorSfml.hpp"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sys/utsname.h>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ncurse/MonitorNcurse.hpp"

DateModule::DateModule() : IMonitorModule("Date", 100, 10 , true)
{
    this->setTime();
    this->_font->loadFromFile("ressources/UbuntuMono.ttf");
}

DateModule::~DateModule()
{
}

std::string DateModule::getTime()
{
    return this->_Time;
}

bool DateModule::getDisp()
{
    return (this->_isdisplay);
}

void DateModule::setDisp(bool b)
{
    this->_isdisplay = b;
}

void DateModule::setTime()
{
    time_t now = time(0);

    char *dt = ctime(&now);
    this->_Time = dt;
}

void DateModule::update()
{
    this->setTime();
}

void DateModule::drawSFML(sf::RenderWindow &window, sf::Vector2i &offset)
{
    float h = getHeightSFML();
    float x = 400;
    sf::Vector2f size(x, h);
    uint fontSize = 20;

    sf::Vector2f size1(20, 20);
    sf::RectangleShape but(size1);
    but.setFillColor(sf::Color::Red);
    but.setPosition(offset.x + 375, offset.y + 15);
    sf::RectangleShape back(size);
    back.setPosition(offset.x, offset.y);
    back.setOutlineColor(sf::Color::White);
    back.setFillColor(sf::Color::White);
    window.draw(back);
    sf::Text t(this->getName(), *_font);
    t.setCharacterSize(fontSize);
    t.setPosition(200 - t.getLocalBounds().width / 2 + offset.x, offset.y + 5);
    // t.setFillColor(sf::Color::Black);
    t.setColor(sf::Color::Black);
    window.draw(t);
    t.setPosition(offset.x + 5, offset.y + 5 + fontSize);
    t.move(0, fontSize);
    t.setString("OS time: " + _Time);
    window.draw(t);
}

void DateModule::drawNcurses(WINDOW *win, int offset[3])
{
    win = subwin(stdscr, offset[1], 45, offset[2], offset[0]);
    wprintw(win, "\n  ");
    wattron(win, A_BOLD | A_STANDOUT | COLOR_PAIR(2));
    wprintw(win, this->getName().c_str());
    wattroff(win, A_BOLD | A_STANDOUT);
    wprintw(win, "\n  ");
    wprintw(win, "OS Time : ");
    wattron(win, A_DIM);
    wprintw(win, this->_Time.c_str());
    wattroff(win, A_DIM);
    wborder(win, '|', '|', '-', '-', '/', '\\', '\\', '/');
    wattroff(win, COLOR_PAIR(2));
    wrefresh(win);
}
