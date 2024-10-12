#pragma once
#include <string>
#include <cstdint>

class Tile
{
public:
	// Unique id of a Tile
	int id;

	// If true, is visible to mouse events
	bool isTargetable;

	// Axial Q coordinate of the tile
	int q; 

	// Axial R coordinate of the tile
	int r;


	int h;

	const char* texture;

	uint8_t textureColor[3];

	bool (*onLClick)(Tile*);
	bool (*onRClick)(Tile*);
    bool (*onEnter)(Tile*);
    bool (*onExit)(Tile*);

	// Default costructor
	// r and q for the axial coordinates
	// Texture = name of the texture you will later use to render this tile
	Tile(int r, int q, const char* texture);

	// Default destructor
	virtual ~Tile();

	// Returns the X position of the texture translation pivot
	int pivotX();

	// Returns the Y position of the texture translation pivot
	int pivotY();

	bool operator == (const Tile& s) const { return id == s.id; };



private:

	// A simple ticker to facilitate assignment of unique tags to Tiles.
	// ++ whenever a new object is created
	inline static int currentGlobalTagTicker = 0;

	static bool onLeftClickDefault(Tile* Tile);
	static bool onRightClickDefault(Tile* Tile);
	static bool onEnterDefault(Tile* Tile);
	static bool onExitDefault(Tile* Tile);

};

