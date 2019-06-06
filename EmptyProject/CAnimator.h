#pragma once
class CTimer;
class CAnimator
{
public:
	CAnimator();
	~CAnimator();

public:
	void Init(const string& _Key, float _fDelay , bool _bLoop);
	void Update();
	void Render();
	void Release();
	// ��� ������
	float m_fDelay;

	// �ݺ� ���� FALSE �ϰ�� �ѹ��� ���� 0���������� ���� ��� ����
	bool m_bLoop;

	// �ִϸ��̼� ��������� 
	bool m_bActive;

	// �ε��� ���� ���� ������
	int m_iFrame = 0;

	// �ε��� ���� �ִ� ������
	int m_iMaxFrame;
	CTexture * GetFrameTexture() { return m_Textures[m_iFrame]; }
private:
	vector<CTexture*> m_Textures;
	CTimer * m_pTimer = nullptr;

};

