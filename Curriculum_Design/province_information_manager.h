#pragma once

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class province_information_manager {
private:
    string province_list[34] = { // 位置 和 省份 的 对应关系 需要用
        "北京",
        "天津",
        "上海",
        "重庆",
        "河北",
        "山西",
        "辽宁",
        "吉林",
        "黑龙江",
        "江苏",
        "浙江",
        "安徽",
        "福建",
        "江西",
        "山东",
        "河南",
        "湖北",
        "湖南",
        "广东",
        "海南",
        "四川",
        "贵州",
        "云南",
        "陕西",
        "甘肃",
        "青海",
        "台湾",
        "内蒙古",
        "广西",
        "宁夏",
        "新疆",
        "西藏",
        "香港",
        "澳门"
    };
    int status_of_province[34] = { 0 }; // 省份状态 -- 0=低风险 1=中风险 2=高风险
    string status_list[3] = { "低风险", "中风险", "高风险" };
    string province_file = R"(C:\Users\edwar\Desktop\cpp_final_task\province_information.dat)";

public:
    province_information_manager();
    void try_to_load_province_information_file(); // 预加载文件
    void write_province_information_file_trunc(); // 写入文件
    void change_province_status(); // 更改省级区域防疫状态
    void show_all_province_status(); // 显示所有省级区域防疫状态
    void show_input_province_status(); // 显示输入区域的防疫状态
    auto if_input_province_valid(const string&) -> int; // 省份有效性检验 [无效返回-1，有效返回 下标]
    void show_high_and_medium_risk_regions(); // 提示 高中风险 地区
    auto if_have_high_and_medium_risk_regions() -> bool; // 有无高中风险区
};