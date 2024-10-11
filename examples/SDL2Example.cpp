#include "SDL2Example.h"

SDL2Example::SDL2Example() {
	this->initVars();
	this->initWindow();
}

SDL2Example::~SDL2Example() {
}

void SDL2Example::initWindow()
{
	window = SDL_CreateWindow( "SDL2 Hex Map Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	textureMap["flat"] = IMG_LoadTexture(renderer, "assets/hexagonFlat.png");
	textureMap["pointy"] = IMG_LoadTexture(renderer, "assets/hexagonPointy.png");

	hexMap->loadAround(0, 0, 5);
	
	hexMap->sortTileList();

	isLoaded = true;
}

void SDL2Example::initVars()
{
	windowHeight = 720;
	windowWidth = 1280;
	tileTargetedByMouse = NULL;
	hexMap = new HexMap(785, true);
	hexMap->deafultTexture = "flat";
	//hexMap = new HexMap(680, false);
}

void SDL2Example::update()
{
	if(!isLoaded)
		return;

	//check to see if mouse moved since last frame

	int newMouseX; int newMouseY;
	SDL_GetMouseState(&newMouseX,&newMouseY);

	Tile* e = getTileAtXY(newMouseX, newMouseY);

	if(tileTargetedByMouse != e && tileTargetedByMouse != NULL)
		tileTargetedByMouse->onExit(tileTargetedByMouse);

	if(tileTargetedByMouse != e && e != NULL)
		e->onEnter(e);
	
	tileTargetedByMouse = e;

	while (SDL_PollEvent(&ev))
		switch (ev.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_MOUSEBUTTONUP:
			//Left button released
			if(ev.button.button == SDL_BUTTON_LEFT){
				if(tileTargetedByMouse != NULL)
					tileTargetedByMouse->onLClick(tileTargetedByMouse);
			}
			//Right button released
			if(ev.button.button == SDL_BUTTON_RIGHT){
				if(tileTargetedByMouse != NULL)
					tileTargetedByMouse->onRClick(tileTargetedByMouse);
			}

			break;

		default:
			break;
	}
}

void SDL2Example::render()
{
	if(!isLoaded)
		return;

	SDL_RenderClear(renderer);

	std::list<Tile*>::iterator i;
	for (i = hexMap->loadedTiles.begin(); i !=  hexMap->loadedTiles.end(); ++i){
		std::pair<int, int> XY = hexMap->rqTOxy(((Tile*)(*i))->r, ((Tile*)(*i))->q);
		SDL_Rect frame;
		frame.x = XY.first;
		frame.y = XY.second;
		SDL_Point size;
    	SDL_QueryTexture(textureMap[((Tile*)(*i))->texture], NULL, NULL, &size.x, &size.y);
		frame.w = size.x;
		frame.h = size.y;
		SDL_SetTextureColorMod(textureMap[((Tile*)(*i))->texture], ((Tile*)(*i))->textureColor[0],((Tile*)(*i))->textureColor[1], ((Tile*)(*i))->textureColor[2]);
		SDL_RenderCopy(renderer, textureMap[((Tile*)(*i))->texture], NULL, &frame);
		SDL_SetTextureColorMod(textureMap[((Tile*)(*i))->texture], 255, 255, 255);
	}

	SDL_RenderPresent(renderer);
}

Tile* SDL2Example::getTileAtXY(int x, int y) {
	for (std::list<Tile*>::reverse_iterator i = hexMap->loadedTiles.rbegin(); i != hexMap->loadedTiles.rend(); ++i)
		if (hexMap->isPointWithinTile(x,y,((Tile*)(*i))))
			return ((Tile*)(*i));
	return NULL;
}
