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

string jylj = "C:\\Program Files (x86)\\Mythware\\������ù���ϵͳ���v6.0 2020������\\StudentMain.exe";

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
        MessageBox(0,"�򿪻���ռ��а����","Error",MB_OK|MB_ICONERROR);   
        return;   
    }
    HGLOBAL hMen;   
    hMen = GlobalAlloc(GMEM_MOVEABLE, ((strlen(in.c_str())+1)*sizeof(TCHAR))); 
    if (!hMen)   
    {   
        MessageBox(0,"����ȫ���ڴ����","Error",MB_OK|MB_ICONERROR);    
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

bool getProcess(const char *procressName)                //�˺��������������ִ�Сд
{
    char pName[MAX_PATH];                                //��PROCESSENTRY32�ṹ���е�szExeFile�ַ����鱣��һ�£����ڱȽ�
    strcpy(pName,procressName);                            //��������
    CharLowerBuff(pName,MAX_PATH);                        //������ת��ΪСд
    PROCESSENTRY32 currentProcess;                        //��ſ��ս�����Ϣ��һ���ṹ��
    currentProcess.dwSize = sizeof(currentProcess);        //��ʹ������ṹ֮ǰ�����������Ĵ�С
    HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//��ϵͳ�ڵ����н�����һ������
 
    if (hProcess == INVALID_HANDLE_VALUE)
    {
        return false;
    }
 
    bool bMore=Process32First(hProcess,&currentProcess);        //��ȡ��һ��������Ϣ
    while(bMore)
    {
        CharLowerBuff(currentProcess.szExeFile,MAX_PATH);        //��������ת��ΪСд
        if (strcmp(currentProcess.szExeFile,pName)==0)            //�Ƚ��Ƿ���ڴ˽���
        {
            CloseHandle(hProcess);                                //���hProcess���
            return true;
        }
        bMore=Process32Next(hProcess,&currentProcess);            //������һ��
    }
 
    CloseHandle(hProcess);    //���hProcess���
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
    ::GetModuleFileName(NULL, Path, MAX_PATH);           //��ȡ����·��
    HINSTANCE res;
    res = ShellExecute(NULL, "runas", Path, Param, NULL, Showcmd);
    return 0;
}

HWND hwnd,hText;

LPCSTR Mods[2]={"�����������У�","����δ���С�"};
HINSTANCE Ghi;
bool SysMode,MMoS;
LPSTR lpRestartString;

int n45; 

bool RDe;

HWND jy[64];
int jyb=0;

HWND Modifyc,Modifyf,Opent;

int Li[4]={SW_SHOWNORMAL,SW_MINIMIZE,SW_MAXIMIZE,SW_HIDE};
LPCSTR CWMT[3]={"���ڻ�������","��С��������","��󻯱�����"};
LPCSTR FWMT[4]={"���ڻ���ǰ����","��С����ǰ����","��󻯵�ǰ����","���ص�ǰ����"};
int Modset[2]={1,1};

int OpenID=0;
LPCSTR Runs[12]={"cmd /c start taskmgr.exe","cmd /c start cmd.exe","cmd /c start osk.exe","cmd /c start gpedit.msc","cmd /c start regedit.exe","cmd /c shutdown -p","cmd /c start notepad.exe","cmd /c start mspaint.exe","cmd /c start calc.exe","cmd /c start compmgmt.msc","cmd /c start control.exe","cmd /c start ms-settings:"};
LPCSTR Openlist[12]={"�����������","��������ʾ��","����Ļ����","�������","��ע���༭��","�򿪹ػ�����","�򿪼��±�","��΢��ͼ","�򿪼�����","�򿪼��������","�򿪿������","������"};

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
				CreateWindowEx(0,"button","ɱ����",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,0,30,160,80,hwnd,(HMENU)101,Ghi,0);
				CreateWindowEx(0,"button","���м���",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,160,30,160,80,hwnd,(HMENU)102,Ghi,0);
				CreateWindowEx(0,"button","��������",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,320,30,160,80,hwnd,(HMENU)103,Ghi,0);
				CreateWindowEx(0,"button","������������",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,480,30,160,80,hwnd,(HMENU)104,Ghi,0);
				CreateWindowEx(0,"button","����ָ�",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,0,110,160,80,hwnd,(HMENU)105,Ghi,0);
				Modifyc=CreateWindowEx(0,"button","��С��������",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,160,110,160,80,hwnd,(HMENU)106,Ghi,0);
				Modifyf=CreateWindowEx(0,"button","��С����ǰ����",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,320,110,160,80,hwnd,(HMENU)107,Ghi,0);
				Opent=CreateWindowEx(0,"button","�����������",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,480,110,160,80,hwnd,(HMENU)108,Ghi,0);
				CreateWindowEx(0,"button","��������",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,0,190,160,80,hwnd,(HMENU)109,Ghi,0);
				CreateWindowEx(0,"button","���ı����ڱ仯ģʽ",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,160,190,160,80,hwnd,(HMENU)110,Ghi,0);
				CreateWindowEx(0,"button","���ĵ�ǰ���ڱ仯ģʽ",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,320,190,160,80,hwnd,(HMENU)111,Ghi,0);
				CreateWindowEx(0,"button","������������",WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON,480,190,160,80,hwnd,(HMENU)112,Ghi,0);
			}
			else
			{
				MMoS=false;
				if(!IsProcessRunAsAdmin())
				{
					int doRetry=MessageBox(0,"δȡ�ù���ԱȨ��,��������!\n��=ʹ��NSudo����(��ҪNSudoLG.exe!)","Warn",MB_OK|MB_ICONWARNING);
					if(doRetry-6)
					{
						char *CommandL;
						sprintf(CommandL,"cmd /c start nsudolg /P:E /U:T \"%s\"",(char*)lpRestartString);
						WinExec(CommandL,SW_HIDE);
						PostQuitMessage(0);
					}
				}
				CreateWindowEx(0,"static","PMA Win32/��ͨģʽ",WS_VISIBLE|WS_CHILD,0,0,200,30,hwnd,0,Ghi,0);
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
						int Mok=MessageBox(0,"��=taskkill\n��=ntsd","ģʽѡ��",MB_YESNO);
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
							MessageBox(0,"ɱ��ʧ��!","Error",MB_OK);
						}
						else{
							MessageBox(0,"ɱ���ɹ�!","Info",MB_OK);
						}
						break;
					}
					case 102:
					{
						if(SysMode)
						{
							MessageBox(0,"�Ѿ�����!","Warn",MB_OK|MB_ICONWARNING);
							break;
						}
						gqhf(0);
						Sleep(100);
						if(getProcess("StudentMain.exe"))
						{
							MessageBox(0,"���гɹ���","Info",MB_OK);
						}
						else
						{
							MessageBox(0,"����ʧ�ܣ�","Error",MB_OK);
						}
						break;
					}
					case 103:
					{
						if(!SysMode)
						{
							MessageBox(0,"����δ���У�","Warn",MB_OK|MB_ICONWARNING);
							break;
						}
						else
						{
							gqhf(1);
							Sleep(100);
							if(getProcess("StudentMain.exe"))
							{
								MessageBox(0,"ɱ��ʧ��!","Error",MB_OK);
							}
							else
							{
								MessageBox(0,"ɱ���ɹ�!","Info",MB_OK);
								gqhf(0);
								Sleep(100);
								if(getProcess("StudentMain.exe"))
								{
									MessageBox(0,"���гɹ�!","Info",MB_OK);
								}
								else
								{
									MessageBox(0,"����ʧ��!","Error",MB_OK);
								} 	
							}
							break;				
						}
					}
					case 104:
					{
						fz("mythware_super_password");
						MessageBox(0,"���!","Info",MB_OK);
						break;
					}
					case 105:
					{
						::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
						int Mms=MessageBox(hwnd,"��=���𣬷�=�ָ�","Select",MB_YESNO|MB_ICONINFORMATION);
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
						MessageBox(0,"��ʱ���԰�'0'�ָ�.","Tip",MB_OK|MB_ICONINFORMATION);
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
	if(getProcess("StudentMain.exe"))n45=MessageBox(0,"��⵽�����������У��Ƿ�������ģʽ��","��ʾ",MB_YESNO);
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

