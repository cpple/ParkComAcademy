// BusinessCardHolderForm.c
#include "BusinessCardHolderForm.h"
#include "PuttingInForm.h"
#include "FindingForm.h"
#include "PuttingOutForm.h"
#include "resource.h"
#include "BusinessCardHolder.h"
#include "IndexHolder.h"
#include "Index.h"
#include <stdlib.h>
#include <CommCtrl.h>
#include <string.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_BUSINESSCARDHOLDERFORM), NULL, BusinessCardHolderFormProc);

	return response;
}

BOOL CALLBACK BusinessCardHolderFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;

	switch (message)
	{
	case WM_INITDIALOG:
		ret = BusinessCardHolderForm_OnInitDialog(hWnd, wParam, lParam);
		break;
	case WM_COMMAND:
		ret = BusinessCardHolderForm_OnCommand(hWnd, wParam, lParam);
		break;
	case WM_NOTIFY:
		ret = BusinessCardHolderForm_OnNotify(hWnd, wParam, lParam);
		break;
	case WM_CLOSE:
		ret = BusinessCardHolderForm_OnClose(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}

	return ret;
}

BOOL BusinessCardHolderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder *businessCardHolder;
	IndexHolder *indexHolder;
	Long count;
	BusinessCard *businessCardLink;
	Index *indexLink;
	Long i;
	Long j;
	Index(*indexes);
	Long countIndex;
	Long location;
	BusinessCard *previous = NULL;
	TVINSERTSTRUCT tvItem = { 0, };
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];

	//1. �����찡 ������ ��
	//1.1. ����ø�� �����ϴ�.
	businessCardHolder = (BusinessCardHolder*)malloc(sizeof(BusinessCardHolder));
	BusinessCardHolder_Create(businessCardHolder);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)businessCardHolder);

	//1.2. ����ø�� �����ϴ�.
	indexHolder = (IndexHolder*)malloc(sizeof(IndexHolder));
	IndexHolder_Create(indexHolder);
	SetProp(hWnd, "PROP_INDEXHOLDER", (HANDLE)indexHolder);

	//1.6. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� �߰��ϴ�.
	tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
	tvItem.item.pszText = "ȸ���";
	tvItem.hInsertAfter = TVI_ROOT;
	hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);

	//1.3. ����ø�� �����ϴ�.
	count = Load(businessCardHolder);

	if (count > 0) {
		//1.4. ����� ��ŭ ����ø�� ������ �����.
		businessCardLink = BusinessCardHolder_First(businessCardHolder);
		while (businessCardLink != previous) {
			indexLink = IndexHolder_PutIn(indexHolder, businessCardLink);
			previous = businessCardLink;
			businessCardLink = BusinessCardHolder_Next(businessCardHolder);
		}
		//1.5. ����ø���� ���� ����Ʈ�� �����.
		IndexHolder_MakeList(indexHolder, &indexes, &countIndex);
		//1.7. ���� ����ŭ �ݺ��Ѵ�.
		i = 0;
		while (i < countIndex) {
			//1.7.1. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� �ڽ����� ��ȣ�� �߰��ϴ�.
			indexLink = indexes + i;
			tvItem.item.pszText = indexLink->name;
			tvItem.hParent = hCompanies;
			tvItem.hInsertAfter = TVI_LAST;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
			//1.7.2. Ʈ���� ��Ʈ�ѿ��� ��ȣ �׸��� �ڽ����� ���� ����ŭ �̸��� �߰��ϴ�.
			j = 0;
			while (j < indexLink->length) {
				businessCardLink = Index_GetAt(indexLink, j);
				tvItem.item.pszText = businessCardLink->personal.name;
				tvItem.hParent = hCompany;
				tvItem.hInsertAfter = TVI_LAST;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
				j++;
			}
			i++;
		}
		//1.8. ����ø���� ó������ �̵��Ѵ�.
		businessCardLink = BusinessCardHolder_First(businessCardHolder);
		//1.9. ������ ����ϴ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);

		//1.10. ����ø���� ó�� ������ ������ ã��.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//1.11. ���ο��� ó�� ������ ��ġ�� ã��.
		location = Index_Find(indexLink, businessCardLink);
		//1.12. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã��.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//1.13. Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ �׸��� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//1.14. Ʈ���� ��Ʈ���� ��ȣ �׸񿡼� �̸� �׸��� ã��.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//1.15. Ʈ���� ��Ʈ���� ȸ����� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//1.16. Ʈ���� ��Ʈ���� ��ȣ �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//1.17. Ʈ���� ��Ʈ�ѿ��� �̸� �׸��� �����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

		if (indexes != NULL) {
			free(indexes);
		}
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BOOL ret;

	switch (LOWORD(wParam))
	{
	case IDC_BUTTON_PUTIN:
		ret = BusinessCardHolderForm_OnPutInButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIND:
		ret = BusinessCardHolderForm_OnFindButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PUTOUT:
		ret = BusinessCardHolderForm_OnPutOutButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_ARRANGE:
		ret = BusinessCardHolderForm_OnArrangeButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_FIRST:
		ret = BusinessCardHolderForm_OnFirstButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_PREVIOUS:
		ret = BusinessCardHolderForm_OnPreviousButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_NEXT:
		ret = BusinessCardHolderForm_OnNextButtonClicked(hWnd, wParam, lParam);
		break;
	case IDC_BUTTON_LAST:
		BusinessCardHolderForm_OnLastButtonClicked(hWnd, wParam, lParam);
		break;
	default:
		ret = FALSE;
		break;
	}

	return TRUE;
}
BOOL BusinessCardHolderForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam) {
	case IDC_TREE_INDEX: ret = BusinessCardHolderForm_OnTreeViewNameItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}
