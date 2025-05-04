#include <iostream>
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Window.hpp>
#include <w2dr.hpp>

int main(){
    Init(800,800,"hi");
    InitRenderer();

    Texture2D texture = LoadTexture("absolute path");

    while (!WindowShouldClose()) {
        ClearBackground({255,255,255,255});

        DrawTexture2D(texture,0,0,{255,255,255,255});

        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }
}
