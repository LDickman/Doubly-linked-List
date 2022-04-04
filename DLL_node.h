// FILE: DLL_node.h
// Header file for Lab 4, CS 223, Winter 2018
// Barb Wahl, 2-15-16
// Revised, 2-18-18
//
// ********** DO NOT CHANGE THIS FILE **********
//
// PROVIDES: A class for a node in a circular doubly-linked list, all within
//   the namespace cs223_dll
//
// TYPEDEF for the DLL_node class:
//   Each node of the list contains an item of data, a pointer to the previous
//   node, and a pointer to the next node.
//   - The type of the data is defined as DLL_node::value_type in a typedef
//     statement.
//   - value_type may be any of the built-in C++ types (int, char, ...) or
//     any class with a copy constructor, an assignment operator (=), and a
//     test for equality (==).
//
// ************************************************************************
// Note: Some of the following functions have a return value which is a pointer
//       to a DLL_node object (DLL_node*).  Each of these functions comes in
//       two versions:
//       - a const version, where the return type is const DLL_node *
//       - a non-const version, where the return type is DLL_node *
//
// EXAMPLES:
//       const DLL_node * c;
//       c->next() // activates the const version of next() on the const
//                     DLL_node referenced by c
//
//       DLL_node * p;
//       p->next() // activates the non-const version of next() on the DLL_node
//                     referenced by p
//
// ************************************************************************
// MEMBER FUNCTIONS for the DLL_node class:
//
//   NODE CONSTRUCTOR -- provides default values for all three parameters
//   DLL_node( const value_type& init_data = value_type(),
//        DLL_node* init_prev = NULL,
//        DLL_node* init_next = NULL )
//   Postcondition: The node contains the specified data and links.
//   Note: The default value for init_data is obtained from the call to
//         value_type(), which is an alias for the default constructor / value
//         initializer for the type represented by value_type.
//
//   void set_data(const value_type& new_data)
//   Postcondition: The node now contains the specified new data.
//
//   void set_prev(DLL_node* new_link)
//   Postcondition: The node's previous pointer is reset to equal new_link.
//
//   void set_link(DLL_node* new_link)
//   Postcondition: The node's next pointer is reset to equal new_link.
//
//   value_type data() const
//   Postcondition: The return value is the data from this node.
//
//   const DLL_node* prev() const <----- const version
//   DLL_node* prev() <----------------- non-const version
//   See the Note (above) about the const version and non-const versions.
//   Postcondition: The return value is the previous pointer from this node.
//
//   const DLL_node* next() const <----- const version
//   DLL_node* next() <----------------- non-const version
//   See the Note (above) about the const version and non-const versions.
//   Postcondition: The return value is the next pointer from this node.
//
// ************************************************************************

#ifndef DLL_node_H
#define DLL_node_H
#include "Person.h"   // so we can store Person data

namespace cs223_dll
{
class DLL_node
{
 public:
    // TYPEDEF
    typedef Person value_type;

    // CONSTRUCTOR with default arguments
    DLL_node(const value_type& init_data = value_type(),
           DLL_node* init_prev = NULL,
           DLL_node* init_next = NULL)
    {
        data_field = init_data; prev_field = init_prev; next_field = init_next;
    }

    // setters
    void set_data(const value_type& new_data) { data_field = new_data; }
    void set_prev(DLL_node* new_link)         { prev_field = new_link; }
    void set_next(DLL_node* new_link)         { next_field = new_link; }

    // data()
    value_type data() const { return data_field; }

    // prev()
    const DLL_node* prev() const { return prev_field; }
          DLL_node* prev()       { return prev_field; }

    // next()
    const DLL_node* next() const { return next_field; }
          DLL_node* next()       { return next_field; }

 private:
    value_type data_field;
    DLL_node* prev_field;
    DLL_node* next_field;
};  // end DLL_node class

}  // end namespace cs223_dll

#endif
