#include "../../include/platforms/win_deviceinfo.h"
#include "windows.h"
#include "psapi.h"

/**
*   Get usage of physical memory and save data to in a SQLite db
*/
void WinDeviceInfo::physicalMemory() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    long long physical_memory = memInfo.ullTotalPhys;
    long long used_memory = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
    long long free_memory = physical_memory - used_memory;

    // create a query to save data in Mb
    std::string sql = "INSERT INTO memory(total, used, available, time) "   \
                      "VALUES (" + std::to_string(physical_memory/(1024*1024)) + "," +  \
                                   std::to_string(used_memory/(1024*1024)) + "," +      \
                                   std::to_string(free_memory/(1024*1024))  + ","  \
                      "strftime('%H:%M','now', 'localtime'));";
    db->query(sql.c_str());
}