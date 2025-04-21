// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// OS_1_1.c
// 08/12/2022
// yaniv hajaj  
// Description: OS part one
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <stdio.h> 
#include <sys/fcntl.h>
#include <errno.h> 
#include <stdlib.h>
/*part 111 */
/*first path:/u/e2020/hajajya/Desktop/OS/1.txt */
/*first path:/u/e2020/hajajya/Desktop/OS/2.txt */
/*gcc comp.c -o comp.out (compiling)*/
/*./comp.out /u/e2020/hajajya/Desktop/OS/1.txt /u/e2020/hajajya/Desktop/OS/2.txt */

/*part 222 */
/*users file path:/u/e2020/hajajya/Desktop/OS/users */

int main(int argc,char* argv[]) /* argc= num of args, argv= list of args*/
{
	char *path_1 =argv[1];
	char *path_2 =argv[2];
	char ch1[1];
	char ch2[1];
	if(argc!=3){ /* number of argument paths is not 3*/
		write(2,"not enoufe args\n",17); /* number of argument paths is not 3*/
		exit(1); /* return 1 not the same files*/
	}
	int fdin1=open(path_1,O_RDONLY);
	if (fdin1 < 0){ /* means file open did not take place */
		write(2,"wrong path number one\n",23); /* wrong path*/
		exit(1); /* return 1 not the same files*/
	}
	int fdin2=open(path_2,O_RDONLY);
	if (fdin2 < 0){ /* means file open did not take place */
		write(2,"wrong path number two\n",23); /* wrong path*/
		close(fdin1);
		exit(1); /* return 1 not the same files*/
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
            exit(1);
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
			exit(1); /* return 1 not the same files*/	
		}
		if(file_1_size==0 || file_2_size==0){
			break;	
		}
	}while(ch1[0]==ch2[0]);
	close(fdin1);
	close(fdin2);
	write(2,"files ok !!\n",13); /*char dont match*/
	exit(2); /* return 1 not the same files*/		
}

