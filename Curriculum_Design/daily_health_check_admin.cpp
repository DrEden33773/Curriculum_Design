#include "daily_health_check_admin.h"

#include <conio.h>

#include "daily_health_check_user.h"
#include "time_manager.h"
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <synchapi.h>
#include <vector>

void daily_health_check_admin::try_to_load_check_status_file()
{
    fstream file_daily_check_list(daily_health_check_file_location, ios::app | ios::binary);
    if (!file_daily_check_list.is_open()) {
        cout << "预加载 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file_daily_check_list.close();
    file_daily_check_list.open(daily_health_check_file_location, ios::binary | ios::in);
    if (!file_daily_check_list.is_open()) {
        cout << "打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cached_health_check_info_tr = new health_check_info_trans;
    file_daily_check_list.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans));
    status_of_if_need_to_check = cached_health_check_info_tr->if_check_is_necessary;
    delete cached_health_check_info_tr;
    cached_health_check_info_tr = nullptr;
}

void daily_health_check_admin::change_all_status_in_daily_check_file()
{
    cout << "现在，对文件中的 <健康打卡状态> 进行更新 ... " << endl;
    Sleep(250);
    // 打开文件
    fstream file_daily_check_list(daily_health_check_file_location, ios::out | ios::binary | ios::in);
    // 使用 out & in 打开文件 => 确保 读写指针可任工指定位置 同时 确保 打开文件的时候不删除原有内容
    if (!file_daily_check_list.is_open()) {
        cout << "写入文件过程中，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // 修改
    cached_health_check_info_tr = new health_check_info_trans;
    // bug => 这个 读写 有问题 [致命的说，应该是这种读写有问题]
    // bug => 修复方法只能是开一个临时文件然后往里写入, 然后改文件名
    fstream temp(temp_daily_health_check_file_location, ios::out | ios::binary);
    if (!temp.is_open()) {
        cout << "写入文件过程中，创建 temp_daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file_daily_check_list.read(
        reinterpret_cast<char*>(cached_health_check_info_tr),
        sizeof(health_check_info_trans))) {
        cached_health_check_info_tr->if_check_is_necessary = status_of_if_need_to_check;
        temp.write(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans));
    }
    delete cached_health_check_info_tr;
    cached_health_check_info_tr = nullptr;
    file_daily_check_list.close();
    temp.close();
    remove(daily_health_check_file_location.c_str());
    rename(temp_daily_health_check_file_location.c_str(), daily_health_check_file_location.c_str());
    // end
    cout << "文件中的 <是否强制健康打卡状态> 修改完毕！即将返回 [功能列表] ... " << endl;
}

void daily_health_check_admin::auto_delete()
{
    // 借助 remove 和 rename 函数，这两个函数对文件的操作，都不需要打开文件
    // 自动删除 => 1.时间索引中的过期索引 2.过期的未打卡用户文件
    if (auto_delete_range > 0) {
        // 得到新的时间索引 & 删除过期未打卡文件
        fstream old_time_dict_file(time_dictionary_file_location, ios::in | ios::binary);
        fstream new_time_dict_file(temp_time_dictionary_file_location, ios::out | ios::binary);
        if (!old_time_dict_file.is_open()) {
            cout << "自动删除过程中，无法打开原有的 time_dictionary.dat ！即将自动退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        if (!new_time_dict_file.is_open()) {
            cout << "自动删除过程中，无法创建新的 time_dictionary.dat ！即将退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        while (old_time_dict_file.read(reinterpret_cast<char*>(&cached_time), sizeof(time_manager))) {
            if (current_time - cached_time < auto_delete_range) {
                new_time_dict_file.write(reinterpret_cast<char*>(&cached_time), sizeof(time_manager));
            } else {
                // 超过期限
                string cached_unchecked_file_location = name_base;
                cached_unchecked_file_location += cached_time.time_str();
                cached_unchecked_file_location += ".txt";
                remove(cached_unchecked_file_location.c_str());
            }
        }
        old_time_dict_file.close();
        new_time_dict_file.close();
        // 删除旧的时间索引
        remove(time_dictionary_file_location.c_str());
        // 重命名新的时间索引
        rename(temp_time_dictionary_file_location.c_str(), time_dictionary_file_location.c_str());
        // done!
        cout << "已删除 <过期的未打卡用户文件> ... " << endl;
    } else {
        cout << "已禁用 <自动删除过期的未打卡用户文件> 功能，跳过此步骤 ... " << endl;
    }
}

