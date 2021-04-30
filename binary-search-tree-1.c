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
int max_queue = 0;//해제함수에서 큐배열의 크기 노드의 수랑 같다.

int main()
{
	char command;
	int key;
	Node* head = NULL;//해드노드
	Node* ptr = NULL;//임시 노드

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
			max_queue = 0;//초기화를 하면 노드가 0개가 되므로 똑같이 초기화
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			max_queue++;//노드를 삽입하면 +1
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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

void inorderTraversal(Node* ptr){//중위순회
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
		printf("%d   ", ptr->key);//왼쪽 자식노드와 오른쪽 자식노드 모두 NULL이던가 출력을 완료했다면 해당 노드의 값을 출력한다.
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
	while (tmp) {//마지막 위치까지 찾는다. NULL이 된다면 반복을 종료한다. 이때 tmp_에 들어갈 위치의 부모노드가 저장되어있다.
		tmp_ = tmp;//부모 노드를 기억한다.
		if (key <= tmp->key)//전달받은 키값이 노드보다 작거나 같다면
			tmp = tmp->left;//왼쪽 자식노드로 이동한다.
		else//크다면
			tmp = tmp->right;//오른쪽 자식노드로 이동한다.
	}
	if (key <= tmp_->key)//전달받은 키값이 부모노드보다 작거나 같다면
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
		else if (key <= tmp->key) {//삭제할 키값이 비교하는 노드보다 작거나 같다면 왼쪽으로 이동한다.
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
		if (key <= tmp_->key)//삭제할 키값이 부모노드의 키값보다 작거나 같다면
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
	if (key <= ptr->key)//키값이 노드보다 작거나 같다면 해당 노드의 왼쪽 자식노드의 주소로 재귀적으로 함수를 호출한다.
		return searchRecursive(ptr->left, key);
	return searchRecursive(ptr->right, key);//크다면 오른쪽 자식노드의 주소로 함수를 호출한다.

}

Node* searchIterative(Node* head, int key)//반복적으로 키값을 가지는 노드를 찾는다.
{
	Node* tmp = head->left;//키값을 가지는 노드를 찾는다.
	while (tmp) {//마지막까지 반복한다.
		if (key == tmp->key)//키값을 찾았다면 해당 노드를 리턴한다.
			return tmp;
		else if (key <= tmp->key)//키값이 작거나 같다면 왼쪽 자식노드로 이동한다.
			tmp = tmp->left;
		else//키값이 크다면 오른쪽 자식노드로 이동한다.
			tmp = tmp->right;
	}
	return NULL;//찾지 못했다면 NULL을 리턴한다.
}


int freeBST(Node* head)//트리를 해제한다. 큐를 이용하여 레벨순회방식으로 해제한다.
{
	int rear = 0;//리어
	int front = -1;//프론트
	Node* node = head->left;//해제할 노드
	Node** queue = (Node**)malloc(sizeof(Node*) * max_queue);//큐 배열의 크기를 노드의 수만큼 할당받는다.

	if (!node)//트리가 비었다면 함수를 종료한다.
		return 0;
	queue[rear++] = node;//트리의 루트노드를 인큐한다.
	while (1) {//반복한다.
		node = queue[++front];//디큐한다.
		if (front != max_queue) {//마지막노드까지 해제가 되지 않았다면
			if (node->left)//노드의 왼쪽 자식노드가 있다면
				queue[rear++] = node->left;//인큐한다.
			if (node->right)//노드의 오른쪽 자식노드가 있다면
				queue[rear++] = node->right;//인큐한다.
			free(node);//노드를 해제한다.
		}
		else//마지막 노드까지 해제를 했다면
			break;//반복을 종료한다.
	}
	free(head);//해드노드를 해제한다.
	return 0;//함수를 종료한다.
}
