/*
FIFOs: Full duplex communication between two independent processes. First process accepts sentences and writes on one pipe to be read by second process and second process counts number of characters, number of words and number of lines in accepted sentences, writes this output in a text file and writes the contents of the file on second pipe to be read by first process and displays on standard output.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main(){
    char buf[100], buf1[100], str;
    int fd, fd1, i=0;                  //discriptor
    // char * fifo1 = "fifo1";
    // char * fifo2 = "fifo2";
    printf("\nEnter a string : ");
    while((str=getchar())!='#')
    buf[i++] = str;
    puts(buf);

    // int flag = mkfifo("fifo1", 0666);             
    // printf("flag:%d", flag);

    mkfifo("fifo1", 0666);  
    fd = open(FIFO1, O_WRONLY);        //write mode
    write(fd, buf, sizeof(buf));       //store in fd
    printf("\nMessage sent");          
    close(fd);

    fd1 = open(FIFO2,O_RDONLY);
    read(fd1,buf1,sizeof(buf1));
    memset(buf1, '\0', sizeof(buf1));
    printf("\nMessage Recieved");  
    printf("\nThe contents of file are : %s\n",buf1);        
    close(fd1);

}

/*
Output : 
$ gcc fifop1.c -o fifop1.out
$ ./fifop1.out

Enter a string : hello world#
hello world

Message sent
Message Recieved
The contents of file are : 
Characters : 10
Words : 2
Lines : 1

*/