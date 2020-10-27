cmake_minimum_required(VERSION 3.17)
project(PasswordManagerConsole)

set(CMAKE_CXX_STANDARD 17)

add_executable(PasswordManagerConsole main.cpp db_lite.h db_lite.cpp
        Passwords.h Passwords.cpp User.cpp User.h)

target_link_libraries(PasswordManagerConsole LINK_PUBLIC sqlite3)