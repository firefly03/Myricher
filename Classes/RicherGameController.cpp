#include "RicherGameController.h"
#include "GameBaseScene.h"

RicherGameController* RicherGameController::richerGameController_Instance = NULL;

bool RicherGameController::init()
{
	if (!Layer::init())
	{
		return false;
	}
	callEndGoFunc = CallFunc::create(CC_CALLBACK_0(RicherGameController::endGo, this));
	registerNotificationObserver();

	positionAroundEnd = new float*[4];
	for (int i = 0; i < 4; i++)
		positionAroundEnd[i] = new float[2];

	return true;
}

RicherGameController* RicherGameController::getInstance()
{
	if (!richerGameController_Instance)
	{
		richerGameController_Instance = RicherGameController::create();
	}
	richerGameController_Instance->retain();
	return richerGameController_Instance;
}

RicherGameController::~RicherGameController()
{
	spawnAction->release();
}

void RicherGameController::moveOneStep(RicherPlayer* richerPlayer)
{
	nextRow = _rowVector[stepHasGone + 1];
	nextCol = _colVector[stepHasGone + 1];
	int distanceRow = nextRow - currentRow;
	int distanceCol = nextCol - currentCol;

	if (distanceRow >0)//up
	{
		moveBy = MoveBy::create(playerGoTotalTime, Vec2(0, tiledHeight));
		repeate = Repeat::create(richerPlayer->getUp(), 1);
	}
	if (distanceRow <0)//down
	{
		moveBy = MoveBy::create(playerGoTotalTime, Vec2(0, -tiledHeight));
		repeate = Repeat::create(richerPlayer->getDown(), 1);
	}
	if (distanceCol >0)//right
	{
		moveBy = MoveBy::create(playerGoTotalTime, Vec2(tiledWidth, 0));
		repeate = Repeat::create(richerPlayer->getRight(), 1);
	}
	if (distanceCol <0)//left
	{
		moveBy = MoveBy::create(playerGoTotalTime, Vec2(-tiledWidth, 0));
		repeate = Repeat::create(richerPlayer->getLeft(), 1);
	}

	spawnAction = Sequence::create(Spawn::create(moveBy, repeate, NULL), callEndGoFunc, NULL);
	spawnAction->retain();
	richerPlayer->runAction(spawnAction);
}

void RicherGameController::handlePropEvent()
{
	
	float playerEnd_X = _colVector[stepsCount] * 32;
	float playerEnd_Y = _rowVector[stepsCount] * 32 + 32;

	Point pointInMap = Util::GL2map(Vec2(playerEnd_X, playerEnd_Y), GameBaseScene::_map);
	int endId = GameBaseScene::wayLayer->getTileGIDAt(pointInMap);
	if (endId == GameBaseScene::randomEvent_tiledID)
	{
		String * str = String::createWithFormat("%d-%f-%f-%d", MSG_RANDOM_ASK_EVENT_TAG, pointInMap.x, pointInMap.y, _richerPlayer->getTag());
		Util::sendCustomEvent(RICHER_MSG, str);
		return;
	}
	if (endId == GameBaseScene::strength_30_tiledID)
	{
		String * str = String::createWithFormat("%d-%d", MSG_STRENGTH_UP30_TAG, _richerPlayer->getTag());
		Util::sendCustomEvent(RICHER_MSG, str);
		return;
	}

	if (endId == GameBaseScene::strength_50_tiledID)
	{
		String * str = String::createWithFormat("%d-%d", MSG_STRENGTH_UP50_TAG, _richerPlayer->getTag());
		Util::sendCustomEvent(RICHER_MSG, str);
		return;
	}

	if (endId == GameBaseScene::strength_80_tiledID)
	{
		String * str = String::createWithFormat("%d-%d", MSG_STRENGTH_UP80_TAG, _richerPlayer->getTag());
		Util::sendCustomEvent(RICHER_MSG, str);
		return;
	}


	aroundLandEvent();
}

