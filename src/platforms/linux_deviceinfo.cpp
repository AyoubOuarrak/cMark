#include "../../include/platforms/linux_deviceinfo.h"
#include "sys/sysinfo.h"
#include "sys/types.h"

/**
*   Get usage of physical memory and save data in a SQLite db
*/
void LinuxDeviceInfo::physicalMemory() {
    struct sysinfo memInfo;
    sysinfo(&memInfo);


    long long physical_memory = memInfo.totalram;
    physical_memory *= memInfo.mem_unit;

    long long used_memory = memInfo.totalram - memInfo.freeram;
    used_memory *= memInfo.mem_unit;

    long long free_memory = physical_memory - used_memory;

    std::string sql = "INSERT INTO memory(total, used, available, time) "   \
                      "VALUES (" + std::to_string(physical_memory/(1024*1024)) + "," +  \
                                   std::to_string(used_memory/(1024*1024)) + "," +      \
                                   std::to_string(free_memory/(1024*1024))  + ","  \
                      "strftime('%H:%M','now', 'localtime'));";
    db->query(sql.c_str());
}