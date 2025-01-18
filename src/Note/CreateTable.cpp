#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include "../../lib/Note.h"


void Note::CreateTable() {
    try {
        std::string connectionString = "dbname=postgres user=" + getUserName() + " password=" + getUserPassword() + " host=localhost";

        pqxx::connection conn(connectionString);

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to database!");
        }

        // Перевірка, чи існує таблиця
        pqxx::work txn(conn);
        pqxx::result res = txn.exec("SELECT to_regclass('public.Notes');");

        if (res[0][0].is_null()) {
            // Якщо таблиця не існує, створити її
            std::string createTableQuery = R"(
                CREATE TABLE public.Notes (
                    id SERIAL PRIMARY KEY,
                    date VARCHAR(255),
                    message TEXT
                );
            )";
            txn.exec(createTableQuery);
            txn.commit();
            std::cout << "\033[1m\033[35m⋆⟡₊⊹\033[36mTable 'Notes' created successfully!\033[35m⊹₊⟡⋆\033[0m\n" << std::endl;
        } else {
            std::cout << "\033[1m\033[35m⋆⟡₊⊹\033[36mTable 'Notes' already exists!\033[35m⊹₊⟡⋆\033[0m\n" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
