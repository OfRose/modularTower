#ifndef I_BUS_MANAGER_H
#define I_BUS_MANAGER_H

#include <I_Device.h>
#include <map>

class I_BusManager
{
public:
    virtual int get_devices_num() = 0;
    virtual void get_devices(I_Device **devices_return_array) = 0;

    virtual void scan_bus() = 0;
    //virtual int get_discovered_devices_num() = 0;
    //virtual void get_discovered_devices(I_Device **devices_return_array) = 0;

    // virtual void add_device(I_Device *device) = 0;
    // virtual void remove_device(I_Device *device) = 0;
    //  virtual std::string get_devices_status_string() = 0;
    //  virtual std::string get_device_info_string(uint8_t device_id) = 0;
    //  virtual void remove_device(I_Device *) = 0;
    //  virtual I_DeviceIOCapability *get_device_IO_capabilities(I_Device *) = 0;
};

#endif /*I_BUS_MANAGER_H*/