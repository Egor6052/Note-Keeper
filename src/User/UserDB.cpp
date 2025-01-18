#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include "../../lib/UserDB.h"

UserDB::UserDB(){
    this->name = "";
    this->password = "";
}
UserDB::~UserDB(){

}
void UserDB::setName(std::string valueName){
    this->name = valueName;
}
void UserDB::setPassword(std::string valuePassword){
    this->password = valuePassword;
}

void UserDB::createPostgresUser(const std::string& adminPassword) {
    try {
        // Підключення до бази даних під адміністратором
        std::string connectionString = "dbname=postgres user=postgres password=" + adminPassword + " host=localhost";

        pqxx::connection conn(connectionString);

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to the database!");
        }

        std::cout << "Connected to the database successfully!" << std::endl;

        // Створення нового користувача
        pqxx::work txn(conn);
        std::string createUserQuery = "CREATE USER " + name + " WITH PASSWORD '" + password + "';";
        txn.exec(createUserQuery);

        txn.commit();
        std::cout << "User '" << name << "' created successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}


std::string UserDB::getUserPassword(){
    return this->password;
}
std::string UserDB::getUserName(){
    return this->name;
}

std::string UserDB::getUser(){
    std::string user = "Name: " + name + "\npassword: " + password;
    return user;
}