#include "../../include/platforms/osx_deviceinfo.h"
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <sys/sysctl.h>
#include <sys/types.h>

/**
* Get usage of physical memory and save data to in a SQLite db
*/
void OSXDeviceInfo::physicalMemory() {
    long long free_memory;
    long long used_memory;

    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);

    // get total physical memory in bytes
    int mib[2];
    int64_t physical_memory;
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    std::size_t length = sizeof(int64_t);
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);

    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
                                         (host_info64_t)&vm_stats, &count)) {
        
        // get free and used memory in bytes
        free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;
        used_memory = ((int64_t)vm_stats.active_count +
                       (int64_t)vm_stats.inactive_count +
                       (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
    }
    
    // create a query to save data in Mb
    std::string sql = "INSERT INTO memory(total, used, available, time) "   \
                      "VALUES (" + std::to_string(physical_memory/(1024*1024)) + "," +  \
                                   std::to_string(used_memory/(1024*1024)) + "," +      \
                                   std::to_string(free_memory/(1024*1024))  + ","  \
                      "strftime('%H:%M','now', 'localtime'));";
    db->query(sql.c_str());
}