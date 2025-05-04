#include <w2dr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <Window.hpp>   

// Transforms pixel cords to opengl cords
vec2 GetSpaceCords(int x, int y) {
    float wH = GetScreenHeight() / 2,wW = GetScreenWidth() / 2;
    float distX = x - wW;
    float distY = wH - y;
    return {distX / wW,distY / wH};
}

Colorf ColorToColorf(Color val)
{
    float r = val.r / 255;
    float g = val.g / 255;
    float b = val.b / 255;
    float a = val.a / 255;
    return {r,g,b,a};
}

unsigned int CompileShader(const char* VertexShader,const char* FragmentShader) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&VertexShader,NULL);
    glCompileShader(vertexShader);

    int  successVertex;
    char infoLogVertex[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successVertex);

    if(!successVertex) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLogVertex);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLogVertex << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&FragmentShader,NULL);
    glCompileShader(fragmentShader);

    int  successFragmet;
    char infoLogFragmet[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFragmet);

    if(!successFragmet) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLogFragmet);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLogFragmet << std::endl;
    }

    int program = glCreateProgram();
    glAttachShader(program,vertexShader);
    glAttachShader(program,fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

    return program;
}

unsigned int DefultShader;

void InitRenderer() {

    const char* VertexShader = "#version 330 core\n"
        "layout (location = 0) in vec4 aPos;\n"
        "layout (location = 1) in vec2 aTexturePos;\n"
        "uniform vec4 u_Position;\n"
        "out vec2 TexturePos;\n"
        "void main()\n"
        "{\n"
            "gl_Position = aPos + u_Position;\n"
            "TexturePos = aTexturePos;\n"
        "}\0";

    const char* FragmentShader = "#version 330 core\n"
        "layout(location = 0) out vec4 color;\n"
        "in vec2 TexturePos;"
        "uniform vec4 u_color;"
        "uniform sampler2D u_texture;"
        "void main(){\n"
            "color = texture(u_texture, TexturePos) * u_color;\n"
        "}\0";

    DefultShader = CompileShader(VertexShader,FragmentShader);
}

void ClearBackground(Color color) {
    Colorf col = ColorToColorf(color);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(col.r,col.g,col.b,col.a);
}

Texture2D LoadTexture(const char *path) {
    unsigned int textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);

    int width,height,nrChannels;
    unsigned char* data = stbi_load(path,&width,&height,&nrChannels,0);

    if (!data) {
        std::cout<<"Failed To load texture with ID: "<<textureID<<"\n";
        return {0,0,0,0,0,0};
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    vec2 trns = GetSpaceCords(GetScreenWidth()/2 + width,GetScreenHeight()/2 + height);

    vec2 p1 = {0,0};
    vec2 p2 = {0,(float)trns.y};
    vec2 p3 = {(float)trns.x,0};
    vec2 p4 = trns;

    float vertices[] = {
        p3.x,p3.y, 1,1,
        p4.x,p4.y, 1,0,
        p2.x,p2.y, 0,0,
        p1.x,p1.y, 0,1
    };

    float indices[] = {
        0,1,3,
        1,2,3
    };

    unsigned int vbo,vao,ebo;

    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*4,0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*4,(void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    return {textureID,vbo,vao,ebo,height,width};

}

void DrawTexture2D(Texture2D texture,int x,int y,Color color) {
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.ID);
    glUseProgram(DefultShader);

    vec2 position = GetSpaceCords(x,y);

    Colorf col = ColorToColorf(color);

    glUniform4f(glGetUniformLocation(DefultShader,"u_Position"),0,0,0,0);
    glUniform4f(glGetUniformLocation(DefultShader,"u_color"),col.r,col.g,col.b,col.a);

    glUniform1i(glGetUniformLocation(DefultShader,"u_texture"),0);

    glBindVertexArray(texture.vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
