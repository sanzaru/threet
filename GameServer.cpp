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
#include "GameServer.h"

GameServer::GameServer(int p) {
	int cliLen = 0;

	if( p <= 0 || p <= 1024 || p >= 65536 ) {
		this->port = DEFAULT_PORT;		
	} else {
		this->port = p;
	}

	#ifdef _WIN32
		WSADATA wsa;
		WSAStartup(MAKEWORD(2,0),&wsa);
	#endif
	this->addr.sin_family = AF_INET;
	this->addr.sin_addr.s_addr = INADDR_ANY;	
	this->addr.sin_port = htons(this->port);	

	this->sock = socket(AF_INET, SOCK_STREAM, 0);	
	bind(this->sock,(struct sockaddr *)&this->addr,sizeof(this->addr));
	printf("Server created on port %d...\nWaiting for a connection...", this->port);
	listen(this->sock, 1);

	cliLen = sizeof(struct sockaddr_in);
	#ifdef _WIN32
  	this->client = accept(this->sock, (struct sockaddr *)&this->addr, &cliLen);
  #else
    this->client = accept(this->sock, (struct sockaddr *)&this->addr, (socklen_t*)&cliLen);
  #endif
	if( this->client < 0 ) {
		perror("Accept connection.\n");
	}
}


// Return server port
int GameServer::GetPort() {
	return this->port;
}

int GameServer::GetClient() {
	return this->client;
}

void GameServer::Close() {
	#ifndef _WIN32
		close(this->client);
	#else
		closesocket(this->client);
	#endif
}
