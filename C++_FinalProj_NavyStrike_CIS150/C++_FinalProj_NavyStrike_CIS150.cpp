//AUTHOR(s): Erik English, Chuck, and Tristan
//eMails: erik.m.english@gmail.com \ eenglish13820@my.monroe.edu, tludwig33344@my.monroeccc.edu, ccurtis2@my.monroeccc.edu
//DATE: 11/11/17
/*DESCRIPTION: Final Project - Naval Strike a game based off of Battleship.  */
//VERSION: 2017

#define _WIN32_WINNT 0x0500 //Must have defined before Windows.h (Citation given on line 71)

#include "stdafx.h"    // Precompiled Header
#include <iostream>    // Standard input output ease of use on std::
#include <stdio.h>     // Instead of using cin.getline you can use cin.gets(),parameter is stdio.h
//#include <istream>   // Has to do with getline  get()
#include <string>      // string x
#include <iomanip>     // setw(x) and others for output formating
#include "fstream"     // For opening up files. like .txt  // we may need this for the ascii art, it could be infinitely easier.
#include <Windows.h>   // To use Sleep
#include <Ctime>       // To use the random number generator for onePlayer.
using namespace std;

//Code found from cplusplus.com: SOURCE: http://www.cplusplus.com/forum/beginner/105484/ ; User: Giblit
enum COLOR
{
	black, blue, 
	green, cyan, 
	red, magenta, 
	brown, normal, 
	darkgrey, lightblue, 
	lightgreen, lightcyan, 
	lightred, lightmagenta, 
	yellow, white
};


//Not entirely sure what this does but is necessary for coloring text.
ostream& operator<<(ostream &stm, const COLOR &c)
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out_handle, c);
	return(stm);
}
//End of found code from cplusplus.com


//==================Function Prototypes==============
int intro();

//void board_intilization();

