/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** monitor_ncurse
*/

#ifndef MONITOR_NCURSE
    #define MONITOR_NCURSE

#include "../IMonitorDisplay.hpp"
#include <ncurses.h>
#include <menu.h>

class MonitorNcurse : public IMonitorDisplay {
    public:
        MonitorNcurse();
        void init_window() override;
        void drawModules();
        WINDOW *getWindow();
        void setWindow(WINDOW *win);
        private:
        WINDOW *_win;
};

#endif /* !MONITOR_NCURSE */
