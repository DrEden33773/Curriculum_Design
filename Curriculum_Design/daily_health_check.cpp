#include "daily_health_check.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

daily_health_check::daily_health_check()
{
    check_if_file_is_empty(); // 直接忽略返回值就行
    check_if_dictionary_is_empty(); // 直接忽略返回值就行
    // 下面，准备更新 => 时间索引文件
    fstream file;
    file.open(time_dictionary_file_location, ios::out | ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "更新时间索引时，打开 time_dictionary.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (if_time_dictionary_file_is_empty) {
        // 直接写入
        file.write((char*)(&current_time), sizeof(time_manager));
    } else {
        // 比对尾部，判断是否写入
        file.seekg(-sizeof(time_manager), ios::end);
        file.seekp(-sizeof(time_manager), ios::end);
        file.read((char*)(&time_dict_tail_checker), sizeof(time_manager));
        if (time_dict_tail_checker == current_time) {
            // 最新的时间就是当前日期，nothing to do
        } else {
            file.seekp(0, ios::end); // 写指针指尾
            file.write((char*)(&current_time), sizeof(time_manager)); // 单次写入
        }
    }
    file.close(); // 及时关闭
}

inline void daily_health_check::make_sure_file_exists()
{
    fstream file;
    /// now, tries to new the file
    file.open(daily_health_check_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预创建 daily_health_check_list.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // 及时关闭
}

auto daily_health_check::check_if_file_is_empty() -> bool
{
    make_sure_file_exists(); // 确保文件正常的产生
    fstream file;
    file.open(daily_health_check_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 daily_health_check_list.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    checker = new health_check_info;
    bool if_empty = true;
    while (file.read((char*)(checker), sizeof(health_check_info))) {
        if_empty = false;
        break;
    }
    file.close();
    delete checker;
    if_daily_check_file_is_empty = if_empty;
    return if_empty;
}

void daily_health_check::make_sure_dictionary_exists() // 用到time_dictionary_file_location
{
    fstream file;
    /// now, tries to new the file
    file.open(time_dictionary_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预创建 time_dictionary.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // 及时关闭
}

auto daily_health_check::check_if_dictionary_is_empty() -> bool
{
    make_sure_file_exists(); // 确保文件正常的产生
    fstream file;
    file.open(time_dictionary_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 time_dictionary.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    time_dict_checker = new dict_checker;
    bool if_empty = true;
    while (file.read((char*)(time_dict_checker), sizeof(dict_checker))) {
        if_empty = false;
        break;
    }
    file.close();
    delete time_dict_checker;
    if_time_dictionary_file_is_empty = if_empty;
    return if_empty;
}
