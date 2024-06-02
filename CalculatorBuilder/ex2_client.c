// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// OS_2.c
// 22/12/2022
// yaniv hajaj  
// Description: OS EX2 client
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*cd Desktop/OSEX2 */
/*gcc ex2_srv.c -o ex2_srv.out (compiling)*/
/*./ex2_srv.out & (run program)*/

/*gcc ex2_client.c -o ex2_client.out (compiling)*/
/*./ex2_client.out (SPID) 30 1 40 (run program)*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <errno.h>

#include <stdlib.h>

#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <string.h>

void sig_handler_client(int num){
//;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     
//handler for client   
    int pid1,pid2;
    int status;
	int clientPidInt = getpid();
	char clientPidChar[6];
	char ToClienFile[51]="";
	strcat(ToClienFile,"to_client_"); //concatanting strings
	sprintf(clientPidChar, "%d", clientPidInt); //convert int to string
	strcat(ToClienFile,clientPidChar);
	strcat(ToClienFile,".txt");
	printf("(in client) ToClientFile path is:%s\n",ToClienFile);

	if ( (pid1 = fork()) < 0){ //fork patent Spid=son's pid if 0
		printf("fork error num1"); //error
		exit(-1);
	}	
	else{
		if (pid1 == 0){
		/* child1 */
			
			int FdToClient = open(ToClienFile,O_RDONLY); //open fd for to_client_xxxx.txt
			printf("(in client) inside child1\n");
			printf("(in client) return value of FdToClient is:%d\n",FdToClient);
			if(FdToClient==-1){
				printf("(in client) error open client file\n"); //error
				exit(-1);
				}
			char ResultStr[51]; 
            int RealClientRead = read(FdToClient, ResultStr, 51); //read result
			ResultStr[RealClientRead]='\0';
			if(RealClientRead==-1){
				printf("error read from client file/n"); //error
				exit(-1);
				}
			close(FdToClient);//finish reading
            printf("(in client) ***the result is: %s we are in client Pid: %d ***\n", ResultStr,clientPidInt); //print result
			execl("/bin/rm","rm",ToClienFile,NULL); //delete file ToClient
		}	
		else{
		/* parent1 */
		waitpid(pid1,&status,NULL);
		}		
	}
	exit(0);
}



//main:
int main(int argc,char* argv[]){
        signal(SIGUSR1, sig_handler_client); //if SIGUSR1 is coming from server goto sig_handler_client
        //check if input is legal 
        if(argc!=5){
           char MSG[] = "arguments dont match\n";
           write(1, MSG,strlen(MSG));
           exit(1);  
        }
          char P3 = *argv[3];
        if((P3!='1')&&(P3!='2')&&(P3!='3')&&(P3!='4')){
           char MSG[] = "code is wrong\n";
           write(1, MSG,strlen(MSG));
           exit(1);
           }   
          if((P3 == '4')&&(*argv[4]=='0')){
           char MSG[] = "error cannot divide by zero\n";
           write(1, MSG,strlen(MSG));
           exit(1);
           }   


        int ServerPID;
		int i;
		int OpenedFlag;
		int clientPID = getpid(); //client's pid    
        sscanf(argv[1],"%d", &ServerPID); //cast string to int and get ServerPID
         
		
        srand(time(0));// Seed the pseudorandom number generator with the current time
        int SecWait;
		int FDtoServer;
        for(i=0;i<10;++i)
        {
            if((FDtoServer = open("to_srv.txt", O_RDWR|O_CREAT|O_APPEND|O_EXCL, 0666))== -1){ //wait random number of sec if nannot open file
               SecWait = rand() % 5;//modolo to get 0-4 number
               SecWait += 1;//add 1 in order to wait 1-5 sec
               sleep(SecWait);
            }
            else{ //file was opened
                OpenedFlag = 1;
                break;
                }
        }
        if(OpenedFlag == 0){ //flag=0 cnnot openfile 10 times
           char MSG[] = "tried open file 10 times and failed\n";
           write(1, MSG,strlen(MSG));
           close(FDtoServer);
           exit(1); 
           }

		
		printf("(in client) client PID :%d\n", clientPID);//client PID
        printf("(in client) num 1 :%s\n", argv[2]);//num1
        printf("(in client) mode :%c\n", *argv[3]);//mode (only 1 char so use *)
        printf("(in client) num 2 :%s\n", argv[4]);//num2
		
        //if file to server opened
        int pid,status;
        if(pid=fork()==0){ //son
           dup2(FDtoServer,1);//redirect writiong to file instead of screen
           close(FDtoServer);//close the old link to FD of FDtoServer
           printf("%d ", clientPID);//client PID
           printf("%s ", argv[2]);//num1
           printf("%c ", *argv[3]);//mode
           printf("%s ", argv[4]);//num2
           }
        else{//if father
             waitpid(pid,&status,NULL); //waiting for son
             close(FDtoServer);
             if(kill(ServerPID, SIGUSR2)==-1){ //send signal SIGUSR2 to server
                printf("error sending signal to server from client:%d\n",getpid());
                if(pid=fork()==0){
                   execl("/bin/rm","rm","to_srv.txt",NULL); //delete to_srv
                   }
                waitpid(pid,&status,NULL);
                exit(1);
                }
             pause(); //wait for server
             }
        exit(0);
}


/* fork template
if ( (Spid = fork()) < 0){ //fork patent Spid=son's pid
			printf("fork error"); //error
		}	
		else{
			if (Spid == 0){
			 // child 
			 
				//printf("inside child\n");
				dup2(inputFD,0); //make inputfile default (keyboard)
				dup2(RealOutputFD,1); //make outputfile default (screen)
				char *args[] = {main_path, NULL };
				execv(main_path, args);//run main an
				//execl(main_path,main_path,NULL);	
			}	
			else{
			// parent 
				//printf("parent before wait\n");
				wait(&status);;//wait for son to end   
				//printf("parent after wait\n");
			}
		}

*/		
