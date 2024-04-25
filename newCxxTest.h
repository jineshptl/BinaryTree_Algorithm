// copyright 2022
//
// Created by jinesh patel on 6/24/22.
//

#ifndef HW_6_NEWCXXTEST_H
#define HW_6_NEWCXXTEST_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "AVL_Tree.h"
#include <cxxtest/TestSuite.h>
#include "Binary_Search_Tree.h"
#include "pre_order_traversal.h"


class MyTestSuite1 : public CxxTest::TestSuite {
public:

    void test_Binary_Tree_is_null() {

        Binary_Search_Tree<int> *thing = NULL;
        thing = new AVL_Tree<int>;
        TS_ASSERT(thing->is_null());

        thing->insert(1);
        TS_ASSERT(!thing->is_null());

        thing->erase(1);
        delete thing;
    }

    void test_erase_Binary_Search_tree() {

        Binary_Search_Tree<int> *thing = NULL;
        thing = new AVL_Tree<int>;
        thing->insert(7);
        thing->insert(6);
        thing->insert(5);
        thing->insert(4);

        std::ostringstream tmp;
        thing->erase(4);
        (*thing, tmp, 0);
        TS_ASSERT_EQUALS(tmp.str(), "");

        tmp.clear();
        tmp.str("");
        thing->erase(7);
        pre_order_traversal(*thing, tmp, 0);
        TS_ASSERT_EQUALS(tmp.str(), "6\n  5\n    null\n    null\n  null\n");

        thing->erase(7);
        thing->erase(6);
        thing->erase(5);
        thing->erase(4);
        delete thing;
    }

    void test_insert_Binary_Search_tree() {

        Binary_Search_Tree<int> *thing = NULL;
        thing = new Binary_Search_Tree<int>;
        thing->insert(7);
        thing->insert(6);
        thing->insert(5);
        thing->insert(4);

        std::ostringstream tmp;
        pre_order_traversal(*thing, tmp, 0);
        TS_ASSERT_EQUALS(tmp.str(), "7\n  6\n    5\n      4\n        null\n        null\n      null\n    null\n  null\n");

        thing->erase(7);
        thing->erase(6);
        thing->erase(5);
        thing->erase(4);
        delete thing;

    }

    void test1234 () {
        AVLNode<int> thing(0);
        TS_ASSERT_EQUALS(thing.to_string(), "0: 0");
    }

    void test123456 () {
        Binary_Tree<int> thing(0);
        TS_ASSERT_EQUALS(thing.to_string(), "0\nNULL\nNULL\n");
    }

    void test12345 () {
        BTNode<int> thing(0);
        TS_ASSERT_EQUALS(thing.to_string(), "0");
    }

    void test_find_Binary_Search_tree() {

        Binary_Search_Tree<int> *thing = NULL;
        thing = new AVL_Tree<int>;
        thing->insert(7);
        thing->insert(14);
        thing->insert(8);
        thing->insert(21);

        const int *obj = thing->find(8);
        TS_ASSERT_EQUALS(*obj, 8);

        obj = thing->find(8);
        TS_ASSERT_EQUALS(*obj, 8);
        thing->insert(15);
        obj = thing->find(15);
        TS_ASSERT_EQUALS(*obj, 15);

        obj = NULL;
        delete obj;

        thing->erase(7);
        thing->erase(14);
        thing->erase(8);
        thing->erase(8);
        thing->erase(15);
        delete thing;
    }

    void test_Binary_Tree_leaf() {

        Binary_Search_Tree<int> *thing = NULL;
        thing = new AVL_Tree<int>;
        thing->insert(7);
        TS_ASSERT(thing->is_leaf());

        thing->insert(14);
        thing->insert(21);
        TS_ASSERT(!thing->is_leaf());

        thing->erase(7);
        thing->erase(14);
        thing->erase(21);
        delete thing;
    }

    void test_Binary_tree_data_functions() {

        Binary_Search_Tree<int> *thing2 = NULL;
        thing2 = new AVL_Tree<int>;
        thing2->insert(7);

        TS_ASSERT_EQUALS(thing2->get_data(), 7);
        TS_ASSERT_THROWS_ANYTHING(thing2->get_left_subtree().get_data());
        TS_ASSERT_THROWS_ANYTHING(thing2->get_right_subtree().get_data());

        thing2->insert(14);
        thing2->insert(21);

        TS_ASSERT_EQUALS(thing2->get_data(), 14);
        TS_ASSERT_EQUALS(thing2->get_left_subtree().get_data(), 7);
        TS_ASSERT_EQUALS(thing2->get_right_subtree().get_data(), 21);

        thing2->erase(7);
        thing2->erase(14);
        thing2->erase(21);
        delete thing2;
    }

