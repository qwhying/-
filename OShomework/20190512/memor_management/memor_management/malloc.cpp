#include <stdio.h>

#define MEM_SIZE 128
static char mem[MEM_SIZE];

#define MINBLK 16
struct block {
	struct block * next;
	size_t length;
	char data[0];
};

static struct block * free_list = NULL;

void malloc_init(void)
{
	free_list = (struct block *)mem;
	free_list->next = NULL;
	free_list->length = MEM_SIZE - sizeof(struct block);
}

void * malloc(size_t size)
{
	size = (size + 7) & ~7;

	struct block * prev = (struct block *) &free_list;
	struct block * cur = free_list;

	while (cur != NULL) {
		if (cur->length >= size) break;
		prev = cur;
		cur = cur->next;
	}

	if (cur == NULL)
		return NULL;

	if ((cur->length - size) >= MINBLK) {
		struct block * temp = (struct block *)(cur->data + size);
		temp->next = cur->next;
		temp->length = cur->length - size - sizeof(struct block);
		prev->next = temp;
		cur->length = size;
	}
	else {
		prev->next = cur->next;
	}

	return cur->data;
}

void free(void * ptr)
{
	if (ptr == NULL)
		return;

	struct block * temp = (struct block *)((char *)ptr - sizeof(struct block));//找到整个分配块的起始位置（也就是把length和next加进去）
	char * tempn = (char *)ptr + temp->length; // 和temp物理上相邻的下一个block的地址

	struct block * prev = (struct block *) &free_list;
	struct block * cur = free_list;
	char * curn = (char*)cur + sizeof(struct block) + cur->length; // 和cur物理上相邻的下一个block的地址

	// 考虑多种情况，完成free函数
	// ... ...
	bool combined = 0;
	while (cur != NULL)
	{
		char * curn = (char*)cur + sizeof(struct block) + cur->length;
	    if (curn == (char*)temp)//待释放的上一个是空闲块
	    {
		    //cur->next = temp->next;
		    temp->length = cur->length + sizeof(struct block) + temp->length;
		    combined = 1;
			prev->next = temp;
		    cur = cur->next;
	    }
		else if (cur == (struct block *)tempn)//待释放的下一个是空闲块
		{
			//cur->next=temp->next;
			temp->next = cur->next;
			temp->length = curn - (char*)ptr;
			prev->next = temp;
			combined = 1;
			cur=cur->next;//当前指针指向temp的起始位置
		}
		else {
			prev = cur;
			cur = cur->next;
		}
	}
	if (!combined)
	{
		prev->next = temp;
		temp->next = NULL;
	}
}

void malloc_state(void)
{
	printf("free blocks:\n");
	struct block * ptr;
	for (ptr = free_list; ptr != NULL; ptr = ptr->next) {
		int i;
		printf("%p:", ptr);
		for (i = 0; i < ptr->length; i++) {
			printf("=");
		}
		printf(" ");
	}
	printf("\n");
}
struct A {
	char a;
	char b;
	int c;
};
struct B {
	double b;
	char a;
	char c;
};
void malloc_test(void)
{
	malloc_state();

	//申请请求
	char *Ptr1 = NULL;
	Ptr1 = (char *)malloc(sizeof(struct A));
	malloc_state();
	char *Ptr2 = NULL;
	Ptr2 = (char *)malloc(sizeof(struct B));
	malloc_state();
	char *Ptr3 = NULL;
	Ptr3 = (char*)malloc(13 * sizeof(char));
	malloc_state();
	char *Ptr4 = NULL;
	Ptr4 = (char*)malloc(8 * sizeof(char));
	malloc_state();

	//释放请求
	free(Ptr1);//这是上下都无空闲块的情况
	Ptr1 = NULL;
	malloc_state();
	free(Ptr2);//这是上有空闲块的情况
	Ptr2 = NULL;
	malloc_state();
	free(Ptr4);//这是下有空闲块的情况
	Ptr4 = NULL;
	malloc_state();
	free(Ptr3);//这是上下都有空闲块的情况
	Ptr3 = NULL;
	malloc_state();
}

int main(int argc, const char *argv[])
{
	malloc_init();

	malloc_test();

	return 0;
}