void TwoPlayer();
void firstCoord(char, int&, bool&, string[], int&, char[][11], char[][11]);
void refresh(int&, char[][11], char[][11], int&, int&, int&, string&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void secCoord(int&, bool&, char[][11], char[][11]);
void displayBlank(char[][11]);

//movement positions.
void setPos(int&, int&, int&, int&, string&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, char[][11]);
void up(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void down(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void left(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);
void right(int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&);

void destroyer();
//void submarine();
//void cruiser();
//void battleship();
//void carrier();
//void sound();

int main()
{
	//Used to set window size for our command prompt. Found at http://www.cplusplus.com/forum/beginner/1481/
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	//MoveWindow(console, r.left, r.top, 800, 800, TRUE);


	//Variables
	int players;


	//Functions
	//players = intro();  //currently to test deeper code comment this out, set players = 2;
	players = 2; //comment this out on release. and uncomment players = intro();

	//board_intilization(); //board intilization will go into the functions OnePlayer(), TwoPlayer() // board intilization is completely replaced with, displayBlank.
	
	if (players == 1)//1 player vs ai.
	{
		//need to make a function to place the ship in a random location on the board.
		cout << "Look forward to this feature in a new update! We require an A.I. to hire, know any around?" << endl;
		

		//Sleep(3000);
		//and back to intro(); until we decide to tackle that	
		//system("cls");
		//intro(); // ****game seems to break and default to press any key if going through the intro function more than once?**** why does it do this.

		//OnePlayer();

	}
	else if (players == 2)//2 players - Primary Focus
	{

		TwoPlayer(); 
		// need when the ship is being placed to be across more than one position on the board.
		//Possible idea, a max amount of shots you can shoot before you lose? could also manipulate in options to unlimited or limited

	}
	else if (players == 3)//Options
	{

		cout << "Future development is required here, look forward to changing colors of the game board!" << endl; // colors and board size? we may be able to manipulate sound still looking into it.
		//Options();

	}
	else
	{
		cout << "How'd you get here? Your not supposed to be here." << endl;
		
		
	}


	system("pause");
	return 0;
}

//==============================Functions=================

int intro()
{
	//any-key to skip some stuff? possible?

	//variables 
	bool menuNumber = false;
	int players = 0;
	//int v = 0;  // was used for now obsolete color switch.

	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(65) << cyan << "Loading..." << endl;
			Sleep(1000);
		}
		else if (i == 1)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(65) << "Loading.." << endl;
			Sleep(1000);
		}
		else if (i == 2)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(75) << "Counting missed shots.." << endl;
			Sleep(1000);
		}
		else if (i == 3)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(80) << "Loading. Please wait patiently." << endl;
			Sleep(1000);
		}
		else if (i == 4)
		{
			system("cls");
			cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << setw(70) << "Undocking ships." << endl;
			Sleep(1000);
		}
	}

	//This, 'do while' was for changing color on one of the splash screens but i dont like it.
	//May be able to use this in options though. - Erik
	
	/*do
	{
		
		if (v == 0)
		{
			cout << white;
		}
		else if (v == 1)
		{
			cout << cyan;
		}
		else if (v == 2)
		{
			cout << blue;
		}
		else if (v == 3)
		{
			cout << white;
		}
		else if (v == 4)
		{
			cout << blue;
		}
		else if (v == 5)
		{
			cout << cyan;
		}
		else if (v == 6)
		{
			cout << white;
		}
		else
		{
			cout << white;
		}*/


		//title
		for (int i = 0; i < 30; i++)
		{
			cout << endl;
			Sleep(10);
		}


		//cout << endl << endl << endl; //part of the above color switch turned off the timer on endl;s

		// very sensitive to spaces and tabs do not change.
		cout << cyan;
		cout << "          _/      _/                                  _/        _/_/_/    _/                _/  _/                " << endl;
		cout << "         _/_/    _/    _/_/_/  _/      _/    _/_/_/  _/      _/        _/_/_/_/  _/  _/_/      _/  _/      _/_/  " << endl;
		cout << "        _/  _/  _/  _/    _/  _/      _/  _/    _/  _/        _/_/      _/      _/_/      _/  _/_/      _/_/_/_/ " << endl;
		cout << "       _/    _/_/  _/    _/    _/  _/    _/    _/  _/            _/    _/      _/        _/  _/  _/    _/        " << endl;
		cout << "      _/      _/    _/_/_/      _/        _/_/_/  _/      _/_/_/        _/_/  _/        _/  _/    _/    _/_/_/   " << endl;
		//Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php


		// very sensitive to spaces and tabs do not change.

		// to utilize back space use \\ twice.
		//ascii art, SOURCE: http://ascii.co.uk/art/battleship
		cout << endl << endl << endl << endl << endl << endl << darkgrey;
		cout << "                                                        |__" << endl;
		cout << "                                                        |\\/" << endl;
		cout << "                                                        ---" << endl;
		cout << "                                                        / | [" << endl;
		cout << "                                                 !      | |||" << endl;
		cout << "                                               _/|     _/|-++'" << endl;
		cout << "                                           +  +--|    |--|--|_ |-" << endl;
		cout << "                                        { /|__|  |/\\__|  |--- |||__/" << endl;
		cout << "                                       +---------------___[}-_===_.'____                 /\\ " << endl;
		cout << "                                   ____`-' ||___-{]_| _[}-  |     |_[___\\==--            \\/   _" << endl;
		cout << "                    __..._____--==/___]_|__|_____________________________[___\\==--____,------' .7" << endl;
		cout << "                   |                                                                     BB-61/" << endl;
		cout << lightblue << "~~~~~~~~~~~~~~~~~~~~" << darkgrey << "\\_________________________________________________________________________|" << lightblue << "~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "                      ~               ~                ~               ~                ~               " << endl;
		//ascii art, SOURCE: http://ascii.co.uk/art/battleship
		cout << endl << endl;
		Sleep(5500);  //if returning to the color switch change the timer to something less than 5.5seconds
		system("cls");
		// very sensitive to spaces and tabs do not change.

		//both the v and the while is the end of the do while color change. again leaving for possible changes in options
		//v++;
	//} while (v != 6);


	//authors
	for (int i = 0; i < 30; i++)
	{
		cout << endl;
		Sleep(10);
	}

	cout << setw(65) << white << "Created By," << endl << setw(70) << "Erik, Tristan and Chuck" << endl << setw(65) << "Version 0.02" << endl; //update version count, for every day in class? we will be at 0.08 on Dec 6, 2017 	
	for (int i = 0; i < 16; i++)
	{
		cout << endl;
		Sleep(100);
	}
	Sleep(1500);
	system("cls");

	//MENU

	do
	{
		//Run this at least once
		system("cls");
		cout << endl << endl << endl << endl;

		//cout << setw(68) << cyan << "Welcome to Navy Strike" << endl;
		cout << white;
	
		cout << "        _ _ _ ____ _    ____ ____ _  _ ____    ___ ____    _  _ ____ _  _ ____ _       ____ ___ ____ _ _  _ ____ " << endl;
		cout << "        | | | |___ |    |    |  | |\\/| |___     |  |  |    |\\ | |__| |  | |__| |       [__   |  |__/ | |_/  |___ " << endl;
		cout << "        |_|_| |___ |___ |___ |__| |  | |___     |  |__|    | \\| |  |  \\/  |  | |___    ___]  |  |  \\ | | \\_ |___ " << endl;
		//Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php




		cout << endl << endl << endl << endl << endl;
		cout << setw(76) << white <<"Choose how you would like to play. \n";
		cout << endl << setw(65) << "1. ONE PLAYER \n";
		cout << setw(66) << "2. TWO PLAYERS \n"; //Only two player will work for the time being, 1 player will require an ai.
		cout << setw(62) << "3. OPTIONS \n"; //If time allows, come back to try to edit colors.

		


		
		// very sensitive to spaces and tabs do not change.
		cout << yellow << " . _  .    ." << red << "__ "<< yellow <<" .  .  __,--' " << endl;
		cout << yellow << "  (_)    ' " << red << "/__\\"<< yellow <<" __,--' " << endl;
		cout << yellow << "'  .  ' . '" << white << "| " << yellow << "o" << white << "|"<< yellow <<"' " << endl;
		cout << "          " << white << "["<< brown <<"IIII"<< white <<"]"<< yellow <<"`--.__ " << endl;
		cout << white <<  "           |  |       "<< yellow <<"`--.__ " << endl;
		cout << red << "           | :|             "<< yellow <<"`--.__ " << endl;
		cout << white << "           |  |                   "<< yellow <<"`--.__ " << endl;
		cout << lightblue << "._,,.-," << darkgrey << ".__." << white <<"'__`" << darkgrey << ".___."<< lightblue <<",.,.-..,_.,.,.,-._..`"<< yellow <<"--"<< lightblue <<".." << yellow << "-" << lightblue << ".,._.,,._,-,..,._..,.,_,,._.,,._,-,..,._..,.,_,,._.,,._,-,..,._..,.,_,,.,, " << endl;
		//SOURCE: http://ascii.co.uk/art/lighthouse Made originally by: unknown
		// very sensitive to spaces and tabs do not change.

		cout << endl << setw(62) << white << "Enter 1 - 3: ";

		//keep running until the player gives an appropriate number
		cin >> players;

		//players has to equal 1-3 if it does not, run it again.
		if(players == 1 || players == 2 || players == 3 )//HERE doesnt seem to want to loop for some reason also need an array for the player choice since this is staying a void function to pass on the choice 1 or 2 Maybe an OPTION button to change the colors? that would be cool. maybe a few presets
		{
			menuNumber = true;
		}
		else
		{
			cout << "Your trying to break my program, are you? I can do that myself, try again." << endl;
		}


	}while (menuNumber != true);
	system("cls");

	return players;
}


