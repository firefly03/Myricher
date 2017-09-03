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

	//�ؿ�������
	static int tiledColsCount;
	//�ؿ���ͼ�ܵ�����
	static int tiledRowsCount;
	//���ݵ�ͼ�ܵ������������Ķ�ά����
	static bool** canPassGrid;
	//ͬ��ͼ��landͼ��
	static TMXLayer* landLayer;
	//ͬ��ͼ�е�wayͼ���Ӧ
	static TMXLayer* wayLayer;
	//��ͨ���ĵ�·λ�� 
	std::vector<Vec2> wayLayerPass_vector;
	//����menu��ť
	CC_SYNTHESIZE(Menu*, _menu, Menu);
	//��ɫ�ʽ��ǩ
	CC_SYNTHESIZE(LabelTTF *, player1_money_label, Player1_money_label);
	CC_SYNTHESIZE(LabelTTF *, player2_money_label, Player2_money_label);
	//��ɫ����Label
	CC_SYNTHESIZE(LabelTTF *, player1_strength_label, Player1_strength_label);
	CC_SYNTHESIZE(LabelTTF *, player2_strength_label, Player2_strength_label);
	//����Go��ť
	MenuItemImage* goMenuItemButton;
	//������ȡ�õĲ���
	int randStepsNumber;
	//���ݵ�ͼͼ��way,������canpassGrid��Ӧ��ֵΪtrue
	void setWayPassToGrid();
	//�˳�ʱ��Ҫ�ͷ�ĳЩ�����ռ�
	void onExit();
	//���Go��ť
	void addGoButton();
	//�����ť�Ļص�����,����ݰ�ťtagֵ,ִ�в�ͬ����
	void menuButtonCallback(Object* pSender);

	//��ʼ��landLayer
	void initLandLayerFromMap();

	//void onReceiveCustomEvent(EventCustom* event);

	RicherPlayer* player1;
	RicherPlayer* player2;
	static Vector<RicherPlayer*> players_vector;

	//����Vector�������6��·���ڵ�����
	static Vector<Sprite*> pathMarkVector;
	//����·���ڵ�����
	static void drawPathColor(std::vector<int> rowVector, std::vector<int> colVector);
	//��������ڵ�����ķ���
	void addPathMark();
	//���յ��Զ����¼��Ĵ�����
	void onReceiveCustomEvent(EventCustom* event);
	//�Զ����¼�������
	EventListenerCustom* customListener;

	static int blank_land_tiledID;		//�հ׵ؿ�ID
	static int strength_30_tiledID;		//����30��ͼ��ID
	static int strength_50_tiledID;		//����50��ͼ��ID
	static int strength_80_tiledID;		//����80��ͼ��ID

	static int randomEvent_tiledID;		//�ʺ�ͼ��ID
	static int lottery_tiledID;			//��Ʊͼ��ID
	static int stock_tiledID;			//��Ʊͼ��ID

	static int player1_building_1_tiledID;		//��ɫ1,�ȼ�Ϊ1�ؿ��ID
	static int player1_building_2_tiledID;		//��ɫ1,�ȼ�Ϊ2�ؿ��ID
	static int player1_building_3_tiledID;		//��ɫ1,�ȼ�Ϊ3�ؿ��ID

	static int player2_building_1_tiledID;		//��ɫ2,�ȼ�Ϊ1�ؿ��ID
	static int player2_building_2_tiledID;		//��ɫ2,�ȼ�Ϊ2�ؿ��ID
	static int player2_building_3_tiledID;		//��ɫ2,�ȼ�Ϊ3�ؿ��ID
	

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
	//����յص�x,y����
	int buy_land_x;
	int buy_land_y;
	//����յ�
	void  showBuyLandDialog(int landTag);
	//����յضԻ���
	PopupLayer* popDialog;
	//��ʼ���Ի���
	void initPopDialog();
	//����յػص�����
	void buyLandCallback(Node *pNode);
private:
	//��������Ч��ǰ��׼��
	void doSomeForParticle();
	//��ʧ����
	FadeOut* landFadeOut;
	//��ʾ����
	FadeIn* landFadeIn;
	//��ɫ1�Ľ�ӡ��������
	Sprite* foot1Sprite;
	Sprite* foot2Sprite;
	//��ɫ�ĺ��Ƕ���
	Sprite* starFish1Sprite;
	Sprite* starFish2Sprite;
	//��ɫ1�����ζ�������
	Sprite* heart1Sprite;
	Sprite* heart2Sprite;
	//���Ŷ���,��С���
	ActionInterval* scaleby1ForBuyLand;
	ActionInterval* scaleby2ForBuyLand;
	//��������Ч��
	void playParticle(Point point, char* plistName);
	void buyLand(int buyTag, float x, float y, Sprite* landSprite, int landLevel, RicherPlayer* player, char* particlelistName);
	void refreshMoneyLabel(RicherPlayer* player, int money);
	//���ɹ�·��
	void payTolls(int payTag, float x, float y, int playerTag);
	RicherPlayer* getPlayerByTiled(float x, float y);
	//��ɫ�ʽ�
	char money1[20];
	char money2[20];
	//���������ؿ��·��
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
	//��������,��������
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