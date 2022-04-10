cmake_minimum_required(VERSION 3.21)
project(Curriculum_Design)

set(CMAKE_CXX_STANDARD 14)

include_directories(Curriculum_Design)

add_executable(Curriculum_Design
        Curriculum_Design/account.cpp
        Curriculum_Design/account.h
        Curriculum_Design/admin_AccountInfoReceiver.cpp
        Curriculum_Design/admin_AccountInfoReceiver.h
        Curriculum_Design/admin_interface.cpp
        Curriculum_Design/admin_interface.h
        Curriculum_Design/main.cpp
        Curriculum_Design/user_AccountInfoReceiver.cpp
        Curriculum_Design/user_AccountInfoReceiver.h
        Curriculum_Design/user_interface.cpp
        Curriculum_Design/user_interface.h
        Curriculum_Design/province_information_manager.h
        Curriculum_Design/province_information_manager.cpp
        Curriculum_Design/daily_health_check_admin.h
        Curriculum_Design/daily_health_check_admin.cpp
        Curriculum_Design/daily_health_check_user.h
        Curriculum_Design/daily_health_check_user.cpp
        Curriculum_Design/account_info_manager.h
        Curriculum_Design/account_info_manager.cpp
        Curriculum_Design/daily_health_check.h
        Curriculum_Design/daily_health_check.cpp
        Curriculum_Design/time_manager.cpp
        Curriculum_Design/time_manager.h
        Curriculum_Design/NAT.h
        Curriculum_Design/NAT.cpp
        Curriculum_Design/NAT_user.h
        Curriculum_Design/NAT_user.cpp
        Curriculum_Design/NAT_admin.h
        Curriculum_Design/NAT_admin.cpp
        Curriculum_Design/necessary_affairs_manager.h
        Curriculum_Design/necessary_affairs_manager.cpp)
