#ifndef MODULAR_DEVICE_CONTROLLER_H
#define MODULAR_DEVICE_CONTROLLER_H

#include <list>

#include <I_BusManager.h>
#include <I_IOChainingManager.h>
#include <I_Device.h>

class ModularDeviceController
{
    void add_bus_manager(I_BusManager *);
    void add_IO_chaining_manager(I_BusManager *);
    void main_loop();

private:
    std::list<I_BusManager *> bus_manager_list;
    std::list<I_IOChainingManager *> IO_chaining_manager_list;
    std::list<I_Device *> device_list;

    static void merge_device_lists(std::list<I_Device *> &destination_list, std::list<I_Device *> &source_list);
};

#endif /*MODULAR_DEVICE_CONTROLLER_H*/