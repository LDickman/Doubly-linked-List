// FILE: List.cpp
// CS 223 Winter 2018, Lab 4
//
// Student Name: Lauren Dickman
// Date: 3/4/2020
//
// List class implementation for a circular doubly-linked list with sentinel
// node.
//
// Instance data:
//    Every List has a pointer (called "head_ptr") to its sentinel node.
//
// Class invariants:
//    1. All the list nodes, including the sentinel node, are stored in
//       dynamic memory.
//    2. The head pointer for the list ALWAYS points to the sentinel node.
//    3. The sentinel node's data is always the default value for
//       DLL_node::value_type.
//    4. For an EMPTY list, the sentinel node's links (prev, next) refer to
//       the sentinel node itself.
//
// NOTE 1: The DLL_node class is already completely implemented in DLL_node.h.
//
// NOTE 2: Use `DLL_node::value_type` to refer to the type of data stored in
//         a node.
//

#include "List.h"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

#include "DLL_node.h"
#include "Person.h"

using namespace std;

namespace cs223_dll
{
// Private helper method. Use for diagnostics, to print out node info.
// Example use:
// cout << *head_ptr     -- Prints info on sentinel node
ostream& operator<<(ostream& out, const DLL_node& n)
{
    out << "Node at: " << &n << "\n"
        << "\tdata: " << n.data() << "\n"
        << "\tprev: " << n.prev() << "\n"
        << "\tnext: " << n.next() << endl;
    return out;
}

// setup_sentinel()
// private helper function for use by the constructors.
// Postcondition: head_ptr points to the sentinel node for an empty list
void List::setup_sentinel()
{
    head_ptr = new DLL_node;
    head_ptr->set_prev(head_ptr);
    head_ptr->set_next(head_ptr);
}

// default constructor
// Postcondition: the list has no items (just a sentinel node)
List::List()
{
    setup_sentinel();
}

// copy constructor
// Postcondition: The new list is an independent copy of `other`.
//    Subsequent changes to one of the lists will *not* affect the
//    other list.
List::List(const List& other)
{
    setup_sentinel();
    DLL_node* curr = other.head_ptr->next();
    while (curr != other.head_ptr)
    {
        tail_insert(curr->data());
        curr = curr->next();
    }
}

// Initializer list constructor, PROVIDED
// Creates a list with initial values provided by an initialization
// list. For example the declaration List L1({ A, B, C });
// creates a list with the three values in order.
List::List(std::initializer_list<DLL_node::value_type> l)
{
    setup_sentinel();
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        tail_insert(*it);
    }
}

// destructor - test it indirectly by checking for memory leaks
List::~List()
{
    this->clear();
    delete head_ptr;
}

// is_empty - checks if the list is empty
// Postcondition: Returns true if there are no items in the list.
bool List::is_empty() const
{
    DLL_node* first = head_ptr->next();
    DLL_node* last = head_ptr->prev();
    if (first == head_ptr && last == head_ptr)
    {
        return true;
    }
    return false;
}

// front - get the value at the front of the list
// Precondition: This list is not empty.
// Postcondition: Return value is a copy of the value stored at
//    the front of the list.
DLL_node::value_type List::front() const
{
    DLL_node* first = head_ptr->next();
    return first->data();
}

// back - get the value at the end of the list
// Precondition: This list is not empty.
// Postcondition: Return value is a copy of the value stored at
//    the back of the list.
DLL_node::value_type List::back() const
{
    DLL_node* last = head_ptr->prev();
    return last->data();
}

// contains - checks for an item in the list
// Postcondition: Returns true if there is an item equivalent to
//    `val` in this list.
bool List::contains(value_type val) const
{
    DLL_node* curr = head_ptr->next();
    while (curr != head_ptr)
    {
        if (curr->data() == val)
        {
            return true;
        }
        curr = curr->next();
    }
    return false;
}

// Implement the bracket-indexing operator as a member function, operator[]
// Precondition:  i >= 0
// Precondition:  the list has at least i+1 items
// Postcondition: returns the ith item in the list, where indexing begins
//    with 0
// EXAMPLE: If myList is <D, O, G>, then myList[0] returns 'D',
//    myList[1] returns 'O', and myList[2] returns 'G'.
DLL_node::value_type List::operator[](size_t i) const
{
    DLL_node* count;
    size_t ans;
    ans = 0;
    for (count = head_ptr->next(); count != head_ptr; count = count->next())
    {
        ++ans;
        if ((ans - 1) == i)
        {
            return count->data();
        }
    }
}

// head_insert - add an item to the front of the list
// Postcondition: The list has one more node than before, and the
//    value `val` is stored at the front of the list.
// EXAMPLE: If the list had items:  <r, o, n, t>, and then the call was
//    to head_insert('f'), the list now has items: <f, r, o, n, t>
void List::head_insert(value_type val)
{
    DLL_node* new_ptr;
    new_ptr = new DLL_node(val, head_ptr, head_ptr->next());
    head_ptr->next()->set_prev(new_ptr);
    head_ptr->set_next(new_ptr);
}

