/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <chrono>
#include "Game.h"
using std::cout;
using std::endl;
using std::string;


int main()
{
	srand(time_t(NULL));
	Pipe p;
	bool isConnect = p.connect();
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return 0;
		}
	}
	Game game;
	string initialBoardState = game.getBoardState();
	char msgToGraphics[1024];
	
	#ifdef _WIN32
	strcpy_s(msgToGraphics, initialBoardState.c_str());
	p.sendMessageToGraphics(msgToGraphics);
	#endif

	string msgFromGraphics = p.getMessageFromGraphics();
	while (msgFromGraphics != "quit")
	{
		string resultToGraphics = game.handleMove(msgFromGraphics);
		//game.printCurrentBoard();
		msgToGraphics[0] = resultToGraphics[0];
		msgToGraphics[1] = 0;
		p.sendMessageToGraphics(msgToGraphics);
		msgFromGraphics = p.getMessageFromGraphics();
	}
	p.close();
}
