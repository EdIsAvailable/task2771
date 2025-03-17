/*#ifndef CHAT_DB_OPERATIONS_H
#define CHAT_DB_OPERATIONS_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <memory>
#include <string>
#include <cppconn/driver.h>

using namespace sql;
using namespace std;
unique_ptr<sql::Connection> connectToDatabase();
void registerUser(const string& username, const string& passwordHash);
void saveMessage(const string& sender, const string& receiver, const string& message);
void fetchMessages(const string& receiver);

#endif
*/

#ifndef CHAT_DB_OPERATIONS_H
#define CHAT_DB_OPERATIONS_H

#include <mysql/mysql.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <memory>
#include <string>
#include <cppconn/driver.h>

// Function declarations
std::unique_ptr<sql::Connection> connectToDatabase();
void registerUser(const std::string& username, const std::string& passwordHash);
void saveMessage(const std::string& sender, const std::string& receiver, const std::string& message);
void fetchMessages(const std::string& receiver);

#endif // CHAT_DB_OPERATIONS_H