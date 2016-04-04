#include "../../include/db/db_manager.h"
#include <iostream>

bool DBManager::CREATE = true;

/**
*   Default constructor, open db
*/
DBManager::DBManager() {
    rc = sqlite3_open("build/memory.db", &db);

    // check if there are errors 
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db);
        exit(0);

    // database ok, if create flag is true create a new one
    } else if(DBManager::CREATE) {
        query("CREATE TABLE if not exists memory(" \
              "total      LONG      NOT NULL," \
              "used       LONG      NOT NULL," \
              "available  LONG      NOT NULL," \
              "time       TIMESTAMP NOT NULL);");

        std::cout << "Opened database successfully" << std::endl;
    }
        
}

/**
*   Default distructor
*/
DBManager::~DBManager() {
    sqlite3_close(db);
}

/**
*   Constructor that take the name of a db
*/
DBManager::DBManager(std::string name) {
    rc = sqlite3_open(name.c_str(), &db);

    // check if there are errors 
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db);
        exit(0);

    // database ok, if create flag is true, create a new one
    } else if(DBManager::CREATE) {
        query("CREATE TABLE if not exists memory(" \
              "total      LONG      NOT NULL," \
              "used       LONG      NOT NULL," \
              "available  LONG      NOT NULL," \
              "time       TIMESTAMP NOT NULL);");

        std::cout << "Opened database successfully" << std::endl;
    }
}

/**
*   Execute query
*/
void DBManager::query(const char* sql) {
    if(strstr(sql, "select") != nullptr || strstr(sql, "SELECT") != nullptr) {
        const char* data = "Callback function called";
        rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    
    } else
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << zErrMsg << std::endl;
      sqlite3_free(zErrMsg);
    }
}

/**
*   DBManager callback
*/
int DBManager::callback(void* NotUsed, int argc, char** argv, char** azColName){
   for (int i = 0; i < argc; i++) {
      std::cout << azColName[i] << " = " << argv[i] ? argv[i] : "NULL";
      std::cout << std::endl;
   }
   
   std::cout << std::endl;
   return 0;
}