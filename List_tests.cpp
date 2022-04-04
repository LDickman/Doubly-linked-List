// FILE: List_tests.cpp
// CS 223 Winter 2018, Lab 4
//
// Student Name: Lauren Dickman
// Date: 3/4/2020
//
// List class testing for a circular DLL with sentinel node.
//

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "DLL_node.h"
#include "List.h"
#include "Person.h"
#include "gtest/gtest.h"  // declares the testing framework

#define BACKWARD_HAS_DW 1
#include "backward.hpp"
backward::SignalHandling sh;

using namespace std;
using namespace cs223_dll;

/*
 Tests for the List class are given below. For this lab,
 you are responsible for writing any tests not already provided.

 Write tests ONE AT A TIME as you go through the
 Test-Driven Development (TDD) process.

 REMINDER: For 2-argument EXPECTS and ASSERTS, the first argument is
 the actual value from executing the function, and the second argument
 is the expected correct value.

 DO NOT CHANGE THE ORDER OF THE TESTS
*/

namespace
{
// create some global Person objects to use in tests
Person Mickey_Mouse("Mickey", "Mouse", 45);
Person Minnie_Mouse("Minnie", "Mouse", 45);
Person Peter_Pan("Peter", "Pan", 100);
Person Ziggy_Wilson("Ziggy", "Wilson", 5);
Person Skye_Wilson("Skye", "Wilson", 4);
Person Mister_Gray("Mister", "Gray", 10);
Person Xerea_Cat("Xerea", "Cat", 5);
Person Dopey_Dwarf("Dopey", "Dwarf", 73);
Person Sleepy_Dwarf("Sleepy", "Dwarf", 73);
Person Happy_Dwarf("Happy", "Dwarf", 73);
Person Snow_White("Snow", "White", 21);

// an array of 10 persons
Person person[] = {Mickey_Mouse, Minnie_Mouse, Peter_Pan,   Ziggy_Wilson,
                   Skye_Wilson,  Mister_Gray,  Dopey_Dwarf, Sleepy_Dwarf,
                   Happy_Dwarf,  Snow_White};

// default constructor, isEmpty
// TestDefaultConstructorANDisEmpty (PROVIDED)
//   - PRVD_ListWithJustSentinel_isEmpty
//

TEST(TestDefaultConstructorANDisEmpty, PRVD_ListWithJustSentinel_isEmpty)
{
    List L1;
    EXPECT_TRUE(L1.is_empty());
}

// head_insert, front, back
// TestHeadInsert_with_Front_and_Back (PROVIDED)
//   - PRVD_HeadInsert_into_EmptyList
//   - PRVD_HeadInsert_into_Length1_List
//   - PRVD_HeadInsert_into_Length2_List
//

TEST(TestHeadInsert_with_Front_and_Back, PRVD_HeadInsert_into_EmptyList)
{
    List L1;
    L1.head_insert(Happy_Dwarf);
    ASSERT_FALSE(L1.is_empty());
    EXPECT_EQ(L1.front(), Happy_Dwarf);
    EXPECT_EQ(L1.back(), Happy_Dwarf);
}

TEST(TestHeadInsert_with_Front_and_Back, PRVD_HeadInsert_into_Length1_List)
{
    List L1;
    L1.head_insert(Happy_Dwarf);
    L1.head_insert(Minnie_Mouse);
    EXPECT_EQ(L1.front(), Minnie_Mouse);
    EXPECT_EQ(L1.back(), Happy_Dwarf);
}

TEST(TestHeadInsert_with_Front_and_Back, PRVD_HeadInsert_into_Length2_List)
{
    List L1;
    L1.head_insert(Happy_Dwarf);
    L1.head_insert(Minnie_Mouse);
    L1.head_insert(Ziggy_Wilson);
    EXPECT_EQ(L1.front(), Ziggy_Wilson);
    EXPECT_EQ(L1.back(), Happy_Dwarf);
}

// tail_insert
// TestTailInsert_with_Front_and_Back (PROVIDED)
//   - PRVD_HeadInsert_into_EmptyList
//   - PRVD_HeadInsert_into_Length1_List
//   - PRVD_HeadInsert_into_Length2_List
//

TEST(TestTailInsert_with_Front_and_Back, PRVD_TailInsert_into_EmptyList)
{
    List L1;
    L1.tail_insert(Happy_Dwarf);
    ASSERT_FALSE(L1.is_empty());
    EXPECT_EQ(L1.front(), Happy_Dwarf);
    EXPECT_EQ(L1.back(), Happy_Dwarf);
}

TEST(TestTailInsert_with_Front_and_Back, PRVD_TailInsert_into_Length1_List)
{
    List L1;
    L1.tail_insert(Happy_Dwarf);
    L1.tail_insert(Minnie_Mouse);
    EXPECT_EQ(L1.back(), Minnie_Mouse);
    EXPECT_EQ(L1.front(), Happy_Dwarf);
}

TEST(TestTailInsert_with_Front_and_Back, PRVD_TailInsert_into_Length2_List)
{
    List L1;
    L1.tail_insert(Happy_Dwarf);
    L1.tail_insert(Minnie_Mouse);
    L1.tail_insert(Ziggy_Wilson);
    EXPECT_EQ(L1.back(), Ziggy_Wilson);
    EXPECT_EQ(L1.front(), Happy_Dwarf);
}

// TestPointersAfterInsert (PROVIDED)
//   - PRVD_HeadInsert_into_Length2_List_then_Traverse_BackToFront
//   - PRVD_TailInsert_into_Length2_List_then_Traverse_BackToFront
//   - PRVD_HeadInsert_into_Length2_List_then_Traverse_FrontToBack
//   - PRVD_TailInsert_into_Length2_List_then_Traverse_FrontToBack
//

// Make sure the prev pointers are being set correctly
TEST(TestPointersAfterInsert,
     PRVD_HeadInsert_into_Length2_List_then_Traverse_BackToFront)
{
    List L1;
    L1.head_insert(Happy_Dwarf);
    L1.head_insert(Minnie_Mouse);
    L1.head_insert(Ziggy_Wilson);
    const DLL_node* curr = L1.get_head_ptr()->prev();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->prev();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

TEST(TestPointersAfterInsert,
     PRVD_TailInsert_into_Length2_List_then_Traverse_BackToFront)
{
    List L1;
    L1.tail_insert(Ziggy_Wilson);
    L1.tail_insert(Minnie_Mouse);
    L1.tail_insert(Happy_Dwarf);
    const DLL_node* curr = L1.get_head_ptr()->prev();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->prev();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

// Make sure the next pointers are being set correctly
TEST(TestPointersAfterInsert,
     PRVD_HeadInsert_into_Length2_List_then_Traverse_FrontToBack)
{
    List L1;
    L1.head_insert(Happy_Dwarf);
    L1.head_insert(Minnie_Mouse);
    L1.head_insert(Ziggy_Wilson);
    const DLL_node* curr = L1.get_head_ptr()->next();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->next();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

TEST(TestPointersAfterInsert,
     PRVD_TailInsert_into_Length2_List_then_Traverse_FrontToBack)
{
    List L1;
    L1.tail_insert(Ziggy_Wilson);
    L1.tail_insert(Minnie_Mouse);
    L1.tail_insert(Happy_Dwarf);
    const DLL_node* curr = L1.get_head_ptr()->next();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Happy_Dwarf);
    curr = curr->next();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

// contains
// TestContains (PROVIDED)
//   - PRVD_EmptyList_so_Contains_is_False
//   - PRVD_Length1_List_and_Contains_is_True
//   - PRVD_Length1_List_and_Contains_is_False
//   - PRVD_Length4_List_and_Contains_is_True_with_Item_at_Tail
//   - PRVD_Length4_List_and_Contains_returns_False
//

TEST(TestContains, PRVD_EmptyList_so_Contains_is_False)
{
    List L1;
    EXPECT_FALSE(L1.contains(Happy_Dwarf));
}

TEST(TestContains, PRVD_Length1_List_and_Contains_is_True)
{
    List L1;
    L1.head_insert(Happy_Dwarf);
    EXPECT_TRUE(L1.contains(Happy_Dwarf));
}

TEST(TestContains, PRVD_Length1_List_and_Contains_is_False)
{
    List L1;
    L1.head_insert(Happy_Dwarf);
    EXPECT_FALSE(L1.contains(Ziggy_Wilson));
}

TEST(TestContains, PRVD_Length4_List_and_Contains_is_True_with_Item_at_Tail)
{
    List L1({Mickey_Mouse, Snow_White, Happy_Dwarf, Ziggy_Wilson});
    EXPECT_TRUE(L1.contains(Ziggy_Wilson));
}

TEST(TestContains, PRVD_Length4_List_and_Contains_returns_False)
{
    List L1({Mickey_Mouse, Snow_White, Happy_Dwarf, Ziggy_Wilson});
    EXPECT_FALSE(L1.contains(Skye_Wilson));
}

//*******************************************************************
// Student To Do: Implement described tests for Brack Indexing []
//*******************************************************************

//
// TestBracketIndexing (NOT PROVIDED - Student must write)
//   - STU_Length1_List_Index_0
//   - STU_Length3_List_Index_0
//   - STU_Length3_List_Index_1
//   - STU_Length3_List_Index_2
//

// WRITE YOUR TestBracketIndexing TESTS HERE.
// Please create your own Persons for the tests that you write.
Person Captain_America("Steve", "Rogers", 70);
Person Iron_Man("Tony", "Stark", 35);
Person The_Hulk("Bruce", "Banner", 27);
Person Spider_Man("Peter", "Parker", 16);
Person Dead_Pool("Wade", "Wilson", 40);
Person Sorcerer_Supreme("Stephan", "Strange", 44);
Person God_Mischief("Loki", "Odinson", 1000);
Person God_Thunder("Thor", "Odinson", 1010);
Person Bat_Man("Bruce", "Wayne", 33);
Person Super_Man("Clark", "Kent", 73);
Person Winter_Soldier("Bucky", "Barnes", 73);

// an array of 10 persons
Person myperson[] = {Captain_America, Iron_Man,      The_Hulk,
                     Spider_Man,      Dead_Pool,     Sorcerer_Supreme,
                     God_Mischief,    God_Thunder,   Bat_Man,
                     Super_Man,       Winter_Soldier};

TEST(TestBracketIndexing, STU_Length1_List_Index_0)
{
    List L1;
    L1.head_insert(Dead_Pool);
    EXPECT_EQ(L1[0], Dead_Pool);
}

TEST(TestBracketIndexing, STU_Length3_List_Index_0)
{
    List L1({Captain_America, Winter_Soldier, Iron_Man});
    EXPECT_EQ(L1[0], Captain_America);
}

TEST(TestBracketIndexing, STU_Length3_List_Index_1)
{
    List L1({God_Thunder, The_Hulk, God_Mischief});
    EXPECT_EQ(L1[1], The_Hulk);
}

TEST(TestBracketIndexing, STU_Length3_List_Index_2)
{
    List L1({Iron_Man, Spider_Man, Dead_Pool});
    EXPECT_EQ(L1[2], Dead_Pool);
}

// head_remove
// TestHeadRemove (PROVIDED)
//   - PRVD_HeadRemove_from_EmptyList_returns_False
//   - PRVD_HeadRemove_from_Length1_List_returns_True
//   - PRVD_HeadRemove_from_Length3_List_returns_True
//

TEST(TestHeadRemove, PRVD_HeadRemove_from_EmptyList_returns_False)
{
    List L1;
    EXPECT_FALSE(L1.head_remove());
}

TEST(TestHeadRemove, PRVD_HeadRemove_from_Length1_List_returns_True)
{
    List L1({Happy_Dwarf});
    EXPECT_TRUE(L1.head_remove());
    EXPECT_TRUE(L1.is_empty());
}

TEST(TestHeadRemove, PRVD_HeadRemove_from_Length3_List_returns_True)
{
    List L1({Happy_Dwarf, Snow_White, Mickey_Mouse});
    EXPECT_TRUE(L1.head_remove());
    EXPECT_EQ(L1.front(), Snow_White);
    EXPECT_TRUE(L1.head_remove());
    EXPECT_EQ(L1.front(), Mickey_Mouse);
    EXPECT_TRUE(L1.head_remove());
    EXPECT_TRUE(L1.is_empty());
}

// tail_remove
// TestTailRemove (PROVIDED)
//   - PRVD_TailRemove_from_EmptyList_returns_False
//   - PRVD_TailRemove_from_Length1_List_returns_True
//   - PRVD_TailRemove_from_Length3_List_returns_True
//

TEST(TestTailRemove, PRVD_TailRemove_from_EmptyList_returns_False)
{
    List L1;
    EXPECT_FALSE(L1.tail_remove());
}

TEST(TestTailRemove, PRVD_TailRemove_from_Length1_List_returns_True)
{
    List L1({Happy_Dwarf});
    EXPECT_TRUE(L1.tail_remove());
    EXPECT_TRUE(L1.is_empty());
}

TEST(TestTailRemove, PRVD_TailRemove_from_Length3_List_returns_True)
{
    List L1({Happy_Dwarf, Snow_White, Mickey_Mouse});
    EXPECT_TRUE(L1.tail_remove());
    EXPECT_EQ(L1.back(), Snow_White);
    EXPECT_TRUE(L1.tail_remove());
    EXPECT_EQ(L1.back(), Happy_Dwarf);
    EXPECT_TRUE(L1.tail_remove());
    EXPECT_TRUE(L1.is_empty());
}

// TestPointersAfterRemove (PROVIDED)
//   - PRVD_HeadRemove_from_Length3_List_then_Traverse_BackToFront
//   - PRVD_TailRemove_from_Length3_List_then_Traverse_BackToFront
//   - PRVD_TailRemove_from_Length3_List_then_Traverse_FrontToBack
//   - PRVD_HeadRemove_from_Length3_List_then_Traverse_FrontToBack
//

// Make sure the prev pointers are being set correctly
TEST(TestPointersAfterRemove,
     PRVD_HeadRemove_from_Length3_List_then_Traverse_BackToFront)
{
    List L1({Happy_Dwarf, Snow_White, Mickey_Mouse});
    L1.head_remove();
    const DLL_node* curr = L1.get_head_ptr()->prev();
    EXPECT_EQ(curr->data(), Mickey_Mouse);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Snow_White);
    curr = curr->prev();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

TEST(TestPointersAfterRemove,
     PRVD_TailRemove_from_Length3_List_then_Traverse_BackToFront)
{
    List L1({Ziggy_Wilson, Minnie_Mouse, Happy_Dwarf});
    L1.tail_remove();
    const DLL_node* curr = L1.get_head_ptr()->prev();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->prev();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->prev();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

// Make sure the next pointers are being set correctly
TEST(TestPointersAfterRemove,
     PRVD_HeadRemove_from_Length3_List_then_Traverse_FrontToBack)
{
    List L1({Happy_Dwarf, Minnie_Mouse, Ziggy_Wilson});
    L1.head_remove();
    const DLL_node* curr = L1.get_head_ptr()->next();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->next();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

TEST(TestPointersAfterRemove,
     PRVD_TailRemove_from_Length3_List_then_Traverse_FrontToBack)
{
    List L1({Ziggy_Wilson, Minnie_Mouse, Happy_Dwarf});
    L1.tail_remove();
    const DLL_node* curr = L1.get_head_ptr()->next();
    EXPECT_EQ(curr->data(), Ziggy_Wilson);
    curr = curr->next();
    EXPECT_EQ(curr->data(), Minnie_Mouse);
    curr = curr->next();
    EXPECT_EQ(L1.get_head_ptr(), curr);
}

//*******************************************************************
// Begin Student To Do: Implement the tests for remove_first_of
//*******************************************************************

// TestRemoveFirstOf
//   - STU_EmptyList_so_RemoveFirstOf_returns_False
//   - STU_Length1_List_and_RemoveFirstOf_returns_True
//   - STU_Length1_List_and_RemoveFirstOf_returns_False
//   - STU_Length4_List_with_All_Items_Diff_and_RemoveFirstOf_returns_True_with_TailItem_Removed
//   - STU_Length4_List_with_All_Items_Diff_and_RemoveFirstOf_returns_False
//   - STU_Length4_List_with_Same_2ndAND4th_and_RemoveFirstOf_returns_True_with_2ndItem_Removed

// WRITE YOUR TestRemoveFirstOf TESTS HERE.
// Please create your own Persons for the tests that you write.

TEST(TestRemoveFirstOf, STU_EmptyList_so_RemoveFirstOf_returns_False)
{
    List L1;
    EXPECT_FALSE(L1.remove_first_of(Spider_Man));
}

TEST(TestRemoveFirstOf, STU_Length1_List_and_RemoveFirstOf_returns_True)
{
    List L1;
    L1.head_insert(Bat_Man);
    EXPECT_TRUE(L1.remove_first_of(Bat_Man));
    List L2;
    EXPECT_TRUE(L1 == L2);
}

TEST(TestRemoveFirstOf, STU_Length1_List_and_RemoveFirstOf_returns_False)
{
    List L1;
    L1.head_insert(God_Mischief);
    EXPECT_FALSE(L1.remove_first_of(God_Thunder));
    List L2;
    L2.head_insert(God_Mischief);
    EXPECT_TRUE(L1 == L2);
}

TEST(
    TestRemoveFirstOf,
    STU_Length4_List_with_All_Items_Diff_and_RemoveFirstOf_returns_True_with_TailItem_Removed)
{
    List L1({Super_Man, Sorcerer_Supreme, Iron_Man, Winter_Soldier});
    L1.tail_remove();
    EXPECT_TRUE(L1.remove_first_of(Iron_Man));
    List L2({Super_Man, Sorcerer_Supreme});
    EXPECT_TRUE(L1 == L2);
}

TEST(TestRemoveFirstOf,
     STU_Length4_List_with_All_Items_Diff_and_RemoveFirstOf_returns_False)
{
    List L1({Spider_Man, Sorcerer_Supreme, God_Mischief, God_Thunder});
    EXPECT_FALSE(L1.remove_first_of(Super_Man));
    List L2({Spider_Man, Sorcerer_Supreme, God_Mischief, God_Thunder});
    EXPECT_TRUE(L1 == L2);
}

TEST(
    TestRemoveFirstOf,
    STU_Length4_List_with_Same_2ndAND4th_and_RemoveFirstOf_returns_True_with_2ndItem_Removed)
{
    List L1({Dead_Pool, The_Hulk, Captain_America, The_Hulk});
    EXPECT_TRUE(L1.remove_first_of(The_Hulk));
    List L2({Dead_Pool, Captain_America, The_Hulk});
    EXPECT_TRUE(L1 == L2);
}

// clear
// TestClear
//   - PRVD_Clear_EmptyList
//   - PRVD_Clear_Length1_List
//   - PRVD_Clear_Length3_List
//

TEST(TestClear, PRVD_Clear_EmptyList)
{
    List L1;
    L1.clear();
    EXPECT_TRUE(L1.is_empty());
}

TEST(TestClear, PRVD_Clear_Length1_List)
{
    List L1;
    L1.head_insert(Happy_Dwarf);
    L1.clear();
    EXPECT_TRUE(L1.is_empty());
}

TEST(TestClear, PRVD_Clear_Length3_List)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    L1.head_insert(person[2]);
    L1.clear();
    EXPECT_TRUE(L1.is_empty());
}

// copy constructor
// TestCopyConstructor (PROVIDED)
//   - PRVD_Copy_EmptyList
//   - PRVD_Copy_Length1_List
//   - PRVD_Copy_Length3_List
//   - PRVD_Copy_is_Independent_of_Other_List
//

TEST(TestCopyConstructor, PRVD_Copy_EmptyList)
{
    List L1;
    List L2(L1);
    EXPECT_TRUE(L2.is_empty());
}

TEST(TestCopyConstructor, PRVD_Copy_Length1_List)
{
    List L1;
    L1.head_insert(person[0]);
    List L2(L1);
    EXPECT_EQ(L2.front(), person[0]);
    EXPECT_EQ(L2.back(), person[0]);
}

TEST(TestCopyConstructor, PRVD_Copy_Length3_List)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    L1.head_insert(person[2]);
    List L2(L1);
    EXPECT_EQ(L2.front(), person[2]);
    EXPECT_EQ(L2.back(), person[0]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[1]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[0]);
    L2.head_remove();
    EXPECT_TRUE(L2.is_empty());
}

TEST(TestCopyConstructor, PRVD_Copy_is_Independent_of_Other_List)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    L1.head_insert(person[2]);
    List L2(L1);
    L1.clear();
    EXPECT_FALSE(L2.is_empty());
}

// assignment operator
// TestAssignmentOperator (PROVIDED)
//   - PRVD_SelfAssignment
//   - PRVD_Assign_Length3_List_to_Different_Length3_List
//   - PRVD_Assign_Longer_List_to_Shorter_List
//   - PRVD_Assign_Shorter_List_to_Longer_List
//   - PRVD_Assignment_Chaining
//   - PRVD_This_List_is_Independ_of_Other_List
//

TEST(TestAssignmentOperator, PRVD_SelfAssignment)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    L1.head_insert(person[2]);
    L1 = L1;
    EXPECT_EQ(L1.front(), person[2]);
    L1.head_remove();
    EXPECT_EQ(L1.front(), person[1]);
    L1.head_remove();
    EXPECT_EQ(L1.front(), person[0]);
    L1.head_remove();
    EXPECT_TRUE(L1.is_empty());
}

TEST(TestAssignmentOperator, PRVD_Assign_Length3_List_to_Different_Length3_List)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    L1.head_insert(person[2]);
    List L2;
    L2.head_insert(person[3]);
    L2.head_insert(person[4]);
    L2.head_insert(person[5]);
    L2 = L1;
    EXPECT_EQ(L2.front(), person[2]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[1]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[0]);
    L2.head_remove();
    EXPECT_TRUE(L2.is_empty());
}

TEST(TestAssignmentOperator, PRVD_Assign_Longer_List_to_Shorter_List)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    L1.head_insert(person[2]);
    List L2;
    L2.head_insert(person[3]);
    L2.head_insert(person[4]);
    L2 = L1;
    EXPECT_EQ(L2.front(), person[2]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[1]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[0]);
    L2.head_remove();
    EXPECT_TRUE(L2.is_empty());
}

