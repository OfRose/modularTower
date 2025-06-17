#ifndef I2C_MODULAR_DEVICE_MANAGER_H
#define I2C_MODULAR_DEVICE_MANAGER_H

#include <A_GenericBusManager.h>
// #include <map>
// #include <string>

/*
    importo classe che modellerà i dispositivi e hasmap per salvarli come coppia chiave valore indirizzo-puntatore a oggetto device
*/
// #include <I2C_Device.h>
/* #include <unordered_map> */

/*
    Wire library uses 7-bit addressing for a total of 128 addresses from 0x00 to 0x7F
    the usable and not reserved range is between 0x08 and 0x77 -> 112 usable addresses
*/

/*
    L'hub dovrà leggere un numero di byte che rappresenta quanto è lunga la mappa comandi-operazioni dei device attraverso una RequestFrom,
    il numero di byte da leggere nella request from è inevitabilmente legato al massimo numero di byte che la mappa può avere.

    ES:
    Se la massima lunghezza mappa desiderata è di 1024 byte ne segue che, essendo il numero 1024 rappresentabile su 10bit
    -> la requestFrom si dovrà aspettare 2byte (arrotondo per eccesso) che possono contenere il numero 1024

    Prova iniziale con 4 byte massimi per rappresentazione lunghezza mappa -> lunghezza massima mappa 2^32-1  (tantissimo zio, tipo.. un botto fidati)
    --> salverò questo valore su un uint32_t

    I device sanno che al byte di comando 0x00 devono rispondere con la loro lista di comandi-operazioni
    strutturata come da documentazione (unico vincolo del protocollo).
*/

/* #define MAX_BYTE_TO_REPRESENT_MAP_LEN 4
 */
/*
Stati possibili device per popolare il vettore di stato definito all'interno della classe I2C_BusManager
*/

/* enum device_statuses
{
    NOT_FOUND,                // 0
    DISCOVERED_TO_INITIALISE, // 1
    INSTALLED,                // 2
    ERROR,                    // 3
}; */

class I2C_BusManager : public A_GenericBusManager<uint8_t>
{
private:
    class I2C_Device : public A_GenericBusManager<uint8_t>::A_GenericDevice
    {
    public:
        I2C_Device(uint8_t address)
        {
            this->address = address;
        };
        std::string get_info_string()
        {
            return std::to_string(address) + " - " + I2C_BusManager::from_device_status_to_string(this->status);
        };
        uint8_t getID()
        {
            return address;
        };
        /*
            std::string get_status();
            void load_info_from_board(I_BusManager *bus_manager);
            void requestEvent();
            void receiveEvent(); */

        /*
            char *getDeviceInfo();
            void setDeviceInfo(char *data);
            void loadConfig(uint8_t* commands_map_buffer);
            uint32_t commands_map_len;
            uint8_t config_retrieve_command = 0x01;
            uint8_t* config = nullptr;
         */
    private:
        uint8_t address;
        // std::string info = "standard";
    };

    // I2C_Device *I2C_device_array[TOTAL_AVAILABLE_ADDRESSES] = {nullptr};
    /*
    Questo vettore permette un accesso diretto in base all'indirizzo del dispositivo di cui viene rappresentato lo stato.
    Inizializzo a stato NOT_FOUND.
    */
    // int device_status_array[TOTAL_AVAILABLE_ADDRESSES] = {NOT_FOUND};

    // hasmap for storing pointers to instances of class modularDevice
    // std::unordered_map<uint8_t, I2C_Device *> devices;
public:
    I2C_BusManager(); // Constructor
    void scan_bus();
    device_statuses retrieve_status_from_hardware_device(uint8_t address);
    // int scan_I2C_bus();      // restituisce numero device DISCOVERED_TO_INITIALISE trovati

    // void init_new_devices(); // inizializza devices (instanziamento classe, lettura mappa comandi, aggiornamento stato ecc)
    /*
        Sample Usage:
        if(deviceManager.scan_I2C_bus() > 0){
            deviceManager.init_new_devices();
        }
    */
    // Restituisce lo stato salvato nel vettore device_status_array
    // int device_status_by_address(uint8_t address);

    // restituisce puntamento all'istanza della classe device per l'indirizzo selezionato
    // I2C_Device *getDevice(uint8_t address);

    // std::string get_devices_status_string();
    // std::string get_device_info_string(uint8_t device_id);
};

#endif /*I2C_MODULAR_DEVICE_MANAGER_H*/