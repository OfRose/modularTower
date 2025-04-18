#ifndef I_DEVICE_STATUS_H
#define I_DEVICE_STATUS_H

#include <string>

class I_DeviceStatus
{
public:
    virtual std::string toString() = 0;
};

#endif /*I_DEVICE_STATUS_H*/