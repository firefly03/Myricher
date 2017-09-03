#include "Util.h"

Vector<String*> Util::splitString(const char* srcStr, const char* sSep)
{
	Vector<String*> stringList;

	int size = strlen(srcStr);
	String* str = String::create(srcStr);

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str->_string.find(sSep);

	String* spliStr = NULL;

	while (endIndex > 0) {
		spliStr = String::create("");
		/* ��ȡ�ַ��� */
		spliStr->_string = str->_string.substr(startIndex, endIndex);
		/* ����ַ������б� */
		stringList.pushBack(spliStr);
		/* ��ȡʣ�µ��ַ��� */
		str->_string = str->_string.substr(endIndex + 1, size);
		/* ������һ���ָ��������±� */
		endIndex = str->_string.find(sSep);
	}
	/* ʣ�µ��ַ���Ҳ��ӽ��б� */
	if (str->_string.compare("") != 0) {
		stringList.pushBack(String::create(str->_string));
	}

	return stringList;

}

Point Util::map2GL(const Point& ptMap, TMXTiledMap* map)
{
	Point ptUI;
	ptUI.x = ptMap.x * map->getTileSize().width;
	ptUI.y = ptMap.y * map->getTileSize().height;

	Point ptGL = ptUI;
	ptGL.y = map->getContentSize().height - ptUI.y;
	return ptGL;
}

Point Util::GL2map(const Point& ptGL, TMXTiledMap* map)
{
	Point ptUI = ptGL;
	ptUI.y = map->getContentSize().height - ptGL.y;

	int x = ptUI.x / map->getTileSize().width;
	int y = ptUI.y / map->getTileSize().height;
	return Vec2(x, y);
}

void  Util::sendCustomEvent(const std::string messageType, String* message)
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	EventCustom _event = EventCustom(messageType);
	_event.setUserData(message);
	dispatcher->dispatchEvent(&_event);
}