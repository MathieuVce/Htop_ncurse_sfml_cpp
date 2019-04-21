/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** NamesModule
*/

#include "NamesModule.hpp"
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

NamesModule::NamesModule() : IMonitorModule("Computer Informations", 100, 10, true)
{
    this->setHostName();
    this->setUserName();
    this->_font->loadFromFile("ressources/UbuntuMono.ttf");
}

NamesModule::~NamesModule()
{
}

void NamesModule::setHostName()
{
    char *tmp = new char[HOST_NAME_MAX];

    gethostname(tmp, HOST_NAME_MAX);
    this->_HostName = tmp;
}

void NamesModule::setUserName()
{
    char *tmp = getenv("USER");
    this->_UserName = tmp;
}

std::string NamesModule::getHostName()
{
    return this->_HostName;
}

std::string NamesModule::getUserName()
{
    return this->_UserName;
}

bool NamesModule::getDisp()
{
    return (this->_isdisplay);
}

void NamesModule::setDisp(bool b)
{
    this->_isdisplay = b;
}

void NamesModule::update()
{
    this->setUserName();
    this->setHostName();
}

void NamesModule::drawSFML(sf::RenderWindow &window, sf::Vector2i &offset)
{
    float h = getHeightSFML();
    float x = 400;
    sf::Vector2f size(x, h);

    uint fontSize = 20;

    sf::RectangleShape back(size);
    back.setPosition(offset.x, offset.y);
    back.setOutlineColor(sf::Color::White);
    back.setFillColor(sf::Color::White);
    window.draw(back);
    sf::Text t(this->getName(), *_font);
    t.setCharacterSize(fontSize);
    t.setPosition(200 - t.getLocalBounds().width / 2 + offset.x, offset.y + 5);
    //t.setFillColor(sf::Color::Black);
    t.setColor(sf::Color::Black);
    window.draw(t);
    t.setPosition(offset.x + 5, offset.y + 5 + fontSize);
    t.setString("Host name: " + _HostName);
    window.draw(t);
    t.move(0, fontSize);
    t.setString("User name: " + _UserName);
    window.draw(t);
}

void NamesModule::drawNcurses(WINDOW *win, int offset[3])
{
    win = subwin(stdscr, offset[1], 45, offset[2], offset[0]);
    wprintw(win, "\n  ");
    wattron(win, A_BOLD | A_STANDOUT | COLOR_PAIR(1));
    wprintw(win, this->getName().c_str());
    wattroff(win, A_BOLD | A_STANDOUT);
    wprintw(win, "\n  ");
    wprintw(win, "Host Name: ");
    wattron(win, A_BOLD);
    wprintw(win, this->_HostName.c_str());
    wattroff(win, A_BOLD);
    wprintw(win, "\n  ");
    wprintw(win, "User Name: ");
    wattron(win, A_BOLD);
    wprintw(win, this->_UserName.c_str());
    wattroff(win, A_BOLD);
    wborder(win, '|', '|', '-', '-', '/', '\\', '\\', '/');
    wattroff(win, COLOR_PAIR(1));
    wrefresh(win);
}
