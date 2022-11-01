#include "..\ProjectMasterDll\Interfaces.h"
#include <iostream>
using namespace std;

HINSTANCE applet;			//дескриптор апплета
void main() {
	setlocale(LC_ALL, "ru");
	applet = LoadLibrary(L"ProjectMasterDll.dll");
	if (applet == NULL) return; //(L"не загружен!")

	CREATEINSTANCEPROC funk = (CREATEINSTANCEPROC) GetProcAddress(applet, "CreateInstance");
	if (funk == NULL) return;

	IUnknown* pIUnknown = funk();//CreateInstance();

	ICollection* pIC = 0;
	IEnumerator* pIE = 0;
	

	//Проверка ICollection
	cout << "ICollection" << endl;
	HRESULT result;
	result = pIUnknown->QueryInterface(IID_ICollection, (void**)&pIC);
	if (result != S_OK) return;


	//Добавляю 3 объекта
	Object valueObj;
	valueObj.Type = ObjectType::otDouble;
	//Записываем 0.123
	valueObj.Value.Double = 0.123;
	pIC->Add(valueObj);

	//Записываем 1.456
	valueObj.Value.Double = 1.456;
	pIC->Add(valueObj);

	//Записываем 2.789
	valueObj.Value.Double = 2.789;
	pIC->Add(valueObj);

	//Проверка кол-ва
	unsigned count;
	HRESULT res = pIC->GetCount(&count);
	cout << "Кол-во до удаления\t" << count << endl;

	//Удаление последнего объекта
	pIC->Remove(valueObj);

	//Проверка кол-ва
	res = pIC->GetCount(&count);
	cout << "Кол-во после удаления\t" << count << endl;

	//В array
	Object arrObj;
	arrObj.Type = ObjectType::otArray;

	pIC->ToArray(&arrObj.Value.Array);
	for (int i = 0; i < arrObj.Value.Array->Count;i++) {
		cout << arrObj.Value.Array->Data[i].Value.Double << "\t";
	}
	cout << endl;

	//Записываем 3.456
	valueObj.Value.Double = 1.456;
	pIC->Add(valueObj);

	//Записываем 4.789
	valueObj.Value.Double = 2.789;
	pIC->Add(valueObj);
	pIC->Release();
	//Проверка IEnumerator
	cout << "IEnumerator" << endl;
	HRESULT resultIE;
	resultIE = pIUnknown->QueryInterface(IID_IEnumerator, (void**)&pIE);
	if (resultIE != S_OK) return;

	//Сброс 
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

