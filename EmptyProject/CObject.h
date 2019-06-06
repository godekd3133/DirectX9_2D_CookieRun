#pragma once
#include "CComponent.h"
#include "CRenderer.h"
#include "CTransform.h"
#include "CBoxCollider.h"

enum ObjectTag
{
	Untagged = 0,
	Player = 1

}typedef Tag;


class CObject abstract
{
public:
	CObject();
	virtual ~CObject();
public:
	
	virtual void Init(ObjectTag _Tag = Untagged);
	virtual void Render();
	virtual void Update();
	virtual void Release();
protected:
	list<CComponent *>m_Components;

protected:
	BOOL m_bDestroy = FALSE; // �ش� ������Ʈ�� �ı�ȣ��Ǿ�����

public:
	CTransform * Translation;
	ObjectTag m_Tag;
	INT m_iDepth;
public:
	ObjectTag GetObjectKind() { return m_Tag; }
	BOOL isDestroyed() { return m_bDestroy; }
	void Destroy() { m_bDestroy = TRUE; }
public:
	virtual void OnCollisionEnter(CObject * _pObject)PURE;
	virtual void OnCollisionStay(CObject * _pObject) PURE;
	virtual void OnCollisionExit(CObject * _pObject) PURE;
	virtual void OnTriggerEnter(CObject * _pObject)	 PURE;
	virtual void OnTriggerStay(CObject * _pObject)	 PURE;
	virtual void OnTriggerExit(CObject * _pObject)	 PURE;
public:
	list<CComponent *>& GetComponents() { return m_Components; }

	template <typename T>
	T*  GetComponent()
	{
		for (auto iter : m_Components)
		{
			//�߻�Ŭ������ �����̳��̱⶧����
			//dynamic_cast�� ���� �ڽ�Ŭ������ �ߺ��� ������Ʈ�� ó���մϴ�.
			
			if (typeid(T) == typeid(*iter))
				return static_cast<T*>(iter);
		}
		return nullptr;
	}

	template <typename T>
	T* AddComponent()
	{
		//������Ʈ�� ��ӹ��� �ʾҴٸ� ����
		if (FALSE == std::is_base_of<CComponent, T>::value)
			return nullptr;

		//�̹� �������ִ� ������Ʈ�� �� �߰��Ϸ��� ����
		if (nullptr != this->GetComponent<T>())
			return this->GetComponent<T>();
		
		CComponent * pComponent = new T(this);

		pComponent->CComponent::Init();

		m_Components.push_back(pComponent);
				 
		return dynamic_cast<T*>(pComponent);
	}
};


