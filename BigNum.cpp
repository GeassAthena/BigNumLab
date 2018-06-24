//
// Created by 17637 on 2018/6/21.
//
#include "BigNum.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include<cmath>
#include <memory.h>
#include <algorithm>

using namespace std;

BigNum::BigNum() {
    memset(this->data, 0, sizeof(this->data));
    this->data[0] = 1;
    for (int i = 1; i < 2*N; i++) {
        this->data[i] = 0;
    }
    this->len = 0;
};
BigNum::~BigNum() = default;
BigNum::BigNum(string num_str) {
        memset(this->data, 0, sizeof(this->data));
        this->data[0] = 1;
        for (int i = 1; i < 2 * N; i++) {
            this->data[i] = 0;
        }
    for (int j = num_str.length() - 1; j >= 0; j--) {
        this->data[num_str.length() - j] = atoi(num_str.substr(j, 1).c_str());
    }
        this->len = num_str.length();
    }

long BigNum::compare(BigNum a, BigNum b) {
    if (a.data[0] == 1 && b.data[0] == 0) {
        return 1;
    } else if (a.data[0] == 0 && b.data[0] == 1) {
        return -1;
    } else if (a.data[0] == 1 && b.data[0] == 1) {
        if (a.len > b.len) {
            return 1;
        } else if (a.len < b.len) {
            return -1;
        } else {
            for (int i = a.len; i > 0; i--) {
                if (a.data[i] > b.data[i])
                    return 1;
                else if (a.data[i] < b.data[i])
                    return -1;
            }
            return 0;
        }
    } else {
        if (a.len > b.len) {
            return -1;
        } else if (a.len < b.len) {
            return 1;
        } else {
            for (int i = a.len; i > 0; i--) {
                if (a.data[i] > b.data[i])
                    return -1;
                else if (a.data[i] < b.data[i])
                    return 1;
            }
            return 0;
        }
    }
}
    //大于号判断重载
bool BigNum:: operator>(BigNum &a) {
        return compare(*this, a) == 1;
    }

    //小于号判断重载
bool BigNum:: operator<(BigNum &a) {
        return -1 == compare(*this, a);
    }

    //等于号判断重载
bool BigNum::operator==(BigNum &a) {
        return compare(*this, a) == 0;
    }

    //加法重载
const BigNum BigNum::operator+(const BigNum &b) const {
        BigNum b_temp = b;
        BigNum temp = *this;
        BigNum result;
        if (temp.data[0] == 1 && b_temp.data[0] == 1) {             //正数加正数
            int add = 0;
            int temp1;
            for (int i = 1; i <= temp.len || i < b_temp.len; i++) {
                temp1 = temp.data[i] + b_temp.data[i] + add;
                result.len++;
                result.data[result.len] = temp1 % 10;
                add = temp1 / 10;
            }
            if (add != 0) {
                result.len++;
                result.data[result.len] = add;
            }
        } else if (this->data[0] == 1 && b.data[0] == 0) {  //正数加负数
            b_temp.data[0] = 1;
            result = temp - b_temp;
        } else if (this->data[0] == 0 && b.data[0] == 1) {  //负数加正数
            temp.data[0] = 0;
            result = b_temp - temp;
        } else {                                      //负数加负数
            temp.data[0] = 1;
            b_temp.data[0] = 1;
            result = temp + b_temp;
            result.data[0] = 0;
        }
        result.resetLen();
        return result;
    }

    //减法重载
const BigNum BigNum::operator-(const BigNum &b) const {
        BigNum temp = *this;
        BigNum b_temp = b;
        BigNum result;
        //正数减去正数
        if (temp.data[0] == 1 && b_temp.data[0] == 1) {
            if (temp > b_temp) {                   //大数减去小数
                for (int i = 1; i <= temp.len; i++) {
                    if (temp.data[i] < b_temp.data[i]) {
                        temp.data[i + 1]--;
                        temp.data[i] += 10;
                    }
                    result.len++;
                    result.data[result.len] = temp.data[i] - b_temp.data[i];
                }
            } else{                       //小数减去大数转化成大数减去小数
                result = b_temp - temp;
                result.data[0] = 0;
            }

        } else if (temp.data[0] == 0 && b_temp.data[0] == 0) {            //负数减去负数
            temp.data[0] = 1;
            b_temp.data[0] = 1;
            result = temp - b_temp;
            result.data[0] = 0;
        } else if (temp.data[0] == 1 && b_temp.data[0] == 0) {    //正数减去负数
            b_temp.data[0] = 1;
            result = temp + b_temp;
        } else {                                        //负数减去正数
            temp.data[0] = 1;
            result = temp + b_temp;
            result.data[0] = 0;
        }
        result.resetLen();
        return result;
    }

    //乘法重载
const BigNum BigNum::operator*(const BigNum &b) const {
        BigNum temp = *this;
        BigNum b_temp = b;
        BigNum result;
        result.len = temp.len + b_temp.len;
        for (int i = 1; i <= temp.len; i++) {
            int temp1 = i;
            for (int j = 1; j <= b.len; j++) {
                result.data[temp1] += temp.data[i] * b_temp.data[j];
                temp1++;
            }
        }
        for (int i = 1; i < result.len; i++) {
            if (result.data[i] > 9) {
                result.data[i + 1] =  result.data[i + 1] + result.data[i] / 10;
                result.data[i] = result.data[i] % 10;
            }
        }
        //判断结果的正负
        if ((temp.data[0] == 0 && b_temp.data[0] == 1) || (temp.data[0] == 1 && b_temp.data[0] == 0)) {
            result.data[0] = 0;
        }
        result.resetLen();
        return result;
    }

    //除法重载
const BigNum BigNum::operator/(const BigNum &b) const {
        BigNum temp = *this;
        BigNum b_temp = b;
        BigNum result;
        result.len = temp.len;
        int count = 0;
        bool  isPositive = true;
        temp.data[0] = 1;
        b_temp.data[0] = 1;
        while (temp > b_temp) {
            int diff = temp.len - b_temp.len;
            if (diff >= 2) {
                BigNum temp2;
                temp2.data[diff] = 1;
                temp2.len = diff;
                BigNum temp3 = b_temp * temp2;
                temp = temp - temp3;
                result = result + temp2;
            } else {
                temp = temp - b_temp;
                count++;
            }
        }
        result.data[1] = count;
        for (int i = 1; i < result.len; i++) {
            while (result.data[i] > 9) {
                result.data[i + 1]++;
                result.data[i] = result.data[i] - 10;
            }
        }
        if ((data[0] == 0 && b.data[0] == 1) || (data[0] == 1 && b.data[0] == 0)){
            isPositive = false;
        }
        if (!isPositive) {
            result.data[0] = 0;
        }
        result.resetLen();
        return result;
    }

//    //输入运算符重载
//istream &operator>>(istream &in, BigNum &num) {
//
//    }

    //输出重载
ostream &operator<<(ostream &out, const BigNum &num) {
        string num_str = "";
        for (int i = num.len ; i >= 1 ; i--) {
            num_str += to_string(num.data[i]);
        }
        if (num_str == "") {
            num_str = num_str + "0";
        }
        if (num.data[0] == 1) {
            out << num_str;
        } else{
            out << "-" << num_str;
        }
        return out;
    }

    //重新计算大数长度，避免计算后首位为0而长度不对的情况
void BigNum::resetLen() {
    for (int i = this->len; i > 1; i--) {
        if (this->data[i] == 0) {
            len--;
        } else {
            break;
        }
    }
}

