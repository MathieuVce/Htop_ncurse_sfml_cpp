/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** NamesModule
*/

#ifndef NAMESMODULE_HPP_
#define NAMESMODULE_HPP_
#include "IMonitorModule.hpp"

class NamesModule:public IMonitorModule {
	public:
		NamesModule();
		~NamesModule();
        void setHostName();
        void setUserName();
        std::string getHostName();
        std::string getUserName();
        bool getDisp();
        void setDisp(bool);
        void update() override;
        void drawSFML(sf::RenderWindow &window, sf::Vector2i &offset) override;
        void drawNcurses(WINDOW *win, int offset[2]) override;
      private:
        std::string _HostName;
        std::string _UserName;
        sf::Font *_font = new sf::Font;
        bool _isdisplay = false;
};

#endif /* !NAMESMODULE_HPP_ */
