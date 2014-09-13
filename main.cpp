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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "3t.h"

#define VERSION "1.1"
#define AUTHOR "Martin Albrecht <martin.albrecht@javacoffee.de>"

// Network menu
int NetworkMenu() {
	int ch;
	char buf[256];

	printf("[+] Network game\n\t");
	printf("(3) Host a game\n\t(4) Join a game\n\t(0) Exit\n\n");
	printf(">> ");
	#ifdef _WIN32
		scanf_s("%s", buf);
	#else
		scanf("%s", buf);
	#endif
	ch = atoi(buf);
	return ch;
}


// The game menu
int GameMenu() {
	int ch;
	char buf[256];
	printf("[+] Menu [+]\n\t");
	printf("(1) Single-Player\n\t(2) Multi-Player\n\t(3) Network game\n\t(0) Exit\n\n");
	// Get user choice
	printf(">> ");
	#ifdef _WIN32
		scanf_s("%s", buf);
	#else
		scanf("%s", buf);
	#endif
	ch = atoi(buf);
	if( ch == 3 ) {
		return NetworkMenu();
	}
	return ch;
}


int main(int argc, char **argv) {
	
	// Print out the version string
	if( argc == 2 && strcmp(argv[1], "-v") == 0 ) {
		printf("3t - Version: %s\nWritten by: %s\n", VERSION, AUTHOR);
		exit(0);
	}
	
	// Start the game
	Game *game = new Game(GameMenu());
	game->Start();          
	return 0;
}

