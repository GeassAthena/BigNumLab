//
// Created by 17637 on 2018/6/23.
//

#ifndef UNTITLED_BIGNUM_H
#define UNTITLED_BIGNUM_H
#include <string>
#include <iostream>

using namespace std;
#define N 200

class BigNum {
public:
    int data[2 * N]{};
    int len;
    BigNum();
    BigNum(string num_str);
    ~BigNum();
    long compare(BigNum a, BigNum b);
    bool operator>(BigNum &a);
    bool operator<(BigNum &a);
    bool operator==(BigNum &a);

    const BigNum operator+(const BigNum &b)const ;
    const BigNum operator-(const BigNum &b)const ;
    const BigNum operator*(const BigNum &b)const ;
    const BigNum operator/(const BigNum &b)const ;
//    friend istream &operator>>(istream &in, BigNum &num);
    friend ostream &operator<<(ostream &out, const BigNum &num);
    void resetLen();
};

#endif //UNTITLED_BIGNUM_H
