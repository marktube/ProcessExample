// ProcessExamp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#pragma comment(lib, "urlmon")

int _tmain(int argc, _TCHAR* argv[])
{
	/*UNIT WinExec(LPCSTR lpCmdLine, UINT uCmdShow)
	lpCmdLine:指向一个要执行的可执行文件
	uCmdShow:程序运行后的窗口状态
	调用示例：WinExec("c:\\windows\\system32\\notepad.exe",SW_HIDE);
	创建记事本进程但是无法看到窗口，只能在任务管理器看到notepad.exe*/

	//将程序拷贝到d：目录下然后开启进程运行(运行需要管理员权限)
	//URLDownloadToFile(NULL, L"D:\\Games\\DmmUnlocker 1.1.exe", L"d:\\virus.exe", 0, NULL);
	//WinExec("d:\\virus.exe", SW_SHOW);

	//CreateProcess函数的使用
	/*BOOL CreateProcess(LPCTSTR lpApplicationName,//可执行文件的文件名
	LPTSTR lpCommandline,//指定欲传给新进程的命令行参数
	LPSECURITY_ATTRIBUTES lpProcessAttributes,//进程安全属性，通常为NULL表示默认
	LPSECURITY_ATTRIBUTES lpThreadAttributes,//线程安全属性，通常为NULL表示默认
	BOOL bInheritHanles, //指定当前进程中可继承句柄是否被新进程继承
	DWORD dwCreationFlags,//指定新进程的优先级以及其他创建标志
	LPVOID lpEnvironment, //指定新进程的环境变量
	LPCTSTR lpCurrentDirectory,//指定新进程使用的当前目录
	LPSTARUPINFO lpStartupInfo,//指向STARUPINFO结构体的指针，指定新进程的启动信息
	LPPROCESS_INFORMATION lpProcessInformation//指向PROCESS_INFORMATION结构体的指针
	,用于返回新进程和主线程的相关信息)*/

	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);
	BOOL bRet = CreateProcess(L"c:\\windows\\system32\\notepad.exe", 
		NULL, NULL, NULL, false, NULL, NULL, NULL, &si, &pi);

	if (!bRet){
		printf("CreateProcess Error!\n");
		return -1;
	}
	//进程创建后需要关闭pi结构体内的两个句柄
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	Sleep(3000);

	//结束指定进程
	HWND hNoteWnd = FindWindow(NULL, L"无标题 - 记事本");
	if (hNoteWnd == NULL){
		MessageBox(NULL, L"未找到窗口", L"GG", MB_OK);
		return -1;
	}

	DWORD dwNotePid = 0;
	GetWindowThreadProcessId(hNoteWnd, &dwNotePid);
	if (dwNotePid == 0){
		MessageBox(NULL, L"未找到进程ID", L"GG", MB_OK);
		return -1;
	}
	HANDLE hNoteHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwNotePid);
	if (hNoteHandle == NULL){
		MessageBox(NULL, L"未找到句柄", L"GG", MB_OK);
		return -1;
	}
	BOOL bret = TerminateProcess(hNoteHandle, 0);
	CloseHandle(hNoteHandle);
	return 0;
}

