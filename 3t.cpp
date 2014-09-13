/*******************************************************************************
	3t - Tic Tac Toe
	
	Author: Martin Albrecht <martin.albrecht@javacoffee.de>
    Date: January 2009
    Website: http://code.javacofee.de
	
	DESCRIPTION:
	------------
		3t is a simple text-based version of the game Tic Tac Toe.

	LICENSE:
	--------
	This program is free software; you can redistribute it and/or modify it 
	under the terms of the GNU General Public License as published by the 
	Free Software Foundation; either version 2 of the License, or (at your 
	option) any later version.

	This program is distributed in the hope that it will be useful, but 
	WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
	Public License for more details.

	You should have received a copy of the GNU General Public License along 
	with this program; if not, write to the

	Free Software Foundation, Inc.,
	59 Temple Place, Suite 330,
	Boston, MA 02111-1307, USA.
 ******************************************************************************/
#include "3t.h"

// General function to clear the screen
void clrscr() {
	#ifdef _WIN32
		system("cls");
	#elif _DOS
		system("cls");
	#else
		system("clear");
	#endif
}

/** Game class functions **/

// Game::Constructor
Game::Game(int mode) {
	for(int i=0; i<9; i++) {
		Board[i] = 3;
	}
	
	switch(mode) {
		// Exit		
		case MODE_EXIT: 
			exit(0);
			break;
		// Multi-Player mode
		case MODE_MULTI:
			GameMode = 1;
			enemy = NULL;
			break;		
		// Single-Player mode
		case MODE_SINGLE:
			GameMode = 2;
			enemy = new Enemy();
			break;
		// Network game (host)
		case MODE_NET_HOST:
			GameMode = MODE_NET_HOST;
			enemy = NULL;
			break;
		// Network game (client)
		case MODE_NET_CLIENT:			
			GameMode = MODE_NET_CLIENT;
			enemy = NULL;
			break;
		// default: exit
		default:
			GameMode = 0;
			break;
	}

	enemy = NULL;
	Running = false;		
	NextPlayer = 1;
}

// Game::Draw the board
void Game::DrawBoard() {
	char b[] = "\r\n\t%c|%c|%c\r\n\t-+-+-\r\n\t%c|%c|%c\r\n\t-+-+-\r\n\t%c|%c|%c\r\n\r\n";	
	char out[9];	

	for(int i=0; i<9; i++) {		
		switch(Board[i]){			
			case 0:
				out[i] = 'X';
				break;
			case 1:
				out[i] = 'O';
				break;
			case 3:
			default:
				out[i] = ' ';
				break;
		}
	}	
	
	#ifdef _WIN32	
		sprintf_s(Output, b, out[0],out[1],out[2],out[3],out[4],
						   out[5],out[6],out[7],out[8]);
	#else
		sprintf(Output, b, out[0],out[1],out[2],out[3],out[4],
						   out[5],out[6],out[7],out[8]);
	#endif
	clrscr();    	
	printf("%s%s", BANNER, Output);
}

// Game::Next step
void Game::NextStep() {
	char tmp[256];
	int choice;
	
	if( enemy == NULL ) {
		if( (GameMode == 1 || NextPlayer == 1 && GameMode != MODE_NET_CLIENT) || (GameMode == MODE_NET_CLIENT && NextPlayer == 2) ) {
			printf("Player %d (1-9): ", NextPlayer);
			memset(tmp,0,256);
			#ifdef _WIN32
			scanf_s("%s", tmp);
			#else
			scanf("%s", tmp);
			#endif
			choice = atoi(tmp);
			
			if(choice<1 || choice>9 || Board[choice-1] != 3)	
				return;
			
			Board[choice-1] = NextPlayer-1;
		}		
	}
	
	switch(GameMode) {
		case 1:
			if(NextPlayer == 1) {
				NextPlayer = 2;
			} else {
				NextPlayer = 1;
			}
			break;

		case 2:
			if(NextPlayer == 2) {
				printf("Enemy is thinkin'...\n");
				Board[enemy->Analyze(Board)] = 1;
				NextPlayer = 1;
			} else {
				NextPlayer = 2;
			}
			break;

		case MODE_NET_HOST:
			if( NextPlayer == 2 ) {
				printf("Waiting for Player 2...\n");
				recv(this->Server->GetClient(), tmp, 1, 0);
				Board[atoi(tmp)-1] = 1;
				NextPlayer = 1;
			} else {
				send(this->Server->GetClient(), Board, 9,0);
				NextPlayer = 2;
			}
			break;

		case MODE_NET_CLIENT:
			if( NextPlayer == 1 ) {				
				printf("Waiting for Player 1...\n");
				recv(this->Client->GetClient(), Board, 9, 0);
				NextPlayer = 2;				
			} else {				
				Board[atoi(tmp)-1] = 1;
				send(this->Client->GetClient(), tmp, 1, 0);
				NextPlayer = 1;
			}
			break;
			
		default:
			break;
	}
}

