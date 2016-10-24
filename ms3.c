#include <stdio.h>
#include <string.h>
#include <time.h>
#define THRESHOLD 500

struct Player
 {
         char playerName;
         int playerScore;
         int prizeCount;
         int playerPosition;
         int playerPrizes[10];
 };

void displayBoard(unsigned int size, struct Player players[], unsigned int playerCount);
char getTileType(unsigned int index, struct Player players[], unsigned int playerCount);
void initPlayer(struct Player* player);
void playGame(unsigned int boardSize, struct Player players[], unsigned int playerCount);
int getValidInteger(int low, int high);
char getValidCharacter(char low, char high);
unsigned int playerRoll();
void winPrize(struct Player* player);
void winGrandPrize(struct Player* player);
int loseItem(struct Player* player);
int checkout(struct Player* player);
void checksteal(struct Player players[],int i, int boardSize,int playerCount);


int main()
{
	int score, hscore = 100, prizes,inventory[10], num_players,i;
	unsigned int position, size;
	char name = ' ', hname = ' ', option;
	printf("Welcome to CHECKOUT\n");
    do
    {
        printf("Main Menu\n\n");
        printf("p-(p)lay q-(q)uit r-inst(r)uctions s-HI(s)core:\n");
        option = getValidCharacter('o','t');
		if(option == 'p')
		{
		    printf("number of players is ");
			num_players = getValidInteger(0,9);
			while(getchar()!='\n');
			struct Player players[num_players];
			for(i=0;i<num_players;i++)
            {
                initPlayer(&players[i]);
            }
			printf("Enter board size: ");
			size = getValidInteger(4,16);
			playGame(size,players,num_players);
			if(score > hscore)
            {
                hscore = score;
                hname = name;
            }
		}
		else if(option == 'r')
        {
            printf("\n1. Up to 8 players compete to be the first to obtain $1000 \n2. Game takes place on a square board with 5 tile types\n\to Empty Tile - No effect\n\to Win Tile - Win a random prize\n\to Lose Tile - Lose a random prize\n\to Grand Prize Tile - Win a grand prize\n\to Checkout Tile - Sells all your prizes for cash\n3. Players can roll 1 - 3 dice to determine how many tiles they move each turn\n4. If a player lands on the same tile as another player, that player steals a prize and moves 1 tile back.\n\n");
        }
        else if(option == 's')
        {
            printf("__\n  \\_______\n   \\++++++|\n    \\=====|\n    0---  0\n\n");
            printf("HI SCORE: %d Player Name: %c\n",hscore,hname);
        }
    }
    while(option!='q');
    printf("This game is much more fun than bash...\n");
    return 0;
}


