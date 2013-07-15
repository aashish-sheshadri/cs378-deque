// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    TestFixture.h
    ...
    % g++ -pedantic -std=c++0x -Wall Deque.h TestDeque.c++ -o TestDeque -lgtest -lpthread -lgtest_main
    % valgrind TestDeque > TestDeque.out
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==
#include <gtest/gtest.h>
#include "Deque.h"

// ---------
// TestDeque
// ---------

template <class C>
class DequeTest : public testing::Test {
protected:
    DequeTest() : aDeque(C()) {}

    virtual void SetUp() {
        aDeque.clear();
    }

    virtual void TearDown() {
    }

    C aDeque;
};

using testing::Types;
typedef Types<std::deque<int>, MyDeque<int>> Implementations;
TYPED_TEST_CASE(DequeTest, Implementations);

TYPED_TEST(DequeTest, push_back) {
    this->aDeque.push_back(1);
    assert(this->aDeque[0] == 1);
} 

TYPED_TEST(DequeTest, size) {
    this->aDeque.push_back(1);
    this->aDeque.push_back(2);
    int size = this->aDeque.size();
    assert(size == 2);
} 