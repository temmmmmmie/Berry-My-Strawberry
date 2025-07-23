#include "pch.h"
#include "ShaderLoader.h"
#include <fstream>
#include <sstream>
#include <PathMgr.h>


void ShaderLoader::init()
{
    wstring path = PathMgr::GetInst()->GetContentPath();
    m_ShaderID = ShaderLoader::GetInst()->LoadShaderFromFile(path + L"Shaders\\text.vs", path + L"Shaders\\text.fs");
}

GLuint ShaderLoader::LoadShaderFromFile(wstring vertexPath, wstring fragmentPath)
{
    // 1. 쉐이더 파일 읽기
    std::ifstream vShaderFile(vertexPath);
    std::ifstream fShaderFile(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    std::string vertexCodeStr = vShaderStream.str();
    std::string fragmentCodeStr = fShaderStream.str();
    const char* vertexCode = vertexCodeStr.c_str();
    const char* fragmentCode = fragmentCodeStr.c_str();

    // 2. 컴파일
    GLuint vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        MessageBoxA(nullptr, infoLog, "Vertex Shader Compile Error", MB_OK);
    }

    // fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        MessageBoxA(nullptr, infoLog, "Fragment Shader Compile Error", MB_OK);
    }

    // 3. 쉐이더 프로그램 링크
    GLuint ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        MessageBoxA(nullptr, infoLog, "Shader Linking Error", MB_OK);
    }

    // 4. 정리
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return ID;
}
ShaderLoader::ShaderLoader() {};
ShaderLoader::~ShaderLoader() {};
