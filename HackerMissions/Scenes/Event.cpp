#include "Event.h"

//�ж��Ƿ����㴥���������������ʹ���
void Event::triggerTest(Player& player){
	if (eventType != EVENT_EXECUTED && player.getHitbox().hitWith(triggerBox)){
		trigger();
		if (eventType == EVENT_ONCE) eventType = EVENT_EXECUTED;
	}
}

//�Ƚϵײ�ĺ�����������������
void Event::trigger(){
	act();
}