//----------------------------------------------------------------------------
// File:	fleet.cpp
// 
// Functions: 
//	  setShipInfo()	
//	  allocMem() 
//	  deleteMem()
//	  printShip() 
//	  printGrid() 
//	  initializePlayer() 
//	  setships()	      
//	  saveGrid()
//	  loadGridFromFile()
//	  getCoord()
//	  isValidLocation() 
//	  header() 
//	  endBox() 
//----------------------------------------------------------------------------
#include "fleet.h"
//----------------------------------------------------------------------------
// YOU ARE RESPONSIBLE FOR CORRECT HEADERS -- one for each function
// include the definitions for each of the non-template functions
//    declared in fleet.h 
//----------------------------------------------------------------------------

const char* shipNames[SHIP_SIZE_ARRAYSIZE] = 
	{"No Ship", "Mine Sweeper", "Submarine", "Frigate",
		"Battleship", "Aircraft Carrier"};
const int TOTALPIECES = 17; // total pieces in all ships

//----------------------------------------------------------------------------
// Function:	setShipInfo()
// Title:		Set ShipInfo
// Description:
//		Sets struct ShipInfo fields
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Intel Xeon PC 
//                Software:   MS Windows 7 for execution; 
//                Compiles under Microsoft Visual C++.Net 2017
//
// Calls:
//
// Called By:
//
// Parameters:	shipInfoPtr: ShipInfo *; pointer to the ShipInfo to be set
//				name: Ship;	enumerated name of type of ship; default: NOSHIP
//				orientation: Direction;	enumerated direction; default: HORIZONTAL
//				row: unsigned short; row-coordinate in grid; default: 0
//				col: unsigned short; column-coordinate in grid; default: 0
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//   
//----------------------------------------------------------------------------
void setShipInfo(ShipInfo * shipInfoPtr, Ship name, Direction orientation,
	unsigned short row, unsigned short col)
{
	
} 

//----------------------------------------------------------------------------
// Function:	allocMem()
// Title:		Allocate Memory
// Description:
//		allocates memory for current grids
// Programmer:	Paul Bladek
// modified by: Ethan Lindemann and Gabe Blumenthal
// 
// Date:	9/13/06
//
// Version:	1.01
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of 2 players in the game
//		size: char;	'	S' or 'L' (small or large)
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 1.0 
//		9/13/06  PB completed v 1.01
//		1/20/17  PB completed v 1.02
//
//----------------------------------------------------------------------------
void allocMem(Player players[], char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		for (int whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++)
		{
			for (short i = 0; i < NUMPLAYERS; ++i)
			{
				players[i].m_gameGrid[whichGrid] = nullptr;
				players[i].m_gameGrid[whichGrid] = new Ship*[numberOfRows];
				for (short j = 0; j < numberOfRows; ++j)
				{
					//-------------------------------------------------
					//	your code goes here ...
					// set the pointers to NULL, then allocate the
					// memory for each row in each grid

					// new code -- GB 1/9/18
					players[i].m_gameGrid[whichGrid][j] = nullptr;
					players[i].m_gameGrid[whichGrid][j] = new Ship[numberOfCols];

					//--------------------------------------------------
					for (short k = 0; k < numberOfCols; ++k)
					{
						players[i].m_gameGrid[whichGrid][j][k] = NOSHIP;
					} // end for k
				} // end for j

			} // end for i
		} // end for whichGrid
	}
	catch(exception e)
	{
		deleteMem(players, size);
		cerr << "exception: " << e.what() << endl;
		cout << "shutting down" << endl;
		cin.ignore(FILENAME_MAX, '\n');
		exit(EXIT_FAILURE);
	}
}

