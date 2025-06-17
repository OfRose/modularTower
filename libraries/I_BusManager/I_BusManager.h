#ifndef I_BUS_MANAGER_H
#define I_BUS_MANAGER_H

#include <list>
#include <I_Device.h>

class I_BusManager
{
public:
    virtual std::list<I_Device *> scan_bus() = 0;
};

#endif /*I_BUS_MANAGER_H*/