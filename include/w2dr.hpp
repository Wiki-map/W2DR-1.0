#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct Colorf {
    float r,g,b,a;
};

struct vec2 {
    float x,y;
};

struct Texture2D {
    unsigned int ID;
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;
    int Height;
    int Width;
};

vec2 GetSpaceCords(int x,int y);

Colorf ColorToColorf(Color val);

unsigned int CompileShader(const char* VertexShader,const char* FragmentShader);
void InitRenderer();

void ClearBackground(Color color);

Texture2D LoadTexture(const char* path);
void DrawTexture2D(Texture2D texture,int x,int y,Color color);

void DrawTriangle(vec2 p1, vec2 p2, vec2 p3);