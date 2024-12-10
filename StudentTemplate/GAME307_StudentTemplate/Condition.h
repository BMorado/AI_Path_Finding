#ifndef CONDITION_H
#define CONDITION_H



class Character;

class Condition
{
public:
	Condition();

	virtual bool test(Character* npc) = 0;
};

class ConditionOutOfRange:public Condition
{
public:
	ConditionOutOfRange();
	bool test(Character* npc) override;
};

class ConditionInRange: public Condition
{
public:
	ConditionInRange();
	bool test(Character* npc) override;
};

class ConditionFlee : public Condition
{
public:
	ConditionFlee();
	bool test(Character* npc) override;
};
class ConditionPatrol : public Condition
{
public:
	ConditionPatrol();
	bool test(Character* npc) override;
};


#endif

