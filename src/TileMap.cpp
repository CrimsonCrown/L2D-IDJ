#include "TileMap.h"
#include <fstream>
#include "GameObject.h"
#include "Camera.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated){
	//std::cout << "tried to make a map\n";
	Load(file);
	this->tileSet=std::unique_ptr<TileSet>(tileSet);
	return;
}

void TileMap::Load(std::string file){
	std::ifstream maptxt;
	char comma;
	maptxt.open(file);
	maptxt >> mapWidth >> comma;
	maptxt >> mapHeight >> comma;
	maptxt >> mapDepth >> comma;
	//std::cout << mapWidth << " " << mapHeight << " " << mapDepth << "\n";
	tileMatrix.clear();
	int aux;
	int i;
	for(i=0;i<(mapWidth*mapHeight*mapDepth);i++){
		maptxt >> aux >> comma;
		//aux--;
		//std::cout << aux << "\n";
		tileMatrix.push_back(aux);
	}
	maptxt.close();
	return;
}

void TileMap::SetTileSet(TileSet* tileSet){
	this->tileSet= std::unique_ptr<TileSet>(tileSet);
	return;
}

int& TileMap::At(int x, int y, int z){
	return tileMatrix[x+(y*mapWidth)+(z*(mapHeight*mapWidth))];
}

void TileMap::Render(){
	int i;
	for(i=0;i<mapDepth;i++){
		RenderLayer(i);
	}
	return;
}

void TileMap::RenderLayer(int layer){
	int x;
	int y;
	int offsetMultiplier = (mapDepth-1) - layer;
	float offset = offsetMultiplier * 0.5;
	float offsetX = Camera::pos.x*offset;
	float offsetY = Camera::pos.y*offset;
	for(x=0;x<mapWidth;x++){
		for(y=0;y<mapHeight;y++){
			tileSet->RenderTile(At(x,y,layer),associated.box.x+x*tileSet->GetTileWidth()+offsetX,associated.box.y+y*tileSet->GetTileHeight()+offsetY);
		}
	}
	return;
}

int TileMap::GetWidth(){
	return mapWidth;
}

int TileMap::GetHeight(){
	return mapHeight;
}

int TileMap::GetDepth(){
	return mapDepth;
}
