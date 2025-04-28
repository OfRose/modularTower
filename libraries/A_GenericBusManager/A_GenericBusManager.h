#ifndef A_GENERIC_BUS_MANAGER
#define A_GENERIC_BUS_MANAGER

#include <I_BusManager.h>
#include <I_Device.h>
#include <map>

template <typename deviceAddress>
class A_GenericBusManager : public I_BusManager
{

protected:
    enum device_statuses
    {
        NONE,
        DISCOVERED,
        UNINITIALISED,
        INITIALISED,
        DISCONNECTED,
        ERROR,
    };

    class A_GenericDevice : public I_Device
    {
    public:
        A_GenericDevice() { this->status = DISCOVERED; };
        //bool is_discovered() { return this->status == DISCOVERED; };
        void set_status(device_statuses new_status) { this->status = new_status; };
        virtual deviceAddress getID() = 0;
        // TMP

    protected:
        device_statuses status;
    };
    std::map<deviceAddress, A_GenericDevice *> devices;

public:
    int get_devices_num() { return devices.size(); };
    void get_devices(I_Device **devices_return_array)
    {
        int i = 0;
        for (auto const &[key, value] : devices)
        {
            devices_return_array[i++] = (I_Device *)value;
        }
    };

    virtual void scan_bus() = 0;

   /*  int get_discovered_devices_num()
    {
        int i = 0;
        for (auto const &[key, value] : this->devices)
        {
            if (value->is_discovered())
            {
                i++;
            }
        }
        return i;
    };
    void get_discovered_devices(I_Device **devices_return_array)
    {
        int i = 0;
        for (auto const &[key, value] : this->devices)
        {
            if (value->is_discovered())
            {
                devices_return_array[i++] = (I_Device *)value;
            }
        }
    }; */
    // void add_device(I_Device *device) { this->devices.insert_or_assign(((A_GenericDevice)device).getID(), device); };
    // void remove_device(I_Device *device) { this->devices.erase(((A_GenericDevice)device)->getID()); };
};

#endif /*A_GENERIC_BUS_MANAGER*/
