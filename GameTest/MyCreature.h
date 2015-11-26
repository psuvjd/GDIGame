#pragma once

#define STAND	0
#define WALK	1

#define SOUTH		0
#define SOUTHWEST	5
#define WEST		10
#define	NORTHWEST	15
#define	NORTH		20
#define	NORTHEAST	25
#define	EAST		30
#define	SOUTHEAST	35

class CMyCreature
{
private:
	const double c_dEps = 1e-4;
	int m_iX;
	int m_iY;
	int m_iDesX;
	int m_iDesY;
	double m_dSpeed;
	int m_iState;
	int m_iFaceTo;
public:
	CMyCreature(void);
	int GetX(void);
	int GetY(void);
	int GetDesX(void);
	int GetDesY(void);
	void SetDes(int iX, int iY);
	void Move(int idx);
	int GetFace(void);
	int GetState(void);
public:
	~CMyCreature(void);
};
