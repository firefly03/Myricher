#ifndef __CONSTUTIL_H__
#define __CONSTUTIL_H__


#define FU1_IMAGE     "fu1.png"
#define WENG_IMAGE     "weng.png"
#define FU2_IMAGE      "fu2.png"
#define PO_IMAGE      "po.png"

#define NORMAL_MENU   "normal_menu.png"
#define PRESS_MENU    "press_menu.png"
#define MENU_LOGO     "menuLogo.png"
#define RAINBOW       "rainbow.png"

#define FONT_MENU     "Marker Felt"

#define SINGLE_GAME   "single_game"
#define MULTI_GAME    "multi_game"
#define MUSIC_ON      "music_on"
#define MUSIC_OFF     "music_off"
#define LOAD_GAME     "load_game"
#define QUIT_GAME     "quit_game"

#define MUSIC_ON_KEY  "music_on_key"


#define  DIALOG_BG "popuplayer/dialog_bg.png"
#define  BUTTON_BG1 "popuplayer/button_bg1.png"
#define  BUTTON_BG2 "popuplayer/button_bg2.png"
#define  BUTTON_BG3 "popuplayer/button_bg3.png"

#define DIALOG_TITLE  "dialog_title"
#define DIALOG_CONTENT "dialog_content"
#define OK "yes"
#define CANCEL "no"

#define STAGE_BACKGROUND "map/stage_background2.png"
#define MAP_1 "map/map_1.png"
#define MAP_2 "map/map_2.png"
#define MAP_3 "map/map_3.png"

#define RIGHT_BANNER "map/right_banner.png"
#define PLAYER_1 "map/player1.png"
#define PLAYER_2 "map/player2.png"

#define PLAYER1_ANIM_PLIST   "images/player1_anim.plist"
#define PLAYER1_ANIM_PNG "images/player1_anim.png"

#define PLAYER2_ANIM_PLIST "images/player2_anim.plist"
#define PLAYER2_ANIM_PNG "images/player2_anim.png"

#define PLAYER_1_NAME "player1"
const int PLAYER_1_TAG = 1;
#define PLAYER_2_NAME "player2"
const int PLAYER_2_TAG = 2;

#define RICHER_MSG "richer_msg"

const int MSG_GO_HIDE_TAG = 0;
const int MSG_GO_SHOW_TAG = 1;
const int MSG_BUY_BLANK_TAG = 2;	//����հ׵ؿ���Ϣ��tag��ʾ
const int MSG_BUY_LAND_1_TAG = 3;	//����ȼ�1�ؿ���Ϣ��tag��ʾ
const int MSG_BUY_LAND_2_TAG = 4;	//����ȼ�2�ؿ����Ϣtag��ʾ
const int MSG_PICKONE_TOGO_TAG = 5;	//��ȡһ����ɫ��ʼ���ߵ�tag��ʾ
const int MSG_PAY_TOLLS_1_TAG = 6;	//�ɷѵȼ�
const int MSG_PAY_TOLLS_2_TAG = 7;
const int MSG_PAY_TOLLS_3_TAG = 8;

const int MSG_AROUND_LAND_TAG = 9;		//��ɫ�������ҵؿ���ϢTag
const int MSG_RANDOM_ASK_EVENT_TAG = 10;	//�ʺ�����¼�tag

const int MSG_BLOCK_WAY_EVENT_TAG = 11;	//��·��������Ϣ
const int MSG_HANDLE_PROP_EVENT_TAG = 12;	//��������¼���Ϣ
const int MSG_ROUND_COUNT_TAG = 13;		//�����ɫ�ܱߵؿ���Ϣ
const int MSG_REST_TAG = 14;		//��ɫ��Ϣ��Ϣ

const int LAND_BLANK_MONEY = 1000;	//����հ׵ؿ���ʽ�
const int LAND_LEVEL_1_MONEY = 2000;	//����ȼ�1�ؿ���Ҫ���ʽ�
const int LAND_LEVEL_2_MONEY = 3000;	//����ȼ�1�ؿ���Ҫ���ʽ�


