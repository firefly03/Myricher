#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;
const float playerGoPerFrameTime = 0.07f;

class RicherPlayer : public Sprite
{
public:
	RicherPlayer();
	~RicherPlayer();
	//��ɫ֡
	SpriteFrameCache* player_spriteFrameCache;

	//�ʽ�Ĭ��5��,����100
	static RicherPlayer* create(char* name, int tag, int money = 50000, int strength = 100);

	bool init(char* name, int tag, int money, int strength);
	void startGo(std::vector<int> rowVector, std::vector<int> colVector);
	//���嶯������Ҫ���ĸ�����
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_left_vector, Anim_left_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_right_vector, Anim_right_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_down_vector, Anim_down_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_up_vector, Anim_up_vector);

	//�����ĸ���������
	CC_SYNTHESIZE(Animate*, left, Left);
	CC_SYNTHESIZE(Animate*, right, Right);
	CC_SYNTHESIZE(Animate*, down, Down);
	CC_SYNTHESIZE(Animate*, up, Up);

	//��ӽ�ɫ����
	void addPlayerAnimation();
	//���ö���
	void setPlayerAnimate();
	//��ɫ����,סԺ�غ���
	int restTimes;
private:
	//��ɫ������
	CC_SYNTHESIZE(std::string, _sname, SName);
	//��ɫ�ʽ�
	CC_SYNTHESIZE(int, _money, Money);
	//��ɫ����
	CC_SYNTHESIZE(int, _strength, Strength);
	//��ɫ���ĸ��й���
	CC_SYNTHESIZE(int, _comeFromeRow, ComeFromRow);
	//��ɫ���ĸ��й���
	CC_SYNTHESIZE(int, _comeFromeCol, ComeFromCol);
	//��ɫ����
	CC_SYNTHESIZE(bool, _isMyTurn, IsMyTurn);

};

#endif