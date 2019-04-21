/*
** EPITECH PROJECT, 2019
** cpp_rush3_2018
** File description:
** ModuleManager.cpp
*/
#include <stdexcept>
#include <iostream>
#include "ModuleManager.hpp"
#include "modules/DateModule.hpp"
#include "modules/NamesModule.hpp"
#include "modules/OSModule.hpp"
#include "modules/CPUModule.hpp"
#include "modules/RAMModule.hpp"

ModuleManager::ModuleManager()
{
    this->loadModule(0, new NamesModule);
    this->loadModule(0, new OSModule);
    this->loadModule(0, new DateModule);
    this->loadModule(0, new CPUModule(4));
    this->loadModule(1, new CPUModule(0));
    this->loadModule(1, new CPUModule(1));
    this->loadModule(1, new CPUModule(2));
    this->loadModule(1, new CPUModule(3));
    this->loadModule(0, new RAMModule);
}

uint ModuleManager::getColumnCount() const
{
    return (uint)this->_modules.size();
}

uint ModuleManager::getColumnModuleCount(uint colId) const
{
    if (this->getColumnCount() < colId)
        throw std::out_of_range("colId out of range");
    return (uint)this->_modules[colId].size();
}

uint ModuleManager::getTotalModuleCount() const
{
    uint nb = 0;

    for (std::vector<IMonitorModule *> v : _modules)
        nb += v.size();
    return nb;
}

uint ModuleManager::loadModule(uint colId, IMonitorModule *module)
{
    if (colId > 2) {
        throw std::out_of_range("Out of range");
    }
    this->_modules[colId].push_back(module);
    return module->getId();
}

void ModuleManager::update()
{
    for (std::vector<IMonitorModule *> &v : _modules)
        for (IMonitorModule *module : v) {
            module->update();
            //TODO add draw SFML/NCURSES
        }
}

uint ModuleManager::getMaxColumns() const
{
    return this->_maxColumn;
}

std::vector<std::vector<IMonitorModule *>> ModuleManager::getModules()
{
    return (_modules);
}

uint ModuleManager::getMaxColumnHeight() const
{
    uint max = 0;
    for (std::vector<IMonitorModule *> v : _modules) {
        uint colHeight = 0;
        for (IMonitorModule *module : v) {
            if (module->getDisp())
                colHeight += module->getHeightSFML();
        }
        max = (colHeight > max) ? colHeight : max;
    }
    return max;
}

void ModuleManager::unloadModule(uint id)
{
    for (std::vector<IMonitorModule *> v : _modules) {
        for (uint i = 0; i < v.size(); i++) {
            IMonitorModule *module = v[i];
            std::cout << v.size() << std::endl;
            if (module->getId() == id) {
                v.erase(v.begin() + i);
                _availableModules.push_back(module);
            }
        }
    }

}

void ModuleManager::activate(uint id)
{
    for (uint i = 0; i < _availableModules.size(); i++) {
        IMonitorModule *mod = _availableModules[i];
        if (mod->getId() == id) {
            _availableModules.erase(_availableModules.begin() + i);
            this->loadModule(0, mod);
        }
    }
}
