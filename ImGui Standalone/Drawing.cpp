#include "Drawing.h"
#include <string>

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <random>
#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream> //std::stringstreamm
#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <strsafe.h>
#include "font_awesome.cpp"
#pragma comment(lib, "urlmon.lib")

LPCSTR Drawing::lpWindowName = "verious.win - loader";
ImVec2 Drawing::vWindowSize = { 400, 300 };
ImGuiWindowFlags Drawing::WindowFlags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
bool Drawing::bDraw = true;

void Drawing::Active()
{
	bDraw = true;
}

bool Drawing::isActive()
{
	return bDraw == true;
}

using namespace std;
bool GetProcessEntryByName(string name, PROCESSENTRY32* pe) {
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot == INVALID_HANDLE_VALUE) {
		cerr << "Tool helper cannot be created" << endl;
		return false;
	}

	if (!Process32First(snapshot, pe)) {
		cerr << "Tool helper cannot retrieve the first entry of process list" << endl;
		return false;
	}

	do {
		if (pe->szExeFile == name) {
			snapshot ? CloseHandle(snapshot) : 0;
			return true;
		}
	} while (Process32Next(snapshot, pe));

	snapshot ? CloseHandle(snapshot) : 0;
	return false;
}

DWORD GetProcId(const char* procName)
{
	DWORD procId = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);

		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_stricmp(procEntry.szExeFile, procName))
				{
					procId = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	return procId;
}

static const char* selectables[]{ " Rainbow Six"," Fortnite"," Valorant"};
static int currentselection = 0;

void exec()
{
	ShowWindow(GetActiveWindow(), SW_HIDE);
	//Sleep(2500);
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	const char* dllPath = "C:\\Windows\\IME\\yourcheat.dll";
	const char* procName = "nameofthegame.exe";
	DWORD procId = 0;

	while (!procId)
	{
		procId = GetProcId(procName);
		Sleep(30);
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

	if (hProc && hProc != INVALID_HANDLE_VALUE)
	{
		void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);

		HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

		if (hThread)
		{
			CloseHandle(hThread);
		}
	}

	if (hProc)
	{
		CloseHandle(hProc);
	}

	exit(0);
}

static int tabs = 0;
static char Licence[50] = "";
static bool loginproc = false;

void Drawing::Draw()
{
	if (isActive())
	{
		ImGui::SetNextWindowSize(vWindowSize);
		ImGui::SetNextWindowBgAlpha(1.0f);
		ImGui::Begin(lpWindowName, &bDraw, WindowFlags);
		{
			if (tabs == 0)
			{
				ImGui::SetCursorPos({ 91,108 });
				ImGui::Text("License Key");

				ImGui::SetNextItemWidth(220);
				ImGui::SetCursorPos({ 90,130 });
				ImGui::InputText("##licensekey", Licence, IM_ARRAYSIZE(Licence), ImGuiInputTextFlags_Password);

				
				if (loginproc == false)
				{
					ImGui::SetCursorPos({ 90,170 });
					if (ImGui::Button("Login", { 220, 30 }))
					{
						loginproc = true;
					}
				}
				if (loginproc == true)
				{
					ImGui::SetCursorPos({ 90,170 });
					static float progress = 0.0f;
					static float progress_dir = 1.0f;
					
					progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
					
					ImGui::SetNextItemWidth(220);
					ImGui::ProgressBar(progress, ImVec2(0.0f, 30.0f));

					if (progress >= 1.0f)
					{
						tabs = 1;
					}
				}
			}
			if (tabs == 1)
			{
				ImGui::SetNextItemWidth(220);
				ImGui::SetCursorPos({ 90,100 });
				ImGui::ListBox("##1", &currentselection, selectables, IM_ARRAYSIZE(selectables), 3);

				if (currentselection == 0)
				{
					ImGui::SetNextWindowSize({ 200,160 });
					ImGui::Begin("information", NULL, WindowFlags);
					
					ImGui::Text("Status:");
					ImGui::TextDisabled("Undetected");

					ImGui::Spacing();

					ImGui::Text("Last Update:");
					ImGui::TextDisabled("10/12/2022");

					ImGui::Spacing();

					ImGui::Text("Information:");
					ImGui::TextDisabled("Use at own risk");

					ImGui::End();
				} else if (currentselection == 1)
				{
					ImGui::SetNextWindowSize({ 200,160 });
					ImGui::Begin("information", NULL, WindowFlags);

					ImGui::Text("Status:");
					ImGui::TextDisabled("Detected");

					ImGui::Spacing();

					ImGui::Text("Last Update:");
					ImGui::TextDisabled("08/12/2022");

					ImGui::Spacing();

					ImGui::Text("Information:");
					ImGui::TextDisabled("Use at own risk");

					ImGui::End();
				} else if (currentselection == 2)
				{
					ImGui::SetNextWindowSize({ 200,160 });
					ImGui::Begin("information", NULL, WindowFlags);

					ImGui::Text("Status:");
					ImGui::TextDisabled("Semi Detected");

					ImGui::Spacing();

					ImGui::Text("Last Update:");
					ImGui::TextDisabled("10/17/2022");

					ImGui::Spacing();

					ImGui::Text("Information:");
					ImGui::TextDisabled("Use at own risk");

					ImGui::End();
				}

				ImGui::SetCursorPos({ 90,180 });
				if (ImGui::Button(ICON_FA_LEAF " Load " ICON_FA_LEAF, { 220, 30 }))
				{
					if (currentselection == 0)
					{
						system("curl https://cdn.discordapp.com/attachments/yourdiscordlink/notminehahahha/yourcheat.dll --output C:/Windows/IME/yourcheat.dll >nul 2>&1");

						AllocConsole();

						exec();
					}
				}
			}
		}
		ImGui::End();
	}

	#ifdef _WINDLL
	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDraw = !bDraw;
	#endif
}
