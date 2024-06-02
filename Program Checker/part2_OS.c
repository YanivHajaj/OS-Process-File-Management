// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// OS_1_2.c
// 08/12/2022
// yaniv hajaj  
// Description: OS part two
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <stdio.h> 
#include <sys/fcntl.h>
#include <errno.h> 
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 

/*part 111 */
/*first path:/u/e2020/hajajya/Desktop/OS/1.txt */
/*first path:/u/e2020/hajajya/Desktop/OS/2.txt */

/*cd Desktop/OS */
/*gcc ex2.c -o ex2.out (compiling)*/
/*./ex2.out /u/e2020/hajajya/Desktop/OS/confFile.txt (run program)*/
/*./comp.out /u/e2020/hajajya/Desktop/OS/1.txt /u/e2020/hajajya/Desktop/OS/2.txt */

/*part 222 */
/*ArrLines[0] path:/u/e2020/hajajya/Desktop/OS/allStudents */
/*ArrLines[1] path:/u/e2020/hajajya/Desktop/OS/input.txt */
/*ArrLines[1] file path:/u/e2020/hajajya/Desktop/OS/output.txt */
/*users file path:/u/e2020/hajajya/Desktop/OS/confFile.txt */

/* 
// **************************** compile ****************************
i assumed that main.exe exist in all dictionary because you said 
in the video to do so :)
so i didnt compile all student file by myself 

			char origin_compilation_path[51];
			char dest_compilation_path[51];
			strcpy(origin_compilation_path, ArrLines[0]); //copy the path
			strcat(origin_compilation_path, dirInformation->d_name);//name of dic
			strcat(compilation_path, "/main.c");
			
			strcpy(dest_compilation_path, ArrLines[0]); //copy the path
			strcat(dest_compilation_path, dirInformation->d_name);//name of dic
			strcat(compilation_path, "/main.exe");
			char *args[] = {"gcc", origin_compilation_path,"-o",dest_compilation_path, NULL };
			int compile_res=execvp("gcc", args);
			if(compile_res=!0)
				//give him 0 grade
// **************************** compile ****************************	
	*/	