TEST(TestAssignmentOperator, PRVD_Assign_Shorter_List_to_Longer_List)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    List L2;
    L2.head_insert(person[3]);
    L2.head_insert(person[4]);
    L2.head_insert(person[5]);
    L2 = L1;
    EXPECT_EQ(L2.front(), person[1]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[0]);
    L2.head_remove();
    EXPECT_TRUE(L2.is_empty());
}

TEST(TestAssignmentOperator, PRVD_Assignment_Chaining)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    List L2;
    L2.head_insert(person[3]);
    L2.head_insert(person[4]);
    L2.head_insert(person[5]);
    List L3;
    L3.head_insert(person[6]);
    L3.head_insert(person[7]);
    L3 = L2 = L1;

    EXPECT_EQ(L2.front(), person[1]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[0]);
    L2.head_remove();
    EXPECT_TRUE(L2.is_empty());

    EXPECT_EQ(L3.front(), person[1]);
    L3.head_remove();
    EXPECT_EQ(L3.front(), person[0]);
    L3.head_remove();
    EXPECT_TRUE(L3.is_empty());
}

TEST(TestAssignmentOperator, This_List_is_Independent_of_Other_List)
{
    List L1;
    L1.head_insert(person[0]);
    L1.head_insert(person[1]);
    L1.head_insert(person[2]);
    List L2;
    L2.head_insert(person[3]);
    L2.head_insert(person[4]);
    L2.head_insert(person[5]);
    L2 = L1;
    L1.clear();
    EXPECT_EQ(L2.front(), person[2]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[1]);
    L2.head_remove();
    EXPECT_EQ(L2.front(), person[0]);
    L2.head_remove();
    EXPECT_TRUE(L2.is_empty());
}

