cmake_minimum_required(VERSION 3.17)
project(PasswordManagerConsole)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

add_executable(PasswordManagerConsole main.cpp db_lite.h db_lite.cpp
        Passwords.h Passwords.cpp User.cpp User.h test_runner.h profile.h
        interface.h interface.cpp)

target_link_libraries(PasswordManagerConsole Qt5::Widgets Qt5::Core Qt5::Gui sqlite3)




#target_link_libraries(PasswordManagerConsole LINK_PUBLIC sqlite3)
