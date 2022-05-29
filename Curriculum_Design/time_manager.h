#pragma once

#include <iostream>
using namespace std;

class time_manager {
private:
    class defined_time {
    public:
        int year {};
        int month {};
        int day {};
    };
    defined_time dtime_; // �ӷ�װ

protected:
    static bool if_leap_year_in_class(const time_manager*); // �ж��Ƿ�Ϊ����
    static bool if_reach_the_end_of_month(const time_manager*); // if reach the end of month, return true
    static bool if_reach_the_end_of_year(const time_manager*); // if reach the end of year, return true
    static bool if_reach_the_start_of_month(const time_manager*); // if reach the start of month, return true
    static bool if_reach_the_start_of_year(const time_manager*); // if reach the start of year, return true
    time_manager update_date(); // ��������--�����һ��
    time_manager update_date_minus(); // ��������--��ǰ��һ��
    void sync_system_time(); // ͬ��ϵͳʱ��

public:
    static bool if_date_valid(const time_manager*); // ������Ч����֤
    time_manager(); // �޲������ => ͬ��ϵͳʱ��
    time_manager(const int&, const int&, const int&); // ���ڳ�ʼ������
    time_manager(const time_manager&);
    time_manager(const time_manager*);
    void operator=(const time_manager&);
    friend int operator-(const time_manager&, const time_manager&); // ����������֮�� [��������]
    time_manager operator+=(const int&); // ���������n��
    time_manager operator-=(const int&); // ������ǰ��n��
    time_manager operator++(); // ǰ��++
    time_manager operator--(); // ǰ��--
    time_manager operator++(int); // ����++
    time_manager operator--(int); // ����--
    friend bool operator==(const time_manager&, const time_manager&); // �Ƚ��������Ƿ����
    friend bool operator>(const time_manager&, const time_manager&); // �Ƚ������ڴ�С(�ȴ�)
    friend bool operator<(const time_manager&, const time_manager&); // �Ƚ������ڴ�С(��С)
    friend ostream& operator<<(ostream&, const time_manager&); // �������
    string time_str() const; // ת�����ַ���ʽ
};
