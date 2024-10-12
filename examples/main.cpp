#include "SDL2/SDL.h"
#include <iostream>
#include "SDL2Example.h"


int main() {

    SDL_Init(SDL_INIT_EVERYTHING);
	SDL2Example ex;

	while(!ex.isRunning){
		SDL_Delay(10);
	}
	while (ex.isRunning) {
		SDL_Delay(10);
		ex.update();
		ex.render();
	}

	cout<<"quitting...\n";
	SDL_Quit();	

}