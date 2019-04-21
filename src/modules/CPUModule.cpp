/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** CPUModule
*/

#include "CPUModule.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>

CPUModule::CPUModule(int ID) : IMonitorModule("CPU Informations", 130, 10, true), _graph(new  Graph("Frequency", 30, 1500, 60, 2))
{
    this->_Usage = 0;
    this->_ID = ID;
    this->_isdisplay = true;
    this->setModelName();
    this->setNbCore();
    this->setFrequency();
    this->setCacheSize();
    this->setUsage();
    this->setmaxFreq();
    this->_font->loadFromFile("ressources/UbuntuMono.ttf");
}

CPUModule::~CPUModule()
{
}

std::string read_cpu_data(const std::string &name, int size, const std::string &path, int ID)
{
    std::filebuf fb;
    std::string procID = "processor	: ";

    procID.append(std::to_string(ID));
    if (ID == 4)
        procID = "processor	: 0";
    if (fb.open(path, std::ios::in))
    {
        std::string line;
        std::istream is(&fb);
        while (std::getline(is, line)) {
            if (line.find(procID, 0) == 0) {
                while (std::getline(is, line)) {
                    if (line.find(name, 0) == 0) {
                        return line.substr(size, line.size());
                    }
                }
            }
        }
    }
    return nullptr;
}

int CPUModule::getID()
{
    return this->_ID;
}

void CPUModule::setModelName()
{
    this->_modelName = read_cpu_data("model name", 13, "/proc/cpuinfo", this->_ID);
}

void CPUModule::setNbCore()
{
    std::string tmp = read_cpu_data("siblings", 11, "/proc/cpuinfo", this->_ID);
    this->_nbCore = std::stoi(tmp);
}

void CPUModule::setFrequency()
{
    std::string tmp = read_cpu_data("cpu MHz", 10, "/proc/cpuinfo", this->_ID);
    this->_Frequency = std::stof(tmp);
    _graph->push_data(static_cast<uint>(this->_Frequency));
}

void CPUModule::setCacheSize()
{
    this->_cacheSize = read_cpu_data("cache size", 13, "/proc/cpuinfo", this->_ID);

}

int CPUModule::set_cpu_value(std::string line)
{
    std::string s;
    std::istringstream f(line);
    int *values = new int[12];
    int check = 0;
    int total_a = 0;
    int total_b = 0;
    int cpu = 0;

    for (int i = 0; i < 12; i++)
        values[i] = 0;
    for (int i = 0; getline(f, s, ' '); i++) {
        if (s == " " || s.c_str() == NULL || s.empty())
            continue;
        for (int n = 0; s[n]; n++) {
            if (std::isdigit(s[n]))
                check += 1;
        }
        if (check == (int)s.size()) {
            values[i] = std::stoi(s);
        }
        check = 0;
    }
    for (int i = 0; i < 10; i++)
        total_a += values[i];
    total_b = values[0] + values[1] + values[2];
        cpu = static_cast<int>((float)(total_b - _old_total_b) / (float)(total_a - _old_total_a) * 100);
    _old_total_a = total_a;
    _old_total_b = total_b;
    return (cpu);
}

int CPUModule::get_CPUStat(int ID)
{
    std::ifstream fb("/proc/stat");
    std::string cpuName = "cpu";

    cpuName.append(std::to_string(ID));
    if (ID == 4)
        cpuName = "cpu";
    if (fb.is_open())
    {
        std::string line;
        while (std::getline(fb, line)) {
            if (line.find(cpuName, 0) == 0) {
                fb.close();
                return set_cpu_value(line);
            }
        }
    }
    fb.close();
    return 0;
}

void CPUModule::setDisp(bool b)
{
    this->_isdisplay = b;
}

bool CPUModule::getDisp()
{
    return (this->_isdisplay);
}

void CPUModule::setUsage()
{
    this->_Usage = get_CPUStat(this->_ID);
}

std::string CPUModule::getModelName()
{
    return this->_modelName;
}

int CPUModule::getNbCore()
{
    return this->_nbCore;
}

float CPUModule::getFrequency()
{
    return this->_Frequency;
}

int CPUModule::getUsage()
{
    return this->_Usage;
}


std::string CPUModule::getCacheSize()
{
    return this->_cacheSize;
}

void CPUModule::update()
{
    this->setModelName();
    this->setNbCore();
    this->setFrequency();
    this->setCacheSize();
    this->setUsage();
}

