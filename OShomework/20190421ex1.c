#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
sem_t metux;//表示父母儿女线程的互斥使用
sem_t empty;//表示盘子是否为空
sem_t apple;//是否可以取苹果
sem_t orange;//是否可以取橘子
void *father(void)
{
   for(int i=0;i<3;i++){
       sem_wait(&empty);//等待盘子为空
       sem_wait(&metux);//等待获取对盘子的操作
       printf("爸爸向盘中放一个苹果\n");
       sem_post(&metux);//释放对盘子的操作
       sem_post(&apple);//通知女儿可以来盘子中取苹果
   }
}
void *mother(void)//与父亲雷同
{
    for(int i=0;i<3;i++){
        sem_wait(&empty);
        sem_wait(&metux);
        printf("妈妈向盘中放一个橘子\n");
        sem_post(&metux);
        sem_post(&orange);//通知儿子可以来盘子中取橘子
    }
}
void *son(void)
{
    for(int i=0;i<3;i++){
        sem_wait(&orange);//判断盘子中是否有橘子
        sem_wait(&metux);//等待获取盘子的操作
        printf("儿子取出盘子中的橘子\n");
        sem_post(&metux);//释放对盘子的操作
        sem_post(&empty);//盘子空了，可以继续放水果了
    }
}
void *daughter(void)//与儿子雷同
{
    for(int i=0;i<3;i++){
        sem_wait(&apple);
        sem_wait(&metux);
        printf("女儿取出盘中苹果\n");
        sem_post(&metux);
        sem_post(&empty);
    }
}
int main(void)
{
    //四个并发线程的同步执行

    int ret=0;
    pthread_t id_f;
    pthread_t id_m;
    pthread_t id_s;
    pthread_t id_d;

    sem_init(&apple,0,0);
    sem_init(&orange,0,0);
    sem_init(&metux,0,1);
    sem_init(&empty,0,1);

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

    /*pthread_cancel(&id_f);//结束线程
    pthread_cancel(&id_m);
    pthread_cancel(&id_s);
    pthread_cancel(&id_d);*/

    pthread_join(id_f,NULL);
    pthread_join(id_m,NULL);
    pthread_join(id_s,NULL);
    pthread_join(id_d,NULL);

    sem_destroy(&apple);
    sem_destroy(&orange);
    sem_destroy(&metux);
    sem_destroy(&empty);
    return 0;

}