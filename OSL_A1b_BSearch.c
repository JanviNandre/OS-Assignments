#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>


int binarySearch(int arr[], int low, int high, int val) {
	while(low <= high) {
		int mid = low + (high - low) / 2;
		
		if(arr[mid] == val) {
			return mid;
		}
		else if(arr[mid] < val) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return -1;
}


int main(int argc, char *argv[]) {   

    printf("\nThis is Child process ID is %d ", getpid());
    printf("\nMy parent process ID is %d ", getppid());

	int len, arr[argc-1], value, result;
    int low, high;
	len=argc-1;
    
	printf("\nValue of argc is : %d", argc);
	printf("\n");
	for(int i = 0; i < len; i++) {
		arr[i] = atoi(argv[i + 1]);     
	}
	
	printf("\nArray Elements : ");
	for(int i = 0; i < len; i++) {
		printf("%d ,", arr[i]);
	}
	
	printf("\nEnter value to search : ");
	scanf("%d", &value);
	low = 0;
    high = len;
	result = binarySearch(arr, low, high, value);
	
	if(result == -1) {
		printf("\nValue not found");
	}
	else {
		printf("\nMatch found at index position %d", result);
	}
}