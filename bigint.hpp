#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>


class BigInt {
private:
    std::vector<int> number;
    bool isNegative;

    void removeLeadingZero() { // remove leading zero (003 to 3)
        while (number.size() > 1 && number.back() == 0) { // if size bigger than 1 and has leading 0
            number.pop_back(); // remove leading 0
        }
        if (number.size() == 1 && number[0] == 0) {
            isNegative = false; // 0 is always nonegative
        }
    }

public:
    // 1. default constructor, creating the integer 0
    BigInt() : number{0}, isNegative(false) {}

    // 2. constructor that takes a signed 64-bit integer, converts it to an arbitrary-precision integer
    BigInt(int64_t integer) {
        isNegative = integer < 0; // check whether negative
        integer = std::abs(integer); // absolute value
        do {
            number.push_back(integer % 10); // get the rightmost digit
            integer = integer / 10; // remove the rightmost digit
        } while (integer != 0);
        if (number.empty()) {
            number.push_back(0); // empty means 0
        }
    }

    // 3. constructor that takes a string of digits, converts it to an arbitrary-precision integer
    BigInt(const std::string& str) {
        if (str.empty()) {
            throw std::invalid_argument("It is empty!!!"); // empty means wrong
        }
        isNegative = (str[0] == '-'); // check whether negative
        for (int i = str.size() - 1; i >= (isNegative ? 1 : 0); --i) { // if negative, skip "-"
            if (!isdigit(str[i])) {
                throw std::invalid_argument("Invalid number!!!"); // invalid number also means wrong
            }
            number.push_back(str[i] - '0'); // change string to int
        }
        removeLeadingZero();
    }

    // Addition (+)
    BigInt operator+(const BigInt& other) const {
        if (isNegative == other.isNegative) { // if all negative, add it directly
            BigInt sum = absoluteAdd(*this, other);
            sum.isNegative = isNegative;
            return sum;
        }
        if (absoluteComparsion(*this, other) >= 0) { // if one is negative and one is not, subtract
            BigInt diffrence = absoluteSubtract(*this, other);
            diffrence.isNegative = isNegative;
            return diffrence;
        }
        BigInt diff = absoluteSubtract(other, *this); // if other one bigger than first, subtract
        diff.isNegative = other.isNegative;
        return diff;
    }

    // Addition (+=)
    BigInt& operator+=(const BigInt& other) {
        *this = *this + other;
        return *this;
    }

    // Subtraction (-)
    BigInt operator-(const BigInt& other) const {
        //*this = *this + (-other);
        return *this + (-other);
    }

    // Subtraction (-=)
    BigInt& operator-=(const BigInt& other) {
        *this = *this - other; 
        return *this; 
    }

