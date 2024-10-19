#include "menu.h"
#include "constants.h"
#include "../feautures/aimbot.h"
#include "gl/GL.h"
#include "gl/GLU.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_opengl2.h"


const ImVec2 init_window_size = ImVec2(400, 400);
bool show_menu{ false };
bool initialized{ false };
bool context_created{ false };
HWND game_window;
HGLRC my_context;
HGLRC game_context;
HDC gHDC;
WNDPROC original_wnd_proc{ nullptr };

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK newWNDProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (show_menu) 
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return 0;

		switch (msg)
		{
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			return 0;
		}
	}
	return CallWindowProc(original_wnd_proc, hWnd, msg, wParam, lParam);
}

void Menu::toggle_menu()
{
	show_menu = !show_menu;
	ImGuiIO& io = ImGui::GetIO();
	io.WantCaptureMouse = show_menu;
	io.WantCaptureKeyboard = show_menu;
	io.MouseDrawCursor = show_menu;
	originall_set_relative_mouse_mode(!show_menu);

}

void Menu::init()
{
	ImGui::CreateContext();
	game_window = FindWindowA(NULL, "AssaultCube");
	original_wnd_proc = (WNDPROC)SetWindowLongPtr(game_window, GWLP_WNDPROC, (LONG_PTR)newWNDProc);
	ImGui_ImplOpenGL2_Init();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags != ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags != ImGuiConfigFlags_NavEnableSetMousePos;
	io.Fonts->AddFontDefault();


	ImGui::SetCurrentContext(ImGui::GetCurrentContext());

	ImGui::SetNextWindowSize(init_window_size);
	initialized = true;
	std::cout << "menu initialized";
}

void setup_context(HDC& hdc)
{
	my_context = wglCreateContext(hdc);

	wglMakeCurrent(hdc, my_context);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	context_created = true;
}

BOOL __stdcall Menu::new_swap_buffers(HDC hdc)
{
	if (!initialized)
	{
		init();
		original_swap_buffers(hdc);
	}

	game_context = wglGetCurrentContext();
	if (!context_created)
		setup_context(hdc);
	wglMakeCurrent(hdc, my_context);
	Menu::start_render();
	Menu::render();
	Menu::end_render();

	wglMakeCurrent(hdc, game_context);
	return original_swap_buffers(hdc);
}

void Menu::start_render()
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame(); 
}

void Menu::end_render()
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void Menu::render()
{
	if (!show_menu)
		return;

	ImGui::Begin("Menu", &show_menu);
	ImGui::Text("hello, world");
	if (ImGui::Button("Tp Up"))
	{
		local_player->pos.z += 5;
	}

	ImGui::End();
}