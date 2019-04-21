/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** init_screen
*/

#include <iostream>
#include <ncurses.h>
#include "MonitorNcurse.hpp"
#include <menu.h>

MonitorNcurse::MonitorNcurse() : IMonitorDisplay()
{
}

WINDOW *MonitorNcurse::getWindow()
{
    return (this->_win);
}

void MonitorNcurse::setWindow(WINDOW *win)
{
    this->_win = win;
}

void MonitorNcurse::init_window()
{
    WINDOW *win = new WINDOW;

    initscr();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    this->_win = win;
}

void MonitorNcurse::drawModules()
{
    int offset[3]{48, 0, 5};
    int count = 0;

    for (std::vector<IMonitorModule *> v : _manager->getModules())
    {
        offset[1] = 1;
        for (IMonitorModule *module : v)
        {
            if (module->getDisp())
            {
                count++;
                if (count > 3)
                {
                    count = 1;
                    offset[2] += 12;
                    offset[0] = 48;
                }
                offset[1] = module->getHeightNcurses();
                module->drawNcurses(_win, offset);
                offset[0] += 48;
            }
        }
    }
}