//;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//I used the first part of the exercise as function in ex2 
int compare(char * path1, char* path2)
{
	char *path_1 =path1;
	char *path_2 =path2;
	char ch1[1];
	char ch2[1];
	
	int fdin1=open(path_1,O_RDONLY);
	if (fdin1 < 0){ /* means file open did not take place */
		write(2,"wrong path number one\n",23); /* wrong path*/
		return -1; /* return 1 not the same files*/
	}
	int fdin2=open(path_2,O_RDONLY);
	if (fdin2 < 0){ /* means file open did not take place */
		write(2,"wrong path number two\n",23); /* wrong path*/
		close(fdin1);
		return -1; /* return 1 not the same files*/
	}
	
	int file_1_size;
	int file_2_size;
	do{
		
		file_1_size = read(fdin1,ch1,1); /*-1=error 0=end file 1=single char was read*/
		file_2_size = read(fdin2,ch2,1); /*-1=error 0=end file 1=single char was read*/
		if(file_1_size<0 || file_2_size<0){  //* error canot read from file 1 or 2*/
			close(fdin1);
			close(fdin2);
            write(2,"canot read the from one of the files file\n",22); 
            return 1;
        }
        //* read 1 char*/
		//printf("file 1 size:%d\n",file_1_size); 
		//printf("file 1 char:%c\n",ch1[0]);
		/* read 2 char*/ 
		//printf("file 2 size:%d\n",file_2_size);
		//printf("file 2 char:%c\n",ch2[0]); 
		if(ch1[0]!=ch2[0]){
			close(fdin1);
			close(fdin2);
			write(2,"files dont match ! \n",21); /*char dont match*/
			return 1; /* return 1 not the same files*/	
		}
		if(file_1_size==0 || file_2_size==0){
			break;	
		}
	}while(ch1[0]==ch2[0]);
	close(fdin1);
	close(fdin2);
	write(2,"files ok !!\n",13); /*char dont match*/
	return 2; /* return 2 same files*/		
}
//;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
//;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//open file and give premmision
int openfile(char *path, int permission)
{
    int fdin = open(path, permission ,0666);/* create the file with write and read permissions from tirgul 1
    if (fdin < 0)  // means file open did not take place 
    {
        char error[] = "path error: ";
        write(2, error, strlen(error));
		printf("\n");
        exit(-1); // error open file 
    }
    return fdin;
}
//;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

//;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//read from file and save data in buffer
int readFile(int fd, char* buffer, int size)
{
    int readsize = read(fd, buffer, size);
    if (readsize < 0)
    {
        write(2, "error while read file\n", 23);
        close(fd);
        exit(-1);
    }
    return readsize;
}
//;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int main(int argc,char* argv[]) /* argc= num of args, argv= list of args*/
{
	
	int confFileFD = open(argv[1], O_RDONLY); /*open and save conf file dile descriptor*/
	if (confFileFD < 0){ /* means file open did not take place */
		write(2,"wrong path of conf file\n",27); /* wrong path*/
		return 1; /* return 1 not the same files*/
	}
	//char *dir;  /*asumming line wont exeed 50 char*/
	//char *in;   /*asumming line wont exeed 50 char*/
	//char *out;  /*asumming line wont exeed 50 char*/


//********** save line 1/2/3 from ConfFile **********
	char allConfFile[151];  /*asumming line wont exeed 50 char*/
	int confActualSize = readFile(confFileFD, allConfFile, 151);
	close(confFileFD);
	allConfFile[confActualSize] = '\0'; //end of the string
	
	/* check buffer
	printf("buffer array\n");
	write(2, allConfFile, strlen(allConfFile));
	*/

	int i=0; //all data var indicator
	int row=0; //line var
	int col=0; //colomn var
	char ArrLines[3][51];
    for (i = 0; i < 151; i++)  /*asumming one line wont exeed 50 char*/
    {
        if (allConfFile[i] != '\n')
        {
            ArrLines[row][col] = allConfFile[i];
            col++;
        }
        else
        {
            ArrLines[row][col] = '\0'; //end of the string
            //if (row==2)
            if (allConfFile[i]=='\0')
			{
				break;
			}
            row++;
            col = 0;
        }
    }
	/*
	printf("each line:\n");
	write(2, ArrLines[0], strlen(ArrLines[0])); //dir
	printf("\n");
	write(2, ArrLines[1], strlen(ArrLines[1])); //input
	printf("\n");
	write(2, ArrLines[2], strlen(ArrLines[2])); //output
	printf("\n");
	*/
	
//********** save line 1/2/3 from ConfFile **********
	
	


	DIR *dir; /*init pointer of dir*/ 
    struct dirent *dirInformation; //allStudents is a struct dirent * variable
	dir = opendir(ArrLines[0]); //open dir
	pid_t Spid; //pid of the son (will call it afterward)
	dirInformation = readdir(dir);//collect first info about allStudents (.)
	dirInformation = readdir(dir);//collect first info about allStudents (..) after this i get info of folders
	
	//char comp_path[10]="./comp.out";
	//char main_path[51];
	char outputPath[51]="";
	strcat(outputPath, "./RealOutput.txt");
	char score[51] = "";
	int status;
	int RealOutputFD;
	
	
	while ((dirInformation = readdir(dir)) != NULL){
	    /*creating path to execlp*/
	   char main_path[51]="";
	    printf("folder name:%s\n",dirInformation->d_name);
        strcpy(main_path, ArrLines[0]); //copy the path
        //strcat(main_path, "/");
        strcat(main_path, dirInformation->d_name);//add student name
        strcat(main_path, "/main.exe"); //add the exe file end (assuming already exist in the folder)
		printf("main path:%s\n",main_path);
		int RealOutputFD =open("RealOutput.txt",O_WRONLY|O_CREAT|O_TRUNC ,0666 );
		if (RealOutputFD < 0){ /* means file open did not take place */
			write(2,"error,RealOutput file cannot create\n",37); /* wrong path*/
			return 1; 
		}
        int inputFD=open(ArrLines[1],O_RDONLY ,0666);
		if (inputFD < 0){ /* means file open did not take place */
			write(2,"error,the input file cannot open\n",34); /* wrong path*/
			close(RealOutputFD);
			return 1; 
		}
		
		if ( (Spid = fork()) < 0){ //fork patent Spid=son's pid
			printf("fork error"); //error
		}	
		else{
			if (Spid == 0){
			 /* child */
			 
				//printf("inside child\n");
				dup2(inputFD,0); //make inputfile default (keyboard)
				dup2(RealOutputFD,1); //make outputfile default (screen)
				char *args[] = {main_path, NULL };
				execv(main_path, args);//run main an
				//execl(main_path,main_path,NULL);	
				
			}	
			else{
			/* parent */
				//printf("parent before wait\n");
				wait(&status);;//wait for son to end   
				//printf("parent after wait\n");
				close(inputFD);
				close(RealOutputFD);
				int gradesFD=open("results.csv",O_RDWR|O_CREAT|O_APPEND, 0666);
				//int expectedOutputFD=open(ArrLines[2],O_RDONLY);
                char name[51];/*asumming line wont exeed 50 char*/
                strcpy(name, dirInformation->d_name);             
                
                //int grade =  execl(comp_path,comp_path, "./RealOutput.txt",ArrLines[2],NULL);
                //char *args1[] = {comp_path,"./RealOutput.txt",ArrLines[2], NULL };
				//int grade = execv(comp_path, args1);
				int grade = compare(ArrLines[2],outputPath);
				if (grade ==-1){ /* means file open did not take place */
					write(2,"error,cannot compare 2 files\n",30); /* wrong path*/
					exit(-1); 
				}
				//printf("the grade is:%d\n",grade);
				if (grade == 2){strcpy(score, ",100\n"); }
				else {strcpy(score, ",0\n"); }
                strcat(dirInformation->d_name, score);
                write(gradesFD, dirInformation->d_name, strlen(dirInformation->d_name));
                printf("grade is:%d\n",grade);
                write(2, dirInformation->d_name, strlen(dirInformation->d_name)); //output
				printf("\n");
				close(gradesFD);
				//close(expectedOutputFD);
			}
		}
			
	}

	//close all open files//
	//already closed confFileFD
	
	//close all open files//
	exit(2)
}







