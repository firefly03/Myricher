#include "GameBaseScene.h"

int GameBaseScene::tiledColsCount;
int GameBaseScene::tiledRowsCount;
bool **GameBaseScene::canPassGrid;
TMXTiledMap* GameBaseScene::_map;
TMXLayer* GameBaseScene::landLayer;
TMXLayer* GameBaseScene::wayLayer;
Vector<RicherPlayer*> GameBaseScene::players_vector;
Vector<Sprite*> GameBaseScene::pathMarkVector;

//地块
int  GameBaseScene::blank_land_tiledID;
int  GameBaseScene::strength_30_tiledID;
int  GameBaseScene::strength_50_tiledID;
int  GameBaseScene::strength_80_tiledID;

int  GameBaseScene::randomEvent_tiledID;
int  GameBaseScene::lottery_tiledID;
int  GameBaseScene::stock_tiledID;

int GameBaseScene::player1_building_1_tiledID;
int GameBaseScene::player1_building_2_tiledID;
int GameBaseScene::player1_building_3_tiledID;

int GameBaseScene::player2_building_1_tiledID;
int GameBaseScene::player2_building_2_tiledID;
int GameBaseScene::player2_building_3_tiledID;


void GameBaseScene::setPlayerAndFogInVisible(int tag)
{
	if (tag == PLAYER_1_TAG)
	{
		player1->setVisible(false);
	}
	if (tag == PLAYER_2_TAG)
	{
		player2->setVisible(false);
	}
	_fog->setVisible(false);
	//throw std::logic_error("The method or operation is not implemented.");
}

void GameBaseScene::startCarGoAgain()
{
	_stretcher->setVisible(false);
	int distance = _emergency->getPositionX();
	MoveBy* moveBy = MoveBy::create(1.0f, Vec2(-distance, 0));
	Repeat* repeate = Repeat::create(_emergency->getCar_go_anmi(), 5);
	Sequence* spawnAction = Sequence::create(Spawn::create(moveBy, repeate, NULL), CallFunc::create([this]() {
		_emergency->setVisible(false);
		Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
	}), NULL);
	spawnAction->retain();
	_emergency->runAction(spawnAction);

	//throw std::logic_error("The method or operation is not implemented.");
}

Scene* GameBaseScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameBaseScene::create();

	scene->addChild(layer);

	return scene;

}

bool GameBaseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	addRightBanner();

	drawTable(2);
	setWayPassToGrid();
	addPathMark();
	addPlayer();
	addGoButton();
	addNotificationObserver();
	addDigiteRoundSprite();
	refreshRoundDisplay();
	initLandLayerFromMap();
	initPropSprite();
	initPopDialog();
	doSomeForParticle();
	initRandomAskEvent();
	registerBlockWaySchedule();
	
	/*************测量单击坐标值************
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event) {

		log("X:%02f, Y:%02f", touch->getLocation().x,touch->getLocation().y);
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	*/
	//addNotificationObserver();
	return true;
}

void  GameBaseScene::addRightBanner()
{
	Sprite* rightBanner = Sprite::create(RIGHT_BANNER);
	rightBanner->setAnchorPoint(Vec2(0, 0));
	rightBanner->setPosition(Vec2(tableStartPosition_x, 0));
	addChild(rightBanner);
}


void GameBaseScene::addPlayer()
{
	Sprite* player_1 = Sprite::create(PLAYER_1);
	player_1->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - tableHeight);
	addChild(player_1);

	player1_money_label = LabelTTF::create();
	player1_money_label->setString("$");
	player1_money_label->setAnchorPoint(Vec2(0, 0.5));
	player1_money_label->setFontSize(25);
	player1_money_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2);
	addChild(player1_money_label);

	player1_strength_label = LabelTTF::create();
	player1_strength_label->setString("+");
	player1_strength_label->setAnchorPoint(Vec2(0, 0.5));
	player1_strength_label->setFontSize(28);
	player1_strength_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 3);
	addChild(player1_strength_label);

	Sprite* player_2 = Sprite::create(PLAYER_2);
	player_2->setPosition(tableStartPosition_x + tableWidth / 2, tableStartPosition_y - 3 * tableHeight);
	addChild(player_2);

	player2_money_label = LabelTTF::create();
	player2_money_label->setString("$");
	player2_money_label->setAnchorPoint(Vec2(0, 0.5));
	player2_money_label->setFontSize(25);
	player2_money_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 5);
	addChild(player2_money_label);

	player2_strength_label = LabelTTF::create();
	player2_strength_label->setString("+");
	player2_strength_label->setAnchorPoint(Vec2(0, 0.5));
	player2_strength_label->setFontSize(28);
	player2_strength_label->setPosition(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight / 2 * 7);
	addChild(player2_strength_label);


	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
	srand(rand_seed);
	player1 = RicherPlayer::create(PLAYER_1_NAME, PLAYER_1_TAG);
	int _rand1 = rand() % (wayLayerPass_vector.size());
	log("rand %d", _rand1);
	Vec2 vec2ForPlayer1 = wayLayerPass_vector.at(_rand1);
	vec2ForPlayer1.y += tiledHeight;
	player1->setPosition(vec2ForPlayer1);
	player1->setAnchorPoint(Vec2(0, 0.5));
	addChild(player1);
	players_vector.pushBack(player1);

	player2 = RicherPlayer::create(PLAYER_2_NAME, PLAYER_2_TAG);
	int _rand2 = rand() % (wayLayerPass_vector.size());
	log("rand %d", _rand2);
	Vec2 vec2ForPlayer2 = wayLayerPass_vector.at(_rand2);
	vec2ForPlayer2.y += tiledHeight;
	player2->setPosition(vec2ForPlayer2);
	player2->setAnchorPoint(Vec2(0, 0.5));
	addChild(player2);
	players_vector.pushBack(player2);

	memset(money1, 0, 20);
	sprintf(money1, "$ %d", player1->getMoney());
	getPlayer1_money_label()->setString(money1);

	memset(money2, 0, 20);
	sprintf(money2, "$ %d", player1->getMoney());
	getPlayer2_money_label()->setString(money2);


	memset(strength1, 0, 20);
	sprintf(strength1, "+ %d", player1->getStrength());
	getPlayer1_strength_label()->setString(strength1);

	memset(strength2, 0, 20);
	sprintf(strength2, "+ %d", player1->getStrength());
	getPlayer2_strength_label()->setString(strength2);
	
}

