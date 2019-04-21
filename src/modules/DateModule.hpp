/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** DateModule
*/

#ifndef DATEMODULE_HPP_
#define DATEMODULE_HPP_
#include "IMonitorModule.hpp"

class DateModule:public IMonitorModule {
	public:
		DateModule();
		~DateModule();
        void setTime();
        bool getDisp();
        void setDisp(bool);
        std::string getTime();
        void update() override;
        void drawSFML(sf::RenderWindow &window, sf::Vector2i &offset) override;
        void drawNcurses(WINDOW *win, int offset[3]) override;
      private:
        sf::Font *_font = new sf::Font;
        std::string _Time;
        bool _isdisplay = true;
};

#endif /* !DATEMODULE_HPP_ */
