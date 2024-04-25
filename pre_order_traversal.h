// copyright 2022
//
// Created by jinesh patel on 6/25/22.
//

#ifndef HW_6_PRE_ORDER_TRAVERSAL_H
#define HW_6_PRE_ORDER_TRAVERSAL_H

#include "Binary_Tree.h"
#include <ostream>

template<typename Item_Type>
void pre_order_traversal(const Binary_Tree<Item_Type>& the_tree,
                         std::ostream& out, int level) { //prints pre-order of the tree when called
    if (the_tree.is_null()) { //is root is null
        for (int i = 0; i < level; i++)
            out << "  ";
        out << "null\n"; //prints "null" and end of line
    } else {
        for (int i = 0; i < level; i++)//looping through until the level provided
            out << "  ";
        out << the_tree.get_data() << std::endl; //prints the data
        pre_order_traversal(the_tree.get_left_subtree(), out, level + 1); //recursion for getting left data
        pre_order_traversal(the_tree.get_right_subtree(), out, level + 1); //recursion for getting right data
    }
}

#endif //HW_6_PRE_ORDER_TRAVERSAL_H
