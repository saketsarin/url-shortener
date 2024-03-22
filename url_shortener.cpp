#include "url_shortener.h"
#include "sqlite/sqlite3.h"
#include <iostream>
#include <string>
#include <algorithm>

const std::string DUMMY_DOMAIN = "http://short.url/";
const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int SHORT_URL_LENGTH = 5;

void shortenURL(sqlite3 *db)
{
    std::string inputUrl;
    std::cout << "Enter URL to shorten: ";
    std::getline(std::cin, inputUrl);

    std::string shortenedUrl = DUMMY_DOMAIN + encryptURL(inputUrl);
    std::cout << "Shortened URL: " << shortenedUrl << std::endl;

    std::string insertSQL = "INSERT INTO urls (original_url, shortened_url) VALUES (?, ?)";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK)
    {
        std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, inputUrl.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, shortenedUrl.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_finalize(stmt);

    const char *query = "SELECT * FROM urls";
    sqlite3_stmt *selectStmt;
    rc = sqlite3_prepare_v2(db, query, -1, &selectStmt, 0);
    if (rc == SQLITE_OK)
    {
        std::cout << "\n\n*****Current Database*****" << std::endl;
        while (sqlite3_step(selectStmt) == SQLITE_ROW)
        {
            int id = sqlite3_column_int(selectStmt, 0);
            const unsigned char *originalUrl = sqlite3_column_text(selectStmt, 1);
            const unsigned char *shortenedUrl = sqlite3_column_text(selectStmt, 2);
            std::cout << "ID: " << id << ", Original URL: " << originalUrl << ", Shortened URL: " << shortenedUrl << std::endl;
        }
        sqlite3_finalize(selectStmt);
    }
    else
    {
        std::cerr << "Error fetching data: " << sqlite3_errmsg(db) << std::endl;
    }
}

std::string generateShortURL()
{
    std::string shortUrl;
    for (int i = 0; i < SHORT_URL_LENGTH; i++)
    {
        shortUrl += CHARACTERS[rand() % CHARACTERS.size()];
    }
    return shortUrl;
}

std::string encryptURL(const std::string &url)
{
    std::string encryptedUrl = generateShortURL();
    return encryptedUrl;
}