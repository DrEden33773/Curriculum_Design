#define _CRT_SECURE_NO_WARNINGS
#include "time_manager.h"
#include <ctime>
#include <iomanip>
using namespace std;

bool time_manager::if_date_valid(const time_manager* input)
{
    bool if_year_valid = false;
    bool if_month_valid = false;
    bool if_day_valid = false;
    if (input->dtime_.year >= 0) {
        if_year_valid = true;
    }
    if (input->dtime_.month >= 1 && input->dtime_.month <= 12) {
        if_month_valid = true;
        if (input->dtime_.month == 1 ||
            input->dtime_.month == 3 ||
            input->dtime_.month == 5 ||
            input->dtime_.month == 7 ||
            input->dtime_.month == 8 ||
            input->dtime_.month == 10 ||
            input->dtime_.month == 12) {
            if (input->dtime_.day >= 0 && input->dtime_.day <= 31) {
                if_day_valid = true;
            }
        } else if (input->dtime_.month == 2) {
            if (if_leap_year_in_class(input)) {
                if (input->dtime_.day >= 0 && input->dtime_.day <= 29) {
                    if_day_valid = true;
                }
            } else {
                if (input->dtime_.day >= 0 && input->dtime_.day <= 28) {
                    if_day_valid = true;
                }
            }
        } else {
            if (input->dtime_.day >= 0 && input->dtime_.day <= 30) {
                if_day_valid = true;
            }
        }
    }
    return if_day_valid && if_year_valid && if_month_valid;
}

bool time_manager::if_leap_year_in_class(const time_manager* input)
{
    const bool status_1 = input->dtime_.year % 4 == 0 && input->dtime_.year % 100 != 0;
    const bool status_2 = input->dtime_.year % 400 == 0;
    return status_1 || status_2;
}

bool if_leap_year(const int& year)
{
    const bool status_1 = year % 4 == 0 && year % 100 != 0;
    const bool status_2 = year % 400 == 0;
    return status_1 || status_2;
}

bool time_manager::if_reach_the_end_of_month(const time_manager* input)
{
    bool result;
    if (input->dtime_.month == 1 || input->dtime_.month == 3 || input->dtime_.month == 5 || input->dtime_.month == 7 || input->dtime_.month == 8 || input->dtime_.month == 10 || input->dtime_.month == 12) {
        result = input->dtime_.day == 31 ? true : false;
    } else if (input->dtime_.month == 2) {
        if (if_leap_year_in_class(input)) {
            result = input->dtime_.day == 29 ? true : false;
        } else {
            result = input->dtime_.day == 28 ? true : false;
        }
    } else {
        result = input->dtime_.day == 30 ? true : false;
    }
    return result;
}

bool time_manager::if_reach_the_end_of_year(const time_manager* input)
{
    const bool result = input->dtime_.month == 12 && input->dtime_.day == 31 ? true : false;
    return result;
}

bool time_manager::if_reach_the_start_of_month(const time_manager* input)
{
    const bool result = input->dtime_.day == 1 ? true : false;
    return result;
}

bool time_manager::if_reach_the_start_of_year(const time_manager* input)
{
    const bool result = input->dtime_.month == 1 && input->dtime_.day == 1 ? true : false;
    return result;
}

time_manager time_manager::update_date()
{
    if (if_reach_the_end_of_month(this)) {
        if (if_reach_the_end_of_year(this)) {
            this->dtime_.day = 1;
            this->dtime_.month = 1;
            ++this->dtime_.year;
        } else {
            this->dtime_.day = 1;
            ++this->dtime_.month;
        }
    } else {
        ++this->dtime_.day;
    }
    return *this;
}

time_manager time_manager::update_date_minus()
{
    if (if_reach_the_start_of_month(this)) {
        if (if_reach_the_start_of_year(this)) {
            this->dtime_.day = 1;
            this->dtime_.month = 1;
            --this->dtime_.year;
        } else {
            this->dtime_.day = 1;
            --this->dtime_.month;
        }
    } else {
        --this->dtime_.day;
    }
    return *this;
}

void time_manager::sync_system_time()
// ��л "����̳�" ���ľ�Ʒʾ��������ر�����ݺݵذ�ס�ˣ�
{
    // ͬ��ϵͳʱ��
    const time_t now = time(nullptr); // ���ڵ�ǰϵͳ�ĵ�ǰ����/ʱ��
    // cout << "1970 ��Ŀǰ��������:" << now << endl;
    const tm* ltm = localtime(&now);
    // ��� tm �ṹ�ĸ�����ɲ���
    // cout << "��: " << 1900 + ltm->tm_year << endl;
    // cout << "��: " << 1 + ltm->tm_mon << endl;
    // cout << "��: " << ltm->tm_mday << endl;
    // cout << "ʱ��: " << ltm->tm_hour << ":";
    // cout << ltm->tm_min << ":";
    // cout << ltm->tm_sec << endl;
    this->dtime_.year = 1900 + ltm->tm_year;
    this->dtime_.month = 1 + ltm->tm_mon;
    this->dtime_.day = ltm->tm_mday;
    // �Ƚ����׵�һ����������Ϊctime��ͷ�ļ��Ƚ�����
}

