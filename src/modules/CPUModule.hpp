/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** CPUModule
*/

#ifndef CPUMODULE_HPP_
#define CPUMODULE_HPP_
#include "IMonitorModule.hpp"
#include "../components/Graph.hpp"
#include <string>

class CPUModule:public IMonitorModule {
	public:
	CPUModule(int ID);
	~CPUModule();
        void update() override;
        void drawSFML(sf::RenderWindow &window, sf::Vector2i &offset) override;
        void drawNcurses(WINDOW *win, int offset[3]) override;
        void setModelName();
        void setNbCore();
        void setFrequency();
        void setCacheSize();
        void setUsage();
        int getID();
        void setDisp(bool);
        bool getDisp();
        int getUsage();
        int getNbCore();
        float getFrequency();
        std::string getModelName();
        std::string getCacheSize();
        void setmaxFreq();
        float getmaxFreq();
	private:
		int set_cpu_value(std::string line);
		int get_CPUStat(int ID);
        std::string _modelName;
        std::string _cacheSize;
        int _ID;
        int _nbCore;
        int _Usage = 0;
        float _Frequency;
		sf::Font *_font = new sf::Font;
		Graph *_graph;
        float _maxFreq;
        bool _isdisplay = true;
        int _old_total_a = 0;
        int _old_total_b = 0;
};

#endif /* !CPUMODULE_HPP_ */
