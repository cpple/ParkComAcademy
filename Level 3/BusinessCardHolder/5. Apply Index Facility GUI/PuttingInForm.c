#include "PuttingInForm.h"
#include "resource.h"
#include "BusinessCardHolder.h"
#include "IndexHolder.h"
#include "Index.h"
#include <stdio.h> //sprintf
#include <string.h>
#include <CommCtrl.h>

BOOL CALLBACK PuttingInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = PuttingInForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = PuttingInForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = PuttingInForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}
BOOL PuttingInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//1. ����� �����찡 ������ ��
	//1.1. ������ ����� �����.
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"naver.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"gmail.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"nate.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"daum.net");
	//1.2. ��å ����� �����.
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"����");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"����");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"����");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"�븮");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)"���");

	return TRUE;
}
BOOL PuttingInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_EDIT_COMPANY_NAME: ret = PuttingInForm_OnCompanyNameKillFocus(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PUTIN: ret = PuttingInForm_OnPutInButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL PuttingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//4. �ݱ� ��ư�� Ŭ������ ��
	//4.1. ����� �����츦 �ݴ�.
	EndDialog(hWnd, 0);

	return TRUE;
}
BOOL PuttingInForm_OnCompanyNameKillFocus(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR companyName[64];
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;

	//2. ��ȣ ������ ��Ŀ���� �Ҿ��� ��
	if (HIWORD(wParam) == EN_KILLFOCUS) {
		//2.1. ��ȣ�� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);
		//2.2. ����ø �����츦 ã�´�.
		businessCardHolderForm = FindWindow("#32770", "����ø");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		indexHolder=(IndexHolder*)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");
		//2.3. ����ø �������� ����ø���� ã�´�.
		indexLink = IndexHolder_Find(indexHolder, companyName);
		//2.4. ã������ ȸ�縦 ����Ѵ�.
		if (indexLink != NULL) {
			businessCardLink = Index_GetAt(indexLink, 0);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		}
	}

	return TRUE;
}
BOOL PuttingInForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard businessCard;
	TCHAR emailID[32];
	TCHAR domain[32];
	HWND businessCardHolderForm;
	BusinessCardHolder *businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };
	HTREEITEM hName;

	//3. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_URL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_EMAILID), WM_GETTEXT, (WPARAM)32, (LPARAM)emailID);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_DOMAIN), WM_GETTEXT, (WPARAM)32, (LPARAM)domain);
		sprintf(businessCard.personal.emailAddress, "%s@%s", emailID, domain);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_POSITION), WM_GETTEXT, (WPARAM)16, (LPARAM)businessCard.personal.position);
		//3.2. ����ø �����츦 ã�´�.
		businessCardHolderForm = FindWindow("#32770", "����ø");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");
		//3.3. ����ø �������� ����ø�� �����.
		businessCardLink = PutIn(businessCardHolder, businessCard);
		//3.4. ����ø �����쿡 ������ ����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//3.5. ����ø �������� ����ø�� ���� ������ ��ġ�� �д´�.
		//3.6. ����ø �������� ����ø���� �����.
		indexLink = IndexHolder_PutIn(indexHolder, businessCardLink);
		//3.7. ����ø �������� Ʈ���� ��Ʈ���� ȸ��� �׸��� ã�´�.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//3.8. ����ø �������� Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ �׸��� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//3.9. ��ã������ ����ø �������� Ʈ���� ��Ʈ���� ȸ��� �׸� ��ȣ �׸��� �߰��Ѵ�.
		if (hCompany == NULL) {
			tvItem.item.pszText = indexLink->name;
			tvItem.hParent = hCompanies;
			tvItem.hInsertAfter = TVI_SORT;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
		}
		//3.10. ����ø �������� Ʈ���� ��Ʈ���� ��ȣ �׸� �̸� �׸��� �ߤ����Ѵ�.
		tvItem.item.pszText = businessCardLink->personal.name;
		tvItem.hParent = hCompany;
		tvItem.hInsertAfter = TVI_LAST;
		hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
		//3.11. ����ø �������� Ʈ���� ��Ʈ���� ȸ��� �׸��� ��ģ��.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//3.12. ����ø �������� Ʈ���� ��Ʈ���� ��ȣ �׸��� ��ģ��.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//3.13. ����ø �������� Ʈ���� ��Ʈ�ѿ��� �߰��� �̸� �׸��� �����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);
		//3.14. ����� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}

	return TRUE;
}