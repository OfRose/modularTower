#include "ModularDeviceController.h"

ModularDeviceController::ModularDeviceController(I_BusManager *bus_manager, I_IOChainingManager *IO_chaining_manager)
{
    bus_manager = bus_manager;
    IO_chaining_manager = IO_chaining_manager;
}

void ModularDeviceController::main_loop()
{
    int devices_num;
    I_Device *newly_discovered_devices = bus_manager->scan_bus_for_new_devices(&devices_num);
    for (int i = 0; i < device_num; i++)
    {
        bus_manager->init_new_device(newly_discovered_devices[i]);
    }
}

String ModularDeviceController::device_status_string()
{
    int devices_num;
    I_Device *all_devices = bus_manager->get_all_devices(&devices_num);

    string all_statuses = "";

    for (int i = 0; i < device_num; i++)
    {
        all_statuses = all_statuses + bus_manager->get_device_status(all_devices[i]).toString();
    }
    return all_statuses;
}
