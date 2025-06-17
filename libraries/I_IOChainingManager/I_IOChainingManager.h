#ifndef I_IO_CHAINING_MANAGER_H
#define I_IO_CHAINING_MANAGER_H

class I_IOChainingManager
{
    public:
    virtual void add_configuration() = 0;
    virtual void run_configuration() = 0;
};

#endif /*I_IO_CHAINING_MANAGER_H*/