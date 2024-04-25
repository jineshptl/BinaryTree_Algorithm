// copyright 2022
//
// Created by jinesh patel on 6/24/22.
//

#ifndef HW_6_BST_WITH_ROTATE_H
#define HW_6_BST_WITH_ROTATE_H

#include "Binary_Search_Tree.h"

/** This class extends the Binary_Search_Tree by adding the rotate
    operations. Rotate will change the balance of a find
    tree while preserving the find tree property.
    Used as a common base class for self-adjusting trees.
*/
template<typename Item_Type>
class BST_With_Rotate : public Binary_Search_Tree<Item_Type> {

protected:

    /** rotate_right
       @param local_root The root of the binary tree to be rotated
    */
    void rotate_right(BTNode<Item_Type> *&local_root) {
        BTNode<Item_Type> *temp = local_root->left;
        local_root->left = temp->right;
        temp->right = local_root;
        local_root = temp;
    }


    /** Insert rotate_left here
     @param local_root The root of the binary tree to be rotated
    */
    void rotate_left(BTNode<Item_Type> *&local_root) {
        BTNode<Item_Type> *temp = local_root->right;
        local_root->right = temp->left;
        temp->left = local_root;
        local_root = temp;
    }
};


#endif //HW_6_BST_WITH_ROTATE_H