//----------------------------------------------------------------------------
// Function:	deleteMem()
// Title:		Delete Memory
// Description:
//		Safely deletes memory for grids
// Programmer: Gabe Blumenthal and Ethan Lindemann-Michael
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of the 2 Players
//		size: char;	'	S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//   
//---------------------------------------------------------------------------------
void deleteMem(Player players[], char size) 
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	
	// new code GB/ELM 1/11/18
	for (int whichGrid = 0; whichGrid < NUMPLAYERS; whichGrid++)
	{
		for (short i = 0; i < NUMPLAYERS; ++i)
		{
			// Make sure grid contains a ptr
			if (players[i].m_gameGrid[whichGrid] != nullptr) 
			{
				for (short r = 0; r < numberOfRows; ++r)
				{
					// delete every row in grid
					if (players[i].m_gameGrid[whichGrid][r] != nullptr)
					{
						delete[] players[i].m_gameGrid[whichGrid][r];
					}
				}
				delete[] players[i].m_gameGrid[whichGrid];
			}
		}
	}
}

//---------------------------------------------------------------------------------
// Function:	printShip()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Output:		three characters representing one ship to sout
//
// Calls:
//
// Called By:	printGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//				thisShip: Ship;	the Ship to be printed in the grid format
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void printShip(ostream & sout, Ship thisShip)
{	
	switch(thisShip)
	{
		case NOSHIP: sout << ' ';
			break;
		case MINESWEEPER: sout << 'M';
			break;
		case SUB: sout << 'S';
			break;
		case FRIGATE: sout << 'F';
			break;
		case BATTLESHIP: sout << 'B';
			break;
		case CARRIER: sout << 'C';
			break;
		case HIT: sout << 'H';
			break;
		case MISSED: sout << MISS;
			break;
		default: sout << 'X';
	}
}

//---------------------------------------------------------------------------------
// Function:	printGrid()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Output:	a single grid to sout
//
// Calls:	printShip()
//
// Called By:	main()
//		setships()
//		saveGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//		grid: Ship**;	the 2-D array of Ships 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
void printGrid(ostream& sout, Ship** grid, char size)
{
	const bool isLarge = toupper(size) == 'L';
	short numberOfRows = (isLarge) ? LARGEROWS : SMALLROWS;
	short numberOfCols = (isLarge) ? LARGECOLS : SMALLCOLS;
	Ship ship;
	// Print column numbers
	for (short j = 1; j <= numberOfCols; ++j) {
		sout << setw(3) << j;
	}
	sout  << endl;
	
	for (short x = 0; x < numberOfRows; ++x)
	{
		sout << char(x + 65);
		for (short y = 0; y < numberOfCols; ++y)
		{
			sout << " ";
			ship = grid[x][y] == NULL ? Ship::NOSHIP : grid[x][y];
			printShip(sout, ship);
			sout << VERT;
		}
		sout << endl;

		// Print Row Separators 
		sout << HORIZ;
		for (int i = 0; i < numberOfCols; i++) {
			sout << HORIZ << HORIZ << CR;
		}
		sout << endl;
	}
} 

//---------------------------------------------------------------------------------
// Function:	initializePlayer()
// Title:	Initialize Player 
// Description:
//		sets initial values for m_ships and m_piecesLeft
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Calls:
//
// Called By:	main()
//
// Parameters:	playerPtr: Player*;	a pointer to the current Player
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void initializePlayer(Player* playerPtr)
{
	for(short i = 0; i < SHIP_SIZE_ARRAYSIZE; i++)
		setShipInfo(playerPtr->m_ships + i, static_cast<Ship>(i));
	
	playerPtr->m_piecesLeft = TOTALPIECES; 
}

