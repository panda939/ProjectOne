#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


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
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pwindow))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(pwindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}