void GameBaseScene::drawPathColor(std::vector<int> rowVector, std::vector<int> colVector)
{
	int stepsCount = rowVector.size() - 1;
	//从遮挡容器中取出遮挡sprite,放置到对应位置,并设为可见
	for (int i = 1; i < rowVector.size(); i++)
	{
		pathMarkVector.at(i - 1)->setPosition(Vec2(colVector[i] * 32, rowVector[i] * 32));
		pathMarkVector.at(i - 1)->setVisible(true);
	}
}

void GameBaseScene::addPathMark()
{
	Sprite* mark1 = Sprite::create(PATH_MARK_1);
	Sprite* mark2 = Sprite::create(PATH_MARK_2);
	Sprite* mark3 = Sprite::create(PATH_MARK_3);
	Sprite* mark4 = Sprite::create(PATH_MARK_4);
	Sprite* mark5 = Sprite::create(PATH_MARK_5);
	Sprite* mark6 = Sprite::create(PATH_MARK_6);
	mark1->setAnchorPoint(Vec2::ZERO);
	mark2->setAnchorPoint(Vec2::ZERO);
	mark3->setAnchorPoint(Vec2::ZERO);
	mark4->setAnchorPoint(Vec2::ZERO);
	mark5->setAnchorPoint(Vec2::ZERO);
	mark6->setAnchorPoint(Vec2::ZERO);
	mark1->setVisible(false);
	mark2->setVisible(false);
	mark3->setVisible(false);
	mark4->setVisible(false);
	mark5->setVisible(false);
	mark6->setVisible(false);
	addChild(mark1);
	addChild(mark2);
	addChild(mark3);
	addChild(mark4);
	addChild(mark5);
	addChild(mark6);
	pathMarkVector.pushBack(mark1);
	pathMarkVector.pushBack(mark2);
	pathMarkVector.pushBack(mark3);
	pathMarkVector.pushBack(mark4);
	pathMarkVector.pushBack(mark5);
	pathMarkVector.pushBack(mark6);

}

void GameBaseScene::drawTable(int playerNumber)
{
	auto s = Director::getInstance()->getWinSize();

	auto draw = DrawNode::create();
	this->addChild(draw);

	for (int i = 0; i<playerNumber; i++)
	{
		draw->drawSegment(Vec2(tableStartPosition_x, tableStartPosition_y - 2 * i*tableHeight),
			Vec2(tableStartPosition_x + 3 * tableWidth, tableStartPosition_y - 2 * i*tableHeight), 1,
			Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x, tableStartPosition_y - 2 * (i + 1)*tableHeight),
			Vec2(tableStartPosition_x + 3 * tableWidth, tableStartPosition_y - 2 * (i + 1)*tableHeight), 1,
			Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - tableHeight - 2 * i*tableHeight),
			Vec2(tableStartPosition_x + 3 * tableWidth, tableStartPosition_y - tableHeight - 2 * i*tableHeight), 1,
			Color4F(0, 1, 0, 1));

		draw->drawSegment(Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - 2 * i*tableHeight),
			Vec2(tableStartPosition_x + tableWidth, tableStartPosition_y - 2 * tableHeight - 2 * i*tableHeight), 1,
			Color4F(0, 1, 0, 1));
	}
}

void GameBaseScene::setWayPassToGrid()
{
	//获取地图的way图层
	wayLayer = _map->layerNamed("way");
	//获取way图层大小
	Size _mapSize = wayLayer->getLayerSize();
	//根据way图层,获取道路的坐标并转换成地图的行列值,设置canPassGrid相应的值
	for (int j = 0; j < _mapSize.width; j++) {
		for (int i = 0; i < _mapSize.height; i++)
		{
			Sprite* _sp = wayLayer->tileAt(Point(j, i));
			if (_sp) {
				float x = _sp->getPositionX();
				float y = _sp->getPositionY();
				int col = x / tiledWidth;
				int row = y / tiledHeight;
				canPassGrid[row][col] = true;
				Vec2 p = _sp->getPosition();
				wayLayerPass_vector.push_back(p);
				log("canPassGrid row = %d, col = %d,canpass = %d", row, col, canPassGrid[row][col]);
			}
		}
	}
	log("setWayPassToGrid finished");
}

void GameBaseScene::addGoButton()
{
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	setMenu(menu);

	goMenuItemButton = MenuItemImage::create("button/go_normal.png", "button/go_press.png",
		CC_CALLBACK_1(GameBaseScene::menuButtonCallback, this));

	goMenuItemButton->setPosition(Vec2(tableStartPosition_x + 2 * tableWidth,
		tableStartPosition_y + -tableHeight * 6));
	goMenuItemButton->setTag(goButtonTag);
	menu->addChild(goMenuItemButton);
	addChild(menu);
}

