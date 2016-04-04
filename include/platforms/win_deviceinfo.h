#ifndef WIN_DEVICE_INFO_GUARD_H
#define WIN_DEVICE_INFO_GUARD_H
#include "../device_info.h"

/**
*   Get device info for Windows platform
*/
class WinDeviceInfo : public DeviceInfo {
private:

public:
    /** default constructor */
    WinDeviceInfo() = default;

    /** default distructor */
    ~WinDeviceInfo() = default;

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