//void board_intilization()
//{
//
//	//this function is being used to give the player a prompt on where they should place the board.
//	//May be possible to use this one to highlight the color of the letter that is currently being selected and then the number, Erik 11/15/2017
//
//	//const int victorVec = 2; // possible idea for a 3d array
//	const int ROWS = 11;
//	const int COLUMNS = 11;
//
//	//variables
//	string div = "===============================================================================================================";
//	string between = "---------------------------------------------------------------------------------------------------------------";
//	
//	//       \/ [victorVec] 3d array
//	char board[ROWS][COLUMNS] = {	{ ' ',  '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9', '0'  },
//									{ 'A',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'B',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'C',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'D',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'E',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'F',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'G',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'H',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'I',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
//									{ 'J',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' } };
//
//
//
//	//This will be the board that the player uses to place and will look similar to the player guessing. except will be rewritten over the hidden spots
//	//2 for loops for making the board
//	cout << setw(115) << darkgrey << div << endl; // divider ' === '
//	for (int i = 0; i < ROWS; i++)
//	{
//		cout << darkgrey << setw(5) << "|";
//		for (int s = 0; s < COLUMNS; s++)
//		{
//			cout << setw(5) << lightcyan << board[i][s] << setw(5) << darkgrey << "|";
//		}
//		if (i != ROWS - 1)
//		{
//			cout << endl << setw(115) << between << endl;
//		}
//		else
//		{
//			cout << endl;
//		}
//	}
//	cout << setw(115) << darkgrey << div << endl;
//
//	//was considering sending a few variables to displayblank.. but wouldnt this also call displayBlank within the current function? I dont want that.
//	//displayBlank();
//
//
//}