void RicherGameController::aroundLandEvent()
{
	float playerEnd_X = _colVector[stepsCount] * 32;
	float playerEnd_Y = _rowVector[stepsCount] * 32 + 32;
	// up
	positionAroundEnd[0][0] = playerEnd_X;
	positionAroundEnd[0][1] = playerEnd_Y + 32;
	// down
	positionAroundEnd[1][0] = playerEnd_X;
	positionAroundEnd[1][1] = playerEnd_Y - 32;
	// left
	positionAroundEnd[2][0] = playerEnd_X - 32;
	positionAroundEnd[2][1] = playerEnd_Y;
	// right
	positionAroundEnd[3][0] = playerEnd_X + 32;
	positionAroundEnd[3][1] = playerEnd_Y;

	//地块购买分析
	for (int i = 0; i < 4; i++)
	{
		Point ptMap = Util::GL2map(Vec2(positionAroundEnd[i][0], positionAroundEnd[i][1]), GameBaseScene::_map);
		int titleId = GameBaseScene::landLayer->getTileGIDAt(ptMap);
		int x = ptMap.x;
		int y = ptMap.y;
		if (titleId == GameBaseScene::blank_land_tiledID)
		{
			//send a message to show buy dialog			
			String * str = String::createWithFormat("%d-%d-%d-%d", MSG_BUY_BLANK_TAG, x, y, _richerPlayer->getTag());
			Util::sendCustomEvent(RICHER_MSG, str);
			break;
		}
		if (titleId == GameBaseScene::player1_building_1_tiledID)
		{
			if (_richerPlayer->getTag() == PLAYER_1_TAG)
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_BUY_LAND_1_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			else
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_PAY_TOLLS_1_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}

			break;
		}
		if (titleId == GameBaseScene::player1_building_2_tiledID)
		{
			if (_richerPlayer->getTag() == PLAYER_1_TAG)
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_BUY_LAND_2_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			else
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_PAY_TOLLS_2_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			break;
		}

		if (titleId == GameBaseScene::player1_building_3_tiledID)
		{
			if (_richerPlayer->getTag() != PLAYER_1_TAG)
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_PAY_TOLLS_3_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			else
			{
				Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			}
			break;
		}

		if (titleId == GameBaseScene::player2_building_1_tiledID)
		{
			if (_richerPlayer->getTag() == PLAYER_2_TAG)
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_BUY_LAND_1_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			else
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_PAY_TOLLS_1_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			break;
		}
		if (titleId == GameBaseScene::player2_building_2_tiledID)
		{
			if (_richerPlayer->getTag() == PLAYER_2_TAG)
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_BUY_LAND_2_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			else
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_PAY_TOLLS_2_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			break;
		}
		if (titleId == GameBaseScene::player2_building_3_tiledID)
		{
			if (_richerPlayer->getTag() != PLAYER_2_TAG)
			{
				String * str = String::createWithFormat("%d-%d-%d-%d", MSG_PAY_TOLLS_3_TAG, x, y, _richerPlayer->getTag());
				Util::sendCustomEvent(RICHER_MSG, str);
			}
			else
			{
				Util::sendCustomEvent(RICHER_CONTROLLER_MSG, String::createWithFormat("%d", MSG_PICKONE_TOGO_TAG));
			}
			break;
		}
	}


}

void RicherGameController::resetPlayerGoTrun()
{
	for (auto it = GameBaseScene::players_vector.begin();it != GameBaseScene::players_vector.end();it++)
	{
		RicherPlayer* richerPlayer = dynamic_cast<RicherPlayer*>(*it);
		richerPlayer->setIsMyTurn(true);
		//每一回合结束,角色的restTimes减1
		richerPlayer->restTimes--;
		if (richerPlayer->restTimes<0)
		{
			richerPlayer->restTimes = 0;
		}
	}

	//发送MSG_ROUND_COUNT更新回合数
	Util::sendCustomEvent(RICHER_MSG, String::createWithFormat("%d", MSG_ROUND_COUNT_TAG));
	pickOnePlayerToGo();

	//throw std::logic_error("The method or operation is not implemented.");
}

