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
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -Wall Deque.c++ TestDeque.c++ -o TestDeque -lcppunit -ldl
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

//#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
//#include "cppunit/TestFixture.h"             // TestFixture
//#include "cppunit/TextTestRunner.h"          // TestRunner
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


// struct TestDeque : CppUnit::TestFixture {
    // ----
    // size
    // ----

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

//    void test_size () {
//        const C x;
//        CPPUNIT_ASSERT(x.size() == 0);}

//    // -----
//    // suite
//    // -----
//
//    CPPUNIT_TEST_SUITE(TestDeque);
//    CPPUNIT_TEST(test_size);
//    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

// int main () {
//    using namespace std;
//    ios_base::sync_with_stdio(false);        // turn off synchronization with C I/O
//    cout << "TestDeque.c++" << endl << endl;
//
//    CppUnit::TextTestRunner tr;
//    tr.addTest(TestDeque< MyDeque<int> >::suite());
//    tr.addTest(TestDeque<   deque<int> >::suite());
//    tr.run();
//
//    cout << "Done." << endl;
//    return 0;}
