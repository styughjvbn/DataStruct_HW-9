/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

int initializeBST(Node** h);//초기화 함수

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	char command;
	int key;
	int initial = 0;//초기화가 진행됐는지 확인한다.
	Node* head = NULL;//해드노드
	Node* ptr = NULL;//임시 노드

	printf("[----- [서종원] [2018038031] -----]\n");

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			initial++;//초기화가 진행된다면 +1을 해준다.
			break;
		case 'q': case 'Q':
			if (initial)
				freeBST(head);
			break;
		case 'n': case 'N':
			if (initial) {
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				insert(head, key);
			}
			else
				printf("초기화를 먼저 진행해주세요 \n");
			break;
		case 'd': case 'D':
			if (initial) {
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				deleteLeafNode(head, key);
			}
			else
				printf("초기화를 먼저 진행해주세요\n");
			break;
		case 'f': case 'F':
			if (initial) {
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				ptr = searchIterative(head, key);
				if (ptr != NULL)
					printf("\n node [%d] found at %p\n", ptr->key, ptr);
				else
					printf("\n Cannot find the node [%d]\n", key);
			}
			else
				printf("초기화를 먼저 진행해주세요\n");
			break;
		case 's': case 'S':
			if (initial) {
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				ptr = searchRecursive(head->left, key);
				if (ptr != NULL)
					printf("\n node [%d] found at %p\n", ptr->key, ptr);
				else
					printf("\n Cannot find the node [%d]\n", key);
			}
			else
				printf("초기화를 먼저 진행해주세요\n");
			break;
		case 'i': case 'I':
			if (initial)
				inorderTraversal(head->left);
			else
				printf("초기화를 먼저 진행해주세요\n");
			break;
		case 'p': case 'P':
			if (initial)
				preorderTraversal(head->left);
			else
				printf("초기화를 먼저 진행해주세요\n");
			break;
		case 't': case 'T':
			if (initial)
				postorderTraversal(head->left);
			else
				printf("초기화를 먼저 진행해주세요\n");
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');
	return 1;
}

int initializeBST(Node** h) {
	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node* ptr) {//중위순회
	if (ptr) {//ptr이 NULL이면 그만둔다.
		inorderTraversal(ptr->left);//왼쪽 자식노드를 전달한다.
		printf("%d   ", ptr->key);//왼쪽 자식노드를 전달하다가 마지막 왼쪽 자식노드에서 전달한 왼쪽 자식노드가 NULL이 되면 윗 문장이 완료되고 마지막 왼쪽 자식노드의 값을 출력한다.
		inorderTraversal(ptr->right);//오른쪽 자식노드를 전달한다.
	}
}

void preorderTraversal(Node* ptr)//전위순회
{
	if (ptr) {//ptr이 NULL이라면 그만둔다.
		printf("%d   ", ptr->key);//우선적으로 노드의 키값을 출력한다.
		preorderTraversal(ptr->left);//왼쪽 자식노드를 전달한다.
		preorderTraversal(ptr->right);//오른쪽 자식노드를 전달한다.
	}
}

void postorderTraversal(Node* ptr)//후위 순회
{
	if (ptr) {//ptr이 NULL이라면 그만둔다.
		postorderTraversal(ptr->left);//왼쪽 자식노드를 전달한다.
		postorderTraversal(ptr->right);//오른쪽 자식노드를 전달한다.
		printf("%d   ", ptr->key);//왼쪽 자식노드와 오른쪽 자식노드 모두 NULL이던가 출력을 완료했다면 해당 노드의 값을 	출력한다.
	}
}

int insert(Node* head, int key)//노드를 삽입한다.
{
	Node* tmp = head->left;//삽입할 노드의 자리를 찾는다.
	Node* node = NULL;//삽입할 노드
	Node* tmp_ = NULL;//삽입할 노드의 부모노드를 찾는다.
	node = (Node*)malloc(sizeof(Node));//삽입할 노드를 할당받는다.
	node->key = key;//노드의 값을 초기화한다.
	node->left = node->right = NULL;//노드의 링크를 초기화 한다.
	if (!tmp) {//트리가 비었다면
		head->left = node;//해드노드의 삽입할 노드를 해드노드의 왼쪽 링크에 연결한다.
		return 0;//함수를 종료한다.
	}
	if (searchIterative(head, key) != NULL)return -1;//삽입할 키값을 가지는 노드가 있다면 함수를 종료한다. 이원탐색트리의 모든 원소는 서로 상이한 키값을 갖는다.
	while (tmp) {//마지막 위치까지 찾는다. NULL이 된다면 반복을 종료한다. 이때 tmp_에 들어갈 위치의 부모노드가 저장되어있다.
		tmp_ = tmp;//부모 노드를 기억한다.
		if (key < tmp->key)//전달받은 키값이 노드보다 작다면
			tmp = tmp->left;//왼쪽 자식노드로 이동한다.
		else//크다면
			tmp = tmp->right;//오른쪽 자식노드로 이동한다.
	}
	if (key < tmp_->key)//전달받은 키값이 부모노드보다 작다면
		tmp_->left = node;//부모노드의 왼쪽 자식노드자리에 들어간다.
	else//크다면
		tmp_->right = node;//부모노드의 오른쪽 자식노드자리에 들어간다.
	return 0;//함수를 종료한다.
}

