#include "Window.hpp"

GLFWwindow* window;
int WindowWidth;
int WindowHeight;

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void Init(int ScreenHeight,int ScreenWidth,const char* title) {

    WindowHeight = ScreenHeight;
    WindowWidth = ScreenWidth;

    if (glfwInit() == false) {
        std::cout<<"Failed to init glfw\n";
        exit(-1);
    }

    glfwWindowHint(GLFW_RESIZABLE,false);

    window = glfwCreateWindow(ScreenWidth,ScreenHeight,title,NULL,NULL);

    if (window == NULL) {
        std::cout<<"Failed to init window\n";
        exit(-1);
    }

    //glfwSetKeyCallback(window);

    glfwMakeContextCurrent(window);
    int gladversion = gladLoadGL(glfwGetProcAddress);
    if (!gladversion) {
        std::cout<<"Failed to load opengl\n";
        exit(-1);
    }

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );

    std::cout<<"Loaded opengl, version: "<<GLAD_VERSION_MAJOR(gladversion)<<"."<<GLAD_VERSION_MINOR(gladversion)<<"\n";

}

bool WindowShouldClose() {
    return glfwWindowShouldClose(window);
}

int GetScreenHeight() {
    return WindowHeight;
}

int GetScreenWidth() {
    return WindowWidth;
}

void SetVsync(bool val) {
    glfwSwapInterval(val);
}

GLFWwindow* GetWindow() {
    return window;
}