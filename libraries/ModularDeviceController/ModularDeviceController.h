#ifndef MODULAR_DEVICE_CONTROLLER_H
#define MODULAR_DEVICE_CONTROLLER_H

#include <I_BusManager.h>
#include <I_IOChainingManager.h>
#include <I_Device.h>
#include <string>

class ModularDeviceController
{
public:
    ModularDeviceController(I_BusManager *bus_manager, I_IOChainingManager *IO_chaining_manager);
    I_BusManager *bus_manager;
    I_IOChainingManager *IO_chaining_manager;
    //void main_loop();
};

#endif /*MODULAR_DEVICE_CONTROLLER_H*/