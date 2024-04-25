// copyright 2022
//
// Created by jinesh patel on 6/24/22.
//

#ifndef HW_6_B_TREE_H
#define HW_6_B_TREE_H

#include <sstream>
#include <string>
#include <algorithm>

/** An implementation of the B-tree. A B-tree is a find tree
 *  in which each node other than the root contains
 *  CAP/2-1 .. CAP-1 items and CAP/2 .. CAP children.  The tree
 *  is always balanced in that all leaves are on the same level,
 *  i.e., the length of the path from the root to a leaf is
 *  constant.
 */
template<typename Item_Type, size_t CAP>
class B_Tree {

    // Inner Class
    /** A Node represents a node in a B-tree. CAP represents
        the maxumum number of children. This class has no functions;
        it is merely a container of private data.
    */
    struct Node {

        /** The number of data items in this node */
        size_t size;

        /** The information */
        Item_Type data[CAP - 1];

        /** The links to the children. child[i] refers to
        the subtree of children < data[i] for i < size
        and to the subtree of children > data[size - 1]
        for i == size. */
        Node *child[CAP];

        Node() {
            for (size_t i = 0; i < CAP; i++) {
                if (i < CAP - 1)
                    data[i] = Item_Type();
                child[i] = NULL;
            }
        }
    };

    // Data Fields
    /** The reference to the root. */
    Node *root;
public:
    /** Create an empty B_Tree */
    B_Tree() : root(NULL) {}

    /** Insert an object into the tree.
        @param obj The object to be inserted
        @return true if the item was inserted
     */
    bool insert(const Item_Type &item) {
        if (root == NULL) {
            root = new Node;
            root->data[0] = item;
            root->size = 1;
            return true;
        }
        Item_Type new_parent;
        Node *new_child = NULL;
        bool result = insert(root, item, new_parent, new_child);
        if (new_child != NULL) {
            Node *new_root = new Node;
            new_root->child[0] = root;
            new_root->child[1] = new_child;
            new_root->data[0] = new_parent;
            new_root->size = 1;
            root = new_root;
        }
        return result;
    }

/** Recursive function to insert an object into the tree.
    @param local_root The local root
    @param item The item to be inserted
    @param new_parent The parent of the split node
    @param new_child Pointer to the subtree containing items
           greater than the new_parent
    @return true if the item was inserted,
    false if the item is already in the tree
*/
    bool insert(Node *local_root, const Item_Type &item,
                Item_Type &new_parent, Node *&new_child) {
        const Item_Type *pointer = binary_search(local_root->data,
                                                 local_root->data + local_root->size,
                                                 item);
        size_t index = pointer - local_root->data;
        // index == local_root->size or item <= local_root.data[index]

        if (index != local_root->size
            && !(item < local_root->data[index])) {
            // Item is already in the tree.
            return false;
        }
        // See if local_root is a leaf
        if (local_root->child[index] == NULL) {
            if (local_root->size < CAP - 1) {
                insert_into_node(local_root, index, item, NULL);
                new_child = NULL;
            } else {
                split_node(local_root, index, item, NULL, new_parent, new_child);
            }
            return true;
        } else {
            bool result = insert(local_root->child[index],
                                 item, new_parent, new_child);
            if (new_child != NULL) {
                if (local_root->size < CAP - 1) {
                    insert_into_node(local_root, index, new_parent, new_child);
                    new_child = NULL;
                } else {
                    split_node(local_root, index, new_parent, new_child,
                               new_parent, new_child);
                }
            }
            return result;
        }
    }

    /** Function to insert a new value into a node.
        Pre: node->data[index - 1] < item < node->data[index]
        and node->size < CAP-1
        Post: node->data[index] = item and old values are moved
        right one
        @param node The node to insert the value into
        @param index The index where the inserted item
        is to be placed
        @param item The value to be inserted
        @param child The right child of the value
    */
    void insert_into_node(Node *node, size_t index,
                          const Item_Type &item, Node *child) {
        // Move items greater than inserted item up one index
        for (size_t i = node->size; i > index; i--) {
            node->data[i] = node->data[i - 1];
            node->child[i + 1] = node->child[i];
        }
        // Insert the new item and its right child
        node->data[index] = item;
        node->child[index + 1] = child;
        node->size++;
    }

