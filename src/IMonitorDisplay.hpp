/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** IMonitorDisplay.hpp
*/

#ifndef IMONITORDISPLAY_HPP_
# define IMONITORDISPLAY_HPP_

#include "ModuleManager.hpp"

class IMonitorDisplay {
public:
    virtual ~IMonitorDisplay() = default;
    virtual void init_window() = 0;
    ModuleManager *getModuleManager() const
    {
        return _manager;
    }

protected:
    ModuleManager *_manager = new ModuleManager();
};

#endif //IMONITORDISPLAY_HPP_