//---------------------------------------------------------------------------------
// Function:	setships()
// Title:	Set Ships 
// Description:
//		Allows user to put ships in grid
// Programmer:	Paul Bladek
// modified by:	Ethan Lindemann and Gabe Blumenthal
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Input:	location and orientation using getCoord from cin
//
// Output:	prompts to cout
//
// Calls:	printGrid()
//		safeChoice()
//		getCoord()
//		saveGrid()
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players 
//		size: char;		'S' or 'L'
//		whichPlayer: short;	the player number (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 0.5
//     
//---------------------------------------------------------------------------------
void setships(Player players[], char size, short whichPlayer)
{
	// Player data
	Ship** shipGrid = players[whichPlayer].m_gameGrid[0];
	ShipInfo playerShip;
	Direction shipOrientation;
	Cell shipBowLocation = { 0, 0 };

	ostringstream confirmation;
	ostringstream outSStream;

	// Refresh console
	system("cls");
	header(cout);
	printGrid(cout, players[whichPlayer].m_gameGrid[0], size);

	// Iterate through every ship
	for(short shipIndex = 1; shipIndex < SHIP_SIZE_ARRAYSIZE; shipIndex++)
	{
		outSStream.str("");
		outSStream << "Player " << whichPlayer + 1 << " Enter " << shipNames[shipIndex] << " orientation";

		// Create the ship
		playerShip = ShipInfo();
		playerShip.m_name = Ship(shipIndex);
		playerShip.m_piecesLeft = shipSize[shipIndex];

		// Set the ship orientation 
		const char input =  safeChoice(outSStream.str(), 'V', 'H');
		playerShip.m_orientation = shipOrientation = (input == 'V') ? VERTICAL : HORIZONTAL;

		// Set the ship bow location
		cout << "Enter " << shipNames[shipIndex] << " bow coordinates. " << endl;
		playerShip.m_bowLocation = shipBowLocation = getCoord(cin, size);

		players[whichPlayer].m_ships[shipIndex] = playerShip;

		// Check if ship location is valid
		if(!isValidLocation(players[whichPlayer], shipIndex, size))
		{
			cout << "invalid location. Press <enter>" ;
			cin.get();
			shipIndex--; // redo
			continue;
		}

		// Place the ship in the grid
		for (int i = 0; i < shipSize[shipIndex]; i++) 
		{
			if (shipOrientation == VERTICAL)
			{
				shipGrid[shipBowLocation.m_row + i][shipBowLocation.m_col] = playerShip.m_name;
			}
			else if (shipOrientation == HORIZONTAL)
			{
				shipGrid[shipBowLocation.m_row][shipBowLocation.m_col + i] = playerShip.m_name;
			}
		}
		system("cls");
		header(cout);
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		
		// Confirm layout choice
		confirmation.str("");
		confirmation << "Is player " << (whichPlayer + 1) << "'s " << shipNames[shipIndex] << " location OK?";
		const char okChoice = safeChoice(confirmation.str());
		if (okChoice == 'N') shipIndex--;
	} 
	// Save the grid
	const char save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if(save == 'Y') saveGrid(players, whichPlayer, size);
}

//---------------------------------------------------------------------------------
// Function:	saveGrid()
// Title:	Save Grid 
// Description:
//		Saves the ship grid to a file
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Output:	grid to specified file
//
// Calls:	printGrid()
//
// Called By:	setships()
//
// Parameters:	player: sPlayer[];	the array of 2 players
//		whichPlayer: short; the player number (0 or 1) 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
void saveGrid(Player players[], short whichPlayer, char size)
{
	// Check for valid grid size
	char gridSize = toupper(size);
	if (!(gridSize == 'L' || gridSize == 'S')) return;

	// Grab row and col sizes
	bool isLargeGrid = gridSize == 'L';
	short numberOfRows = isLargeGrid ? LARGEROWS : SMALLROWS;
	short numberOfCols = isLargeGrid ? LARGECOLS : SMALLCOLS;

	// Open file
	stringstream gameFilename(""); 
	gameFilename << "player" << (whichPlayer + 1) << "grid" << ".shp";
	ofstream gameFile = ofstream(gameFilename.str());
	if (!gameFile) return;

	// Grab players game grid
	Ship **playerGrid = players[whichPlayer].m_gameGrid[0];

	// Save the grid size
	gameFile << size;

	// Write the grid to a file
	for (short x = 0; x < numberOfRows; x++) {
		for (short y = 0; y < numberOfCols; y++) {
			gameFile << playerGrid[x][y];
		}
	}

	// Close out the file
	gameFile.close();
	cout << "Wrote file to " << gameFilename.str() << endl;
}

