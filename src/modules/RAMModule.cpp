/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** RAMModule
*/

#include "RAMModule.hpp"
#include <sys/sysinfo.h>

RAMModule::RAMModule() : IMonitorModule("RAM Informations", 200, 10, true)
{
    this->setBufferRam();
    this->setFreeRam();
    this->setProcs();
    this->setSharedRam();
    this->setTotalRam();
    this->setUptime();
    this->_font->loadFromFile("ressources/UbuntuMono.ttf");
    _graph = new Graph("Used memory", 40, static_cast<uint>(this->getTotalRam()), 100, 1);
}

void RAMModule::setUptime()
{
    struct sysinfo *info = new struct sysinfo;
    sysinfo(info);
    this->_Uptime = info->uptime;
}

void RAMModule::setTotalRam()
{
    struct sysinfo *info = new struct sysinfo;
    sysinfo(info);
    this->_TotalRam = info->totalram;

}

void RAMModule::setFreeRam()
{
    struct sysinfo *info = new struct sysinfo;
    sysinfo(info);
    this->_FreeRam = info->freeram;
}

void RAMModule::setSharedRam()
{
    struct sysinfo *info = new struct sysinfo;
    sysinfo(info);
    this->_SharedRam = info->sharedram;
}

void RAMModule::setBufferRam()
{
    struct sysinfo *info = new struct sysinfo;
    sysinfo(info);
    this->_BufferRam = info->bufferram;
}

void RAMModule::setProcs()
{
    struct sysinfo *info = new struct sysinfo;
    sysinfo(info);
    this->_Procs = info->procs;
}

long RAMModule::getUptime()
{
    return this->_Uptime;
}

unsigned long RAMModule::getTotalRam()
{
    return this->_TotalRam;
}

unsigned long RAMModule::getFreeRam()
{
    return this->_FreeRam;
}

unsigned long RAMModule::getSharedRam()
{
    return this->_SharedRam;
}

unsigned long RAMModule::getBufferRam()
{
    return this->_BufferRam;
}

unsigned short RAMModule::getProcs()
{
    return this->_Procs;
}

bool RAMModule::getDisp(void)
{
    return(this->_isdisplay);
}

void RAMModule::setDisp(bool b)
{
    this->_isdisplay = b;
}

void RAMModule::update()
{
    this->setBufferRam();
    this->setFreeRam();
    this->setProcs();
    this->setSharedRam();
    this->setTotalRam();
    this->setUptime();
    _graph->push_data(static_cast<uint>(_TotalRam - _FreeRam));
}

std::string ConvertSectoDay(int n)
{
    std::string *m = new std::string;
    int day = n / (24 * 3600);
    n = n % (24 * 3600);
    int hour = n / 3600;
    n %= 3600;
    int minutes = n / 60;
    n %= 60;
    int seconds = n;

    *m = std::to_string(day) + "d " + std::to_string(hour) + "h " + std::to_string(minutes) + "m " + std::to_string(seconds) + "s";
    return (*m);
}

void RAMModule::drawSFML(sf::RenderWindow &window, sf::Vector2i &offset)
{
    float h = getHeightSFML();
    float x = 400;
    sf::Vector2f size(x, h);
    uint fontSize = 20;
    sf::RectangleShape back(size);
    back.setPosition(offset.x, offset.y);
    back.setOutlineColor(sf::Color::Black);
    back.setFillColor(sf::Color::White);
    window.draw(back);

    sf::Text t(this->getName(), *_font);
    t.setCharacterSize(fontSize);
    t.setPosition(200 - t.getLocalBounds().width / 2 + offset.x, offset.y + 5);
    //t.setFillColor(sf::Color::Black);
    t.setColor(sf::Color::Black);
    window.draw(t);
    t.setPosition(offset.x + 5, offset.y + 5 + fontSize);
    t.setString("Uptime since boot: " + ConvertSectoDay((int)_Uptime));
    window.draw(t);
    t.move(0, fontSize);
    t.setString("Total RAM: " + std::to_string(_TotalRam));
    window.draw(t);
    t.move(0, fontSize);
    t.setString("Shared RAM: " + std::to_string(_SharedRam));
    window.draw(t);
    t.move(0, fontSize);
    t.setString("Free RAM: " + std::to_string(_FreeRam));
    window.draw(t);
    t.move(0, fontSize);
    t.setString("Used RAM: " + std::to_string(_TotalRam - _FreeRam));
    window.draw(t);
    t.move(0, fontSize);
    t.setString("Buffer RAM: " + std::to_string(_BufferRam));
    window.draw(t);
    t.move(0, fontSize);
    t.setString("Number of Processes active: " + std::to_string(_Procs));
    window.draw(t);
    _graph->draw(sf::Vector2i(offset.x, offset.y + fontSize * 4), &window);
}

void RAMModule::drawNcurses(WINDOW *win, int offset[3])
{
    win = subwin(stdscr, offset[1], 45, offset[2], offset[0]);
    wprintw(win, "\n  ");
    wattron(win, A_BOLD | A_STANDOUT | COLOR_PAIR(3));
    wprintw(win, this->getName().c_str());
    wattroff(win, A_BOLD | A_STANDOUT);
    wprintw(win, "\n  ");
    wprintw(win, "Time since Boot: ");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(this->_Uptime).c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Total RAM: ");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(this->_TotalRam).c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Free RAM: ");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(this->_FreeRam).c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Shared RAM: ");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(this->_SharedRam).c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Buffer RAM: ");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(this->_BufferRam).c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Number of Process: ");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(this->_Procs).c_str());
    wattroff(win, A_DIM);
    wborder(win, '|', '|', '-', '-', '/', '\\', '\\', '/');
    wattroff(win, COLOR_PAIR(3));
    wrefresh(win);
}

RAMModule::~RAMModule()
{
}
