#include <iostream>
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <Window.hpp>
#include <w2dr.hpp>

#include <time.h>

int main(){
    Init(1024,1024,"hi");
    InitRenderer();

    while (!WindowShouldClose()) {
        ClearBackground({255,255,255,255});


        glfwSwapBuffers(GetWindow());
        glfwPollEvents();
    }
}
