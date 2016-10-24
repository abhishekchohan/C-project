#include <stdio.h>
#include <string.h>
#include <time.h>

// Funtions Declarations here....
int getValidInteger(int low, int high);
char getValidCharacter(char low, char high);
void initPlayer(int* playerScore, int playerPrizes[], unsigned int *prizeCount, char * playerName, int* playerPosition);
void playGame(unsigned int boardSize, int *playerScore, int playerPrizes[],unsigned int* prizeCount, char * playerName, int* playerPosition);
char getDisplayTile (unsigned int index, unsigned int playerPosition, char  playerName);
void displayBoard(unsigned int size, unsigned int playerPosition, char playerName);
int getRandom(int low, int high);
unsigned int playerRoll();
void winPrize(int playerPrizes[], unsigned int* prizeCount);
void winGrandPrize(int playerPrizes[], unsigned int* prizeCount);
void loseItem(int playerPrizes[], unsigned int* prizeCount);
int checkout(int* playerScore, int playerPrizes[], unsigned int* prizeCount);


// Main Funtion Definiton here..
int main()
{
	int playerScore, highscore = 100, prizeCount,playerPrizes[10], num_players;
	unsigned int playerPosition, size;
	char playerName = ' ', highscoreplayername = ' ', choice;
	printf("Welcome to CHECKOUT\n");
	//looping for Game Menu..
    do
    {
        printf("Main Menu\n\n");
        printf("p-(p)lay q-(q)uit r-inst(r)uctions s-HI(s)core:\n");
        choice = getValidCharacter('o','t');
		// options conditions..
		if(choice == 'p')
		{
		    printf("number of players is ");
			num_players = getValidInteger(0,9);
			while(getchar()!='\n');
			initPlayer(&playerScore,playerPrizes, &prizeCount, &playerName, &playerPosition);
			printf("Enter board size: ");
			size = getValidInteger(4,16);
			playGame(size,&playerScore,playerPrizes,&prizeCount,&playerName,&playerPosition);
			if(playerScore > highscore)
            {
                highscore = playerScore;
                highscoreplayername = playerName;
            }
		}
		else if(choice == 'r')
        {
            printf("\n1. Up to 8 players compete to be the first to obtain $1000 \n2. Game takes place on a square board with 5 tile types\n\to Empty Tile - No effect\n\to Win Tile - Win a random prize\n\to Lose Tile - Lose a random prize\n\to Grand Prize Tile - Win a grand prize\n\to Checkout Tile - Sells all your prizeCount for cash\n3. Players can roll 1 - 3 dice to determine how many tiles they move each turn\n4. If a player lands on the same tile as another player, that player steals a prize and moves 1 tile back.\n\n");
        }
        else if(choice == 's')
        {
            printf("__\n  \\_______\n   \\++++++|\n    \\=====|\n    0---  0\n\n");
            printf("HI SCORE: %d Player Name: %c\n",highscore,highscoreplayername);
        }
    }
    while(choice!='q');
	// Finished here...
    printf("This game is much more fun than bash...\n");
    return 0;
}

// Integer validation..
int getValidInteger(int low, int high)
{
    int num, valid;
    do
    {
        valid = scanf("%d", &num);
        if(valid == 0)	// extra validation for garbage or bad characters
        {
            printf("Invalid input, try again: ");
            while (getchar() != '\n');
        }
        else if(!(num < high && num > low))
        {
            printf("Invalid input, try again: ");
        }
    }
	while(!(num < high && num > low));
    return num;
}

// Character Validations..
char getValidCharacter(char low, char high)
{
    char num;
    do
    {
        scanf(" %c",&num);
        while('\n'!=getchar());
        if(!(num < high && num > low))
        {
            printf("Invalid input, try again: ");
        }
    }
	while(!(num < high && num > low));
    return num;
}

// Initialize all stuff here..
void initPlayer(int* playerScore, int playerPrizes[], unsigned int *prizeCount, char * playerName, int* playerPosition)
{
    int n = 0;
    *playerScore = 0;
    while(n<10){playerPrizes[n];n++;};
    *prizeCount = 0;
    *playerPosition = 0;
    printf("Enter player ID: ");
    *playerName = getchar();
    while('\n'!=getchar());
}

