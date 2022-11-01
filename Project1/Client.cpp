#include "..\ProjectMasterDll\Interfaces.h"
#include <iostream>
using namespace std;

HINSTANCE applet;			//���������� �������
void main() {
	setlocale(LC_ALL, "ru");
	applet = LoadLibrary(L"ProjectMasterDll.dll");
	if (applet == NULL) return; //(L"�� ��������!")

	CREATEINSTANCEPROC funk = (CREATEINSTANCEPROC) GetProcAddress(applet, "CreateInstance");
	if (funk == NULL) return;

	IUnknown* pIUnknown = funk();//CreateInstance();

	ICollection* pIC = 0;
	IEnumerator* pIE = 0;
	

	//�������� ICollection
	cout << "ICollection" << endl;
	HRESULT result;
	result = pIUnknown->QueryInterface(IID_ICollection, (void**)&pIC);
	if (result != S_OK) return;


	//�������� 3 �������
	Object valueObj;
	valueObj.Type = ObjectType::otDouble;
	//���������� 0.123
	valueObj.Value.Double = 0.123;
	pIC->Add(valueObj);

	//���������� 1.456
	valueObj.Value.Double = 1.456;
	pIC->Add(valueObj);

	//���������� 2.789
	valueObj.Value.Double = 2.789;
	pIC->Add(valueObj);

	//�������� ���-��
	unsigned count;
	HRESULT res = pIC->GetCount(&count);
	cout << "���-�� �� ��������\t" << count << endl;

	//�������� ���������� �������
	pIC->Remove(valueObj);

	//�������� ���-��
	res = pIC->GetCount(&count);
	cout << "���-�� ����� ��������\t" << count << endl;

	//� array
	Object arrObj;
	arrObj.Type = ObjectType::otArray;

	pIC->ToArray(&arrObj.Value.Array);
	for (int i = 0; i < arrObj.Value.Array->Count;i++) {
		cout << arrObj.Value.Array->Data[i].Value.Double << "\t";
	}
	cout << endl;

	//���������� 3.456
	valueObj.Value.Double = 1.456;
	pIC->Add(valueObj);

	//���������� 4.789
	valueObj.Value.Double = 2.789;
	pIC->Add(valueObj);
	pIC->Release();
	//�������� IEnumerator
	cout << "IEnumerator" << endl;
	HRESULT resultIE;
	resultIE = pIUnknown->QueryInterface(IID_IEnumerator, (void**)&pIE);
	if (resultIE != S_OK) return;

	//����� 
	pIE->Reset();

	int go = 0;
	pIE->MoveNext(&go);
	while (go ==1) {
		Object objCur;
		pIE->GetCurrent(&objCur);
		cout << objCur.Value.Double << "\t";
		pIE->MoveNext(&go);
	}


}

