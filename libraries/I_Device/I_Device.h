#ifndef I_DEVICE_H
#define I_DEVICE_H

#include <string>

class I_Device
{
public:
    virtual bool is_equal(I_Device other) = 0;
    virtual bool merge_with(I_Device other) = 0;
};

#endif /*I_DEVICE_H*/