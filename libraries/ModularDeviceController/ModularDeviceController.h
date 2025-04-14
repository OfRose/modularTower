#include <I_BusManager.h>
#include <I_IOChainingManager.h>
#include <I_DeviceStatus.h>
#include <string>

class ModularDeviceController
{
public:
    ModularDeviceController(I_BusManager *bus_manager, I_IOChainingManager *IO_chaining_manager);
    void main_loop();
    String device_status_string();

private:
    I_BusManager *bus_manager;
    I_IOChainingManager *IO_chaining_manager;
}