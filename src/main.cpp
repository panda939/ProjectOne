#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


GLfloat point[] = {  // ����� (�����������)
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f

};
GLfloat colors[] = {  // ���� (RGB)
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f

};

/* ������ */

const char* vertex_shader =   // ���������� 
"#version 460/n" // ������ ������� 
"layout(location = 0) in vec3 vertex_position;" // ������� ������ (�����) 
"layout(location = 1) in vec3 vertex_color;" // �������� ������ (����)
"out vec3 color;"
"void main() {"  // ������������ 
"   color = vertex_color;"
/* vec4 - �������������������, ��������� 1.0 - �������� ����������� */
"   gl_Position = vec4(vertex_position, 1.0);" // ������� �������� �� �����. 
"}";

const char* fragment_shader =  // ����������� 
"#version 460/n"
"in vec3 color;"
"out vec4 frag_color;" //�������� ��������  4-� ��� ����� ����� 
"void main() {"
/* vec4 - �������������������, ��������� 1.0 - �������� ������������ */
"   frag_color = vec4(color, 1.0);"
"}";

/*====================================================================================*/

int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfw_windowSizeCallback(GLFWwindow* pwindow, int width, int height) { // ������������ ��������� ����
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);

}
void glfw_KeyCallback(GLFWwindow* pwindow, int key, int scancode, int action, int mode) { // ������������ ������� ESC
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pwindow, GL_TRUE);  // �������� ���� 
  }
}

int main(void)
{
    GLFWwindow* pwindow;

    /* Initialize the library */
    if (!glfwInit()) {
        cout << "glfw init failend!" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    pwindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Hello World", NULL, NULL);
    if (!pwindow)
    {
        cout << "GLFW CreateWindow failend!" << endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pwindow, glfw_windowSizeCallback); // ����� �������� ����
    glfwSetKeyCallback(pwindow, glfw_KeyCallback); // ����� ������� ������� "ESC:

    /* Make the window's context current */
    glfwMakeContextCurrent(pwindow);

    if (!gladLoadGL())
    {
      cout << "Can't load GLAD!"  << endl; 
      return -1;
    }
    cout << "Render " << glGetString(GL_RENDERER) << endl; // ���� � GPU
    cout << "OpenGL Version" << glGetString(GL_VERSION) << endl; //���� � ������ OpenGL � ������ �������
   
   glClearColor(0, 1, 0, 1);

   /* ���������� �������� */
  
   GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);  // ����������� ����������� �������
   glShaderSource(vertexShader, 1, &vertex_shader,nullptr); // �������� ��� �������
   glCompileShader(vertexShader); // ���������� ����������� �������

   GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);  // ����������� ������������ �������
   glShaderSource(fragmentShader, 1, &fragment_shader, nullptr); // �������� ��� �������
   glCompileShader(fragmentShader); // ���������� ������������ �������

   GLuint shader_program = glCreateProgram(); //  �������� ��������� ���������
   glAttachShader(shader_program, vertexShader); // ������������ ���������� ������ � ������������ �������
   glAttachShader(shader_program, fragmentShader); // ������������ ����������� ������ � ������������ �������
   glLinkProgram(shader_program); // ������� 

   /*����� �������� �������*/

   glDeleteShader(vertexShader); // �������� ����������� �������
   glDeleteShader(fragmentShader); // ������������ �������

   /*====================================================================================*/

   /* �������� � GPU - Vertex buffer object */

   GLuint points_vbo = 0; // ���������� (�����) 
   glGenBuffers(1, &points_vbo); // ��������� ������ ������
   glBindBuffer(GL_ARRAY_BUFFER, points_vbo); // ����������� ������ 
   glBufferData(GL_ARRAY_BUFFER, sizeof(point),point,GL_STATIC_DRAW); // �������� ������� �������� ������ �� ���

   GLuint colors_vbo = 0; // ���������� (�����) Vertex buffer
   glGenBuffers(1, &colors_vbo); // ��������� ������ ������
   glBindBuffer(GL_ARRAY_BUFFER, colors_vbo); // ����������� ������ 
   glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW); // �������� ������� �������� ������ �� ���

   /*====================================================================================*/


     /*��������� GPU - Vertex array object*/

   GLuint vao = 0;
   glGenVertexArrays(1, &vao); // ���������� �������
   glBindVertexArray(vao); // ��������� ������ �������

   glEnableVertexAttribArray(0); // ��������� 0-� ������� ������� � �������
   glBindBuffer(GL_ARRAY_BUFFER, points_vbo); // ����������� ������ 
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // ���� ������ ��� �������� ������ points_vbo
   
   glEnableVertexAttribArray(1); // ��������� 0-� ������� ������� � �������
   glBindBuffer(GL_ARRAY_BUFFER, colors_vbo); // ����������� ������ 
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // ���� ������ ��� �������� ������ colors_vbo



   /*====================================================================================*/

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pwindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program); // ����������� ��������� ��������� 
        glBindVertexArray(vao); //  ��������� ������� (����������)
        glDrawArrays(GL_TRIANGLES, 0, 3); // ��������� 


        /* Swap front and back buffers */
        glfwSwapBuffers(pwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}