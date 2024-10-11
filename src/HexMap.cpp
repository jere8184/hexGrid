#include "HexMap.h"

HexMap::HexMap(uint32_t TileWidth, bool mapMd){
    this->mapMode = mapMd;
    this->width = TileWidth;
    if(mapMd){
        this->size = TileWidth/2.;
    } else {
        this->size = TileWidth/sqrt3;
    }
}

HexMap::~HexMap(){
    clearMap();
}

void HexMap::loadAround(int rc, int qc, uint32_t radius){
    for(int r = -radius; r <= 0; r++)
        for(int q = -radius - r; q <= radius; q++){
            if(!isTileLoaded(rc+r, qc+q))
                spawnTile(rc+r, qc+q);
        }
        
    for(int r = 1; r <= radius; r++)
        for(int q = -radius; q <= radius - r; q++){
            if(!isTileLoaded(rc+r, qc+q))
                spawnTile(rc+r, qc+q);
        }
}


void HexMap::unloadAround(int rc, int qc, uint32_t radius){
    std::list<Tile*>::iterator i = loadedTiles.begin();
    while (i != loadedTiles.end())
    {
    if (axialDistance(rc, qc, ((Tile*)(*i))->r, ((Tile*)(*i))->q) > radius)
        deleteTile((Tile*)(*(i++)));
    else
        ++i;
    }
}

void HexMap::clearMap(){
     while(loadedTiles.size()){
        delete(loadedTiles.front());
        loadedTiles.pop_front();
    }
}

Tile* HexMap::getTileAtRQ(int r, int q){
    std::list<Tile*>::iterator i = loadedTiles.begin();
    while (i != loadedTiles.end()){
        if (r == ((Tile*)(*i))->r && q == ((Tile*)(*i))->q)
            return (Tile*)(*i);
        ++i;
    }
    return NULL;
}

std::pair<int, int> HexMap::rqTOxy(int r, int q) {
	return std::pair(size*(3. / 2 * q), size * (sqrt3 / 2 * q + sqrt3 * r ));
}

bool HexMap::isPointWithinTile(int x, int y, Tile* tile) {
    std::pair<int, int> pos = rqTOxy(tile->r, tile->q);

	if (x < pos.first || x > pos.first + width)
		return false;

	if (y < pos.second)
		return false;

	if (y < pos.second + width*0.22)
		if (x < pos.first + width*0.22 && (y - pos.second) + (x - pos.first) < width*0.22 )
			return false;
		else if (x > pos.first + (width - width*0.22)  && (y - pos.second) + (width + pos.first - x) < width*0.22)
			return false;

	return true;
}


Tile* HexMap::spawnTile(int r, int q){
    Tile* tile = new Tile(r, q, determineTextureAt(r,q));
    tile->r = r;
    tile->q = q;
    tile->h = determineHeightAt(r,q);
    loadedTiles.push_back(tile);
    return tile;
}

bool HexMap::deleteTile(Tile* tile){
    if(tile == NULL)
        return false;
    loadedTiles.remove(tile);
    delete (tile);
    return true;
}

void HexMap::sortTileList() {
    if(mapMode){
	loadedTiles.sort([](Tile* lhs, Tile* rhs) {
		    return (
				    lhs->r < rhs->r
				    || 
				    (lhs->r == rhs->r && lhs->q < rhs->q)
			);
	    });
    } else {
        loadedTiles.sort([](Tile* lhs, Tile* rhs) {
		    return (
				    lhs->q < rhs->q
				    || 
				    (lhs->q == rhs->q && lhs->r < rhs->r)
			);
	    });
    }
}

bool HexMap::isTileLoaded(int r, int q){
    for (std::list<Tile*>::iterator i = loadedTiles.begin(); i != loadedTiles.end(); ++i)
        if(((Tile*)(*i))->r == r && ((Tile*)(*i))->q == q)
            return true;
    return false;
}


uint32_t HexMap::axialDistance(int r1, int q1, int r2, int q2){
    return (abs(q1 - q2) 
          + abs(q1 + r1 - q2 - r2)
          + abs(r1 - r2)) / 2;
}

int HexMap::determineHeightAt(int r, int q){
    // To make map generation more interesting, add random height for tiles
    // Adding PerlinNoise using the XY from HexMap::rqTOxy can be a good start
    return 0;
}

std::string HexMap::determineTextureAt(int r, int q){
    // To make map generation more interesting, add different textures for tiles
    // Adding diffused PerlinNoise can help with creating different biomes for the map with different textures
    return deafultTexture;
}