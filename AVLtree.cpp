#pragma once
#include "AVLtree.hpp"

AVL_node* createTreeAVL(int* array, int start, int end, AVL_node* up) {

	if (start > end)
		return NULL;

	int middle = (start + end + 1) / 2;
	AVL_node* root = new AVL_node(array[middle], up);

	root->left = createTreeAVL(array, middle + 1, end, root);
	root->right = createTreeAVL(array, start, middle - 1, root);

	return root;
}

AVL_node* findMaxAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return root;
	}

	while (root->right) {
		printf("--> %d ", root->key);
		root = root->right;
	}

	printf("--> %d\nMax element: %d\n", root->key, root->key);
	return root;
}


AVL_node* findMinAVL(AVL_node* root) {
	return root->left ? findMinAVL(root->left) : root;
}

AVL_node* deleteNodeAVL(AVL_node* root, int key) {
	if (root == NULL) return root;
	if (root->left == NULL && root->right == NULL) { //jeżeli wierzchołek jest liściem
		if (root->parent) {
			if (root->parent->right == root) {//usunięcie odwołania do wierzchołka w rodzicu
				root->parent->right = NULL;
			}
			else {
				root->parent->left = NULL;
			}
		}
		delete root;
		return NULL;
	}
	else if (root->left == NULL) {//jeżeli wierzchołek ma tylko prawego potomka
		AVL_node* temp = root->right;
		if (root->parent) {//zmiana odwołania w rodzicu wierzchołka
			if (root->parent->right == root) {
				root->parent->right = temp;
			}
			else {
				root->parent->left = temp;
			}
		}
		temp->parent = root->parent;
		delete root;
		return temp;
	}
	else if (root->right == NULL) {//jeżeli wierzchołek ma tylko lewego potomka
		AVL_node* temp = root->left;
		if (root->parent) {
			if (root->parent->right == root) {//zmiana odwołania w rodzicu wierzchołka
				root->parent->right = temp;
			}
			else {
				root->parent->left = temp;
			}
		}
		temp->parent = root->parent;
		delete root;
		return temp;
	}
	else {//jeżeli wierzchołek ma obu potomków

		AVL_node* temp = findMinAVL(root->right);
		root->key = temp->key;
		deleteNodeAVL(temp, temp->key);
		//root->right = deleteNodeAVL(root->right, temp->key); //nie wiem po co to //JB
	}
	return root;
}

void removeNodesAVL(AVL_node* root, int* valueList, int n) {
	for (int i = 0; i < n; i++) {
		AVL_node* beDeleted = searchAVL(root, valueList[i]);
		if (!beDeleted) {
			printf("\nNode with key %d didn\'t found.", valueList[i]);
		}
		else {
			deleteNodeAVL(beDeleted, beDeleted->key);
			printf("\nNode with key %d deleted.", valueList[i]);
		}
	}
}


void printInOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}
	if (root->left) printInOrderAVL(root->left);
	printf("%d ", root->key);
	if (root->right) printInOrderAVL(root->right);
}

void printPreOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}
	printf("%d ", root->key);
	if (root->left) printPreOrderAVL(root->left);
	if (root->right) printPreOrderAVL(root->right);
}

void deletePostOrderAVL(AVL_node* root) {
	if (!root) {
		puts("AVL-tree is empty.");
		return;
	}

	if (root->left) deletePostOrderAVL(root->left);
	if (root->right) deletePostOrderAVL(root->right);
	delete root;
}

void printSubtreeAVL(AVL_node* root) {
	int key;
	AVL_node* result;
	do {
		printf("\nType root key of subtree:");
		scanf_s("%d", &key);
	} while (!key);

	result = searchAVL(root, key);

	if (!result) {
		puts("No such element.");
	}
	else {
		printf("Printing subtree with root key %d:\n", result->key);
		printAVL("", "", result);
		//printInOrderAVL(result);
	}
}

AVL_node* searchAVL(AVL_node* root, int key) {
	if (!root || root->key == key) {
		return root;
	}

	if (root->key > key)
		return searchAVL(root->left, key);

	return searchAVL(root->right, key);
}

void printAVL(std::string sp, std::string sn, AVL_node* root) {
	std::string s;

	if (root) {
		s = sp;
		if (sn == RIGHT_BRANCH) s[s.length() - 2] = ' ';
		printAVL(s + VERTICAL_BRANCH, RIGHT_BRANCH, root->right);

		s = s.substr(0, sp.length() - 2);
		std::cerr << s << sn << root->key << std::endl;

		s = sp;
		if (sn == LEFT_BRANCH) s[s.length() - 2] = ' ';
		printAVL(s + VERTICAL_BRANCH, LEFT_BRANCH, root->left);
	}
}