string time_manager::time_str() const
{
    char res[10]{}; // Ԥ�Ƶ������ʽ => 2022-04-08
    // for (char i : res) {
    //     i = '\0';
    // }
    char temp[8]{}; // 80402202 need to be reversed
    // for (char i : temp) {
    //     i = '\0';
    // }
    char revd[8]{}; // reversed to 20220408
    // for (char i : revd) {
    //     i = '\0';
    // }

    // tnum
    int tnum = dtime_.year * 10000 + dtime_.month * 100 + dtime_.day;
    // push into temp
    for (char& i : temp) {
        // һ��Ҫд�� ���ø�ʽ�������޸���Ч
        i = tnum % 10 + '0';
        tnum /= 10;
    }

    int pos, pos_rev, pos_res;

    // push into revd
    for (pos = 7, pos_rev = 0; pos >= 0; --pos, ++pos_rev) {
        revd[pos_rev] = temp[pos];
    }
    // push into res
    for (pos_rev = 0, pos_res = 0; pos_rev < 4; ++pos_rev, ++pos_res) {
        res[pos_res] = revd[pos_rev];
    }
    res[pos_res++] = '-';
    for (; pos_rev < 6; ++pos_rev, ++pos_res) {
        res[pos_res] = revd[pos_rev];
    }
    res[pos_res++] = '-';
    for (; pos_rev < 8; ++pos_rev, ++pos_res) {
        res[pos_res] = revd[pos_rev];
    }
    const string result = res;
    string final_result = result.substr(0, 10);
    return final_result;
}

time_manager::time_manager()
{
    // dtime_ = new defined_time;
    //�޲� => ֱ��ͬ��ϵͳʱ��
    sync_system_time();
}

// ���ڳ�ʼ��
time_manager::time_manager(const int& year, const int& month, const int& day)
{
    // dtime_ = new defined_time;
    this->dtime_.year = year;
    this->dtime_.month = month;
    this->dtime_.day = day;
}

time_manager::time_manager(const time_manager& input)
{
    // dtime_ = new defined_time;
    this->dtime_.year = input.dtime_.year;
    this->dtime_.month = input.dtime_.month;
    this->dtime_.day = input.dtime_.day;
}

time_manager::time_manager(const time_manager* input)
{
    // dtime_ = new defined_time;
    this->dtime_.year = input->dtime_.year;
    this->dtime_.month = input->dtime_.month;
    this->dtime_.day = input->dtime_.day;
}

void time_manager::operator=(const time_manager& input)
{
    this->dtime_.year = input.dtime_.year;
    this->dtime_.month = input.dtime_.month;
    this->dtime_.day = input.dtime_.day;
}

time_manager time_manager::operator+=(const int& n)
{
    for (int i = 0; i < n; ++i) {
        update_date();
    }
    return *this;
}

time_manager time_manager::operator-=(const int& n)
{
    for (int i = 0; i < n; ++i) {
        update_date_minus();
    }
    return *this;
}

time_manager time_manager::operator++()
// ++time_manager
{
    return update_date();
}

time_manager time_manager::operator--()
{
    return update_date_minus();
}

time_manager time_manager::operator++(int any)
// time_manager++
{
    const time_manager result = *this;
    update_date(); // update ���ո��ĵ� ֻ�� this ָ��� [��ǰ����]
    // �������� result ������ *this �����ã��޷������ģ���˷��ص���δ������֮ǰ�� [����]
    // ���ǡ�÷��� ����++ �� ԭ����˼
    return result;
}

time_manager time_manager::operator--(int any)
{
    time_manager result = *this;
    update_date_minus();
    return result;
}

int operator-(const time_manager& date1, const time_manager& date2)
{
    // ��ʱ, ������֤������Ч�� [���е����ڣ�����ͬ��ϵͳʱ��ģ���Ȼ����Ч��]

    // �������
    if (date1 == date2) {
        return 0;
    }
    bool if_result_smaller_than_zero = false;
    time_manager big, small;
    int result = 0;
    // ӳ���С��ϵ
    if (date1 > date2) {
        big = date1;
        small = date2;
        if_result_smaller_than_zero = false;
    } else {
        big = date2;
        small = date1;
        if_result_smaller_than_zero = true;
    }
    /* ------------------------CORE------------------------ */
    // �������
    for (int i = small.dtime_.year; i < big.dtime_.year; ++i) {
        if (if_leap_year(i)) {
            result += 366;
        } else {
            result += 365;
        }
    }
    // ����� ���� ����
    for (int i = 1; i < big.dtime_.month; ++i) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            result += 31;
        } else if (i == 2) {
            result += if_leap_year(big.dtime_.year) ? 29 : 28;
        } else {
            result += 30;
        }
    }
    // ����� С�� ����
    for (int i = 1; i < small.dtime_.month; ++i) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            result -= 31;
        } else if (i == 2) {
            result -= if_leap_year(small.dtime_.year) ? 29 : 28;
        } else {
            result -= 30;
        }
    }
    result += big.dtime_.day;
    result -= small.dtime_.day;
    /* ------------------------END OF CORE------------------------ */
    result = if_result_smaller_than_zero ? -1 * result : 1 * result;
    return result;
}

bool operator==(const time_manager& a, const time_manager& b)
{
    const bool result = a.dtime_.year == b.dtime_.year && a.dtime_.month == b.dtime_.month && a.dtime_.day == b.dtime_.day;
    return result;
}

bool operator>(const time_manager& a, const time_manager& b)
{
    bool result = false;
    if (a.dtime_.year > b.dtime_.year) {
        result = true;
    } else if (a.dtime_.month > b.dtime_.month) {
        result = true;
    } else if (a.dtime_.day > b.dtime_.day) {
        result = true;
    } else {
        result = false;
    }
    return result;
}

bool operator<(const time_manager& a, const time_manager& b)
{
    bool result = false;
    if (a.dtime_.year < b.dtime_.year) {
        result = true;
    } else if (a.dtime_.month < b.dtime_.month) {
        result = true;
    } else if (a.dtime_.day < b.dtime_.day) {
        result = true;
    } else {
        result = false;
    }
    return result;
}

ostream& operator<<(ostream& out, const time_manager& t)
{
    out << t.dtime_.year << "��" << t.dtime_.month << "��" << t.dtime_.day << "��";
    return out;
}