// Game::Start
void Game::Start() {
	if( this->GameMode == MODE_NET_HOST ) {		
		this->Server = new GameServer(DEFAULT_PORT);
	}

	if( this->GameMode == MODE_NET_CLIENT ) {		
		this->Client = new GameClient();
	}

	while(1) {
		DrawBoard();
		Analyze();
		NextStep();             
	}
}

/* Game::End
   Parameter values:
	0: Draw
	1: Player 1 wins
	2: Player 2 wins */
void Game::EndGame(int winner) {
	if( winner == 0 ) {
		printf("\n[+] Game ended!\nThere is no winner.\n", winner);
	} else {
		printf("\n[+] Game ended!\nWinner is Player %d.\n", winner);
	}

	// Close connection when hosting a network game
	if( this->GameMode == MODE_NET_HOST ) {
		this->Server->Close();
	}

	// Close connection when joined a network game
	if( this->GameMode == MODE_NET_CLIENT ) {
		this->Client->Close();
	}

	/* Wait for keystroke on windows machines before exit to show
	   results even if the user just double clicked the exe */
	#ifdef _WIN32
		system("PAUSE");	
	#endif
	exit(0);
}


// Game::Analyze the game board
void Game::Analyze() {  

	int check = 0;
	for(int i=0; i<9; i++) {
		switch(Board[i]){
			case 1:
			case 0:
				check++;
				break;
		}
	}	
	
	// Horizontal Player 1
	if( (Board[0] == 0 && Board[1] == 0 && Board[2] == 0) || 
		(Board[3] == 0 && Board[4] == 0 && Board[5] == 0) ||
		(Board[6] == 0 && Board[7] == 0 && Board[8] == 0)) {            
			EndGame(1);
	}
	// Vertical Player 1
	if( (Board[0] == 0 && Board[3] == 0 && Board[6] == 0) ||
		(Board[1] == 0 && Board[4] == 0 && Board[7] == 0) ||
		(Board[2] == 0 && Board[5] == 0 && Board[8] == 0)) {
			EndGame(1);
	}
	// Diagonal Player 1
	if( (Board[0] == 0 && Board[4] == 0 && Board[8] == 0) ||
		(Board[2] == 0 && Board[4] == 0 && Board[6] == 0)) {
			EndGame(1);
	}
	
	// ----------------------------------------------------------
	
	// Horizontal Player 2
	if( (Board[0] == 1 && Board[1] == 1 && Board[2] == 1) || 
		(Board[3] == 1 && Board[4] == 1 && Board[5] == 1) ||
		(Board[6] == 1 && Board[7] == 1 && Board[8] == 1)) {
			EndGame(2);
	}
	// Vertical Player 2
	if( (Board[0] == 1 && Board[3] == 1 && Board[6] == 1) ||
		(Board[1] == 1 && Board[4] == 1 && Board[7] == 1) ||
		(Board[2] == 1 && Board[5] == 1 && Board[8] == 1)) {
			EndGame(2);
	}
	// Diagonal Player 2
	if( (Board[0] == 1 && Board[4] == 1 && Board[8] == 1) ||
		(Board[2] == 1 && Board[4] == 1 && Board[6] == 1)) {
			EndGame(2);
	}            

	// We have a Draw!
	if( check >= 9 ) {
		EndGame(0);
	}
}