BOOL BusinessCardHolderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder *businessCardHolder;
	IndexHolder *indexHolder;

	businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
	indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");

	//����ø�� �����.
	if (indexHolder != NULL) {
		IndexHolder_Destroy(indexHolder);
		free(indexHolder);
	}
	if (businessCardHolder != NULL)
	{
		Save(businessCardHolder);
		BusinessCardHolder_Destroy(businessCardHolder);
		free(businessCardHolder);
	}

	RemoveProp(hWnd, "PROP_INDEXHOLDER");

	EndDialog(hWnd, 0);

	return TRUE;
}

BOOL BusinessCardHolderForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGINFORM), NULL, PuttingInFormProc);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnPutOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == BN_CLICKED)
	{
		DialogBox((HINSTANCE)GetWindow(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGOUTFORM), NULL, PuttingOutFormProc);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder *businessCardHolder;
	IndexHolder *indexHolder;
	BusinessCard *businessCardLink;
	BusinessCard *previous = NULL;
	Long i;
	Long j;
	Index(*indexes);
	Index *indexLink;
	Long indexCount;
	Long location;
	TVINSERTSTRUCT tvItem = { 0, };
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];

	//5. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//5.1. ����ø���� �����ϴ�.
		IndexHolder_Arrange(indexHolder);
		//5.2. Ʈ���� ��Ʈ���� ��� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_DELETEITEM, (WPARAM)0, (LPARAM)TVGN_ROOT);
		//5.3. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� �߰��ϴ�.
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.pszText = "ȸ���";
		tvItem.hInsertAfter = TVI_FIRST;
		tvItem.hParent = TVI_ROOT;
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
		//5.4. ����ø���� ���θ���Ʈ�� �����.
		IndexHolder_MakeList(indexHolder, &indexes, &indexCount);
		//5.5. ���� ����ŭ �ݺ��ϴ�.
		i = 0;
		while (i < indexCount) {
			//5.5.1. Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ�� �߰��ϴ�.
			indexLink = indexes + i;
			tvItem.item.pszText = indexLink->name;
			tvItem.hParent = hCompanies;
			tvItem.hInsertAfter = TVI_LAST;
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
			//5.5.2. Ʈ���� ��Ʈ���� ��ȣ �׸� ���� ����ŭ �̸��� �߰��ϴ�.
			j = 0;
			while (j < indexLink->length) {
				businessCardLink = Index_GetAt(indexLink, j);
				tvItem.item.pszText = businessCardLink->personal.name;
				tvItem.hParent = hCompany;
				tvItem.hInsertAfter = TVI_LAST;
				SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_INSERTITEM, (WPARAM)0, (LPARAM)&tvItem);
				j++;
			}
			i++;
		}
		//5.6. ó�� �������� �̵��ϴ�.
		businessCardLink = BusinessCardHolder_First(businessCardHolder);
		//5.7. ������ ����ϴ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//5.8. ����ø���� ������ ã��.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//5.9. ���ο��� ������ ��ġ�� ã��.
		location = Index_Find(indexLink, businessCardLink);
		//5.10. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã��.

		//5.11. Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ�� ã��.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//5.12. Ʈ���� ��Ʈ���� ��ȣ �׸񿡼� �̸� �׸��� ã��.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//5.13. Ʈ���� ��Ʈ���� ȸ����� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//5.14. Ʈ���� ��Ʈ���� ��ȣ �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//5.15. Ʈ���� ��Ʈ�ѿ��� �̸� �׸��� �����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

		if (indexes != NULL) {
			free(indexes);
		}
	}
	return TRUE;
}

