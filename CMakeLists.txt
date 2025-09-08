# Мінімальна версія CMake
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
    ./src/GUI/NoteKeeperApp.cpp
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

# Якщо компілюється на Windows, додаємо специфічні налаштування
if(WIN32)
    message(STATUS "Configuring for Windows")

    # Якщо використовуєте MinGW
    if(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    endif()

    # Якщо використовуєте MSVC
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
    endif()
endif()

# Додавання GTKMM
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Додати шляхи до заголовкових файлів і бібліотек GTKMM
target_include_directories(start PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(start PRIVATE ${GTKMM_LIBRARIES})
target_compile_options(start PRIVATE ${GTKMM_CFLAGS_OTHER})

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

# Додавання PostgreSQL
find_package(PostgreSQL REQUIRED)
target_link_libraries(start PRIVATE pqxx)