// tail_insert - add an item to the end of the list
// Postcondition: The list has one more node than before, and the
//    value `val` is stored at the end of the list.
// EXAMPLE: If the list had items:  <p, i, g>, and then the call was
//    to tail_insert('g'), the list now has items: <p, i, g, g>
void List::tail_insert(value_type val)
{
    DLL_node* new_ptr;
    new_ptr = new DLL_node(val, head_ptr->prev(), head_ptr);
    head_ptr->prev()->set_next(new_ptr);
    head_ptr->set_prev(new_ptr);
}

// head_remove - remove an item from the front of the list
// Postcondition:  Return value is `true` iff an item was removed.
//    If the list was empty before head_remove(), return value is
//    `false`.
// EXAMPLE:  If the list had items <f, r, o, g> before the call to
//    head_remove(), after the call the list has: <r, o, g>
bool List::head_remove()
{
    if (is_empty())
    {
        return false;
    }
    DLL_node* remove_ptr = head_ptr->next();
    DLL_node* move_ptr = remove_ptr->next();
    head_ptr->set_next(move_ptr);
    move_ptr->set_prev(head_ptr);
    delete remove_ptr;
    return true;
}

// tail_remove - remove an item from the end of the list
// Postcondition:  Return value is `true` iff an item was removed.
//    If the list was empty before tail_remove(), return value is
//    `false`.
// EXAMPLE:  If the list had items <c, a, t, s> before the call to
//    tail_remove(), after the call the list has: <c, a, t>
bool List::tail_remove()
{
    if (is_empty())
    {
        return false;
    }
    else
    {
        DLL_node* remove_ptr;
        DLL_node* move_ptr;
        remove_ptr = head_ptr->prev();
        move_ptr = remove_ptr->prev();
        head_ptr->set_prev(move_ptr);
        move_ptr->set_next(head_ptr);
        delete remove_ptr;
        return true;
    }
}

// remove_first_of - tries to remove the first instance of an item
//    from the list
// Postcondition: Removes the front-most item in the list that is
//    equivalent (==) to the given value `val`.  Return value is
//    true iff an item was removed from the list.
// NOTE: If no item in the list is equivalent to `val`, the list
//    is unchanged and `false` is returned.
// EXAMPLE: The list has items: <2, 9, 2>.  A call to
//    remove_first_of('2') will return true, and the list items
//    are now: <9, 2>
bool List::remove_first_of(value_type val)
{
    DLL_node* item;
    DLL_node* move_ptr;
    DLL_node* back_ptr;
    for (item = head_ptr->next(); item != head_ptr; item = item->next())
    {
        if (item->data() == val)
        {
            move_ptr = item->next();
            back_ptr = item->prev();
            move_ptr->set_prev(back_ptr);
            back_ptr->set_next(move_ptr);
            delete item;
            return true;
        }
    }
    return false;
}

// clear - deletes all items from the list
// Postcondition: List is empty.
void List::clear()
{
    while (!(is_empty()))
    {
        head_remove();
    }
}

// assignment operator
// Postcondition: This list becomes an identical -- but indepedent --
//    copy of `other` list.
// NOTE: Returns the updated list to enable chaining of assignment.
List& List::operator=(const List& other)
{
    if (this == &other)
    {
        return *this;
    }
    clear();
    DLL_node* curr = other.head_ptr;
    while (curr->next() != other.head_ptr)
    {
        curr = curr->next();
        tail_insert(curr->data());
    }
    return *this;
}

// list equivalence operator - implementation provided
// Postcondition: returns true when list1 and list2 have the same length
//   and store equivalent elements in the same order: for every position
//   i in the range [0, length of list1), the ith element of list1 is
//   equivalent to the ith element of list2
bool operator==(const List& list1, const List& list2)
{
    const DLL_node* head1 = list1.get_head_ptr();
    const DLL_node* head2 = list2.get_head_ptr();
    const DLL_node* curr1 = head1;
    const DLL_node* curr2 = head2;

    while (curr1->next() != head1 && curr2->next() != head2)
    {
        curr1 = curr1->next();
        curr2 = curr2->next();
        if (curr1->data() != curr2->data()) return false;
    }

    return (curr1->next() == head1 && curr2->next() == head2);
}

// stream output operator - implementation provided
// Postcondition: For lists with length > 0, contents of the list are placed
//    into the given output stream using the following format:
//         "List:\n first_item\n ... \n last_item\n"
//    For lists of length = 0, the following will be placed into the
//    given output stream:
//         "Empty List\n"
//    EXAMPLE: If myList is <rain, grass, flowers>, then cout << myList will
//       produce the following in standard out:
//    List:
//     rain
//     grass
//     flowers
std::ostream& operator<<(std::ostream& out, const List& list)
{
    if (list.is_empty())
    {
        out << "Empty List" << endl;
    }
    else
    {
        out << "List:\n";
        const DLL_node* curr = list.get_head_ptr()->next();
        while (curr != list.get_head_ptr())
        {
            out << curr->data() << endl;
            curr = curr->next();
        }
    }
    return out;
}

}  // namespace cs223_dll
