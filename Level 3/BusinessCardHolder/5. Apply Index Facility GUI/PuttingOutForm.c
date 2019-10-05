#include "PuttingOutForm.h"
#include "BusinessCardHolder.h"
#include "resource.h"
#include "Index.h"
#include "IndexHolder.h"
#include <Commctrl.h>


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
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	HTREEITEM hName;
	HTREEITEM hCompany;
	HTREEITEM hCompanies;
	Long location;
	TVITEM tvi = { 0, };
	TCHAR companyName[64];
	Long i;

	//1. ���� �����찡 ������ ��
	//1.1. ����ø �����츦 ã�´�.
	businessCardHolderForm = FindWindow("#32770", "����ø");
	businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
	//1.2. ����ø �������� ����ø���� �� ������ ��ġ�� �д´�.
	businessCardLink = businessCardHolder->current;
	//1.3. ����ø �������� ����ø���� ������ ����.
	businessCard = PutOut(businessCardHolder, businessCardLink);
	//1.4. ���� �����쿡 ������ ����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.faxNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.url);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.telephoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	//1.5. �� ������ ��ȣ�� �д´�.
	//1.6. ����ø �������� ����ø���� ������ ����.
	indexHolder = (IndexHolder*)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");
	indexLink = IndexHolder_PutOut(indexHolder, businessCard.company.name, businessCardLink);
	//1.7. ����ø �������� Ʈ���� ��Ʈ�ѿ��� ���õ� �̸��׸��� �д´�.
	hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
		(WPARAM)TVGN_CARET, (LPARAM)0);
	//1.8. ����ø �������� ����ø���� ������ ��������
	if (indexLink == NULL) {
		//1.8.1. Ʈ���� ��Ʈ���� ���õ� �̸� �׸��� ���� �׸��� �д´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_PARENT, (LPARAM)hName);
		//1.8.2. Ʈ���� ��Ʈ���� �����׸��� �����.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_DELETEITEM,
			(WPARAM)0, (LPARAM)hCompany);
	}
	else { // 1.9. ����ø�������� ����ø���� ������ ���� �ʾ����� Ʈ���� ��Ʈ���� ���õ� �̸��׸��� �����.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_DELETEITEM,
			(WPARAM)0, (LPARAM)hName);
	}
	//1.10. ����ø �������� ������ ������
	if (businessCardHolder->length > 0) {
		businessCardLink = businessCardHolder->current;
		//1.10.1. ����ø �������� ������ ����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
	
		//1.10.2. ����ø �������� ������ ��ġ�� �д´�.
		//1.10.3. ������ ��ȣ�� �д´�.
		//1.10.4. ������ �������� ����ø���� ã�´�
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//1.10.5. ã�� ���ο��� ������ ��ġ�� ã�´�.
		location = Index_Find(indexLink, businessCardLink);
		//1.10.6. ����ø �������� Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã�´�.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//1.10.7. ����ø �������� Ʈ���� ��Ʈ�ѿ��� ��ȣ �׸��� ã��.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.hItem = hCompany;
		tvi.pszText = companyName;
		tvi.cchTextMax = 64;
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvi.hItem = hCompany;
			SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}
		//1.10.8. ����ø �������� Ʈ���� ��Ʈ���� ��ȣ�׸񿡼� �̸� �׸��� ã�´�.
		hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//1.10.9 Ʈ���� ��Ʈ���� ȸ����� ��ģ��.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		//1.10.10 Ʈ���� ��Ʈ���� ȸ��鿡�� ��ȣ�׸��� ��ġ��.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		//1.10.11 Ʈ���� ��Ʈ���� ��ȣ���� �̸��� �����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE,
			(LPARAM)hName);
	}
	else {	//1.5. ����ø �������� ����ø�� ������ ������ ������ ����Ѵ�.
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
	IndexHolder *indexHolder;
	Index *indexLink;
	BusinessCard *businessCardLink;
	TVITEM tvi = { 0, };
	TVINSERTSTRUCT tvins = { 0, };
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];
	

	//2. �ݱ� ��ư�� Ŭ������ ��
	//2.1. �޽��� �ڽ��� ����Ѵ�.
	ret = MessageBox(hWnd, (LPCWSTR)"����ðڽ��ϱ�?", (LPCWSTR)"�����", MB_YESNOCANCEL);
	switch (ret) {
		//2.2. �� ��ư�� Ŭ������ ��
	case IDYES:
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)16, (LPARAM)businessCard.personal.position);
		//2.2.1. ����ø �����츦 ã�´�.
		businessCardHolderForm = FindWindow("#32770", "����ø");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		indexHolder = (IndexHolder *)GetProp(businessCardHolderForm, "PROP_INDEXHOLDER");
		//2.2.2. ����ø �������� ����ø�� �����.
		businessCardLink = PutIn(businessCardHolder, businessCard);
		//2.2.3. ����ø �����쿡 ������ ����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//2.2.4. ����ø �������� ����ø�� ���� ������ ��ġ�� �д´�.
		//2.2.5. ����ø �������� ����ø�� ������ �����.
		indexLink = IndexHolder_PutIn(indexHolder, businessCardLink);
		//2.2.6. ����ø�������� Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã�´�.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX),
			TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//2.2.7. ����ø �������� Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ �׸��� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
			(WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvi.mask = TVIF_TEXT | TVIF_HANDLE;
		tvi.hItem = hCompany;
		tvi.pszText = companyName;
		tvi.cchTextMax = 64;
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
			(WPARAM)0, (LPARAM)&tvi);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETNEXTITEM,
				(WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvi.hItem = hCompany;
			SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_GETITEM,
				(WPARAM)0, (LPARAM)&tvi);
		}
		tvins.item.mask = TVIF_TEXT | TVIF_HANDLE;
		//2.2.8. �� ã������ Ʈ���� ��Ʈ���� ȸ��� �׸� ��ȣ�׸��� �߰��Ѵ�.
		if (hCompany == NULL) {
			tvins.item.pszText = indexLink->name;
			tvins.hParent = hCompanies;
			tvins.hInsertAfter = TVI_SORT;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_INSERTITEM,
				(WPARAM)0, (LPARAM)&tvins);
		}
		//2.2.9. ����ø �������� Ʈ���� ��Ʈ���� ��ȣ�׸� �̸��� �߰��Ѵ�.
		tvins.item.pszText = businessCardLink->personal.name;
		tvins.hParent = hCompany;
		tvins.hInsertAfter = TVI_LAST;
		hName = (HTREEITEM)SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_INSERTITEM,
			(WPARAM)0, (LPARAM)&tvins);

	   // Ʈ���� ��Ʈ���� ȸ����� ��ģ��.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompanies);
		// Ʈ���� ��Ʈ���� ȸ��鿡�� ��ȣ�׸��� ��ġ��.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND,
			(LPARAM)hCompany);
		// Ʈ���� ��Ʈ���� ��ȣ���� �̸��� �����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE,
			(LPARAM)hName);
	
		//2.13 ���� �����츦 �ݴ´�.
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