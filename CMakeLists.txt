cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Назва проекту
project(NoteProject)

# Опція для використання статичних бібліотек
option(USE_STATIC "Use static library" ON)

# Вивід повідомлення про систему
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")

# Шлях до вихідних файлів
set(SOURCE_FILES
    ./src/User/UserDB.cpp
    ./src/User/CreatePostgresUser.cpp
    ./src/Note/Note.cpp
    ./src/Note/CreateBackup.cpp
    ./src/Note/CreateTable.cpp
    ./src/Note/DateTime.cpp
)

# Заголовкові файли
set(HEADER_FILES
    ./lib/Note.h
    ./lib/UserDB.h
)

# Додавання виконуваного файлу
add_executable(start
    src/main.cpp
    ${SOURCE_FILES}
)

# Компіляторні опції
target_compile_options(start
    PRIVATE
        -Wall -fPIC
)

# Додавання шляхів до заголовкових файлів
target_include_directories(start
    PRIVATE
        ./lib
)

find_package(PostgreSQL REQUIRED)
target_link_libraries(start PRIVATE pqxx)
