#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

/**
 * @class BigInt
 * @brief The class for arbitrary length integer calculations.
 *
 * Supports basic mathematical operations, comparison operators, and some various utility functions.
 */
class BigInt {
private:
    /**
     * @brief To store the number of digits.
     * 
     * Each element is a digit from 0 to 9.
     */
    std::vector<int64_t> number;

    /**
     * @brief Determines if a number is negative.
     *
     * If it is negative, then it is true. 
     */
    bool isNegative;

    /**
     * @brief Remove all leading zeros from the number.
     *
     * Ensure that the digits contained in the number remain valid.
     */
    void removeLeadingZero() {
        while (number.size() > 1 && number.back() == 0) {
            number.pop_back();
        }
        if (number.size() == 1 && number[0] == 0) {
            isNegative = false;
        }
    }

public:
    /**
     * @brief Default constructor, initializes the number to 0.
     */
    BigInt() : number{0}, isNegative(false) {}

    /**
     * @brief A constructor that converts a signed 64-bit integer to a BigInt.
     * 
     * @param integer The signed 64-bit integer to be converted, equivalent to long long.
     */
    BigInt(int64_t integer) {
        isNegative = integer < 0;
        integer = std::abs(integer);
        do {
            number.push_back(integer % 10);
            integer = integer / 10;
        } while (integer != 0);
        if (number.empty()) {
            number.push_back(0);
        }
    }

    /**
     * @brief The constructor that converts a number in string form to a BigInt.
     * 
     * @param str The integer in string form.
     * @throws std::invalid_argument if the string is invalid.
     */
    BigInt(const std::string& str) {
        if (str.empty()) {
            throw std::invalid_argument("It is empty");
        }
        
        isNegative = (str[0] == '-');
        size_t first = isNegative ? 1 : 0;

        if (str.size() == first) {
            throw std::invalid_argument("Only the symbol of negative '-'");
        }

        for (size_t i = str.size(); i > first; --i) {
            char c = str[i - 1];
            if (!std::isdigit(c)) {
                throw std::invalid_argument("String with other symbol");
            }
            number.push_back(c - '0');
        }
        removeLeadingZero();

        if (number.empty()) {
            isNegative = false;
        }
    }

    /**
     * @brief Adds two BigInts numbers.
     * 
     * @param other The other BigInt to be added to the first BigInt.
     * @return The sum of the two BigInts.
     */
    BigInt operator+(const BigInt& other) const {
        if (isNegative == other.isNegative) {
            BigInt sum = absoluteAdd(*this, other);
            sum.isNegative = isNegative;
            return sum;
        }
        if (absoluteComparison(*this, other) >= 0) {
            BigInt difference = absoluteSubtract(*this, other);
            difference.isNegative = isNegative;
            return difference;
        }
        BigInt diff = absoluteSubtract(other, *this);
        diff.isNegative = other.isNegative;
        return diff;
    }

    /**
     * @brief Adds another BigInt with this BigInt.
     * 
     * @param other Another BigInt to add tis BigInt.
     * @return A reference to this BigInt.
     */
    BigInt& operator+=(const BigInt& other) {
        *this = *this + other;
        return *this;
    }

    /**
     * @brief Subtracts another BigInt from this BigInt.
     * 
     * @param other The other BigInt to be subtracted.
     * @return The answer of the subtraction.
     */
    BigInt operator-(const BigInt& other) const {
        return *this + (-other);
    }

    /**
     * @brief Subtracts another BigInt from this BigInt.
     * 
     * @param other The other BigInt to subtract from this BigInt.
     * @return A reference to this BigInt.
     */
    BigInt& operator-=(const BigInt& other) {
        *this = *this - other; 
        return *this; 
    }

    /**
     * @brief Multiplies this BigInt by another BigInt.
     * 
     * @param other The other BigInt to multiply first BigInt by.
     * @return The product of these two BigInts.
     */
    BigInt operator*(const BigInt& other) const {
        BigInt answer;
        answer.number.resize(number.size() + other.number.size(), 0);
        answer.isNegative = (isNegative != other.isNegative);

        for (size_t i = 0; i < number.size(); ++i) {
            int64_t carry = 0;
            for (size_t j = 0; j < other.number.size() || carry; ++j) {
                int64_t multiplicand = (int64_t)number[i];
                int64_t multiplier;
                if (j < other.number.size()) {
                    multiplier = other.number[j];
                } else {
                    multiplier = 0;
                }
                int64_t product = multiplicand * multiplier; 
                int64_t current = answer.number[i + j] + product + carry;
                answer.number[i + j] = current % 10;
                carry = current / (int64_t)10;
            }
        }
        answer.removeLeadingZero();
        return answer;
    }

    /**
     * @brief Multiplies this BigInt by another BigInt.
     * 
     * @param other The other BigInt to multiply this BigInt by.
     * @return A reference to this BigInt.
     */
    BigInt& operator*=(const BigInt& other) {
        *this = *this * other;
        return *this;
    }

    /**
     * @brief Negates this BigInt.
     * 
     * @return The negated BigInt.
     */
    BigInt operator-() const {
        BigInt answer = *this;
        if (number[0] == 0 && number.size() == 1) {
            answer.isNegative = false;
        } else {
            answer.isNegative = !isNegative;
        }
        return answer;
    }

    /**
     * @brief Compares this BigInt to another BigInt to determine equality.
     * 
     * @param other The other BigInt to compare.
     * @return Returns true if the two BigInt are equal, false otherwise.
     */
    bool operator==(const BigInt& other) const {
        bool sameSign = (isNegative == other.isNegative);
        bool sameNumber = (number == other.number);
        return sameNumber && sameSign;
    }

