#include <sstream>
#include <iostream>
#include <cassert>

#include "bigint.hpp"

/**
 * @brief Tests the constructors of the BigInt class.
 * 
 * This function tests various constructors of the BigInt class, including default constructor, 
 * signed integer conversion, and string conversion. It also verifies proper handling of invalid inputs.
 */
void testConstructor() {
    BigInt zero;
    assert(zero == BigInt(0));
    
    BigInt longLong(9025467891111682738);
    assert(longLong == BigInt("9025467891111682738"));
    
    BigInt negativeLongLong(-7762836615529837640);
    assert(negativeLongLong == BigInt("-7762836615529837640"));
        
    try {
        BigInt invalid("");
        assert(false);
    } catch (const std::invalid_argument&) {
    }
    
    try {
        BigInt invalid("89i1o4");
        assert(false);
    } catch (const std::invalid_argument&) {
    }
}

/**
 * @brief Tests the computation and comparison operators of the BigInt class.
 * 
 * This function tests almost all computation operators (+, -, *), unary negation,
 * and comparison operators (==, !=, <, >, <=, >=). It also validates the functionality 
 * of pre-increment, post-increment, pre-decrement, and post-decrement operators.
 */
void testOperator() {
    BigInt a("13206478842272655311"); 
    BigInt b("80250025245863872589"); 
    BigInt c("-48084066885301367633");
    BigInt d("-30477676548372141302");
    BigInt o;

    assert(a + b == BigInt("93456504088136527900"));
    assert(a + o == BigInt("13206478842272655311"));
    
    assert(a - d == BigInt("43684155390644796613"));
    assert(o - c == BigInt("48084066885301367633"));
    
    assert(c * d == BigInt("1465490637660506965476761506497325278166"));
    assert(o * (a + c) == BigInt("0"));

    BigInt H("90000000000000000000000000000");
    BigInt h("-90000000000000000000000000000");
    assert(-H == BigInt("-90000000000000000000000000000"));
    assert(-h == BigInt("90000000000000000000000000000"));
    
    BigInt O("333666999222777555000888111");
    BigInt P("-333666999222777555000888111");
    BigInt Q("-111888000555222777999333666");
    BigInt R("111888000555222777999333666");
    BigInt Z("333666999222777555000888111");

    assert(O == Z);
    assert(!(P == Z));

    assert(P != O);
    assert(O != (-Z));
    
    assert(Q < O);
    assert((P + R) < Q);
    
    assert(R > P);
    assert((Q * P) > Z);

    assert(Z <= O);
    assert((P - Q) <= Z);

    assert(R >= Q);
    assert(-Z >= P);

    BigInt last1("100010001000100010001000");
    BigInt last2("-888888888855555555553");
    
    assert(++last1 == BigInt("100010001000100010001001"));
    assert(++last2 == BigInt("-888888888855555555552"));

    assert(last1++ == BigInt("100010001000100010001001"));
    assert(last1 == BigInt("100010001000100010001002"));
    assert(last2++ == BigInt("-888888888855555555552"));
    assert(last2 == BigInt("-888888888855555555551"));
    
    assert(--last1 == BigInt("100010001000100010001001"));
    assert(--last2 == BigInt("-888888888855555555552"));
    
    assert(last1-- == BigInt("100010001000100010001001"));
    assert(last1 == BigInt("100010001000100010001000"));
    assert(last2-- == BigInt("-888888888855555555552"));
    assert(last2 == BigInt("-888888888855555555553"));

}

/**
 * @brief Tests the less-than operator of the BigInt class.
 *
 * This function verifies that the BigInt class correctly compares two
 * instances using the < operator.
 */
void testLessThanOperator() {
    BigInt large1("29348572947832947983214789345657892384923978472394832");
    BigInt large2("29348572947832947983214789345657892384923978472394833");
    assert(large1 < large2);
    assert(!(large2 < large1));

    BigInt largeNegative1("-29348572947832947983214789345657892384923978472394832");
    BigInt largeNegative2("-29348572947832947983214789345657892384923978472394833");
    assert(largeNegative2 < largeNegative1);
    assert(!(largeNegative1 < largeNegative2));

}

/**
 * @brief Tests the output operator of the BigInt class.
 *
 * This function verifies that the BigInt class correctly outputs
 * its string representation using the << operator. 
 */
void testOutputOperator() {
    BigInt positiveNUmber("876534312345678987656434325566");
    BigInt negativeNumber("-435678932123456789098666436772");
    BigInt zero("-0");
    
    std::ostringstream oss;

    oss << positiveNUmber;
    assert(oss.str() == "876534312345678987656434325566");
    oss.str("");
    oss.clear();

    oss << negativeNumber;
    assert(oss.str() == "-435678932123456789098666436772");
    oss.str("");
    oss.clear();

    oss << zero;
    assert(oss.str() == "0");
    oss.str("");
    oss.clear();

    std::cout << "Pass testOutputOperator()\n";
}


/**
 * @brief The main function for testing the BigInt class.
 * 
 * Runs the constructor tests and operator tests for the BigInt class.
 * Prints the results of each test case and a final success message.
 * 
 * @return Returns 0 after all tests complete successfully.
 */
int main() {
    testConstructor();
    std::cout << "Pass testConstructor()\n";
    
    testOperator();
    std::cout << "Pass testOperator()\n";

    testOutputOperator();
    std::cout << "Pass testOutputOperator()\n";

    testLessThanOperator();
    std::cout << "Pass testLessThanOperator()\n";
    
    std::cout << "Pass all!!!\n";
    return 0;
}
