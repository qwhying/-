#include<pthread.h>
//#include<fstream>
//#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
//using namespace std;
int apple=0;
int orange=0;
int empty=1;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty_=PTHREAD_COND_INITIALIZER;
pthread_cond_t orange_=PTHREAD_COND_INITIALIZER;
pthread_cond_t apple_=PTHREAD_COND_INITIALIZER;
void *father(void)
{
    for(int i=0;i<3;i++)
    {
        pthread_mutex_lock(&lock);
        if(!empty)pthread_cond_wait(&empty_,&lock);
        printf("爸爸向盘中放一个苹果\n");
        apple++;
        empty--;
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&apple_);
    }
}
void *mother(void)
{
    for(int i=0;i<3;i++)
    {
        pthread_mutex_lock(&lock);
        if(!empty)pthread_cond_wait(&empty_,&lock);
        printf("妈妈向盘中放一个橘子\n");
        orange++;
        empty--;
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&orange_);
        
    }
}
void *son(void)
{
    for(int i=0;i<3;i++)
    {
        pthread_mutex_lock(&lock);
        if(!orange)pthread_cond_wait(&orange_,&lock);
        printf("儿子取出盘中橘子\n");
        orange--;
        empty++;
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&empty_);
    }
}
void *daughter(void)
{
    for(int i=0;i<3;i++)
    {
        pthread_mutex_lock(&lock);
        if(!apple)pthread_cond_wait(&apple_,&lock);
        printf("女儿取出盘中苹果\n");
        apple--;
        empty++;
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&empty_);
        
    }
}
int main(void)
{
    int ret=0;
    pthread_t id_f;
    pthread_t id_m;
    pthread_t id_s;
    pthread_t id_d;
    ret=pthread_create(&id_f,NULL,father,NULL);
    if(ret)
    {
        printf("创建线程失败！");
        return 1;
    }
    ret=pthread_create(&id_m,NULL,mother,NULL);
    if(ret)
    {
        printf("创建线程失败！");
        return 1;
    }
    ret=pthread_create(&id_s,NULL,son,NULL);
    if(ret)
    {
        printf("创建线程失败！");
        return 1;
    }
    ret=pthread_create(&id_d,NULL,daughter,NULL);
    if(ret)
    {
        printf("创建线程失败！");
        return 1;
    }
    pthread_join(id_f,NULL);
    pthread_join(id_m,NULL);
    pthread_join(id_s,NULL);
    pthread_join(id_d,NULL);

}