void CPUModule::drawSFML(sf::RenderWindow &window, sf::Vector2i &offset)
{
    static sf::Text text("", *_font);
    static sf::Vector2f size(400, getHeightSFML());
    static sf::RectangleShape back(size);
    static int fontSize = 17;

    back.setPosition(offset.x, offset.y);
    window.draw(back);
    text.setCharacterSize(fontSize + 3);
    text.setString(((_ID != 4) ? this->getName() : "All CPUs") + " (" + std::to_string(_ID) + ")");
    text.setPosition(offset.x + 200 - text.getLocalBounds().width / 2, offset.y);
    //text.setFillColor(sf::Color::Black);
    text.setColor(sf::Color::Black);
    window.draw(text);
    text.setCharacterSize(fontSize);
    text.setString("Model Name:");
    float labelWidth = text.getLocalBounds().width;
    text.setPosition(offset.x + 5, offset.y + 5 + fontSize);
    window.draw(text);
    text.setString(" " + _modelName);
    text.move(labelWidth, 4);
    text.setCharacterSize(fontSize - 4);
    window.draw(text);
    text.setPosition(offset.x + 5, offset.y + 5 + 2 * fontSize);
    text.setString("Number of cores: " + std::to_string(_nbCore));
    text.setCharacterSize(fontSize);
    window.draw(text);
    text.move(0, fontSize);
    text.setString("ID: " + std::to_string(_ID));
    window.draw(text);
    text.move(0, fontSize);
    text.setString("Cache size: " + _cacheSize);
    window.draw(text);
    text.move(0, fontSize);
    text.setString("Frequency: " + std::to_string(_Frequency) + " MHz");
    window.draw(text);
    text.move(0, fontSize);
    text.setString("Usage: " + std::to_string(_Usage) + "%");
    window.draw(text);
    _graph->draw(sf::Vector2i(offset.x, offset.y + fontSize * 5), &window);
}

void CPUModule::setmaxFreq()
{
    this->_maxFreq = 3500;
}

float CPUModule::getmaxFreq()
{
    return this->_maxFreq;
}

void CPUModule::drawNcurses(WINDOW *win, int offset[3])
{
    int it = 0;
    int res = 0;

    win = subwin(stdscr, offset[1], 45, offset[2], offset[0]);
    wprintw(win, "\n  ");
    wattron(win, A_BOLD | A_STANDOUT | COLOR_PAIR(3));
    wprintw(win, this->getName().c_str());
    wattroff(win, A_BOLD | A_STANDOUT);
    wprintw(win, "\n  ");
    wprintw(win, "Model Name: ");
    wattron(win, A_BOLD);
    wprintw(win, this->_modelName.c_str());
    wattroff(win, A_BOLD);
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Number of Core: ");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(this->_nbCore).c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "ID: ");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(this->getID()).c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Cache Size: ");
    wattron(win, A_DIM);
    wprintw(win, this->_cacheSize.c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Frequency: [");
    wattroff(win, COLOR_PAIR(3));
    it = 24 * round(this->_Frequency) / this->_maxFreq;
    res = 24 - it;
    for (int i = 0; i < it; i++) {
        wattron(win, A_DIM | COLOR_PAIR(4));
        wprintw(win, "|");
        wattroff(win, A_DIM | COLOR_PAIR(4));
    }
    for (int i = 0; i < res; i++) {
        wattron(win, A_DIM | COLOR_PAIR(4));
        wprintw(win, " ");
        wattroff(win, A_DIM | COLOR_PAIR(4));
    }
    wattron(win, COLOR_PAIR(3));
    wprintw(win, "]\t%%");
    it = 100 * it / 24;
    wattron(win, A_DIM);
    wprintw(win, std::to_string(it).c_str());
    wattroff(win, A_DIM);
    wprintw(win, "\n  ");
    wprintw(win, "Usage: [");
    wattroff(win, COLOR_PAIR(3));
    it = 24 * round(this->_Usage) / 100;
    res = 24 - it;
    for (int i = 0; i < it; i++)
    {
        wattron(win, A_DIM | COLOR_PAIR(4));
        wprintw(win, "|");
        wattroff(win, A_DIM | COLOR_PAIR(4));
    }
    for (int i = 0; i < res; i++)
    {
        wattron(win, A_DIM | COLOR_PAIR(4));
        wprintw(win, " ");
        wattroff(win, A_DIM | COLOR_PAIR(4));
    }
    wattron(win, COLOR_PAIR(3));
    wprintw(win, "]\t%%");
    wattron(win, A_DIM);
    wprintw(win, std::to_string(round(this->_Usage)).c_str());
    wattroff(win, A_DIM);
    wborder(win, '|', '|', '-', '-', '/', '\\', '\\', '/');
    wattroff(win, COLOR_PAIR(3));
    wrefresh(win);
}
