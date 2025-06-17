#ifndef I_BUS_MANAGER_H
#define I_BUS_MANAGER_H

#include <I_Device.h>

class I_BusManager
{
public:
    enum device_statuses
    {
        NONE,
        DISCOVERED,
        UNINITIALISED,
        INITIALISED,
        INPUT_AVAILABLE,
        DISCONNECTED,
        ERROR,
        ANY
    };

    static inline std::string device_statuses_string[] = {"NONE", "DISCOVERED", "UNINITIALISED", "INITIALISED", "INPUT_AVAILABLE", "DISCONNECTED", "ERROR", "ANY"};
    static std::string from_device_status_to_string(device_statuses status) { return device_statuses_string[status]; };

    virtual void update_devices_list() = 0;

    virtual int get_devices_num(device_statuses status_to_filter_by = ANY) = 0;
    virtual void get_devices(I_Device **devices_return_array, device_statuses status_to_filter_by = ANY) = 0;

    virtual static device_statuses get_status(I_Device* device) = 0;
};

#endif /*I_BUS_MANAGER_H*/