#include <iostream>
#include "Component.h"

bool operator == (const Object& obj1, const Object& obj2) {
	if (obj1.Type != obj2.Type) return false;
	switch (obj1.Type)
	{
	case otInt:
		return obj1.Value.Int == obj2.Value.Int;
	case otDouble:
		return obj1.Value.Double == obj2.Value.Double;
	case otArray:
		if (obj1.Value.Array->Count != obj2.Value.Array->Count) return false;

		for (int i = 0; i < obj1.Value.Array->Count; i++) {
			if (!(obj1.Value.Array->Data[i] == obj2.Value.Array->Data[i])) {
				return false;
			}
		}
		return true;
	default:
		break;
	}
}

// Методы IUnknown
HRESULT __stdcall CList::QueryInterface(REFIID iid, void** ppv) {
	if (iid == IID_IUnknown) *ppv = (ICollection*)this;
	else if (iid == IID_ICollection) *ppv = (ICollection*)this;
	else if (iid == IID_IEnumerator) *ppv = (ICollection*)this;
	else {
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

//Увеличивает счетчик ссылок
ULONG __stdcall CList::AddRef() {	
	return ++m_cRef;
}

//Уменьшает счетчик ссылок
ULONG __stdcall CList::Release() {	
	if (--m_cRef == 0) {
		delete this;
		return 0;
	}
	return m_cRef;
}

// Методы ICollection
HRESULT __stdcall CList::Add(Object obj) {
	data.push_back(obj);
	return S_OK;
}

HRESULT __stdcall CList::Remove(Object obj) {
	data.remove(obj);
	return S_OK;
}

HRESULT __stdcall CList::GetCount(unsigned* count) {
	*count = data.size();
	return S_OK;
}

HRESULT __stdcall CList::ToArray(ObjectArray** arr) {
	*arr = new ObjectArray();
	(*arr)->Data = new Object[data.size()];
	int i = 0;
	for (std::list<Object>::iterator it = data.begin(); it != data.end(); it++) {
		(*arr)->Data[i] = *it;
		i++;
	}
	(*arr)->Count = data.size();
	return S_OK;
}

// Методы IEnumerator
HRESULT __stdcall CList::Reset() {
	iter_d = data.begin();
	return S_OK;
}

HRESULT __stdcall CList::MoveNext(int* result) {

	if (++iter_d == data.end()) {
		--iter_d;
		*result = 0;
		return S_FALSE;
	} 
	*result = 1;
	return S_OK;
}

HRESULT __stdcall CList::GetCurrent(Object* obj) {
	*obj = *iter_d;
	return S_OK;
}

IUnknown* CreateInstance() {
	IUnknown* instance = (ICollection*)(new CList);
	instance->AddRef();
	return instance;
}

