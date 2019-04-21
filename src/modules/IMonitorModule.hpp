/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** IMonitorModule.hpp
*/

#ifndef IMONITORMODULE_HPP_
# define IMONITORMODULE_HPP_

#include <string>
#include <def.hpp>
#include <SFML/System.hpp>
#include <ncurses.h>
#include <SFML/Graphics.hpp>

class IMonitorModule {
public:
    explicit IMonitorModule(std::string name, uint sfmlHeight, uint ncursesHeight, bool disp): _id(getNewId()), _name(name),
    _heightSFML(sfmlHeight), _heightNcurses(ncursesHeight), _isdisplay(disp) {};
    virtual ~IMonitorModule() = default;
    uint getId() const
    {
        return _id;
    };
    std::string getName() const
    {
        return _name;
    };
    virtual void update() = 0;
    virtual void drawSFML(sf::RenderWindow &window, sf::Vector2i &offset) = 0;
    virtual void drawNcurses(WINDOW *win, int offset[3]) = 0;
    uint getHeightSFML() const
    {
        return _heightSFML;
    }
    uint getHeightNcurses() const
    {
        return _heightNcurses;
    }
    bool getDisp() const
    {
        return (this->_isdisplay);
    }
    void setDisp(bool d) {
        _isdisplay = d;
    }
    enum header
    {
        NAME,
        HOSTNAME,
        USERNAME,
        OSNAME,
        KERNEL,
        TIME
    };
  protected:
  private:
    static uint getNewId()
    {
        static uint __i = 0;
        return (__i++);
    }
    const uint _id;
    const std::string _name;
    const uint _heightSFML = 0;
    const uint _heightNcurses = 0;
    bool _isdisplay = false;
};

#endif //IMONITORMODULE_HPP_