    /**
     * @brief Compares this BigInt to another BigInt to determine if they are unequal.
     * 
     * @param other The other BigInt to compare.
     * @return Returns true if the two BigInt are unequal, false otherwise.
     */
    bool operator!=(const BigInt& other) const {
        bool sameSign = (isNegative == other.isNegative);
        bool sameNumber = (number == other.number);
        return !(sameNumber && sameSign);
    }


    /**
     * @brief Checks if this BigInt is less than another BigInt.
     * 
     * @param other The other BigInt to compare.
     * @return Returns true if this BigInt is less than another BigInt, false otherwise.
     */
    bool operator<(const BigInt& other) const {
        if (isNegative != other.isNegative) {
            return isNegative;
        }
        if (isNegative) {
            return absoluteComparison(*this, other) > 0;
        }
        return absoluteComparison(*this, other) < 0;
    }

    /**
     * @brief Checks if this BigInt is greater than another BigInt.
     * 
     * @param other The other BigInt to compare.
     * @return Returns true if this BigInt is greater than the other BigInt, false otherwise.
     */
    bool operator>(const BigInt& other) const {
        return other < *this;
    }

    /**
     * @brief Checks if this BigInt is less than or equal to another BigInt.
     * 
     * @param other The other BigInt to compare.
     * @return Return true if this BigInt is less than or equal to the other BigInt, false otherwise.
     */
    bool operator<=(const BigInt& other) const {
        return !(other < *this);
    }

    /**
     * @brief Checks if this BigInt is greater than or equal to another BigInt.
     * 
     * @param other The other BigInt to compare.
     * @return Return true if this BigInt is greater than or equal to the other BigInt, false otherwise.
     */
    bool operator>=(const BigInt& other) const {
        return !(*this < other);
    }

    /**
     * @brief Outputs the BigInt to an output stream.
     * 
     * @param output The output stream.
     * @param integer The BigInt to be output.
     * @return A reference to the output stream.
     */
    friend std::ostream &operator<<(std::ostream& output, const BigInt& integer) {
        if (integer.isNegative) {
            output << '-';
        }
        for (int64_t i = static_cast<int64_t>(integer.number.size()) - 1; i >= 0; --i) {
            output << integer.number[static_cast<std::size_t>(i)];
        }
        return output;
    }

    /**
     * @brief Pre-increments this BigInt.
     * 
     * @return A reference to this BigInt.
     */
    BigInt& operator++() {
        *this = *this + 1;
        return *this;
    }

    /**
     * @brief Post-increments this BigInt.
     * 
     * @return The BigInt before the increment.
     */
    BigInt operator++(int) {
        BigInt temp = *this;
        ++(*this);
        return temp;
    }

    /**
     * @brief Pre-decrements this BigInt.
     * 
     * @return A reference to this BigInt.
     */
    BigInt& operator--() {
        *this = *this - 1;
        return *this;
    }

    /**
     * @brief Post-decrements this BigInt.
     * 
     * @return The BigInt before the decrement.
     */
    BigInt operator--(int) {
        BigInt temp = *this;
        --(*this);
        return temp;
    }


private:

    /**
     * @brief Computes the absolute sum of two BigInts.
     * 
     * @param a The first BigInt.
     * @param b The second BigInt.
     * @return The absolute sum of these two BigInts.
     */
    static BigInt absoluteAdd(const BigInt& a, const BigInt& b) {
        BigInt sumAbs;
        sumAbs.number.clear();
        int64_t carry = 0;
        size_t maxLength = std::max(a.number.size(), b.number.size());
        for (size_t i = 0; i < maxLength || carry; ++i) {
            int64_t sum = carry;
            if (i < a.number.size()) {
                sum += a.number[i];
            }
            if (i < b.number.size()) { 
                sum += b.number[i];
            }
            sumAbs.number.push_back(sum % 10);
            carry = sum / 10;
        }
        return sumAbs;
    }

    /**
     * @brief Computes the absolute difference of two BigInts.
     * 
     * @param a The first BigInt.
     * @param b The second BigInt.
     * @return The absolute difference of these two BigInts.
     */
    static BigInt absoluteSubtract(const BigInt& a, const BigInt& b) {
        BigInt diffAbs;
        diffAbs.number.clear();
        int64_t borrow = 0;
        for (size_t i = 0; i < a.number.size(); ++i) {
            int64_t temp = 0;
            if (i < b.number.size()) {
                temp = b.number[i];
            }
            int64_t diff = a.number[i] - temp - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            diffAbs.number.push_back(diff);
        }
        diffAbs.removeLeadingZero();
        return diffAbs;
    }

    /**
     * @brief Compares the absolute values of two BigInts.
     * 
     * @param a The first BigInt.
     * @param b The second BigInt.
     * @return Return 1 if a > b, return -1 if a < b, and return 0 if a == b.
     */
    static int64_t absoluteComparison(const BigInt& a, const BigInt& b) {
        if (a.number.size() != b.number.size()) {
            if (a.number.size() > b.number.size()) {
                return 1;
            } else {
                return -1;
            }
        }

        for (int64_t i = static_cast<int64_t>(a.number.size()) - 1; i >= 0; --i) {
            if (a.number[static_cast<size_t>(i)] != b.number[static_cast<size_t>(i)]) {
                if (a.number[static_cast<size_t>(i)] > b.number[static_cast<size_t>(i)]) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
        return 0;
    }
};

#endif
