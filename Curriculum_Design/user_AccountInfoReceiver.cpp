// 重构完成

#define _CRT_SECURE_NO_WARNINGS
#include "user_AccountInfoReceiver.h"
#include <Windows.h> // Sleep() 使用
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

user_info_receiver::user_info_receiver(const string& input_account)
{
    if_user_list_empty = true;
    cu_info = nullptr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    const string& trans_account = input_account;
    user_import_from_login_interface(trans_account);
    user_list_file_empty_check();
    if (!if_user_list_empty) {
        try_to_load_user_file(trans_account);
    }
    ask_to_set_user_info();
}

user_info_receiver::user_info_receiver() // 无参构造函数
{
    if_user_list_empty = true;
    cu_info = nullptr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    user_list_file_empty_check();
}

inline void user_info_receiver::user_import_from_login_interface(const string& input_account)
{
    cu_info = new current_user_info; // 别忘了申请空间
    cu_info->c_account = input_account;
    cu_info->if_first_use = true; // 初始化 是否第一次使用
    // 不要释放cu_info的空间，后面用
}

bool user_info_receiver::if_sno_already_exists(const string& input_sno)
{
    const string user_list_file_location_ = R"(C:\Users\edwar\Desktop\cpp_final_task\user_list.dat)";
    bool result = false;
    cu_cache = new current_user_info;
    cu_cache_tr = new current_user_info_tr;
    fstream file(user_list_file_location_, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "预加载 user_list_file.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
    file.open(user_list_file_location_, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "预加载 user_list_file.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    while (file.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
        *cu_cache = *cu_cache_tr;
        if (cu_cache->student_number == input_sno) {
            result = true;
            break;
        }
    }
    file.close();
    delete cu_cache;
    delete cu_cache_tr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    return result;
}

void user_info_receiver::initialize_user_list_file() const
{
    fstream file;
    file.open(file_location, ios::binary | ios::app);
    if (!file.is_open()) {
        cout << "预加载时，打开 user_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.close();
}

void user_info_receiver::user_list_file_empty_check()
{
    // 判断 user_list.dat 是否为空
    // 采用新方法，不必读取一次文件，直接判断文件是否为空
    initialize_user_list_file();
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "预加载时，打开 user_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    }
    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        if_user_list_empty = true;
    } else {
        if_user_list_empty = false;
    }
    file.close();
}

void user_info_receiver::try_to_load_user_file(const string& correct_account)
{
    cu_cache_tr = new current_user_info_tr;
    fstream file;
    file.open(file_location, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "打开 user_list.dat 失败！即将退出程序 ... " << endl;
        Sleep(250);
        exit(-1);
    } else {
        while (file.read(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr))) {
            if (strcmp(cu_cache_tr->c_account, correct_account.c_str()) == 0) {
                cu_cache = new current_user_info(cu_cache_tr); // copy constructor
                cu_info->real_name = cu_cache->real_name;
                cu_info->student_number = cu_cache->student_number;
                cu_info->dorm_number = cu_cache->dorm_number;
                cu_info->if_first_use = false;
                break;
            }
        }
    }
    delete cu_cache; // 解除缓存 cu_cache
    delete cu_cache_tr; // 解除缓存 cu_cache_tr
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
    // 但是不要解除 主存储变量 cu_info
}

