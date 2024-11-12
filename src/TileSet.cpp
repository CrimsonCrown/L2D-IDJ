#include "TileSet.h"


TileSet::TileSet(int tileWidth, int tileHeight, std::string file){
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	//std::cout <<"tried to make a set\n";
	tileSet.Open(file);
	if(tileSet.IsOpen()){
		tileCount = (tileSet.GetWidth() / tileWidth) * (tileSet.GetHeight() / tileHeight);
		tileSet.SetFrameCount(tileSet.GetWidth() / tileWidth, tileSet.GetHeight() / tileHeight);
	}
	else{
		std::cout << SDL_GetError();
		tileCount = 0;
	}
}

void TileSet::RenderTile(int index, int x, int y){
	if (index >= 0 && index < tileCount) {
		tileSet.SetFrame(index);
		tileSet.Render(x, y, tileWidth, tileHeight);
	}
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

int TileSet::GetTileHeight(){
	return tileHeight;
}