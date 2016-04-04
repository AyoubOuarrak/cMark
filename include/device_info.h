#ifndef DEVICE_INFO_GUARD_H
#define DEVICE_INFO_GUARD_H
#include "db/db_manager.h"

/**
*   Abstract class that contain method to get device info
*/
class DeviceInfo {
protected:
    DBManager* db;

public:
    /** default constructor */
    DeviceInfo();

    /** constructor that get a db manager */
    explicit DeviceInfo(DBManager*);

    /** default distructor */
    ~DeviceInfo();

    /** get physical memory info */
    virtual void physicalMemory() = 0;

    /** in future, add other methods */
    /*
    virtual void cpuInfo() = 0;
    virtual void diskInfo() = 0;
    .....
    */

};

#endif