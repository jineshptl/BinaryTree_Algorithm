// copyright 2022
//
// Created by jinesh patel on 6/24/22.
//

#ifndef HW_6_AVL_TREE_H
#define HW_6_AVL_TREE_H

#include "BST_With_Rotate.h"
#include "AVLNode.h"

/** Definition of the AVL Binary Search Tree class.
    @param Item_Type The type of item to be stored in the tree
    Note: Item_Type must define the less-than operator as a
    total ordering.
*/
template<typename Item_Type>
class AVL_Tree : public BST_With_Rotate<Item_Type> {

public:
    // Constructor
    /** Construct an empty AVL_Tree */
    AVL_Tree() : BST_With_Rotate<Item_Type>() {

    }

    // Public Member Functions
    /** Insert an item into the tree by calling overridden insert function.
        post: The item is in the tree.
        @param item The item to be inserted
        @return true only if the item was not already in the tree
    */
    virtual bool insert(const Item_Type &item) {
        return insert(this->root, item);
    }


private:

    // Private member functions declarations
    /** Insert an item into the tree. Called by starter function (see
        listing 11.2) with this->root as first argument.
        post: The item is in the tree.
        @param local_root A reference to the current root
        @param item The item to be inserted
        @return true only if the item was not already in the
    */
    virtual bool insert(BTNode<Item_Type> *&, const Item_Type &);

    /** Correct a critical left balance condition
        pre:  Root is the root of an AVL subtree that is
        critically heavy.
        post: balance is restored
        @param Root is the root of the AVL subtree
        that needs rebalancing
    */
    void rebalance_left(BTNode<Item_Type> *&Root);

    /** Correct a critical right balance condition
        pre:  Root is the root of an AVL subtree that is
        critically heavy.
        post: balance is restored
        @param Root is the root of the AVL subtree
        that needs rebalancing
    */
    void rebalance_right(BTNode<Item_Type> *&Root);


    // Data Fields
    /** A flag to indicate that the height of the tree has increased */
    bool increase;


}; // End of AVL_Tree class definition

// Implementation of member functions

template<typename Item_Type>
bool
AVL_Tree<Item_Type>::insert(BTNode<Item_Type> *&root, const Item_Type &object) {
    if (root == NULL) {
        root = new AVLNode<Item_Type>(object);
        increase = true;
        return true;
    } else {
        if (object < root->data) {
            bool return_value = insert(root->left, object);
            if (increase) {
                AVLNode<Item_Type> *AVL_local_root = dynamic_cast<AVLNode<Item_Type> *> (root);
                switch (AVL_local_root->balance) {
                    case AVLNode<Item_Type>::balanced:
                        AVL_local_root->balance = AVLNode<Item_Type>::left2;
                        break;
                    case AVLNode<Item_Type>::right2:
                        AVL_local_root->balance = AVLNode<Item_Type>::balanced;
                        increase = false;
                        break;
                    case AVLNode<Item_Type>::left2:
                        rebalance_left(root);
                        increase = false;
                        break;
                }
            }
            return return_value;
        } else if (root->data < object) {
            bool return_value = insert(root->right, object);
            if (increase) {
                AVLNode<Item_Type> *AVL_local_root = dynamic_cast<AVLNode<Item_Type> *> (root);
                switch (AVL_local_root->balance) {
                    case AVLNode<Item_Type>::balanced:
                        AVL_local_root->balance = AVLNode<Item_Type>::right2;
                        break;
                    case AVLNode<Item_Type>::left2:
                        AVL_local_root->balance = AVLNode<Item_Type>::balanced;
                        increase = false;
                        break;
                    case AVLNode<Item_Type>::right2:
                        rebalance_right(root);
                        increase = false;
                        break;
                }
            }
            return return_value;
        } else {
            increase = false;
            return false;
        }
    }
}

template<typename Item_Type>
void AVL_Tree<Item_Type>::rebalance_left(BTNode<Item_Type> *&Root) {

    AVLNode<Item_Type> *root = dynamic_cast<AVLNode<Item_Type> *> (Root);
    AVLNode<Item_Type> *left = dynamic_cast<AVLNode<Item_Type> *> (Root->left);

    if (left->balance == AVLNode<Item_Type>::right2) {
        AVLNode<Item_Type> *left_right_child = dynamic_cast<AVLNode<Item_Type> *> (left->right);
        if (left_right_child->balance == AVLNode<Item_Type>::left2) {
            left->balance = AVLNode<Item_Type>::balanced;
            left_right_child->balance = AVLNode<Item_Type>::balanced;
            root->balance = AVLNode<Item_Type>::right2;
        } else if (left_right_child->balance
                   == AVLNode<Item_Type>::balanced) {
            left->balance = AVLNode<Item_Type>::balanced;
            left_right_child->balance = AVLNode<Item_Type>::balanced;
            root->balance = AVLNode<Item_Type>::balanced;
        } else {
            left->balance = AVLNode<Item_Type>::left2;
            left_right_child->balance = AVLNode<Item_Type>::balanced;
            root->balance = AVLNode<Item_Type>::balanced;
        }
        this->rotate_left(Root->left);
    } else {
        left->balance = AVLNode<Item_Type>::balanced;
        root->balance = AVLNode<Item_Type>::balanced;
    }
    this->rotate_right(Root);
}

template<typename Item_Type>
void AVL_Tree<Item_Type>::rebalance_right(BTNode<Item_Type> *&Root) {

    AVLNode<Item_Type> *root = dynamic_cast<AVLNode<Item_Type> *> (Root);
    AVLNode<Item_Type> *right = dynamic_cast<AVLNode<Item_Type> *> (Root->right);

    if (right->balance == AVLNode<Item_Type>::left2) {
        AVLNode<Item_Type> *right_left_child = dynamic_cast<AVLNode<Item_Type> *> (right->left);
        if (right_left_child->balance == AVLNode<Item_Type>::right2) {
            right->balance = AVLNode<Item_Type>::balanced;
            right_left_child->balance = AVLNode<Item_Type>::balanced;
            root->balance = AVLNode<Item_Type>::left2;
        } else if (right_left_child->balance == AVLNode<Item_Type>::balanced) {
            right->balance = AVLNode<Item_Type>::balanced;
            right_left_child->balance = AVLNode<Item_Type>::balanced;
            root->balance = AVLNode<Item_Type>::balanced;
        } else {
            right->balance = AVLNode<Item_Type>::right2;
            right_left_child->balance = AVLNode<Item_Type>::balanced;
            root->balance = AVLNode<Item_Type>::balanced;
        }
        this->rotate_right(Root->right);
    } else {
        right->balance = AVLNode<Item_Type>::balanced;
        root->balance = AVLNode<Item_Type>::balanced;
    }
    this->rotate_left(Root);
}


#endif //HW_6_AVL_TREE_H
