#include "DXUT.h"
#include "CMainScene.h"
#include "CPlayer.h"

CMainScene::CMainScene()
{
}


CMainScene::~CMainScene()
{
}

void CMainScene::Init()
{
	m_pPlayer01 = OBJECT.AddObject<CPlayer>(); 
	m_pPlayer01->Init();
	m_pPlayer01->Translation->m_fRotation = 0;
	m_pPlayer01->Translation->m_vPosition = Vector2(WINSIZEX / 2.F, WINSIZEY / 2.F);


	m_pPlayer02 = OBJECT.AddObject<CPlayer>();
	m_pPlayer02->Init();
	m_pPlayer02->Translation->m_fRotation = 0;
	
}

void CMainScene::Update()
{

	
	if (INPUT.KeyPress(VK_LEFT))  	m_pPlayer01->Translation->m_vPosition.x -= 300 * TIME.DeltaTime;
	if (INPUT.KeyPress(VK_RIGHT))  	m_pPlayer01->Translation->m_vPosition.x += 300 * TIME.DeltaTime;
	if (INPUT.KeyPress(VK_UP))  	m_pPlayer01->Translation->m_vPosition.y -= 300 * TIME.DeltaTime;
	if (INPUT.KeyPress(VK_DOWN))  	m_pPlayer01->Translation->m_vPosition.y += 300 * TIME.DeltaTime;
	if (INPUT.KeyPress('1'))		m_pPlayer01->Translation->m_fRotation -= 100 * TIME.DeltaTime;
	if (INPUT.KeyPress('2'))		m_pPlayer01->Translation->m_fRotation += 100 * TIME.DeltaTime;


	if (INPUT.KeyPress('A'))  	m_pPlayer02->Translation->m_vPosition.x -= 300 * TIME.DeltaTime;
	if (INPUT.KeyPress('D'))  	m_pPlayer02->Translation->m_vPosition.x += 300 * TIME.DeltaTime;
	if (INPUT.KeyPress('W'))  	m_pPlayer02->Translation->m_vPosition.y -= 300 * TIME.DeltaTime;
	if (INPUT.KeyPress('S'))  	m_pPlayer02->Translation->m_vPosition.y += 300 * TIME.DeltaTime;
	if (INPUT.KeyPress('3'))		m_pPlayer02->Translation->m_fRotation -= 100 * TIME.DeltaTime;
	if (INPUT.KeyPress('4'))		m_pPlayer02->Translation->m_fRotation += 100 * TIME.DeltaTime;
}

void CMainScene::Render()
{

}

void CMainScene::Release()
{
}
