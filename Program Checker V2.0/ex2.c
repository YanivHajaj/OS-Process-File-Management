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
#include <unistd.h>     // fork, write, read, close, dup2, execv
#include <sys/wait.h>   // wait

/*part 111 */
/*first path: /home/yaniv/Desktop/OS/Checker/1.txt */
/*first path: /home/yaniv/Desktop/OS/Checker/2.txt */

/*cd Desktop/OS */
/*./comp.out /u/e2020/hajajya/Desktop/OS/1.txt /u/e2020/hajajya/Desktop/OS/2.txt */

/*part 222 */

/*gcc -g ex2.c -o ex2.out (compiling)*/
/*./ex2.out /home/yaniv/Desktop/OS/Checker/confFile.txt (run program)*/

// ArrLines[0] /home/yaniv/Desktop/OS/Checker/allStudents/
// ArrLines[1] /home/yaniv/Desktop/OS/Checker/input.txt
// ArrLines[1] /home/yaniv/Desktop/OS/Checker/output.txt */
/*users file path: /home/yaniv/Desktop/OS/Checker/confFile.txt */

//debuggin
// gdb ./ex2.out
// set args /home/yaniv/Desktop/OS/Checker/confFile.txt
// set follow-fork-mode child
// break main
// layout src
// run   

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

// This function prints the contents of a file to the console.
// It receives the filename as input.
void printFile(const char *filename) {
    // Open the file in read-only mode
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        // Print error if the file cannot be opened
        perror("Failed to open file");
        return;
    }

    char buf[1025]; // Buffer to store the file content
    int sz = read(fd, buf, 1024); // Read up to 1024 bytes
    if (sz < 0) {
        // Print error if reading fails
        perror("Failed to read file");
        close(fd);
        return;
    }

    buf[sz] = '\0';  // Null-terminate the string so it can be safely printed
    printf("\n--- %s ---\n%s\n", filename, buf); // Print the filename and its content
    close(fd); // Close the file
}

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
		/* read 2 char*/ 
		//printf("file 2 size:%d\n",file_2_size);
		printf("file 1 char:'%c' (ascii %d) | file 2 char:'%c' (ascii %d)\n", ch1[0], ch1[0], ch2[0], ch2[0]);

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
		write(2, "wrong path of conf file\n", strlen("wrong path of conf file\n"));
		return 1; /* return 1 not the same files*/
	}
	//char *dir;  /*asumming line wont exeed 50 char*/
	//char *in;   /*asumming line wont exeed 50 char*/
	//char *out;  /*asumming line wont exeed 50 char*/
/* 	int testResult = compare("output.txt", "output.txt");
		if (testResult == 2) {
			printf("✅ compare() test passed: output.txt is equal to itself.\n");
		} else {
			printf("❌ compare() test failed: output.txt not equal to itself.\n");
		} */

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
	if (dir == NULL) {
		perror("opendir failed\n");
		exit(1);
	}
	pid_t Spid; //pid of the son (will call it afterward)

	//char comp_path[10]="./comp.out";
	//char main_path[51];
	char outputPath[51]="";
	strcat(outputPath, "./RealOutput.txt");
	char score[51] = "";
	int status;
	int RealOutputFD;
	int gradesFD = open("results.csv", O_WRONLY | O_CREAT | O_TRUNC, 0666);

	
	while ((dirInformation = readdir(dir)) != NULL){
		////collect first info about allStudents (.) and (..) continue if dot or dot X2
		if (strcmp(dirInformation->d_name, ".") == 0 || strcmp(dirInformation->d_name, "..") == 0)
			continue;
	    /*creating path to execlp*/
	   char main_path[51]="";
	    printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~folder name:%s~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",dirInformation->d_name);
        strcpy(main_path, ArrLines[0]); //copy the path
        //strcat(main_path, "/");
        strcat(main_path, dirInformation->d_name);//add student name
        strcat(main_path, "/main.exe"); //add the exe file end (assuming already exist in the folder)
		
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
				printf("Executing: %s\n", main_path);
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
				
				printFile("RealOutput.txt");
				printf("\n");
				printFile("output.txt");
				printf("\n");
				
                strcat(dirInformation->d_name, score);
                write(gradesFD, dirInformation->d_name, strlen(dirInformation->d_name));
				printf("!!!! The grade of %s is %d !!!!\n", name, atoi(score + 1));
				close(gradesFD);
				//close(expectedOutputFD);
			}
		}
			
	}

	exit(2);
}