void RicherGameController::startRealGo(std::vector<int> rowVector, std::vector<int> colVector, RicherPlayer* richerPlayer)
{
	//角色第一个位置的行列值
	currentRow = rowVector[0];
	currentCol = colVector[0];
	//角色下一步的行列值 
	nextRow = 0;
	nextCol = 0;
	//根据参数给相应变量赋值
	_rowVector = rowVector;
	_colVector = colVector;
	_richerPlayer = richerPlayer;
	//动画是否结束
	isAnimFinished = false;
	//角色已经走了几步
	stepHasGone = 0;
	//取得路径需要走的步数
	stepsCount = _rowVector.size() - 1;
	//开始行走,先走一步
	moveOneStep(richerPlayer);
}

void RicherGameController::endGo()
{
	GameBaseScene::pathMarkVector.at(stepHasGone)->setVisible(false);
	stepHasGone++;
	if (stepHasGone >= stepsCount)
	{
		//_richerPlayer->setIsMyTurn(false);

		//pickOnePlayerToGo();
		//handlePropEvent();
		String* str = String::createWithFormat("%d-%d", MSG_BLOCK_WAY_EVENT_TAG, _richerPlayer->getTag());
		Util::sendCustomEvent(RICHER_MSG, str);
		return;
	}
	currentRow = nextRow;
	currentCol = nextCol;
	moveOneStep(_richerPlayer);
	log("go end");
}
void RicherGameController::pickOnePlayerToGo()
{
	for (auto it = GameBaseScene::players_vector.begin(); it!= GameBaseScene::players_vector.end(); it++)
	{
		RicherPlayer* richerPlayer = dynamic_cast<RicherPlayer*>(*it);
		
		//如果轮到角色行走,但是在休息
		if (richerPlayer->getIsMyTurn()&& richerPlayer->restTimes > 0)
		{
			String* str = String::createWithFormat("%d-%d", MSG_REST_TAG, richerPlayer->getTag());
			Util::sendCustomEvent(RICHER_MSG, str);
			return;
		}

		if (richerPlayer->getIsMyTurn() && richerPlayer->restTimes == 0)
		{
			richerPlayer->setVisible(true);
			//角色1发送MSG_GO消息,显示go按钮
			if (richerPlayer->getTag()== PLAYER_1_TAG)
			{
				Util::sendCustomEvent(RICHER_MSG, String::createWithFormat("%d", MSG_GO_SHOW_TAG));
				return;
			}
			//其它角色获取路径,自动行走
			int randNumber = rand() % 6 + 1;
			RouteNavigation::getInstance()->getPath(richerPlayer, randNumber,
				GameBaseScene::canPassGrid,
				GameBaseScene::tiledRowsCount, GameBaseScene::tiledColsCount);
			richerPlayer->startGo(RouteNavigation::getInstance()->getPathRow_vector(),
				RouteNavigation::getInstance()->getPathCols_vector());
			return;

		}

	}

	//重新设置角色
	resetPlayerGoTrun();


	/*for (auto it = GameBaseScene::players_vector.begin(); it != GameBaseScene::players_vector.end(); it++)
	{
		RicherPlayer* richerPlayer = dynamic_cast<RicherPlayer*>(*it);
		richerPlayer->setIsMyTurn(true);

	}
	

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	EventCustom _event = EventCustom(RICHER_MSG);
	_event.setUserData(String::createWithFormat("%d", MSG_GO_SHOW_TAG));
	dispatcher->dispatchEvent(&_event);*/
}


void RicherGameController::registerNotificationObserver()
{
	/*
	NotificationCenter::getInstance()->addObserver(
	this,
	callfuncO_selector(RicherGameController::receivedMsg),
	RICHER_CONTROLLER_MSG,
	NULL);

	*/
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	controllerCustomListener = EventListenerCustom::create(RICHER_CONTROLLER_MSG, CC_CALLBACK_1(RicherGameController::receivedMsg, this));
	dispatcher->addEventListenerWithFixedPriority(controllerCustomListener, 1);
}

void RicherGameController::receivedMsg(EventCustom* event)
{
	String* srcDate = (String*)event->getUserData();

	int retMsgType = srcDate->intValue();

	if (retMsgType == MSG_PICKONE_TOGO_TAG)
	{
		pickOnePlayerToGo();
	}
	if (retMsgType == MSG_AROUND_LAND_TAG)
	{
		aroundLandEvent();
	}
	if (retMsgType == MSG_HANDLE_PROP_EVENT_TAG)
	{
		handlePropEvent();
	}
}
