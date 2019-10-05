#include "UpdatingForm.h"
#include "resource.h"
#include "FindingForm.h"
#include "WordBook.h"
#include <stdlib.h>
#include <stdio.h>
#include <commctrl.h>
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	int response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_UPDATINGFORM), NULL, UpdatingFormProc);

	return response;
}
BOOL CALLBACK UpdatingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = UpdatingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = UpdatingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = UpdatingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = UpdatingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook *wordBook;
	Long count;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	EnglishWord englishWord;
	//1. �����찡 ������ ��

	//1.1. �ܾ����� �����.
	wordBook = (WordBook*)malloc(sizeof(WordBook));
	WordBook_Create(wordBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (Long)wordBook);

	//1.2. �����ϴ�.
	count = Load(wordBook);

	//1.3. ����Ʈ�� ��Ʈ���� ����� �����.
	column.mask = LVCF_WIDTH | LVCF_TEXT;

	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);

	column.cx = 150;
	column.pszText = "�ܾ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);

	column.cx = 100;
	column.pszText = "ǰ��";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	column.cx = 200;
	column.pszText = "�ǹ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);

	column.cx = 250;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	//1.4. ����Ʈ�� ��Ʈ�ѿ� ��ü ������ �����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//1.5. ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸���� �߰��Ѵ�.
	item.mask = LVIF_TEXT;
	i = 0;
	while (i < count) {
		item.iItem = i;
		sprintf(number, "%d", i + 1);
		englishWord = WordBook_GetAt(wordBook, i);

		item.iSubItem = 0;
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = englishWord.word;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = englishWord.wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = englishWord.meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = englishWord.example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
		i++;
	}

	return TRUE;
}
BOOL UpdatingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_RECORD: ret = UpdatingForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = UpdatingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CORRECT: ret = UpdatingForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ERASE: ret = UpdatingForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = UpdatingForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam) {
	case IDC_LIST_ENGLISHWORDS: ret = UpdatingForm_OnListViewItemDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}
BOOL UpdatingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook *wordBook;
	
	//8. �ݱ� ��ư�� Ŭ������ ��

	//8.1. �����Ѵ�.
	wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
	
	if (wordBook != NULL) {
		Save(wordBook);
		//8.2. �ܾ����� ���ش�.
		WordBook_Destroy(wordBook);
		free(wordBook);
	}
	//8.3. �����츦 �ݴ´�.
	EndDialog(hWnd, 0);

	return TRUE;
}
BOOL UpdatingForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook *wordBook;
	TCHAR number[64];
	TCHAR word[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	Long index;
	LVITEM item = { 0, };
	//2. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. ���ܾ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORD), WM_GETTEXT, (WPARAM)64, (LPARAM)word);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);
		
		//2.2. �ܾ��忡�� �����Ѵ�.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(wordBook, word, wordClass, meaning, example);

		//2.3. ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		sprintf(number, "%d", index + 1);

		item.iSubItem = 0;
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = word;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}

	return TRUE;
}
BOOL UpdatingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//3. ã�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. ã�� �����츦 ����Ѵ�.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}
BOOL UpdatingForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	Long index;
	WordBook *wordBook;
	LVITEM item = { 0, };
	EnglishWord englishWord;

	//4. ��ġ�� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. ���ܾ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);

		//4.2. ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//4.3. �ܾ��忡�� ��ġ��.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(wordBook, index, wordClass, meaning, example);

		//4.4. ����Ʈ�� ��Ʈ���� �׸��� ��ġ��.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		englishWord = WordBook_GetAt(wordBook, index);

		item.iSubItem = 2;
		item.pszText = englishWord.wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = englishWord.meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = englishWord.example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}
BOOL UpdatingForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	WordBook *wordBook;
	Long erased;
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	//5. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1. ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
	
		//5.2. �ܾ��忡�� �����.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		erased = Erase(wordBook, index);
		if (erased == -1) {
			//5.3. ����Ʈ�� ��Ʈ���� �׸��� �����.
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);

			//5.4. ���õ� ��ġ���� ������ �ٱ��� ��ȣ�� ��ģ��.
			item.iSubItem = 0;
			i = index;
			while (i < wordBook->length) {
				sprintf(number, "%d", i + 1);
				item.iItem = index;
				item.pszText = number;
				SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
				i++;
			}
		}
	}
	return TRUE;
}
BOOL UpdatingForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook *wordBook;
	Long i;
	TCHAR number[64];
	LVITEM item = { 0, };
	EnglishWord englishWord;

	//6. �����ϱ� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1. �ܾ��忡�� �����Ѵ�.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(wordBook);

		//6.2. ����Ʈ�� ��Ʈ���� ��� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//6.3. �ܾ��忡 ���� �� ����ŭ ����Ʈ�� ��Ʈ���� �׸��� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		i = 0;
		while (i < wordBook->length) {
			sprintf(number, "%d", i + 1);
			item.iItem = i;
			englishWord = WordBook_GetAt(wordBook, i);

			item.iSubItem = 0;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			item.iSubItem = 1;
			item.pszText = englishWord.word;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = englishWord.wordClass;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = englishWord.meaning;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = englishWord.example;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			i++;
		}
	}
	return TRUE;
}
BOOL UpdatingForm_OnListViewItemDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	LVITEM item = { 0, };
	TCHAR word[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	//7. ����Ʈ�� ��Ʈ���� �׸��� ����Ŭ������ ��
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//7.1. ����Ʈ�� ��Ʈ���� ���õ� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		
		//7.2. ���õ� ��ġ�� �׸��� �д´�.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 1;
		item.pszText = word;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordClass;
		item.cchTextMax = 11;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = meaning;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		
		item.iSubItem = 4;
		item.pszText = example;
		item.cchTextMax = 128;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_ENGLISHWORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		//7.3. ���ܾ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORD), WM_SETTEXT, (WPARAM)0, (LPARAM)word);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)example);
	}
	return TRUE;
}