char getTileType(unsigned int index, struct Player players[], unsigned int playerCount)
{
	char playerName;
	int playerPosition,i;
	for(i=0;i<playerCount;i++)
	{
		if(players[i].playerPosition == index)
		{
			playerName = players[i].playerName;
			playerPosition = players[i].playerPosition;
			break;
		}
	}
	if(index == 0)
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
		if (index % 7 == 0)
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
		if (index % 5 == 0)
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
		if (index % 3 == 0)
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

void displayBoard(unsigned int size, struct Player players[], unsigned int playerCount)
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
				printf("| %c |",getTileType(input,players,playerCount));	// calling funtion to get tile type.
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
						printf("| %c |",getTileType(high,players,playerCount));
						high--;
					}
					else		// else if the column is in btw 1st and last of this row.
					{
						printf("| %c |",getTileType(low,players,playerCount));
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


int getValidInteger(int low, int high)
{
    int num, valid;
    do
    {
        valid = scanf("%d", &num);
        if(valid == 0)
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

void initPlayer(struct Player *player)
{
    int n = 0;
    (*player).playerScore = 0;
    while(n<10){(*player).playerPrizes[n];n++;};
    (*player).prizeCount = 0;
    (*player).playerPosition = 0;
    printf("Enter player ID: ");
    (*player).playerName = getchar();
    while('\n'!=getchar());
}

void playGame(unsigned int boardSize, struct Player players[], unsigned int playerCount)
{
	unsigned int roll,rollval[3] = {0,0,0},i,j,z,stop,x,score;
    int won = 2, over = 0;
    int out[playerCount];
    int outcount = 0;
    do
    {
        i=0;
        for(i=0;i<playerCount;i++)
        {
            stop = 0;
            for(z=0;z < outcount;z++)
            {
                if(i == out[z])
                {
                    stop = 1;
                }
            }
            if(stop == 0)
            {
                rollval[0] = 0,rollval[1] = 0,rollval[2] = 0;
                displayBoard(boardSize,players,playerCount);
                /*printf("score: %d inventory (%d items): ",players[i].playerScore,players[i].prizeCount);
                for(j=0;j<players[i].prizeCount;j++)
                    printf("%d,",players[i].playerPrizes[j]);*/
                printf("\n");
                printf("%c\'s turn, how many dice will you roll? ",players[i].playerName);
                roll = playerRoll();
                for(j=0;j<roll;j++)
                    rollval[j] = 1 + rand() % (6);
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
                players[i].playerPosition = players[i].playerPosition + rollval[0]+rollval[1]+rollval[2];
                if(players[i].playerPosition > (((boardSize * 4) - 4) - 1) )
                {
                    players[i].playerPosition = players[i].playerPosition % (((boardSize * 4) - 4) - 1);
                    players[i].playerPosition = players[i].playerPosition - 1;
					checksteal(players,i,boardSize,playerCount);
                }
                checksteal(players,i,boardSize,playerCount);
                score = 0;
                for(j=0;j<players[i].prizeCount;j++)
                    score = score + players[i].playerPrizes[j];
                if(players[i].playerPosition == 0 || score >= THRESHOLD )
                {
                    won = checkout(&players[i]);
                    if(won == 0)
                    {
                        out[outcount] = i;
                        outcount = outcount + 1;
                        players[i].playerPosition = -1;
                    }
                }
                else if(players[i].playerPosition % 7 == 0)
                {
                    winGrandPrize(&players[i]);
                }
                else if (players[i].playerPosition % 5 == 0)
                {
                    loseItem(&players[i]);
                    printf("You lost a prize..\n");
                }
                else if (players[i].playerPosition % 3 == 0)
                {
                    winPrize(&players[i]);
                }
                else
                {
                    printf("nothing happens..\n");
                }
            }
            if(won==1)
            {
                break;
            }
        }
    }while(won!=1);
}

void checksteal(struct Player players[],int i, int boardSize,int playerCount)
{
    int x;
    for(x=0;x<playerCount;x++)
    {
        if(players[i].playerPosition == players[x].playerPosition && x != i)
        {
            if(players[i].playerPosition == 0)
            {
                players[i].playerPosition = boardSize*4 - 5;
            }
            else
            {
                players[i].playerPosition = players[i].playerPosition - 1;
            }
            int steal = loseItem(&players[x]);
            if(steal==0)
            {
                printf("You were unable to steal from %c!\n",players[x].playerName);
            }
            else
            {
                printf("You stole a prize from %c!\n",players[x].playerName);
                if(players[i].prizeCount <= 10)
                {
                    players[i].playerPrizes[players[i].prizeCount] = steal;
                    players[i].prizeCount = players[i].prizeCount + 1;
                }
                else
                {
                    printf("Player inventory is full\n");
                }
            }
        }
    }
}

unsigned int playerRoll()
{
    return getValidInteger(0,4);
}

void winPrize(struct Player* player)
{
	int value;
    value = getRandom(10,100);
    if((*player).prizeCount <= 10)
    {
        (*player).playerPrizes[(*player).prizeCount] = value;
        (*player).prizeCount = (*player).prizeCount + 1;
        printf("you won a prize of %d\n",value);
    }
    else
    {
        printf("Player inventory is full\n");
    }
}

void winGrandPrize(struct Player* player)
{
	int value;
    value = getRandom(100,200);
    if((*player).prizeCount <= 10)
    {
        (*player).playerPrizes[(*player).prizeCount] = value;
        (*player).prizeCount = (*player).prizeCount + 1;
        printf("you won a prize of %d\n",value);
    }
    else
    {
        printf("Player inventory is full\n");
    }
}

int loseItem(struct Player* player)
{
	int index,i;
	int lost = 0;
    if((*player).prizeCount > 0)
    {
        index = getRandom(1,(*player).prizeCount) - 1;
        lost = (*player).playerPrizes[index];
        for(;index < (*player).prizeCount-1;index++ )
        {
            (*player).playerPrizes[index] = (*player).playerPrizes[index+1];
        }
        (*player).playerPrizes[index] = 0;
        (*player).prizeCount = (*player).prizeCount - 1;
    }
    return lost;
}

int checkout(struct Player* player)
{
	int value=0,i;
    for(i=0;i<(*player).prizeCount;i++)
        value = value + (*player).playerPrizes[i];
    (*player).prizeCount = 0;
    (*player).playerScore = value;
    if(value>=THRESHOLD)
    {
		printf("Prize total = %d \n",value);
		printf("You checkedout for $%d.00 score is now: $%d.00\n",value,value);
		printf("You won the game!\n");
        return 1;
    }
    else
    {
		printf("You checkedout for $%d.00 !!\n",value);
        return 0;
    }
}

int getRandom(int low, int high)
{
    srand(time(NULL));
    return  low + rand() % high;
}
