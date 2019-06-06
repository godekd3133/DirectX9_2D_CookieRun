#pragma once
#include "CComponent.h"		   

class CRenderer 
	: public CComponent
{
public:
	CRenderer(CObject * _pObj);
	~CRenderer();
public:
	virtual void Init( );
	virtual void Update();
	virtual void Render();
	virtual void Release();
public:
	CTexture * m_pTexture = nullptr;
	FLOAT m_fWidth;
	FLOAT m_fHeight;
	Color m_Color;

	//������ �Ǵ� ������ ��� �簢�� ����
	Rect  m_rRect;

public:
	void SetTexture(CTexture * _pTexture);


};

 