#include "Map1Scene.h"

Scene * Map1Scene::createScene()
{
	auto scene = Scene::create();
	auto layer = Map1Scene::create();
	scene->addChild(layer);
	return scene;
}

bool Map1Scene::init() 
{

	
	addMap();
	initTiledGrid();
	initPropTiledID();
	if (!GameBaseScene::init())
		return false;
	
	return true;
}

void Map1Scene::initTiledGrid()
{
	//地图总的列数
	tiledColsCount = 21;
	tiledRowsCount = 16;

	//根据行列数创建二维数组canPassGrid

	canPassGrid = new bool*[tiledRowsCount];
	for (int i = 0; i < tiledRowsCount; i++)
		canPassGrid[i] = new bool[tiledColsCount];
	//给canPassGrid设置默认值为false 表示不能通过
	for (int row = 0; row < tiledRowsCount; row++) {
		for (int col = 0; col < tiledColsCount; col++) {
			canPassGrid[row][col] = false;
		}
	}

}

void Map1Scene::initPropTiledID()
{
	blank_land_tiledID = 1;
	strength_30_tiledID = 4;
	strength_50_tiledID = 5;
	strength_80_tiledID = 6;

	randomEvent_tiledID = 7;
	lottery_tiledID = 8;
	stock_tiledID = 9;

	player2_building_1_tiledID = 10;
	player2_building_2_tiledID = 11;
	player2_building_3_tiledID = 12;

	player1_building_1_tiledID = 13;
	player1_building_2_tiledID = 14;
	player1_building_3_tiledID = 15;
}

void Map1Scene::addMap()
{
	_map = TMXTiledMap::create("map/map_1.tmx");
	addChild(_map);
}