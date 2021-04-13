/*
File name: CSE_2122_HW05.cpp
Created by: Surya Kodali
Created on: 3/23/20
Synopsis: This program utilizes binary trees and allows the use of functions
that can determine the size of a tree, occurences of a target value, height of 
a tree, check if two trees are the same, if a path exists where its sum is the
target value, and if a tree is balanced. The trees contain right and left
child nodes and data of non-negative integers.
*/

#include <iostream>
#include <cstddef>
#include <cassert>

using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
};

// Function declarations
int size(TreeNode *root);
int count(TreeNode *root, int target);
int height(TreeNode *root);
bool isSameTree(TreeNode *root1, TreeNode *root2);
bool hasPathSum(TreeNode *root, int target);
bool isBalanced(TreeNode *root);

// A helper function to build a tree, you do not need to modify it
// Inputs:
//     nodeValues, a list of all node values from top to bottom, left to right. If no node at one place, use -1 as the placeholder
//     root, a pointer to the root node
//     i, set it to 0 when calling this function from outside
//     n, size of the 'nodeValues' array
// Postcondition: a tree is built with the second input argument as its root pointer
TreeNode *insertNodes(int nodeValues[], TreeNode *root, int i, int n);

// A helper function to free all nodes in a binary tree, you do not need to modify it
// Inputs:
//     root, the root node of a binary tree
// Postcondition: all nodes in this tree are freed
void freeNodes(TreeNode *root);

int main()
{
    // the binary trees in instruction examples
    TreeNode *root, *root2;
    int nodedatas[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, -1, -1, -1, -1, -1, 1};
    int nodedatas2[] = {1, 2, 3, 4, 5, -1, 7, 8, 1, -1, -1, -1, -1, 1, -1};
    root = NULL;
    root2 = NULL;
    root = insertNodes(nodedatas, root, 0, 15);
    root2 = insertNodes(nodedatas2, root2, 0, 15);

    assert(size(root) == 10);
    assert(size(root->left) == 5);
    assert(count(root, 1) == 3);
    assert(count(root, 9) == 0);
    assert(height(root) == 3);
    assert(height(root->left->right) == 0);
    assert(hasPathSum(root, 10) == true);
    assert(hasPathSum(root, 1) == false);
    assert(isBalanced(root) == true);
    assert(isSameTree(root, root2) == false);
    assert(isSameTree(root->left, root2->left) == true);
    assert(isBalanced(root2) == true);

    cout << "Congratulation!" << endl;

    freeNodes(root);
    freeNodes(root2);
    return 0;
}

// A helper function to build the test cases. You do not need to modify it.
TreeNode *insertNodes(int nodeValues[], TreeNode *root, int i, int n)
{
    if (i < n && nodeValues[i] != -1)
    {
        root = new TreeNode;
        root->data = nodeValues[i];
        root->left = insertNodes(nodeValues, root->left, 2 * i + 1, n);
        root->right = insertNodes(nodeValues, root->right, 2 * i + 2, n);
    }
    else
    {
        root = NULL;
    }
    return root;
}

void freeNodes(TreeNode *root)
{
    if (root != NULL)
    {
        freeNodes(root->left);
        freeNodes(root->right);
        delete root;
    }
}

// Count the number of nodes in the tree
int size(TreeNode *root)
{
    // count root node
    int count = 1;
    // count nodes in right and left branches
    if (root->left != NULL)
        count += size(root->left);
    if (root->right != NULL)
        count += size(root->right);
    return count;
}

// Count number of times target appears in the tree
int count(TreeNode *root, int target)
{
    int num = 0;
    // node is null so target is not there
    if (root == NULL)
        return 0;
    // target is in the current node
    if (target == root->data)
        num += 1;
    // target is in the left child node
    if (root->left != NULL)
        num += count(root->left, target);
    // target is in the right child node
    if (root->right != NULL)
        ;
    num += count(root->right, target);
    return num;
}

// Returns the max height of the tree/ path with most nodes
int height(TreeNode *root)
{
    // return -1 if tree is empty
    if (root == NULL)
        return -1;
    else
    {
        // find height of left and right branches
        int hleft = height(root->left);
        int hright = height(root->right);
        // return tallest tree plus the root node
        return (hright > hleft ? hright + 1 : hleft + 1);
    }
}

// Checks if trees are identical
bool isSameTree(TreeNode *root1, TreeNode *root2)
{
    // check if the nodes are both null
    if (root1 == NULL && root2 == NULL)
        return true;
    // check if the data in the nodes are the same and the nodes
    // they point to (left and right) are the same
    if (root1 != NULL && root2 != NULL)
    {
        return (
            root1->data == root2->data &&
            isSameTree(root1->right, root2->right) &&
            isSameTree(root1->left, root2->left));
    }
    // if only one root is null
    return false;
}

// Checks if a summed path equal to the target exists
bool hasPathSum(TreeNode *root, int target)
{
    // if there is no value in root
    if (root == NULL)
        return false;
    // if the root has the target
    if (root->data == target && root->right == NULL && root->left == NULL)
        return true;
    // if sum of any path is equal to target
    // subtract current node from target until leaf equals remainder
    return (
        hasPathSum(root->right, target - root->data) ||
        hasPathSum(root->left, target - root->data));
}

// Checks if there is no difference greater than 1 for subtree heights
bool isBalanced(TreeNode *root)
{
    // empty node is balanced
    if (root == NULL)
        return true;
    int num = 0;
    // add height of right tree
    num += height(root->right) == -1 ? 0 : height(root->right);
    // subtract height of left tree to get difference
    num -= height(root->left) == -1 ? 0 : height(root->left);
    // check if each subtree is balanced and that the difference in heights is <= 1
    return (num <= 1 && num >= -1 &&
            isBalanced(root->right) &&
            isBalanced(root->left));
}