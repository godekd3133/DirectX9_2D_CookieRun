#include "DXUT.h"
#include "CObjectManager.h"


CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
	for (auto& iter : m_Objects)
	{
		iter->Release();
		SAFE_DELETE(iter);
	} 
	m_Objects.clear();
}



void CObjectManager::Update()
{
	 
	for (auto& iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		CObject * pObj = (CObject*)(LP(iter));

		pObj->CObject::Update();

		pObj->Update();
		
		for (auto& iter : pObj->GetComponents())
		{
			if(iter->isActive())
				iter->Update();
		}
		//BoxCollider ������Ʈ�� ����ϴ� ������Ʈ���� �浹 �˻縦 �����ϰ� �˴ϴ�.
		auto pBoxCollider = pObj->GetComponent<CBoxCollider>();
		
		if (pBoxCollider != nullptr && pBoxCollider->isActive())
		{
			for (auto& iterObj = m_Objects.begin(); iterObj != m_Objects.end(); iterObj++)
			{
				if (*iterObj == pObj || (*iterObj)->GetComponent<CBoxCollider>() == nullptr && !(*iterObj)->GetComponent<CBoxCollider>()->isActive()) continue;
				else
				{
					auto& Status = pObj->GetComponent<CBoxCollider>()->m_Status;
					if (Math::OBBCheckCollision(
						(*iterObj)->GetComponent<CBoxCollider>()->m_reRect,
						(*iterObj)->Translation->m_fRotation,
						pObj->GetComponent<CBoxCollider>()->m_reRect,
						pObj->Translation->m_fRotation
					))
					{
						switch (Status)
						{
						case COLS_NONE:
							Status = COLS_OnEnter;
							break;
						case COLS_OnEnter:
							if ((*iterObj)->GetComponent<CBoxCollider>()->m_bIsTrigger)
								(*iterObj)->OnTriggerEnter(*iterObj);
							else
								(*iterObj)->OnCollisionEnter(*iterObj);
							Status = COLS_OnStay;
						break;
						case COLS_OnStay:
							if ((*iterObj)->GetComponent<CBoxCollider>()->m_bIsTrigger)
								(*iterObj)->OnTriggerStay(*iterObj);
							else
								(*iterObj)->OnCollisionStay(*iterObj);
							break;
						}
					}
					else
					{
						switch (Status)
						{
						case COLS_OnStay:
							Status = COLS_OnExit;
							break;
						case COLS_OnExit:
							if((*iterObj)->GetComponent<CBoxCollider>()->m_bIsTrigger)
								(*iterObj)->OnTriggerExit(*iterObj);
							else
								(*iterObj)->OnCollisionExit(*iterObj);
							Status = COLS_NONE;
							break;
						}
					}
				}
			}
		}

		// ������Ʈ�� �ı��Ǿ��ٸ�
		if (TRUE == LP(iter)->isDestroyed())
		{
			LP(iter)->Release();
			SAFE_DELETE(LP(iter));
			iter = m_Objects.erase(iter);
		}
		else iter++;
	}
}

void CObjectManager::Render()
{
	// ������Ʈ�� �޾ƿͼ� ��¼��� ���� ������ ����Ʈ�� �����Ѵ�.
	list<CObject *> Renderlist = m_Objects;
	Renderlist.sort([&](CObject *  pPrev, CObject *  pNext)->bool { return pPrev->m_iDepth > pNext->m_iDepth; });
	for (auto& iter : Renderlist)
	{

		iter->Render();
		//1. ������ ������Ʈ�� ����ϰ�
		//2. ������ ������Ʈ�� ����� �����ִٸ�
		//3. ������ ����Ʈ�� �߰��Ѵ�.

		/*for (auto& Obj : iter->GetComponents())
		{
			if (Obj->isActive)
				Obj->Render();
		}*/

		for (auto Comp : iter->GetComponents())
		{
			if (Comp == iter->GetComponent<CRenderer>())
			{
				if (Comp->isActive()) Comp->Render();
			}
		}
	}
	for (auto& iter : Renderlist)
	{
		for (auto Comp : iter->GetComponents())
		{
			if (Comp != iter->GetComponent<CRenderer>())
			{
				if (Comp->isActive()) Comp->Render();
			}
		}
	}


}
