#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


GLfloat point[] = {  // точки (триугольник)
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f

};
GLfloat colors[] = {  // цвет (RGB)
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f

};

/* Шейдер */

const char* vertex_shader =   // вертексный 
"#version 460/n" // версия шейдера 
"layout(location = 0) in vec3 vertex_position;" // входные данные (точки) 
"layout(location = 1) in vec3 vertex_color;" // воходные данные (цвет)
"out vec3 color;"
"void main() {"  // интерполяция 
"   color = vertex_color;"
/* vec4 - четырехкомпонентный, добовляем 1.0 - параметр перспективы */
"   gl_Position = vec4(vertex_position, 1.0);" // позиция вертекса на выход. 
"}";

const char* fragment_shader =  // фрагментный 
"#version 460/n"
"in vec3 color;"
"out vec4 frag_color;" //выходной параметр  4-й это альфа канал 
"void main() {"
/* vec4 - четырехкомпонентный, добовляем 1.0 - параметр прозрачности */
"   frag_color = vec4(color, 1.0);"
"}";

/*====================================================================================*/

int g_windowSizeX = 640;
int g_windowSizeY = 480;

void glfw_windowSizeCallback(GLFWwindow* pwindow, int width, int height) { // отслеживания изминение окна
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);

}
void glfw_KeyCallback(GLFWwindow* pwindow, int key, int scancode, int action, int mode) { // отслеживание клавиши ESC
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pwindow, GL_TRUE);  // закрытие окна 
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

    glfwSetWindowSizeCallback(pwindow, glfw_windowSizeCallback); // вызов изминеня окна
    glfwSetKeyCallback(pwindow, glfw_KeyCallback); // вызов нажатия клавиши "ESC:

    /* Make the window's context current */
    glfwMakeContextCurrent(pwindow);

    if (!gladLoadGL())
    {
      cout << "Can't load GLAD!"  << endl; 
      return -1;
    }
    cout << "Render " << glGetString(GL_RENDERER) << endl; // Инфо о GPU
    cout << "OpenGL Version" << glGetString(GL_VERSION) << endl; //Инфо о версии OpenGL и версии дрйвера
   
   glClearColor(0, 1, 0, 1);

   /* Коипиляция шейдеров */
  
   GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);  // индификатор вертексного шейдера
   glShaderSource(vertexShader, 1, &vertex_shader,nullptr); // исходный код щейдера
   glCompileShader(vertexShader); // компиляция вертексного шейдера

   GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);  // индификатор фрагментного шейдера
   glShaderSource(fragmentShader, 1, &fragment_shader, nullptr); // исходный код щейдера
   glCompileShader(fragmentShader); // компиляция фрагментного шейдера

   GLuint shader_program = glCreateProgram(); //  создание шейдерной программы
   glAttachShader(shader_program, vertexShader); // Присоединяет вертексный шейдер к программному объекту
   glAttachShader(shader_program, fragmentShader); // Присоединяет фрагментный шейдер к программному объекту
   glLinkProgram(shader_program); // Линкует 

   /*после линковки удаляем*/

   glDeleteShader(vertexShader); // удаление вертексного шейдера
   glDeleteShader(fragmentShader); // фрагментного шейдера

   /*====================================================================================*/

   /* Передача в GPU - Vertex buffer object */

   GLuint points_vbo = 0; // идификатор (точек) 
   glGenBuffers(1, &points_vbo); // генирация одного буфера
   glBindBuffer(GL_ARRAY_BUFFER, points_vbo); // подключение буфера 
   glBufferData(GL_ARRAY_BUFFER, sizeof(point),point,GL_STATIC_DRAW); // Передача позиций текущего буфера из ОЗУ

   GLuint colors_vbo = 0; // идификатор (цвета) Vertex buffer
   glGenBuffers(1, &colors_vbo); // генирация одного буфера
   glBindBuffer(GL_ARRAY_BUFFER, colors_vbo); // подключение буфера 
   glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW); // Передача позиций текущего буфера из ОЗУ

   /*====================================================================================*/


     /*Оброботка GPU - Vertex array object*/

   GLuint vao = 0;
   glGenVertexArrays(1, &vao); // идификатор массива
   glBindVertexArray(vao); // генирация одного массива

   glEnableVertexAttribArray(0); // включение 0-й вертекс позиции в шейдере
   glBindBuffer(GL_ARRAY_BUFFER, points_vbo); // подключение буфера 
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // берём данные для текущего буфера points_vbo
   
   glEnableVertexAttribArray(1); // включение 0-й вертекс позиции в шейдере
   glBindBuffer(GL_ARRAY_BUFFER, colors_vbo); // подключение буфера 
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // берём данные для текущего буфера colors_vbo



   /*====================================================================================*/

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pwindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program); // подключение шейдерной программы 
        glBindVertexArray(vao); //  генирация массива (избыточная)
        glDrawArrays(GL_TRIANGLES, 0, 3); // Отрисовка 


        /* Swap front and back buffers */
        glfwSwapBuffers(pwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}