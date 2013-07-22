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
        //Initial reserved size allocated by T* allocator.
        const size_type static OUTTER_RESERVED = 100;
        const static bool DEBUG_MODE = false;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code>
            // you must use std::equal()
            return true;}

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
            return true;}

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


        // <your data>

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
            return true;}

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
                 * <your documentation>
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    
                    return true;}

                /**
                 * <your documentation>
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                
                // MyDeque* _outer;


            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                iterator (){//MyDeque* outer):_outer(outer) {
                    
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    static value_type dummy;
                    return dummy;}

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
                iterator& operator ++ () {
                    // <your code>
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                iterator& operator -- () {
                    // <your code>
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
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
                 * <your documentation>
                 */
                iterator& operator += (difference_type d) {
                    // <your code>
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -= (difference_type d) {
                    // <your code>
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
                 * <your documentation>
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    // <your code>
                    return true;}

                /**
                 * <your documentation>
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator (/* <your arguments> */) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    static value_type dummy;
                    return dummy;}

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
                    // <your code>
                    assert(valid());
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
                    // <your code>
                    assert(valid());
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
                const_iterator& operator += (difference_type) {
                    // <your code>
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type) {
                    // <your code>
                    assert(valid());
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
            //Calculate the number of rows needed based on size / constant row width.
            size_type rows_needed = 2 * (s / INNER_SIZE) + 1;
            _outer_begin = _astar.allocate(rows_needed);
            //Set size to 0 and the capacity to the size of our initial inner row.
            _size = s;
            _capacity = (rows_needed-1) * INNER_SIZE;

            _outer_very_begin = _outer_begin;
            _outer_end = _outer_begin;
            for (size_type i =0 ; i<(rows_needed-1); ++i){
                _astar.construct(_outer_end);
                ++_outer_end;}
            _outer_very_end = _outer_end;

            _outer_begin += (rows_needed/2);
            _outer_end = _outer_begin;

            _data_begin = _a.allocate(INNER_SIZE);
            _data_end = _data_begin;

            *_outer_begin = _data_begin;

            size_type iter = 1;
            while (iter <= s) {
                //std::cout<<"Inserting element: "<<iter<<std::endl;

                _a.construct(_data_end, v);                
                ++_data_end;

                //Made a new row to fit the next INNER_SIZE elements.
                if ((iter % INNER_SIZE) == 0) {
                    //std::cout<<"Creating new row"<<std::endl;
                    _data_end = _a.allocate(INNER_SIZE);
                    *_outer_end = _data_end;
                    ++_outer_end;
                }
                ++iter;
            }

            assert(valid());}

        /**
         * <your documentation>
         */
        MyDeque (const MyDeque& that) {
            // <your code>
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
        MyDeque& operator = (const MyDeque& rhs) {
            // <your code>
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation>
         */
        reference operator [] (size_type index) {
            //std::cout<<std::endl<<"*************************Indexing []*****************************"<<std::endl;
            // std::cout<<"\nCalling pointers debug from []\n"; 
            pointers_debug();

            size_type newIndex = index + (_data_begin - *_outer_begin);
            size_type outerIndex = newIndex / INNER_SIZE;
            size_type innerIndex = newIndex % INNER_SIZE;
            
            //std::cout<<std::endl<<"Input Index: "<<index<<" Offset Index: "<<newIndex<<" outerIndex: "<<outerIndex<<" innerIndex: "<<innerIndex<<std::endl;
            
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
            pointers_debug();

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
            // <your code>
            return iterator(/* <your arguments> */);}

        /**
         * <your documentation>
         */
        const_iterator begin () const {
            // <your code>
            return const_iterator(/* <your arguments> */);}

        // -----
        // clear
        // -----

        /**
         * <your documentation>
         */
        void clear () {
            if (_capacity > 0) {
                //std::cout<<std::endl<<"*************************Before Clear*****************************"<<std::endl;
                // std::cout<<"\nI'm in clear"<<std::endl;
                pointers_debug();
                pointer* tempOuter = _outer_begin;
                pointer temp = _data_begin;

                if(!(_data_begin == _data_end)) {
                    while (true) {
                    // std::cout<<std::endl<<"Running"<<std::endl;
                    // std::cout<<"deleting: "<<*temp<<std::endl;
                    if(temp!=_data_end)
                        _a.destroy(temp);

                    // std::cout<<"Destroying within row"<<std::endl;

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

                //std::cout<<std::endl<<"*************************After Clear*****************************"<<std::endl;
                pointers_debug();
            }
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () {
            // <your code>
            return iterator(/* <your arguments> */);}

        /**
         * <your documentation>
         */
        const_iterator end () const {
            // <your code>
            return const_iterator(/* <your arguments> */);}

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();}

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () {
            return *_data_begin;}

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<MyDeque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         */
        iterator insert (iterator, const_reference) {
            assert(valid());
            return iterator();}

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () {
            if(static_cast<size_type>(_data_end != *_outer_end+1))  {
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
         * <your documentation>
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

                // std::cout<<"\n At this point we have pointers to handle: "<<_outer_very_end - _outer_very_begin +1<<" Rows"<<std::endl;

                if(bTop){
                    _astar.construct(--_outer_begin);
                    _data_begin = _a.allocate(INNER_SIZE);
                    *_outer_begin = _data_begin;
                    _data_begin+=(INNER_SIZE - 1);
                } else {
                    // std::cout<<"\nBefore Reading in resize_outer\n";
                    _astar.construct(_outer_end);
                    _data_end = _a.allocate(INNER_SIZE);
                    *_outer_end = _data_end;

                    // std::cout<<"\nAfter Reading in resize_outer\n";

                    ++_outer_end;
                }

                // std::cout<<"\n Currently _outer_begin is at: "<<_outer_begin - _outer_very_begin + 1<<std::endl;
                // std::cout<<"\n Currently _outer_end is at: "<<_outer_end - _outer_very_begin + 1<<std::endl;

                _capacity = (((_capacity/INNER_SIZE) * 4) * INNER_SIZE);
            }
        }

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference value) { 
            if (_outer_begin == _outer_end) {
                //First time or after clear
                resize_outer(false);
                // std::cout<<"\nCalled resize for the first time to add: "<<value<<"\n";
                _a.construct(_data_begin, value);
            } else if(static_cast<size_type>((_data_end - *(_outer_end - 1))) < INNER_SIZE) {
                //Have room in existing row.
                // std::cout<<"\nHave space in row to add: "<<value<<"\n";
                _a.construct(_data_end, value);
                ++_data_end; 
            }else{
                //Need to grow.
                if((_outer_end == (_outer_very_end + 1))) {
                    resize_outer(false);
                    // std::cout<<"\nCalling resize to add: "<<value<<"\n";
                    _a.construct(_data_end, value);
                    ++_data_end;
                }else{
                    // std::cout<<"Number of rows we currently have: "<<_outer_very_end - _outer_very_begin + 1<<std::endl;
                    // std::cout<<"Currently in row: "<<_outer_end - _outer_very_begin<<std::endl; 
                    // std::cout<<"Currently in row (counting back): "<<_outer_very_end - _outer_end + 1<<std::endl;
                    // std::cout<<"If condition: "<<(_outer_end == (_outer_very_end + 1))<<std::endl;
                    // std::cout<<"\nHave space but adding new row to add: "<<value<<"\n";
                    _astar.construct(_outer_end);
                    _data_end = _a.allocate(INNER_SIZE);
                    *_outer_end = _data_end;
                    _a.construct(_data_end,value);
                    ++_data_end;
                    ++_outer_end;
                    // std::cout<<"Number of rows we currently have: "<<_outer_very_end - _outer_very_begin + 1<<std::endl;
                    // std::cout<<"Currently in row: "<<_outer_end - _outer_very_begin<<std::endl; 
                    // std::cout<<"Currently in row (counting back): "<<_outer_very_end - _outer_end + 1<<std::endl;
                    // std::cout<<"If condition: "<<(_outer_end == (_outer_very_end + 1))<<std::endl;   
                }}
            assert(valid());
            _size++;
        }

        /**
         * <your documentation>
         */
        void push_front (const_reference value) {
            if (_outer_begin == _outer_end) {
                //First time or after clear
                // std::cout<<"\nCalled resize for the first time to add: "<<value<<"\n";
                resize_outer(false);
                _a.construct(_data_begin, value);
            }else if(_data_begin - *_outer_begin >= 1){
                // std::cout<<"\nHave space in row to add: "<<value<<"\n";
                //Have room in existing row.
                --_data_begin;
                _a.construct(_data_begin, value); 
            }else{
                //Need to grow.
                // std::cout<<"\nCalling resize to add: "<<value<<"\n";
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
            // std::cout<<"Number of rows we currently have: "<<_outer_very_end - _outer_very_begin + 1<<std::endl;
            // std::cout<<"Currently in row: "<<_outer_end - _outer_very_begin<<std::endl; 
            // std::cout<<"Currently in row (counting back): "<<_outer_very_end - _outer_end + 1<<std::endl;
            // std::cout<<"If condition: "<<(_outer_end == (_outer_very_end + 1))<<std::endl;
            // std::cout<<"\nHave space but adding new row to add: "<<value<<"\n";
        }

        void pointers_debug(){
            if (DEBUG_MODE) {
                size_type numberOuter = _outer_end - _outer_begin;
                size_type numberWithinRowBegin = _data_begin - ((_outer_begin==_outer_end)?0:*_outer_begin);
                size_type numberWithinRowEnd = _data_end - ((_outer_end==_outer_begin)?0:*(_outer_end - 1));
                size_type numberOuterBegin = _outer_begin - _outer_very_begin + 1;
                size_type numberOuterEnd = _outer_very_end - _outer_end + 1;
                std::cout<<std::endl<<"Size: "<<_size<<" Capacity: "<<_capacity<<std::endl;
                std::cout<<std::endl<<"Number Outer: "<<numberOuter<<std::endl;
                std::cout<<std::endl<<"Number Begin Row: "<<numberWithinRowBegin<<" Number End Row: "<<numberWithinRowEnd<<std::endl;
                std::cout<<std::endl<<"Number Outer Begin: "<<numberOuterBegin<<" Number Outer End: "<<numberOuterEnd<<std::endl;
            }
        }

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            // <your code>
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * <your documentation>
         */
        size_type size () const {
            return _size;}

        // ----
        // swap
        // ----

        /**
         * <your documentation>
         */
        void swap (MyDeque&) {
            // <your code>
            assert(valid());}};

#endif // Deque_h
