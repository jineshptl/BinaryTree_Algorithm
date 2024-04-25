// copyright 2022
//
// Created by jinesh patel on 6/24/22.
//

#ifndef HW_6_BINARY_SEARCH_TREE_H
#define HW_6_BINARY_SEARCH_TREE_H

#include "Binary_Tree.h"

/** Definition of the Binary Search Tree class.
    @param Item_Type The type of item to be stored in the tree
    Note: Item_Type must define the less-than operator as a
    total ordering.
*/
template<typename Item_Type>
class Binary_Search_Tree : public Binary_Tree<Item_Type> {
public:
    // Constructor
    /** Construct an empty Binary_Search_Tree */
    Binary_Search_Tree() : Binary_Tree<Item_Type>() {}

    // Public Member Functions
    /** Insert an item into the tree.
        post: The item is in the tree.
        @param item The item to be inserted
        @return true if the item was not already
                in the tree, false otherwise
    */
    virtual bool insert(const Item_Type &item);

    /** Remove an item from the tree.
        post: The item is no longer in the tree.
        @param item The item to be removed
        @return true if the item was in the tree,
                false otherwise
    */
    virtual bool erase(const Item_Type &item);

    /** Determine whether an item is in the tree.
        @param item The item sought
        @return A const pointer to the item if in the
                tree, or NULL if not
    */
    const Item_Type *find(const Item_Type &target) const;

private:

    // Private Member Functions
    /** Insert an item into the tree.
        post: The item is in the tree.
        @param local_root A reference to the current root
        @param item The item to be inserted
        @return true if the item was not already in the
                tree, false otherwise
    */
    virtual bool insert(BTNode<Item_Type> *&local_root,
                        const Item_Type &item);

    /** Remove an item from the tree.
        post: The item is no longer in the tree.
        @param local_root A reference to the current root
        @param item The item to be removed
        @return true if the item was in the tree,
                false otherwise
    */
    virtual bool erase(BTNode<Item_Type> *&local_root,
                       const Item_Type &item);

    /** Determine whether an item is in the tree.
        @param local_root A reference to the current root
        @param target The item sought
        @return A const pointer to the item in the tree
    */
    const Item_Type *find(BTNode<Item_Type> *local_root,
                          const Item_Type &target) const;

    /** Find a replacement for a node that is being deleted.
        This function finds the rightmost local root that
        does not have a right child. The data in this local_root
        replaces the data in old_root. The pointer to local_root
        is then saved in old_root and local_root is replaced
        by its left child.
        @param old_root Reference to the pointer to old parent
        @param local_root Reference to the pointer to local root
    */
    virtual void replace_parent(BTNode<Item_Type> *&old_root,
                                BTNode<Item_Type> *&local_root);

}; // End binary find tree

// Implementation of member functions
template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::insert(
        const Item_Type &item) {
    return insert(this->root, item);
}

template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::insert(
        BTNode<Item_Type> *&local_root,
        const Item_Type &item) {
    if (local_root == NULL) {
        local_root =
                new BTNode<Item_Type>(item);
        return true;
    } else {
        if (item < local_root->data) {
            return insert(local_root->left, item);
        } else if (local_root->data < item) {
            return insert(local_root->right, item);
        } else {
            return false;
        }
    }
}

template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::erase(
        const Item_Type &item) {
    return erase(this->root, item);
}

template<typename Item_Type>
bool Binary_Search_Tree<Item_Type>::erase(
        BTNode<Item_Type> *&local_root,
        const Item_Type &item) {
    if (local_root == NULL) {
        return false;
    } else {
        if (item < local_root->data) {
            return erase(local_root->left, item);
        } else if (local_root->data < item) {
            return erase(local_root->right, item);
        } else {
            BTNode<Item_Type> *old_root = local_root;
            if (local_root->left == NULL) {
                local_root = local_root->right;
            } else if (local_root->right == NULL) {
                local_root = local_root->left;
            } else {
                replace_parent(old_root, old_root->left);
            }
            delete old_root;
            return true;
        }
    }
}

template<typename Item_Type>
void
Binary_Search_Tree<Item_Type>::replace_parent(BTNode<Item_Type> *&old_root,
                                              BTNode<Item_Type> *&local_root) {
    if (local_root->right != NULL) {
        replace_parent(old_root, local_root->right);
    } else {
        old_root->data = local_root->data;
        old_root = local_root;
        local_root = local_root->left;
    }
}

template<typename Item_Type>
const Item_Type *Binary_Search_Tree<Item_Type>::find(
        const Item_Type &target) const {
    return find(this->root, target);
}

template<typename Item_Type>
const Item_Type *Binary_Search_Tree<Item_Type>::find(
        BTNode<Item_Type> *local_root,
        const Item_Type &target) const {
    if (local_root == NULL)
        return NULL;
    if (target < local_root->data)
        return find(local_root->left, target);
    else if (local_root->data < target)
        return find(local_root->right, target);
    else
        return &(local_root->data);
}


#endif //HW_6_BINARY_SEARCH_TREE_H