void TwoPlayer()
{
	//Variables
	string PlayerX;

	const int ROWS = 11;
	const int COLUMNS = 11;
	
	string userDirectionalInput;

	char spaceOne = ' '; //letter that player enters for coordinate 1
	int spaceTwo = 0; //Number that player enters for coordinate 2
	int spaceOneNum = 0; //Number conversion between char and int for spaceOne

	bool validInput = false; //Making sure their guess stays within bounds of the board
	bool promptCheck = false;

	const int ships = 5;

	//directional variables
	//accounting for the first input, each additional variable -
	// - will be based on the points availble to it. Destroyer has two points -
	// - so along with the first cord put in, we need one additional input.
	// etc. Erik 11.15.2017

	//with the initial cord this makes 2 spots
	int destroy = 0;
	int destroy1 = 0;
	
	//with the initial cord this makes 3 spots
	int sub = 0;
	int sub1 = 0;
	int sub2 = 0;
	

	/*sub, cruis, battleship, carrier
	int&, int&, int&, int&
	int &sub, int &cruis, int &battleship, int &carrier*/

	//with the initial cord this makes 3 spots
	int cruis = 0;
	int cruis1 = 0;
	int cruis2 = 0;

	//with the initial cord this makes 4 spots
	int battleship = 0;
	int battleship1 = 0;
	int battleship2 = 0;
	int battleship3 = 0;

	//with the initial cord this makes 5 spots
	int carrier = 0;
	int carrier1 = 0;
	int carrier2 = 0;
	int carrier3 = 0;
	int carrier4 = 0;

	//11.14.17 observation Erik
	// our ships arent actually tied to anything in our arrays..
	// were replacing ~ with Xs for place holders of the ships but they dont actually represent Destroyer equals 3 spots
	// but not just that we cant - a point from the ship, of course the entire ship will make up a point a piece per array but if we kept coding now it would
	// be more difficult to try to fix what the destroyer represents on the board.
	//11.15.17 Erik.
	//Currrent setup is more like the missile attack then the ship placement.

	string shipName[ships] = { "Destroyer","Submarine","Cruiser","Battleship","Carrier" };
	int shipsLeft = ships;

	char board[ROWS][COLUMNS] = {	{ ' ',  '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9', '0'  },
									{ 'A',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'B',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'C',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'D',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'E',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'F',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'G',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'H',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'I',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' },
									{ 'J',  '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' , '~' } };

	//could these boards be their own function to use repeatedly? pretty sure we will need a third board.
	
	char shipsPlaced[ROWS][COLUMNS] = {		{ ' ',  '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9', '0'  },
											{ 'A',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'B',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'C',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'D',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'E',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'F',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'G',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'H',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'I',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' },
											{ 'J',  'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' } };




	//come back to this if i can figure out the position marker.
	//Still want to try to make this go back and forth like a real battleship game, player one goes then player two for placing ships and taking turns.
	//work on player 2 after player one is fully working, will be easier. Erik 11/15/2017

	//for (int x = 0; x < 2; x++)
	//{
	//	if (x == 0)
	//	{
	//		PlayerX = "One ";
	//	}
	//	else if (x == 1)
	//	{
	//		PlayerX = "Two ";
	//	}
	//	cout << "Enter your positions player " << PlayerX;
	//	Sleep(3000);
	//	system("cls");
	//	board_intilization();
	//}






	//Player One
	
	//another loop surronding all this for shipName[ships] until all ships are placed on the board.
	for (int count = 0; count < ships; count++)
	{
		if (count == 0)
		{

			firstCoord(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipsPlaced);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
			//destroyer(spaceOneNum, spaceTwo); // idea to break this up so that each ship has its own function...
			//if this doesnt work break the if else chain keep the functions within this, 'for loop'.
		}
		else if (count == 1)
		{
			firstCoord(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipsPlaced);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);

		}
		else if (count == 2)
		{
			firstCoord(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipsPlaced);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);

		}
		else if (count == 3)
		{
			firstCoord(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipsPlaced);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);

		}
		else if (count == 4)
		{
			firstCoord(spaceOne, spaceOneNum, promptCheck, shipName, count, board, shipsPlaced); // count and ships could go into here to move the cout prompt down?
			secCoord(spaceTwo, promptCheck, board, shipsPlaced);


			setPos(spaceOneNum, spaceTwo, count, destroy1, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy, board);
			cout << endl << endl;
			refresh(spaceOneNum, board, shipsPlaced, spaceTwo, destroy1, count, userDirectionalInput, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);

		}
		//replacing the shipsplaced on to the board making it visible to player one to see where their placed.
		//This does not update with every placed ship though. perhaps make this a function. Erik - 11/15/2017
		//maybe can use board intilization to refresh. what the board looks like, from placement to placement.
		
		
	}
	system("cls");
	displayBlank(board);


	
	





}