BOOL BusinessCardHolderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	Long i;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };

	//6. ó�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//6.1. ����ø���� ó������ �̵��ϴ�.
		businessCardLink = BusinessCardHolder_First(businessCardHolder);
		//6.2. ������ ����ϴ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//6.3. ����ø���� ������ ã��.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//6.4. ã�� ���ο��� ������ ��ġ�� ã��.
		location = Index_Find(indexLink, businessCardLink);
		//6.5. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã�´�.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//6.6. Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ �׸��� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//6.7. Ʈ���� ��Ʈ���� ��ȣ �׸񿡼� �̸� �׸��� ã��.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//6.8. Ʈ���� ��Ʈ���� ȸ����� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//6.9. Ʈ���� ��Ʈ���� ��ȣ �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//6.10. Ʈ���� ��Ʈ�ѿ��� �̸� �׸��� �����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	Long i;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };

	//7. ���� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//7.1. ����ø���� �������� �̵��ϴ�.
		businessCardLink = BusinessCardHolder_Previous(businessCardHolder);
		//7.2. ������ ����ϴ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//7.3. ����ø���� ������ ã��.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//7.4. ã�� ���ο��� ������ ��ġ�� ã��.
		location = Index_Find(indexLink, businessCardLink);
		//7.5. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã�´�.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//7.6. Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ �׸��� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//7.7. Ʈ���� ��Ʈ���� ��ȣ �׸񿡼� �̸� �׸��� ã��.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//7.8. Ʈ���� ��Ʈ���� ȸ����� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//7.9. Ʈ���� ��Ʈ���� ��ȣ �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//7.10. Ʈ���� ��Ʈ�ѿ��� �̸� �׸��� �����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

	}
	return TRUE;
}

