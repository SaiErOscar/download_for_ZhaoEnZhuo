#include <bits/stdc++.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <ShellAPI.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <conio.h>
//#include "cutil.h"
using namespace std;

string jylj = "C:\\Program Files (x86)\\Mythware\\极域课堂管理系统软件v6.0 2020豪华版\\StudentMain.exe";

void gqhf(bool ng)
{
	char s[1145];
	sprintf(s,"start \"%s\"",jylj.c_str());
	if(ng == 1)
	{
		system("cmd /c taskkill /f /im StudentMain.exe /t");
	}
	else
	{
		system(s);
	}  
}

typedef struct tagWNDINFO
{
	DWORD dwProcessId;
	HWND hWnd;
} WNDINFO, *LPWNDINFO;

static BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam)
{
	DWORD dwProcessId;
	GetWindowThreadProcessId(hWnd, &dwProcessId);
	LPWNDINFO pInfo = (LPWNDINFO)lParam;

	if (dwProcessId == pInfo->dwProcessId)
	{
		pInfo->hWnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

static HWND GetProcessMainWnd()
{
	DWORD dwProcessId=::GetCurrentProcessId();
	WNDINFO wi;
	wi.dwProcessId = dwProcessId;
	wi.hWnd = NULL;
	EnumWindows(EnumProc, (LPARAM)&wi);
	return wi.hWnd;
}

HANDLE hout=GetStdHandle(STD_OUTPUT_HANDLE);

void fz(string in)    
{
    if(!OpenClipboard(NULL)|| !EmptyClipboard())    
    {   
        MessageBox(0,"打开或清空剪切板出错","Error",MB_OK|MB_ICONERROR);   
        return;   
    }
    HGLOBAL hMen;   
    hMen = GlobalAlloc(GMEM_MOVEABLE, ((strlen(in.c_str())+1)*sizeof(TCHAR))); 
    if (!hMen)   
    {   
        MessageBox(0,"分配全局内存出错","Error",MB_OK|MB_ICONERROR);    
        CloseClipboard();   
        return;         
    } 
    LPSTR lpStr = (LPSTR)GlobalLock(hMen);    
    memcpy(lpStr,in.c_str(), ((strlen(in.c_str()))*sizeof(TCHAR)));  
    lpStr[strlen(in.c_str())] = (TCHAR)0;   
    GlobalUnlock(hMen);   
    SetClipboardData(CF_TEXT, hMen);   
    CloseClipboard();   
    return;   
}

void EnableDebugPriv(){
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, NULL);
	CloseHandle(hToken);
}

bool getProcess(const char *procressName)                //此函数进程名不区分大小写
{
    char pName[MAX_PATH];                                //和PROCESSENTRY32结构体中的szExeFile字符数组保持一致，便于比较
    strcpy(pName,procressName);                            //拷贝数组
    CharLowerBuff(pName,MAX_PATH);                        //将名称转换为小写
    PROCESSENTRY32 currentProcess;                        //存放快照进程信息的一个结构体
    currentProcess.dwSize = sizeof(currentProcess);        //在使用这个结构之前，先设置它的大小
    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//给系统内的所有进程拍一个快照
 
    if (hProcess == INVALID_HANDLE_VALUE)
    {
        return false;
    }
 
    bool bMore=Process32First(hProcess,&currentProcess);        //获取第一个进程信息
    while(bMore)
    {
        CharLowerBuff(currentProcess.szExeFile,MAX_PATH);        //将进程名转换为小写
        if (strcmp(currentProcess.szExeFile,pName)==0)            //比较是否存在此进程
        {
            CloseHandle(hProcess);                                //清除hProcess句柄
            return true;
        }
        bMore=Process32Next(hProcess,&currentProcess);            //遍历下一个
    }
 
    CloseHandle(hProcess);    //清除hProcess句柄
    return false;
}
bool IsProcessRunAsAdmin()
{
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    BOOL b = AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &AdministratorsGroup);
    if(b)
    {
        CheckTokenMembership(NULL, AdministratorsGroup, &b);
        FreeSid(AdministratorsGroup);
    }
    return b == TRUE;
}
short GetAdmin(LPCSTR Param, int Showcmd)
{
    if (IsProcessRunAsAdmin())
        return 0;
    TCHAR Path[MAX_PATH];
    ZeroMemory(Path, MAX_PATH);
    ::GetModuleFileName(NULL, Path, MAX_PATH);           //获取程序路径
    HINSTANCE res;
    res = ShellExecute(NULL, "runas", Path, Param, NULL, Showcmd);
    return 0;
}

HWND hwnd,hText;

LPCSTR Mods[2]={"极域正在运行！","极域未运行。"};
HINSTANCE Ghi;
bool SysMode,MMoS;
LPSTR lpRestartString;