//---------------------------------------------------------------------------------
// Function:	loadGridFromFile()
// Title:	loadGridFromFile 
// Description:
//		Reads grid from a file and properly sets the ships
// Programmer:	Paul Bladek
// modified by:	Ethan Lindemann and Gabe Bru
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Input:	grid from specified file
//
// Output:	prompts to cout
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players
//		whichPlayer: short;	the player number  (0 or 1) 
//		size: char;		'S' or 'L'
//		string fileName:	the name of the file to be opened for reading
// 
// Returns: bool -- 	true if the file is opened and read;
//			false otherwise
//
// History Log: 
//		9/12/06 PB comleted v 0.5
//     
//---------------------------------------------------------------------------------
bool loadGridFromFile(Player players[], short whichPlayer, char size, string fileName)
{
	// Check for valid grid size
	char gridSize = toupper(size);
	if (!(gridSize == 'L' || gridSize == 'S')) return false;

	// Grab row and col sizes
	bool isLargeGrid = gridSize == 'L';
	short numberOfRows = isLargeGrid ? LARGEROWS : SMALLROWS;
	short numberOfCols = isLargeGrid ? LARGECOLS : SMALLCOLS;

	// Grab players game grid
	Ship** playerGrid = players[whichPlayer].m_gameGrid[0];

	// Open game file
	ifstream gameFile(fileName.c_str());
	if (!gameFile)
	{
		cout << "Could not open file " << fileName << endl << "Press <enter> to continue" << endl;
		cin.ignore(FILENAME_MAX, '\n');
		return false;
	}

	// Check for valid file grid size
	const char fileGridSize = toupper(static_cast<char>(gameFile.get()));
	if (!(fileGridSize == 'L' || fileGridSize == 'S') || fileGridSize != gridSize)
	{
		gameFile.close();
		cout << "Could not load file " << fileName << endl << "Press <enter> to continue" << endl;
		cin.ignore(FILENAME_MAX, '\n');
		return false;
	};

	// Write the grid to a file
	for (short x = 0; x < numberOfRows; x++) {
		for (short y = 0; y < numberOfCols; y++) {
			playerGrid[x][y] = static_cast<Ship>(gameFile.get() - '0');
		}
	}

	for (short s = 1; s < SHIP_SIZE_ARRAYSIZE; s++)
	{
		players[whichPlayer].m_ships[s].m_name = Ship(s);
		players[whichPlayer].m_ships[s].m_piecesLeft = shipSize[s];
	}
		
	gameFile.close();
	printGrid(cout, playerGrid, size);
	return true;
}

