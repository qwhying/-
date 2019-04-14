#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
    pid_t pid;
        int x0,x1,x2;
        x0=0;
        x1=1;
    if(argv[1]<0)
      {
           printf("input error!");
           }
      pid=fork();
    //printf("pid=%d",pid);
     if(pid<0)
     {//出错
           printf("fork失败");
           exit(-1);
       }
     else if(pid==0)
     {//子进程
          printf("argv[1]=%d\n",atoi(argv[1]));
	  printf("%d %d ",x0,x1);
          for(int i=2;i<atoi(argv[1]);i++)
        {
           x2=x0+x1;
           x0=x1;
           x1=x2;
           printf("%d ",x2);
        }
         printf("\n子进程完成");
     }
     else
     {//父进程
          wait(NULL);
          printf("\n父进程退出\n");
     }
     return 0;
}    