void GameBaseScene::menuButtonCallback(Object * pSender)
{
	
	int tag = ((Node*)pSender)->getTag();
	if (tag == goButtonTag)
	{
		log("go button clicked");
		randStepsNumber = rand() % 6 + 1;
		RouteNavigation::getInstance()->getPath(player1, randStepsNumber, canPassGrid, tiledRowsCount, tiledColsCount);
		std::vector<int> colVector = RouteNavigation::getInstance()->getPathCols_vector();
		std::vector<int> rowVector = RouteNavigation::getInstance()->getPathRow_vector();

		for (int i = 0; i < rowVector.size(); i++)
		{
			log(" rowVector row is %d --- colVector col is %d", rowVector[i], colVector[i]);
		}

		//NotificationCenter::getInstance()->postNotification(RICHER_MSG, String::createWithFormat("%d", MSG_GO_HIDE_TAG));
		
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		EventCustom _event = EventCustom(RICHER_MSG);
		_event.setUserData(String::createWithFormat("%d", MSG_GO_HIDE_TAG));
		//通过事件分发器发送自定义事件
		dispatcher->dispatchEvent(&_event);
		player1->startGo(rowVector, colVector);
		log("go button clicked over");
	}

}

void GameBaseScene::initLandLayerFromMap()
{
	landLayer = _map->layerNamed("land");
}

void GameBaseScene::onReceiveCustomEvent(EventCustom * event)
{

	String* srcDate = (String*)event->getUserData();
	Vector<String*> messageVector = Util::splitString(srcDate->getCString(), "-");
	int retMsgType = messageVector.at(0)->intValue();
	log("received go message is: %d", retMsgType);
	log("onCustomEvent data = %d", srcDate);
	switch (retMsgType)
	{
		case MSG_GO_SHOW_TAG:
		{
			goMenuItemButton->runAction(MoveBy::create(0.3, Vec2(-(goMenuItemButton->getContentSize().width) * 2, 0)));
			gameRoundCount++;
			refreshRoundDisplay();
			break;
		}
		case  MSG_GO_HIDE_TAG:
		{
			goMenuItemButton->runAction(MoveBy::create(0.3, Vec2((goMenuItemButton->getContentSize().width) * 2, 0)));
			break;
		}

		case MSG_BUY_BLANK_TAG:
		{
			buy_land_x = messageVector.at(1)->intValue();
			buy_land_y = messageVector.at(2)->intValue();
			int playerTag = messageVector.at(3)->intValue();
			switch (playerTag)
			{
				case PLAYER_1_TAG:
				{
					showBuyLandDialog(MSG_BUY_BLANK_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					buyLand(MSG_BUY_BLANK_TAG, buy_land_x, buy_land_y, foot2Sprite, player2_building_1_tiledID, player2, PLAYER2_1_PARTICLE_PLIST);
					Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
					break;
				}
			}
			break;
		}

		case MSG_BUY_LAND_1_TAG:
		{
			buy_land_x = messageVector.at(1)->intValue();
			buy_land_y = messageVector.at(2)->intValue();
			int playerTag = messageVector.at(3)->intValue();

			switch (playerTag)
			{
				case PLAYER_1_TAG:
				{
					showBuyLandDialog(MSG_BUY_LAND_1_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					buyLand(MSG_BUY_LAND_1_TAG, buy_land_x, buy_land_y, starFish2Sprite, player2_building_2_tiledID, player2, PLAYER2_1_PARTICLE_PLIST);
					Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
					break;
				}
			}
			break;
		}
		case MSG_BUY_LAND_2_TAG:
		{
			buy_land_x = messageVector.at(1)->intValue();
			buy_land_y = messageVector.at(2)->intValue();
			int playerTag = messageVector.at(3)->intValue();

			switch (playerTag)
			{
				case PLAYER_1_TAG:
				{
					showBuyLandDialog(MSG_BUY_LAND_2_TAG);
					break;
				}
				case PLAYER_2_TAG:
				{
					buyLand(MSG_BUY_LAND_2_TAG, buy_land_x, buy_land_y, heart2Sprite, player2_building_3_tiledID, player2, PLAYER2_1_PARTICLE_PLIST);
					Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
					break;
				}
			}
			break;
		}
		case MSG_PAY_TOLLS_1_TAG:
		case MSG_PAY_TOLLS_2_TAG:
		case MSG_PAY_TOLLS_3_TAG:
		{
			buy_land_x = messageVector.at(1)->intValue();
			buy_land_y = messageVector.at(2)->intValue();
			int playerTag = messageVector.at(3)->intValue();
			payTolls(retMsgType, buy_land_x, buy_land_y, playerTag);
			break;
		}
		case MSG_RANDOM_ASK_EVENT_TAG:
		{

			int playerTag = messageVector.at(3)->intValue();
			switch (playerTag)
			{
				case PLAYER_1_TAG:
				{
					doRandomAskEvent(player1);
					break;
				}
				case PLAYER_2_TAG:
				{
					doRandomAskEvent(player2);
					break;
				}
			}

			break;
		}
		case MSG_STRENGTH_UP30_TAG:
		case MSG_STRENGTH_UP50_TAG:
		case MSG_STRENGTH_UP80_TAG:
		{
			//当接收到分值卡消息时,调用doItemStrengthUp 方法给角色进行体力的增加
			doItemStrengthUp(retMsgType, messageVector.at(1)->intValue());
			break;
		}
		case MSG_BLOCK_WAY_EVENT_TAG:
		{
			int	playerTag = messageVector.at(1)->intValue();
			switch (playerTag)
			{
			case PLAYER_1_TAG:
			{
				doBlockWayEvent(player1);
				break;
			}
			case PLAYER_2_TAG:
			{
				doBlockWayEvent(player2);
				break;
			}

			}
			break;
		}
		case MSG_REST_TAG:
		{
			int playerTag = messageVector.at(1)->intValue();
			switch (playerTag)
			{
			case PLAYER_1_TAG:
			{
				player1->setIsMyTurn(false);
				CocosToast::createToast(this, String::createWithFormat("%s %d %s", 
					LanguageString::getInstance()->getLanguageString(IN_HOSPITAL_REMAIN)->getCString(),
					player1->restTimes, LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString()
				)->getCString(), TOAST_SHOW_TIME, player1->getPosition(), 
					(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGo);
				break;
			}
			case PLAYER_2_TAG:
			{
				player2->setIsMyTurn(false);
				CocosToast::createToast(this, String::createWithFormat("%s %d %s",
					LanguageString::getInstance()->getLanguageString(IN_HOSPITAL_REMAIN)->getCString(), 
					player2->restTimes, LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString()
				)->getCString(), TOAST_SHOW_TIME, 
					player2->getPosition(), 
					(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGo);
				break;
			}
			}

			break;
		}

	}
}

void GameBaseScene::onExit()
{
	CC_SAFE_DELETE(canPassGrid);
	//NotificationCenter::getInstance()->removeObserver(this, RICHER_MSG);
	Director::getInstance()->getEventDispatcher()->removeEventListener(customListener);
	Layer::onExit();
}


void GameBaseScene::addNotificationObserver()
{

	/*NotificationCenter::getInstance()->addObserver(
		this,
		callfuncO_selector(GameBaseScene::receivedNotificationMsg),
		RICHER_MSG,
		NULL);*/
	//获取事件分发器
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	//创建自定义事件监听器,监听器名字为RICHER_MSG
	//响应函数为onReceiveCustomEvent
	customListener = EventListenerCustom::create(RICHER_MSG, CC_CALLBACK_1(GameBaseScene::onReceiveCustomEvent, this));
	//添加自定义事件监听器,优先权为1
	dispatcher->addEventListenerWithFixedPriority(customListener, 1);

		

}

void GameBaseScene::receivedNotificationMsg(Object* data)
{
	//调用Util工具类的方法,获取消息的类型
	String* srcDate = (String*)data;
	Vector<String*> messageVector = Util::splitString(srcDate->getCString(), "-");
	int retMsgType = messageVector.at(0)->intValue();
	log("received go message is :%d", retMsgType);
	switch (retMsgType)
	{
		case MSG_GO_SHOW_TAG:
		{
			goMenuItemButton->runAction(MoveBy::create(
				0.3, Vec2(-(goMenuItemButton->getContentSize().width * 2),0)));
			gameRoundCount++;
			refreshRoundDisplay();
			break;
		}
		case MSG_GO_HIDE_TAG:
		{
			goMenuItemButton->runAction(MoveBy::create(
				0.3, Vec2(goMenuItemButton->getContentSize().width * 2, 0)));
			break;
		}

	}
}

void GameBaseScene::addDigiteRoundSprite()
{
	//定义变量gameRoundCount,初始值为0,记录游戏进行的回合
	gameRoundCount = 0;
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("images/digital_round.plist");
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_0));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_1));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_2));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_3));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_4));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_5));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_6));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_7));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_8));
	digiteRoundVector.pushBack(frameCache->getSpriteFrameByName(DIGITAL_9));
	
}

