//
//@brief: Implementations of BigInt class.
//@copyright: Copyright NPU-Franklin 2020
//@license: MIT License
//@birth: created by NPU-Franklin 2020-3-31
//@version: 4.0.2
//@revision: last revised by NPU-Franklin 2020-4-4
//

#include "BigInt.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include<complex>

typedef std::complex<double> complex;

const double PI(acos(-1.0));
const int N = static_cast<const int>(1e4);

//binary method for multiplication.
void bit_reverse_swap(complex *a, int n) {
    for (int i = 1, j = n >> 1, k; i < n - 1; ++i) {
        if (i < j) swap(a[i], a[j]);
        for (k = n >> 1; j >= k; j -= k, k >>= 1);
        j += k;
    }
}

//FFT method to do multiplication.
void FFT(complex *a, int n, int t) {
    bit_reverse_swap(a, n);
    for (int i = 2; i <= n; i <<= 1) {
        complex wi(cos(2.0 * t * PI / i), sin(2.0 * t * PI / i));
        for (int j = 0; j < n; j += i) {
            complex w(1);
            for (int k = j, h = i >> 1; k < j + h; ++k) {
                complex t = w * a[k + h], u = a[k];
                a[k] = u + t;
                a[k + h] = u - t;
                w *= wi;
            }
        }
    }
    if (t == -1) {
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
}

//binary method to do multiplication.
int trans(int x) {
    return 1 << int(ceil(log(x) / log(2) - 1e-9));  // math.h/log() 以e为底
}

std::istream &operator>>(std::istream &in, BigInt &x) {
//    Use operator>> to input.
    std::string tmp;
    in >> tmp;
    for (char &i : tmp) {
//        Method to deal with '-' while inputting.
        if (i == '-') x.bigint.push_back(-1);
        else x.bigint.push_back(i - '0');
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const BigInt &x) {
//    Use operator<< to output.
    if (x.bigint[0] == -1) {
//        Method to deal with '-'&'.' while outputting.
        out << "-";
        int len = x.bigint.size();
        for (int i = 1; i < len; i++) {
            if (x.bigint[i] == 0.1) { out << "."; }
            else if (x.bigint[i] < 10) { out << char(x.bigint[i] + '0'); }
            else {
                char copy[N];
                int tmp = x.bigint[i];
                int k = 0;
                while (tmp != 0) {
                    copy[k] = tmp % 10 + '0';
                    tmp /= 10;
                    k++;
                }
                for (int j = k; j >= 0; j--) {
                    out << copy[j];
                }
            }
        }
    } else {
        int len = x.bigint.size();
        for (int i = 0; i < len; i++) {
            if (x.bigint[i] == 0.1) { out << '.'; }
            else if (x.bigint[i] < 10) { out << char(x.bigint[i] + '0'); }
            else {
                char copy[N];
                int tmp = x.bigint[i];
                int k = 0;
                while (tmp != 0) {
                    copy[k] = tmp % 10 + '0';
                    tmp /= 10;
                    k++;
                }
                for (int j = k; j >= 0; j--) {
                    out << copy[j];
                }
            }
        }
    }
    return out;
}

BigInt &BigInt::operator=(std::string &s) {
//    Assignment function.
    for (char &i : s) {
        if (i == '-') this->bigint.push_back(-1);
        else this->bigint.push_back(i - '0');
    }
}

//function to compare two BigInt and return specific code for each situation.
int BigInt::cmp(const BigInt &x) const {
//    If caller is bigger than return 0, otherwise return 1, if is equal return 2.
    if (this->bigint[0] != -1 && x.bigint[0] != -1) {
        if (this->bigint.size() > x.bigint.size()) { return 0; }
        else if (this->bigint.size() < x.bigint.size()) { return 1; }
        else {
            for (int i = 0; i < x.bigint.size(); i++) {
                if (this->bigint[i] > x.bigint[i]) { return 0; }
                else if (this->bigint[i] < x.bigint[i]) { return 1; }
            }
            return 2;
        }
    } else if (this->bigint[0] != -1 && x.bigint[0] == -1) { return 0; }
    else if (this->bigint[0] == -1 && x.bigint[0] != -1) { return 1; }
    else {
        if (this->bigint.size() > x.bigint.size()) { return 1; }
        else if (this->bigint.size() < x.bigint.size()) { return 0; }
        else {
            for (int i = 0; i < x.bigint.size(); i++) {
                if (this->bigint[i] > x.bigint[i]) { return 1; }
                else if (this->bigint[i] < x.bigint[i]) { return 0; }
            }
            return 2;
        }
    }
}

BigInt BigInt::add(const BigInt &a) const {
//    Add two BigInt.
    BigInt a1, b1, result;

    a1 = a;
    b1 = *this;

    reverse(a1.bigint.begin(), a1.bigint.end());
    reverse(b1.bigint.begin(), b1.bigint.end());

    int tmp, len, carry = 0;
    if (a1 < b1) {
        int limitation = b1.size() - a1.size();
        for (int i = 0; i < limitation; i++) { a1.bigint.push_back(0); }
        len = b1.size();
    } else if (a1 == b1) { len = a1.size(); }
    else {
        int limitation = a1.size() - b1.size();
        for (int i = 0; i < limitation; i++) { b1.bigint.push_back(0); }
        len = a1.size();
    }
//Calculate.
    for (int i = 0; i < len; i++) {
        tmp = static_cast<int>(a1.bigint[i] + b1.bigint[i] + carry);
        carry = tmp / 10;
        tmp %= 10;
        result.bigint.push_back(tmp);
    }
    if (carry != 0) { result.bigint.push_back(carry); }

    reverse(result.bigint.begin(), result.bigint.end());

    return result;
}

BigInt BigInt::minus(const BigInt &b) const {
    BigInt a1, b1, result;
    enum theSign {
        pl, mi
    };
    theSign sign;
    if (*this > b) {
        a1 = *this;
        b1 = b;
        sign = pl;
    } else if (*this < b) {
        a1 = b;
        b1 = *this;
        sign = mi;
    } else {
        result.bigint.push_back(0);
        return result;
    }

    reverse(a1.bigint.begin(), a1.bigint.end());
    reverse(b1.bigint.begin(), b1.bigint.end());

    unsigned long long limitation = a1.bigint.size() - b1.bigint.size();
    for (int i = 0; i < limitation; i++) { b1.bigint.push_back(0); }

    int tmp, borrow = 0, len = a1.size();
    for (int i = 0; i < len; i++) {
        tmp = static_cast<int>(a1.bigint[i] - b1.bigint[i] + borrow);
        if (tmp < 0) {
            tmp += 10;
            borrow = -1;
        } else { borrow = 0; }
        result.bigint.push_back(tmp);
    }

    limitation = result.bigint.size();
    int flag = 0;
    for (unsigned long long i = limitation - 1; i >= 0; i--) {
        if (result.bigint[i] == 0) { flag++; }
        else break;
    }
    for (int i = 0; i < flag; i++) {
        result.bigint.pop_back();
    }
    reverse(result.bigint.begin(), result.bigint.end());

    if (sign == mi) { result.bigint.insert(result.bigint.begin(), -1); }

}

//multiplication based on FFT.
BigInt BigInt::multiply(const BigInt &x) const {
    BigInt result;
    int n, m, l;
    n = static_cast<int>(this->bigint.size());
    m = static_cast<int>(x.bigint.size());
    l = trans(n + m - 1);
    complex a[N], b[N];
    int ans[N];
    for (int i = 0; i < n; ++i) a[i] = complex(this->bigint[n - 1 - i]);
    for (int i = n; i < l; ++i) a[i] = complex(0);
    for (int i = 0; i < m; ++i) b[i] = complex(x.bigint[m - 1 - i]);
    for (int i = m; i < l; ++i) b[i] = complex(0);

    FFT(a, l, 1);
    FFT(b, l, 1);
    for (int i = 0; i < l; ++i) a[i] *= b[i];
    FFT(a, l, -1);
    for (int i = 0; i < l; ++i) ans[i] = (int) (a[i].real() + 0.5);
    ans[l] = 0;
    for (int i = 0; i < l; ++i) {
        ans[i + 1] += ans[i] / 10;
        ans[i] %= 10;
    }
    int p = l;
    for (; p && !ans[p]; --p);
    for (; ~p; result.bigint.push_back(ans[p--]));

    return result;
}

BigInt BigInt::divide(const BigInt &x, int i) const {
//    Division method, which default reserved digits is 0.
    BigInt a1, b1, result;
    if (i < 0) { throw "Invalid reservation digits."; }
    if (x.bigint[0] == 0 && x.size() == 1) { throw "Can't divide by zero."; }
    if (*this == x) {
        result.bigint.push_back(1);
        if (i == 0) { return result; }
        else {
            result.bigint.push_back(0.1);
            for (int j = 0; j < i; j++) { result.bigint.push_back(0); }
        }
    } else if (*this > x) {
        a1 = *this;
        b1 = x;

        double carry = b1.bigint[b1.size() - 1];
        unsigned long long limitation = a1.size() - b1.size();
        for (unsigned long long i = 0; i < limitation; i++) { b1.bigint.push_back(0); }

        int tmp = 0, len = b1.bigint.size();
        for (int i = 0; i < limitation + 1; i++) {
            while (a1 >= b1) {
                a1 = a1 - b1;
                tmp++;
            }
            result.bigint.push_back(tmp);
            b1.bigint.pop_back();
            tmp = 0;
        }

        int flag = 0;
        for (unsigned long long j = 0; j < len; j++) {
            if (result.bigint[j] == 0) { flag++; }
            else break;
        }
        reverse(result.bigint.begin(), result.bigint.end());
        for (int j = 0; j < flag; j++) { result.bigint.pop_back(); }
        reverse(result.bigint.begin(), result.bigint.end());

        if (i != 0) {
            result.bigint.push_back(0.1);
            if (a1.bigint[0] == 0 && a1.bigint.size() == 1) {
                for (int j = 0; j < i; j++) {
                    result.bigint.push_back(0);
                }
            } else {
                for (int j = 0; j < i; j++) { a1.bigint.push_back(0); }
                b1.bigint.push_back(carry);
                for (int j = 0; j < i - 1; j++) { b1.bigint.push_back(0); }

                for (int j = 0; j < i; j++) {
                    if (a1 < b1) { tmp = 0; }
                    else {
                        while (a1 >= b1) {
                            a1 = a1 - b1;
                            tmp++;
                        }
                    }

                    result.bigint.push_back(tmp);
                    b1.bigint.pop_back();
                    tmp = 0;
                }
            }
        }
    } else {
        result.bigint.push_back(0);
        if (i != 0) {
            a1 = *this;
            b1 = x;

            result.bigint.push_back(0.1);
            for (int j = 0; j < i; j++) { a1.bigint.push_back(0); }
            for (int j = 0; j < i - 1; j++) { b1.bigint.push_back(0); }

            int tmp = 0;
            for (int j = 0; j < i; j++) {
                if (a1 < b1) { tmp = 0; }
                else {
                    while (a1 >= b1) {
                        a1 = a1 - b1;
                        tmp++;
                    }
                }
                result.bigint.push_back(tmp);
                b1.bigint.pop_back();
                tmp = 0;
            }
        }
    }

    return result;
}

//modulo function
BigInt BigInt::mod(const BigInt &a) const {
    BigInt a1, b1, result;
    a1 = *this;
    b1 = a;
    result = a1.divide(b1, 0);
    result = b1 * result;
    result = a1 - result;

    return result;
}

BigInt operator+(BigInt &a, BigInt &b) {
//    Reload operator '+'
    BigInt result;

    std::vector<double>::iterator it;
    if (a.bigint[0] == -1 && b.bigint[0] == -1) {
        it = a.bigint.begin();
        a.bigint.erase(it);

        it = b.bigint.begin();
        b.bigint.erase(it);

        result = a.add(b);
        result.bigint.insert(result.bigint.begin(), -1);
    } else if (a.bigint[0] != -1 && b.bigint[0] != -1) {
        result = a.add(b);
    } else if (a.bigint[0] == -1 && b.bigint[0] != -1) {
        it = a.bigint.begin();
        a.bigint.erase(it);
        result = b.minus(a);
    } else {
        it = b.bigint.begin();
        b.bigint.erase(it);
        result = a.minus(b);
    }

    return result;
}

BigInt operator-(BigInt &a, BigInt &b) {
//    Reload operator ‘-’
    BigInt result;

    std::vector<double>::iterator it;
    if (a.bigint[0] == -1 && b.bigint[0] == -1) {
        it = a.bigint.begin();
        a.bigint.erase(it);

        it = b.bigint.begin();
        b.bigint.erase(it);

        result = b.minus(a);
    } else if (a.bigint[0] == -1 && b.bigint[0] != -1) {
        it = a.bigint.begin();
        a.bigint.erase(it);

        result = a.add(b);
        result.bigint.insert(result.bigint.begin(), -1);
    } else if (a.bigint[0] != -1 && b.bigint[0] == -1) {
        it = b.bigint.begin();
        b.bigint.erase(it);

        result = a.add(b);
    } else { result = a.minus(b); }

    return result;
}

BigInt operator*(BigInt &a, BigInt &b) {
//    Reload operator '*'
    BigInt result;

    std::vector<double>::iterator it;
    if (a.bigint[0] == -1 && b.bigint[0] == -1) {
        it = a.bigint.begin();
        a.bigint.erase(it);

        it = b.bigint.begin();
        b.bigint.erase(it);

        result = a.multiply(b);
    } else if (a.bigint[0] == -1 && b.bigint[0] != -1) {
        it = a.bigint.begin();
        a.bigint.erase(it);

        result = a.multiply(b);
        it = result.bigint.begin();
        result.bigint.insert(it, -1);
    } else if (a.bigint[0] != -1 && b.bigint[0] == -1) {
        it = b.bigint.begin();
        b.bigint.erase(it);

        result = a.multiply(b);
        it = result.bigint.begin();
        result.bigint.insert(it, -1);
    } else { result = a.multiply(b); }

    return result;
}

BigInt operator/(BigInt &a, BigInt &b) {
//    Reload operator '/'
    BigInt result;
    if (a.bigint[0] == -1 && b.bigint[0] == -1) {
        std::vector<double>::iterator it;
        it = a.bigint.begin();
        a.bigint.erase(it);

        it = b.bigint.begin();
        b.bigint.erase(it);

        result = a.divide(b);
    } else if (a.bigint[0] == -1 && b.bigint[0] != -1) {
        std::vector<double>::iterator it;
        it = a.bigint.begin();
        a.bigint.erase(it);

        result = a.divide(b);
        it = result.bigint.begin();
        result.bigint.insert(it, -1);
    } else if (a.bigint[0] != -1 && b.bigint[0] == -1) {
        std::vector<double>::iterator it;
        it = b.bigint.begin();
        b.bigint.erase(it);

        result = a.divide(b);
        it = result.bigint.begin();
        result.bigint.insert(it, -1);
    } else {
        result = a.divide(b);
    }

    return result;
}

BigInt operator%(BigInt &a, BigInt &b) {
//    Reload operator '%'
    BigInt result;
    if (a.bigint[0] == -1 && b.bigint[0] == -1) {
        std::vector<double>::iterator it;
        it = a.bigint.begin();
        a.bigint.erase(it);

        it = b.bigint.begin();
        b.bigint.erase(it);

        result = a.mod(b);
        it = result.bigint.begin();
        result.bigint.insert(it, -1);
    } else if (a.bigint[0] == -1 && b.bigint[0] != -1) {
        std::vector<double>::iterator it;
        it = a.bigint.begin();
        a.bigint.erase(it);

        result = a.mod(b);
    } else if (a.bigint[0] != -1 && b.bigint[0] == -1) {
        std::vector<double>::iterator it;
        it = b.bigint.begin();
        b.bigint.erase(it);

        result = a.mod(b);
        it = result.bigint.begin();
        result.bigint.insert(it, -1);
    } else {
        result = a.mod(b);
    }

    return result;
}

BigInt operator+=(BigInt &a, BigInt &b) {
//    Reload operator '+='
    a = a + b;
    return a;
}

BigInt operator-=(BigInt &a, BigInt &b) {
//    Reload operator '-='
    a = a - b;
    return a;
}

BigInt operator*=(BigInt &a, BigInt &b) {
//    Reload operator '*='
    a = a * b;
    return a;
}

BigInt operator/=(BigInt &a, BigInt &b) {
//    Reload operator '/='
    a = a / b;
    return a;
}

BigInt operator%=(BigInt &a, BigInt &b) {
//    Reload operator '%='
    a = a % b;
    return a;
}

BigInt pow(BigInt &a, int n) {
//    ordinary method to calculate power.
    BigInt result;
    result.bigint.push_back(1);
    for (int i = 0; i < n; i++) {
        result = result * a;
    }

    return result;
}

BigInt &BigInt::operator++(int) {
    BigInt tmp;
    tmp.bigint.push_back(1);
    *this = this->add(tmp);
    return *this;
}

BigInt &BigInt::operator++() {
    BigInt tmp;
    tmp.bigint.push_back(1);
    *this = this->add(tmp);
    return *this;
}

BigInt &BigInt::operator--(int) {
    BigInt tmp;
    tmp.bigint.push_back(-1);
    *this = this->add(tmp);
    return *this;
}

BigInt &BigInt::operator--() {
    BigInt tmp;
    tmp.bigint.push_back(-1);
    *this = this->add(tmp);
    return *this;
}

bool operator==(const BigInt &x, const BigInt &y) {
    return x.cmp(y) == 2;
}

bool operator!=(const BigInt &x, const BigInt &y) {
    return x.cmp(y) != 2;
}

bool operator<(const BigInt &x, const BigInt &y) {
    return x.cmp(y) == 1;
}

bool operator>(const BigInt &x, const BigInt &y) {
    return x.cmp(y) == 0;
}

bool operator<=(const BigInt &x, const BigInt &y) {
    return x.cmp(y) == 1 || x.cmp(y) == 2;
}

bool operator>=(const BigInt &x, const BigInt &y) {
    return x.cmp(y) == 0 || x.cmp(y) == 2;
}

inline int BigInt::size() const {
    return static_cast<int>(this->bigint.size());
}