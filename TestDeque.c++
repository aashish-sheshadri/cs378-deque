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
    DequeTest() : aDequeLHS(C()),aDequeRHS(C()) {}

    virtual void SetUp() {
        aDequeLHS.clear();
        aDequeRHS.clear();
    }

    virtual void TearDown() {
    }

    C aDequeLHS,aDequeRHS;
    typename C::iterator it;
    typename C::iterator itOther;
    typename C::const_iterator cit;
    typename C::const_iterator citOther;
    typename C::difference_type dt;
    typename C::size_type st;
};

using testing::Types;
typedef Types<std::deque<int>, MyDeque<int> > Implementations;
TYPED_TEST_CASE(DequeTest, Implementations);

TYPED_TEST(DequeTest, push_back) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    EXPECT_TRUE(this->aDequeLHS[1] == 2);
}

TYPED_TEST(DequeTest, push_front) {
    this->aDequeLHS.push_front(1);
    this->aDequeLHS.push_front(2);
    EXPECT_TRUE(this->aDequeLHS[0] == 2);
} 

TYPED_TEST(DequeTest, size) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    int size = this->aDequeLHS.size();
    EXPECT_TRUE(size == 2);
}

TYPED_TEST(DequeTest, equal_equal) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);

    this->aDequeRHS.push_back(1);
    this->aDequeRHS.push_back(2);

    EXPECT_TRUE(this->aDequeLHS == this->aDequeRHS);
}  

TYPED_TEST(DequeTest, less_than) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);

    this->aDequeRHS.push_back(2);
    this->aDequeRHS.push_back(1);

    EXPECT_TRUE(this->aDequeLHS < this->aDequeRHS);
}

TYPED_TEST(DequeTest, starIt) {
    this->aDequeLHS.push_back(1);
    this->it = this->aDequeLHS.begin();
    EXPECT_TRUE(*(this->it) == 1);
}

TYPED_TEST(DequeTest, begin) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->it = this->aDequeLHS.begin();
    EXPECT_TRUE(*(this->it) == 1);
}

TYPED_TEST(DequeTest, equalIt) {
    this->aDequeLHS.push_back(1);
    this->it = this->aDequeLHS.begin();
    this->itOther = this->aDequeLHS.begin();
    EXPECT_TRUE(this->it == this->itOther);
}

TYPED_TEST(DequeTest, incrementIt) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->it = this->aDequeLHS.begin();
    ++this->it;
    EXPECT_TRUE(*(this->it) == 2);
}

TYPED_TEST(DequeTest, decrementIt) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->it = this->aDequeLHS.end();
    --this->it;
    EXPECT_TRUE(*(this->it) == 3);
}

TYPED_TEST(DequeTest, plus_equalIt) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->it = this->aDequeLHS.begin();
    this->dt = 2;
    this->it += this->dt;
    EXPECT_TRUE(*(this->it) == 3);
}

TYPED_TEST(DequeTest, minus_equalIt) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->it = this->aDequeLHS.end();
    this->dt = 2;
    this->it -= this->dt;
    EXPECT_TRUE(*(this->it) == 2);
}

//TYPED_TEST(DequeTest, equalCIt) {
//    this->aDequeLHS.push_back(1);
//     this->cit = this->aDequeLHS.begin();
//     this->citOther = this->aDequeLHS.begin();
//     EXPECT_TRUE(this->cit == this->citOther);
// }

//No tests for const iterator

TYPED_TEST(DequeTest, equal) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->aDequeRHS = this->aDequeLHS;
    EXPECT_TRUE(&this->aDequeLHS != &this->aDequeRHS);
    EXPECT_TRUE(this->aDequeLHS == this->aDequeRHS);
}

TYPED_TEST(DequeTest, index) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->st = 2;
    EXPECT_TRUE((this->aDequeLHS)[this->st] == 3);
}

TYPED_TEST(DequeTest, at_1) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->st = 2;
    EXPECT_TRUE((this->aDequeLHS).at(this->st) == 3);
}

TYPED_TEST(DequeTest, at_2) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->st = 4;
    try{
        (this->aDequeLHS).at(this->st);
        EXPECT_TRUE(false);
    } catch (std::out_of_range e) {
        EXPECT_TRUE(true);
    }

}

TYPED_TEST(DequeTest, back) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    EXPECT_TRUE((this->aDequeLHS).back() == 3);
}

TYPED_TEST(DequeTest, clear) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->aDequeLHS.clear();
    EXPECT_TRUE((this->aDequeLHS).size() == 0);
}

TYPED_TEST(DequeTest, end) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->it = this->aDequeLHS.end();
    --this->it;
    EXPECT_TRUE(*(this->it) == 3);
}

TYPED_TEST(DequeTest, erase) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->it = this->aDequeLHS.begin();
    this->it = (this->aDequeLHS).erase(this->it);
    EXPECT_TRUE(*(this->it) == 2);
}

TYPED_TEST(DequeTest, front) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    EXPECT_TRUE((this->aDequeLHS).front()==1);
}

TYPED_TEST(DequeTest, insert) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->it = this->aDequeLHS.begin();
    this->it = this->aDequeLHS.insert(this->it,5);
    EXPECT_TRUE(*(this->it)==5);
    EXPECT_TRUE((this->aDequeLHS)[0]==5);
}

TYPED_TEST(DequeTest, pop_back) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->aDequeLHS.pop_back();
    EXPECT_TRUE((this->aDequeLHS).size()==2);
    EXPECT_TRUE((this->aDequeLHS)[1]==2);
}

TYPED_TEST(DequeTest, pop_front) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->aDequeLHS.pop_front();
    EXPECT_TRUE((this->aDequeLHS).size()==2);
    EXPECT_TRUE((this->aDequeLHS)[0]==2);
}

TYPED_TEST(DequeTest, resize) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    this->st = 2;
    (this->aDequeLHS).resize(this->st);
    EXPECT_TRUE((this->aDequeLHS).size()==2);
    EXPECT_TRUE((this->aDequeLHS)[1]==2);
}

TYPED_TEST(DequeTest, swap) {
    this->aDequeLHS.push_back(1);
    this->aDequeLHS.push_back(2);
    this->aDequeLHS.push_back(3);
    
    this->aDequeRHS.push_back(3);
    this->aDequeRHS.push_back(2);
    this->aDequeRHS.push_back(1);

    (this->aDequeLHS).swap(this->aDequeRHS);

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    EXPECT_TRUE(std::equal((this->aDequeRHS).begin(),(this->aDequeRHS).end(),vec.begin()));
    std::reverse(vec.begin(),vec.end());
    EXPECT_TRUE(std::equal((this->aDequeLHS).begin(),(this->aDequeLHS).end(),vec.begin()));
}