//
// TestEquivalence (PROVIDED)
//   - PRVD_EmptyList_same_as_Another_EmptyList
//   - PRVD_EmptyList_not_same_as_Length1_List
//   - PRVD_Length3_List_not_same_as_Length3_List_With_Diff_First_Item
//   - PRVD_Length3_List_not_same_as_Length3_List_With_Diff_Last_Item
//   - PRVD_Length3_List_not_same_as_Length4_List_With_Same_First_Three_Items
//

TEST(TestEquivalence, PRVD_EmptyList_same_as_Another_EmptyList)
{
    List L1;
    List L2;
    EXPECT_TRUE(L1 == L2);
}

TEST(TestEquivalence, PRVD_EmptyList_not_same_as_Length1_List)
{
    List L1;
    List L2;

    L1.head_insert(Skye_Wilson);
    EXPECT_FALSE(L1 == L2);
    EXPECT_FALSE(L2 == L1);
}

TEST(TestEquivalence,
     PRVD_Length3_List_not_same_as_Length3_List_With_Diff_First_Item)
{
    List L1({Mister_Gray, Skye_Wilson, Ziggy_Wilson});
    List L2({Xerea_Cat, Skye_Wilson, Ziggy_Wilson});

    EXPECT_FALSE(L1 == L2);
    EXPECT_FALSE(L2 == L1);
}

