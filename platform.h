#ifndef PLATFORM_HEADER_GUARD_H
#define PLATFORM_HEADER_GUARD_H

#if defined(_WIN32)
#include "include/platforms/win_deviceinfo.h"
typedef WinDeviceInfo DeviceInfos;

#elif  (defined(__APPLE__) && defined(__MACH__))
#include "include/platforms/osx_deviceinfo.h"
typedef OSXDeviceInfo DeviceInfos;

#elif __linux__
#include "include/platforms/linux_deviceinfo.h"
typedef LinuxDeviceInfo DeviceInfos;

#endif

#endif // PLATFORM_HEADER_GUARD_H