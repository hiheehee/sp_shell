#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>

#define MAX_SIZE 100
#define    READ_END 0
#define    WRITE_END 1

int main(void) {

    char *input;//입력받은 문자열
    char *text1=NULL;

    char *command1[4];//앞쪽명령어

    int i ;
    char *pch;//문장나눌때 임시 저장
   //pipe
    int fd[2]; // 파이프 처리
    pid_t pid;
 while(1){
       printf("my_shell>> ");
       fflush(stdout);
      //입력값을 나누기
      input = (char*)malloc(MAX_SIZE*sizeof(char));
      fgets(input, MAX_SIZE, stdin);     
             //
             input[strlen(input)]='\0';
             i=0;//초기화
             pch = strtok (input," ");
             while (pch != NULL && i<3)
             {
             command1[i]=pch;
             pch = strtok (NULL, " ");
             i++;
             }
             command1[i]=(char*)0;

              if(strcmp(input,"\n")==0){  //입력이 없을 때
                  continue;
              }else if(strcmp(input,"exit\n")==0){ //나가기
                  break;
 
              }else if(strcmp(command1[0],"mkdir")==0){ //디렉토리 생성
		              if(mkdir(command1[1],0777)<0){
                                      perror(command1[1]);
                                      
                              }
                               continue;
              }else if(strcmp(command1[0],"rmdir")==0){ //디렉토리 제거 
		              if(rmdir(command1[1])<0){
                                      perror(command1[1]);
                                     
                         } continue;     
              }else if(strcmp(command1[0],"pwd\n")==0){ //현재 작업 위치 
		               system("pwd");
                              continue;
              }else if(strcmp(command1[0],"ls\n")==0){ //파일 목록 확인
		             execlp("/bin/ls","ls",NULL);
                             continue;
              }

    pid_t pid = fork();
    if (pid < 0) { //포크 에러
      perror("Fork error");
      exit(0);
    }

    if (pid == 0) { //자식 프로세스 생성
                
		execvp("/bin/ls", command1);
    }

    if (pid > 0) { //부모 프로세스 생성
               
               waitpid(pid,NULL,0);
    }

 }
return 0;
} 
