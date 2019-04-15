#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#define MAX_SPACE 100
typedef struct Data {
	int num; //斐波那契数列的项数
	int fibo[MAX_SPACE];//最大容量，斐波那契数列
}Data;
DWORD WINAPI thread_fibonacci(void* data)
{
	Data *tmp = (Data*)data;
	int i;
	int x0 = 0;
	int x1 = 1;
	int x2;
	tmp->fibo[0] = 0;
	tmp->fibo[1] = 1;
	if (tmp->num <= 2)return 0;
	for (i = 2; i < tmp->num; i++)
	{
		x2 = x1 + x0;
		x0 = x1;
		x1 = x2;
		tmp->fibo[i] = x2;
	}
	printf("Thread returned successfully\n");
	return 0;
}
int main(int argc, char* argv[])
{
	Data data;
	data.num = atoi(argv[1]);
	HANDLE hThread;
	DWORD ThreadID;
	int i;
	int a_thread;
	hThread = CreateThread(NULL, 0, thread_fibonacci, (void *)&data,0,&ThreadID);
	/*if (res != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}*/
	printf("Waiting for thread to finish..\n");
    WaitForSingleObject(hThread, INFINITE);
	/*if (res != 0) {
		perror("Thread  join failed");
		exit(EXIT_FAILURE);
	}*/
	printf("The Fibonacci %d items are:\n", data.num);
	for (int j = 0; j < data.num; j++)
	{
		printf("%d ", data.fibo[j]);
	}
	printf("\n");


}
