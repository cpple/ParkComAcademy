#include "PuttingOutForm.h"
#include "BusinessCardHolder.h"
#include "resource.h"

BOOL CALLBACK PuttingOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = PuttingOutForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = PuttingOutForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}
BOOL PuttingOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard businessCard;
	BusinessCard *index;

	//1. ���� �����찡 ������ ��
	//1.1. ����ø �����츦 ã�´�.
	businessCardHolderForm = FindWindow("#32770", "����ø");
	businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
	//1.2. ����ø �������� ����ø���� ������ ����.
	businessCard = PutOut(businessCardHolder, businessCardHolder->current);
	//1.3. ���� �����쿡 ������ ����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	//1.4. ����ø �������� ����ø�� ������ ������ ����ø �����쿡 ������ ����Ѵ�.
	if (businessCardHolder->current != NULL) {
		index = businessCardHolder->current;
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
	}
	//1.5. ����ø �������� ����ø�� ������ ������ ������ ����Ѵ�.
	else {
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}
BOOL PuttingOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	int ret;
	BusinessCard businessCard;
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard *index;

	//2. �ݱ� ��ư�� Ŭ������ ��
	//2.1. �޽��� �ڽ��� ����Ѵ�.
	ret = MessageBox(hWnd, (LPCWSTR)L"����ðڽ��ϱ�?", (LPCWSTR)L"�����", MB_YESNOCANCEL);
	switch (ret) {
		//2.2. �� ��ư�� Ŭ������ ��
	case IDYES:
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
		businessCard.next = NULL;
		//2.2.1. ����ø �����츦 ã�´�.
		businessCardHolderForm = FindWindow("#32770", "����ø");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//2.2.2. ����ø �������� ����ø�� �����.
		index = PutIn(businessCardHolder, businessCard);
		//2.2.3. ����ø �����쿡 ������ ����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		//2.2.4. ���� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
		break;
		//2.3. �ƴϿ� ��ư�� Ŭ������ ��
	case IDNO:
		//2.3.1. ���� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
		break;
	default:
		break;
	}

	return TRUE;
}