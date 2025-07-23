#pragma once

#include <GL/glew.h>
#include <gl/GL.h>
class ATexture;


class RenderMgr
{
	SINGLE(RenderMgr);
private:
	list<tDebugShapeInfo> m_DebugRenderList;
	list<wstring>		  m_DebugLog;

	list<tImGUIDebugInfo> m_ImGUIDebugList;

	GLuint m_DebugTex;

	bool m_DebugRender;


public:
	void SetDebugRender(bool _switch) { m_DebugRender = _switch; }

	void AddDebugShape(const tDebugShapeInfo& _Info) { m_DebugRenderList.push_back(_Info); }
	void ClearDebugShape() { m_DebugRenderList.clear(); }

	void AddImGUIDisplay(const tImGUIDebugInfo& _info) { m_ImGUIDebugList.push_back(_info); }
	void InitOpenGL(HWND _hwnd);
	void InitImGUI();
	void Release();
	
	void Draw(ATexture* tex, float x, float y, float w, float h);
	void Draw(ATexture* tex, Vec2 _pos, Vec2 _size, Vec2 _leftop, Vec2 _spritesize);
	void Render();


private:
	void ImGUIRender();
	void DebugRender();
	void DebugLog();
};