void firstCoord(char spaceOne, int &spaceOneNum, bool &promptCheck, string shipName[], int &count, char board[][11], char shipsPlaced[][11])
{
	//variables
	const int ROWS = 11;
	char letter = 'a';
	char cLETTER = 'A';
	


	do
	{
		//board_intilization(spaceOneNum, spaceTwo);
		system("cls");
		displayBlank(board);
		cout << endl;
		cout << white << setw(55) << "Player one, enter coordinates for the " << shipName[count] << endl;
		cout << setw(75) << white << "Using letters A-J, and then a number 1-10, enter your coordinates: ";
		cin >> spaceOne;

		//check to see if input is a-j or A-J before sending it on.
		if ((spaceOne >= 'a' && spaceOne <= 'j') || (spaceOne >= 'A' && spaceOne <= 'J'))
		{
			promptCheck = true;



		}
		else
		{
			cout << endl;
			cout << setw(74) << red << "=========================================================" << endl;
			cout << setw(75) << "This is not a valid input. Try again, using a letter a-j. " << endl;
			cout << setw(74) << "=========================================================" << endl;
			Sleep(1500);
			system("cls");

		}
	} while (promptCheck == false);


	//talking about the loop below not above.
	//Now this loops through ROWS which is not dynamic at the moment, with the function 
	//in board_intilization(); so if we change one manually has to do both inless
	//we change board_intilization(); from a void into an int and carry it over; or use &

	//'i' will cycle through the number of rows, and increment i, i will only add
	//to spaceonenum if the letter equals spaceOne. should catch before hand if
	//their is a letter that is not a-j before here. adding +1 to i as my board
	// will be including A-J and the 1-9 will also carry a plus 1; oh and 0 == 10 inless
	// we can figure out a way to implement that char into a string? to carry more than one value.




	for (int i = 0; i < ROWS; i++) //once a char has been chosen highlight it another color to help the user see the change on the board? cyan > red?
	{
		if ((spaceOne == letter) || (spaceOne == cLETTER))
		{
			spaceOneNum = (i + 1);
		}
		letter++;
		cLETTER++;
	}

	//cout << spaceOneNum; //testing to see if it counts right.

}

void secCoord(int &spaceTwo, bool &promptCheck, char board[][11], char shipsPlaced[][11])
{

	promptCheck = false;
	while (!promptCheck)
	{
		system("cls");
		//board_intilization(spaceOneNum, spaceTwo);
		displayBlank(board);
		cout << endl;
		cout << setw(60) << white << "Using numbers 1-10, enter your second coordinate: ";
		cin >> spaceTwo;

		if (spaceTwo >= 1 && spaceTwo <= 10)
		{
			promptCheck = true;
			spaceTwo = (spaceTwo); //In order for the board to be user friendly, the user inputs 1, but the array is read at position 0.
									   //need to check if the negative -1 still works. E. 11/13/17 on my board.

		}
		else
		{
			cout << endl;
			cout << setw(75) << red << "============================================================" << endl;
			cout << setw(75) << "This is not a valid input. Try again, using the numbers 1-10." << endl;
			cout << setw(75) << "============================================================" << endl;
			//cout << setw(60) << white << "Using numbers 1-10, enter your second coordinate: ";
			cout << endl;
			Sleep(1500);
			system("cls");

		}

	}
	promptCheck = false;

	

}

void displayBlank(char board[][11])
{
	//Erik 11/13/17
	//dragging variables down from, board_intilization(); uncertain when calling the 
	//function to put things inside of it when I dont want to use it inside that function 
	//but just send stuff will do something I do not want it to do. will expirment more with this later.
	string div = "===============================================================================================================";
	string between = "---------------------------------------------------------------------------------------------------------------";
	const int ROWS = 11;
	const int COLUMNS = 11;

	cout << setw(115) << darkgrey << div << endl; // divider ' === '
	for (int i = 0; i < ROWS; i++)
	{
		cout << darkgrey << setw(5) << "|";
		for (int s = 0; s < COLUMNS; s++)
		{
			//if else added by Tristan to make our X equal red.
			if (board[i][s] == 'X')
			{
				cout << setw(5) << red << board[i][s] << setw(5) << darkgrey << "|";
			}
			else
			{
				cout << setw(5) << cyan << board[i][s] << setw(5) << darkgrey << "|";
			}
		}
		if (i != ROWS - 1)
		{
			cout << endl << setw(115) << between << endl;
		}
		else
		{
			cout << endl;
		}
	}
	cout << setw(115) << darkgrey << div << endl;


}

void setPos(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, string &userDirectionalInput, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy, char board[][11]) // board
{
	system("cls");
	displayBlank(board);
	cout << setw(65) << white << "How would you like to place your ship: (Up, Down, Left or Right) " << endl;
	cin >> userDirectionalInput;
	//getline(cin, userDirectionalInput);
	//system("pause");
	//get( userDirectionalInput);

	//would like to get, wasd, arrow keys or numpad to correspond with this instead of typing in the direction. Erik, 11/15/2017

	if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
	{
		up(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);

	}
	else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
	{
		down(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);
	}
	else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
	{
		left(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);

	}
	else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
	{
		right(spaceOneNum, spaceTwo, count, destroy1, sub1, sub2, cruis1, cruis2, battleship1, battleship2, battleship3, carrier1, carrier2, carrier3, carrier4, sub, cruis, battleship, carrier, destroy);

	}
	else
	{
		//need to test if setw is correct still.
		cout << setw(65) << red << "--------------------------" << endl;
		cout << setw(65) << "Invalid input. Try again." << endl;
		cout << setw(65) << "--------------------------" << endl;
	}


}