//---------------------------------------------------------------------------------
// Function:	getCoord()
// Title:	Get Coordinates 
// Description:
//		Returns a cell with coordinates set by user
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Input:	cell coordinates (in the form "A13" from sin
//
// Output:	prompts to cout
//
// Calls:	none
//
// Called By:	main()
//		setships()
//
// Parameters:	sin: istream&;	the stream to read from
//		size: char;	'S' or 'L'
// 
// Returns:	Cell location -- a cell containing the input coordinates
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
Cell getCoord(istream& sin, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	char highChar = static_cast<char>(numberOfRows - 1) + 'A';
	char row  = 'A';
	short col = 0;
	Cell location = {0, 0};
	do
	{
		col = 0;
		cout << "Row must be a letter from A to " << highChar 
			<< " and column must be from 1 to "  << numberOfCols << ": ";
		while((row = toupper(sin.get())) < 'A' || row  > highChar)
		{
			sin.ignore(FILENAME_MAX, '\n');
			cout << "Row must be a letter from A to " << highChar 
				<< " and column must be from 1 to "  << numberOfCols << ": ";
		}
		sin >> col;
		if(!sin)
			sin.clear();
		sin.ignore(FILENAME_MAX, '\n');
	}
	while(col < 1 || col > numberOfCols);
	
	location.m_col = col - 1;
	location.m_row = static_cast<short>(row - 'A');
	return location;
}

bool testHit(Player* game, short currentPlayer, short enemyPlayer, Cell coord)
{
	Ship** currentGrid = game[currentPlayer].m_gameGrid[1];
	Ship** enemyGrid = game[enemyPlayer].m_gameGrid[0];

	bool isHit = enemyGrid[coord.m_row][coord.m_col] > Ship::NOSHIP && enemyGrid[coord.m_row][coord.m_col] < Ship::HIT;
	currentGrid[coord.m_row][coord.m_col] = isHit ? Ship::HIT : Ship::MISSED;

	if (isHit)
	{
		Ship shipHit = enemyGrid[coord.m_row][coord.m_col];
		game[enemyPlayer].m_ships[shipHit].m_piecesLeft--;
		game[enemyPlayer].m_piecesLeft--;
	}

	return isHit;
}

Ship sunkShip(Player* game, short player, Cell coord)
{
	Ship testShip = game[player].m_gameGrid[0][coord.m_row][coord.m_col];
	if (testShip > Ship::NOSHIP && testShip < Ship::HIT)
	{
		return game[player].m_ships[testShip].m_piecesLeft <= 0 ? testShip : Ship::NOSHIP;
	}
	return Ship::NOSHIP;
}

//---------------------------------------------------------------------------------
// Function:	isValidLocation()
// Title:	Valid Location 
// Description:
//		Can the ship legitimately go there?
// Programmer:
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Calls:
//
// Called By:
//
// Parameters:	player: const Player&;	a reference to the specific Player
//		shipNumber: short;	the number of the ship (1 - 5)
//					in the array player.m_ships[]
//		size: char;		'S' or 'L'
// 
// Returns: bool -- 	true if the ship would not go off the edge
//				or cross another ship;
//			false otherwise
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
bool isValidLocation(const Player& player, short shipNumber, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	// Get ship position
	const ShipInfo ship = player.m_ships[shipNumber];
	const short shpSize = shipSize[shipNumber];
	const Cell bow = ship.m_bowLocation;
	const Direction orientation = ship.m_orientation;
	
	// Check for an out of bounds ship
	if (bow.m_col > numberOfCols || bow.m_col < 0) return false;
	if (bow.m_row > numberOfRows || bow.m_row < 0) return false;

	// Check ship position exceeds grid size
	if (orientation == HORIZONTAL && bow.m_col + shpSize > numberOfCols) return false;
	else if (orientation == VERTICAL && bow.m_row + shpSize > numberOfRows) return false;

	// This ship location is valid
	return true;
}

//---------------------------------------------------------------------------------
// Function:	header()
// Title:	header 
// Description:
//		Prints opening graphic
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	sout: ostream&;	the stream to print to
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void header(ostream& sout)
{
	const string empty;
	const string sink("SINK THE FLEET!");
	// your name goes here!
	const string by("Edmonds Community College CS 132");
	boxTop(sout, BOXWIDTH);
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, sink , BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, by, BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxBottom(sout, BOXWIDTH);
}

//---------------------------------------------------------------------------------
// Function:	endBox()
// Title:	End Box 
// Description:
//		prints closinging graphic
// Programmer:	Paul Bladek
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2017
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	player: short; the number of the winner (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void endBox(short player)
{
	const string empty;
	ostringstream msg;
	msg << "Congratulations player " << player + 1 << "!";
	boxTop(cout, BOXWIDTH);
	boxLine(cout, empty, BOXWIDTH);
	boxLine(cout, msg.str() , BOXWIDTH, 'C');
	boxLine(cout, empty, BOXWIDTH);
	boxBottom(cout, BOXWIDTH);
}