    // Multiplication (*)
    BigInt operator*(const BigInt& other) const {
        BigInt answer;
        answer.number.resize(number.size() + other.number.size(), 0); // storage space
        answer.isNegative = (isNegative != other.isNegative); // if not equal, result is positive

        for (size_t i = 0; i < number.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < other.number.size() || carry; ++j) {
                long long multiplicand = (long long)number[i]; // multiplicand
                long long multiplier; // multiplier
                if (j < other.number.size()) {
                    multiplier = other.number[j];
                } else {
                    multiplier = 0; // if tranversal all number, just add carry at end (so it is 0)
                }
                long long product = multiplicand * multiplier; 
                long long current = answer.number[i + j] + product + carry; // add each time result and carry
                answer.number[i + j] = current % 10; // store the rightmost digit on [i, j]
                carry = current / 10; // next carry
            }
        }
        answer.removeLeadingZero();
        return answer;
    }

    // Multiplication (*=)
    BigInt& operator*=(const BigInt& other) {
        *this = *this * other;
        return *this;
    }

    // Negation (unary -)
    BigInt operator-() const { // no parameter
        BigInt answer = *this;
        if (number[0] == 0 && number.size() == 1) {
            answer.isNegative = false; // 0 is not negative
        } else {
            answer.isNegative = !isNegative; // change + to -, or - to +
        }
        return answer;
    }

    // Comparison (==)
    bool operator==(const BigInt& other) const {
        bool sameSign = (isNegative == other.isNegative);
        bool sameNumber = (number == other.number);
        return sameNumber && sameSign; // if sign and number all same, then they are equal
    }

    // Comparison (!=)
    bool operator!=(const BigInt& other) const {
        bool sameSign = (isNegative == other.isNegative);
        bool sameNumber = (number == other.number);
        return !(sameNumber && sameSign); // if one of sign and number not same, then not equal
    }


    // Comparison (<)
    bool operator<(const BigInt& other) const {
        if (isNegative != other.isNegative) { //if one is - and other is +, return negative one
            return isNegative;
        }
        if (isNegative) { // if all negative and one absolute value is large, return this one
            return absoluteComparsion(*this, other) > 0;
        }
        return absoluteComparsion(*this, other) < 0; // if all positive, return smaller one
    }

    // Comparison (>)
    bool operator>(const BigInt& other) const {
        return other < *this; // just use <
    }

    // Comparison (<=)
    bool operator<=(const BigInt& other) const {
        return !(other < *this); // not > means <=
    }

    // Comparison (>=)
    bool operator>=(const BigInt& other) const {
        return !(*this < other); // not < means >=
    }

    // Insertion (<<)
    friend std::ostream &operator<<(std::ostream& output, const BigInt& integer) {
        if (integer.isNegative) { // if it is negative, output -
            output << '-';
        }
        for (int i = integer.number.size() - 1; i >= 0; --i) {
            output << integer.number[i]; // then output number from left to right
        }
        return output;
    }

    // Increment (++ pre-increment)
    BigInt& operator++() {
        *this = *this + 1; // just add one
        return *this;
    }

    // Increment (++ post-increment)
    BigInt operator++(int) {
        BigInt temp = *this;
        // (*this)++; // recursion
        ++(*this); // let number add 1 but return initial value
        return temp;
    }

    // Decrement (-- pre-decrement)
    BigInt& operator--() {
        *this = *this - 1;
        return *this;
    }

    // Decrement (-- post-decrement)
    BigInt operator--(int) {
        BigInt temp = *this;
        --(*this); // let number minus 1 but return initial value
        return temp; // -- almost same as ++
    }


private:
    // absolute value of the sum of two int
    static BigInt absoluteAdd(const BigInt& a, const BigInt& b) {
        BigInt sumAbs;
        sumAbs.number.clear();
        int carry = 0;
        size_t maxLength = std::max(a.number.size(), b.number.size()); // find longer one and choose it's size
        for (size_t i = 0; i < maxLength || carry; ++i) {
            int sum = carry; // add carry to sum each time
            if (i < a.number.size()) {
                sum += a.number[i]; // add number a[i] to sum
            }
            if (i < b.number.size()) { 
                sum += b.number[i]; // add number b[i] to sum
            }
            sumAbs.number.push_back(sum % 10); //  then add sum to absolute value sum
            carry = sum / 10;
        }
        return sumAbs;
    }

    // absolute value of the diffrence of two int
    static BigInt absoluteSubtract(const BigInt& a, const BigInt& b) {
        BigInt diffAbs;
        diffAbs.number.clear();
        int borrow = 0;
        for (size_t i = 0; i < a.number.size(); ++i) {
            int newb = 0;
            if (i < b.number.size()) {
                newb = b.number[i]; // replace b to new one
            }
            int diff = a.number[i] - newb - borrow; // a - b - borrow = diffrence
            if (diff < 0) {
                diff += 10; // it should not be negative
                borrow = 1; // The higher digit needs to minus 1
            } else {
                borrow = 0;
            }
            diffAbs.number.push_back(diff); // add diffrence to absolute diffrence
        }
        diffAbs.removeLeadingZero();
        return diffAbs;
    }

    // comparison of absolute values of two numbers
    static int absoluteComparsion(const BigInt& a, const BigInt& b) {
        if (a.number.size() != b.number.size()) {
            if (a.number.size() > b.number.size()) { // compare length of number
                return 1; // if a > b
            } else {
                return -1; // if b >a
            }
        }
        // if two number size are equal
        for (int i = a.number.size() - 1; i >= 0; --i) { // from higher digit to compare
            if (a.number[i] != b.number[i]) {
                if (a.number[i] > b.number[i]) {
                    return 1; // if a > b
                } else {
                    return -1; // if a < b
                }
            }
        }
        return 0; // when a == b
    }
};

#endif
