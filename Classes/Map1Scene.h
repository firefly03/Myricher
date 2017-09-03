#ifndef __MAP1_SCENE_H__
#define __MAP1_SCENE_H__

#include "cocos2d.h"
#include "GameBaseScene.h"

USING_NS_CC;
class Map1Scene :public GameBaseScene
{
public:
	static Scene* createScene();
	void addMap();
	virtual bool init();

	void initTiledGrid();
	//³õÊ¼»¯µØ¿éID
	void initPropTiledID();
	CREATE_FUNC(Map1Scene);
private:
};
#endif //!__MAP1_SCENE_H__