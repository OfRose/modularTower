#ifndef I2C_MODULAR_DEVICE_MANAGER
#define I2C_MODULAR_DEVICE_MANAGER
/*
    libreria rduino per comunicazione I2C
*/
#include <Wire.h>
/*
    importo classe che modellerà i dispositivi e hasmap per salvarli come coppia chiave valore indirizzo-puntatore a oggetto device
*/
#include <I2C_ModularDevice.h>
#include <unordered_map>

/*
    Wire library uses 7-bit addressing for a total of 128 addresses from 0x00 to 0x7F
    the usable and not reserved range is between 0x08 and 0x77 -> 112 usable addresses
*/

#define USABLE_ADDRESSES_RANGE_LOW 0x08
#define USABLE_ADDRESSES_RANGE_HIGH 0x77
#define TOTAL_AVAILABLE_ADDRESSES USABLE_ADDRESSES_RANGE_HIGH - USABLE_ADDRESSES_RANGE_LOW + 1

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

#define MAX_BYTE_TO_REPRESENT_MAP_LEN 4

/*
Stati possibili device per popolare il vettore di stato definito all'interno della classe I2C_ModularDevicesManager
*/

enum device_statuses
{
    NOT_FOUND,                // 0
    DISCOVERED_TO_INITIALISE, // 1
    INSTALLED,                // 2
    ERROR,
};

class I2C_ModularDevicesManager
{
public:
    I2C_ModularDevicesManager(); // Constructor

    int scan_I2C_bus();       //restituisce numero device DISCOVERED_TO_INITIALISE trovati
    void init_new_devices();  // inizializza devices (instanziamento classe, lettura mappa comandi, aggiornamento stato ecc)
    /*
        Sample Usage:
        if(deviceManager.scan_I2C_bus() > 0){
            deviceManager.init_new_devices();
        }
    */

    // Restituisce lo stato salvato nel vettore device_status_array
    int device_status_by_address(uint8_t address);

    // restituisce puntamento all'istanza della classe device per l'indirizzo selezionato
    I2C_ModularDevice *getDevice(uint8_t address);

private:
    /*
    Questo vettore permette un accesso diretto in base all'indirizzo del dispositivo di cui viene rappresentato lo stato.
    Inizializzo a Sìstato NOT_FOUND.
    */
    int device_status_array[TOTAL_AVAILABLE_ADDRESSES] = {NOT_FOUND};

    // hasmap for storing pointers to instances of class modularDevice
    std::unordered_map<uint8_t, I2C_ModularDevice *> devices;
};

#endif /*I2C_MODULAR_DEVICE_MANAGER*/