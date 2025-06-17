#include <ModularDeviceController.h>

ModularDeviceController::ModularDeviceController(I_BusManager *bus_manager, I_IOChainingManager *IO_chaining_manager)
{
    this->bus_manager = bus_manager;
    this->IO_chaining_manager = IO_chaining_manager;
}

/* void ModularDeviceController::main_loop()
{
    this->bus_manager->scan_bus();
    for device in bus_manager.devices_input_ready()
        if IO_chaining_manager->check_for_configuration(device.input)
            IO_chaining_manager->triggerconfig(device.input)
}
 */