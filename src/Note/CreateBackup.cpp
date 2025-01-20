#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include <fstream>
#include "../../lib/Note.h"

void Note::createBackup() {
    try {
        pqxx::connection conn("dbname=postgres user=" + getUserName() + " password=" + getUserPassword() + " host=localhost");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Executing an SQL query
        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT id, date, message FROM public.notes ORDER BY id ASC;");

        if (res.empty()) {
            throw std::runtime_error("No notes found in the database to back up.");
        }

        std::string backupDirectory = "../backups/";
        std::filesystem::create_directories(backupDirectory);

        std::string backupFileName = backupDirectory + getCurrentDateTime() + ".sql";

        // Opening a file for recording
        std::ofstream backupFile(backupFileName);

        if (!backupFile.is_open()) {
            throw std::runtime_error("Failed to open backup file for writing.");
        }

        // Headers
        backupFile << "id,date,message\n";

        // other data
        for (const auto& row : res) {
            backupFile << row["id"].as<std::string>() << ","
                << row["date"].as<std::string>() << ","
                << "\"" << row["message"].as<std::string>() << "\"\n";
        }

        backupFile.close();
        std::cout << "\033[1m\033[35m˚｡⋆\033[36mBackup created successfully in file: \033[35m" << backupFileName << "\033[0m\n" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error creating backup: " << e.what() << '\n';
    }
}

