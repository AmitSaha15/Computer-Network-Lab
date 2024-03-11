#include<stdio.h>
#include<string.h>

#define MAX 1024

void bitStuffing(char data[], char stuffed[])
{
	int i, j;
	int n = 0;
	
	for(i=0, j=0; i<strlen(data); i++,j++)
	{
	
		stuffed[j] = data[i];
		
		if(data[i] == '1')
		{
			n++;
		}
		
		else
		{
			n = 0;
		}
		
		if(n == 5)
		{
			stuffed[++j] = '0';
			n = 0;
		}
	}
	
	stuffed[j] = '\0';
}


int main()
{
	char data[MAX];
	char stuffed[MAX];

	printf("\nEnter the data: ");
	scanf("%s",data);

	printf("\nBEFORE Bit Stuffing: %s",data);
	
	bitStuffing(data, stuffed);
	
	printf("\nAFTER Bit stuffing : %s", stuffed);
	
	printf("\n");

	return 0;
}