int deleteLeafNode(Node* head, int key)//리프노드를 삭제한다.
{
	Node* tmp = head->left;//삭제할 노드를 찾는다.
	Node* tmp_ = head;//삭제한 노드의 부모노드를 찾는다.
	while (tmp) {//삭제할 노드를 찾을 때까지 반복한다.
		if (key == tmp->key)//삭제할 키값을 가지는 노드를 찾았다면
			break;//반복문을 종료한다.
		else if (key < tmp->key) {//삭제할 키값이 비교하는 노드보다 작다면 왼쪽으로 이동한다.
			tmp_ = tmp;//부모노드를 저장한다.
			tmp = tmp->left;//왼쪽자식노드로 이동한다.
		}
		else {//삭제할 키값이 비교하는 노드보다 크다면
			tmp_ = tmp;//부모노드를 저장한다.
			tmp = tmp->right;//오른쪽 자식노드로 이동한다.
		}
	}
	if (!tmp) {//노드를 찾지못했다면 메시지를 출력하고 함수를 종료한다.
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}
	else if (tmp->left != NULL && tmp->right != NULL) {//노드가 리프노드가 아닐경우 메시지를 출력하고 함수를 종료한다.
		printf("\n%d is not LeafNode\n", key);
		return 0;
	}
	else {//노드를 찾았다면
		if (key < tmp_->key)//삭제할 키값이 부모노드의 키값보다 작다면
			tmp_->left = NULL;//왼쪽 자식노드의 링크를 NULL로 만든다.
		else//삭제할 키값이 부모노드의 키값보다 크다면
			tmp_->right = NULL;//오른쪽 자식노드의 링크를 NULL로 만든다.
		free(tmp);//해당 키값을 가지는 노드를 삭제한다.
	}
	return 0;//함수를 종료한다.
}

Node* searchRecursive(Node* ptr, int key)//재귀적으로 키값을 가지는 노드를 찾는다.
{
	if (!ptr) return NULL;//트리가 비었다면 NULL을 리턴한다.
	if (ptr->key == key)//키값을 가지는 노드를 발견했다면 해당 노드를 리턴한다.
		return ptr;
	if (key < ptr->key)//키값이 노드보다 작다면 해당 노드의 왼쪽 자식노드의 주소로 재귀적으로 함수를 호출한다.
		return searchRecursive(ptr->left, key);
	return searchRecursive(ptr->right, key);//크다면 오른쪽 자식노드의 주소로 함수를 호출한다.
}

Node* searchIterative(Node* head, int key)//반복적으로 키값을 가지는 노드를 찾는다.
{
	Node* tmp = head->left;//키값을 가지는 노드를 찾는다.
	while (tmp) {//마지막까지 반복한다.
		if (key == tmp->key)//키값을 찾았다면 해당 노드를 리턴한다.
			return tmp;
		else if (key < tmp->key)//키값이 작다면 왼쪽 자식노드로 이동한다.
			tmp = tmp->left;
		else//키값이 크다면 오른쪽 자식노드로 이동한다.
			tmp = tmp->right;
	}
	return NULL;//찾지 못했다면 NULL을 리턴한다.
}

int freeBST(Node* head)//트리를 해제한다. 후위순회방식으로 해제한다.
{
	if (head != NULL) {//노드가 없다면 함수를 종료한다.
		freeBST(head->left);//왼쪽자식노드를 우선적으로 보낸다.
		if (head->right != head) {//노드의 오른쪽 자식노드가 자기 자신이 아니라면 즉, 해드노드가 아니라면 오른쪽 노드를 	보낸다.
			freeBST(head->right);
		}
		free(head);//노드를 해제한다.
	}
	return 0;//함수를 종료한다.
}
