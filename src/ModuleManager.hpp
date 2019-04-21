/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** ModuleManager.hpp
*/
#ifndef MODULEMANAGER_HPP_
# define MODULEMANAGER_HPP_

#include "modules/IMonitorModule.hpp"
#include <vector>
#include <def.hpp>

class ModuleManager {
public:
    ModuleManager();
    uint getColumnCount() const;
    uint getTotalModuleCount() const;
    uint getColumnModuleCount(uint colId) const;
    uint loadModule(uint colId, IMonitorModule *);
    void unloadModule(uint id);
    void update();
    uint getMaxColumns() const;
    uint getMaxColumnHeight() const;
    void activate(uint id);
    std::vector<std::vector<IMonitorModule *>> getModules();
private:
    std::vector<std::vector<IMonitorModule *>> _modules = {{}, {}};
    std::vector<IMonitorModule *> _availableModules = {};
    const uint _maxColumn = 5;

};


#endif //MODULEMANAGER_HPP_
