#pragma once

#include "StaticLED.h"

#define HAND_LOOSE  FALSE
#define HAND_TIGHT  TRUE

#define STATUS_OFFLINE  ID_COLOR_GRAY
#define STATUS_WARNING  ID_COLOR_RED
#define STATUS_READY    ID_COLOR_GREEN
#define STATUS_RUNNING  ID_COLOR_BLUE
#define STATUS_ONLINE   ID_COLOR_YELLOW

//������λ����Ϣ
class CStation
{
public:
	CStation(void);
	virtual ~CStation(void);
	CStation(int nID);
	CStation(const CStation& station);
	CStation& operator= (const CStation& station);

	int m_nID;                //��λID

	LONGLONG m_nX, m_nY, m_nZ;       //����������Ϣ
	int m_nVx, m_nVy, m_nVz;    //�����˶��ٶ�

	//enum Status {Red = ID_COLOR_RED, Green = ID_COLOR_GREEN, Blue = ID_COLOR_BLUE, Yellow = ID_COLOR_YELLOW, Gray = ID_COLOR_GRAY };
	int m_Status;               //��λ״̬
	BOOL m_Hand;                //��е��״̬

	void SetStatus(int status);

public:
	CCriticalSection m_CritSection;
public:
	void Position(LONGLONG X, LONGLONG Y, LONGLONG Z);
	void PosX(LONGLONG X);
	void PosY(LONGLONG Y);
	void PosZ(LONGLONG Z);
	void SetHand(BOOL hand);
	void VelX(int m_Vx);
	void VelY(int m_Vy);
	void VelZ(int m_Vz);

	
};

