#pragma once
class CMyScenery
{
private:
	const int ScePicAmount = 97;
	int m_iX;
	int m_iY;
	int m_iID;
public:
	CMyScenery();
	CMyScenery(int nX, int nY, int nID);
	int GetX(void) const;
	int GetY(void) const;
	int GetID(void) const;
	void SetX(int nX);
	void SetY(int nY);
	void SetID(int nID);
	bool operator <(const CMyScenery& rhs) const;
	~CMyScenery();
};