    /** Function to virtually insert a new item into a full
        node and split the result into two nodes.
        pre:  node->data[index - 1] < item < node->data[index]
        and node->size = CAP-1.
        post: Node is split and the item is inserted in the left, right,
        or center. The center item becomes the parent of the right half.
        @param node The node to insert the value into
        @param index The index where the inserted item is to be placed
        @param item The value to be inserted
        @param child The right child of the value to be inserted
        @param new_parent The item that is the parent of the split-
        off child
        @param new_child The split-off child
    */
    void split_node(Node *node, size_t index,
                    const Item_Type &item, Node *child,
                    Item_Type &new_parent, Node *&new_child) {
        // Create new child
        new_child = new Node;
        // Determine number of items to move
        size_t num_to_move = (CAP - 1) - (CAP - 1) / 2;
        // If insert is to the right half, move one less item
        if (index > (CAP - 1) / 2)
            num_to_move--;

        // Move items
        std::copy(node->data + (CAP - 1) - num_to_move,
                  node->data + (CAP - 1), new_child->data);
        std::copy(node->child + CAP - num_to_move, node->child + CAP,
                  new_child->child + 1);
        node->size = (CAP - 1) - num_to_move;
        new_child->size = num_to_move;

        // Insert new item
        if (index == (CAP - 1) / 2) { // Insert into the middle
            new_parent = item;
            new_child->child[0] = child;
        } else {
            if (index < (CAP - 1) / 2) { // Insert into the left
                insert_into_node(node, index, item, child);
            } else { // Insert into right
                insert_into_node(new_child, index - (CAP - 1) / 2 - 1, item, child);
            }
            // The rightmost item of the node becomes the new parent
            new_parent = node->data[node->size - 1];
            // Its child is now the left child of the split-off node
            new_child->child[0] = node->child[node->size];
            node->size--;
        }
    }

    /** Determine if an item is in the tree
        @param target Item being sought in tree
        @return true If the item is in the tree, false otherwise
    */
    bool contains(const Item_Type &target) {
        return find(target) != NULL;
    }

    /** Find an object in the tree
        @param item The object sought, must be Comparable
        @return The object in the tree, or NULL
        if the object is not in the tree
    */
    const Item_Type *find(const Item_Type &item) {
    }

    /** Recursive find function. Find the object
        in the node or one of its children
        @param local_root The node to find
        @param item The object sought, must be Comparable
        @return The object in the tree, or NULL
        if the object is not in the tree
    */
    const Item_Type *find(Node *local_root, const Item_Type &item) {
    }

    /** Function to find the data array for an item
        Pre:  Data array is sorted
        @param first A pointer to the beginning of the find array
        @param last A pointer to one-past the end of the find array
        @return A pointer to the item if it in the array, otherwise
        a pointer to the position in the array where the item should be
    */
    const Item_Type *binary_search(Item_Type *first, Item_Type *last,
                                   const Item_Type &item) const {
    }

    bool erase(const Item_Type &item) {
    }

    /** Return a pre-order traversal as the string
        representation of the tree
        @return a string representation of the tree
    */
    std::string to_string() {
        std::ostringstream sb;
        pre_order_traverse(root, 0, sb);
        return sb.str();
    }

    /** Perform a pre-order traversal
        @param node - The local root
        @param d - The depth
        @param sb - The string buffer to put the output
    */
    void pre_order_traverse(Node *node, int d, std::ostream &sb) {
        for (int i = 0; i < d; i++) {
            sb << "  ";
        }
        if (node == NULL) {
            sb << "NULL";
        } else {
            for (size_t i = 0; i < node->size; i++) {
                sb << node->data[i];
                if (i != node->size - 1) {
                    sb << ", ";
                }
            }
            sb << "\n";
            for (size_t i = 0; i < node->size; i++) {
                pre_order_traverse(node->child[i], d + 1, sb);
                sb << '\n';
            }
            pre_order_traverse(node->child[node->size], d + 1, sb);
            sb << "\n\n";
        }
    }
};

#endif //HW_6_B_TREE_H
