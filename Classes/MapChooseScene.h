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

//���������Źؿ�ͼƬ
const int  MAP_COUNT = 3;
//���ƻ�������
const int TOUCH_DISTANCE = 50;

//��ͼѡ��
class MapChooseScene : public Layer, public ScrollViewDelegate
{
public:

	static Scene* createScene();

	bool init();

	CREATE_FUNC(MapChooseScene);

private:
	Size visibleSize;
	//���ڴ��3�Źؿ���ͼƬ������
	Layer* _spritesContainer;
	void back(Object*);
	//��ǰ�ؿ�
	int currentPage;
	//������ʼ��λ��
	Point beginTouchPoint;

	ScrollView *scrollView;

	void singleTouchDown(Object* pSender, Control::EventType event);
	//��ӱ���
	void addBackgroundSprite();

	void addScrollView();
	//�̳�scrollViewDelegate��ʵ�ֵ���������
	void scrollViewDidScroll(ScrollView* view);
	void scrollViewDidZoom(ScrollView* view);
	void scrollViewMoveOver(ScrollView* view);
	//�Զ��巽��,����λ��У��
	void adjustScrollView(float distance);
	//��������������
	void onTouchEnded(Touch*touch, Event *unused_event);
	bool onTouchBegan(Touch * touch, Event *unused_event);//��ʼ״̬
	void onTouchMoved(Touch *touch, Event *unused_event);//�ƶ�״̬


};



#endif