void daily_health_check_admin::change_auto_delete_range()
{
    cout << "当前的 <{未打卡名单} 自动删除期限> 为 => [" << auto_delete_range << "天] ... " << endl;
    cout << "<自动删除期限 N> 指的是：将删除 N 天前(含)的所有 {未打卡名单} ... " << endl;
    cout << "请注意！如果想要停用该功能，请输入任意负数；但如果不想停用该功能，请输入 [大于零的正数] ！" << endl;
    while (true) {
        Sleep(250);
        cout << "现在请输入修改后的 <自动删除期限> : ";
        int input;
        cin >> input;
        if (!input) {
            cout << "输入无效！请重新输入！" << endl;
            cout << endl;
        } else {
            auto_delete_range = input;
            break;
        }
    }
    change_auto_delete_range_file();
    if (auto_delete_range > 0) {
        cout << "已将 <{未打卡名单} 自动删除期限> 调整为 [" << auto_delete_range << "天] ，按任意键返回 [健康打卡管理菜单] ... " << endl;
    } else {
        cout << "已取消 <自动删除 {未打卡名单}> 功能！按任意键返回 [健康打卡管理菜单] ... " << endl;
    }
    _getch();
    Sleep(250);
    system("cls");
}

void daily_health_check_admin::try_to_load_auto_delete_range_file()
{
    if_auto_delete_range_file_is_empty(); // => 忽略返回值，这个同时会 确保有效化 自动删除文件
    if (if_auto_delete_range_file_empty) {
        // 自动删除期限文件 为空
        // 维持默认 => 7天
    } else {
        // 自动删除期限文件 有数据 => 读取
        // 现在文件必定存在
        fstream file;
        file.open(auto_delete_range_file_location, ios::in | ios::binary);
        if (!file.is_open()) {
            cout << "读取自动删除期限过程中，打开 auto_delete_range.dat 失败！即将自动退出程序 ... " << endl;
            Sleep(250);
            exit(-1);
        }
        file.read(reinterpret_cast<char*>(&auto_delete_range), sizeof(int));
        // 读取结束
        file.close();
    }
}