void GameBaseScene::refreshRoundDisplay()
{
	for (auto it = refreshRoundVector.begin(); it != refreshRoundVector.end(); it++)
	{
		((Sprite*)*it)->setVisible(false);
	}

	refreshRoundVector.clear();
	int count = gameRoundCount;
	Sprite* st;
	//当游戏刚开始,显示回合数为0
	if (count == 0)
	{
		st = Sprite::createWithSpriteFrame(digiteRoundVector.at(0));
		addChild(st);
		refreshRoundVector.pushBack(st);
	}

	//把数字转换成sprite存放进refreshRoundVector容器
	while (count != 0)
	{
		st = Sprite::createWithSpriteFrame(digiteRoundVector.at(count % 10));
		addChild(st);
		refreshRoundVector.pushBack(st);
		count = count / 10;
	}
	refreshRoundVector.reverse();

	for (int i = 0; i < refreshRoundVector.size(); i++)
	{
		//取出数字SPRITE,设置位置,显示出来
		Sprite* sp = refreshRoundVector.at(i);
		sp->setPosition(Vec2(tableStartPosition_x + 50 + i * 25, 50));
		sp->setVisible(true);
	}
}

void GameBaseScene::showBuyLandDialog(int landTag)
{
	String showMessage = "";
	switch (landTag)
	{
	case MSG_BUY_BLANK_TAG:
	{
		showMessage = String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(),LAND_BLANK_MONEY)->getCString();
		break;
	}
	case MSG_BUY_LAND_1_TAG:
	{
		showMessage = String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(), LAND_LEVEL_1_MONEY)->getCString();
		break;
	}
	case MSG_BUY_LAND_2_TAG:
	{
		showMessage = String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(BUY_LAND_MSG)->getCString(), LAND_LEVEL_2_MONEY)->getCString();
		break;
	}
	}
	popDialog->setDataTag(landTag);
	popDialog->getLabelContentText()->setString(showMessage.getCString());
	popDialog->setVisible(true);
	
}

void GameBaseScene::initPopDialog()
{
	popDialog = PopupLayer::create(DIALOG_BG);
	//设置对话框为非模态对话框,防止go按钮无法响应事件
	popDialog->setPopModalDialog(false);
	//对话框太小
	popDialog->setContentSize(CCSizeMake(Dialog_Size_Width, Dialog_Size_Height));
	popDialog->setTitle(DIALOG_TITLE);
	popDialog->setContentText("", 20, 60, 250);
	//对话框响应事件的回调函数,当点击确定取消时调用
	popDialog->setCallbackFunc(this, callfuncN_selector(GameBaseScene::buyLandCallback));
	//添加确定键
	popDialog->addButton(BUTTON_BG1, BUTTON_BG3, OK, Btn_OK_TAG);
	popDialog->addButton(BUTTON_BG2, BUTTON_BG3, CANCEL, Btn_Cancel_TAG);
	this->addChild(popDialog);
	popDialog->setVisible(false);
}

