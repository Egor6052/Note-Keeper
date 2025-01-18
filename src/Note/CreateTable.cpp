#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include "../../lib/Note.h"

void Note::CreateTable() {
    try {
        // Connecting to DB
        pqxx::connection conn("dbname=server user=" + getUserName() + " password=" + getUserPassword() + " host=TextKeeper");

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }
        std::cout << "Connected to database successfully: " << conn.dbname() << std::endl;

        // Executing SQL queries
        pqxx::work txn(conn);

        txn.exec(
            "CREATE TABLE IF NOT EXISTS Notes ("
            "id SERIAL PRIMARY KEY, "
            "date TIMESTAMPTZ NOT NULL, "
            "message TEXT NOT NULL"
            ");"
        );
        txn.commit();
        std::cout << "Table created successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}