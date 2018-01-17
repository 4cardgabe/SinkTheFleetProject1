//----------------------------------------------------------------------------
// File:	SinkTheFleetleet.cpp
// 
// Function:
//      main()
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "fleet.h"

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
extern const char* shipNames[7];
//---------------------------------------------------------------------------------
// Function:	main()
// Title:		Set ShipInfo
// Description:
//				Runs the Sink the Fleet Game
// Programmer:	Paul Bladek
// modified by:
// 
// Date:		12/9/2010
//
// Version:		0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2015
//
// Input:		
//
// Output:		
//
// Calls:		initializePlayer()
//				allocMem()
//				safeChoice()
//				loadGridFromFile()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				12/9/2010 PB completed v 0.5
//   
//---------------------------------------------------------------------------------
int main(void)
{
	short numRows = SMALLROWS;			// total number of rows in the array
	short numCols = SMALLCOLS;			// total number of columns in the array
	char again = 'N';
	char gridSize = 'S';
	short whichPlayer = 0;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = {0, 0};
	string message;
	string filename;
	Ship shipHit = NOSHIP;
	Player game[NUMPLAYERS];	// the two players in an array
	// YOUR CODE GOES HERE ...
	string s2("");
	do
	{
		system("cls");
		cout << endl;
		header(cout);
		gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');

		numRows = (toupper(gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		numCols = (toupper(gridSize) == 'L') ? LARGECOLS : SMALLCOLS;
		
		initializePlayer(game);		
		initializePlayer(game + 1);
		// dynamically create the rows of the array
		allocMem(game, gridSize);
		
		// YOUR CODE GOES HERE ...


		for(whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
			// enter grid files or let users enter ships

		}
		whichPlayer = 0;
		while(!gameOver)
		{
			// YOUR CODE GOES HERE ....
			gameOver = true;

			// new code GB 1/16/18
			printGrid(cout, *game->m_gameGrid,gridSize);
			whichPlayer = !whichPlayer;  // switch players
		}
		// clean up memory ...
		deleteMem(game, gridSize);

		again = safeChoice("Would you like to play again?", 'Y', 'N');
	}
	while(again == 'Y');
	
	_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
} 
