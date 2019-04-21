/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** launch.cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "MonitorSfml.hpp"
#include "ncurse/MonitorNcurse.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "ModuleManager.hpp"
#include "modules/DateModule.hpp"
#include "modules/NamesModule.hpp"
#include "modules/OSModule.hpp"
#include "modules/CPUModule.hpp"
#include "modules/RAMModule.hpp"

void launch_sfml()
{
    sf::Color c(205, 196, 208);
    MonitorSfml m;
    sf::Clock clock;
    sf::Vector2f s(2000, 2000);
    sf::Vector2f s1(1, 2000);
    sf::RectangleShape back(s);
    sf::RectangleShape line(s1);
    line.setPosition(700, 0);
    line.setFillColor(c);
    m.init_window();
    m.getWindow()->setFramerateLimit(30);
    m.getWindow()->setVerticalSyncEnabled(false);
    while (m.getWindow()->isOpen())
    {
        if (clock.getElapsedTime().asSeconds() > 1.0)
        {
            clock.restart();
            m.getModuleManager()->update();
        }
        sf::Event event;
        while (m.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m.getWindow()->close();
        }
        m.getWindow()->clear();
        if (!m.getMouse().isButtonPressed(sf::Mouse::Left))
            m.setIsMousePressed(false);
        m.getWindow()->draw(back);
        m.drawModules();
        m.getWindow()->draw(line);
        m.getWindow()->display();
    }
}

void launch_ncurse()
{
    MonitorNcurse m;
    sf::Clock clock;
    int sstr;
    MENU *my_menu;
    ITEM *cur;
    std::vector<std::vector<IMonitorModule *>> modList = m.getModuleManager()->getModules();
    std::string *choices = new std::string[m.getModuleManager()->getTotalModuleCount()];
    int inc = 0;
    std::vector<IMonitorModule *> modules;
    for (std::vector<IMonitorModule *> v : modList)
        for (IMonitorModule * mod : v) {
            choices[inc] = mod->getName();
            inc++;
            modules.push_back(mod);
        }
    int n_choices = m.getModuleManager()->getTotalModuleCount();
    int i = 0;
    ITEM **my_items = new ITEM*[n_choices + 1];
    for (int i = 0; i < n_choices; ++i)
        my_items[i] = new_item(choices[i].c_str(), "");
    my_items[n_choices] = (ITEM *)nullptr;
    my_menu = new_menu((ITEM **)my_items);
    m.init_window();
    WINDOW *boite = subwin(stdscr, 15, 25, 18, 13);
    m.setWindow(subwin(stdscr, LINES - 10, 40, 5, 5));
    box(m.getWindow(), ACS_VLINE, ACS_HLINE);
    set_menu_win(my_menu, boite);
    printw("Press <ENTER> to hide/show any Module\n");
    printw("Up and Down arrow keys to navigate\n");
    printw("Press <Q> to exit programm\n");
    post_menu(my_menu);
    while (1)
    {
        refresh();
        wrefresh(m.getWindow());
        wrefresh(boite);
        timeout(1);
        sstr = getch();
        if (sstr == 'q' || sstr == 'Q')
        {
            unpost_menu(my_menu);
            for (int i = 0; i < n_choices; ++i)
                free_item(my_items[i]);
            free_menu(my_menu);
            endwin();
            exit(0);
        }
        if (sstr == KEY_DOWN)
        {
            menu_driver(my_menu, REQ_DOWN_ITEM);
            refresh();
        }
        if (sstr == KEY_UP)
        {
            menu_driver(my_menu, REQ_UP_ITEM);
            refresh();
        }
        if (sstr == '\n')
        {
            cur = current_item(my_menu);
            pos_menu_cursor(my_menu);
            for (i = 0; i < 9; i++)
                if (cur == my_items[i])
                    break;
            modules[i]->setDisp(!modules[i]->getDisp());
            clear();
            refresh();
            wrefresh(boite);
            menu_driver(my_menu, REQ_UP_ITEM);
            menu_driver(my_menu, REQ_DOWN_ITEM);
            box(m.getWindow(), ACS_VLINE, ACS_HLINE);
            set_menu_win(my_menu, boite);
            printw("Press <ENTER> to hide/show any Module\n");
            printw("Up and Down arrow keys to navigate\n");
            printw("Press <Q> to exit programm\n");
            post_menu(my_menu);
            m.drawModules();
        }
        if (clock.getElapsedTime().asSeconds() > 1.0)
        {
            clock.restart();
            m.getModuleManager()->update();
        }
        m.drawModules();
    }
}
void launch_prog(int ac, char **av)
{
    if (ac < 2 || strcmp(av[1], "-h") == 0)
    {
        std::cout << "Invalid arguments : Missing mode :" << std::endl;
        std::cout << "-n for Ncurses mode" << std::endl;
        std::cout << "-s for SFML mode" << std::endl;
        exit(0);
    }
    if (std::string(av[1]) == "-n")
    {
        launch_ncurse();
        exit(0);
    }
    if (std::string(av[1]) == "-s")
    {
        launch_sfml();
        exit(0);
    }
}
