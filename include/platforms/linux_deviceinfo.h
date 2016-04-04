#ifndef LINUX_DEVICE_INFO_GUARD_H
#define LINUX_DEVICE_INFO_GUARD_H
#include "../device_info.h"

/**
*   Get device info for Linux platform
*/
class LinuxDeviceInfo : public DeviceInfo {
private:

public:
    /** default constructor */
    LinuxDeviceInfo() = default;

    /** default distructor */
    ~LinuxDeviceInfo() = default;

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