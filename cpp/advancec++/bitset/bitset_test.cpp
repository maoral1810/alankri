#include <iostream> // cout
#include "MUTest.hpp" // TEST
#include "bitset.hpp"
#include "bitset_reference.hpp"

UNIT(GetAndSet)
    experis::Bitset<50> bitarr;
    //experis::Bitset<60> bitarray2(bitarray);
    unsigned long index = 1;
    experis::BitsetReference referance(&index, 12);
    bitarr[14] = true;

    ASSERT_THAT(bitarr[14] == true);

END_UNIT

UNIT(SetAll)
    experis::Bitset<65> bitarr;

    bitarr.SetALLOn();
    bool testPlace = bitarr[12];
    bool testPlace2 = bitarr[13];
    
    std::cout<< sizeof(unsigned long) << std::endl;

    for(size_t i = 0; i < 128; ++i) {
        if(i % 8 == 0){
            putchar('\n');
        }
        /* ASSERT_THAT */std::cout << bitarr[i];
    }

/*     bitarr.SetALLOff();
    for(size_t i = 0; i < 120; ++i) {
        ASSERT_THAT(bitarr[i] == false);
    } */
    
END_UNIT

UNIT(SetBitOn)
    
    experis::Bitset<2000> bitarr;

    bitarr.SetBitOnTo(1200, true);

    ASSERT_THAT(bitarr[1200]== true);
    ASSERT_THAT(bitarr[1201] == false);

END_UNIT

UNIT(FlipBit)
    experis::Bitset<32> bitarr;
    bitarr.FlipBitSet(5);
    bool testPlace = bitarr[5];

    ASSERT_THAT(bitarr[5] == true);

END_UNIT

UNIT(AndOp)
    experis::Bitset<32> bitarr;
    bitarr.SetALLOn();

    experis::Bitset<32> other;
    other.SetALLOff();

    experis::Bitset<32> clone = bitarr & other;

    ASSERT_THAT(clone[10] == false);

END_UNIT

UNIT(OrOp)
    experis::Bitset<32> bitarr;
    bitarr.SetALLOn();

    experis::Bitset<32> other;
    other.SetALLOff();

    experis::Bitset<32> clone = bitarr | other;
    ASSERT_THAT(clone[10] == true);

END_UNIT

UNIT(XorOp)
    experis::Bitset<32> bitarr;
    bitarr.SetALLOn();

    experis::Bitset<32> other;
    other.SetALLOff();

    experis::Bitset<32> clone = bitarr ^ other;

    ASSERT_THAT(clone[10] == true);

END_UNIT

UNIT(NotOp)
    experis::Bitset<32> bitarr;
    bitarr.SetALLOn();
    for(size_t i = 0; i < 32; ++i) {
        ASSERT_THAT(bitarr[i] == true);
    }

    bitarr = ~bitarr;
    for(size_t i = 0; i < 32; ++i) {
        ASSERT_THAT(bitarr[i] == false);
    }

END_UNIT

UNIT(Mirror)
    experis::Bitset<32> bitarr;
    
    for(size_t i = 0; i < 64; ++i) {
        if(i % 2 == 0) {
            bitarr[i] = true;
        }
        //std::cout << bitarr[i];
    }

    for(size_t i = 0; i < 64; ++i) {
        //std::cout << bitarr[i];
    }

    putchar('\n');

    bitarr.MirrorBitSet();

    for(size_t i = 0; i < 64; ++i) {
        //std::cout << bitarr[i];

        if(i % 2) {
            ASSERT_THAT(bitarr[i] == true);
        }
    }

END_UNIT

UNIT(CountOn)
    experis::Bitset<64> bitarr;
    
    bitarr.SetALLOn();
    std::cout << bitarr.CountOnBits() << std::endl;

END_UNIT


TEST_SUITE(BitSet Test)
    TEST(GetAndSet)
    //TEST(SetAll)
    TEST(SetBitOn)
    TEST(FlipBit)
    TEST(AndOp)
    TEST(OrOp)
    TEST(XorOp)
    TEST(NotOp)
    TEST(Mirror)
    //TEST(CountOn)

END_SUITE



