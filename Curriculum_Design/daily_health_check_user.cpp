#include "daily_health_check_user.h"
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

daily_health_check_user::daily_health_check_user()
{
    // 现在编写 => 新版 => 文件结构发生~巨大的改变
    /*write into current_info*/
    current_health_check_info = new health_check_info; // new，记得delete
    current_health_check_info->student_name = return_real_name();
    current_health_check_info->account_id = return_c_account();
    current_health_check_info->student_id = return_student_number();
    current_health_check_info->if_check_is_necessary = true; // 默认 必须上报
    current_health_check_info->if_checked = false; // 默认 没有打卡
    /*load from file*/
    try_to_load_from_file_new(current_health_check_info->student_id);
    // old
    //     current_health_check_info = new health_check_info;
    //     const string temp_account_id = return_c_account();
    //     const string temp_student_name = return_real_name();
    //     const string temp_student_id = return_student_number();
    //     const string possible_file_name = file_root + temp_student_id + "_daily_check.dat";
    //     current_health_check_info->student_name = temp_student_name;
    //     current_health_check_info->student_id = temp_student_id;
    //     current_health_check_info->account_id = temp_account_id;
    //     try_to_load_from_file(possible_file_name);
    if (current_health_check_info->if_checked) {
        cout << "您已完成健康打卡！是否需要查看当前的健康打卡状态？(输入Y/y则查看，其他字符则不查看，并自动回到上一级菜单) >>> ";
        char temp;
        cin >> temp;
        if (temp == 'y' || temp == 'Y') {
            show_check_status();
        } else {
            cout << "收到！即将返回 [用户界面] ... " << endl;
            Sleep(250);
        }
    } else if (current_health_check_info->if_check_is_necessary == true) {
        pre_push_lable(); // 没有每日打卡，提示，然后强制打卡
        do_the_check();
    } else {
        cout << "您并未被强制要求进行 <健康打卡>，请问您是否要自愿打卡？(输入Y/y则打卡，其他字符则不打卡，并自动回到上一级菜单) >>> ";
        char flag;
        cin >> flag;
        if (flag == 'y' || flag == 'Y') {
            do_the_check();
        } else {
            cout << "收到！即将返回 [用户界面] ... " << endl;
            Sleep(250);
        }
    }
}

// 下面这个函数已被弃用
void daily_health_check_user::try_to_load_from_file(const string& possible_file_name)
{
    fstream file;
    file.open(possible_file_name, ios::in | ios::binary);
    if (!file.is_open()) {
        // 没有出错的情况下，就是没有这个文件，准备执行
        if (current_health_check_info->if_check_is_necessary) {
            pre_push_lable();
            do_the_check();
        } else {
            file.read((char*)(current_health_check_info), sizeof(health_check_info));
        }
    }
    file.close(); // 及时关闭
}
// 上面这个函数已被弃用

void daily_health_check_user::try_to_load_from_file_new(const string& input_sno)
{
    cached_health_check_info = new health_check_info; // 缓存，用于比对信息
    fstream file;
    bool if_file_is_empty = check_if_file_is_empty();
    if (if_file_is_empty) { // 文件是空的
        // 保留 current_health_check_info 中的默认参数
    } else {
        file.open(daily_health_check_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            delete cached_health_check_info;
            // 现在一定存在这个文件，打不开就是失败
            cout << "无法打开 daily_health_check_list.dat！即将自动退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (file.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (cached_health_check_info->account_id == current_health_check_info->account_id) {
                // move value
                current_health_check_info = std::move(cached_health_check_info); // 贼好用这个
                break;
            }
        }
        file.close(); // 及时关闭
        delete cached_health_check_info; // 解除缓存
    }
}

