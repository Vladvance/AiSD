#pragma once

#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <iostream>

#define RIGHT_BRANCH "┌─"
#define LEFT_BRANCH "└─"
#define VERTICAL_BRANCH "│ "

using namespace std;

typedef struct AVL_node {
	int key;
	unsigned char height;
	struct AVL_node* left;
	struct AVL_node* right;
	struct AVL_node* parent;
	AVL_node(int k, AVL_node* up = NULL) { key = k; left = right = NULL; height = 1; parent = up; }
} AVL_node;

AVL_node* createTreeAVL(int* array, int start, int end, AVL_node* up = NULL);
AVL_node* findMaxAVL(AVL_node* root);
void removeNodesAVL(AVL_node* root, int* valueList, int n);
void printInOrderAVL(AVL_node* root);
void printPreOrderAVL(AVL_node* root);
void deletePostOrderAVL(AVL_node* root);
void printSubtreeAVL(AVL_node* root);
AVL_node* searchAVL(AVL_node* root, int key);


unsigned char height(AVL_node* p);
int bfactor(AVL_node* p);
void fixheight(AVL_node* p);
AVL_node* rotateright(AVL_node* p);
AVL_node* balance(AVL_node* p);

void printAVL(std::string sp, std::string sn, AVL_node* v);