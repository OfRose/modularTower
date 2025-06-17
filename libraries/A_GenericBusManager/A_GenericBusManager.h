#ifndef A_GENERIC_BUS_MANAGER
#define A_GENERIC_BUS_MANAGER

#include <I_BusManager.h>
#include <I_Device.h>
#include <map>
#include <functional>

template <typename deviceAddress>
class A_GenericBusManager : public I_BusManager
{

protected:

    class A_GenericDevice : public I_Device
    {
    public:
        A_GenericDevice() { this->status = DISCOVERED; };
        // bool is_discovered() { return this->status == DISCOVERED; };
        device_statuses get_status() { return this->status; };
        void set_status(device_statuses new_status) { this->status = new_status; };
        virtual deviceAddress getID() = 0;
        // TMP

    protected:
        device_statuses status;
    };
    std::map<deviceAddress, A_GenericDevice *> devices;

public:
    int get_devices_num()
    {
        return this->get_devices_num([](A_GenericDevice *d)
                                     { return true; });
    };
    void get_devices(I_Device **devices_return_array)
    {
        return this->get_devices(devices_return_array, [](A_GenericDevice *d)
                                 { return true; });
    };

    int get_devices_num(const std::function<bool(A_GenericDevice *)> &filter)
    {
        int i = 0;
        for (auto const &[key, value] : devices)
        {
            if (filter(value))
            {
                i++;
            }
        }
        return i;
    };
    void get_devices(I_Device **devices_return_array, const std::function<bool(A_GenericDevice *)> &filter)
    {
        int i = 0;
        for (auto const &[key, value] : devices)
        {
            if (filter(value))
            {
                devices_return_array[i++] = (I_Device *)value;
            }
        }
    };

    virtual void scan_bus() = 0;

    static std::string from_device_status_to_string(device_statuses status) { return status_string[status]; };

    int get_input_available_devices_num()
    {
        return this->get_devices_num([](A_GenericDevice *d)
                                     { return d->get_status() == INPUT_AVAILABLE; });
    };
    void get_input_available_devices(I_Device **devices_return_array)
    {
        return this->get_devices(devices_return_array, [](A_GenericDevice *d)
                                 { return d->get_status() == INPUT_AVAILABLE; });
    };
    int get_UNINITIALISED_devices_num()
    {
        return this->get_devices_num([](A_GenericDevice *d)
                                     { return d->get_status() == UNINITIALISED; });
    };
    void get_UNINITIALISED_devices(I_Device **devices_return_array)
    {
        return this->get_devices(devices_return_array, [](A_GenericDevice *d)
                                 { return d->get_status() == UNINITIALISED; });
    };

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
