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
#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_PORT 4711

#ifndef _WIN32
	#include <unistd.h>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <unistd.h>	
	#include <sys/un.h>	
	#include <arpa/inet.h>
#else
	#pragma comment(lib, "ws2_32.lib")
	#pragma comment(lib, "wsock32.lib")
	#include <winsock.h>	
#endif

#endif
