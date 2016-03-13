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
#ifndef __3T_H__
#define __3T_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Enemy.h"
#include "GameServer.h"
#include "GameClient.h"

#define BANNER "-------------------\r\n[+] Tic Tac Toe [+]\r\n-------------------\r\n"

// Game modes
#define MODE_EXIT		0
#define MODE_SINGLE		1
#define MODE_MULTI		2
#define MODE_NET_HOST	3
#define MODE_NET_CLIENT	4

// General function to clear the screen
void clrscr();

// The Game class
class Game {
	private:
		char GameMode;
		Enemy *enemy;
		char Board[9];
		bool Running;
		char Output[512];
		int NextPlayer;
		GameServer *Server;
		GameClient *Client;

		void NextStep();
		void DrawBoard();
		void EndGame(int w);
		void Analyze();

	public:
		Game(int mode);
		void Start();
};
#endif
