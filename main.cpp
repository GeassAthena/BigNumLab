#include <iostream>
#include <vector>
#include <fstream>
#include "BigNum.h"

using namespace std;

extern void splitString(const string& s, vector<string>& v, const string& c)  //字符串分割函数
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}
extern bool isOperator(string &op){               //判断操作符
    return op == "+" || op == "-" || op == "*" || op == "/";
}

extern BigNum calculate(BigNum &a, string &op, BigNum &b){
    if (op == "+") {
        return a + b;
    }
    if (op == "-") {
        return a - b;
    }
    if ("*" == op) {
        return a * b;
    }
    if ("/" == op) {
        return a / b;
    }
}

int main() {
//    BigNum num1("121932631356500531347203169112635269");
//    BigNum num2("23456789123456789");
//    BigNum num3("10");
//    bool compare = (num1==num2);
////    BigNum temp = num2 * num3;
////    cout << temp << endl;
//    BigNum result = num1 / num2;
////    result = result - num3;
//
//    cout << result << endl;
    string in_filename("sample.in");
    string out_filename("sample.out");
    ifstream in(in_filename);
    ofstream out(out_filename);
    string line;
    getline(in, line);
    bool valid = true;
    int row;
    row = atoi(line.c_str());
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
    while (row > 0) {
        if (getline(in, line)) {
            vector<string> operators;
            vector<string> ops;
            vector<BigNum> nums;
            splitString(line, operators, " ");
            for (int i = 0; i < operators.size(); i++) {
                if (isOperator(operators[i])) {
                    ops.push_back(operators[i]);
                } else{
                    if (operators[i].length() > 100) {
                        valid = false;
                    } else {
                        BigNum num((operators[i]));
                        nums.push_back(num);
                    }
                }
            }
            if (!valid) {
                out << "数字长度超过100!"<<endl;
                valid = true;
                row--;
                continue;
            }
            BigNum result = nums[0];
            for (int i = 0; i < ops.size(); i++) {
                result = calculate(result, ops[i], nums[i + 1]);
                if (result.len > 100) {
                    out << "数字长度超过100!"<<endl;
                    valid = false;
                    continue;
                }
            }
            if (valid){
                out<< result<<endl;
            } else{
                valid = true;
                row--;
                continue;
            }
        }
        row--;
    }
    return 0;
}