#ifndef TILEMAP_INCLUDE
#define TILEMAP_INCLUDE


#define INCLUDE_SDL
#include "SDL_include.h"

#include <iostream>
#include <vector>
#include <memory>
#include "TileSet.h"
#include "Sprite.h"
#include "Component.h"

class TileMap : public Component{
public:
	TileMap(GameObject& associated, std::string file, TileSet* tileSet);
	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z=0);
	void Render();
	void RenderLayer(int layer);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	void Update(float dt){return;}
private:
	std::vector<int> tileMatrix;
	std::unique_ptr<TileSet> tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};

#endif