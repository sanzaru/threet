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
#include "Enemy.h"

// Pseudo constructor
Enemy::Enemy() {
	return;
}

// Enemy:Analyze and return next move
int Enemy::Analyze(char *b) {

	// First, we check if there is any possibility to win,
	// after that we check for any threads of the opponent
	// and if all fails we select a random field, that is free.
	if( b[1] == 1 && b[2] == 1 || // Fields 2 and 3 -> 1
		b[3] == 1 && b[6] == 1 || // Fields 4 and 7 -> 1
		b[8] == 1 && b[4] == 1 || // Fields 9 and 5 -> 1
		b[1] == 0 && b[2] == 0 || // Fields 2 and 3 -> 1
		b[8] == 0 && b[4] == 0 || // Fields 9 and 5 -> 1
		b[3] == 0 && b[6] == 0 ) // Fields 4 and 7 -> 1
	{
		if( b[0] == 3 ) {
			return 0;
		}
	}

	if( b[4] == 1 && b[7] == 1 || // Fields 5 and 8 -> 2
		b[0] == 1 && b[2] == 1 || // Fields 1 and 3 -> 2
		b[0] == 0 && b[2] == 0 || // Fields 1 and 3 -> 2
		b[4] == 0 && b[7] == 0 )  // Fields 5 and 8 -> 2
	{
		if( b[1] == 3 ) {
			return 1;
		}
	}

	if( b[0] == 1 && b[1] == 1 || // Fields 1 and 2 -> 3
		b[5] == 1 && b[8] == 1 || // Fields 6 and 9 -> 3
		b[6] == 1 && b[4] == 1 || // Fields 7 and 5 -> 3
		b[0] == 0 && b[1] == 0 || // Fields 1 and 2 -> 3
		b[5] == 0 && b[8] == 0 || // Fields 6 and 9 -> 3
		b[6] == 0 && b[4] == 0 )  // Fields 7 and 5 -> 3
	{
		if( b[2] == 3 ) {
			return 2;
		}
	}

	if( b[4] == 1 && b[5] == 1 || // Fields 5 and 6 -> 4
		b[0] == 1 && b[6] == 1 || // Fields 1 and 7 -> 4
		b[4] == 0 && b[5] == 0 || // Fields 5 and 6 -> 4
		b[0] == 0 && b[6] == 0 )  // Fields 1 and 7 -> 4
	{
		if( b[3] == 3 ) {
			return 3;
		}
	}

	if( b[3] == 1 && b[5] == 1 || // Fields 4 and 6 -> 5
		b[1] == 1 && b[7] == 1 || // Fields 2 and 8 -> 5
		b[0] == 1 && b[8] == 1 || // Fields 1 and 9 -> 5
		b[2] == 1 && b[6] == 1 || // Fields 3 and 7 -> 5
		b[3] == 0 && b[5] == 0 || // Fields 4 and 6 -> 5
		b[1] == 0 && b[7] == 0 || // Fields 2 and 8 -> 5
		b[0] == 0 && b[8] == 0 || // Fields 1 and 9 -> 5
		b[2] == 0 && b[6] == 0 )  // Fields 3 and 7 -> 5
	{
		if( b[4] == 3 ) {
			return 4;
		}
	}

	if( b[3] == 1 && b[4] == 1 || // Fields 4 and 5 -> 6
		b[2] == 1 && b[8] == 1 || // Fields 3 and 9 -> 6
		b[3] == 0 && b[4] == 0 || // Fields 4 and 5 -> 6
		b[2] == 0 && b[8] == 0 )  // Fields 3 and 9 -> 6
	{
		if( b[5] == 3 ) {
			return 5;
		}
	}

	if( b[7] == 1 && b[8] == 1 || // Fields 8 and 9 -> 7
		b[0] == 1 && b[3] == 1 || // Fields 1 and 4 -> 7
		b[2] == 1 && b[4] == 1 || // Fields 3 and 5 -> 7
		b[7] == 0 && b[8] == 0 || // Fields 8 and 9 -> 7
		b[0] == 0 && b[3] == 0 || // Fields 1 and 4 -> 7
		b[2] == 0 && b[4] == 0 )  // Fields 3 and 5 -> 7
	{
		if( b[6] == 3 ) {
			return 6;
		}
	}

	if( b[1] == 1 && b[4] == 1 || // Fields 2 and 5 -> 8
		b[6] == 1 && b[8] == 1 || // Fields 7 and 9 -> 8
		b[1] == 0 && b[4] == 0 || // Fields 2 and 5 -> 8
		b[6] == 0 && b[8] == 0 )  // Fields 7 and 9 -> 8
    {
		if( b[7] == 3 ) {
			return 7;
		}
	}

	if( b[6] == 1 && b[7] == 1 || // Fields 7 and 8 -> 9
		b[2] == 1 && b[5] == 1 || // Fields 3 and 6 -> 9
		b[0] == 1 && b[4] == 1 || // Fields 1 and 5 -> 9
		b[6] == 0 && b[7] == 0 || // Fields 7 and 8 -> 9
		b[2] == 0 && b[5] == 0 || // Fields 3 and 6 -> 9
		b[0] == 0 && b[4] == 0 )  // Fields 1 and 5 -> 9
    {
		if( b[8] == 3 ) {
			return 8;
		}
	}

	// -----------------------------------------------------------

	// If no thread an no winning chance is found, return random
	// int between 0 and 8
	time_t dt;
	bool done = false;
	int val = 0;
	while( !done ) {
		srand((unsigned int)time(&dt));
		val = (int) rand()%8;
		if( b[val] == 3 ) {
			done = true;
		}
	}

	return val;
}
