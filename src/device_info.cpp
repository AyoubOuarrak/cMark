#include "../include/device_info.h"

/**
*   Default constructor, initialize db manager
*/
DeviceInfo::DeviceInfo() {
    db = new DBManager();
}

/**
*   Default constructor, initialize db manager
*/
DeviceInfo::DeviceInfo(DBManager* _db) {
    db = _db;
}

/**
*   Default constructor, initialize db manager
*/
DeviceInfo::~DeviceInfo() {
    delete db;
}

