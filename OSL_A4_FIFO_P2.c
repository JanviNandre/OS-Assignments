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
    char buf[100], buf1[100];
    int fd, fd1; 
    int words=0, lines=0, characters=0;
    int len, i, count=0;
    char ch;
    FILE *fp;

    fd = open(FIFO1, O_RDONLY);
    memset(buf, '\0', sizeof(buf));
    read(fd,buf,sizeof(buf));
    printf("Message received");
    //printf("%s",buf);
    close(fd);

    while(buf[i]!='\0'){
        if(buf[i]==' '||buf[i]=='\n'){
            words++;
        }
        else{
            characters++;
        }
        if(buf[i]=='\n'){
                lines++;
        }
        i++;
           
    }
    lines = lines+1;
    words = words+1;
    printf("\nCount :- words:%d lines:%d characters:%d", words,lines, characters);

    fp=fopen("fifo.txt","w+");
	fprintf(fp,"\nCharacters : %d",characters);
	fprintf(fp,"\nWords : %d",words);
	fprintf(fp,"\nLines : %d",lines);
	fclose(fp);
	
	fp=fopen("fifo.txt","r");
	i=0;
	while((ch=fgetc(fp))!=EOF)
	{
		buf1[i]=ch;
		i++;
	}
	printf("\nContents of Buffer are : ");
	printf("\n%s",buf1);
	fclose(fp);
	
	mkfifo(FIFO2,0666);
	fd1=open(FIFO2,O_WRONLY);
    memset(buf1, '\0', sizeof(buf1));
	write(fd1,buf1,sizeof(buf1));
	
	printf("\nMessage sent\n");
	close(fd1);
	return 0;
}

/*
Output: 

$ gcc fifop2.c -o fifop2.out
$ ./fifop2.out
Message received
Count :- words:2 lines:1 characters:10

Contents of Buffer are : 
Characters : 10
Words : 2
Lines : 1
Message sent
*/