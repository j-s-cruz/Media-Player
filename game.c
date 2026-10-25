#include "LPC17xx.h"                      /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

#include <stdlib.h>

#include "game.h"	//includes 2D arrays for each level

#include "empty.c"
#include "player.c"
#include "boulder.c"
#include "rock.c"
#include "hole.c"
#include "rock_in.c"

#define __FI        1                      /* Font index 16x24               */
//#define NO_DEMO   	0									 /* Uncomment to use the designed levels */
#define DEMO   			0									 /* Uncomment for demo purposes */

#define ROWS 12
#define COLS 16

#define EMPTY		0	
#define PLAYER	1
#define BOULDER	2		
#define ROCK		3	
#define HOLE		4		
#define ROCK_IN	5

//Game Pictures
unsigned char* gallery[]= {(unsigned char *)&EMPTY_pixel_data, (unsigned char *)&PLAYER_pixel_data, (unsigned char *)&BOULDER_pixel_data, (unsigned char *)&ROCK_pixel_data, 
(unsigned char *)&HOLE_pixel_data, (unsigned char *)&ROCK_IN_pixel_data};

//0=empty, 1=player, 2=boulder, 3=rock, 4=hole, 5=rock_in


int board[ROWS][COLS];	// Define the game board
int playerX = 3, playerY = 4; // Initial player position
int level;	// Initial level

void printBoard() {
		int i =0, j=0;
    for (i = 0; i < COLS; i++) {
        for (j = 0; j < ROWS; j++) {
          GLCD_Bitmap (  i*20,  j*20, 20,  20, gallery[board[j][i]]);  
        }
    }
		#ifdef DEMO
	GLCD_DisplayString(0, 0, __FI, " Demo Purposes Only ");
		#endif
	GLCD_DisplayString(9, 0, __FI, "   Select-->Reset   ");
}

void initBoard() {
	int i=0, j=0;
	    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
          board[i][j] = 0;  
        }
			}
	if (level==0)
			level++;
	if (level==1) {
		#ifdef NO_DEMO
		playerX = 8, playerY = 12;
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLS; j++) {
				board[i][j] = level1[i][j];  
        }
    }
		#endif
		#ifdef DEMO
		playerX = 3, playerY = 4;
		board[3][4]=PLAYER;
		board[3][5]=BOULDER;
		for (i=0;i<COLS;i++) {
			if (i%2==0)
				board[5][i]=ROCK;
		}
		board[3][9]=HOLE;
#endif
	}
	else if (level==2) {
		#ifdef NO_DEMO
		playerX = 5, playerY = 8;
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLS; j++) {
				board[i][j] = level2[i][j];  
        }
    }
		#endif
		#ifdef DEMO
		playerX = 3, playerY = 4;
		board[3][4]=PLAYER;
		board[3][5]=BOULDER;
		board[7][5]=BOULDER;
		for (i=0;i<COLS;i++) {
			if (i%2==0)
				board[5][i]=ROCK;
		}
		board[7][9]=HOLE;
		board[7][12]=HOLE;
		#endif		
	}
	printBoard();
}

int getInput (void) {
		int KBD_but, disp_val=0;
		KBD_but = get_button ();
		for (;;) {	
		switch(KBD_but){
			case KBD_SELECT:
				return disp_val;
			break;
			case KBD_UP:
				if(disp_val > 1) {
					disp_val--;
				} else{
					disp_val = 4;
				}
			break;
			case KBD_DOWN:
				if(disp_val < 4) {
					disp_val++;
				} else {
					disp_val = 1;
				}
			break;
		}
	}
		return 0;
}

void movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;
    int destination = board[newX][newY];
		LED_Off(3);
		LED_Off(4);
		LED_Off(5);	
		LED_Off(6);	
    if (destination == EMPTY) { // Move to an empty space or target
        board[playerX][playerY] = EMPTY;
        playerX = newX;
        playerY = newY;
        board[playerX][playerY] = PLAYER;
				printBoard();
    } 
		else if (destination == BOULDER) { // Push a boulder
        int boulderX = newX + dx;
        int boulderY = newY + dy;
        if (board[boulderX][boulderY] == EMPTY) {
            board[boulderX][boulderY] = BOULDER;
            board[newX][newY] = PLAYER;
            board[playerX][playerY] = EMPTY;
            playerX = newX;
            playerY = newY;
						printBoard();
        }
			  else if (board[boulderX][boulderY] == HOLE) {
            board[boulderX][boulderY] = ROCK_IN;
            board[newX][newY] = PLAYER;
            board[playerX][playerY] = EMPTY;
            playerX = newX;
            playerY = newY;
						printBoard();
        }	
				else if (board[boulderX][boulderY] == ROCK) {
					LED_On(3);
					GLCD_SetTextColor(White);
					GLCD_DisplayString(9, 0, __FI, "  Rock in the way!  ");				
				}
				else if (board[boulderX][boulderY] == BOULDER) {
					LED_On(4);
					GLCD_SetTextColor(White);
					GLCD_DisplayString(9, 0, __FI, "Boulder in the way! ");				
				}
				else if (board[boulderX][boulderY] == ROCK_IN) {
					LED_On(5);
					GLCD_SetTextColor(White);
					GLCD_DisplayString(9, 0, __FI, " Find another hole  ");				
				}
				
			}
		else if (destination == ROCK) {
				LED_On(3);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(9, 0, __FI, "  Rock in the way!  ");
		}	
		else if (destination == HOLE || destination == ROCK_IN) {
				LED_On(6);
				GLCD_SetTextColor(White);
				GLCD_DisplayString(9, 0, __FI, "Watch out for holes!");
		}	
}

int checkWin() {
	int i=0, j=0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (board[i][j] == HOLE || level == 0) {  
							return 0; // Not all targets are covered
            }
        }
    }
		return 1; // All targets are covered
}

int game() {
		int KBD_but;
		level=0;
		// Start game
		GLCD_Clear(Black);
		GLCD_SetBackColor(Black);
		GLCD_SetTextColor(White);
		GLCD_DisplayString(0, 0, __FI, "    Sokoban Game    ");
		GLCD_DisplayString(2, 0, __FI, "Goal: Push all      ");
		GLCD_DisplayString(3, 0, __FI, "boulders into the   ");
		GLCD_DisplayString(4, 0, __FI, "holes               ");
		GLCD_DisplayString(6, 0, __FI, "     Game Start     ");
	for (;;){
		KBD_but = get_button ();
		switch(KBD_but){
			case (KBD_UP):
				movePlayer(-1,0);
				break;
			case (KBD_DOWN):
				movePlayer(1,0);
				break;
			case (KBD_LEFT):
				movePlayer(0,-1);
				break;
			case (KBD_RIGHT):
				movePlayer(0,1);
				break;
			case (KBD_SELECT):
				GLCD_Clear(White);
				initBoard();
				break;
		}
		
		if (checkWin()) {
			if (level > 2) {
				GLCD_DisplayString(5, 0, __FI, "      You win!      ");
				GLCD_DisplayString(9, 0, __FI, "   Up->Main Menu    ");
				switch(KBD_but) {
					case (KBD_UP):
						GLCD_Clear(White);
						LED_Off(2);
						return 0;
				}
			}
			else {
				GLCD_DisplayString(6, 0, __FI, "   W's in the chat  ");
				GLCD_DisplayString(9, 0, __FI, "   Up->Next Level   ");
				switch(KBD_but) {
					case (KBD_UP):
						level++;
						initBoard();
					break;
				}
			}
		}		
	}
}


