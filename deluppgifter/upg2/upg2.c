#include <stdio.h> 
#include <string.h>

int main(int argc, char* argv[]) 
{


    int totalLength = 0; 
    for(int i = 0; i < argc; i++)
    {
	totalLength += strlen(argv[i]); 
	printf("%-20s%5ld\n", argv[i], strlen(argv[i]));
    }

    printf("%-20s%5d\n%-20s%5.2f\n","Total length", totalLength, "Average length", (float)totalLength/argc); 

    return totalLength;
} 
