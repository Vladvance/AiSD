
#include "BSTtree.hpp"

BST_node* createTreeBST(int* array, int n) {
	BST_node* node = new BST_node(array[0]);
	BST_node* root = node;

	for (int i = 1; i < n; i++) {
		while (node) {
			if (array[i] < node->key) {
				if (node->left)	node = node->left;
				else {
					node->left = new BST_node(array[i], node);
					break;
				}
			}
			else {
				if (node->right) node = node->right;
				else {
					node->right = new BST_node(array[i], node);
					break;
				}
			}
		}
		//node = root;  // dla ciągów posortowanych nie trzeba wracać do korzenia
	}
	return root;
}

BST_node* findMaxBST(BST_node* root) {
	if (!root) {
		puts("BST-tree is empty.");
		return root;
	}

	while (root->right) {
		printf("--> %d ", root->key);
		root = root->right;
	}

	printf("--> %d\nMax element: %d\n", root->key, root->key);
	return root;
}

BST_node* findMinBST(BST_node* root) {
	return root->left ? findMinBST(root->left) : root;
}

BST_node* deleteNodeBST(BST_node* root, int key) {
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
		BST_node* temp = root->right;
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
		BST_node* temp = root->left;
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

		BST_node* temp = findMinBST(root->right);
		root->key = temp->key;
		deleteNodeBST(temp, temp->key);
	}
	return root;
}

void removeNodesBST(BST_node* root, int* valueList, int n) {
	for (int i = 0; i < n; i++) {
		BST_node* beDeleted = searchBST(root, valueList[i]);
		
		if (!beDeleted) {
			printf("\nNode with key %d didn\'t found.", valueList[i]);
		}
		else {
			deleteNodeBST(beDeleted, beDeleted->key);
			printf("\nNode with key %d deleted.", valueList[i]);
		}
	}
}

void printInOrderBST(BST_node* root) {
	if (!root) {
		puts("BST-tree is empty.");
		return;
	}

	if (root->left) printInOrderBST(root->left);
	printf("%d ", root->key);
	if (root->right) printInOrderBST(root->right);
}

void printPreOrderBST(BST_node* root) {
	if (!root) {
		puts("BST-tree is empty.");
		return;
	}

	printf("%d ", root->key);
	if (root->left) printPreOrderBST(root->left);
	if (root->right) printPreOrderBST(root->right);
}

void deletePostOrderBST(BST_node* root) {
	if (!root) {
		puts("BST-tree is empty.");
		return;
	}

	if (root->left) deletePostOrderBST(root->left);
	if (root->right) deletePostOrderBST(root->right);
	delete root;
}

void printSubtreeBST(BST_node* root) {
	int key;
	BST_node* result;

	puts("Type root key of subtree:");
	scanf_s("%d", &key);

	result = searchBST(root, key);

	if (!result) {
		puts("No such element.");
	}
	else {
		printBST("", "", result);
	}
}

BST_node* searchBST(BST_node* root, int key) {
	if (!root || root->key == key) {
		return root;
	}

	if (root->key > key)
		return searchBST(root->left, key);

	return searchBST(root->right, key);
}


void rotateRightBST(BST_node* & root, BST_node* node) {
	BST_node* q = node->left;
	node->left = q->right;
	if (node->left) node->left->parent = node;
	q->right = node;
	q->parent = node->parent;
	node->parent = q;
	if (q->parent) {
		if (q->parent->left == node)
			q->parent->left = q;
		else q->parent->right = q;
	}
	else root = q;
}

void rotateLeftBST(BST_node* & root, BST_node* node) {
	BST_node* p = node->right;
	if (p) {
		node->right = p->left;
		if (node->right) node->right->parent = node;
		p->left = node;
		p->parent = node->parent;
		node->parent = p;
		if (p->parent) {
			if (p->parent->left == node)
				p->parent->left = p;
			else	p->parent->right = p;
		}
		else root = p;
	}
}

unsigned log2(unsigned x) {
	unsigned y = 1;

	while ((x >>= 1) > 0)
		y <<= 1;

	return y;
}

BST_node* balanceBST(BST_node* root) {
	unsigned s, n = 0;
	BST_node* node = root;
	//obroty w lewo
	while (node) {
		if (node->left) {
			rotateRightBST(root, node);
			node = node->parent;
		}
		else {
			if (node->right)	node = node->right;
			else break;
			n++;
		}
	}
	//obroty w prawo
	s = n + 1 - log2(n + 1); // liczba liści na najniższym poziomie - 1

	cout << s << endl;
	
	node = root;
	for (unsigned int i = 0; i < s; i++) {
		rotateLeftBST(root, node);
		node = node->parent->right;
	}
	n = n - s;
	
	node = root;
	while (n > 1) {
		n >>= 1;
		for (unsigned int i = 0; i < n; i++) {
			rotateLeftBST(root, node);
			node = node->parent->right;
		}
		node = root;
		//	printBST("", "", root);
	}
	return root;
}

void printBST(std::string sp, std::string sn, BST_node* root) {
	std::string s;

	if (root) {
		s = sp;
		if (sn == RIGHT_BRANCH) s[s.length() - 2] = ' ';
		printBST(s + VERTICAL_BRANCH, RIGHT_BRANCH, root->right);

		s = s.substr(0, sp.length() - 2);
		std::cerr << s << sn << root->key << std::endl;

		s = sp;
		if (sn == LEFT_BRANCH) s[s.length() - 2] = ' ';
		printBST(s + VERTICAL_BRANCH, LEFT_BRANCH, root->left);
	}
}