void user_info_receiver::ask_to_set_user_info()
{
    if (cu_info->if_first_use) {
        while (true) {
            cout << "第一次使用 "
                 << cu_info->c_account
                 << " 这个账号，稍等片刻，请按照提示填入真实且正确的信息："
                 << endl;
            cout << "请注意，输入个人信息后，您将无权更改个人信息(仅有管理员有此权限)" << endl;
            Sleep(1000);
            cout << endl;
            //变量池
            string temp_name, temp_name_check;
            string temp_sno, temp_sno_check;
            string temp_dorm_no, temp_dorm_no_check;
            bool if_back_to_first_step_when_name_conflict;
            bool if_back_to_first_step_when_sno_conflict;
            bool if_back_to_first_step_when_dorm_no_conflict;
            //输入姓名
            while (true) {
                cout << "请输入您的真实姓名 (只接受16位以内的输入)：";
                cin >> temp_name;
                if (temp_name.size() > 16)
                    temp_name.erase(temp_name.begin() + 16, temp_name.end());
                while (true) {
                    char temp_flag;
                    cout << "请再次输入您 (刚刚输入) 的真实姓名 (只接受16位以内的输入)：";
                    cin >> temp_name_check;
                    if (temp_name_check.size() > 16)
                        temp_name_check.erase(temp_name_check.begin() + 16, temp_name_check.end());
                    if (temp_name_check == temp_name) {
                        if_back_to_first_step_when_name_conflict = false;
                        break;
                    } else {
                        cout << "两次输入的姓名不同" << endl
                             << "输入A/a -> 再次输入最初输入的姓名 || "
                             << "输入其他内容 -> 重新指定姓名 >>> ";
                        cin >> temp_flag;
                        if (temp_flag == 'A' || temp_flag == 'a') {
                            system("cls");
                            cout << "稍等片刻，准备 [再次输入最初输入的姓名]" << endl;
                            Sleep(1000);
                        } else {
                            system("cls");
                            cout << "稍等片刻，准备 [重新指定姓名]" << endl;
                            Sleep(1000);
                            if_back_to_first_step_when_name_conflict = true;
                            break;
                        }
                    }
                }
                if (!if_back_to_first_step_when_name_conflict) {
                    break;
                }
            }
            cout << "已成功输入 [真实姓名]，稍等片刻请输入 [学号]" << endl;
            Sleep(1000);
            cout << endl;
            //输入学号
            while (true) {
                cout << "请输入您的学号 (只接受10位数字以内的输入)：";
                cin >> temp_sno;
                if (temp_sno.size() > 10)
                    temp_sno.erase(temp_sno.begin() + 10, temp_sno.end());
                // 验证学号是否已经存在
                if (if_sno_already_exists(temp_sno)) {
                    cout << "学号已经存在！请重新输入" << endl;
                    Sleep(300);
                    continue;
                }
                while (true) {
                    char temp_flag;
                    cout << "请再次输入您 (刚刚输入) 的学号 (只接受10位数字以内的输入)：";
                    cin >> temp_sno_check;
                    if (temp_sno_check.size() > 10)
                        temp_sno_check.erase(temp_sno_check.begin() + 10, temp_sno_check.end());
                    if (temp_sno_check == temp_sno) {
                        if_back_to_first_step_when_sno_conflict = false;
                        break;
                    } else {
                        cout << "两次输入的学号不同" << endl
                             << "输入A/a -> 再次输入最初输入的学号 || "
                             << "输入其他内容 -> 重新指定学号 >>> ";
                        cin >> temp_flag;
                        if (temp_flag == 'A' || temp_flag == 'a') {
                            // system("cls");
                            cout << "稍等片刻，准备 [再次输入最初输入的学号]" << endl;
                            Sleep(1000);
                        } else {
                            // system("cls");
                            cout << "稍等片刻，准备 [重新指定学号]" << endl;
                            Sleep(1000);
                            if_back_to_first_step_when_sno_conflict = true;
                            break;
                        }
                    }
                }
                if (!if_back_to_first_step_when_sno_conflict) {
                    break;
                }
            }
            cout << "已成功输入 [学号]，稍等片刻请确认 [是否住宿]，若住宿还需输入 [宿舍号]" << endl;
            Sleep(1000);
            cout << endl;
            //输入宿舍号
            cout << "请问您当前是否住校？(Y->住校，其他字符->不住校) >>> ";
            string flag;
            cin >> flag;
            if (flag == "Y" || flag == "y") {
                while (true) {
                    cout << "请输入您目前所处的宿舍号 (只接受3位数字以内的输入)：";
                    cin >> temp_dorm_no;
                    if (temp_dorm_no.size() > 3)
                        temp_dorm_no.erase(temp_dorm_no.begin() + 3, temp_dorm_no.end());
                    while (true) {
                        char temp_flag;
                        cout << "请再次输入您 (刚刚输入) 的宿舍号 (只接受3位数字以内的输入)：";
                        cin >> temp_dorm_no_check;
                        if (temp_dorm_no_check.size() > 3)
                            temp_dorm_no_check.erase(temp_dorm_no_check.begin() + 3, temp_dorm_no_check.end());
                        if (temp_dorm_no_check == temp_dorm_no) {
                            if_back_to_first_step_when_dorm_no_conflict = false;
                            break;
                        } else {
                            cout << "两次输入的宿舍号不同" << endl
                                 << "输入A/a -> 再次输入最初输入的宿舍号 || "
                                 << "输入其他内容 -> 重新指定宿舍号 >>> ";
                            cin >> temp_flag;
                            if (temp_flag == 'A' || temp_flag == 'a') {
                                cout << endl;
                                cout << "稍等片刻，准备 [再次输入最初输入的宿舍号]" << endl;
                                Sleep(1000);
                                cout << endl;
                            } else {
                                cout << endl;
                                cout << "稍等片刻，准备 [重新指定宿舍号]" << endl;
                                Sleep(1000);
                                cout << endl;
                                if_back_to_first_step_when_dorm_no_conflict = true;
                                break;
                            }
                        }
                    }
                    if (!if_back_to_first_step_when_dorm_no_conflict) {
                        break;
                    }
                }
            } else {
                temp_dorm_no = -1; // 不住校，宿舍号，录入 -1
                cout << "由于您目前不住校，系统将自动跳过 <输入宿舍号> 环节，若之后住校，请联系管理员完善此信息！" << endl;
            }
            cout << endl;
            cout << "请 ==最后一次== 确认您输入的个人信息：" << endl
                 << endl;
            cout << "========================================================" << endl;
            cout.setf(ios::left); // 左对齐
            cout << "\t"
                 << "姓名：" << setw(12) << temp_name << endl;
            cout << "\t"
                 << "学号：" << setw(12) << temp_sno << endl;
            cout << "\t"
                 << "宿舍号：" << setw(12) << temp_dorm_no << endl;
            cout << "========================================================" << endl
                 << endl;
            cout << "是否正确？正确=>请输入Y/y || 不正确=>请输入其他任意非空字符(稍后将自动重新引导您输入姓名、学号) >>> ";
            string flag_of_flush;
            cin >> flag_of_flush;
            if (flag_of_flush == "Y" || flag_of_flush == "y") {
                // 写入结构体
                cu_info->real_name = temp_name;
                cu_info->student_number = temp_sno;
                cu_info->dorm_number = temp_dorm_no;
                // next
                system("cls");
                break;
            } else {
                cout << "请稍后，系统将自动重新引导您输入姓名、学号、宿舍号" << endl;
                Sleep(1000);
                system("cls");
            }
        }
        // 更新用户状态 -> 是否第一次使用
        cu_info->if_first_use = false;
        // 写入用户文件
        write_to_user_file();
        // end of function
        cout << "已成功输入 [个人信息]，稍等片刻将进入 <用户界面>" << endl;
        Sleep(1000);
        system("cls");
    }
}

void user_info_receiver::write_to_user_file()
{
    fstream file;
    file.open(file_location, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "写入文件时，打开 user_list.dat 失败！即将自动退出程序" << endl;
        Sleep(250);
        exit(-1);
    }
    cu_cache_tr = new current_user_info_tr(cu_info);
    file.write(reinterpret_cast<char*>(cu_cache_tr), sizeof(current_user_info_tr)); // 文件尾部 写入
    file.close();
    delete cu_cache_tr;
    cu_cache_tr = nullptr;
}

//接口函数
string user_info_receiver::return_c_account() const
{
    return cu_info->c_account;
}

string user_info_receiver::return_real_name() const
{
    return cu_info->real_name;
}

string user_info_receiver::return_student_number() const
{
    return cu_info->student_number;
}

string user_info_receiver::return_dorm_number() const
{
    return cu_info->dorm_number;
}

//析构函数
user_info_receiver::~user_info_receiver()
{
    delete cu_info;
    delete cu_cache;
    delete cu_cache_tr;
    cu_info = nullptr;
    cu_cache = nullptr;
    cu_cache_tr = nullptr;
}
