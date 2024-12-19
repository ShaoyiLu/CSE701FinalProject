#include <iostream>
#include <cassert>

#include "bigint.hpp"

// constructor tester
void testConstructor() {
    BigInt zero;
    assert(zero == BigInt(0));
    
    BigInt longLong(9025467891111682738LL);
    assert(longLong == BigInt("9025467891111682738"));
    
    BigInt negativeLongLong(-7762836615529837640LL);
    assert(negativeLongLong == BigInt("-7762836615529837640"));
        
    // string
    try {
        BigInt invalid("");
        assert(false);
    } catch (const std::invalid_argument&) {
        // if invalid, pass
    }
    
    try {
        BigInt invalid("89i1o4");
        assert(false);
    } catch (const std::invalid_argument&) {
        // if invalid, passs
    }
}

// bigint calculator tester!
void testOperator() {
    BigInt a("13206478842272655311"); 
    BigInt b("80250025245863872589"); 
    BigInt c("-48084066885301367633");
    BigInt d("-30477676548372141302");
    BigInt o;

    // +
    assert(a + b == BigInt("93456504088136527900"));
    assert(a + o == BigInt("13206478842272655311"));
    
    // -
    assert(a - d == BigInt("43684155390644796613"));
    assert(o - c == BigInt("48084066885301367633"));
    
    // *
    assert(c * d == BigInt("1465490637660506965476761506497325278166"));
    assert(o * (a + c) == BigInt("0"));

    // unary -
    BigInt H("90000000000000000000000000000");
    BigInt h("-90000000000000000000000000000");
    assert(-H == BigInt("-90000000000000000000000000000"));
    assert(-h == BigInt("90000000000000000000000000000"));
    
    BigInt O("333666999222777555000888111");
    BigInt P("-333666999222777555000888111");
    BigInt Q("-111888000555222777999333666");
    BigInt R("111888000555222777999333666");
    BigInt Z("333666999222777555000888111");

    // ==
    assert(O == Z);
    assert(!(P == Z));

    // !=
    assert(P != O);
    assert(O != (-Z));
    
    // <
    assert(Q < O);
    assert((P + R) < Q);
    
    // >
    assert(R > P);
    assert((Q * P) > Z);
    
    // <= 
    assert(Z <= O);
    assert((P - Q) <= Z);
    
    // >=
    assert(R >= Q);
    assert(-Z >= P);

    BigInt last1("100010001000100010001000");
    BigInt last2("-888888888855555555553");
    
    // pre-increment
    assert(++last1 == BigInt("100010001000100010001001"));
    assert(++last2 == BigInt("-888888888855555555552"));
    
    // post-increment
    assert(last1++ == BigInt("100010001000100010001001"));
    assert(last1 == BigInt("100010001000100010001002"));
    assert(last2++ == BigInt("-888888888855555555552"));
    assert(last2 == BigInt("-888888888855555555551"));
    
    // pre-decrement
    assert(--last1 == BigInt("100010001000100010001001"));
    assert(--last2 == BigInt("-888888888855555555552"));
    
    // post-decrement
    assert(last1-- == BigInt("100010001000100010001001"));
    assert(last1 == BigInt("100010001000100010001000"));
    assert(last2-- == BigInt("-888888888855555555552"));
    assert(last2 == BigInt("-888888888855555555553"));

}

int main() {
    testConstructor();
    std::cout << "Pass testConstructor()\n";
    
    testOperator();
    std::cout << "Pass testOperator()\n";
    
    std::cout << "Pass all!!!\n";
    return 0;
}
