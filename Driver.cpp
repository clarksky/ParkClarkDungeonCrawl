/***************************************

Project: Dungeon Crawl
Authors: Parker Evans and Skyler Clark
Class:	 CS 3150
Date: 	 21-Sep-2019

***************************************/
#include "Structs_and_enum.h"
#include "Map.h"
#include "Hero.h"
#include <iostream>

int main()
{
	hero h;
	h = hero_select();
	print_array(h);
	return 0;
}
