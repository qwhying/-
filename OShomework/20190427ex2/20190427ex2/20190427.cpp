#include<Windows.h>
#include<process.h>
#include<stdio.h>
#include<conio.h>
#include<fstream>
#include<condition_variable>
#include<iostream>
struct ThreadInfo
{
	int tid; //线程ID
	char role;//扮演角色S/N
	double delay;//线程延迟
	double persist;//线程操作持续时间
};
using namespace std;
#define sleep(n) Sleep(n*1000)
//CONDITION_VARIABLE bothonbridge;//条件变量

HANDLE south,north,total;//互斥变量及信号量
void crossFromsouth(void *p);
void crossFromnorth(void *p);
int main()
{
	DWORD n_thread = 0;//线程数目
	DWORD thread_ID;//线程ID
	//线程对象数组
	HANDLE h_thread[10];
	ThreadInfo thread_info[10];
	//初始化同步对象
	south = CreateMutex(NULL, FALSE, LPCSTR("mutex_for_south_bridge"));
	north = CreateMutex(NULL, FALSE, LPCSTR("mutex_for_north_bridge"));
	total = CreateSemaphore(NULL, 2, 2, LPCTSTR("semaphore_for_total"));
	//创建几个从南来的
	for (int i = 0; i < 10; i++)
	{
		srand(time(0));
		int n = rand() % 100;
		if (n<50) {
			thread_info[i].tid = i;
			thread_info[i].role = 'S';
			thread_info[i].delay = 1;
			thread_info[i].persist = 1;
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(crossFromsouth), &thread_info[i], 0, &thread_ID);
			n_thread++;
		}
		else
		{
			thread_info[i].tid = i;
			thread_info[i].role = 'N';
			thread_info[i].delay = 1;
			thread_info[i].persist = 1;
			h_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(crossFromnorth), &thread_info[i], 0, &thread_ID);
			n_thread++;
		}
	}
	//创建几个从北来的
	/*for (int i = 0; i < 5; i++)
	{
		thread_info[i+5].tid = i+5;
		thread_info[i+5].role = 'N';
		thread_info[i+5].delay = 1;
		thread_info[i+5].persist = 1;
		h_thread[i+5] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(crossFromnorth), &thread_info[i+5], 0, &thread_ID);
		n_thread++;
	}*/
	DWORD wait_for_all = WaitForMultipleObjects(n_thread, h_thread, true, -1);
	printf("All thread have finish operating\n");
	return 0;
}
void crossFromsouth(void *p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	m_delay = ((ThreadInfo*)(p))->delay;
	m_persist = ((ThreadInfo*)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	//sleep(m_delay);//延迟等待
	WaitForSingleObject(total, -1);
	WaitForSingleObject(south, -1);
	printf("江安南来了一个人上桥，他是第%d个人\n",m_id+1);
	ReleaseMutex(south);
	printf("第%d个人进入桥中间\n", m_id+1);
	WaitForSingleObject(north,-1);
	printf("第%d个人从北面下桥\n", m_id+1);
	ReleaseMutex(north);
	ReleaseSemaphore(total, 1, NULL);
}
void crossFromnorth(void *p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	m_delay = ((ThreadInfo*)(p))->delay;
	m_persist = ((ThreadInfo*)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	//sleep(m_delay);//延迟等待
	WaitForSingleObject(total, -1);
	WaitForSingleObject(north, -1);
	printf("江安北来了一个人上桥，他是第%d个人\n", m_id+1);
	ReleaseMutex(north);
	printf("第%d个人进入桥中间\n", m_id+1);
	WaitForSingleObject(south, -1);
	printf("第%d个人从南面下桥\n", m_id+1);
	ReleaseMutex(south);
	ReleaseSemaphore(total, 1, NULL);
}