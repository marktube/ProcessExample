// ProcessExamp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#pragma comment(lib, "urlmon")

int _tmain(int argc, _TCHAR* argv[])
{
	/*UNIT WinExec(LPCSTR lpCmdLine, UINT uCmdShow)
	lpCmdLine:ָ��һ��Ҫִ�еĿ�ִ���ļ�
	uCmdShow:�������к�Ĵ���״̬
	����ʾ����WinExec("c:\\windows\\system32\\notepad.exe",SW_HIDE);
	�������±����̵����޷��������ڣ�ֻ�����������������notepad.exe*/

	//�����򿽱���d��Ŀ¼��Ȼ������������(������Ҫ����ԱȨ��)
	//URLDownloadToFile(NULL, L"D:\\Games\\DmmUnlocker 1.1.exe", L"d:\\virus.exe", 0, NULL);
	//WinExec("d:\\virus.exe", SW_SHOW);

	//CreateProcess������ʹ��
	/*BOOL CreateProcess(LPCTSTR lpApplicationName,//��ִ���ļ����ļ���
	LPTSTR lpCommandline,//ָ���������½��̵������в���
	LPSECURITY_ATTRIBUTES lpProcessAttributes,//���̰�ȫ���ԣ�ͨ��ΪNULL��ʾĬ��
	LPSECURITY_ATTRIBUTES lpThreadAttributes,//�̰߳�ȫ���ԣ�ͨ��ΪNULL��ʾĬ��
	BOOL bInheritHanles, //ָ����ǰ�����пɼ̳о���Ƿ��½��̼̳�
	DWORD dwCreationFlags,//ָ���½��̵����ȼ��Լ�����������־
	LPVOID lpEnvironment, //ָ���½��̵Ļ�������
	LPCTSTR lpCurrentDirectory,//ָ���½���ʹ�õĵ�ǰĿ¼
	LPSTARUPINFO lpStartupInfo,//ָ��STARUPINFO�ṹ���ָ�룬ָ���½��̵�������Ϣ
	LPPROCESS_INFORMATION lpProcessInformation//ָ��PROCESS_INFORMATION�ṹ���ָ��
	,���ڷ����½��̺����̵߳������Ϣ)*/

	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);
	BOOL bRet = CreateProcess(L"c:\\windows\\system32\\notepad.exe", 
		NULL, NULL, NULL, false, NULL, NULL, NULL, &si, &pi);

	if (!bRet){
		printf("CreateProcess Error!\n");
		return -1;
	}
	//���̴�������Ҫ�ر�pi�ṹ���ڵ��������
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	Sleep(3000);

	//����ָ������
	HWND hNoteWnd = FindWindow(NULL, L"�ޱ��� - ���±�");
	if (hNoteWnd == NULL){
		MessageBox(NULL, L"δ�ҵ�����", L"GG", MB_OK);
		return -1;
	}

	DWORD dwNotePid = 0;
	GetWindowThreadProcessId(hNoteWnd, &dwNotePid);
	if (dwNotePid == 0){
		MessageBox(NULL, L"δ�ҵ�����ID", L"GG", MB_OK);
		return -1;
	}
	HANDLE hNoteHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwNotePid);
	if (hNoteHandle == NULL){
		MessageBox(NULL, L"δ�ҵ����", L"GG", MB_OK);
		return -1;
	}
	BOOL bret = TerminateProcess(hNoteHandle, 0);
	CloseHandle(hNoteHandle);
	return 0;
}

