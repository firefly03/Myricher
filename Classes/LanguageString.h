#ifndef __LANGUAGESTRING__H__
#define __LANGUAGESTRING__H__

#include "cocos2d.h"


USING_NS_CC;
class LanguageString
{
public:
	static LanguageString* instance;
	static Dictionary *strings;
	static LanguageString * getInstance();
	String* getLanguageString(const char* strName);
	//声明ValueMap变量
	ValueMap plist_map;
	//声明一个字符串变量
	std::string str;
};

#endif