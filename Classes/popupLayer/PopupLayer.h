#ifndef __Richer_PopupLayer__
#define __Richer_PopupLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;
const int Pop_FontSize = 20;

enum POP_TYPE
{
	NORMAL,
};

class PopupLayer :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(PopupLayer);

	POP_TYPE pop_type;
	void setPopType(POP_TYPE type);
	void setPopModalDialog(bool mD);
	static PopupLayer * create(const char* backgroundImage);
	//设置对话框类型
	void setTitle(const char* title, int fontsize = Pop_FontSize);
	//设置文本框类型
	void setContentText(const char* text, int fontsize = Pop_FontSize, int padding = 50, int paddintTop = 100);
	//把调用者和其处理方法设置为按键回调方法
	void setCallbackFunc(Object* target, SEL_CallFuncN callfun);
	//添加对话框按键.如确认,取消
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);
	virtual void onEnter();
	virtual void onExit();

private:

	//按钮点击调用的方法
	void buttonCallback(CCObject* pSender);

	int m_contentPadding = 0;
	int m_contentPaddingTop = 0;;
	Object* m_callbackListener;
	SEL_CallFuncN m_callback;
	CC_SYNTHESIZE_RETAIN(Menu*, m__pMenu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, m__sfBackGround, SpriteBackGround);
	CC_SYNTHESIZE_RETAIN(Scale9Sprite*, m__s9BackGround, Sprite9BackGround);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltTitle, LabelTitle);
	CC_SYNTHESIZE_RETAIN(LabelTTF*, m__ltContentText, LabelContentText);
	CC_SYNTHESIZE(int, dataTag, DataTag);

};

#endif