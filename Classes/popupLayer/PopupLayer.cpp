#include "PopupLayer.h"

bool PopupLayer::init()
{
	if (!Layer::init())
		return false;

	m__pMenu = NULL;
	m_callbackListener = NULL;
	m_callback = NULL;
	m__sfBackGround = NULL;
	m__s9BackGround = NULL;
	m__ltContentText = NULL;
	m__ltTitle = NULL;
	this->setContentSize(Size::ZERO);
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	setMenuButton(menu);
	
	/*auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch* touch, Event* event) {
		log("PopupLayer touch");
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);*/
	return true;
}

//对话框创建
PopupLayer* PopupLayer::create(const char *backgroundImage)
{
	PopupLayer* ml = PopupLayer::create();
	ml->setSprite9BackGround(Scale9Sprite::create(backgroundImage));
	return ml;
}

//设置对话框类型
void PopupLayer::setPopType(POP_TYPE type)
{
	pop_type = type;
}

void PopupLayer::setPopModalDialog(bool mD)
{
	//如果为true,则是需要屏蔽界面的事件响应
	if (mD)
	{
		auto listener = EventListenerTouchOneByOne::create();
		//不向下传递触摸
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [](Touch* touch, Event* event) {
			log("PopupLayer touch");
			//返回true,让对话框处理掉该事件,阻止向下层传递
			return true;
		};
		//添加事件监听
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
}

//设置对话框标题
void PopupLayer::setTitle(const char *title, int fontsize)
{
	LabelTTF* ltfTitle = LabelTTF::create(title, "", fontsize);
	setLabelTitle(ltfTitle);
}

//设置对话框文本和边距
void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop)
{
	LabelTTF* ltf = LabelTTF::create(text, "", fontsize);
	setLabelContentText(ltf);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

//设置调用对象和响应方法
void PopupLayer::setCallbackFunc(cocos2d::Object *target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}


bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);

	MenuItemImage* menuImage = MenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallback));
	menuImage->setTag(tag);
	menuImage->setPosition(pCenter);

	Size imenu = menuImage->getContentSize();
	LabelTTF* ttf = LabelTTF::create(title, "", 20);
	ttf->setColor(ccc3(0, 0, 0));
	ttf->setPosition(Vec2(imenu.width / 2, imenu.height / 2));
	menuImage->addChild(ttf);

	getMenuButton()->addChild(menuImage);
	return true;
}
void PopupLayer::buttonCallback(cocos2d::CCObject *pSender)
{

	Node* node = dynamic_cast<Node*>(pSender);
	log("touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener) {
		(m_callbackListener->*m_callback)(node);
	}
}

void PopupLayer::onEnter()
{
	Layer::onEnter();
	Size winSize = Director::getInstance()->getWinSize();
	Point pCenter = Vec2(winSize.width / 2, winSize.height / 2);
	Size contentSize;
	Scale9Sprite *background = getSprite9BackGround();
	background->setContentSize(getContentSize());

	background->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(background, 0, 0);
	contentSize = getContentSize();

	this->addChild(getMenuButton());
	float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
	Vector<Node*> vecArray = getMenuButton()->getChildren();

	int j = 0;
	for (auto it = vecArray.begin(); it != vecArray.end(); it++)
	{
		Node* node = dynamic_cast<Node*>(*it);
		node->setPosition(Point(winSize.width / 2 - contentSize.width / 2 + btnWidth*(j + 1), winSize.height / 2 - contentSize.height / 3));
		j++;
	}

	if (getLabelTitle())
	{
		getLabelTitle()->setPosition(ccpAdd(pCenter, Vec2(0, contentSize.height / 2 - 20)));
		getLabelTitle()->setColor(ccc3(0, 0, 0));
		this->addChild(getLabelTitle());
	}

	switch (pop_type)
	{

	default:
	{
		if (getLabelContentText())
		{
			LabelTTF* ltf = getLabelContentText();
			ltf->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
			ltf->setDimensions(CCSizeMake(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
			ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
			ltf->setColor(ccc3(0, 0, 0));
			this->addChild(ltf);
		}
	}
	}


	Action* popupLayer = Sequence::create(ScaleTo::create(0.0, 1),
		ScaleTo::create(0.15, 1.05),
		ScaleTo::create(0.08, 0.95),
		ScaleTo::create(0.08, 1.0),
		NULL);
	this->runAction(popupLayer);

}

void PopupLayer::onExit()
{
	Layer::onExit();
	log("popup on exit");
	CC_SAFE_RELEASE(m__pMenu);
	CC_SAFE_RELEASE(m__sfBackGround);
	CC_SAFE_RELEASE(m__ltContentText);
	CC_SAFE_RELEASE(m__ltTitle);
	CC_SAFE_RELEASE(m__s9BackGround);
}