void daily_health_check_user::do_the_check()
{
    // 可能用到的文件名 [弃用]
    // const string file_name = file_root + current_health_check_info->student_id + "_daily_check.dat";
    // 是否询问 是否返校
    bool if_ask_if_accomodated;
    // 是否返校
    while (true) {
        cout << endl;
        cout << "请问你是否已经返校 ？(Y/N) >>> ";
        char temp;
        cin >> temp;
        if (temp == 'y' || temp == 'Y') {
            current_health_check_info->if_returned_school = true;
            if_ask_if_accomodated = true;
            break;
        } else if (temp == 'n' || temp == 'N') {
            current_health_check_info->if_returned_school = false;
            if_ask_if_accomodated = false;
            break;
        } else {
            cout << "输入的字符无效，请输入Y/y/N/n，将再次显示之前的选项：" << endl;
        }
    }
    // 是否住校
    if (!if_ask_if_accomodated) {
        current_health_check_info->if_is_accomodated = false;
    } else {
        while (true) {
            cout << endl;
            cout << "请问你是否住校 ？(Y/N) >>> ";
            char temp;
            cin >> temp;
            if (temp == 'y' || temp == 'Y') {
                current_health_check_info->if_is_accomodated = true;
                break;
            } else if (temp == 'n' || temp == 'N') {
                current_health_check_info->if_is_accomodated = false;
                break;
            } else {
                cout << "输入的字符无效，请输入Y/y/N/n，将再次显示之前的选项：" << endl;
            }
        }
    }
    // 体温是否正常
    while (true) {
        cout << endl;
        cout << "请问你的体温是否超过 37℃ ？(Y/N) >>> ";
        char temp;
        cin >> temp;
        if (temp == 'y' || temp == 'Y') {
            current_health_check_info->if_temperature_higher_than_37 = true;
            break;
        } else if (temp == 'n' || temp == 'N') {
            current_health_check_info->if_temperature_higher_than_37 = false;
            break;
        } else {
            cout << "输入的字符无效，请输入Y/y/N/n，将再次显示之前的选项：" << endl;
        }
    }
    // 14天内 是否曾经在 中风险/高风险地区 停留超过一天
    if (if_have_medium_and_high_risk_region_direct()) {
        while (true) {
            cout << endl;
            cout << "14天内，是否曾经在 <中风险/高风险地区> 停留超过一天 " << endl
                 << "(0=>无，1=>在中风险区域停留超过一天，2=>在高风险区域停留超过一天，3=>显示中、高风险区域列表) >>> ";
            int temp;
            cin >> temp;
            if (temp == 0) {
                current_health_check_info->if_passed_by_high_risk_regions = false;
                current_health_check_info->if_passed_by_midium_risk_regions = false;
            } else if (temp == 1) {
                current_health_check_info->if_passed_by_midium_risk_regions = true;
                current_health_check_info->if_passed_by_high_risk_regions = false;
            } else if (temp == 2) {
                current_health_check_info->if_passed_by_high_risk_regions = true;
                current_health_check_info->if_passed_by_midium_risk_regions = false;
            } else if (temp == 3) {
                // TODO: function_show_high_and_medium_risk_regions
                show_province_info_direct();
            } else {
                cout << "输入的字符无效，请输入0/1/2/3，将再次显示之前的选项：" << endl;
            }
        }
    } else {
        current_health_check_info->if_passed_by_midium_risk_regions = false;
        current_health_check_info->if_passed_by_high_risk_regions = false;
        cout << endl
             << "目前，34个省级区域，均为低风险区，系统将跳过 <是否在中高风险区停留> 这一选项！" << endl;
    }
    // 是否有出国旅居史
    while (true) {
        cout << endl;
        cout << "近期是否有出国旅居史 ？(Y/N) >>> ";
        char temp;
        cin >> temp;
        if (temp == 'y' || temp == 'Y') {
            current_health_check_info->if_temperature_higher_than_37 = true;
            break;
        } else if (temp == 'n' || temp == 'N') {
            current_health_check_info->if_temperature_higher_than_37 = false;
            break;
        } else {
            cout << "输入的字符无效，请输入Y/y/N/n，将再次显示之前的选项：" << endl;
        }
    }
    // 更新打卡的完成情况
    current_health_check_info->if_checked = true;
    // 写入 打卡文件
    write_to_file_new(); // 采用 新函数
    // end
    cout << endl;
    cout << "您已完成 <每日健康打卡> ，感谢您的配合！" << endl;
}

void daily_health_check_user::write_to_file(const string& filename)
{
    fstream file;
    file.open(filename, ios::trunc | ios::binary | ios::out);
    if (!file.is_open()) {
        cout << "信息写入阶段，打开 xx_daily_check.dat 失败！即将退出程序" << endl;
        Sleep(250);
        exit(-1);
    }
    file.write((char*)(current_health_check_info), sizeof(health_check_info));
    file.close();
}

void daily_health_check_user::write_to_file_new()
{
    cached_health_check_info = new health_check_info;
    fstream file(daily_health_check_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "信息写入阶段，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    if (!if_daily_check_file_is_empty) { // 文件里不是空的 => 需要找到正确的位置
        int POS;
        while (file.read((char*)(cached_health_check_info), sizeof(health_check_info))) {
            if (cached_health_check_info->student_id == current_health_check_info->student_id) {
                POS = file.tellg();
                break;
            }
        }
        file.close();
        file.open(daily_health_check_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "信息写入阶段，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.seekp(POS, ios::beg);
        file.write((char*)(current_health_check_info), sizeof(health_check_info));
        file.close();
    } else { // 文件是空的 => 直接不用找位置了，写到头上就完全OK
        file.close();
        file.open(daily_health_check_file_location, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "信息写入阶段，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.write((char*)(current_health_check_info), sizeof(health_check_info));
        file.close();
    }
}

void daily_health_check_user::show_province_info_direct()
{
    // 由于 [展示函数] 是public的，所有不需要继承或者友元函数，直接临时调用就可以
    auto* temp = new province_information_manager;
    //
    temp->show_high_and_medium_risk_regions();
    delete temp;
}

auto daily_health_check_user::if_have_medium_and_high_risk_region_direct() -> bool
{
    // 由于 [判断函数] 是public的，所有不需要继承或者友元函数，直接临时调用就可以
    bool result;
    auto* temp = new province_information_manager;
    //
    result = temp->if_have_high_and_medium_risk_regions();
    delete temp;
    return result;
}