void GameBaseScene::buyLandCallback(Node* pNode)
{
	if (pNode->getTag() == Btn_OK_TAG)
	{
		switch (popDialog->getDataTag())
		{
		case MSG_BUY_BLANK_TAG:
		{
			buyLand(MSG_BUY_BLANK_TAG, buy_land_x, buy_land_y, foot1Sprite, player1_building_1_tiledID, player1, PLAYER1_1_PARTICLE_PLIST);
			log("need $1000 ");
			break;
		}
		case MSG_BUY_LAND_1_TAG:
		{
			buyLand(MSG_BUY_LAND_1_TAG, buy_land_x, buy_land_y, starFish1Sprite, player1_building_2_tiledID, player1, PLAYER1_1_PARTICLE_PLIST);
			log("need $2000 ");
			break;
		}
		case MSG_BUY_LAND_2_TAG:
		{
			buyLand(MSG_BUY_LAND_2_TAG, buy_land_x, buy_land_y, heart1Sprite, player1_building_3_tiledID, player1, PLAYER1_1_PARTICLE_PLIST);
			log("need $3000 ");
			break;
		}
		}
	}
	popDialog->setVisible(false);
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
}

void GameBaseScene::doSomeForParticle()
{
	landFadeOut = FadeOut::create(0.1);
	landFadeIn = FadeIn::create(0.1);
	landFadeOut->retain();
	landFadeIn->retain();

	scaleby1ForBuyLand = ScaleBy::create(0.1, 1.5);
	scaleby2ForBuyLand = ScaleBy::create(0.5, 0.7);
	scaleby1ForBuyLand->retain();
	scaleby2ForBuyLand->retain();
	foot1Sprite = Sprite::create(PLAYER1_1_PARTICLE_PNG);
	addChild(foot1Sprite);
	foot1Sprite->setAnchorPoint(Vec2(0, 0));

	foot2Sprite = Sprite::create(PLAYER2_1_PARTICLE_PNG);
	addChild(foot2Sprite);
	foot2Sprite->setAnchorPoint(Vec2(0, 0));

	starFish1Sprite = Sprite::create(PLAYER1_2_PARTICLE_PNG);
	addChild(starFish1Sprite);
	starFish1Sprite->setAnchorPoint(Vec2(0, 0));

	starFish2Sprite = Sprite::create(PLAYER2_2_PARTICLE_PNG);
	addChild(starFish2Sprite);
	starFish2Sprite->setAnchorPoint(Vec2(0, 0));

	heart1Sprite = Sprite::create(PLAYER1_3_PARTICLE_PNG);
	addChild(heart1Sprite);
	heart1Sprite->setAnchorPoint(Vec2(0, 0));

	heart2Sprite = Sprite::create(PLAYER2_3_PARTICLE_PNG);
	addChild(heart2Sprite);
	heart2Sprite->setAnchorPoint(Vec2(0, 0));
}

void GameBaseScene::playParticle(Point point, char * plistName)
{
	//根据文件名创建粒子系统
	ParticleSystem* particleSystem_foot = ParticleSystemQuad::create(plistName);
	particleSystem_foot->retain();
	//批处理节点,可以提高效率
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(particleSystem_foot->getTexture());
	batch->addChild(particleSystem_foot);
	addChild(batch);
	//设置粒子系统位置,就在购买地块的中心位置
	particleSystem_foot->setPosition(point + Vec2(tiledWidth / 2, tiledHeight / 2));
	particleSystem_foot->release();
	//粒子系统播放完后自动删除
	particleSystem_foot->setAutoRemoveOnFinish(true);

}

void GameBaseScene::buyLand(int buyTag, float x, float y, Sprite * landSprite, int landLevel, RicherPlayer * player, char * particlelistName)
{
	int money = 0;

	if (buyTag == MSG_BUY_BLANK_TAG)
	{
		money = LAND_BLANK_MONEY;
	}
	if (buyTag == MSG_BUY_LAND_1_TAG)
	{
		money = LAND_LEVEL_1_MONEY;
	}
	if (buyTag == MSG_BUY_LAND_2_TAG)
	{
		money = LAND_LEVEL_2_MONEY;
	}

	Point pointOfGL = Util::map2GL(Vec2(x, y), GameBaseScene::_map);
	landSprite->setVisible(true);
	landSprite->setPosition(pointOfGL);
	Point pointOfMap = Vec2(x, y);
	landSprite->runAction(Sequence::create(scaleby1ForBuyLand, scaleby2ForBuyLand, CallFunc::create([this, pointOfMap, pointOfGL, landSprite, landLevel, x, y, player, money, particlelistName]()
	{
		playParticle(pointOfGL, particlelistName);
		landSprite->setVisible(false);
		landLayer->setTileGID(landLevel, Vec2(x, y));
		refreshMoneyLabel(player, -money);
	}), NULL));
}

void GameBaseScene::refreshMoneyLabel(RicherPlayer * player, int money)
{
	int tag = player->getTag();
	player->setMoney(player->getMoney() + money);


	if (tag == PLAYER_1_TAG)
	{
		memset(money1, 0, 20);
		sprintf(money1, "$ %d", player->getMoney());
		getPlayer1_money_label()->setString(money1);
	}
	if (tag == PLAYER_2_TAG)
	{
		memset(money2, 0, 20);
		sprintf(money2, "$ %d", player->getMoney());
		getPlayer2_money_label()->setString(money2);
	}
}