void up(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{
	
	//put a check in the directionals to decide if its overlapping ships / board?

	if (count == 0) // 0 is the destroyer, 2 spots
	{
		destroy = spaceOneNum;
		destroy1 = (spaceOneNum - 1);   // may be prudent to make an additional variable since spaceOneNum will rewrite all the time. like..
										// destroy = spaceOneNum;   Erik 11/15/17
	}
	else if (count == 1) // 1 is the submarine, 3 spots
	{
		sub = spaceOneNum;
		sub1 = (spaceOneNum - 1);
		sub2 = (spaceOneNum - 2);

	}
	else if (count == 2) // 2 is the cruiser, 3 spots
	{
		cruis = spaceOneNum;
		cruis1 = (spaceOneNum - 1);
		cruis2 = (spaceOneNum - 2);
	}
	else if (count == 3) // 3 is the battleship, 4 spots
	{
		battleship = spaceOneNum;
		battleship1 = (spaceOneNum - 1);
		battleship2 = (spaceOneNum - 2);
		battleship3 = (spaceOneNum - 3);

	}
	else if (count == 4) // 4 is the airship carrier, 5 spots
	{
		carrier = spaceOneNum;
		carrier1 = (spaceOneNum - 1);
		carrier2 = (spaceOneNum - 2);
		carrier3 = (spaceOneNum - 3);
		carrier4 = (spaceOneNum - 4);

	}

}

void down(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{
	


	if (count == 0) // 0 is the destroyer
	{
		destroy = spaceOneNum;
		destroy1 = (spaceOneNum + 1);
	}
	else if (count == 1) // 1 is the submarine
	{
		sub = spaceOneNum;
		sub1 = (spaceOneNum + 1);
		sub2 = (spaceOneNum + 2);

	}
	else if (count == 2) // 2 is the cruiser
	{
		cruis = spaceOneNum;
		cruis1 = (spaceOneNum + 1);
		cruis2 = (spaceOneNum + 2);

	}
	else if (count == 3) // 3 is the battleship
	{
		battleship = spaceOneNum;
		battleship1 = (spaceOneNum + 1);
		battleship2 = (spaceOneNum + 2);
		battleship3 = (spaceOneNum + 3);

	}
	else if (count == 4) // 4 is the airship carrier
	{
		carrier = spaceOneNum;
		carrier1 = (spaceOneNum + 1);
		carrier2 = (spaceOneNum + 2);
		carrier3 = (spaceOneNum + 3);
		carrier4 = (spaceOneNum + 4);

	}

}

void left(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{
	

	if (count == 0) // 0 is the destroyer
	{
		destroy = spaceTwo;
		destroy1 = (spaceTwo - 1);
	}
	else if (count == 1) // 1 is the submarine
	{
		sub = spaceTwo;
		sub1 = (spaceTwo - 1);
		sub2 = (spaceTwo - 2);

	}
	else if (count == 2) // 2 is the cruiser
	{
		cruis = spaceTwo;
		cruis1 = (spaceTwo - 1);
		cruis2 = (spaceTwo - 2);

	}
	else if (count == 3) // 3 is the battleship
	{
		battleship = spaceTwo;
		battleship1 = (spaceTwo - 1);
		battleship2 = (spaceTwo - 2);
		battleship3 = (spaceTwo - 3);

	}
	else if (count == 4) // 4 is the airship carrier
	{
		carrier = spaceTwo;
		carrier1 = (spaceTwo - 1);
		carrier2 = (spaceTwo - 2);
		carrier3 = (spaceTwo - 3);
		carrier4 = (spaceTwo - 4);

	}

}

void right(int &spaceOneNum, int &spaceTwo, int &count, int &destroy1, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{
	

	if (count == 0) // 0 is the destroyer
	{
		destroy = spaceTwo;
		destroy1 = (spaceTwo + 1);
	}
	else if (count == 1) // 1 is the submarine
	{
		sub = spaceTwo;
		sub1 = (spaceTwo + 1);
		sub2 = (spaceTwo + 2);

	}
	else if (count == 2) // 2 is the cruiser
	{
		cruis = spaceTwo;
		cruis1 = (spaceTwo + 1);
		cruis2 = (spaceTwo + 2);

	}
	else if (count == 3) // 3 is the battleship
	{
		battleship = spaceTwo;
		battleship1 = (spaceTwo + 1);
		battleship2 = (spaceTwo + 2);
		battleship3 = (spaceTwo + 3);

	}
	else if (count == 4) // 4 is the airship carrier
	{
		carrier = spaceTwo;
		carrier1 = (spaceTwo + 1);
		carrier2 = (spaceTwo + 2);
		carrier3 = (spaceTwo + 3);
		carrier4 = (spaceTwo + 4);

	}

}


void refresh(int &spaceOneNum, char board[][11], char shipsPlaced[][11], int &spaceTwo, int &destroy1, int &count, string &userDirectionalInput, int &sub1, int &sub2, int &cruis1, int &cruis2, int &battleship1, int &battleship2, int &battleship3, int &carrier1, int &carrier2, int &carrier3, int &carrier4, int &sub, int &cruis, int &battleship, int &carrier, int &destroy)
{
	const int ROWS = 11;
	const int COLUMNS = 11;

	for (int rows = 0; rows < ROWS; rows++)
	{

		for (int cols = 0; cols < COLUMNS; cols++)
		{
			//initial ship placement idea by Tristan
			//board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][spaceTwo];


			if (count == 0) // 0 is the destroyer, 2 spots
			{
				
				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[destroy][spaceTwo];
					board[destroy1][spaceTwo] = shipsPlaced[destroy1][spaceTwo];

				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[destroy][spaceTwo];
					board[destroy1][spaceTwo] = shipsPlaced[destroy1][spaceTwo];

				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][destroy];
					board[spaceOneNum][destroy1] = shipsPlaced[spaceOneNum][destroy1];

				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][destroy];
					board[spaceOneNum][destroy1] = shipsPlaced[spaceOneNum][destroy1];

				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}


			}
			else if (count == 1) // 1 is the submarine, 3 spots
			{
				//what if the board isnt updating the position of the ship because spaceonenum / space two arent updating to the right number..

				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[sub][spaceTwo];
					board[sub1][spaceTwo] = shipsPlaced[sub1][spaceTwo];
					board[sub2][spaceTwo] = shipsPlaced[sub2][spaceTwo];

				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[sub][spaceTwo];
					board[sub1][spaceTwo] = shipsPlaced[sub1][spaceTwo];
					board[sub2][spaceTwo] = shipsPlaced[sub2][spaceTwo];

				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][sub];
					board[spaceOneNum][sub1] = shipsPlaced[spaceOneNum][sub1];
					board[spaceOneNum][sub2] = shipsPlaced[spaceOneNum][sub2];

				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][sub];
					board[spaceOneNum][sub1] = shipsPlaced[spaceOneNum][sub1];
					board[spaceOneNum][sub2] = shipsPlaced[spaceOneNum][sub2];

				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}
			else if (count == 2) // 2 is the cruiser, 3 spots
			{

				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[cruis][spaceTwo];
					board[cruis1][spaceTwo] = shipsPlaced[cruis1][spaceTwo];
					board[cruis2][spaceTwo] = shipsPlaced[cruis2][spaceTwo];

				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[cruis][spaceTwo];
					board[cruis1][spaceTwo] = shipsPlaced[cruis1][spaceTwo];
					board[cruis2][spaceTwo] = shipsPlaced[cruis2][spaceTwo];

				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{

					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][cruis];
					board[spaceOneNum][cruis1] = shipsPlaced[spaceOneNum][cruis1];
					board[spaceOneNum][cruis2] = shipsPlaced[spaceOneNum][cruis2];

				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{

					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][cruis];
					board[spaceOneNum][cruis1] = shipsPlaced[spaceOneNum][cruis1];
					board[spaceOneNum][cruis2] = shipsPlaced[spaceOneNum][cruis2];

				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}
			else if (count == 3) // 3 is the battleship, 4 spots
			{

				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[battleship][spaceTwo];
					board[battleship1][spaceTwo] = shipsPlaced[battleship1][spaceTwo];
					board[battleship2][spaceTwo] = shipsPlaced[battleship2][spaceTwo];
					board[battleship3][spaceTwo] = shipsPlaced[battleship3][spaceTwo];

				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{
					board[spaceOneNum][spaceTwo] = shipsPlaced[battleship][spaceTwo];
					board[battleship1][spaceTwo] = shipsPlaced[battleship1][spaceTwo];
					board[battleship2][spaceTwo] = shipsPlaced[battleship2][spaceTwo];
					board[battleship3][spaceTwo] = shipsPlaced[battleship3][spaceTwo];

				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{

					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][battleship];
					board[spaceOneNum][battleship1] = shipsPlaced[spaceOneNum][battleship1];
					board[spaceOneNum][battleship2] = shipsPlaced[spaceOneNum][battleship2];
					board[spaceOneNum][battleship3] = shipsPlaced[spaceOneNum][battleship3];

				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{

					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][battleship];
					board[spaceOneNum][battleship1] = shipsPlaced[spaceOneNum][battleship1];
					board[spaceOneNum][battleship2] = shipsPlaced[spaceOneNum][battleship2];
					board[spaceOneNum][battleship3] = shipsPlaced[spaceOneNum][battleship3];

				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}
			else if (count == 4) // 4 is the airship carrier, 5 spots
			{

				if (userDirectionalInput == "up" || userDirectionalInput == "UP" || userDirectionalInput == "Up")
				{

					board[spaceOneNum][spaceTwo] = shipsPlaced[carrier][spaceTwo];
					board[carrier1][spaceTwo] = shipsPlaced[carrier1][spaceTwo];
					board[carrier2][spaceTwo] = shipsPlaced[carrier2][spaceTwo];
					board[carrier3][spaceTwo] = shipsPlaced[carrier3][spaceTwo];
					board[carrier4][spaceTwo] = shipsPlaced[carrier4][spaceTwo];

				}
				else if (userDirectionalInput == "down" || userDirectionalInput == "DOWN" || userDirectionalInput == "Down")
				{

					board[spaceOneNum][spaceTwo] = shipsPlaced[carrier][spaceTwo];
					board[carrier1][spaceTwo] = shipsPlaced[carrier1][spaceTwo];
					board[carrier2][spaceTwo] = shipsPlaced[carrier2][spaceTwo];
					board[carrier3][spaceTwo] = shipsPlaced[carrier3][spaceTwo];
					board[carrier4][spaceTwo] = shipsPlaced[carrier4][spaceTwo];
				}
				else if (userDirectionalInput == "left" || userDirectionalInput == "LEFT" || userDirectionalInput == "Left")
				{

					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][carrier];
					board[spaceOneNum][carrier1] = shipsPlaced[spaceOneNum][carrier1];
					board[spaceOneNum][carrier2] = shipsPlaced[spaceOneNum][carrier2];
					board[spaceOneNum][carrier3] = shipsPlaced[spaceOneNum][carrier3];
					board[spaceOneNum][carrier4] = shipsPlaced[spaceOneNum][carrier4];

				}
				else if (userDirectionalInput == "right" || userDirectionalInput == "RIGHT" || userDirectionalInput == "Right")
				{

					board[spaceOneNum][spaceTwo] = shipsPlaced[spaceOneNum][carrier];
					board[spaceOneNum][carrier1] = shipsPlaced[spaceOneNum][carrier1];
					board[spaceOneNum][carrier2] = shipsPlaced[spaceOneNum][carrier2];
					board[spaceOneNum][carrier3] = shipsPlaced[spaceOneNum][carrier3];
					board[spaceOneNum][carrier4] = shipsPlaced[spaceOneNum][carrier4];

				}
				else
				{
					//need to test if setw is correct still.
					cout << setw(65) << red << "--------------------------" << endl;
					cout << setw(65) << "Invalid input. Try again." << endl;
					cout << setw(65) << "--------------------------" << endl;
				}

			}













				

		}

	}

}

