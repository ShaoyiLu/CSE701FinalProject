# BigInt, a code written in C++ language that can perform calculations on any large numbers

## Introduction

This project, written entirely in C++, is called **BigInt**. As its name suggests, it can perform basic calculations on very long positive and negative integers, including following operators: `+`, `+=`, `-`, `-=`, `*`, `*=`, unary `-`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `<<`, pre-increment `++`, post-increment `++`, pre-increment `--`, and post-increment `--`.

## Private Parameters

- **bool isNegative**: Indicates whether a BigInt represents a negative number. Defaults to `false`, meaning the number is positive or zero.
- **vector<int64_t> number**: Used to store integers of arbitrary length. Each element represents a single digit in the range 0 to 9, stored in reverse order for operations to be performed in the normal way, that is, from the ones digit to the most significant digit.

## Private Method

- **void removeLeadingZero()**: Removes all leading zeros from the `number` vector to ensure that the number representation is still valid. If a number reduces to a zero, its `isNegative` is changed to `false` to represent zero as a non-negative value. This method maintains the integrity of the BigInt object, ensuring accurate arithmetic and comparison operations.

## Constructors

#### `BigInt()`: Default Constructor  
Initializes a `BigInt` object with a default value of `0`.  
- The `number` vector is initialized with a single number `0`.  
- The `isNegative` flag is set to `false`.

**Example:**
```cpp
BigInt zero;  // Initializes a BigInt with the value 0
std::cout << zero;  // Output: 0
```

#### `BigInt(int64_t integer)`: Signed Integer Constructor  
Constructs a `BigInt` object from a signed 64-bit integer, `int64_t`.  
- Determines the sign of the integer by checking whether it is less than `0`, and sets the `isNegative` flag.  
- Breaks the absolute value of the integer into individual digits, storing them in reverse order in that `number` vector.

**Example:**
```cpp
BigInt negativeInt(-888777666);  // Initializes a BigInt with the value -888777666
std::cout << negativeInt;  // Output: -888777666
```

#### `BigInt(const std::string& str)`: String Constructor  
Constructs a `BigInt` object from a string representation of an integer.  
- Checks if the string is empty. If so, throws a `std::invalid_argument` exception.  
- Determines the sign by examining the first character, only `'-'` for negative numbers.  
- Verifies that all characters without the sign are digits; otherwise, also need to throws a `std::invalid_argument` exception.  
- Extracts the numbers in reverse order and stores them in the `number` vector.  
- Removes leading zeros using the `removeLeadingZero` method and resets the `isNegative` flag if the resulting number is zero.

**Example:**
```cpp
BigInt stringInt("-299933331");  // Initializes a BigInt with the value -299933331 in string
std::cout << stringInt;  // Output: -299933331
```

## Operators

#### `BigInt operator+(const BigInt& other) const`  
Adds two `BigInt` objects and returns their sum.  
- If both numbers have the same `isNegative` flag, their absolute values are added, and the resulting sign is preserved.  
- If the signs are different, the absolute values are subtracted, and the resulting sign is determined by the larger operand.  
- This function is modular in design with helper methods `absoluteAdd` and `absoluteSubtract`. 

**Example:**
```cpp
BigInt n(7020);
BigInt m(1045);
BigInt sum = m + n;  // sum = 8065
std::cout << sum;  // Output: 8065
```

#### `BigInt& operator+=(const BigInt& other)`  
Adds another `BigInt` to the current object and updates the value of current one.
- This operator internally calls the `+` operator.

**Example:**
```cpp
BigInt uuu(40000);
BigInt yyy(2000);
uuu += yyy;  // uuu = 42000
std::cout << uuu;  // Output: 42000
```

#### `BigInt operator-(const BigInt& other) const`
Subtracts another `BigInt` from the current object and returns the result.
- This operator internally calls the `+` operator and the unary `-` operator to handle how the sign changes.

**Example:**
```cpp
BigInt X(-33333);
BigInt Z(66666);
BigInt difference = Z - X;  // difference = 99999
std::cout << difference;  // Output: 99999
```

#### `BigInt& operator-=(const BigInt& other)`
Subtracts another `BigInt` from the current object and updates the value of the current one.
- Now this operator internally calls the `-` operator.

**Example:**
```cpp
BigInt e(50012);
BigInt f(12);
e -= f;  // e = 50000
std::cout << e;  // Output: 50000
```

#### `BigInt operator*(const BigInt& other) const`
Multiplies two `BigInt` objects and returns their product.
- Computes the product of two operands using nested loops and stores the intermediate results in the `answer.number` vector.
- Handles carries and adjusts the sign `isNegative` based on the signs of the operands.
- Gets a correct integer result by removing leading zeros using the `removeLeadingZero` method.

**Example:**
```cpp
BigInt longInt(222333444111);
BigInt shortInt(20);
BigInt product = shortInt * longInt;  // product = 4446668882220
std::cout << product;  // Output: 4446668882220
```

#### `BigInt& operator*=(const BigInt& other)`
Multiplies the current `BigInt` by other `BigInt` and updates the value of current one.
- This operator internally calls the `*` operator.

**Example:**
```cpp
BigInt a(-5050000000000);
BigInt aa(4);
a *= aa;  // a = -20200000000000
std::cout << a;  // Output: -20200000000000
```

#### `BigInt operator-() const`  
Negates the current `BigInt` object and returns the negated value.  
- If the `BigInt` is `0`, the `isNegative` flag set to `false` to ensure `0` is non-negative. Otherwise, the `isNegative` flag is changed.

**Example:**
```cpp
BigInt a(98867363674656737523456332222);
BigInt negativeA = -a;  // negativeA = -98867363674656737523456332222
std::cout << negativeA;  // Output: -98867363674656737523456332222
```