void GameBaseScene::payTolls(int payTag, float x, float y, int playerTag)
{
	int money = 0;
	if (payTag == MSG_PAY_TOLLS_1_TAG)
	{
		money = LAND_BLANK_MONEY;
	}
	if (payTag == MSG_PAY_TOLLS_2_TAG)
	{
		money = LAND_LEVEL_1_MONEY;
	}
	if (payTag == MSG_PAY_TOLLS_3_TAG)
	{
		money = LAND_LEVEL_2_MONEY;
	}

	Point pointOfGL = Util::map2GL(Vec2(x, y), GameBaseScene::_map);
	Sprite* sp = landLayer->getTileAt(Vec2(x, y));

	sp->runAction(Sequence::create(landFadeOut, landFadeIn, NULL));

	RicherPlayer* landOwner = getPlayerByTiled(buy_land_x, buy_land_y);
	//调用之前清空displayArea
	displayVector.clear();
	switch (playerTag)
	{
	case PLAYER_1_TAG:
	{
		if (landOwner->restTimes > 0)
		{
			CocosToast::createToast(this, LanguageString::getInstance()->getLanguageString(IN_HOSPITAL)->getCString(),
				TOAST_SHOW_TIME, player1->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGPickOneToGo);
		}

		//取得地块过路费总和,播放相邻地块动画
		int retMoney = displayArea(x, y, player1, player2_building_1_tiledID, player2_building_2_tiledID, player2_building_3_tiledID);
		//地块所有者增加相应资金
		refreshMoneyLabel(landOwner, money + retMoney);
		//过路者缴纳相应资金
		refreshMoneyLabel(player1, -(money + retMoney));

		//Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		CocosToast::createToast(this, String::createWithFormat("+%d", money + retMoney)->getCString(), TOAST_SHOW_TIME + 1, landOwner->getPosition());
		CocosToast::createToast(this, String::createWithFormat("-%d", money + retMoney)->getCString(), TOAST_SHOW_TIME, player1->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGPickOneToGo);
		break;
	}
	case PLAYER_2_TAG:
	{
		if (landOwner->restTimes > 0)
		{
			CocosToast::createToast(this, 
				LanguageString::getInstance()->getLanguageString(IN_HOSPITAL)->getCString(),
				TOAST_SHOW_TIME, player2->getPosition(), 
				(SEL_CallFun)&GameBaseScene::sendMSGPickOneToGo);
			return;
		}

		int retMoney = displayArea(x, y, player2, player1_building_1_tiledID, player1_building_2_tiledID, player1_building_3_tiledID);
		refreshMoneyLabel(landOwner, money + retMoney);
		refreshMoneyLabel(player2, -(money + retMoney));
		//Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
		CocosToast::createToast(this, String::createWithFormat("+%d", money + retMoney)->getCString(), TOAST_SHOW_TIME + 1, landOwner->getPosition());
		CocosToast::createToast(this, String::createWithFormat("-%d", money + retMoney)->getCString(), TOAST_SHOW_TIME, player2->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGPickOneToGo);
		break;
	}
	}
}

RicherPlayer * GameBaseScene::getPlayerByTiled(float x, float y)
{
	int gid = landLayer->getTileGIDAt(Vec2(x, y));
	if (gid == player1_building_1_tiledID || gid == player1_building_2_tiledID || gid == player1_building_3_tiledID)
	{
		return player1;
	}
	if (gid == player2_building_1_tiledID || gid == player2_building_2_tiledID || gid == player2_building_3_tiledID)
	{
		return player2;
	}
}

int GameBaseScene::displayArea(float x, float y, RicherPlayer * player, int building_1_tiledID, int building_2_tiledID, int building_3_tiledID)
{
	int sumMoney = 0;
	float retX = Util::GL2map(player->getPosition(), _map).x;
	if (x == retX)
	{
		float leftX = x - 1;
		float rightX = x + 1;
		int leftGID = landLayer->getTileGIDAt(Vec2(leftX, y));
		int rightGID = landLayer->getTileGIDAt(Vec2(rightX, y));
		displayVector.pushBack(landLayer->getTileAt(Vec2(x, y)));
		while (leftGID != 0 && (leftGID == building_1_tiledID || leftGID == building_2_tiledID || leftGID == building_3_tiledID))
		{
			if (leftGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY;
			}
			if (leftGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY;
			}
			if (leftGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY;
			}
			displayVector.pushBack(landLayer->getTileAt(Vec2(leftX, y)));
			leftX -= 1;
			leftGID = landLayer->getTileGIDAt(Vec2(leftX, y));

			if (leftGID == 0)
			{
				break;
			}
			log("leftGID: %d", leftGID);
		}
		while (rightGID != 0 && (rightGID == building_1_tiledID || rightGID == building_2_tiledID || rightGID == building_3_tiledID))
		{
			if (rightGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY;
			}
			if (rightGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY;
			}
			if (rightGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY;
			}
			displayVector.pushBack(landLayer->getTileAt(Vec2(rightX, y)));
			rightX += 1;
			rightGID = landLayer->getTileGIDAt(Vec2(rightX, y));

			if (rightGID == 0)
			{
				break;
			}
			log("rightGID: %d", rightGID);
		}
	}

	float retY = Util::GL2map(player->getPosition(), _map).y;
	if (y == retY)
	{
		float upY = y - 1;
		float downY = y + 1;
		int upGID = landLayer->getTileGIDAt(Vec2(x, upY));
		int downGID = landLayer->getTileGIDAt(Vec2(x, downY));
		displayVector.pushBack(landLayer->getTileAt(Vec2(x, y)));
		while (upGID != 0 && (upGID == building_1_tiledID || upGID == building_2_tiledID || upGID == building_3_tiledID))
		{
			if (upGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY;
			}
			if (upGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY;
			}
			if (upGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY;
			}
			displayVector.pushBack(landLayer->getTileAt(Vec2(x, upY)));
			upY -= 1;
			upGID = landLayer->getTileGIDAt(Vec2(x, upY));

			if (upGID == 0)
			{
				break;
			}
			log("leftGID: %d", upGID);
		}
		while (downGID != 0 && (downGID == building_1_tiledID || downGID == building_2_tiledID || downGID == building_3_tiledID))
		{
			if (downGID == building_1_tiledID)
			{
				sumMoney += LAND_BLANK_MONEY;
			}
			if (downGID == building_2_tiledID)
			{
				sumMoney += LAND_LEVEL_1_MONEY;
			}
			if (downGID == building_3_tiledID)
			{
				sumMoney += LAND_LEVEL_2_MONEY;
			}
			displayVector.pushBack(landLayer->getTileAt(Vec2(x, downY)));
			downY += 1;
			downGID = landLayer->getTileGIDAt(Vec2(x, downY));

			if (downGID == 0)
			{
				break;
			}
			log("rightGID: %d", downGID);
		}
	}
	for (auto it = displayVector.begin(); it != displayVector.end(); it++)
	{
		(Sprite*)(*it)->runAction(Sequence::create(landFadeOut->clone(), landFadeIn->clone(), NULL));
	}
	return sumMoney;
}

