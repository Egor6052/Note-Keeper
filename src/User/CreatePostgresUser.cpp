#include <iostream>
#include <string.h>
#include <pqxx/pqxx>
#include "../../lib/UserDB.h"

void UserDB::createPostgresUser(const std::string& adminPassword) {
    try {
        // Підключення до бази даних під адміністратором
        std::string connectionString = "dbname=postgres user=postgres password=" + adminPassword + " host=localhost";

        pqxx::connection conn(connectionString);

        if (!conn.is_open()) {
            throw std::runtime_error("Failed to connect to the database!");
        }

        // std::cout << "\033[36m Connected to the database successfully!\033[0m" << std::endl;

        // Створення нового користувача або перевірка, чи існує вже
        pqxx::work txn1(conn);

        // Перевірка, чи існує вже роль з таким ім'ям
        std::string checkUserQuery = "SELECT 1 FROM pg_roles WHERE rolname = '" + name + "';";
        pqxx::result checkResult = txn1.exec(checkUserQuery);

        if (checkResult.empty()) {
            // Якщо роль не існує, створюємо її
            std::string createUserQuery = "CREATE USER " + name + " WITH PASSWORD '" + password + "';";
            txn1.exec(createUserQuery);
            std::cout << "\033[36m User '" << name << "' created successfully!\033[0m" << std::endl;
        } else {
            // std::cout << "\033[36m Role '" << name << "' already exists.\033[0m" << std::endl;
        }

        // std::string grantTablePrivilegesQuery = "GRANT ALL PRIVILEGES ON TABLE public.notes TO " + name + ";";
        // txn.exec(grantTablePrivilegesQuery);
        txn1.commit();
        // std::cout << "\033[36m Privileges granted to user '\033[0m\033[35m" << name << "\033[0m\033[36m'.\033[0m" << std::endl;


        // Виконання запиту для перевірки, чи має користувач вже привілеїї на таблицю
        pqxx::work txn2(conn);
        std::string checkPrivilegesQuery = "SELECT has_table_privilege('" + name + "', 'public.notes', 'INSERT, SELECT, UPDATE, DELETE');";
        pqxx::result res = txn2.exec(checkPrivilegesQuery);

        if (res.empty()) {
            throw std::runtime_error("Error checking privileges.");
        }

        // Якщо користувач не має привілеїй
        if (res[0][0].as<bool>() == false) {
            // Надання привілеїй
            std::string grantTablePrivilegesQuery = "GRANT ALL PRIVILEGES ON TABLE public.notes TO " + name + ";";
            txn2.exec(grantTablePrivilegesQuery);
            txn2.commit();
            std::cout << "\033[36m Privileges granted to user '\033[0m\033[35m" << name << "\033[0m\033[36m'.\033[0m" << std::endl;
            std::cout << "Privileges granted." << std::endl;
        } else {
            // std::cout << "\033[36m User '\033[0m\033[35m" << name << "\033[0m\033[36m' already has privileges.\033[0m" << std::endl;
            // std::cout << "User already has privileges." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}