#### `bool operator==(const BigInt& other) const`
Compares two `BigInt` objects for equality.
- Returns true if both `isNegative` flags and `number` vectors are same. Otherwise, returns `false`.

**Example:**
```cpp
BigInt k(21111134567654554323455);
BigInt t(21111134567654554323455);
std::cout << (k == t);  // Output: 1 (which means true)
```

#### `bool operator!=(const BigInt& other) const`
Compares two `BigInt` objects for inequality.
- Returns `true` if either the `isNegative` flag or the `number` vector are different.

**Example:**
```cpp
BigInt bc(80811728376453992646);
BigInt cb(28337645392947567383);
std::cout << (bc != cb);  // Output: 1 (which means true)
```

#### `bool operator<(const BigInt& other) const`
Checks if the current `BigInt` is less than other `BigInt`.
- Compares the `isNegative` flag and the absolute value to determine the result. If both numbers are negative, compares their absolute values.

**Example:**
```cpp
BigInt large(283746536755876356547);
BigInt small(123475466254738886467);
std::cout << (small < large);  // Output: 1 (which means true)
```

#### `bool operator>(const BigInt& other) const`
Checks if the current `BigInt` is greater than other `BigInt`.
- Internally calls the `<` operator by swapping operands.

**Example:**
```cpp
BigInt largeInt(999999999999999999);
BigInt smallInt(222222222222222222);
std::cout << (largeInt > smallInt);  // Output: 1 (which means true)
```

#### `bool operator<=(const BigInt& other) const`
Checks if the current `BigInt` is less than or equal to other `BigInt`.
- Combines the `<` operator and equality check to determine the result.

**Example:**
```cpp
BigInt right(707070707070707070);
BigInt left(707070707070707070);
std::cout << (left <= right);  // Output: 1 (which means true)
```

#### `bool operator>=(const BigInt& other) const`
Checks if the current `BigInt` is greater than or equal to other `BigInt`.
- Also combines the < operator and equality check to determine the result.

**Example:**
```cpp
BigInt right(607070607070606060);
BigInt left(707070707070707070);
std::cout << (left >= right);  // Output: 1 (which means true)
```

#### `friend std::ostream& operator<<(std::ostream& output, const BigInt& integer)`  
Outputs the `BigInt` to an output stream.  
- Handles negative numbers by printing a `'-'` sign before the digits.  
- Iterates over the numbers in reverse order to display the numbers in the correct form. 

**Example:**
```cpp
BigInt outPut(-123455432112345);
std::cout << outPut;  // Output: -123455432112345
```

#### `BigInt& operator++()` (Pre-Increment)  
This operator increments the current `BigInt` by 1 and returns a reference to the updated object.  
- Uses the `+` operator to perform the addition.  

**Example:**
```cpp
BigInt x(99999);
++x;  // x = 100000
std::cout << x;  // Output: 100000
```

#### `BigInt& operator++()` (Post-Increment)  
This operator increments the current `BigInt` by 1 and returns a value before increment.  
- Creates a temporary copy of the current `BigInt`, increments it, and then returns the copy.

**Example:**
```cpp
BigInt r(9999);
BigInt p = r++;  // p = 9999, r = 10000
std::cout << r << ", " << p;  // Output: 10000, 9999
```

#### `BigInt& operator--()` (Pre-decrement)  
This operator decrements the current BigInt by 1 and returns a reference to the updated object.
- Uses the `-` operator to perform the subtraction.  

**Example:**
```cpp
BigInt g(999998);
--g;  // a = 999997
std::cout << g;  // Output: 999997
```

#### `BigInt& operator--()` (Post-decrement)  
Decrements the current BigInt by 1 and returns the value before the decrement.
- Creates a temporary copy of the current `BigInt`, decrements it, and returns the copy.

**Example:**
```cpp
BigInt j(100);
BigInt l = j--;  // l = 100, j = 99
std::cout << j << ", " << l;  // Output: 99, 100
```

## Private Static Method

#### `static BigInt absoluteAdd(const BigInt& a, const BigInt& b)`  
Computes the absolute sum of two `BigInt` objects.  
- Adds the digits of `a` and `b` element-wise and takes into account carries.  
- Handles the case where the sizes of `a` and `b` are different by iterating to a larger size.
- Returns a `BigInt` representing the absolute sum.  
- If the result exceeds 9 in any position, carry is carried up to the next position. 
- The resulting digits are stored in reverse order in that `number` vector.  

**Example**
```cpp
BigInt sum = BigInt::absoluteAdd(BigInt(666666), BigInt(222111111));  // sum = 222777777
```

#### `static BigInt absoluteSubtract(const BigInt& a, const BigInt& b)`
Computes the absolute difference of two `BigInt` objects.
- Subtract the numbers of `b` from the elements of `a` and account for borrow.
- Assume `a` is greater than or equal to `b` to avoid negative results.
- Returns a `BigInt` representing the absolute difference.
- If a borrow is needed, add 10 to the current number and carry the borrow to the next position.
- Use `removeLeadingZero` to remove leading zeros from the result.

**Example**
```cpp
BigInt difference = BigInt::absoluteSubtract(BigInt(32), BigInt(45));  // difference = 13
```

#### `static int64_t absoluteComparison(const BigInt& a, const BigInt& b)`
Compares the absolute values of two `BigInt` objects.
- First compares the sizes of the `number` vectors.
- If the sizes are equal, iterates through the digits from the most significant bit to the least significant bit to determine the result.
- Returns `1` if `a > b`, `-1` if `a < b`, and `0` if `a == b`.

**Example**
```cpp
int result = BigInt::absoluteComparison(BigInt(3339), BigInt(7907));  // result = -1
```
