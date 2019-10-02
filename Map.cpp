/*
Created by Parker Evans on 9/19
with the help of Skyler Clark 

This is the map file we are creating a char array to fill all of the field with an '*' and then when explored to a 'space'


*/

#include "Structs_and_enum.h"
#include "Hero.h"
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

/*******************TODO***********************
Make printArray put 'H' for where hero currently is? Should be doable without creating another enum.

***********************************************/

/*
Here we created the map as a global two dimensional array, since we will never change its size.
*/
int map [30][10];
enum tile_type entrance = 	ENTRANCE;
enum tile_type end = 		END;
enum tile_type spike_trap = 	SPIKE_TRAP;
enum tile_type spike_trap_ex = 	SPIKE_TRAP_EX;
enum tile_type qs_trap = 	QS_TRAP;
enum tile_type qs_trap_ex = 	QS_TRAP_EX;
enum tile_type insult_trap = 	INSULT_TRAP;
enum tile_type insult_trap_ex = INSULT_TRAP_EX;
enum tile_type good_potion = 	GOOD_POTION;
enum tile_type good_potion_ex = GOOD_POTION_EX;
enum tile_type bad_potion = 	BAD_POTION;
enum tile_type bad_potion_ex = 	BAD_POTION_EX;
enum tile_type empty = 		EMPTY;
enum tile_type empty_ex = 	EMPTY_EX;

//generates unbiased random number between specified range
// int randomInt(int x, int y)
// {
	// srand(time(NULL));  // was commented out before
	// std::random_device rd;
	// std::mt19937 eng(rd());
	// std::uniform_int_distribution<> uni(x,y);
	// return uni(eng);
// }

int randomInt(int x){
	return (int)rand()%x;	
}
//fills array first with blanks, then with randomized special tiles, then creates static entrance and exit
void fillArray()
{
	//fill entire array with empty tiles
	for(int i = 0; i < 30; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			map[i][j] = empty;
		}
	}

	for(int i = 0; i < 30; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			//random column to fill, up to 5 special tiles per row, limits unbeatable maps
			int col = randomInt(10);		
			
			//generate random 'trap' tile to place
			int r = randomInt(5);
			if(r == 0){map[i][col] = spike_trap;}
			if(r == 1){map[i][col] = qs_trap;}
			if(r == 2){map[i][col] = insult_trap;}
			if(r == 3){map[i][col] = good_potion;}
			if(r == 4){map[i][col] = bad_potion;}
		}
	}
	//place entrance and exit
	map[0][0] = entrance;
	map[29][9] = end;
}

/*
Here we are creating the explored room method of change the tile. Need to add change of status to tiles.
*/
void found_empty(hero h){
	std:: cout<<"Just another empty room, that's good right?"<<std::endl;
	map[h.y][h.x] = empty_ex;	// This is a space for empty
}

