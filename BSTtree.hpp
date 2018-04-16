#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <iostream>

#define RIGHT_BRANCH "┌─"
#define LEFT_BRANCH "└─"
#define VERTICAL_BRANCH "│ "

using namespace std;

typedef struct BST_node {
	int key;
	struct BST_node* left;
	struct BST_node* right;
	struct BST_node* parent;
	BST_node(int k, BST_node* p = NULL) { key = k; left = right = NULL; parent = p; }
} BST_node;

BST_node* createTreeBST(int* array, int n);
BST_node* findMaxBST(BST_node* root);
void removeNodesBST(BST_node* root, int* valueList, int n);
void printInOrderBST(BST_node* root);
void printPreOrderBST(BST_node* root);
void deletePostOrderBST(BST_node* root);
void printSubtreeBST(BST_node* root);
BST_node* searchBST(BST_node* root, int key);
void rotateLeftBST(BST_node* & root, BST_node* node);
void rotateRightBST(BST_node* & root, BST_node* node);
BST_node* balanceBST(BST_node* root);

void printBST(std::string sp, std::string sn, BST_node* v);