#include "../platform.h"
#include <thread>
#include <chrono>

/**
*   Main thread
*/
int main() {
    // seconds constant, by default 5min
    const int SECONDS = 60*5; 

    DeviceInfos device;

    while (true) {
        // sleep for 5 min
        std::this_thread::sleep_for(std::chrono::seconds(SECONDS));
        
        // collect physical memory infos and save data into the db
        device.physicalMemory();   
    }
}