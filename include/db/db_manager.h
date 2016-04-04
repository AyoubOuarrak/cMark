#ifndef DB_MANAGER_GUARD_H
#define DB_MANAGER_GUARD_H

#include <sqlite3.h>
#include <cstdlib>
#include <string>

/**
*   Database manager class
*/
class DBManager {
private:
    static bool CREATE;
    std::string db_name;
    sqlite3* db;
    char* zErrMsg;
    int  rc;

    static int callback(void* NotUsed, int argc, char** argv, char** azColName);

public:
    /** default constructor */
    DBManager();
    /** default distructor */
    ~DBManager();
    /** constructor that take the name of a db */
    DBManager(std::string name);

    /** execute db query */
    void query(const char* _sql);
};
#endif