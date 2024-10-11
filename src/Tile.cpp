#include "Tile.h"
#include <iostream>


Tile::Tile(int R, int Q, std::string animationTag){
	id = currentGlobalTagTicker++;

	isTargetable = true;

    this->q = Q;
    this->r = R;
    h = 0;

	textureColor[0] = 255;	//Red
	textureColor[1] = 255;	//Green
	textureColor[2] = 255;	//Blue

	this->onLClick = onLeftClickDefault;
	this->onRClick = onRightClickDefault;
    this->onEnter = onEnterDefault;
    this->onExit = onExitDefault;
}

Tile::~Tile(){
	// default destructor
}

bool Tile::onLeftClickDefault(Tile* Tile){
	std::cout << "Lclicked: " << Tile->r << " " << Tile->q << "\n";
	return true;
}

bool Tile::onRightClickDefault(Tile* Tile){
	std::cout << "Rclicked: " << Tile->r << " " << Tile->q << "\n";
	return true;
}

bool Tile::onEnterDefault(Tile* Tile){
	// lower texture brightness whenever a cursor enters a tile
	Tile->textureColor[0] = 200;
	Tile->textureColor[1] = 200;
	Tile->textureColor[2] = 200;
	return true;
}

bool Tile::onExitDefault(Tile* Tile){
	// bring back texture brightness whenever a cursor leaves a tile
	Tile->textureColor[0] = 255;
	Tile->textureColor[1] = 255;
	Tile->textureColor[2] = 255;
	return true;
}