const int MSG_STRENGTH_UP30_TAG = 15;	//30����
const int MSG_STRENGTH_UP50_TAG = 16;	//50����
const int MSG_STRENGTH_UP80_TAG = 17;	//80����

#define DIGITAL_0 "digital_0.png"
#define DIGITAL_1 "digital_1.png"
#define DIGITAL_2 "digital_2.png"
#define DIGITAL_3 "digital_3.png"
#define DIGITAL_4 "digital_4.png"
#define DIGITAL_5 "digital_5.png"
#define DIGITAL_6 "digital_6.png"
#define DIGITAL_7 "digital_7.png"
#define DIGITAL_8 "digital_8.png"
#define DIGITAL_9 "digital_9.png"

#define PATH_MARK_1 "images/mark1.png"
#define PATH_MARK_2 "images/mark2.png"
#define PATH_MARK_3 "images/mark3.png"
#define PATH_MARK_4 "images/mark4.png"
#define PATH_MARK_5 "images/mark5.png"
#define PATH_MARK_6 "images/mark6.png"

const int Dialog_Size_Width = 400;	//�Ի�����
const int Dialog_Size_Height = 220;	//�Ի���߶�

const int Btn_OK_TAG = 1;	//ȷ�ϰ�����tag
const int Btn_Cancel_TAG = 0;	//ȡ��������tag

#define RICHER_CONTROLLER_MSG "richer_controller_msg"	//��������Ϣ����

//����Ч��
#define PLAYER1_1_PARTICLE_PNG "images/foot1.png"
#define PLAYER2_1_PARTICLE_PNG "images/foot2.png"

#define PLAYER1_2_PARTICLE_PNG "images/starfish1.png"
#define PLAYER2_2_PARTICLE_PNG "images/starfish2.png"

#define PLAYER1_3_PARTICLE_PNG "images/heart1.png"
#define PLAYER2_3_PARTICLE_PNG "images/heart2.png"

#define PLAYER1_1_PARTICLE_PLIST "images/showClick.plist"
#define PLAYER2_1_PARTICLE_PLIST "images/fire.plist"


const float TOAST_SHOW_TIME = 2.0f;	//label��ʾʱ��

#define  BUY_LAND_MSG "buy_land_msg"	//������Ϣ

const int TAX_REBATES_KEY = 1;			//��������Ͷ�ʣ�����˰��10000
const int PAY_TAXES_KEY = 2;			//�����ϲ����񣬲���˰��20000
const int LOSS_STRENGTH_KEY = 3;		//�ȵ��پƣ�������к�������Ĺ�
const int PHYSICAL_RECOVERY_KEY = 4;	//���˴��裬�����ָ�
const int INVESTMENT_DIVIDENDS_KEY = 5;	//Ͷ�ʻ������ֺ�20000
const int INVESTMENT_LOSS_KEY = 6;		//Ͷ��ʧ�ܣ�����30000

#define  TAX_REBATES  "tax_rebates"						//��������Ͷ�ʣ�����˰��10000
#define  PAY_TAXES "pay_taxes"							//�����ϲ����񣬲���˰��20000
#define  LOSS_STRENGTH "loss_strength"					//�ȵ��پƣ�������к�������Ĺ�
#define  PHYSICAL_RECOVERY "physical_recovery"			//���˴��裬�����ָ�
#define  INVESTMENT_DIVIDENDS "investment_dividends"	//Ͷ�ʻ������ֺ�20000
#define  INVESTMENT_LOSS "investment_loss"				//Ͷ��ʧ�ܣ�����30000

#define STRENGTH_UP "strength_up"
#define PLAYER_HURT "player_hurt"
#define RICH_DAY "rich_day"
#define IN_HOSPITAL_REMAIN "in_hospital_remain"
#define IN_HOSPITAL "in_hospital"
#define PICK_BALL "pick_ball"


#endif
