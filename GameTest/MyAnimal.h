#pragma once
#include "MyCreature.h"

#define TIGER	0
#define DOG		1
#define BEAR	2
#define DEER	3
#define HORSE	4
#define SHEEP	5
#define PEACOCK 6	/* ¿×È¸...*/
#define TYPE_MAX 7

class CMyAnimal :
	public CMyCreature
{
private:
	int m_iType;
	int m_iTimer;
	int m_iStop;
public:
	CMyAnimal();
	CMyAnimal(int, int);
	int GetType(void) const;
	int CreateX(void) const;
	int CreateY(void) const;
	void AI(int );
	~CMyAnimal();
};

