//
// Created by NPU-Franklin on 2020/3/31.
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H
#pragma once

#include <vector>
#include <string>
#include <regex>

using namespace std;

class BigInt {
    /**
     *  Define a BigInt class which can do mathematical operations include plus, minus, multiplication,
     * division and so on on BigInt.
     */
    friend istream &operator>>(istream &, BigInt &);

    friend ostream &operator<<(ostream &, const BigInt &);

    friend BigInt operator+(BigInt &, BigInt &);

    friend BigInt operator-(BigInt &, BigInt &);

    friend BigInt operator*(BigInt &, BigInt &);

    friend BigInt operator/(BigInt &, BigInt &);

    friend BigInt operator%(BigInt &, BigInt &);

    friend BigInt operator+=(BigInt &, BigInt &);

    friend BigInt operator-=(BigInt &, BigInt &);

    friend BigInt operator*=(BigInt &, BigInt &);

    friend BigInt operator/=(BigInt &, BigInt &);

    friend BigInt operator%=(BigInt &, BigInt &);

    friend BigInt pow(BigInt &, int);

    friend bool operator==(const BigInt &, const BigInt &);

    friend bool operator!=(const BigInt &, const BigInt &);

    friend bool operator<(const BigInt &, const BigInt &);

    friend bool operator>(const BigInt &, const BigInt &);

    friend bool operator<=(const BigInt &, const BigInt &);

    friend bool operator>=(const BigInt &, const BigInt &);

public:
    BigInt() = default;

    ~BigInt() = default;

    BigInt &operator=(string &);

    BigInt &operator++(int);

    BigInt &operator++();

    BigInt &operator--(int);

    BigInt &operator--();

    inline int size() const;

    BigInt divide(const BigInt &, int = 5) const;

private:
    vector<double> bigint;

private:
    int cmp(const BigInt &) const;

    BigInt add(const BigInt &) const;

    BigInt minus(const BigInt &) const;

    BigInt multiply(const BigInt &) const;

    BigInt mod(const BigInt &) const;
};


#endif //BIGINT_BIGINT_H
