#pragma once
#include "..\BasicInclude.h"

typedef std::function<void()> Action;
typedef std::function<bool()> Judge;
typedef int EventType;
enum{ EVENT_ONCE, EVENT_NORMAL, EVENT_EXECUTED };

class Event{
private:
	AABB triggerBox;
	EventType eventType;
	Action act;
	Judge requirement;

public:
	Event() :eventType(EVENT_NORMAL){};
	Event(Action actset) :act(actset), eventType(EVENT_NORMAL){};
	Event(bool OnceLimit) :eventType(OnceLimit ? EVENT_ONCE : EVENT_NORMAL){};
	Event(AABB eventBox) :triggerBox(eventBox), eventType(EVENT_NORMAL){};
	Event(AABB eventBox, bool OnceLimit) :triggerBox(eventBox), eventType(OnceLimit ? EVENT_ONCE : EVENT_NORMAL){};
	Event(AABB eventBox, Action actset) :triggerBox(eventBox), act(actset), eventType(EVENT_NORMAL){};
	Event(AABB eventBox, Action actset, bool OnceLitmit) :triggerBox(eventBox), act(actset), eventType(OnceLitmit ? EVENT_ONCE : EVENT_NORMAL){};
	Event(Action actset, Judge req) :requirement(req), act(actset), eventType(EVENT_NORMAL){};
	Event(AABB eventBox, Action actset, Judge req) :requirement(req), triggerBox(eventBox), act(actset), eventType(EVENT_NORMAL){};
	Event(AABB eventBox, Action actset, Judge req, bool OnceLitmit) :requirement(req), triggerBox(eventBox), act(actset), eventType(OnceLitmit ? EVENT_ONCE : EVENT_NORMAL){};

	inline void setAction(Action actset){ act = actset; }
	inline void setRequirement(Judge req){ requirement = req; }
	inline EventType& getEventType(){ return eventType; }

	void triggerTest(Player& player);  //判断是否满足触发条件，如果满足就触发
	void trigger(); //比较底层的函数，不处理触发条件
};