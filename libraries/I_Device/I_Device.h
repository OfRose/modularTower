#ifndef I_DEVICE_H
#define I_DEVICE_H

#include <string>

class I_Device
{
public:
    // virtual std::string get_status() = 0;
    virtual std::string get_info_string() = 0;
    // virtual void load_info_from_board() = 0;
};

#endif /*I_DEVICE_H*/