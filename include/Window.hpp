#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

void Init(int ScreenHeight,int ScreenWidth,const char* title);
bool WindowShouldClose();
int GetScreenHeight();
int GetScreenWidth();
void SetVsync(bool val);

GLFWwindow* GetWindow();