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

int initializeBST(Node** h);//�ʱ�ȭ �Լ�

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
	int initial = 0;//�ʱ�ȭ�� ����ƴ��� Ȯ���Ѵ�.
	Node* head = NULL;//�ص���
	Node* ptr = NULL;//�ӽ� ���

	printf("[----- [������] [2018038031] -----]\n");

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
			initial++;//�ʱ�ȭ�� ����ȴٸ� +1�� ���ش�.
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
				printf("�ʱ�ȭ�� ���� �������ּ��� \n");
			break;
		case 'd': case 'D':
			if (initial) {
				printf("Your Key = ");
				fflush(stdout);
				scanf("%d", &key);
				deleteLeafNode(head, key);
			}
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
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
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
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
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'i': case 'I':
			if (initial)
				inorderTraversal(head->left);
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 'p': case 'P':
			if (initial)
				preorderTraversal(head->left);
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
			break;
		case 't': case 'T':
			if (initial)
				postorderTraversal(head->left);
			else
				printf("�ʱ�ȭ�� ���� �������ּ���\n");
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

void inorderTraversal(Node* ptr) {//������ȸ
	if (ptr) {//ptr�� NULL�̸� �׸��д�.
		inorderTraversal(ptr->left);//���� �ڽĳ�带 �����Ѵ�.
		printf("%d   ", ptr->key);//���� �ڽĳ�带 �����ϴٰ� ������ ���� �ڽĳ�忡�� ������ ���� �ڽĳ�尡 NULL�� �Ǹ� �� ������ �Ϸ�ǰ� ������ ���� �ڽĳ���� ���� ����Ѵ�.
		inorderTraversal(ptr->right);//������ �ڽĳ�带 �����Ѵ�.
	}
}

void preorderTraversal(Node* ptr)//������ȸ
{
	if (ptr) {//ptr�� NULL�̶�� �׸��д�.
		printf("%d   ", ptr->key);//�켱������ ����� Ű���� ����Ѵ�.
		preorderTraversal(ptr->left);//���� �ڽĳ�带 �����Ѵ�.
		preorderTraversal(ptr->right);//������ �ڽĳ�带 �����Ѵ�.
	}
}

void postorderTraversal(Node* ptr)//���� ��ȸ
{
	if (ptr) {//ptr�� NULL�̶�� �׸��д�.
		postorderTraversal(ptr->left);//���� �ڽĳ�带 �����Ѵ�.
		postorderTraversal(ptr->right);//������ �ڽĳ�带 �����Ѵ�.
		printf("%d   ", ptr->key);//���� �ڽĳ��� ������ �ڽĳ�� ��� NULL�̴��� ����� �Ϸ��ߴٸ� �ش� ����� ���� 	����Ѵ�.
	}
}

int insert(Node* head, int key)//��带 �����Ѵ�.
{
	Node* tmp = head->left;//������ ����� �ڸ��� ã�´�.
	Node* node = NULL;//������ ���
	Node* tmp_ = NULL;//������ ����� �θ��带 ã�´�.
	node = (Node*)malloc(sizeof(Node));//������ ��带 �Ҵ�޴´�.
	node->key = key;//����� ���� �ʱ�ȭ�Ѵ�.
	node->left = node->right = NULL;//����� ��ũ�� �ʱ�ȭ �Ѵ�.
	if (!tmp) {//Ʈ���� ����ٸ�
		head->left = node;//�ص����� ������ ��带 �ص����� ���� ��ũ�� �����Ѵ�.
		return 0;//�Լ��� �����Ѵ�.
	}
	if (searchIterative(head, key) != NULL)return -1;//������ Ű���� ������ ��尡 �ִٸ� �Լ��� �����Ѵ�. �̿�Ž��Ʈ���� ��� ���Ҵ� ���� ������ Ű���� ���´�.
	while (tmp) {//������ ��ġ���� ã�´�. NULL�� �ȴٸ� �ݺ��� �����Ѵ�. �̶� tmp_�� �� ��ġ�� �θ��尡 ����Ǿ��ִ�.
		tmp_ = tmp;//�θ� ��带 ����Ѵ�.
		if (key < tmp->key)//���޹��� Ű���� ��庸�� �۴ٸ�
			tmp = tmp->left;//���� �ڽĳ��� �̵��Ѵ�.
		else//ũ�ٸ�
			tmp = tmp->right;//������ �ڽĳ��� �̵��Ѵ�.
	}
	if (key < tmp_->key)//���޹��� Ű���� �θ��庸�� �۴ٸ�
		tmp_->left = node;//�θ����� ���� �ڽĳ���ڸ��� ����.
	else//ũ�ٸ�
		tmp_->right = node;//�θ����� ������ �ڽĳ���ڸ��� ����.
	return 0;//�Լ��� �����Ѵ�.
}

