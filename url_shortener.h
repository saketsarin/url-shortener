#ifndef URL_SHORTENER_H
#define URL_SHORTENER_H

#include <string>
#include "sqlite/sqlite3.h"

void shortenURL(sqlite3 *db);
std::string generateShortURL();
std::string encryptURL(const std::string &url);

#endif
