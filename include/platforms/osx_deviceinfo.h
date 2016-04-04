#ifndef OSX_DEVICE_INFO_GUARD_H
#define OSX_DEVICE_INFO_GUARD_H
#include "../device_info.h"

/**
*   Get device info for OSX platform
*/
class OSXDeviceInfo : public DeviceInfo {
private:

public:
    /** default constructor */
    OSXDeviceInfo() = default;

    /** default distructor */
    ~OSXDeviceInfo() = default;

    /** implementation for physicalMemory method */
    void physicalMemory();

    /** implementation for other methods */
    /*
    void cpuInfo();
    void diskInfo();
    .....
    */
};

#endif