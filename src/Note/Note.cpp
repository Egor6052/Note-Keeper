#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include "../../lib/Note.h"

Note::Note(){
    this->data = "";
    this->content = "";
}
Note::~Note(){

}

void Note::setMessage(std::string valueMessage){

    try {
    this->data = getCurrentDateTime();
    this->content = valueMessage;
    
    // Connection to DB
        pqxx::connection conn("dbname=server user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Executing an SQL query to insert data
        pqxx::work txn(conn);
        txn.exec(
            "INSERT INTO Notes (date, message) VALUES ("
            "'" + data + "', '" + txn.esc(content) + "'"
            ");"
        );
        txn.commit();
        std::cout << "Message saved successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

std::string Note::getNote() {
    try {
        // Підключення до бази даних
        pqxx::connection conn("dbname=server user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Виконання SQL-запиту для отримання останнього запису
        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT date, message FROM Notes ORDER BY id DESC LIMIT 1;");

        if (res.empty()) {
            return "No notes found in the database.";
        }

        // Витягування даних з результату
        std::string latestDate = res[0]["date"].as<std::string>();
        std::string latestMessage = res[0]["message"].as<std::string>();

        // Повернення запису у вигляді рядка
        return latestDate + " # " + latestMessage;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return "Error retrieving note.";
    }
}
