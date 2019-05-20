#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_SPACE 100
 typedef struct Data{
     int num; //斐波那契数列的项数
     int fibo[MAX_SPACE];//最大容量，斐波那契数列
}Data;
void *thread_fibonacci(void* data)
{
    Data *tmp=(Data*)data;
    int i;
    int x0=0;
    int x1=1;
    int x2;
    tmp->fibo[0]=0;
    tmp->fibo[1]=1;
    if(tmp->num<=2)return;
    for( i=2;i<tmp->num;i++)
    {
        x2=x1+x0;
        x0=x1;
        x1=x2;
        tmp->fibo[i]=x2;
    }
}
int main(int argc,char* argv[])
{
    Data data;
    data.num=atoi(argv[1]);
    int res;
    int i;
    pthread_t a_thread;
    res=pthread_create(&a_thread,NULL,thread_fibonacci,(void *)&data);
    if(res!=0){perror("Thread creation failed");
                          exit(EXIT_FAILURE);}
    printf("Waiting for thread to finish..\n");
    res=pthread_join(a_thread,NULL);
    if(res!=0){perror("Thread  join failed");
                          exit(EXIT_FAILURE);}
    printf("The Fibonacci %d items are:\n",data.num);
    for(int j=0;j<data.num;j++)
    {
        printf("%d ",data.fibo[j]);
    }
    printf("\n");
    

}