hero found_spike(hero h){
	
	if(h.name == "Indiana"){
		if(randomInt(10)>4){
			std::cout << "Indiana Jones uses his rope to swing to safety"<<std::endl;
			return h;
	}
	int rint = rand()%10+1;
	
	std::cout<<"You fell into a spike trap! You lost " << rint << " hit points."<<std::endl;
	map[h.y][h.x] = spike_trap_ex;	 // This is a carrot for spike
	h.health-=rint;
	h = take_damage(h);
	
	return h;
}

hero found_qs(hero h){
	if(h.name == "Indiana"){
		if(randomInt(10)>4){
			std::cout << "Indiana Jones graps a snake to climb out of the sand."<<std::endl;
			return h;
	}
	int health_before = h.health;	
	std::cout<<"Quick Sand! Quickly Type your hero's first name!"<<std::endl;
	std::string s1;
		
	double temp;	
	clock_t time_start;
	time_start = clock();
		
	while(s1!=h.name){
	std::cin>>s1;
	}
	temp = (clock()-time_start)/1000;
	h.health-=temp;
	std::cout << "You lost " << health_before - h.health << " hit points.\n";
	map[h.y][h.x] = qs_trap_ex;	// This is an exclamation mark
	return take_damage(h);			// come back and change
}

void found_insult(hero h){
	std:: cout<< "A voice from the dungeon taunts you...\n"<<std::endl;
	int r = randomInt(20);
	switch(r){
		case 0: std::cout<< "Your Mom goes to college"<<std::endl; break;
		case 1: std::cout<< "First Time visiting a dungeon, isn't it?"<<std::endl; break;
		case 2: std::cout<< "You don't even go here!"<<std::endl; break;
		case 3: std::cout<< "You probably dropped out!"<<std::endl; break;
		case 4: std::cout<< "Nice shoes... is that what heroes are wearing these days?"<<std::endl; break;
		case 5: std::cout<< "Where'd you get that cape? Walmart?"<<std::endl; break;
		case 6: std::cout<< "Rocks are your only friends."<<std::endl; break;
		case 7: std::cout<< "Dishonor on you, dishonor on your cow, dishonor on your whole family!"<<std::endl; break;
		case 8: std::cout<< "I'm surrounded by idiots."<<std::endl; break;
		case 9: std::cout<< "You clinking, clanking, clattering collection of caliginous junk!"<<std::endl; break;
		case 10: std::cout<< "Let me guess, you have a GREAT personality."<<std::endl; break;
		case 11: std::cout<< "You are a sad strange little man"<<std::endl; break;
		case 12: std::cout<< "To call you stupid would be an insult to stupid people!"<<std::endl; break;
		case 13: std::cout<< "You have no enemies, but are intensely disliked by your friends."<<std::endl; break;
		case 14: std::cout<< "Sharp as a marble you are."<<std::endl; break;
		case 15: std::cout<< "Hahahahahahaha... have you seen your face!"<<std::endl; break;
		case 16: std::cout<< "Scientists say the universe is made up of neutrons, protons and electrons. They forgot to mention morons."<<std::endl; break;
		case 17: std::cout<< "Someday you’ll go far… and I hope you stay there."<<std::endl; break;
		case 18: std::cout<< "If I was stuck in a room with you, Hitler, Bin Laden and a gun with 2 bullets... I'd shoot you twice.\n"; break;
		case 19: std::cout<< "That's okay, I remember my first time playing a video game too.\n"; break;
		case 20: std::cout<< "I fart in your general direction.\n"; break;
		default: std::cout<< "You're weird"<<std::endl;
	}
	
	
	map[h.y][h.x] = insult_trap_ex;	// This is the question mark
}
hero found_good_potion(hero h){
	int health_before = h.health;
	h = gain_health(h);
	std:: cout << "A health potion! You gained " << h.health - health_before << " hit points.  Phew... That was needed."<< std:: endl;
	map[h.y][h.x] = good_potion_ex;	// This is the plus signal
	return h;
}

hero found_bad_potion(hero h){
	std:: cout << "You suddenly feel really dizzy... is up still up?"<< std::endl;
	map[h.y][h.x] = bad_potion_ex; // This is the asterix
	return confuse(h);
}

void set_entrance(){
	map[0][0] = 91; // This is the open bracket for the start space
}

// Parker: I have written up the code for printing the array. Here we are
// using the various ASCII codes to print characters to the array where the 
// enum type corresponds.
void print_array(hero h){
	for(int i=0;i<30;i++){
		for(int j = 0; j<10;j++){
			if(i == h.y && j == h.x){
				std::cout<<"H";
				continue;
			}
			if(map[i][j] <= 5){
				std::cout << char(35);
			}
			if(map[i][j] == 6){
				std::cout<<char(94);
			}
			if(map[i][j] == 7){
				std::cout<< char(33);
			}
			if(map[i][j] == 8){
				std::cout<<char(63);
			}
			if(map[i][j] == 9){
				std::cout<<char(43);
			}
			if(map[i][j] == 10){
				std::cout<<char(42);
			}
			if(map[i][j] == 11){
				std::cout<< char(32);
			}
			if(map[i][j] == 12){
				std::cout<<char(123);
			}
			if(map[i][j] == 13){
				std::cout<<"E";
			}
			
			
		}
		std::cout<<" "<< std::endl;
	}
	
}

int get_tile(hero h)
{
	return map[h.y][h.x];
}
