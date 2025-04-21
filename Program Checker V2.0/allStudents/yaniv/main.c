#include <stdio.h> 
#include <sys/fcntl.h>
#include <errno.h> 
#include <stdlib.h>

/*first path:/u/e2020/hajajya/Desktop/OS/1.txt */
/*first path:/u/e2020/hajajya/Desktop/OS/2.txt */
/*gcc main.c -o main.out (compiling)*/

/*part 222 */
/*users file path:/u/e2020/hajajya/Desktop/OS/users */
/*users file path:/u/e2020/hajajya/Desktop/OS/input.txt */
/*users file path:/u/e2020/hajajya/Desktop/OS/output.txt */
	
int main(int argc,char* argv[]) /* argc= num of args, argv= list of args*/
{
    
    printf("Please enter mode\n");
    int mode;
    scanf("%d", &mode);
    int num1, num2;
    printf("Please enter two numbers\n");
    scanf("%d %d", &num1, &num2);
    int result;
    {
    if (mode==1)
        result = num1 + num2;
    else
        result = num1 - num2;
    }
    printf("The result is:%d", result);
    exit(0);
}


