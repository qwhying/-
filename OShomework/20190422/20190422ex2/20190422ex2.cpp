#include<Windows.h>>
#include<conio.h>//控制台输入输出 console input/output
#include<fstream>
#include<iostream>
using namespace std;
#define sleep(n) Sleep(n*1000)
void input(void *p);
void calculate(void *p);
void output(void *p);
struct ThreadInfo
{
	int tid; //线程ID
	char role;//扮演角色I/O/C
	double delay;//线程延迟
	double persist;//线程操作持续时间
};
HANDLE mutex1, mutex2,full1,full2,empty1,empty2;
//CRITICAL_SECTION buffer1, buffer2;
int main(void)
{
	DWORD n_thread = 0;//线程数目
	DWORD thread_ID;//线程ID
	//线程对象数组 
	HANDLE h_thread[3];
	ThreadInfo thread_info[3];
	//初始化同步对象
	mutex1 = CreateMutex(NULL, FALSE, LPCSTR("mutex_for_buffer1"));
	mutex2 = CreateMutex(NULL, FALSE, LPCSTR("mutex_for_buffer2"));
	full1 = CreateSemaphore(NULL, 0, 1, LPCTSTR("semaphore_for_full1"));
	full2 = CreateSemaphore(NULL, 0, 1, LPCTSTR("semaphore_for_full2"));
	empty1= CreateSemaphore(NULL, 1, 1, LPCTSTR("semaphore_for_empty1"));
	empty2 = CreateSemaphore(NULL, 1, 1, LPCTSTR("semaphore_for_empty2"));
	thread_info[0].tid = 1;
	thread_info[0].role = 'I';
	thread_info[0].delay = 3;
	thread_info[0].persist = 5;
	h_thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(input), &thread_info[0], 0, &thread_ID);
	n_thread++;
	thread_info[1].tid = 2;
	thread_info[1].role = 'C';
	thread_info[1].delay = 4;
	thread_info[1].persist = 5;
	h_thread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(calculate), 
	  &thread_info[1], 0, &thread_ID);
	n_thread++;
	thread_info[2].tid = 3;
	thread_info[2].role = 'O';
	thread_info[2].delay = 5;
	thread_info[2].persist = 2;
	h_thread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(output), &thread_info[2], 0, &thread_ID);
	n_thread++;
	DWORD wait_for_all = WaitForMultipleObjects(n_thread, h_thread, true, -1);
	printf("All thread have finish operating\n");
	return 0;
}
void input(void *p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo*)(p))->delay;
	m_persist = ((ThreadInfo*)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	sleep(m_delay);//延迟等待
	printf("输入线程发送请求buffer1\n");
	//等待资源
	WaitForSingleObject(empty1, -1);
	WaitForSingleObject(mutex1, -1);
	printf("输入线程开始输入,添加到buffer1\n");
	sleep(m_persist);
	printf("输入线程完成\n");
	ReleaseMutex(mutex1);//释放互斥信号量
	ReleaseSemaphore(full1,1, NULL);//释放信号量full1
}
void calculate(void *p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo*)(p))->delay;
	m_persist = ((ThreadInfo*)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	sleep(m_delay);//延迟等待
	printf("计算线程发送请求buffer1\n");
	//等待资源
	WaitForSingleObject(full1, -1);
	WaitForSingleObject(mutex1, -1);
	printf("计算线程从buffer1取数据并开始计算\n");
	sleep(m_persist);
	printf("计算线程完成计算\n");
	ReleaseMutex(mutex1);//释放互斥信号量1
	ReleaseSemaphore(empty1, 1, NULL);//释放信号量empty1
	WaitForSingleObject(empty2, -1);
	WaitForSingleObject(mutex2, -1);
	printf("计算线程将结果放入到buffer2\n");
	ReleaseMutex(mutex2);//释放互斥信号量2
	ReleaseSemaphore(full2, 1, NULL);//释放信号量full2
}
void output(void *p)
{
	DWORD m_delay;
	DWORD m_persist;
	int m_id;
	//从参数中获取信息
	m_delay = ((ThreadInfo*)(p))->delay;
	m_persist = ((ThreadInfo*)(p))->persist;
	m_id = ((ThreadInfo*)(p))->tid;
	sleep(m_delay);//延迟等待
	printf("输出线程发送请求buffer2\n");
	//等待资源
	WaitForSingleObject(full2, -1);
	WaitForSingleObject(mutex1, -1);
	printf("输出线程从buffer2取走计算结果\n");
	sleep(m_persist);
	printf("打印\n");
	ReleaseMutex(mutex2);//释放互斥信号量2
	ReleaseSemaphore(empty2, 1, NULL);//释放信号量empty2
}


