#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void child(int idx,pid_t parent,int level){                                 //A
  pid_t cpid[3]; int i; pid_t l_parent=getpid();
 if(idx==0 && level==1){                                //B                 C                   D
    for(i=0 ; i<2; i++){
      if((cpid[i]=fork())==0){                                       //E    F    G 
	    child(i,l_parent,2);
      }
    }
    sleep(5);
    for(i=0; i<2; i++){
      kill(cpid[i],SIGKILL);
      printf("We killed %d.\n", cpid[i]);
    }
    printf("MY_PID = %d, PARENT_ID = %d. I'm B.\n",getpid(),parent);
    sleep(5);
  }
    else if(idx== 1 && level == 1){
        printf("Hi, I'm C\n");
        printf("C: MY_PID=%d,PARENT_ID=%d, level = %d\n", getpid(),parent, level);
        sleep(1);
        if((cpid[2]=fork())==0){
            child(0, l_parent, 2);
        }
        sleep(10);
        kill(cpid[2], SIGKILL);
        sleep(5);
    }
  else{
    printf("MY_PID=%d,PARENT_ID=%d\n", getpid(),parent);
    sleep(10);
  }
}

int main(){

  pid_t cpid[2];
  pid_t parent = getpid();
  int i;
  for (i=0; i<2; i++){
    if((cpid[i]=fork())==0){
      child(i,parent,1);
    }
  }
  sleep(10);
  for(i=0; i<2; i++){
    kill(cpid[i],SIGKILL);
    printf("We killed %d.\n", cpid[i]);
  }
  sleep(5);
  printf("A:pid = %d\n",getpid());
  return 0;
}