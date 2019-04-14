#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
int main()
{
     int pid=fork();
     if(pid==-1)
{
      printf("error!\n");
     }else if(pid==0){
      printf("This is the child process!\nchild process id =%d\n",getpid());
}else {
	wait(NULL);
     printf("This is the parent process!\nparent process id=%d\n",getpid());
}
 return 0;
}