BOOL BusinessCardHolderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	Long i;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };

	//8. ���� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//8.1. ����ø���� �������� �̵��ϴ�.
		businessCardLink = BusinessCardHolder_Next(businessCardHolder);
		//8.2. ������ ����ϴ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//8.3. ����ø���� ������ ã��.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//8.4. ã�� ���ο��� ������ ��ġ�� ã��.
		location = Index_Find(indexLink, businessCardLink);
		//8.5. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã�´�.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//8.6. Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ �׸��� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//8.7. Ʈ���� ��Ʈ���� ��ȣ �׸񿡼� �̸� �׸��� ã��.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//8.8. Ʈ���� ��Ʈ���� ȸ����� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//8.9. Ʈ���� ��Ʈ���� ��ȣ �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//8.10. Ʈ���� ��Ʈ�ѿ��� �̸� �׸��� �����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);

	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hCompanies;
	HTREEITEM hCompany;
	HTREEITEM hName;
	Long i;
	TCHAR companyName[64];
	TVINSERTSTRUCT tvItem = { 0, };

	//9. ������ ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//9.1. ����ø���� ���������� �̵��ϴ�.
		businessCardLink = BusinessCardHolder_Last(businessCardHolder);
		//9.2. ������ ����ϴ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
		//9.3. ����ø���� ������ ã��.
		indexLink = IndexHolder_Find(indexHolder, businessCardLink->company.name);
		//9.4. ã�� ���ο��� ������ ��ġ�� ã��.
		location = Index_Find(indexLink, businessCardLink);
		//9.5. Ʈ���� ��Ʈ�ѿ��� ȸ��� �׸��� ã�´�.
		hCompanies = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0);
		//9.6. Ʈ���� ��Ʈ���� ȸ��� �׸񿡼� ��ȣ �׸��� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompanies);
		tvItem.item.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.item.hItem = hCompany;
		tvItem.item.pszText = companyName;
		tvItem.item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		while (hCompany != NULL && strcmp(companyName, indexLink->name) != 0) {
			hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hCompany);
			tvItem.item.hItem = hCompany;
			SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem.item);
		}
		//9.7. Ʈ���� ��Ʈ���� ��ȣ �׸񿡼� �̸� �׸��� ã��.
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		i = 0;
		while (i < location) {
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);
			i++;
		}
		//9.8. Ʈ���� ��Ʈ���� ȸ����� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompanies);
		//9.9. Ʈ���� ��Ʈ���� ��ȣ �׸��� ��ģ��.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)hCompany);
		//9.10. Ʈ���� ��Ʈ�ѿ��� �̸� �׸��� �����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)hName);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hName);
	}

	return TRUE;
}
BOOL BusinessCardHolderForm_OnTreeViewNameItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder * businessCardHolder;
	BusinessCard *businessCardLink;
	IndexHolder *indexHolder;
	Index *indexLink;
	Long location;
	HTREEITEM hSelected;
	HTREEITEM hCompany;
	HTREEITEM hName;
	TCHAR companyName[64];
	TVITEM tvItem = { 0, };

	//10. Ʈ���� ��Ʈ���� �̸� �׸��� ����Ŭ������ ��
	if (((LPNMHDR)lParam)->code == NM_DBLCLK)
	{
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		indexHolder = (IndexHolder*)GetProp(hWnd, "PROP_INDEXHOLDER");
		//10.1. Ʈ���� ��Ʋ�ο��� ���õ� �̸� �׸��� �д´�.
		hSelected = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CARET, (LPARAM)0);
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_SELECTITEM, (WPARAM)TVGN_DROPHILITE, (LPARAM)hSelected);
		//10.2. Ʈ���� ��Ʈ�ѿ��� ���õ� �̸� �׸��� �θ� ��ȣ�� ã�´�.
		hCompany = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_PARENT, (LPARAM)hSelected);
		//10.3. Ʈ���� ��Ʈ�ѿ��� ���õ� �̸� �׸��� ��ġ�� ã�´�.
		location = 0;
		hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)hCompany);
		while (hName != hSelected) {
			location++;
			hName = (HTREEITEM)SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)hName);

		}
		//10.4. ����ø���� ������ ã��.
		tvItem.mask = TVIF_TEXT | TVIF_HANDLE;
		tvItem.hItem = hCompany;
		tvItem.pszText = companyName;
		tvItem.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_TREE_INDEX), TVM_GETITEM, (WPARAM)0, (LPARAM)&tvItem);
		indexLink = IndexHolder_Find(indexHolder, companyName);
		//10.5. ���ο��� ������ ã��.
		businessCardLink = Index_GetAt(indexLink, location);
		//10.6. ����ø���� �̵��ϴ�.
		businessCardLink = BusinessCardHolder_Move(businessCardHolder, businessCardLink);
		//10.7. ������ ����ϴ�.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_FAXNUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.faxNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMPANY_URL), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->company.url);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.telephoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCardLink->personal.position);
	}
	return TRUE;
}