void GameBaseScene::sendMSGPickOneToGo()
{
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));

}

void GameBaseScene::initRandomAskEvent()
{
	randomAskEventMap.insert(TAX_REBATES_KEY, LanguageString::getInstance()->getLanguageString(TAX_REBATES));
	randomAskEventMap.insert(PAY_TAXES_KEY, LanguageString::getInstance()->getLanguageString(PAY_TAXES));
	randomAskEventMap.insert(LOSS_STRENGTH_KEY, LanguageString::getInstance()->getLanguageString(LOSS_STRENGTH));
	randomAskEventMap.insert(PHYSICAL_RECOVERY_KEY, LanguageString::getInstance()->getLanguageString(PHYSICAL_RECOVERY));
	randomAskEventMap.insert(INVESTMENT_DIVIDENDS_KEY, LanguageString::getInstance()->getLanguageString(INVESTMENT_DIVIDENDS));
	randomAskEventMap.insert(INVESTMENT_LOSS_KEY, LanguageString::getInstance()->getLanguageString(INVESTMENT_LOSS));
}

void GameBaseScene::sendMSGDealAroundLand()
{
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_AROUND_LAND_TAG));
}

void GameBaseScene::doRandomAskEvent(RicherPlayer * player)
{
	int randomNumber = rand() % (randomAskEventMap.size()) + 1;
	__String * str = randomAskEventMap.at(randomNumber);

	switch (randomNumber)
	{
		case TAX_REBATES_KEY:
		{
			refreshMoneyLabel(player, 10000);
			break;
		}
		case PAY_TAXES_KEY:
		{
			refreshMoneyLabel(player, -20000);
			break;
		}

		case LOSS_STRENGTH_KEY:
		{
			refreshStrengthLabel(player, -100);
			break;
		}
		case PHYSICAL_RECOVERY_KEY:
		{
			refreshStrengthLabel(player, 100);
			break;
		}
		case INVESTMENT_DIVIDENDS_KEY:
		{
			refreshMoneyLabel(player, 20000);
			break;
		}
		case INVESTMENT_LOSS_KEY:
		{
			refreshMoneyLabel(player, -30000);
			break;
		}
	}
	CocosToast::createToast(this, str->getCString(), TOAST_SHOW_TIME, player->getPosition(), (SEL_CallFun)&GameBaseScene::sendMSGDealAroundLand);
}

void GameBaseScene::refreshStrengthLabel(RicherPlayer * player, int strength)
{
	int tag = player->getTag();
	int totalStrength = player->getStrength() + strength;
	if (totalStrength > 100) totalStrength = 100;
	if (totalStrength < 0) totalStrength = 0;
	player->setStrength(totalStrength);

	if (tag == PLAYER_1_TAG)
	{
		memset(strength1, 0, 20);
		sprintf(strength1, "+ %d", player->getStrength());
		getPlayer1_strength_label()->setString(strength1);
	}
	if (tag == PLAYER_2_TAG)
	{
		memset(strength2, 0, 20);
		sprintf(strength2, "+ %d", player->getStrength());
		getPlayer2_strength_label()->setString(strength2);
	}
}

void GameBaseScene::initPropSprite()
{
	_strength_up = Strength_up::create();
	addChild(_strength_up);
	_strength_up->setVisible(false);
	_strength_up->setAnchorPoint(Vec2(0, 0.5));
	//创建蜜蜂精灵
	_bee = Bee::create();
	addChild(_bee);
	//让蜜峰重复运动
	_bee->runAction(RepeatForever::create(_bee->getNormal_anmi()));
	//刚添加到场景,设置为不可见
	_bee->setVisible(false);
	//创建救护车精灵
	_emergency = Emergency::create();
	addChild(_emergency);
	_emergency->setVisible(false);
	//创建烟雾精灵
	_fog = Fog::create();
	addChild(_fog);
	_fog->setVisible(false);
	//创建担架精灵
	_stretcher = Stretcher::create();
	addChild(_stretcher);
	_stretcher->setVisible(false);
	_stretcher->setAnchorPoint(Vec2(0, 0.9));
	//珍珠精灵
	_pearl = Pearl::create();
	addChild(_pearl);
	_pearl->runAction(RepeatForever::create(_pearl->getNormal_anmi()));
	_pearl->setVisible(false);
	

}

