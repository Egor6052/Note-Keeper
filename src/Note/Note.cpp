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
    
        pqxx::connection conn("dbname=postgres user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        pqxx::work txn(conn);
        txn.exec(
            "INSERT INTO public.notes (date, message) VALUES ('" + data + "', '" + txn.esc(content) + "');"
        );


        txn.commit();
        std::cout << "\033[36m Message saved successfully!\033[0m" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

std::string Note::getNote() {
    try {
        pqxx::connection conn("dbname=postgres user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Виконання SQL-запиту для отримання всіх записів
        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT id, date, message FROM public.notes ORDER BY id DESC;");

        if (res.empty()) {
            return "No notes found in the database.";
        }

        // Формування рядка з усіма записами
        std::string allNotes;
        for (const auto& row : res) {
            std::string noteID = row["id"].as<std::string>();
            std::string noteDate = row["date"].as<std::string>();
            std::string noteMessage = row["message"].as<std::string>();
            allNotes += "\033[35mid: \033[0m" + noteID + " |\033[37m " + noteDate + " \033[0m|\n   " + noteMessage + "\n\n";
        }
        return allNotes;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return "Error retrieving notes.";
    }
}


void Note::deleteMessage(std::string valueID) {
    try {
        pqxx::connection conn("dbname=postgres user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Виконання SQL-запиту для видалення запису з таблиці за ID
        pqxx::work txn(conn);
        std::string deleteQuery = "DELETE FROM public.notes WHERE id = " + valueID + ";";
        txn.exec(deleteQuery);

        txn.commit();
        std::cout << "\033[36mNote with ID " << valueID << " deleted successfully.\033[0m" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

