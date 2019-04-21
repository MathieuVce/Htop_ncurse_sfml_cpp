/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** OSModule
*/

#include "OSModule.hpp"
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

OSModule::OSModule() : IMonitorModule("OS Informations", 100, 10, true)
{
    this->setOSName();
    this->_font->loadFromFile("ressources/UbuntuMono.ttf");
}

OSModule::~OSModule()
{
}

void OSModule::setOSName()
{
    struct utsname *tmp = new struct utsname;

    uname(tmp);
    this->_OSName = tmp->sysname;
    this->_KernelVers = tmp->release;
}

std::string OSModule::getOSName()
{
    return this->_OSName;
}

std::string OSModule::getKernelVers()
{
    return this->_KernelVers;
}
void OSModule::update()
{
    this->setOSName();
}

bool OSModule::getDisp()
{
    return (this->_isdisplay);
}

void OSModule::setDisp(bool b)
{
    this->_isdisplay = b;
}

    void OSModule::drawSFML(sf::RenderWindow &winow, sf::Vector2i &offset)
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
    winow.draw(back);
    sf::Text t(this->getName(), *_font);
    t.setCharacterSize(fontSize);
    t.setPosition(200 - t.getLocalBounds().width / 2 + offset.x, offset.y + 5);
    //t.setFillColor(sf::Color::Black);
    t.setColor(sf::Color::Black);
    winow.draw(t);
    t.setPosition(offset.x + 5, offset.y + 5 + fontSize);
    t.move(0, fontSize);
    t.setString("OS name: " + _OSName);
    winow.draw(t);
    t.move(0, fontSize);
    t.setString("Kernel version: " + _KernelVers);
    winow.draw(t);
}

void OSModule::drawNcurses(WINDOW *win, int offset[3])
{
    win = subwin(stdscr, offset[1], 45, offset[2], offset[0]);
    wprintw(win, "\n  ");
    wattron(win, A_BOLD | A_STANDOUT | COLOR_PAIR(2));
    wprintw(win, this->getName().c_str());
    wattroff(win, A_BOLD | A_STANDOUT);
    wprintw(win, "\n  ");
    wprintw(win, "OS Name: ");
    wattron(win, A_NORMAL);
    wprintw(win, this->_OSName.c_str());
    wattroff(win, A_NORMAL);
    wprintw(win, "\n  ");
    wprintw(win, "Kernel Version: ");
    wattron(win, A_UNDERLINE);
    wprintw(win, this->_KernelVers.c_str());
    wattroff(win, A_UNDERLINE);
    wborder(win, '|', '|', '-', '-', '/', '\\', '\\', '/');
    wattroff(win, COLOR_PAIR(2));
    wrefresh(win);
}