// Real fun inside here... aka game stuff here..
void playGame(unsigned int boardSize, int *playerScore, int playerPrizes[],unsigned int* prizeCount, char * playerName, int* playerPosition)
{
    unsigned int roll,rollval[3] = {0,0,0},i;
    int quit;
    do
    {
		//intialize rolled value array..
        rollval[0] = 0,rollval[1] = 0,rollval[2] = 0;
        displayBoard(boardSize,*playerPosition,*playerName);
        printf("playerScore: %d playerPrizes (%d items): ",*playerScore,*prizeCount);
        for(i=0;i<*prizeCount;i++)
            printf("%d,",playerPrizes[i]);
        printf("\n");
        roll = playerRoll();
        srand(time(NULL));
        for(i=0;i<roll;i++)
            rollval[i] = 1 + rand() % (6);
        if(roll == 1)
        {
            printf("You rolled: %d \n",rollval[0]);
            printf("Advancing %d spaces\n",rollval[0]);
        }
        if(roll == 2)
        {
            printf("You rolled: %d %d \n",rollval[0],rollval[1]);
            printf("Advancing %d spaces\n",rollval[0]+rollval[1]);
        }
        if(roll == 3)
        {
            printf("You rolled: %d %d %d\n",rollval[0],rollval[1],rollval[2]);
            printf("Advancing %d spaces\n",rollval[0]+rollval[1]+rollval[2]);
        }
        *playerPosition = *playerPosition + rollval[0]+rollval[1]+rollval[2];
        if(*playerPosition > (((boardSize * 4) - 4) - 1) )
        {
            *playerPosition = *playerPosition % (((boardSize * 4) - 4) - 1);
            *playerPosition = *playerPosition - 1;
        }
        if(*playerPosition == 0)
        {
            quit = checkout(playerScore,playerPrizes,prizeCount);
        }
        else if(*playerPosition % 7 == 0)
        {
            winGrandPrize(playerPrizes,prizeCount);
        }
        else if (*playerPosition % 5 == 0)
        {
            loseItem(playerPrizes,prizeCount);
        }
        else if (*playerPosition % 3 == 0)
        {
            winPrize(playerPrizes,prizeCount);
        }
        else
        {
            printf("nothing happens, go again.\n");
        }
    }
    while(!(quit==1 || quit==0));
}

// Function that returns character based on the index value
char getDisplayTile (unsigned int index, unsigned int playerPosition, char  playerName )
{
    unsigned int y = index;  // Variable that will hold character value that to be returned
	if(y == 0)
	{
	    if(index == playerPosition)
        {
            return playerName;
        }
        else
        {
            return 'C';
        }
	}
	else
	{
		if (y % 7 == 0)
		{
			if(index == playerPosition)
            {
                return playerName;
            }
            else
            {
                return 'G';
            }
		}
		if (y % 5 == 0)
		{
			if(index == playerPosition)
            {
                return playerName;
            }
            else
            {
                return 'L';
            }
		}
		if (y % 3 == 0)
		{
			if(index == playerPosition)
            {
                return playerName;
            }
            else
            {
                return 'W';
            }
		}
		else
		{
		    if(index == playerPosition)
            {
                return playerName;
            }
            else
            {
                return ' ';
            }
		}
	}
}

// Function that will print the Board game on the screen
void displayBoard(unsigned int size, unsigned int playerPosition, char playerName)
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
				printf("| %c |",getDisplayTile(input,playerPosition,playerName));	// calling funtion to get tile type.
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
						printf("| %c |",getDisplayTile(high,playerPosition,playerName));
						high--;
					}
					else		// else if the column is in btw 1st and last of this row.
					{
						printf("| %c |",getDisplayTile(low,playerPosition,playerName));
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

// Random number generators...
int getRandom(int low, int high)
{
    srand(time(NULL));
    return  low + rand() % high;
}

// Rolling Dice...
unsigned int playerRoll()
{
    printf("your turn, how many dice will you roll? ");
    return getValidInteger(0,4);
}

// Win Prize ...
void winPrize(int playerPrizes[], unsigned int* prizeCount)
{
    int value;
    value = getRandom(10,100);
    if(*prizeCount < 10)
    {
        playerPrizes[*prizeCount] = value;
        *prizeCount = *prizeCount + 1;
        printf("you won a prize of %d.\n",value);
    }
    else
    {
        printf("Player Inventory is full.\n");
    }

}

// Win Grand Prize here..
void winGrandPrize(int playerPrizes[], unsigned int* prizeCount)
{
    int value;
    value = getRandom(100,200);
    if(*prizeCount < 10)
    {
        playerPrizes[*prizeCount] = value;
        *prizeCount = *prizeCount + 1;
        printf("you won a prize of %d\n",value);
    }
    else
    {
        printf("Player Inventory is full\n");
    }
}

// Lose one item randomly from inventory here..
void loseItem(int playerPrizes[], unsigned int* prizeCount)
{
    int index,i;
    if(*prizeCount > 0)
    {
        for(index = getRandom(1,*prizeCount) - 1;index < *prizeCount-1;index++ )
        {
            playerPrizes[index] = playerPrizes[index+1];
        }
        playerPrizes[index] = 0;
        *prizeCount = *prizeCount - 1;
    }
}

// Game finised here.. so doing check out..
int checkout(int* playerScore, int playerPrizes[], unsigned int* prizeCount)
{
    int value=0,i;
    for(i=0;i<*prizeCount;i++)
        value = value + playerPrizes[i];
    printf("Prize total = %d \n",value);
    printf("You checkedout for $%d.00 playerScore is now: $%d.00\n",value,value);
    *prizeCount = 0;
    *playerScore = value;
	// check whether score is 200 or not..
    if(value>=200)
    {
		printf("You won the game!\n");
        return 1;
    }
    else
    {
        printf("You lose the game!\n");
        return 0;
    }
}

// All functions completed and MS2 is done here...at last... :(
