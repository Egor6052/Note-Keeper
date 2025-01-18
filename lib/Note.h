#pragma once
#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string.h>
#include "UserDB.h"

class Note : public UserDB{
    private:
    std::string data; 
    std::string content;

    public:
        Note();
        ~Note();

        std::string getCurrentDateTime();

        void CreateTable();
        void setMessage(std::string valueMessage);
        void deleteMessage(std::string valueID);
        std::string getNote();
};

#endif