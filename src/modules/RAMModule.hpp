/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** RAMModule
*/

#ifndef RAMMODULE_HPP_
#define RAMMODULE_HPP_
#include "IMonitorModule.hpp"
#include "../components/Graph.hpp"

class RAMModule : public IMonitorModule
{
    public:
        RAMModule();
        ~RAMModule();
        void update() override;
        void drawSFML(sf::RenderWindow &window, sf::Vector2i &offset) override;
        void drawNcurses(WINDOW *win, int offset[3]) override;
        void setUptime();
        void setTotalRam();
        void setFreeRam();
        void setSharedRam();
        void setBufferRam();
        void setProcs();
        long getUptime();
        unsigned long getTotalRam();
        unsigned long getFreeRam();
        unsigned long getSharedRam();
        unsigned long getBufferRam();
        unsigned short getProcs();
        bool getDisp();
        void setDisp(bool);
      private:
        long _Uptime;
        unsigned long _TotalRam;
        unsigned long _FreeRam;
        unsigned long _SharedRam;
        unsigned long _BufferRam;
        unsigned short _Procs;
        sf::Font *_font = new sf::Font;
        bool _isdisplay = true;
		Graph *_graph;
};

#endif /* !RAMMODULE_HPP_ */
