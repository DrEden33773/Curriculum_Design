#pragma once

#include <string>
using namespace std;

class user_interface {
protected:
    string c_account;
    string real_name;
    string student_number;
    string dorm_number;
    inline void show_current_user_info() const; // չʾ��ǰ�û���Ϣ
    inline void goto_daily_check() const; // ǰ��ÿ�մ�
    inline void goto_nat_check() const; // ǰ��������
    inline void goto_necessary_affairs_check(const bool&) const; // ǰ�������������ƽ̨[��ָ���Ƿ�ߴ����]

public:
    user_interface() = default; // �չ��캯��
    user_interface(const string&, const string&, const string&, const string&); // �湹�캯��
    void shell_of_user_interface() const; //
    string return_c_account();
    string return_real_name();
    string return_student_number();
};
