// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// OS_2.c
// 22/12/2022
// yaniv hajaj  
// Description: OS EX2 server
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*cd Desktop/OSEX2 */
/*gcc ex2_srv.c -o ex2_srv.out (compiling)*/
/*./ex2_srv.out & (run program)*/

/*gcc ex2_client.c -o ex2_client.out (compiling)*/
/*./ex2_client.out (SPID) 30 1 40 (run program)*/

#include <stdio.h>
#include <sys/fcntl.h>

#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

#include <signal.h>

void signalHandler()
{  	
  int pid,status;
  int i = 0;
  if(pid = fork() == 0 ){ 
	 int ToServerFD = open("to_srv.txt", O_RDONLY); //Open to_srv.txt
	 if(ToServerFD==-1){
		printf("canot open to_srv file\n"); //error in open the file
		exit(-1);
		}
	
	//
	char ClientPID[51];
	char mode[2];
	char num1[51];
	char num2[51];
	char Onechar;
	int read1 = 1;
	//read pid of server
	while (read1>0) 
	{  	
		read1 = read(ToServerFD, &Onechar, 1);
		if (read1==-1){ 
			printf("cannot read server PID\n");
			exit(-1);
		}
		if (Onechar == ' '){ 
			break;//' ' move on 
		}
		ClientPID[i]=Onechar;   
		i++;
	}
	ClientPID[i] = '\0';
	
	//read num1
	int i=0;
	while (read1>0)
	{ 	
		read1 = read(ToServerFD, &Onechar, 1);
		if (read1==-1){ 
			printf("cannot read num1\n"); 
			exit(-1);
		}
		if (Onechar == ' '){ 
			break;//' ' move on 
		}
		num1[i]=Onechar;
		i++;
	}  
	num1[i]='\0';
  

	//read mode
	i=0;
	while (read1>0)
	{ 	
		read1 = read(ToServerFD, &Onechar, 1);
		if (read1==-1){ 
			printf("canot read mode\n"); 
			exit(-1);
		}
		if (Onechar == ' '){ 
			break;//' ' move on 
		}
		mode[i]=Onechar;  
		i++;
	}
	mode[1]='\0';

	//read num2
	i=0;
	while (read1>0)
	{ 	
		read1 = read(ToServerFD, &Onechar, 1);
		if (read1==-1){ 
			printf("canot read num2\n"); 
			exit(-1);
		}
		if (Onechar == ' '){
			break;//' ' move on 
		}
		num2[i]=Onechar;  
		i++;
	}
	//printf("num2: %s\n", num2);
	
	
	int pidMode;
	num2[i]='\0';
	
	close(ToServerFD);//close file
	if(pidMode=fork()==0){ 	//delete file immideatly after read to allow another client to write to server
		execl("/bin/rm","rm","to_srv.txt",NULL); 
		}


	int cast_int;
	sscanf(num1, "%d", &cast_int);//cast string to int and get 
	int num1_int = cast_int;
	sscanf(mode, "%d", &cast_int);//cast string to int and get 
	int mode_int = cast_int;
	sscanf(num2, "%d", &cast_int);//cast string to int and get 
	int num2_int = cast_int;


	int num1INT = atoi(num1);
	int modeINT = atoi(mode);
	int num2INT = atoi(num2);
	int ClientPidINT = atoi(ClientPID);
	
	printf("(in server) num 1 :%d\n", num1_int);
	printf("(in server) mode :%d\n", mode_int);
	printf("(in server) num 2 :%d\n", num2_int);
	printf("(in server) clientPID :%d\n", ClientPidINT);
	 

	//calculate:

	int result;
	switch (modeINT){
		case 1:
			result = num1INT + num2INT;
			break;
		case 2:
			result = num1INT - num2INT;
			break;
		case 3:
			result = num1INT * num2INT;
			break;
		case 4:
			result = num1INT / num2INT;
			break;
			}

	printf("(in server) the result is: %d\n", result);


	//create file to_client
	char ToclientFileName[51]="to_client_";
	strcat(ToclientFileName, ClientPID);
	strcat(ToclientFileName, ".txt");
	//create file ToclientFileName
	int ToClientFD = open(ToclientFileName,O_RDWR|O_CREAT|O_APPEND, 0666); //Open or create to_client_txt
	if(ToClientFD==-1){
	  printf("canot open ToclientFile\n"); 
	  exit(-1);
	  } 
	if(pid=fork()==0){ /*Creat a procces*/
		dup2(ToClientFD,1);
		printf("%d ", result);
		}
	waitpid(pid,&status,NULL);
	close(ToClientFD);
	kill(ClientPidINT, SIGUSR1); //Send a signal to the client about finish calculate
	exit(0);
	}

//set handler one more time for next use
	signal(SIGUSR2, signalHandler);
}




int main(int argc,char* argv[]){
	int pid;
	int status;
	if(access("to_srv.txt", F_OK)==0){ //F_OK test for file existance
		if(pid=fork()==0){ 
		   execl("/bin/rm","rm","to_srv.txt",NULL); 
		   }
		waitpid(pid,&status,NULL);//wait for delete to end
		}
		
	 while(1){ //keep wating for signals
		   signal(SIGUSR2,signalHandler); //goto signalHandler when SIGUSR2 arrived
		   pause();
		   }
	 exit(0);
}
