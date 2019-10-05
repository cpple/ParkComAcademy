#include "BusinessCardHolder.h"
#include "FindingForm.h"
#include "resource.h"
#include "IndexHolder.h"
#include "Index.h"
#include <Commctrl.h>
#include <string.h>

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND: ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_SELECT: ret = FindingForm_OnSelectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST: ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);

	//7. �ݱ� ��ư�� Ŭ������ ��
	//7.1. ã�� �����츦 �ݴ´�.
	indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL) {
		free(indexes);
	}
	RemoveProp(hWnd, "PROP_COUNT");
	RemoveProp(hWnd, "PROP_CURRENT");

	EndDialog(hWnd, 0);

	return TRUE;
}
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR name[11];
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard* (*indexes);
	Long count;
	Long current;
	BusinessCard *businessCard;

	//1. ã�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//1.1. ������ �Է¹޴´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		//1.2. ����ø �����츦 ã�´�.
		businessCardHolderForm = FindWindow("#32770", "����ø");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//1.3. ����ø �������� ����ø���� ã�´�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}
		Find(businessCardHolder, name, &indexes, &count);
		//1.4. ã������ ù ��° ������ ����Ѵ�.
		if (count > 0) {
			current = 0;
			businessCard = indexes[current];
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.url);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);
		}
		else {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);
		SetProp(hWnd, "PROP_COUNT", (HANDLE)count);
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}
BOOL FindingForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {

	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard *businessCardLink;
	BusinessCard* (*indexes);
	Long current;
	Long location;
	Long i;

	IndexHolder *indexHolder;
	Index *indexLink;
	TVITEM tvi = { 0, };
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];

	//2. ���� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. ���õ� ������ ��ġ�� �д´�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		businessCardLink = indexes[current];
		//2.2. ����ø �����츦 ã�´�.
		businessCardHolderForm = FindWindow("#32770", "����ø");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//2.3. ����ø �������� ����ø���� �̵��Ѵ�.
		businessCardLink = BusinessCardHolder_Move(businessCardHolder, businessCardLink);
		//2.4. ����ø �����쿡 ���õ� ������ ����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		
		indexHolder = (IndexHolder*)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");

		//2.5. ����ø���� ������ ã��.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//2.6. ���ο��� ������ ��ġ�� ã��.
		location = Index_Find(indexLink, businessCardLink);
		
		//2.7. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã��.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//2.8. Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ�� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.pszText = companyName;
		tvi.hItem = hCompany;
		tvi.cchTextMax = 64;

		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvi);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvi.hItem = hCompany;
			SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}
		//2.9. Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� �̸��׸��� ã��.
		hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}

		//2.10. Ʈ���� ��Ʈ���� ȸ����� ��ģ��.

		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//2.11. Ʈ���� ��Ʈ���� ȸ��鿡�� ��ȣ�׸��� ��ġ��.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//2.12. Ʈ���� ��Ʈ���� ��ȣ���� �̸��� �����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE,
			(LPARAM)hName);
		//2.13. �����츦 �ݴ�.

		if (indexes != NULL) {
			free(indexes);
		}
		RemoveProp(hWnd, "PROP_COUNT");
		RemoveProp(hWnd, "PROP_CURRENT");

		EndDialog(hWnd, 0);
	}
	return TRUE;
}
BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long current;
	BusinessCard *businessCard;

	//3. ó�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. ó�� ������ ��ġ�� �д´�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = 0;
		businessCard = indexes[current];
		//3.2. ������ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}
BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long current;
	BusinessCard *businessCard;

	//4. ���� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. ���� ������ ��ġ�� �д´�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		current--;
		if (current < 0) {
			current = 0;
		}
		businessCard = indexes[current];
		//4.2. ������ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}
BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long current;
	BusinessCard *businessCard;
	Long count;

	//5. ���� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1. ���� ������ ��ġ�� �д´�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "PROP_COUNT");
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		current++;
		if (current >= count) {
			current = count - 1;
		}
		businessCard = indexes[current];
		//5.2. ������ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}
BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard* (*indexes);
	Long current;
	BusinessCard *businessCard;
	Long count;

	//6. ������ ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1. ������ ������ ��ġ�� �д´�.
		indexes = (BusinessCard*(*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "PROP_COUNT");
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		current = count - 1;
		businessCard = indexes[current];
		//6.2. ������ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}