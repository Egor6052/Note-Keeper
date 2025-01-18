#include <iostream>
#include <string.h>
#include "../lib/Note.h"

int main(){
    std::cout << "\033[1m\033[35m˚｡⋆\033[36mWelcome to the Note Keeper!\033[35m⋆｡˚\033[0m\n" << std::endl;
    Note note;
    std::string adminPassword;
    std::printf("Enter admin password: ");
    std::cin >> adminPassword;
    std::cin.ignore();
    note.createPostgresUser(adminPassword);
    note.CreateTable();
    std::string message;
    do {
        std::string message, menu, answer;
        menu = "|\033[37m Create note - 1 \033[0m|  |\033[37m Delete note - 2 \033[0m|   |\033[37m View table - 3 \033[0m|";

        std::string horizontalLine(menu.length()-27, '-');
        std::cout << horizontalLine << "\n" << menu << "\n" << horizontalLine << std::endl;
        

        std::cin >> answer;
        std::cin.ignore();

        if (answer == "1") {
            std::printf("Enter your message: ");
            std::getline(std::cin, message);
            note.setMessage(message);
            std::cout << note.getNote() << std::endl;

        } else if (answer == "2") {
            std::cout << note.getNote() << std::endl;
            std::printf("Enter id message would you like to delete: ");
            std::cin >> answer;
            std::cin.ignore();
            note.deleteMessage(answer);
            std::cout << note.getNote() << std::endl;
        } else if (answer == "3"){
            std::cout << note.getNote() << std::endl;
        }
    } while (true);


    return 0;
}