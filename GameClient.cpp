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
#include "GameClient.h"

void GameClient::InputData() {
	char p_buf[256];

	printf("[+] Join game\n\t");	
	printf("Server Address: ");
	#ifdef _WIN32
		scanf_s("%s", this->ip);
	#else
		scanf("%s", this->ip);
	#endif	
	
	printf("\tPort: ");
	#ifdef _WIN32
		scanf_s("%s", p_buf);
	#else
		scanf("%s", p_buf);
	#endif
	this->port = atoi(p_buf);
}


GameClient::GameClient() {
	int status; 

	this->InputData();
	this->addr.sin_family = AF_INET;
	this->addr.sin_port = htons(this->port);
	this->addr.sin_addr.s_addr = inet_addr(this->ip);
	#ifdef _WIN32
		WSADATA wsa;
		WSAStartup(MAKEWORD(2,0),&wsa);
	#endif

	printf("Connecting to %s on port %d...\n", this->ip, this->port);
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	status = connect(this->sock, (struct sockaddr *)&this->addr, sizeof(sockaddr_in));
	if( status == -1 ) {
		printf("Error: Cannot connect to game!\n");
		exit(1);
	}
}

int GameClient::GetClient() {
	return this->sock;
}

void GameClient::Close() {
	#ifndef _WIN32
		close(this->sock);
	#else
		closesocket(this->sock);
	#endif
}