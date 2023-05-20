#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DataType;       // 链表存储的数据类型

struct ListNode   // 链表结点的结构体
{
	DataType data;
	struct ListNode* next;
};

typedef struct ListNode* LinkList; // LinkList为指向结构体ListNode的指针类型

// 单链表的建立
LinkList CreateList(void)
{
	LinkList head, tail, p;
	head = (LinkList)malloc(sizeof(struct ListNode));
	head->data = 0;
	head->next = NULL;
	tail = head;
	int n;
	printf("请输入单链表的长度：");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(struct ListNode));
		printf("请输入第%d个数据：", i + 1);
		scanf("%d", &p->data);
		p->next = NULL;
		tail->next = p;
		tail = p;
	}
	return head;
}

// 单链表的打印
void LocateNode(LinkList head)
{
	struct ListNode* p = head->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

// 单链表的查找1
// 单链表的查找1：查找指定值是否在链表中存在
void FindNode(LinkList head, DataType key)
{
	struct ListNode* p = head->next;
	int i = 1;
	while (p != NULL && p->data != key)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)
	{
		printf("找不到\n");
	}
	else
	{
		printf("找到了，在第%d个位置\n", i);
	}
}

// 单链表的查找2
LinkList GetNode(LinkList head, int i)
{
	struct ListNode* p = head->next;
	int j = 1;
	while (p != NULL && j < i)
	{
		p = p->next;
		j++;
	}
	if (j == i)
		return p;
	else
		return NULL;
}

// 单链表的插入
void InsertList(LinkList head, DataType x, int i)
{
	struct ListNode* p = GetNode(head, i - 1);
	if (p == NULL)
	{
		printf("插入位置不合法！\n");
		return;
	}
	struct ListNode* q = (LinkList)malloc(sizeof(struct ListNode));
	q->data = x;
	q->next = p->next;
	p->next = q;
}

// 单链表的删除
void DeleteList(LinkList head, int i)
{
	struct ListNode* p = GetNode(head, i - 1);
	if (p == NULL || p->next == NULL)
	{
		printf("删除位置不合法！\n");
		return;
	}
	struct ListNode* q = p->next;
	p->next = q->next;
	free(q);
}

// 删除单链表中重复值
void DeleteManyList(LinkList head)
{
	const int MAX_VALUE = 10000;
	bool exists[MAX_VALUE] = { false };
	
	struct ListNode* p = head->next;
	struct ListNode* prev = head;
	while (p != NULL)
	{
		if (exists[p->data])
		{
			prev->next = p->next;
			free(p);
			p = prev->next;
		}
		else
		{
			exists[p->data] = true;
			prev = p;
			p = p->next;
		}
	}
}

// 删除单链表中偶数值
void DeleteEvenList(LinkList head)
{
	struct ListNode* p = head;
	while (p->next != NULL)
	{
		if (p->next->data % 2 == 0)
		{
			struct ListNode* q = p->next;
			p->next = q->next;
			free(q);
		}
		else
		{
			p = p->next;
		}
	}
}

// 分割成两个单链表
void DivideList(LinkList head, LinkList* A, LinkList* B)
{
	*A = (LinkList)malloc(sizeof(struct ListNode));
	(*A)->next = NULL;
	*B = (LinkList)malloc(sizeof(struct ListNode));
	(*B)->next = NULL;
	struct ListNode* p = head->next;
	struct ListNode* q1 = *A, * q2 = *B;
	int i = 1;
	while (p != NULL)
	{
		if (i % 2 == 1)
		{
			q1->next = p;
			q1 = p;
		}
		else
		{
			q2->next = p;
			q2 = p;
		}
		p = p->next;
		i++;
	}
	q1->next = NULL;
	q2->next = NULL;
}

void PrintList(LinkList head)
{
	printf("单链表的元素为：");
	struct ListNode* p = head->next;
	while (p)
	{
		printf("%d", p->data);
		p = p->next;
	}
	printf("\n");
}

int main()
{
	int i;
	DataType key, x;
	LinkList head;
	struct ListNode* p;
	LinkList A, B;
	head = CreateList();     // 建立单链表
	LocateNode(head);        // 打印单链表
	printf("输入要查找的值：");
	scanf("%d", &key);
	FindNode(head, key);     // 单链表查找
	printf("请输入欲插入元素的位置：");
	scanf("%d", &i);
	printf("请输入欲插入的元素：");
	scanf("%d", &x);
	InsertList(head, x, i); // 单链表插入
	PrintList(head);        // 打印单链表
	printf("请输入欲删除结点的位置：");
	scanf("%d", &i);
	DeleteList(head, i);    // 单链表删除
	PrintList(head);        // 打印单链表
	DeleteManyList(head);   // 删除重复值
	PrintList(head);        // 打印单链表
	DeleteEvenList(head);   // 删除偶数值
	PrintList(head);        // 打印单链表
	DivideList(head, &A, &B);
	PrintList(A);
	PrintList(B);
	return 0;
}