//Erik
void destroyer()
{


}

//chuck
void sound()
{


}



//Erik 11/13/17
//           ascii art place holder until we get to it.
//if things look off center its because \\ is required for one 
//backslash to be recognized in cout. if things are not lining 
//up in the command prompt it may be because i missed a backslash
//game over / you won! with x amount of shots left. time left? or with a total time.

/*ship blows up use this,
 red and orange black/grey

             \\         .  ./
          \\      .:";'.:.."   /
                (M^^.^~~:.'").
          -   (/  .    . . \\ \\)  -
             ((| :. ~ ^  :. .|))
          -   (\\- |  \\ /  |  /)  -
               -\\  \\     /  /-
                 \\  \\   /  /
//Made with the help of this site, SOURCE:	 http://www.chris.com/ascii/index.php?art=objects/explosives
				 
				 */



/* when shot was missed trigger this
green?
  __  __ ___ ____ ____  _ 
 |  \\/  |_ _/ ___/ ___|| |
 | |\\/| || |\\___ \\___ \\| |
 | |  | || | ___) |__) |_|
 |_|  |_|___|____/____/(_)
 //Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php

*/


/*
when you get a hit
red on the flames, green on text

  *   )                            )     (                                     (     
` )  /(    )  (    (  (     (   ( /(     )\\           (     (   (   (      (   )\\ )  
 ( )(_))( /(  )(   )\\))(   ))\\  )\\()) ((((_)(   (   ( )\\   ))\\  )\\  )(    ))\\ (()/(  
(_(_()) )(_))(()\\ ((_))\\  /((_)(_))/   )\\ _ )\\  )\\  )(( ) /((_)((_)(()\\  /((_) ((_)) 
|_   _|((_)_  ((_) (()(_)(_))  | |_    (_)_\\(_)((_)((_)_)(_))(  (_) ((_)(_))   _| |  
  | |  / _` || '_|/ _` | / -_) |  _|    / _ \\ / _| / _` || || | | || '_|/ -_)/ _` |  
  |_|  \\__,_||_|  \\__, | \\___|  \\__|   /_/ \\_\\\\__| \\__, | \\_,_| |_||_|  \\___|\\__,_|  
                  |___/                               |_|                            
 //Made with the help of this ascii text to art generator SOURCE: http://www.kammerl.de/ascii/AsciiSignature.php



*/