void GameBaseScene::doItemStrengthUp(int strengthUp, int playerTag)
{
	int strengthValue = 0;
	switch (strengthUp)
	{
		case MSG_STRENGTH_UP30_TAG:
		{
			strengthValue = 30;
			break;
		}
		case MSG_STRENGTH_UP50_TAG:
		{
			strengthValue = 50;
			break;
		}
		case MSG_STRENGTH_UP80_TAG:
		{
			strengthValue = 80;
			break;
		}
	}
	RicherPlayer* tmp;
	switch (playerTag)
	{
		case PLAYER_1_TAG:
		{
			tmp = player1;
			break;
		}
		case PLAYER_2_TAG:
		{
			tmp = player2;
			break;
		}
	}
	_strength_up->setVisible(true);
	_strength_up->setPosition(tmp->getPosition() - Vec2(5, 0));
	Sequence* action = Sequence::create(_strength_up->getNormal_anmi(),
		CallFunc::create([this]() {
		_strength_up->setVisible(false);
		sendMSGDealAroundLand();
	}
	), NULL);
	_strength_up->runAction(action);
	CocosToast::createToast(this,
		String::createWithFormat("%s %d", LanguageString::getInstance()->getLanguageString(STRENGTH_UP)->getCString(), strengthValue)->getCString(),
		TOAST_SHOW_TIME, tmp->getPosition());
	refreshStrengthLabel(tmp, strengthValue);
}

void GameBaseScene::registerBlockWaySchedule()
{
	//每隔10秒调用方法
	schedule(schedule_selector(GameBaseScene::updateBlockWaySprites), 10.f);

}

void GameBaseScene::updateBlockWaySprites(float dt)
{
	int _rand1 = rand() % (wayLayerPass_vector.size());
	Vec2 position = wayLayerPass_vector.at(_rand1);
	position.x += 5;
	position.y += tiledHeight;
	_bee->setVisible(true);
	_bee->setPosition(position);
	_bee->setAnchorPoint(Vec2(0, 0.6));

	int _rand2 = rand() % (wayLayerPass_vector.size());
	Vec2 position2 = wayLayerPass_vector.at(_rand2);
	_pearl->setVisible(true);
	_pearl->setPosition(position2);
	_pearl->setAnchorPoint(Vec2(0, 0));

}

void GameBaseScene::doBlockWayEvent(RicherPlayer* player)
{
	
	if (player->getBoundingBox().containsPoint(_bee->getPosition() + Vec2(_bee->getContentSize().width / 2, -_bee->getContentSize().height / 2)))
	{
		_bee->setPosition(Vec2(-200, -200));
		player->restTimes = rand() % (5) + 1;

		//救护车设置
		_emergency->setVisible(true);
		int distance = tableStartPosition_x - player->getPosition().x;
		_emergency->setPosition(player->getPosition() + Vec2(distance, 0));
		//烟雾设置
		_fog->setVisible(true);
		_fog->setPosition(player->getPosition());
		Repeat* repeate0 = Repeat::create(_fog->getNormal_anmi(), 2);
		_fog->runAction(repeate0);

		MoveBy* moveBy = MoveBy::create(1.0f, Vec2(-distance, 0));
		MoveBy* moveBy2 = MoveBy::create(0.5f, Vec2(-60, 0));
		Repeat* repeate = Repeat::create(_emergency->getCar_go_anmi(), 5);
		Repeat* repeate2 = Repeat::create(_emergency->getCar_stop_anmi(), 1);

		Sequence* spawnAction = Sequence::create(Spawn::create(moveBy, repeate, NULL),
			Spawn::create(moveBy2, repeate2, NULL),
			CallFunc::create(std::bind(&GameBaseScene::endCarGo, this, player->getTag())), NULL);
		spawnAction->retain();
		_emergency->runAction(spawnAction);

		CocosToast::createToast(this, String::createWithFormat("%s %d %s", LanguageString::getInstance()->getLanguageString(PLAYER_HURT)->getCString(), player->restTimes, LanguageString::getInstance()->getLanguageString(RICH_DAY)->getCString())->getCString(), TOAST_SHOW_TIME, player->getPosition());
	}else if (player->getBoundingBox().intersectsRect(_pearl->getBoundingBox()))
	{
		_pearl->setPosition(Vec2(-200, -200));
		int money = 20000;
		refreshMoneyLabel(player, money);
		CocosToast::createToast(this, String::createWithFormat("%s %d",
			LanguageString::getInstance()->getLanguageString(PICK_BALL)->getCString(),
			money)->getCString(), TOAST_SHOW_TIME, player->getPosition(),
			(SEL_CallFun)&GameBaseScene::sendMSGDealProp);
	}
	else
	{
		Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_HANDLE_PROP_EVENT_TAG));
	}
}

void GameBaseScene::endCarGo(int tag)
{
	_stretcher->setVisible(true);
	_stretcher->setPosition(_emergency->getPosition());
	MoveBy* moveBy = MoveBy::create(0.5f, Vec2(60, 0));
	ScaleBy* scaleBy = ScaleBy::create(0.5f, 0.8);
	Repeat* repeate = Repeat::create(_stretcher->getStretcher_empty_anmi(), 1);
	ScaleBy* scaleBy2 = ScaleBy::create(0.5f, 1.25);
	MoveBy* moveBy2 = MoveBy::create(0.5f, Vec2(-60, 0));
	Repeat* repeate2 = Repeat::create(_stretcher->getStretcher_full_anmi(), 1);
	Sequence* spawnAction = Sequence::create(
		Spawn::create(moveBy, scaleBy, repeate, CallFunc::create(CC_CALLBACK_0(GameBaseScene::setPlayerAndFogInVisible, this, tag)), NULL),
		Spawn::create(moveBy2, scaleBy2, repeate2, NULL), CallFunc::create(CC_CALLBACK_0(GameBaseScene::startCarGoAgain, this)), NULL);
	spawnAction->retain();
	_stretcher->runAction(spawnAction);

	//throw std::logic_error("The method or operation is not implemented.");
}

void GameBaseScene::sendMSGDealProp()
{
	Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_HANDLE_PROP_EVENT_TAG));
}

