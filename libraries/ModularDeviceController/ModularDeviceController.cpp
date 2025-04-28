#include <ModularDeviceController.h>

ModularDeviceController::ModularDeviceController(I_BusManager *bus_manager, I_IOChainingManager *IO_chaining_manager)
{
    this->bus_manager = bus_manager;
    this->IO_chaining_manager = IO_chaining_manager;
}