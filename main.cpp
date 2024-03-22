#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"
#include "url_shortener.h"

int main()
{
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("url_shortener.db", &db);
    if (rc)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS urls (id INTEGER PRIMARY KEY AUTOINCREMENT, original_url TEXT NOT NULL, shortened_url TEXT NOT NULL)";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }

    shortenURL(db);

    sqlite3_close(db);
    return 0;
}

