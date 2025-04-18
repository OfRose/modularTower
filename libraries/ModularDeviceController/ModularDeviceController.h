#ifndef MODULAR_DEVICE_CONTROLLER_H
#define MODULAR_DEVICE_CONTROLLER_H

#include <I_BusManager.h>
#include <I_IOChainingManager.h>
#include <string>

class ModularDeviceController
{
public:
    ModularDeviceController(I_BusManager *bus_manager, I_IOChainingManager *IO_chaining_manager);
    void main_loop();
    std::string get_device_status_string();

private:
    I_BusManager *bus_manager;
    I_IOChainingManager *IO_chaining_manager;
};

#endif /*MODULAR_DEVICE_CONTROLLER_H*/