int deleteLeafNode(Node* head, int key)//������带 �����Ѵ�.
{
	Node* tmp = head->left;//������ ��带 ã�´�.
	Node* tmp_ = head;//������ ����� �θ��带 ã�´�.
	while (tmp) {//������ ��带 ã�� ������ �ݺ��Ѵ�.
		if (key == tmp->key)//������ Ű���� ������ ��带 ã�Ҵٸ�
			break;//�ݺ����� �����Ѵ�.
		else if (key < tmp->key) {//������ Ű���� ���ϴ� ��庸�� �۴ٸ� �������� �̵��Ѵ�.
			tmp_ = tmp;//�θ��带 �����Ѵ�.
			tmp = tmp->left;//�����ڽĳ��� �̵��Ѵ�.
		}
		else {//������ Ű���� ���ϴ� ��庸�� ũ�ٸ�
			tmp_ = tmp;//�θ��带 �����Ѵ�.
			tmp = tmp->right;//������ �ڽĳ��� �̵��Ѵ�.
		}
	}
	if (!tmp) {//��带 ã�����ߴٸ� �޽����� ����ϰ� �Լ��� �����Ѵ�.
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}
	else if (tmp->left != NULL && tmp->right != NULL) {//��尡 ������尡 �ƴҰ�� �޽����� ����ϰ� �Լ��� �����Ѵ�.
		printf("\n%d is not LeafNode\n", key);
		return 0;
	}
	else {//��带 ã�Ҵٸ�
		if (key < tmp_->key)//������ Ű���� �θ����� Ű������ �۴ٸ�
			tmp_->left = NULL;//���� �ڽĳ���� ��ũ�� NULL�� �����.
		else//������ Ű���� �θ����� Ű������ ũ�ٸ�
			tmp_->right = NULL;//������ �ڽĳ���� ��ũ�� NULL�� �����.
		free(tmp);//�ش� Ű���� ������ ��带 �����Ѵ�.
	}
	return 0;//�Լ��� �����Ѵ�.
}

Node* searchRecursive(Node* ptr, int key)//��������� Ű���� ������ ��带 ã�´�.
{
	if (!ptr) return NULL;//Ʈ���� ����ٸ� NULL�� �����Ѵ�.
	if (ptr->key == key)//Ű���� ������ ��带 �߰��ߴٸ� �ش� ��带 �����Ѵ�.
		return ptr;
	if (key < ptr->key)//Ű���� ��庸�� �۴ٸ� �ش� ����� ���� �ڽĳ���� �ּҷ� ��������� �Լ��� ȣ���Ѵ�.
		return searchRecursive(ptr->left, key);
	return searchRecursive(ptr->right, key);//ũ�ٸ� ������ �ڽĳ���� �ּҷ� �Լ��� ȣ���Ѵ�.
}

Node* searchIterative(Node* head, int key)//�ݺ������� Ű���� ������ ��带 ã�´�.
{
	Node* tmp = head->left;//Ű���� ������ ��带 ã�´�.
	while (tmp) {//���������� �ݺ��Ѵ�.
		if (key == tmp->key)//Ű���� ã�Ҵٸ� �ش� ��带 �����Ѵ�.
			return tmp;
		else if (key < tmp->key)//Ű���� �۴ٸ� ���� �ڽĳ��� �̵��Ѵ�.
			tmp = tmp->left;
		else//Ű���� ũ�ٸ� ������ �ڽĳ��� �̵��Ѵ�.
			tmp = tmp->right;
	}
	return NULL;//ã�� ���ߴٸ� NULL�� �����Ѵ�.
}

int freeBST(Node* head)//Ʈ���� �����Ѵ�. ������ȸ������� �����Ѵ�.
{
	if (head != NULL) {//��尡 ���ٸ� �Լ��� �����Ѵ�.
		freeBST(head->left);//�����ڽĳ�带 �켱������ ������.
		if (head->right != head) {//����� ������ �ڽĳ�尡 �ڱ� �ڽ��� �ƴ϶�� ��, �ص��尡 �ƴ϶�� ������ ��带 	������.
			freeBST(head->right);
		}
		free(head);//��带 �����Ѵ�.
	}
	return 0;//�Լ��� �����Ѵ�.
}
