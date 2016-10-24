#include <stdio.h>

// Function that returns character based on the index value
char getTileType(unsigned int index)
{
	char result;  // Variable that will hold character value that to be returned
	if(index == 0)
	{
		result = 'C';
	}
	else if (index % 7 == 0)
	{
		result = 'G';
	}
	else if (index % 5 == 0)
	{
		result = 'L';
	}
	else if (index % 3 == 0)
	{
		result = 'W';
	}
	else
	{
		result = ' ';
	}
	return result;  //Return result
}



// Function that will print the Board game on the screen
void displayBoard(unsigned int size)
{
	int i,k;
	int low = size;	// last value of index after printing 1st row. means after printing 1st line of boxes.
	int high = size*4 - 5;	// Highest value of index in board like board size of 4 => 0 to 11 so 11 is the highest. 
	int input;   // just the input parameter for getTileType funtion
	int hh = high - (size-2);	// The starting index of last row.
	int ll = size + (size-2);	// The last index of last row.
	for(k=0;k<size;k++)		// 1st iteration or parent to iterate "size" times..
	{
		if(k==0 || k == size-1)	// First row of baord printing or last row printing
		{
			if(k==0)	// If its 1st row and change the index to 0
			{
				input = 0;	
			}
			else		// else if its last and change the index to staring index of last row
			{
				input = hh;
			}
			for(i=0;i<size;i++)
			{						// print the Top stuff
				printf(" ___ ");
			}
			printf("\n");	// newline
			for(i=0;i<size;i++)		// print the Middle stuff
			{
				printf("| %c |",getTileType(input));	// calling funtion to get tile type.
				if(k==0)
				{
					input++;
				}
				else
				{
					input--;
				}
			}
			printf("\n");		// newline
			for(i=0;i<size;i++)
			{					// Print the bottom stuff
				printf("|___|");
			}				
			printf("\n");
		}
		else		// else if the row is not 1st and not the last ..means any row in btw 1st and last.
		{
			for(i=0;i<size;i++)		//printing the TOP stuff here..
			{
				if(i==0||i==size-1)		// check if its the 1st column of the row or the last
				{
					printf(" ___ ");
				}
				else			// else if the column is in btw 1st and last of this row.
				{
					printf("     ");
				}
			}
			printf("\n");	//newline
			for(i=0;i<size;i++)		// printing MIDDLE stuff here..
			{
				if(i==0||i==size-1)		// check if its the 1st column of the row or the last
				{
					if(i==0)
					{
						printf("| %c |",getTileType(high));
						high--;
					}
					else		// else if the column is in btw 1st and last of this row.
					{
						printf("| %c |",getTileType(low));
						low++;
					}
				}
				else
				{
					printf("     ");
				}
			}
			printf("\n");
			for(i=0;i<size;i++)			// printing Bottom stuff here..
			{
				if(i==0||i==size-1)		// check if its the 1st column of the row or the last
				{
					printf("|___|");
				}
				else		// else if the column is in btw 1st and last of this row.
				{
					printf("     ");
				}
			}
			printf("\n");	//final newline :)
		}
	}
	
}

// Main funtion already given by You..
int main()
{
	int s = 1;
	if(getTileType(153) != 'W') printf("153 should return W");
	else if (getTileType(65) != 'L') printf("65 should return L");
	else if (getTileType(49) != 'G') printf("49 should return G");
	else if (getTileType(0) != 'C') printf("0 should return C");
	else if (getTileType(105) != 'G') printf("105 should be G");
	else if (getTileType(79) != ' ') printf("79 should be space");
	else
	{
		printf("getTileType test passed!\nEnter board size: ");
		scanf("%d", &s);
		displayBoard(s);
	}
}
