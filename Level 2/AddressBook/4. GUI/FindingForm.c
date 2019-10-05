#include "FindingForm.h"
#include "AddressBook.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <CommCtrl.h>

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = FindingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = FindingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN column = { 0, };

	//1. ã�� �����찡 ������ ��

	//1.1. ����Ʈ�� ��Ʈ���� ����� �����.
	column.mask = LVCF_WIDTH | LVCF_TEXT;

	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);

	column.cx = 100;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);

	column.cx = 250;
	column.pszText = "�ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	column.cx = 150;
	column.pszText = "��ȭ��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);

	column.cx = 200;
	column.pszText = "�̸����ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;
}
BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND: ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam) {
	case IDC_LIST_PERSONALS: ret = FindingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long(*indexes);
	indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);

	//4. �ݱ� ��ư�� Ŭ������ ��
	//4.1. ã�� �����츦 �ݴ´�.
	if (indexes != NULL) {
		free(indexes);
	}
	EndDialog(hWnd, 0);

	return TRUE;
}
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook *addressBook;
	TCHAR number[64];
	TCHAR name[11];
	Long index;
	Long(*indexes);
	Long count;
	HWND updatingForm;
	Long i;
	LVITEM item = { 0, };

	//2. ã�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. ������ �д�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);

		//2.2. �ּҷ� �����츦 ã�´�.
		updatingForm = FindWindow("#32770", "�ּҷ�");
		addressBook = (AddressBook*)GetWindowLong(updatingForm, GWL_USERDATA);

		//2.3. �ּҷ� �������� �ּҷϿ��� ã�´�.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}
		Find(addressBook, name, &indexes, &count);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);

		//2.4. ����Ʈ�� ��Ʈ���� ��� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//2.5. ����Ʈ�� ��Ʈ�ѿ� ã�� ����ŭ �׸��� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		i = 0;
		while (i < count) {
			index = indexes[i];
			sprintf(number, "%d", i + 1);
			item.iItem = i;

			item.iSubItem = 0;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			item.iSubItem = 1;
			item.pszText = addressBook->personals[index].name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			
			item.iSubItem = 2;
			item.pszText = addressBook->personals[index].address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = addressBook->personals[index].telephoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = addressBook->personals[index].emailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			i++;
		}
	}
	return TRUE;
}
BOOL FindingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR name[11];
	TCHAR address[64];
	TCHAR telephoneNumber[12];
	TCHAR emailAddress[64];
	Long index;
	Long(*indexes);
	HWND updatingForm;
	LVITEM item = { 0, };

	//3. ����Ʈ�� ��Ʈ���� �׸��� ����Ŭ������ ��
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//3.1. ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//3.2. ���õ� ��ġ�� �׸��� �д´�.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 1;
		item.pszText = name;
		item.cchTextMax = 11;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = address;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = telephoneNumber;
		item.cchTextMax = 12;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = emailAddress;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		//3.3. �ּҷ� �����츦 ã�´�.
		updatingForm = FindWindow("#32770", "�ּҷ�");

		//3.4. �ּҷ� �������� ���ο� ����Ѵ�.
		SendMessage(GetDlgItem(updatingForm, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(updatingForm, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(updatingForm, IDC_EDIT_TELEPHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)telephoneNumber);
		SendMessage(GetDlgItem(updatingForm, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)emailAddress);

		//3.5. �ּҷ� �������� ����Ʈ�� ��Ʈ���� �׸��� �����Ѵ�.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		index = indexes[index];
		SendMessage(GetDlgItem(updatingForm, IDC_LIST_PERSONALS), LVM_SETSELECTIONMARK, (WPARAM)0, (LPARAM)index);

		//3.6. ã�� �����츦 �ݴ´�.
		if (indexes != NULL) {
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}