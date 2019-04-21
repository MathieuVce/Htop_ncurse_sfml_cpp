/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** OSModule
*/

#ifndef OSMODULE_HPP_
#define OSMODULE_HPP_
#include <string>
#include "IMonitorModule.hpp"
class OSModule : public IMonitorModule
{
    public:
        OSModule();
        ~OSModule();
        bool getDisp();
        void setDisp(bool);
        void setOSName();
        std::string getOSName();
        std::string getKernelVers();
        void update() override;
        void drawSFML(sf::RenderWindow &window, sf::Vector2i &offset) override;
        void drawNcurses(WINDOW *win, int offset[3]) override;

      private:
        std::string _OSName;
        std::string _KernelVers;
        sf::Font *_font = new sf::Font;
        bool _isdisplay = true;
};

#endif /* !OSMODULE_HPP_ */
