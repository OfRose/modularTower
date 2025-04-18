#ifndef I_BUS_MANAGER_H
#define I_BUS_MANAGER_H

#include <I_Device.h>
#include <I_DeviceStatus.h>
#include <I_DeviceIOCapability.h>

class I_BusManager
{
public:
    virtual I_Device *scan_bus_for_new_devices(int *devices_num) = 0;
    virtual void init_new_device(I_Device *) = 0;
    virtual I_Device* get_all_devices(int *devices_num) = 0;
    virtual I_DeviceStatus* get_device_status(I_Device *) = 0;
    //virtual void remove_device(I_Device *) = 0;
    //virtual I_DeviceIOCapability *get_device_IO_capabilities(I_Device *) = 0;
};

#endif /*I_BUS_MANAGER_H*/