int n45; 

bool RDe;

HWND jy[64];
int jyb=0;

HWND Modifyc,Modifyf,Opent;

int Li[4]={SW_SHOWNORMAL,SW_MINIMIZE,SW_MAXIMIZE,SW_HIDE};
LPCSTR CWMT[3]={"窗口化本窗口","最小化本窗口","最大化本窗口"};
LPCSTR FWMT[4]={"窗口化当前窗口","最小化当前窗口","最大化当前窗口","隐藏当前窗口"};
int Modset[2]={1,1};

int OpenID=0;
LPCSTR Runs[12]={"cmd /c start taskmgr.exe","cmd /c start cmd.exe","cmd /c start osk.exe","cmd /c start gpedit.msc","cmd /c start regedit.exe","cmd /c shutdown -p","cmd /c start notepad.exe","cmd /c start mspaint.exe","cmd /c start calc.exe","cmd /c start compmgmt.msc","cmd /c start control.exe","cmd /c start ms-settings:"};
LPCSTR Openlist[12]={"打开任务管理器","打开命令提示符","打开屏幕键盘","打开组策略","打开注册表编辑器","打开关机程序","打开记事本","打开微软画图","打开计算器","打开计算机管理","打开控制面板","打开设置"};

LRESULT CALLBACK WndProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
{
	switch(Message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_CREATE:
		{
			if(n45==6)
			{
				MMoS=true;
				SysMode=true;
				hText=CreateWindowEx(0,"static",Mods[0],WS_VISIBLE|WS_CHILD,0,0,200,30,hwnd,0,Ghi,0);
				CreateWindowEx(0,"button","杀极域",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,0,30,160,80,hwnd,(HMENU)101,Ghi,0);
				CreateWindowEx(0,"button","运行极域",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,160,30,160,80,hwnd,(HMENU)102,Ghi,0);
				CreateWindowEx(0,"button","重启极域",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,320,30,160,80,hwnd,(HMENU)103,Ghi,0);
				CreateWindowEx(0,"button","复制万能密码",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,480,30,160,80,hwnd,(HMENU)104,Ghi,0);
				CreateWindowEx(0,"button","挂起恢复",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,0,110,160,80,hwnd,(HMENU)105,Ghi,0);
				Modifyc=CreateWindowEx(0,"button","最小化本窗口",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,160,110,160,80,hwnd,(HMENU)106,Ghi,0);
				Modifyf=CreateWindowEx(0,"button","最小化当前窗口",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,320,110,160,80,hwnd,(HMENU)107,Ghi,0);
				Opent=CreateWindowEx(0,"button","打开任务管理器",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,480,110,160,80,hwnd,(HMENU)108,Ghi,0);
				CreateWindowEx(0,"button","重启程序",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,0,190,160,80,hwnd,(HMENU)109,Ghi,0);
				CreateWindowEx(0,"button","更改本窗口变化模式",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,160,190,160,80,hwnd,(HMENU)110,Ghi,0);
				CreateWindowEx(0,"button","更改当前窗口变化模式",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,320,190,160,80,hwnd,(HMENU)111,Ghi,0);
				CreateWindowEx(0,"button","更改启动程序",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,480,190,160,80,hwnd,(HMENU)112,Ghi,0);
			}
			else
			{
				MMoS=false;
				if(!IsProcessRunAsAdmin())
				{
					int doRetry=MessageBox(0,"未取得管理员权限,功能受限!\n否=使用NSudo尝试(需要NSudoLG.exe!)","Warn",MB_OK|MB_ICONWARNING);
					if(doRetry-6)
					{
						char *CommandL;
						sprintf(CommandL,"cmd /c start nsudolg /P:E /U:T \"%s\"",(char*)lpRestartString);
						WinExec(CommandL,SW_HIDE);
						PostQuitMessage(0);
					}
				}
				CreateWindowEx(0,"static","PMA Win32/普通模式",WS_VISIBLE|WS_CHILD,0,0,200,30,hwnd,0,Ghi,0);
			}
			break;
		}
		case WM_COMMAND:
		{
			if(MMoS)
			{
				switch((int)wParam)
				{
					case 101:
					{
						int Mok=MessageBox(0,"是=taskkill\n否=ntsd","模式选择",MB_YESNO);
						if(Mok==6)
						{
							WinExec("cmd /c taskkill /F /IM StudentMain.exe /T",SW_HIDE);
						}
						else
						{
							WinExec(".\\ntsd.exe -c q -pn studentmain.exe",SW_HIDE);
						}
						Sleep(100);	
						if(getProcess("StudentMain.exe")){
							MessageBox(0,"杀死失败!","Error",MB_OK);
						}
						else{
							MessageBox(0,"杀死成功!","Info",MB_OK);
						}
						break;
					}
					case 102:
					{
						if(SysMode)
						{
							MessageBox(0,"已经运行!","Warn",MB_OK|MB_ICONWARNING);
							break;
						}
						gqhf(0);
						Sleep(100);
						if(getProcess("StudentMain.exe"))
						{
							MessageBox(0,"运行成功！","Info",MB_OK);
						}
						else
						{
							MessageBox(0,"运行失败！","Error",MB_OK);
						}
						break;
					}
					case 103:
					{
						if(!SysMode)
						{
							MessageBox(0,"极域未运行！","Warn",MB_OK|MB_ICONWARNING);
							break;
						}
						else
						{
							gqhf(1);
							Sleep(100);
							if(getProcess("StudentMain.exe"))
							{
								MessageBox(0,"杀死失败!","Error",MB_OK);
							}
							else
							{
								MessageBox(0,"杀死成功!","Info",MB_OK);
								gqhf(0);
								Sleep(100);
								if(getProcess("StudentMain.exe"))
								{
									MessageBox(0,"运行成功!","Info",MB_OK);
								}
								else
								{
									MessageBox(0,"运行失败!","Error",MB_OK);
								} 	
							}
							break;				
						}
					}
					case 104:
					{
						fz("mythware_super_password");
						MessageBox(0,"完成!","Info",MB_OK);
						break;
					}
					case 105:
					{
						::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
						int Mms=MessageBox(hwnd,"是=挂起，否=恢复","Select",MB_YESNO|MB_ICONINFORMATION);
						if(Mms==6)
						{
							gqhf(1);
						}
						else
						{
							gqhf(0);
						}
						break;
					}
					case 106:
					{
						ShowWindow(hwnd,Li[Modset[0]]);
						break;
					}
					case 107:
					{
						ShowWindow(hwnd,SW_MINIMIZE);
						Sleep(100);
						jy[jyb++] = GetForegroundWindow();
						ShowWindow(jy[jyb-1],Li[Modset[1]]);
						ShowWindow(hwnd,SW_SHOWNORMAL);
						Sleep(100);
						MessageBox(0,"随时可以按'0'恢复.","Tip",MB_OK|MB_ICONINFORMATION);
						break; 
					}
					case 108:
					{
						WinExec(Runs[OpenID],SW_HIDE);
						break;
					}
					case 109:
					{
						char* CommandL;
						sprintf(CommandL,"cmd /c start \"%s\"",(char*)lpRestartString);
						WinExec((LPCSTR)CommandL,SW_HIDE);
						PostQuitMessage(0);
						break;
					}
					case 110:
					{
						Modset[0]++;
						Modset[0]%=3;
						SetWindowText(Modifyc,CWMT[Modset[0]]);
						break;
					}
					case 111:
					{
						Modset[1]++;
						Modset[1]%=4;
						SetWindowText(Modifyf,FWMT[Modset[1]]);
						break;
					}
					case 112:
					{
						OpenID++;
						OpenID%=12;
						SetWindowText(Opent,Openlist[OpenID]);
						break;
					}
					default:
					{
						break;
					}
				}
			}
			break;
		}
		default:
		{
			return DefWindowProc(hwnd,Message,wParam,lParam);
		}
	}
	return 0;
}

