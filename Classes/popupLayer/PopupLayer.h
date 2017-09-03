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
	//���öԻ�������
	void setTitle(const char* title, int fontsize = Pop_FontSize);
	//�����ı�������
	void setContentText(const char* text, int fontsize = Pop_FontSize, int padding = 50, int paddintTop = 100);
	//�ѵ����ߺ��䴦��������Ϊ�����ص�����
	void setCallbackFunc(Object* target, SEL_CallFuncN callfun);
	//��ӶԻ��򰴼�.��ȷ��,ȡ��
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);
	virtual void onEnter();
	virtual void onExit();

private:

	//��ť������õķ���
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