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
	//角色帧
	SpriteFrameCache* player_spriteFrameCache;

	//资金默认5万,体力100
	static RicherPlayer* create(char* name, int tag, int money = 50000, int strength = 100);

	bool init(char* name, int tag, int money, int strength);
	void startGo(std::vector<int> rowVector, std::vector<int> colVector);
	//定义动画所需要的四个容器
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_left_vector, Anim_left_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_right_vector, Anim_right_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_down_vector, Anim_down_vector);
	CC_SYNTHESIZE(Vector<SpriteFrame*>, player_anim_up_vector, Anim_up_vector);

	//定义四个动画对象
	CC_SYNTHESIZE(Animate*, left, Left);
	CC_SYNTHESIZE(Animate*, right, Right);
	CC_SYNTHESIZE(Animate*, down, Down);
	CC_SYNTHESIZE(Animate*, up, Up);

	//添加角色动画
	void addPlayerAnimation();
	//设置动画
	void setPlayerAnimate();
	//角色受伤,住院回合数
	int restTimes;
private:
	//角色的名称
	CC_SYNTHESIZE(std::string, _sname, SName);
	//角色资金
	CC_SYNTHESIZE(int, _money, Money);
	//角色体力
	CC_SYNTHESIZE(int, _strength, Strength);
	//角色从哪个行过来
	CC_SYNTHESIZE(int, _comeFromeRow, ComeFromRow);
	//角色从哪个列过来
	CC_SYNTHESIZE(int, _comeFromeCol, ComeFromCol);
	//角色行走
	CC_SYNTHESIZE(bool, _isMyTurn, IsMyTurn);

};

#endif