void UpdateEvent()
{
	if(jyb)
	{
		::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if(GetAsyncKeyState('0'))
		{
			ShowWindow(jy[--jyb],SW_SHOWNORMAL);
			while(GetAsyncKeyState('0'));
		}
	}
	if(getProcess("StudentMain.exe"))
	{
		if(!SysMode)
		{
			SetWindowText(hText,Mods[0]);
			SysMode=true;
		}
	}
	else if(SysMode)
	{
		SysMode=false;
		SetWindowText(hText,Mods[1]);
	}
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	if(getProcess("StudentMain.exe"))n45=MessageBox(0,"检测到极域正在运行，是否开启极域模式？","提示",MB_YESNO);
	lpRestartString=lpCmdLine;
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	memset(&wc,0,sizeof(wc));
	wc.cbSize=sizeof(WNDCLASSEX);
	wc.lpfnWndProc=WndProc;
	wc.hInstance=hInstance;
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)(5);
	wc.lpszClassName="WindowClass";
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	RegisterClassEx(&wc);
	hwnd=CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","1",WS_VISIBLE|WS_SYSMENU|WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_MAXIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,640,480,NULL,NULL,hInstance,NULL);
	if(hwnd==NULL)
	{
		return 0;
	}
	Ghi=hInstance; 
	while(GetMessage(&Msg,NULL,0,0)>0)
	{
		UpdateEvent();
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}

