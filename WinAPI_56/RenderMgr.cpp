#include "pch.h"
#include "RenderMgr.h"

#include "Engine.h"
#include "LevelMgr.h"
#include "TimeMgr.h"
#include "Camera.h"
#include "VideoPlayer.h"
#include "ATexture.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_opengl3.h"

int PenColor[(int)PEN_TYPE::END] =
{
	IM_COL32(255, 0, 0, 255),
	IM_COL32(0, 255, 0, 255),
	IM_COL32(0, 0, 255, 255),
	IM_COL32(100, 100, 100, 255),
	IM_COL32(255, 255, 255, 255),
	IM_COL32(255, 100, 255, 255),

};
struct GLfloat4
{
	GLfloat R;
	GLfloat G;
	GLfloat B;
	GLfloat A;
	GLfloat4(float r, float g, float b, float a)
		:R(r), G(g), B(b), A(a){}
};
GLfloat4 RectPenColor[(int)PEN_TYPE::END] =
{
	GLfloat4(1, 0, 0, 1),
	GLfloat4(0, 1, 0, 1),
	GLfloat4(0, 0, 1, 1),
	GLfloat4(0.4f, 0.4f, 0.4f, 1),
	GLfloat4(1, 1, 1, 1),
	GLfloat4(1, 0.4f, 1, 1),
};

RenderMgr::RenderMgr()
	:m_DebugRender(false)
{

}

RenderMgr::~RenderMgr()
{

}

void RenderMgr::InitOpenGL(HWND _hwnd) {
	PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1 };
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pf = ChoosePixelFormat(Engine::GetInst()->GetMainDC(), &pfd);
	SetPixelFormat(Engine::GetInst()->GetMainDC(), pf, &pfd);
	Engine::GetInst()->SetMainGLRC(wglCreateContext(Engine::GetInst()->GetMainDC()));
	wglMakeCurrent(Engine::GetInst()->GetMainDC(), Engine::GetInst()->GetMainGLRC());

	if (glewInit() != GLEW_OK) {
		MessageBox(nullptr, L"GLEW 초기화 실패", L"GLEW 오류", MB_OK);
		return;
	}
	InitImGUI();
}

void RenderMgr::InitImGUI() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // 키보드 입력 허용

	ImGui::StyleColorsDark(); // 테마 설정

	// Platform/Renderer binding
	ImGui_ImplWin32_Init(Engine::GetInst()->GetMainWinow());
	ImGui_ImplOpenGL3_Init();

}

void RenderMgr::Release()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(Engine::GetInst()->GetMainGLRC());

}

void RenderMgr::Draw(ATexture* tex, float x, float y, float w, float h) {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, tex->GetLuint());
	glColor4f(1.0f, 1.0f, 1.0f, 1);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(x - w / 2, y - h / 2);
	glTexCoord2f(1, 0); glVertex2f(x + w / 2, y - h / 2);
	glTexCoord2f(1, 1); glVertex2f(x + w / 2, y + h / 2);
	glTexCoord2f(0, 1); glVertex2f(x - w / 2, y + h / 2);
	glEnd();
}

void RenderMgr::Draw(ATexture* tex, Vec2 _pos, Vec2 _size, Vec2 _leftop, Vec2 _spritesize) {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, tex->GetLuint());
	glColor4f(1.0f, 1.0f, 1.0f, 1);

	Vec2 screenResolution = Engine::GetInst()->GetResolution();
	// 좌표 변환
	float left = (_pos.x / (float)screenResolution.x) * 2.0f - 1.1f;
	float right = ((_pos.x + _spritesize.x) / (float)screenResolution.x) * 2.0f - 1.1f;
	float top = ((screenResolution.y - _pos.y) / screenResolution.y) * 2.0f - 0.8f;
	float bottom = ((screenResolution.y - (_pos.y + _spritesize.y)) / screenResolution.y) * 2.0f - 0.8f;

	float u0 = _leftop.x / tex->GetWidth();
	float v0 = _leftop.y / tex->GetHeight();
	float u1 = (_leftop.x + _spritesize.x) / tex->GetWidth();
	float v1 = (_leftop.y + _spritesize.y) / tex->GetHeight();

	glBegin(GL_QUADS);
	glTexCoord2f(u0, v0); glVertex2f(_pos.x - (_spritesize.x * _size.x) / 2, _pos.y - (_spritesize.y * _size.y) /2);
	glTexCoord2f(u1, v0); glVertex2f(_pos.x + (_spritesize.x * _size.x) / 2, _pos.y - (_spritesize.y * _size.y) / 2);
	glTexCoord2f(u1, v1); glVertex2f(_pos.x + (_spritesize.x * _size.x) / 2, _pos.y + (_spritesize.y * _size.y) / 2);
	glTexCoord2f(u0, v1); glVertex2f(_pos.x - (_spritesize.x * _size.x) / 2, _pos.y + (_spritesize.y * _size.y) / 2);
	glEnd();
}

void RenderMgr::Render()
{
	if(m_DebugRender)ImGUIRender();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 한번만 지우기
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

	// 투영 행렬 세팅도 여기서 한 번만 (초기화해두면 더 좋고)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Engine::GetInst()->GetResolution().x, Engine::GetInst()->GetResolution().y, 0, -1, 1);


	LevelMgr::GetInst()->Render(Engine::GetInst()->GetMainDC());

	VideoPlayer::GetInst()->Render();

	Camera::GetInst()->Render();


	if (m_DebugRender)ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SwapBuffers(Engine::GetInst()->GetMainDC());
}

void RenderMgr::ImGUIRender()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	{
		ImGuiWindowFlags flags = 0;
		ImGui::SetNextWindowSize(ImVec2(150, 80), ImGuiCond_Always);
		ImGui::Begin("Debug Info", nullptr, flags);
		for (auto& info : m_ImGUIDebugList)
		{
			ImGui::Text("%s: %s", info.Text, info.Value.c_str());
		}
		m_ImGUIDebugList.clear();

		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::Text("deltaTime: %.4f", ImGui::GetIO().DeltaTime);


	}
	DebugRender();
	ImGui::End();
	ImGui::Render();
}

void RenderMgr::DebugRender()
{
	if (m_DebugRenderList.empty())
		return;

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	list<tDebugShapeInfo>::iterator iter = m_DebugRenderList.begin();

	for (; iter != m_DebugRenderList.end(); )
	{		 
		switch (iter->Shape)
		{
		case DEBUG_SHAPE::RECT:
			drawList->AddRect(ImVec2((int)iter->Center.x - iter->Scale.x / 2.f, (int)iter->Center.y - iter->Scale.y / 2.f), ImVec2((int)iter->Center.x + iter->Scale.x / 2.f, (int)iter->Center.y + iter->Scale.y / 2.f), PenColor[(int)iter->PenType]);
			break;
		case DEBUG_SHAPE::CIRCLE:
			drawList->AddCircle(ImVec2((int)(iter->Center.x), (int)(iter->Center.y)), iter->Scale.x, PenColor[(int)iter->PenType]);
			break;
		case DEBUG_SHAPE::LINE:
			drawList->AddLine(ImVec2((int)iter->Center.x, (int)iter->Center.y), ImVec2((int)iter->Scale.x, (int)iter->Scale.y), PenColor[(int)iter->PenType]);
			break;
		}
				
		iter->CurTime += DT;
		if (iter->Duration < iter->CurTime)
		{
			iter = m_DebugRenderList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void RenderMgr::DebugLog()
{
}
