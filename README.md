# BigInt, a code written in C++ language that can perform calculations on any large numbers

## Introduction

This project implements a C++ class called **BigInt** that can handle integers of arbitrary length. It is not affected by the size of the number, which is more practical than `int` or `long`, which have length restrictions on numbers, because it can effectively recognize any very very long numbers and perform calculations.

## Constructors

- **Default constructor**: Create the integer 0.
- **Constructor from 64-bit integer**: Takes a signed 64-bit integer and converts it to an arbitrary-precision integer.
- **Constructor from string**: Take a string of digits and converts it to an arbitrary-precision integer.

## Operators
- **Addition**: Supports the `+` and `+=` operators.
- **Subtraction**: Supports the `-` and `-=` operators.
- **Multiplication**: Supports the `*` and `*=` operators.
- **Negation**: Supports the unary `-` operator to negate the number.
- **Comparison**: Supports the `==`, `!=`, `<`, `>`, `<=`, and `>=` comparisons.
- **Insertion**: Supports the `<<` operator for printing the integer to a stream such as `std::cout` or a file.
- **Increment**: Supports pre-increment `++` and post-increment `++`.
- **Decrement**: Supports pre-increment `--` and post-increment `--`.

## Class

The class stores the number as unsigned integer vector `std::vector`, which allows it to efficiently handle large integers without memory overflow. This implementation uses the base-256 method, where each element in the vector represents 256-bit chunks of the number. This class can throw exceptions for invalid inputs, such as invalid strings that cannot be converted to a number.

## Data Representation

- Each number is represented as a vector of 32-bit integers, ensuring an efficient memory layout and fast operations.
- Numbers are stored with the least significant bit first.

## Example

Here is an example of how to use the `BigInt` class:

```cpp
BigInt a("1111222233334444555577776666999900001111");
BigInt b("8888888800000000999999991111111133333333");

BigInt sum = a + b;
BigInt diff = a - b;
BigInt prod = a * b;

std::cout << "Sum: " << sum << std::endl;
std::cout << "Difference: " << diff << std::endl;
std::cout << "Product: " << prod << std::endl;

Output:
> Sum: 10000111033334445555577767778111033334444  
> Difference: -7777666566665556444422214444111233332222  
> Product: 9877530864197531975518500001110358019758765456708640247629619752222135833332963