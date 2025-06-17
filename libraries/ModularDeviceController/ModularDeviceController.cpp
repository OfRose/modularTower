#include <ModularDeviceController.h>

#include <algorithm>

void ModularDeviceController::add_bus_manager(I_BusManager *new_bus_manager)
{
    this->bus_manager_list.push_back(new_bus_manager);
}

void ModularDeviceController::add_IO_chaining_manager(I_BusManager *new_IO_chaining_manager)
{
    this->IO_chaining_manager_list.push_back(new_IO_chaining_manager);
}

void ModularDeviceController::main_loop()
{
    for (I_BusManager *bm : this->bus_manager_list)
    {
        ModularDeviceController::merge_device_lists(this->device_list, bm->scan_bus());
    }
}

void ModularDeviceController::merge_device_lists(std::list<I_Device *> &destination_list, std::list<I_Device *> &source_list)
{
    auto it = source_list.begin();
    while (it != source_list.end())
    {
        I_Device *sd = *it;
        auto found = std::find_if(destination_list.begin(), destination_list.end(), [sd](I_Device *dd)
                                  { return dd->is_equal(sd); });
        if (found == destination_list.end())
        {
            destination_list.push_back(sd);
        }
        else
        {
          (*found)->merge_with(sd);
            delete sd;
        }
        it = source_list.erase(it); // erase restituisce il prossimo iteratore
    }
}