void daily_health_check_admin::make_sure_auto_delete_range_file_exists() const
{
    fstream file;
    /// now, tries to new the file
    file.open(auto_delete_range_file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预创建 auto_delete_range.dat 失败！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close(); // 及时关闭
}

bool daily_health_check_admin::if_auto_delete_range_file_is_empty()
{
    make_sure_auto_delete_range_file_exists(); // 确保文件正常的产生
    fstream file;
    file.open(auto_delete_range_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 auto_delete_range.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    auto* auto_delete_range_checker = new int;
    bool if_empty = true;
    while (file.read(reinterpret_cast<char*>(auto_delete_range_checker), sizeof(int))) {
        if_empty = false;
        break;
    }
    file.close();
    delete auto_delete_range_checker;
    auto_delete_range_checker = nullptr;
    if_auto_delete_range_file_empty = if_empty;
    return if_empty;
}

daily_health_check_admin::daily_health_check_admin()
    : daily_health_check("flag")
{
    system("cls");
    // 初始化
    if_have_unchecked_all = false;
    if_have_unchecked_only_necessary = false;
    if_auto_delete_range_file_empty = false;
    status_of_if_need_to_check = false;
    auto_delete_range = 7; // 自动删除期限默认为7天
    // 根据当天日期 设定正确的 未打卡名单 文件名
    today_unchecked_file_location += current_time.time_str();
    today_unchecked_file_location += ".txt";
    temp_today_unchecked_file_location += current_time.time_str();
    temp_today_unchecked_file_location += ".txt";
    // 自动读取 自动删除期限
    try_to_load_auto_delete_range_file();
    cout << "已加载 自动删除期限！" << endl;
    // 自动删除 过期的 未打卡用户列表
    auto_delete();
    // 自动更新 强制健康打卡 状态
    try_to_load_check_status_file();
    cout << "已加载 是否强制健康打卡 相关状态！" << endl;
    // 自动更新 健康打卡 文件
    update_health_check_file();
    // 给出提示
    cout << "已更新 包含所有用户的 <健康打卡列表> ！即将进入 [健康打卡管理界面] ... " << endl;
    Sleep(250);
}

daily_health_check_admin::~daily_health_check_admin()
{
    /*
     * Nothing to do!
     * 'Cause this destructor will call the one of base class,
     * which will free all ptr_var-allocated space in the heap
     */
}

inline void daily_health_check_admin::change_auto_delete_range_file()
{
    fstream file;
    file.open(auto_delete_range_file_location, ios::out | ios::binary | ios::in);
    // out，in 一块用 => 防止删除数据
    // ios::app => 打开文件，用于在其尾部添加数据。如果文件不存在，则新建该文件
    if (!file.is_open()) {
        // 现在一定存在这个文件，打不开就是失败
        cout << "无法打开 auto_delete_range.dat！即将自动退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.write(reinterpret_cast<char*>(&auto_delete_range), sizeof(int));
    file.close();
}

void daily_health_check_admin::switch_status_of_check()
{
    show_status_of_check();
    cout << "是否切换状态？(输入Y/y以切换，输入其他任意非空字符则不切换) >> ";
    string flag;
    cin >> flag;
    if (flag == "y" || flag == "Y") {
        if (status_of_if_need_to_check) {
            status_of_if_need_to_check = false;
            cout << "状态已切换为 => <不需要> 进行每日健康打卡！";
        } else {
            status_of_if_need_to_check = true;
            cout << "状态已切换为 => <需要> 进行每日健康打卡！";
        }
        change_all_status_in_daily_check_file(); // 更改每个用户的 强制打卡状况
    } else {
        cout << "未切换状态！";
    }
    cout << endl;
    cout << "即将返回 [功能菜单] ... " << endl;
    Sleep(250);
}

inline void daily_health_check_admin::show_status_of_check() const
{
    cout << "当前状态为 => ";
    if (status_of_if_need_to_check) {
        cout << "<需要> 进行每日健康打卡" << endl;
    } else {
        cout << "<不需要> 进行每日健康打卡" << endl;
    }
}

void daily_health_check_admin::show_unchecked_user()
{
    cout << "输入1 => 展示“所有未打卡”的用户 || 输入其他任意非空字符 => 只展示“被强制而未打卡”的用户 >> ";
    string flag;
    cin >> flag;
    // pre-load the file
    fstream file_daily_check_list(daily_health_check_file_location, ios::binary | ios::in);
    if (!file_daily_check_list.is_open()) {
        cout << "写入文件过程中，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // pre-print the list
    cout << "开始输出名单：" << endl;
    cout << "=================================================" << endl;
    cout << "\t"
         << "姓名" << setw(18) << "学号" << endl;
    cached_health_check_info = new health_check_info;
    cached_health_check_info_tr = new health_check_info_trans;
    if (flag == "1") {
        while (file_daily_check_list.read(
            reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (!cached_health_check_info->if_checked) {
                cout << "\t";
                cout << cached_health_check_info->student_name;
                cout << setw(18);
                cout << cached_health_check_info->student_id;
                cout << endl;
            }
        }
    } else {
        while (file_daily_check_list.read(
            reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (!cached_health_check_info->if_checked && cached_health_check_info->if_check_is_necessary) {
                cout << "\t";
                cout << cached_health_check_info->student_name;
                cout << setw(18);
                cout << cached_health_check_info->student_id;
                cout << endl;
            }
        }
    }
    cout << "=================================================" << endl;
    file_daily_check_list.close();
    delete cached_health_check_info;
    delete cached_health_check_info_tr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
    cout << "名单输出完毕！按任意键返回 [健康打卡管理界面] ... " << endl;
    _getch();
    Sleep(250);
}

void daily_health_check_admin::generate_unchecked_user_list()
{
    // 这次必须是 “文件格式保存了” => 因为要有“可读性”，且这个文件恰好没有“隐私性”
    cout << "输入1 => 生成“所有未打卡”用户的名单 || 输入其他任意非空字符 => 只生成“被强制而未打卡”用户的名单 >> ";
    string flag;
    cin >> flag;
    // pre-load the file
    fstream file_daily_check_list(daily_health_check_file_location, ios::in | ios::binary);
    if (!file_daily_check_list.is_open()) {
        cout << "写入文件过程中，打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    fstream file_unchecked_list(today_unchecked_file_location, ios::out); // 这个用 out 就可以，就是要清除当前数据的
    if (!file_daily_check_list.is_open()) {
        cout << "写入文件过程中，打开 unchecked_list_XXXX-XX-XX.txt 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    // start generate the new file
    cached_health_check_info = new health_check_info;
    cached_health_check_info_tr = new health_check_info_trans;
    if (flag == "1") {
        file_unchecked_list << current_time.time_str() << " 所有未打卡的 用户名单：" << endl
                            << endl;
        file_unchecked_list << "=================================================" << endl;
        file_unchecked_list << "\t"
                            << "姓名" << setw(18) << "学号" << endl;
        while (file_daily_check_list.read(
            reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (!cached_health_check_info->if_checked) {
                file_unchecked_list << "\t";
                file_unchecked_list << cached_health_check_info->student_name;
                file_unchecked_list << setw(18);
                file_unchecked_list << cached_health_check_info->student_id;
                file_unchecked_list << endl;
            }
        }
        file_unchecked_list << "=================================================";
    } else {
        file_unchecked_list << current_time.time_str() << " 被强制，但未打卡的 用户名单：" << endl
                            << endl;
        file_unchecked_list << "=================================================" << endl;
        file_unchecked_list << "\t"
                            << "姓名" << setw(18) << "学号" << endl;
        while (file_daily_check_list.read(
            reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
            *cached_health_check_info = *cached_health_check_info_tr;
            if (!cached_health_check_info->if_checked && cached_health_check_info->if_check_is_necessary) {
                file_unchecked_list << "\t";
                file_unchecked_list << cached_health_check_info->student_name;
                file_unchecked_list << setw(18);
                file_unchecked_list << cached_health_check_info->student_id;
                file_unchecked_list << endl;
            }
        }
        file_unchecked_list << "=================================================";
    }
    file_unchecked_list.close();
    file_daily_check_list.close();
    delete cached_health_check_info;
    delete cached_health_check_info_tr;
    cached_health_check_info = nullptr;
    cached_health_check_info_tr = nullptr;
    cout << "已生成 相应的 未打卡用户名单！按任意键返回 [健康打卡管理界面] ... " << endl;
    _getch();
    Sleep(250);
}

void daily_health_check_admin::shell_of_nat_admin()
{
    // 管理界面
    cout << endl;
    cout << "欢迎进入 [健康打卡 <管理员端>]！下面即将展示 [功能菜单] ... " << endl;
    Sleep(250);
    while (true) {
        cout << endl;
        cout << "健康打卡 <管理员端> [功能菜单] ... " << endl;
        cout << "============================================" << endl;
        cout << "\t"
             << "1. 查看当前 <是否强制所有用户每日健康打卡> 状态" << endl;
        cout << "\t"
             << "2. 切换 <是否强制所有用户每日健康打卡> 状态" << endl;
        cout << "\t"
             << "3. 查看当天未打卡用户" << endl;
        cout << "\t"
             << "4. 生成当天未打卡用户列表" << endl;
        cout << "\t"
             << "5. 手动更新健康打卡文件" << endl;
        cout << "\t"
             << "6. 修改 <自动删除未打卡用户列表> 的期限 (默认为7天(含)前)" << endl;
        cout << "\t"
             << "7. 查看当天 <健康风险用户列表> (可生成文件)" << endl;
        cout << "\t"
             << "8. 查询特定用户的打卡状态(通过学号查询)(可展示其打卡细节)" << endl;
        cout << "\t"
             << "9. 再次显示 [功能菜单]" << endl;
        cout << "\t"
             << "10. 退出管理界面" << endl;
        cout << "============================================" << endl;
        cout << "请输入您的选择 >> ";
        string flag;
        cin >> flag;
        cout << endl;
        if (flag == "1") {
            show_status_of_check();
        } else if (flag == "2") {
            switch_status_of_check();
        } else if (flag == "3") {
            show_unchecked_user();
        } else if (flag == "4") {
            generate_unchecked_user_list();
        } else if (flag == "5") {
            cout << "按下任意键后，开始<手动更新>健康打卡文件 ... " << endl;
            _getch();
            update_health_check_file();
            Sleep(250);
            cout << "已完成 <健康打卡文件 的 手动更新>！即将回到 [功能菜单] ... " << endl;
        } else if (flag == "6") {
            change_auto_delete_range();
        } else if (flag == "9") {
            cout << "即将再次展示 [功能菜单] ... " << endl;
            Sleep(250);
        } else if (flag == "10") {
            cout << "收到！即将返回 [管理员菜单] ... " << endl;
            Sleep(350);
            system("cls");
            break;
        } else if (flag == "7") {
            // TODO: 查看当天 <风险用户列表> (可生成文件)
            show_user_in_danger_today();
        } else if (flag == "8") {
            // TODO: 查询特定用户的打卡状态(通过学号查询)(可展示其打卡细节)
            show_check_status_of_input_user();
        } else {
            cout << "功能未开发！即将重新返回 [功能菜单] ... " << endl;
            Sleep(250);
        }
    }
}

void daily_health_check_admin::show_user_in_danger_today()
{
    // search in binary file and fill the vector
    vector<user_in_danger_template> list_of_user_in_danger {};
    fstream file(daily_health_check_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    cached_health_check_info_tr = new health_check_info_trans;
    cached_health_check_info = new health_check_info;
    while (file.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
        *cached_health_check_info = *cached_health_check_info_tr;
        const auto& ref = cached_health_check_info;
        if (ref->if_checked) {
            string temp_danger_code;
            if (ref->if_temperature_higher_than_37) {
                temp_danger_code += "a";
            }
            if (ref->if_passed_by_high_risk_regions) {
                temp_danger_code += "b";
            }
            if (ref->if_passed_by_medium_risk_regions) {
                temp_danger_code += "c";
            }
            if (ref->if_go_abroad) {
                temp_danger_code += "d";
            }
            if (!temp_danger_code.empty()) {
                user_in_danger_template current(ref->student_id, ref->student_name, temp_danger_code);
                list_of_user_in_danger.push_back(current);
            }
        }
    }
    file.close();
    delete cached_health_check_info;
    delete cached_health_check_info_tr;
    cached_health_check_info_tr = nullptr;
    cached_health_check_info = nullptr;
    // if_list_empty
    if (list_of_user_in_danger.empty()) {
        cout << "今天并没有 {健康状态存在风险的用户}！按下任意键后，回到上一级菜单" << endl;
        _getch();
        return;
    }
    // show
    time_manager today;
    cout << "本名单生成于 " << today << endl;
    cout << endl;
    cout << "接下来，将会从 {已完成今日健康打卡} 的用户中，提取出 {健康状态存在风险的用户} ... " << endl;
    cout << endl;
    cout << "在这之前，请先阅读 {风险代号} 规则 >> " << endl;
    cout << "\t"
         << "a = 体温高于37摄氏度" << endl;
    cout << "\t"
         << "b = 14天内途径 高风险地区 并停留超过24小时" << endl;
    cout << "\t"
         << "c = 14天内途径 中风险地区 并停留超过24小时" << endl;
    cout << "\t"
         << "d = 近14天有外国旅居史" << endl;
    cout << "\t"
         << "(出于时间原因未匹配的规则 => e = 自身健康状况良好，但是舍友存在上述四种情况之一)" << endl;
    cout << "风险代号是一个1~4位的数字串，只要含有上述任一字母就说明，该用户存在对应的风险" << endl;
    cout << endl;
    cout << "下面是 提取出的 {健康状态存在风险的用户} 名单:" << endl;
    cout << "======================================================================" << endl;
    cout << "\t"
         << "学号" << setw(14) << "姓名" << setw(14) << "风险代号" << endl;
    cout << endl;
    for (const auto& user : list_of_user_in_danger) {
        cout << "\t"
             << user.sno << setw(14) << user.name << setw(14) << user.danger_code << endl;
    }
    cout << "======================================================================" << endl;
    cout << "提取完毕！";
    cout << endl;
    cout << "请问是否需要生成对应的文件呢？需要则输入Y/y，否则输入任意非空字符(随后返回上一级菜单)";
    cout << ">>";
    string flag;
    cin >> flag;
    if (flag == "y" || flag == "Y") {
        // TODO: generate file [need to add a new function]
        generate_file_of_user_in_danger_today(list_of_user_in_danger);
    }
}

void daily_health_check_admin::show_check_status_of_input_user()
{
    cout << "为了提高查询准确率，现只提供 >> 学号精确查询 << 模式" << endl;
    Sleep(250);
    string temp_sno;
    cout << "请输入待查询的学号 >> ";
    cin >> temp_sno;
    // TODO: open binary file and then check & load
    fstream file(daily_health_check_file_location, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "打开 daily_health_check_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    bool if_found_user = false;
    cached_health_check_info_tr = new health_check_info_trans;
    cached_health_check_info = new health_check_info;
    while (file.read(reinterpret_cast<char*>(cached_health_check_info_tr), sizeof(health_check_info_trans))) {
        *cached_health_check_info = *cached_health_check_info_tr;
        const auto& ref = cached_health_check_info;
        if (ref->student_id == temp_sno) {
            if_found_user = true;
            break;
        }
    }
    file.close();
    delete cached_health_check_info_tr;
    cached_health_check_info_tr = nullptr;
    if (!if_found_user) {
        delete cached_health_check_info;
        cached_health_check_info = nullptr;
        cout << "文件中没有与 " << temp_sno << " 相关的记录！按任意键返回上一级菜单 ..." << endl;
        _getch();
        return;
    }
    // TODO: SHOW
    cout << "匹配到了学号！按任意键后展示 该用户的 当日健康打卡状态 ... " << endl;
    _getch();
    cout << endl;
    cout << "=======================================================" << endl;
    cout << "\t"
         << "用户名： " << cached_health_check_info->account_id << endl;
    cout << "\t"
         << "姓名： " << cached_health_check_info->student_name << endl;
    cout << "\t"
         << "学号： " << cached_health_check_info->student_id << endl;
    cout << "\t"
         << "是否被强制打卡： "
         << daily_health_check_user::trans_bool(cached_health_check_info->if_check_is_necessary) << endl;
    cout << "\t"
         << "是否完成打卡： "
         << daily_health_check_user::trans_bool(cached_health_check_info->if_checked) << endl;
    cout << "\t"
         << "是否已经返校： "
         << daily_health_check_user::trans_bool(cached_health_check_info->if_returned_school) << endl;
    cout << "\t"
         << "是否住校： "
         << daily_health_check_user::trans_bool(cached_health_check_info->if_is_accommodated) << endl;
    cout << "\t"
         << "近14天是否在 高风险地区 停留超过1天： "
         << daily_health_check_user::trans_bool(cached_health_check_info->if_passed_by_high_risk_regions) << endl;
    cout << "\t"
         << "近14天是否在 中风险地区 停留超过1天： "
         << daily_health_check_user::trans_bool(cached_health_check_info->if_passed_by_medium_risk_regions) << endl;
    cout << "\t"
         << "当天最高体温是否超过 37摄氏度： "
         << daily_health_check_user::trans_bool(cached_health_check_info->if_temperature_higher_than_37) << endl;
    cout << "\t"
         << "近14天是否有 外国旅居史： "
         << daily_health_check_user::trans_bool(cached_health_check_info->if_go_abroad) << endl;
    cout << "=======================================================" << endl;
    cout << "显示完毕！" << endl
         << endl;
    delete cached_health_check_info;
    cached_health_check_info = nullptr;
    cout << "按任意键返回 上一级菜单 ... " << endl;
    _getch();
}

void daily_health_check_admin::generate_file_of_user_in_danger_today(const vector<user_in_danger_template>& input)
{
    const string file_path = R"(C:\Users\edwar\Desktop\cpp_final_task\file_of_user_in_danger.txt)";
    fstream file(file_path, ios::out);
    if (!file.is_open()) {
        cout << "未能创建 file_of_user_in_danger.txt！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    time_manager today;
    file << "本名单生成于 " << today << endl;
    file << endl;
    file << "接下来，将会从 {已完成今日健康打卡} 的用户中，提取出 {健康状态存在风险的用户} ... " << endl;
    file << endl;
    file << "在这之前，请先阅读 {风险代号} 规则 >> " << endl;
    file << "\t"
         << "a = 体温高于37摄氏度" << endl;
    file << "\t"
         << "b = 14天内途径 高风险地区 并停留超过24小时" << endl;
    file << "\t"
         << "c = 14天内途径 中风险地区 并停留超过24小时" << endl;
    file << "\t"
         << "d = 近14天有外国旅居史" << endl;
    file << "\t"
         << "(出于时间原因未匹配的规则 => e = 自身健康状况良好，但是舍友存在上述四种情况之一)" << endl;
    file << "风险代号是一个1~4位的数字串，只要含有上述任一字母就说明，该用户存在对应的风险" << endl;
    file << endl;
    file << "下面是 提取出的 {健康状态存在风险的用户} 名单:" << endl;
    file << "======================================================================" << endl;
    file << "\t"
         << "学号" << setw(14) << "姓名" << setw(14) << "风险代号" << endl;
    file << endl;
    for (const auto& user : input) {
        file << "\t"
             << user.sno << setw(14) << user.name << setw(14) << user.danger_code << endl;
    }
    file << "======================================================================" << endl;
    file << "提取完毕！";
    file.close();
    cout << "已经成功的在 "
         << R"(C:\Users\edwar\Desktop\cpp_final_task\)"
         << " 中生成了 "
         << "file_of_user_in_danger.txt！按任意键返回 上一级菜单 ..." << endl;
    _getch();
}
