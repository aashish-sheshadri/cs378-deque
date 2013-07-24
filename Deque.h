// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=
#include <iostream>

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -------
// MyDeque
// -------

template < typename T, typename A = std::allocator<T> >
class MyDeque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::template rebind<pointer>::other outer_pointer;

        //Size of inner row arrays.
        const size_type static INNER_SIZE = 5;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * @param lhs is a MyDeque by reference 
         * @param rhs is a MyDeque by reference
         * @return bool true if lhs == rhs
         */
        friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
            if(lhs._size == 0 && rhs._size == 0)
                return true;
            if(lhs._size == 0 || rhs._size == 0)
                return false;
            if(lhs._size!=rhs._size)
                return false;
            return std::equal(const_cast<MyDeque&>(lhs).begin(), const_cast<MyDeque&>(lhs).end(), const_cast<MyDeque&>(rhs).begin());}

        // ----------
        // operator <
        // ----------

        /**
         * @param lhs is a MyDeque by reference 
         * @param rhs is a MyDeque by reference
         * @return bool true if lhs < rhs
         */
        friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
            if(lhs._size == 0 && rhs._size == 0)
                return true;
            if(lhs._size == 0)
                return true;
            if(lhs._size>rhs._size)
                return false;
            return std::lexicographical_compare(const_cast<MyDeque&>(lhs).begin(), const_cast<MyDeque&>(lhs).end(), const_cast<MyDeque&>(rhs).begin(), const_cast<MyDeque&>(rhs).end());}

    private:
        // ----
        // data
        // ----

        allocator_type _a;
        outer_pointer _astar;
        pointer* _outer_begin;
        pointer* _outer_end;
        pointer* _outer_very_begin;
        pointer* _outer_very_end;
        pointer _data_begin;
        pointer _data_end;
        size_type _size;
        size_type _capacity;

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            return _outer_very_begin < _outer_very_end && _capacity >= 0 && _size >= 0;}

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename MyDeque::value_type      value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::pointer         pointer;
                typedef typename MyDeque::outer_pointer outer_pointer;
                typedef typename MyDeque::reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs is a MyDeque::iterator by reference 
                 * @param rhs is a MyDeque::iterator by reference
                 * @return bool true if lhs iterator location is equal to rhs iterator location
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    
                    return lhs._iterator_location == rhs._iterator_location;}

                /**
                 * @param lhs is a MyDeque::iterator by reference 
                 * @param rhs is a MyDeque::iterator by reference
                 * @return bool true if lhs iterator location is not equal to rhs iterator location
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs is a MyDeque::iterator by value 
                 * @param rhs is a difference_type by value
                 * @return an iterator stepped by value rhs
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs is a MyDeque::iterator by value 
                 * @param rhs is a difference_type by value
                 * @return an iterator stepped back by value rhs
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                pointer* _outer_begin;
                pointer _iterator_location;
                size_type _iterator_location_outer;
                size_type _room_on_row;
                pointer _data_end;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return _outer_begin!=0;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * default constructor
                 */
                iterator (){

                } 
                /**
                * @param outer is a pointer to a MyDeque
                * constructs an iterator for a MyDeque
                */
                iterator (MyDeque<T,A>* outer): 
                    _outer_begin(outer->_outer_begin),
                    _iterator_location(outer->_data_begin),
                    _data_end(outer->_data_end)
                {
                    _room_on_row = INNER_SIZE - (_iterator_location - *_outer_begin) - 1;
                    _iterator_location_outer = 0;
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * @return reference to value type 
                 * Operator returns value at iterator location
                 */
                reference operator * () const {
                    return *_iterator_location;
                }

                // -----------
                // operator ->
                // -----------

                /**
                 * @return pointer to value type location 
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * @return iterator reference -- self pre increment
                 */
                iterator& operator ++ () {
                    // std::cout<<"\nRoom on row before ++ : "<<_room_on_row<<" Current Value: "<<_iterator_location<<std::endl;
                    if(_iterator_location == _data_end - 1){
                            ++_iterator_location;
                            // std::cout<<"\nRoom on row before return ++ : "<<_room_on_row<<" Current Value: "<<_iterator_location - _data_end<<std::endl;
                            return *this;}
                    if(_room_on_row) {
                        ++_iterator_location;
                        --_room_on_row;
                    }else{
                        ++_iterator_location_outer;
                        _iterator_location = *(_outer_begin + _iterator_location_outer);
                        _room_on_row = INNER_SIZE - 1;
                    }
                    // std::cout<<"\nRoom on row after ++ : "<<_room_on_row<<" Current Value: "<<_iterator_location - _data_end<<std::endl;

                    assert(valid());
                    return *this;}

                /**
                 * @return iterator -- self post increment 
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * @return iterator reference -- self pre decrement
                 */
                iterator& operator -- () {
                    // std::cout<<"\nRoom on row before -- : "<<_room_on_row<<" Current Value: "<<_iterator_location - _data_end<<std::endl;
                    bool endCase = _iterator_location == _data_end;
                    if(INNER_SIZE - _room_on_row || endCase) {
                        --_iterator_location;
                        if(!endCase)
                            ++_room_on_row;
                    }else{
                        --_iterator_location_outer;
                        _iterator_location = *(_outer_begin + _iterator_location_outer) + INNER_SIZE - 1;
                        _room_on_row = 0;
                    }
                    assert(valid());
                    return *this;}

                /**
                 * @return iterator -- self post decrement
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * @param d is difference_type 
                 * @return iterator by reference stepped by d
                 */
                iterator& operator += (difference_type d) {
                    while(d){
                        ++*this;
                        --d;};
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * @param d is difference_type 
                 * @return iterator by reference stepped back by d
                 */
                iterator& operator -= (difference_type d) {
                    while(d){
                        --*this;
                        --d;};
                    assert(valid());
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename MyDeque::value_type      value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::const_pointer   pointer;
                typedef typename MyDeque::const_reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * @param lhs is a MyDeque::const_iterator by reference 
                 * @param rhs is a MyDeque::const_iterator by reference
                 * @return bool true if lhs iterator location is equal to rhs iterator location
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    return lhs._normal_it == rhs._normal_it;}

                /**
                 * @param lhs is a MyDeque::const_iterator by reference 
                 * @param rhs is a MyDeque::const_iterator by reference
                 * @return bool true if lhs iterator location is not equal to rhs iterator location
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs is a MyDeque::const_iterator by value 
                 * @param rhs is a difference_type by value
                 * @return an const_iterator stepped by value rhs
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs is a MyDeque::const_iterator by value 
                 * @param rhs is a difference_type by value
                 * @return an const_iterator stepped back by value rhs
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                MyDeque::iterator _normal_it;

                // const_pointer* _outer_begin;
                // const_pointer _iterator_location;
                // size_type _iterator_location_outer;
                // size_type _room_on_row;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                * default constructor
                */
                const_iterator(){

                }

                /**
                 *  
                 */
                const_iterator (const MyDeque* outer):_normal_it(const_cast<MyDeque*>(outer)) {
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * @return const_reference to value type 
                 */
                const_reference operator * () const {
                    return const_cast<const_reference>(*_normal_it);}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator ++ () {
                    assert(valid());
                    ++_normal_it;
                    return *this;}

                /**
                 * <your documentation>
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -- () {
                    assert(valid());
                    --_normal_it;
                    return *this;}

                /**
                 * <your documentation>
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator += (difference_type d) {
                    assert(valid());
                    _normal_it += d;
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type d) {
                    assert(valid());
                    _normal_it -= d;
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        explicit MyDeque (const allocator_type& a = allocator_type()) : _a(a) {
            _outer_begin = 0;
            _outer_end = 0;
            _outer_very_begin = 0;
            _outer_very_end = 0;
            _data_end = 0;
            _data_begin = 0;
            _size = 0;
            _capacity = 0;
            assert(valid());}

        /**
         * <your documentation>
         */
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) {            
            // //Calculate the number of rows needed based on size / constant row width.
            // size_type rows_needed = 2 * (s / INNER_SIZE) + 1;
            // _outer_begin = _astar.allocate(rows_needed);
            // //Set size to 0 and the capacity to the size of our initial inner row.
            // _size = s;
            // _capacity = (rows_needed-1) * INNER_SIZE;

            // _outer_very_begin = _outer_begin;
            // _outer_end = _outer_begin;
            // for (size_type i =0 ; i<(rows_needed-1); ++i){
            //     _astar.construct(_outer_end);
            //     ++_outer_end;}
            // _outer_very_end = _outer_end;

            // _outer_begin += (rows_needed/2);
            // _outer_end = _outer_begin;

            // _data_begin = _a.allocate(INNER_SIZE);
            // _data_end = _data_begin;

            // *_outer_begin = _data_begin;

            // size_type iter = 1;
            // while (iter <= s) {
            //     //std::cout<<"Inserting element: "<<iter<<std::endl;

            //     _a.construct(_data_end, v);                
            //     ++_data_end;

            //     //Made a new row to fit the next INNER_SIZE elements.
            //     if ((iter % INNER_SIZE) == 0) {
            //         //std::cout<<"Creating new row"<<std::endl;
            //         _data_end = _a.allocate(INNER_SIZE);
            //         *_outer_end = _data_end;
            //         ++_outer_end;
            //     }
            //     ++iter;

            _outer_begin = 0;
            _outer_end = 0;
            _outer_very_begin = 0;
            _outer_very_end = 0;
            _data_end = 0;
            _data_begin = 0;
            _size = 0;
            _capacity = 0;
            while(s){
                push_back(v);
                --s;
            }
            assert(valid());}

        /**
         * <your documentation>
         */
        MyDeque (const MyDeque& that){//:_a(that._a),_astar(that._astar),_size(that._size) {
            // size_type outerSize = (_size/INNER_SIZE) + 1;
            // _outer_very_begin = _astar.allocate(outerSize);
            // _outer_very_end = _outer_very_begin + outerSize - 1;
            // _outer_begin = _outer_very_begin;
            // _outer_end = _outer_very_begin;
            // _capacity = (outerSize) * INNER_SIZE;
            
            // std::cout<<"\nOuter Size: "<<outerSize<<std::endl;

            // while(outerSize){
            //     _astar.construct(_outer_end);
            //     *_outer_end = _a.allocate(INNER_SIZE);
            //     ++_outer_end;
            //     --outerSize;}

            // _data_begin = *_outer_very_begin;
            // _data_end = 0;
            // uninitialized_copy(_a,const_cast<MyDeque&>(that).begin(),const_cast<MyDeque&>(that).end(),begin());
            // std::cout<<"Begin: "<<*begin()<<" End:"<<back()<<std::endl;
            // _data_begin = *_outer_very_end + _size%INNER_SIZE;


            _outer_begin = 0;
            _outer_end = 0;
            _outer_very_begin = 0;
            _outer_very_end = 0;
            _data_end = 0;
            _data_begin = 0;
            _size = 0;
            _capacity = 0;

            *this = that;

            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         */
        ~MyDeque () {
            this->clear();

            if(_outer_very_begin != 0)
                _astar.deallocate(_outer_very_begin,_outer_very_end - _outer_very_begin + 1);

            _outer_begin = 0;
            _outer_end = 0;
            _outer_very_begin = 0;
            _outer_very_end = 0;
            _data_end = 0;
            _data_begin = 0;
            _size = 0;
            _capacity = 0;
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
         */
        MyDeque& operator = (const MyDeque& that) {
            if (this == &that)
                return *this;
            clear();
            auto temp = const_cast<MyDeque&>(that).begin();
            while(temp!=const_cast<MyDeque&>(that).end()){
                push_back(*temp);
                ++temp;}

            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation>
         */
        reference operator [] (size_type index) {

            size_type newIndex = index + (_data_begin - *_outer_begin);
            size_type outerIndex = newIndex / INNER_SIZE;
            size_type innerIndex = newIndex % INNER_SIZE;
            
            pointer* tempOuter = _outer_begin;
            tempOuter += outerIndex;
            pointer tempInner = *tempOuter;
            tempInner += innerIndex;
            return *tempInner;}

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<MyDeque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * <your documentation>
         */
        reference at (size_type index) {

            size_type newIndex = index + (_data_begin - *_outer_begin);
            size_type outerIndex = newIndex / INNER_SIZE;
            size_type innerIndex = newIndex % INNER_SIZE;

            if((index<0)||(index > _size - 1))
                throw std::out_of_range("MyDeque::MyDeque()");
            
            pointer* tempOuter = _outer_begin;
            tempOuter += outerIndex;
            pointer tempInner = *tempOuter;
            tempInner += innerIndex;
            return *tempInner;}

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<MyDeque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * <your documentation>
         */
        reference back () {
            return *(_data_end - 1);}

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<MyDeque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () {
            return iterator(this);}

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(this);}

        // -----
        // clear
        // -----

        /**
         * Clears deque. 
         */
        void clear () {
            if (_capacity > 0) {
                pointer* tempOuter = _outer_begin;
                pointer temp = _data_begin;

                if(!(_data_begin == _data_end)) {
                    while (true) {
                    if(temp!=_data_end)
                        _a.destroy(temp);

                    if (((*tempOuter+(INNER_SIZE - 1)) == temp)) {
                        // std::cout<<"Deleting row"<<std::endl;
                        _a.deallocate(*(tempOuter),INNER_SIZE);
                        _astar.destroy(tempOuter);
                        ++tempOuter;
                        if(tempOuter == _outer_end)
                            break;
                        temp = *tempOuter;
                    }else{
                    ++temp;}}}

                _outer_begin = _outer_very_begin; 
                _outer_begin += ((_capacity/INNER_SIZE)/2);
                _outer_end = _outer_begin; //This should be set when outer_resize is called
                _data_begin = 0;
                _data_end = 0; 
                _size = 0;

            }
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * @return True if deque is empty. False otherwise.
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * @return Iterator to the end of the deque.
         */
        iterator end () {
            // <your code>
            return iterator(this) += _size;}

        /**
         * @return Read-only iterator to the end of the deque.
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(this);}

        // -----
        // erase
        // -----

        /**
         * Erases a value from deque given by iterator location.
         * @param loc Value to delete.
         * @return Iterator to next location.
         */
        iterator erase (iterator loc) {
            auto prevIt = loc;
            auto nextIt = ++loc;
            auto endIt = end();
            while(nextIt!=endIt){
                *prevIt = *nextIt;
                ++nextIt;
                ++prevIt;}
            pop_back();
            assert(valid());
            return --loc;}

        // -----
        // front
        // -----

        /**
         * @return Reference to value that is at front of deque.
         */
        reference front () {
            return *_data_begin;}

        /**
         * @return Read-only Value that is at front of deque.
         */
        const_reference front () const {
            return const_cast<MyDeque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * Inserts an element at the location of the iterator and pushes remaining elements to the back.
         * @parma loc Location Location to insert an element at.
         * @val Value to insert.
         * @returns Iterator to where the value was placed.
         */
        iterator insert (iterator loc, const_reference val) {
            auto prevIt = loc;
            auto nextIt = ++loc;
            auto endIt = end();
            value_type tempVal;
            while(nextIt!=endIt){
                tempVal = *nextIt;
                *nextIt = *prevIt;
                ++nextIt;
                ++prevIt;}
            push_back(tempVal);
            *(--loc) = val;
            return iterator(loc);}

        // ---
        // pop
        // ---

        /**
         * Pops an element from the back.
         */
        void pop_back () {
            if(static_cast<size_type>(_data_end != (*(_outer_end-1)+1)))  {
                //Not the first element in the row so just destroy it.
                _a.destroy(_data_end-1);
                --_data_end;
                --_size;
            }else{
                //Back of data is the first element in its row, so we also have to deallocate the row it was in.
                _a.destroy(_data_end-1);
                --_size;
                _a.deallocate(*_outer_end,INNER_SIZE);
                _astar.destroy(_outer_end);
                if(_outer_very_begin!=_outer_very_end){
                    --_outer_end;
                    _data_end = *_outer_end + INNER_SIZE;
                } else {
                    _outer_begin = _outer_very_begin; 
                    _outer_begin += ((_capacity/INNER_SIZE)/2);
                    _outer_end = _outer_begin; //This should be set when outer_resize is called
                    _data_begin = 0;
                    _data_end = 0; 
                    _size = 0;
                }
            }

            assert(valid());}

        /**
         * Deletes an element from the front of the deque.
         */
        void pop_front () {
            if(_data_begin != *_outer_begin + INNER_SIZE-1){
                _a.destroy(_data_begin);
                ++_data_begin;
                --_size;
            }else{
                _a.destroy(_data_begin);
                --_size;
                _a.deallocate(*_outer_begin, INNER_SIZE);
                _astar.destroy(_outer_begin);
                if (_outer_very_begin != _outer_very_end) {
                    ++_outer_begin;
                    _data_begin = *_outer_begin;
                } else {
                    //No rows left
                    _outer_begin = _outer_very_begin; 
                    _outer_begin += ((_capacity/INNER_SIZE)/2);
                    _outer_end = _outer_begin; //This should be set when outer_resize is called
                    _data_begin = 0;
                    _data_end = 0; 
                    _size = 0;
                }
            }
            assert(valid());}

        //throw if unable to allocate
        void resize_outer(bool bTop){
            if (_capacity == 0) {
                _outer_begin = _astar.allocate(1);
                _astar.construct(_outer_begin);

                _outer_very_end = _outer_begin;
                _outer_very_begin = _outer_begin;
                
                _outer_end = _outer_begin + 1;

                _data_begin = _a.allocate(INNER_SIZE);
                
                *_outer_begin = _data_begin;
                _data_begin += INNER_SIZE/2;
                _data_end = _data_begin + 1;
                _capacity = INNER_SIZE;
            } else if(_size == 0){
                _astar.construct(_outer_begin);
                _outer_end = _outer_begin + 1;
                _data_begin = _a.allocate(INNER_SIZE);
                *_outer_begin = _data_begin;
                _data_begin += INNER_SIZE/2;
                _data_end = _data_begin + 1;
            } else {
                //create temporary pointers for new allocation
                pointer* new_outer_begin;
                pointer* new_outer_end;
                pointer* old_outer_very_begin = _outer_very_begin;
                pointer* old_outer_very_end = _outer_very_end;

                //allocate outer pointers to manage 4x old memory 
                new_outer_begin = _astar.allocate((_capacity/INNER_SIZE) * 4);
                
                //Reset memory block ponters
                _outer_very_begin = new_outer_begin;
                _outer_very_end = _outer_very_begin + ((_capacity/INNER_SIZE) * 4) - 1; 

                //center _outer_begin and _outer_end
                new_outer_begin += (_capacity/INNER_SIZE);
                new_outer_end = new_outer_begin;

                //copy data from old block to new block
                for(pointer* temp_pointer = _outer_begin; temp_pointer<_outer_end;++temp_pointer){
                    _astar.construct(new_outer_end);
                    *new_outer_end = *temp_pointer;
                    ++new_outer_end;
                }

                //deallocate outer pointers managing the memory block
                pointer* tempBegin = _outer_begin;

                while(tempBegin!=_outer_end){
                    _astar.destroy(tempBegin);
                    ++tempBegin;}

                _astar.deallocate(old_outer_very_begin, (old_outer_very_end - old_outer_very_begin + 1));
                
                //reset block pointers
                _outer_begin = new_outer_begin;
                _outer_end = new_outer_end;


                if(bTop){
                    _astar.construct(--_outer_begin);
                    _data_begin = _a.allocate(INNER_SIZE);
                    *_outer_begin = _data_begin;
                    _data_begin+=(INNER_SIZE - 1);
                } else {
                    _astar.construct(_outer_end);
                    _data_end = _a.allocate(INNER_SIZE);
                    *_outer_end = _data_end;

                    ++_outer_end;
                }


                _capacity = (((_capacity/INNER_SIZE) * 4) * INNER_SIZE);
            }
        }

        // ----
        // push
        // ----

        /**
         * Pushes a value onto the back of the deque.
         * @param value Value you want to push onto the back of the deque.
         */
        void push_back (const_reference value) { 
            if (_outer_begin == _outer_end) {
                //First time or after clear
                resize_outer(false);
                _a.construct(_data_begin, value);
            } else if(static_cast<size_type>((_data_end - *(_outer_end - 1))) < INNER_SIZE) {
                //Have room in existing row.
                _a.construct(_data_end, value);
                ++_data_end; 
            }else{
                //Need to grow.
                if((_outer_end == (_outer_very_end + 1))) {
                    resize_outer(false);
                    _a.construct(_data_end, value);
                    ++_data_end;
                }else{
                    _astar.construct(_outer_end);
                    _data_end = _a.allocate(INNER_SIZE);
                    *_outer_end = _data_end;
                    _a.construct(_data_end,value);
                    ++_data_end;
                    ++_outer_end;
                }}
            assert(valid());
            _size++;
        }

        /**
         * Pushes a value onto the front of the deque.
         * @param value Value you want to push onto the front of the deque.
         */
        void push_front (const_reference value) {
            if (_outer_begin == _outer_end) {
                //First time or after clear
                resize_outer(false);
                _a.construct(_data_begin, value);
            }else if(_data_begin - *_outer_begin >= 1){
                //Have room in existing row.
                --_data_begin;
                _a.construct(_data_begin, value); 
            }else{
                //Need to grow.
                if((_outer_begin == _outer_very_begin) && (_data_begin == *_outer_begin)) {
                    resize_outer(true);
                    _a.construct(_data_begin, value);
                }else{
                    --_outer_begin;
                    _astar.construct(_outer_begin);
                    _data_begin = _a.allocate(INNER_SIZE);
                    *_outer_begin = _data_begin;
                    _data_begin+=(INNER_SIZE-1);
                    _a.construct(_data_begin,value);} }
            assert(valid());
            _size++;
        }

        // ------
        // resize
        // ------

        /**
         * Resizes the container so that it contains n elements.
         * @param s Size you want to resize to
         * @param v Optional value to fill new space with.
         */
        void resize (size_type s, const_reference v = value_type()) {
            while (_size > s) {
                pop_back();
            }
            while (_size != s) {
                push_back(v);
            }
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * @return Returns size of container, e.g. allocated and constructed elements.
         */
        size_type size () const {
            return _size;}

        // ----
        // swap
        // ----

        /**
         * Exchanges the content of the container by the content of x, 
         * which is another deque object containing elements of the same type. Sizes may differ.
         * 
         */
        void swap (MyDeque& that) {
            MyDeque temp;
            temp = *this;
            *this = that;
            that = temp;
            assert(valid());}};

#endif // Deque_h
