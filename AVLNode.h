// copyright 2022
//
// Created by jinesh patel on 6/24/22.
//

#ifndef HW_6_AVLNODE_H
#define HW_6_AVLNODE_H

#include <sstream>

/** A node for an AVL Tree. */
template<typename Item_Type>
struct AVLNode : public BTNode<Item_Type> {

    enum  balance_type {left2 = -1, balanced = 0, right2 = +1};
    // Additional data field
    balance_type balance;

    // Constructor
    AVLNode(const Item_Type& the_data, BTNode<Item_Type>* left_val = NULL,
            BTNode<Item_Type>* right_val = NULL) :
            BTNode<Item_Type>(the_data, left_val, right_val), balance(balanced) {}

    // Destructor (to avoid warning message)
    virtual ~AVLNode() {}

    // to_string
    virtual std::string to_string() const {
        std::ostringstream os;
        os << balance << ": " << this->data;
        return os.str();
    }
}; // End AVLNode

#endif //HW_6_AVLNODE_H
