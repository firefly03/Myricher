#ifndef __MAP_CHOOSE_SCENE_H__
#define __MAP_CHOOSE_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include "Map1Scene.h"
#include "Map2Scene.h"
#include "Map3Scene.h"

USING_NS_CC;
USING_NS_CC_EXT;

//定义了三张关卡图片
const int  MAP_COUNT = 3;
//手势滑动距离
const int TOUCH_DISTANCE = 50;

//地图选择
class MapChooseScene : public Layer, public ScrollViewDelegate
{
public:

	static Scene* createScene();

	bool init();

	CREATE_FUNC(MapChooseScene);

private:
	Size visibleSize;
	//用于存放3张关卡的图片的容器
	Layer* _spritesContainer;
	void back(Object*);
	//当前关卡
	int currentPage;
	//触摸开始的位置
	Point beginTouchPoint;

	ScrollView *scrollView;

	void singleTouchDown(Object* pSender, Control::EventType event);
	//添加背景
	void addBackgroundSprite();

	void addScrollView();
	//继承scrollViewDelegate类实现的三个方法
	void scrollViewDidScroll(ScrollView* view);
	void scrollViewDidZoom(ScrollView* view);
	void scrollViewMoveOver(ScrollView* view);
	//自定义方法,用于位置校正
	void adjustScrollView(float distance);
	//触摸的三个方法
	void onTouchEnded(Touch*touch, Event *unused_event);
	bool onTouchBegan(Touch * touch, Event *unused_event);//开始状态
	void onTouchMoved(Touch *touch, Event *unused_event);//移动状态


};



#endif

