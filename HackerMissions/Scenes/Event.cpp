#include "Event.h"

//判断是否满足触发条件，如果满足就触发
void Event::triggerTest(Player& player){
	if (eventType != EVENT_EXECUTED && player.getHitbox().hitWith(triggerBox)){
		trigger();
		if (eventType == EVENT_ONCE) eventType = EVENT_EXECUTED;
	}
}

//比较底层的函数，不处理触发条件
void Event::trigger(){
	act();
}