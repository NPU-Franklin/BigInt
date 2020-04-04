//
//@brief: Definitions for BigInt class.
//@copyright: Copyright NPU-Franklin 2020
//@license: MIT License
//@birth: created by NPU-Franklin 2020-3-31
//@version: 4.0.2
//@revision: last revised by NPU-Franklin 2020-4-4
//

#ifndef BIGINT_BIGINT_H
#define BIGINT_BIGINT_H
#pragma once

#include <vector>
#include <string>

class BigInt {
    /**
     *  Define a BigInt class which can do mathematical operations include plus, minus, multiplication,
     * division and so on on BigInt.The operations is just the same as what we can do on int type.
     * ATTENTION: When you do division on two BigInt developer offered you two ways:
     * (Suppose we have BigInt a, b;)
     *  1. a / b with no decimal
     *  2. a.divide(b, <decimal digit>)
     */
    friend std::istream &operator>>(std::istream &, BigInt &);

    friend std::ostream &operator<<(std::ostream &, const BigInt &);

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

    BigInt &operator=(std::string &);

    BigInt &operator++(int);

    BigInt &operator++();

    BigInt &operator--(int);

    BigInt &operator--();

    inline int size() const;

    BigInt divide(const BigInt &, int = 0) const;

private:
    std::vector<double> bigint;

private:
    int cmp(const BigInt &) const;

    BigInt add(const BigInt &) const;

    BigInt minus(const BigInt &) const;

    BigInt multiply(const BigInt &) const;

    BigInt mod(const BigInt &) const;
};


#endif //BIGINT_BIGINT_H
