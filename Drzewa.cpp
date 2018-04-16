
#include "stdafx.h"
#include <ctime>
#include <chrono>

#include "AVLtree.hpp"
#include "BSTtree.hpp"

#define MAX_ARRAY_VALUE 100

using namespace std;
using tp = chrono::time_point<chrono::system_clock>; //do pomiaru czasu


int* RandDescending(int n);

int main(){
	srand(time(NULL));
	tp start, end;

	int *array;
	unsigned int numElements;
	
	int answer;
	bool isCorrectAnswer = false;

	int treeType;
	AVL_node* AVLtree = NULL;
	BST_node* BSTtree = NULL;
	
	int* nodesToDelete;
	int numNodesToDelete = 0;
	
	while(true){ //ilość danych
		puts("Enter number of data: ");
		if(!scanf_s("%u", &numElements) || numElements < 1)
			puts("Incorrect answer. Try again.");
		else break;
	}

	array = RandDescending(numElements); //wygenerowanie ciągu(można dodać wczytywanie z klawiatury i sortowanie)
	
	while(true){ //pętla główna programu
		
		isCorrectAnswer = false;

		while(!isCorrectAnswer){ //wybór drzewa
			puts("Choose tree to build:");
			puts("   '1' - AVL-tree;");
			puts("   '2' - BST-tree;");
			
			scanf_s("%d", &treeType);
			
			switch(treeType){
				case 1:// Drzewo AVL

					start = chrono::system_clock::now();
					AVLtree = createTreeAVL(array, 0, numElements - 1);
					end = chrono::system_clock::now();
					
					cout <<"Time in microseconds(creating AVL): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
					//printAVL("", "", AVLtree);
					puts("AVL-tree builded succesfully.");
					
					isCorrectAnswer = true;
					break;

				case 2:// Drzewo BST
					
					start = chrono::system_clock::now();
					BSTtree = createTreeBST(array, numElements);
					end = chrono::system_clock::now();
					
					cout << "Time in microseconds(creating BST): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
					//printBST("", "", BSTtree);
					puts("BST-tree builded succesfully.");
					
					isCorrectAnswer = true;
					break;

				default:
					puts("Incorrect answer. Try again.");
					break;
			}
		}

		isCorrectAnswer = false;

		while(!isCorrectAnswer){
			puts("\nWhat do you want to do with a tree:");
			puts("  1  Find way to max value;");
			puts("  2  Delete few elements;");
			puts("  3  Print tree in-order;");
			puts("  4  Print tree pre-order;");
			puts("  5  Delete tree post-order;");
			puts("  6  Print subtree from given key;");
			puts("  7  Balance tree using rotation;");
			puts("  8  Change tree type;");
			puts("  9  Exit;");

			puts("Give your answer:");
			scanf_s("%d", &answer);
			
			if(treeType == 1){// Drzewa AVL
				switch(answer){
					case 1:
						start = chrono::system_clock::now();
						findMaxAVL(AVLtree);
						end = chrono::system_clock::now();
						
						cout << endl << "Time in microseconds(Max Value AVL): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					
					case 2:
						while(true){//ilość danych do usunięcia
							puts("Enter number of data to delete: ");

							if(!scanf_s("%d", &numNodesToDelete) || numNodesToDelete < 1)
								puts("Incorrect number of nodes. Try again.");
							else break;
						}
						
						nodesToDelete = (int*)malloc(numNodesToDelete * sizeof(int));
						
						for(int i = 0; i < numNodesToDelete; i++){
							while(true){//klucze węzłów do usunięcia(bez sprawdzania czy istnieje węzeł o podanym kluczu)
								puts("Enter key of node to delete: ");
								
								if(!scanf_s("%d", &nodesToDelete[i]))
									puts("Incorrect key value. Try again.");
								else break;
							}
						}

						removeNodesAVL(AVLtree, nodesToDelete, numNodesToDelete);
						break;
					case 3:
						puts("In-order:");

						start = chrono::system_clock::now();
						printInOrderAVL(AVLtree);
						end = chrono::system_clock::now();
						
						cout << endl << "Time in microseconds(in-order AVL): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 4:
						puts("Pre-order:");
						printPreOrderAVL(AVLtree);
						break;
					case 5:
						puts("Deleting AVL-tree in post-order...");
						deletePostOrderAVL(AVLtree);
						puts("AVL-tree deleted.");
						
						isCorrectAnswer = true;
						break;
					case 6:
						puts("Print subtree:");
						printSubtreeAVL(AVLtree);
						break;
					case 7:
						puts("Balancing AVL-tree...");
						balance(AVLtree);	
						puts("AVL-tree balanced.");
						break;
					case 8:
						isCorrectAnswer = true;
						break;
					case 9:
						puts("Exited");
						return 0;
					default:
						puts("Incorrect answer. Try again.");
						break;
				}
			} else {
				switch(answer){
					case 1:
						puts("Finding max element...");

						start = chrono::system_clock::now();
						findMaxBST(BSTtree);
						end = chrono::system_clock::now();

						cout << endl << "Time in microseconds(Max Value BST): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 2:
						while(true){//ilość danych do usunięcia
							puts("Enter number of data to delete: ");
							if(!scanf_s("%d", &numNodesToDelete) || numNodesToDelete < 1)
								puts("Incorrect number of nodes. Try again.");
							else break;
						}

						nodesToDelete = (int*)malloc(numNodesToDelete * sizeof(int));
						
						for(int i = 0; i < numNodesToDelete; i++){
							while(true){//klucze węzłów do usunięcia(bez sprawdzania czy istnieje węzeł o podanym kluczu)
								puts("Enter key of node to delete: ");
								if(!scanf_s("%d", &nodesToDelete[i]))
									puts("Incorrect key value. Try again.");
								else break;
							}
						}

						removeNodesBST(BSTtree, nodesToDelete, numNodesToDelete);
						break;
					case 3:
						puts("In-order:");

						start = chrono::system_clock::now();
						printInOrderBST(BSTtree);
						end = chrono::system_clock::now();
						
						cout << endl << "Timein microseconds(in-order BST): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 4:
						puts("Pre-order:");
						printPreOrderBST(BSTtree);
						break;
					case 5:
						puts("Deleting BST-tree in post-order...");
						deletePostOrderBST(BSTtree);
						puts("BST-tree deleted.");
						
						isCorrectAnswer = true;
						break;
					case 6:
						puts("Print subtree:");
						printSubtreeBST(BSTtree);
						break;
					case 7:
						puts("Balancing BST-tree...");
						
						start = chrono::system_clock::now();
						BSTtree = balanceBST(BSTtree);
						end = chrono::system_clock::now();
						
						puts("BST-tree balanced.");
						printBST("", "", BSTtree);
						cout << endl << "Time in microseconds(balancing BST): " << chrono::duration_cast<chrono::microseconds>(end - start).count() << endl;
						break;
					case 8:
						isCorrectAnswer = true;
						break;
					case 9:
						puts("Exited");
						return 0;
					default:
						puts("Incorrect answer. Try again.");
						break;
				}
				puts("");
			}
		}

	}
	system("pause");
	return 0;
}

unsigned char height(AVL_node* p){
	return p ? p->height : 0;
}

int bfactor(AVL_node* p){
	return height(p->right) - height(p->left);
}

void fixheight(AVL_node* p){
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
}

AVL_node* rotateright(AVL_node* p){
	AVL_node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

AVL_node* rotateleft(AVL_node* q){
	AVL_node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

AVL_node* balance(AVL_node* p) // балансировка узла p
{
	fixheight(p);
	if(bfactor(p) == 2){
		if(bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if(bfactor(p) == -2){
		if(bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

int* RandDescending(int numElement){
	int* array = (int*)malloc(numElement * sizeof(int));
	int gap = MAX_ARRAY_VALUE / numElement;
	for(int x = 0; x < numElement; x++)
		array[x] = (rand() % gap) + (MAX_ARRAY_VALUE - (x + 1) * gap);
	return array;
}