    void test_Tree_Balancing() {

        Binary_Search_Tree<int> *the_tree = NULL;
        the_tree = new AVL_Tree<int>;
        std::ostringstream pre;

        the_tree->insert(12);
        pre_order_traversal(*the_tree, pre, 0);

        TS_ASSERT_EQUALS(pre.str(), "12\n  null\n  null\n");
        pre.clear();
        pre.str("");

        the_tree->insert(17);
        the_tree->insert(9);
        pre_order_traversal(*the_tree, pre, 0);

        TS_ASSERT_EQUALS(pre.str(), "12\n  9\n    null\n    null\n  17\n    null\n    null\n");
        pre.clear();
        pre.str("");
        the_tree->insert(14);
        the_tree->insert(10);
        the_tree->insert(13);
        pre_order_traversal(*the_tree, pre, 0);

        TS_ASSERT_EQUALS(pre.str(),
                         "12\n  9\n    null\n    10\n      null\n      null\n  14\n    13\n      null\n      null\n    17\n      null\n      null\n");
        pre.clear();
        pre.str("");
        the_tree->insert(20);
        the_tree->insert(18);
        pre_order_traversal(*the_tree, pre, 0);

        TS_ASSERT_EQUALS(pre.str(),
                         "12\n  9\n    null\n    10\n      null\n      null\n  14\n    13\n      null\n      null\n    18\n      17\n        null\n        null\n      20\n        null\n        null\n");

        the_tree->erase(12);
        the_tree->erase(17);
        the_tree->erase(9);
        the_tree->erase(14);
        the_tree->erase(10);
        the_tree->erase(13);
        the_tree->erase(20);
        the_tree->erase(18);
        delete the_tree;

    }

    void BalanceRight() {

        Binary_Search_Tree<int> *the_tree = NULL;
        the_tree = new AVL_Tree<int>;
        std::ostringstream pre;
        the_tree->insert(35);
        the_tree->insert(25);
        the_tree->insert(15);
        the_tree->insert(5);

        pre_order_traversal(*the_tree, pre, 0);
        TS_ASSERT_EQUALS(pre.str(), "25\n  15\n    5\n      null\n      null\n    null\n  35\n    null\n    null\n");

        the_tree->erase(35);
        the_tree->erase(25);
        the_tree->erase(15);
        the_tree->erase(5);
        delete the_tree;

    }

    void BalanceLeft() {

        Binary_Search_Tree<int> *thing = NULL;
        thing = new AVL_Tree<int>;
        std::ostringstream obj;
        thing->insert(7);
        thing->insert(14);
        thing->insert(21);
        thing->insert(28);

        pre_order_traversal(*thing, obj, 0);
        TS_ASSERT_EQUALS(obj.str(), "14\n  7\n    null\n    null\n  21\n    null\n    28\n      null\n      null\n");

        thing->erase(7);
        thing->erase(14);
        thing->erase(21);
        thing->erase(28);
        delete thing;


    }

    void test_Left_Right_Rotate__RightHeavy() {

        Binary_Search_Tree<int> *the_tree = NULL;
        the_tree = new AVL_Tree<int>;

        the_tree->insert(20);
        the_tree->insert(17);
        the_tree->insert(22);
        the_tree->insert(15);
        the_tree->insert(18);
        the_tree->insert(19);

        TS_ASSERT_EQUALS(the_tree->get_data(), 18);

        the_tree->erase(20);
        the_tree->erase(17);
        the_tree->erase(22);
        the_tree->erase(15);
        the_tree->erase(18);
        the_tree->erase(19);
        delete the_tree;
    }

    void test_Right_Left_Rotate__RightHeavy() {

        Binary_Search_Tree<int> *thing = NULL;
        thing = new AVL_Tree<int>;

        thing->insert(7);
        thing->insert(14);
        thing->insert(21);

        TS_ASSERT_EQUALS(thing->get_data(), 14);

        thing->erase(7);
        thing->erase(14);
        thing->erase(21);
        delete thing;
    }

    void test_Right_Left_Rotate__LeftHeavy() {

        Binary_Search_Tree<int> *thing1 = NULL;
        thing1 = new AVL_Tree<int>;

        thing1->insert(7);
        thing1->insert(14);

        TS_ASSERT_EQUALS(thing1->get_data(), 7);

        thing1->erase(7);
        thing1->erase(14);
        delete thing1;
    }


};

#endif //HW_6_NEWCXXTEST_H
