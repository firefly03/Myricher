#ifndef __GAME_BASE_SCENE_H__
#define __GAME_BASE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include "RicherPlayer.h"
#include "RouteNavigation.h"
#include "popupLayer\PopupLayer.h"
#include "PopupLayer\CocosToast.h"
#include "LanguageString.h"
#include "prop\Strength_up.h"
#include "Util.h"
#include "prop\Bee.h"
#include "prop\Emergency.h"
#include "prop\Fog.h"
#include "prop\Strength_up.h"
#include "prop\Stretcher.h"
#include "prop\Pearl.h"
USING_NS_CC;
USING_NS_CC_EXT;

const int tableStartPosition_x = 650;
const int tableStartPosition_y = 450;
const int tableWidth = 50;
const int tableHeight = 40;
const int tiledWidth = 32;
const int tiledHeight = 32;

const int goButtonTag = 700;


class GameBaseScene : public Layer
{
public:
	static Scene* createScene();
	static TMXTiledMap* _map;
	virtual bool init();

	CREATE_FUNC(GameBaseScene);

	//关卡总列数
	static int tiledColsCount;
	//关卡地图总的行数
	static int tiledRowsCount;
	//根据地图总的行列数创建的二维数组
	static bool** canPassGrid;
	//同地图的land图层
	static TMXLayer* landLayer;
	//同地图中的way图层对应
	static TMXLayer* wayLayer;
	//可通过的道路位置 
	std::vector<Vec2> wayLayerPass_vector;
	//定义menu按钮
	CC_SYNTHESIZE(Menu*, _menu, Menu);
	//角色资金标签
	CC_SYNTHESIZE(LabelTTF *, player1_money_label, Player1_money_label);
	CC_SYNTHESIZE(LabelTTF *, player2_money_label, Player2_money_label);
	//角色体力Label
	CC_SYNTHESIZE(LabelTTF *, player1_strength_label, Player1_strength_label);
	CC_SYNTHESIZE(LabelTTF *, player2_strength_label, Player2_strength_label);
	//定义Go按钮
	MenuItemImage* goMenuItemButton;
	//存放随机取得的步数
	int randStepsNumber;
	//根据地图图层way,设置能canpassGrid相应的值为true
	void setWayPassToGrid();
	//退出时需要释放某些变量空间
	void onExit();
	//添加Go按钮
	void addGoButton();
	//点击按钮的回调方法,会根据按钮tag值,执行不同代码
	void menuButtonCallback(Object* pSender);

	//初始化landLayer
	void initLandLayerFromMap();

	//void onReceiveCustomEvent(EventCustom* event);

	RicherPlayer* player1;
	RicherPlayer* player2;
	static Vector<RicherPlayer*> players_vector;

	//定义Vector用来存放6个路径遮挡精灵
	static Vector<Sprite*> pathMarkVector;
	//绘制路径遮挡方法
	static void drawPathColor(std::vector<int> rowVector, std::vector<int> colVector);
	//定义添加遮挡精灵的方法
	void addPathMark();
	//当收到自定义事件的处理方法
	void onReceiveCustomEvent(EventCustom* event);
	//自定义事件监听器
	EventListenerCustom* customListener;

	static int blank_land_tiledID;		//空白地块ID
	static int strength_30_tiledID;		//体力30的图块ID
	static int strength_50_tiledID;		//体力50的图块ID
	static int strength_80_tiledID;		//体力80的图块ID

	static int randomEvent_tiledID;		//问号图块ID
	static int lottery_tiledID;			//彩票图块ID
	static int stock_tiledID;			//股票图块ID

	static int player1_building_1_tiledID;		//角色1,等级为1地块的ID
	static int player1_building_2_tiledID;		//角色1,等级为2地块的ID
	static int player1_building_3_tiledID;		//角色1,等级为3地块的ID

	static int player2_building_1_tiledID;		//角色2,等级为1地块的ID
	static int player2_building_2_tiledID;		//角色2,等级为2地块的ID
	static int player2_building_3_tiledID;		//角色2,等级为3地块的ID
	

	void setPlayerAndFogInVisible(int tag);
	void startCarGoAgain();
	
private:

	void drawTable(int playerNumber);
	void addPlayer();
	void addRightBanner();

	void addNotificationObserver();
	void receivedNotificationMsg(Object* data);

	void addDigiteRoundSprite();
	int gameRoundCount;
	Vector<SpriteFrame*>  digiteRoundVector;

	Vector<Sprite*> refreshRoundVector;
	void refreshRoundDisplay();
	//购买空地的x,y坐标
	int buy_land_x;
	int buy_land_y;
	//购买空地
	void  showBuyLandDialog(int landTag);
	//购买空地对话框
	PopupLayer* popDialog;
	//初始化对话框
	void initPopDialog();
	//购买空地回调方法
	void buyLandCallback(Node *pNode);
private:
	//播放粒子效果前的准备
	void doSomeForParticle();
	//消失动画
	FadeOut* landFadeOut;
	//显示动画
	FadeIn* landFadeIn;
	//角色1的脚印动画精灵
	Sprite* foot1Sprite;
	Sprite* foot2Sprite;
	//角色的海星动画
	Sprite* starFish1Sprite;
	Sprite* starFish2Sprite;
	//角色1的心形动画精灵
	Sprite* heart1Sprite;
	Sprite* heart2Sprite;
	//缩放动画,由小变大
	ActionInterval* scaleby1ForBuyLand;
	ActionInterval* scaleby2ForBuyLand;
	//播放粒子效果
	void playParticle(Point point, char* plistName);
	void buyLand(int buyTag, float x, float y, Sprite* landSprite, int landLevel, RicherPlayer* player, char* particlelistName);
	void refreshMoneyLabel(RicherPlayer* player, int money);
	//缴纳过路费
	void payTolls(int payTag, float x, float y, int playerTag);
	RicherPlayer* getPlayerByTiled(float x, float y);
	//角色资金
	char money1[20];
	char money2[20];
	//缴纳相连地块过路费
private:
	Vector<Sprite*> displayVector;
	int displayArea(float x, float y, RicherPlayer* player, int building_1_tiledID, int building_2_tiledID, int building_3_tiledID);
	void sendMSGPickOneToGo();
private:
	Map<int, __String*> randomAskEventMap;
	void initRandomAskEvent();
	void sendMSGDealAroundLand();
	void doRandomAskEvent(RicherPlayer* player);
	char strength1[20];
	char strength2[20];
	void refreshStrengthLabel(RicherPlayer* player, int strength);
	//捡到体力卡,增加体力
private:
	void initPropSprite();
	void doItemStrengthUp(int strengthUp, int playerTag);
	void registerBlockWaySchedule();
	void updateBlockWaySprites(float dt);
	void doBlockWayEvent(RicherPlayer* player);
	Strength_up* _strength_up;
	Bee* _bee;
	Fog* _fog;
	Stretcher* _stretcher;
	Emergency* _emergency;
	Pearl* _pearl;

private:
	void endCarGo(int tag);
	void sendMSGDealProp();
};

#endif