TEST(TestEquivalence,
     PRVD_Length3_List_not_same_as_Length3_List_With_Diff_Last_Item)
{
    List L1({Skye_Wilson, Ziggy_Wilson, Mister_Gray});
    List L2({Skye_Wilson, Ziggy_Wilson, Xerea_Cat});

    EXPECT_FALSE(L1 == L2);
    EXPECT_FALSE(L2 == L1);
}

TEST(TestEquivalence,
     PRVD_Length3_List_same_as_Length3_List_With_Same_Items_Same_Order)
{
    List L1({Skye_Wilson, Ziggy_Wilson, Mister_Gray});
    List L2({Skye_Wilson, Ziggy_Wilson, Mister_Gray});

    EXPECT_TRUE(L1 == L2);
}

TEST(TestEquivalence,
     PRVD_Length3_List_not_same_as_Length4_List_With_Same_First_Three_Items)
{
    List L1({Skye_Wilson, Ziggy_Wilson, Mister_Gray});
    List L2({Skye_Wilson, Ziggy_Wilson, Mister_Gray, Xerea_Cat});

    EXPECT_FALSE(L1 == L2);
    EXPECT_FALSE(L2 == L1);
}

//
// TestStreamOutput (PROVIDED)
//   - PRVD_Send_EmptyList_to_OutputStream
//   - PRVD_Send_Length1_List_to_OutputStream
//   - PRVD_Send_Length3_List_to_OutputStream
//

TEST(TestStreamOutput, PRVD_Send_EmptyList_to_OutputStream)
{
    stringstream out;
    List L1;
    out << L1;
    EXPECT_EQ(out.str(), "Empty List\n");
}

TEST(TestStreamOutput, PRVD_Send_Length1_List_to_OutputStream)
{
    stringstream out;
    List L1;
    L1.head_insert(Skye_Wilson);
    out << L1;
    EXPECT_EQ(out.str(), "List:\nPerson: Skye Wilson, age 4\n");
}

TEST(TestStreamOutput, PRVD_Send_Length3_List_to_OutputStream)
{
    stringstream out;
    List L1({Mister_Gray, Skye_Wilson, Ziggy_Wilson});
    string correct = "List:\n";
    correct += "Person: Mister Gray, age 10\n";
    correct += "Person: Skye Wilson, age 4\n";
    correct += "Person: Ziggy Wilson, age 5\n";
    out << L1;
    EXPECT_EQ(out.str(), correct);
}

}  // namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
