#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    printf("Quem tem medo pula fora\n");
  }
}

static unsigned int CompileShader(unsigned int type, const char *source) {
  unsigned int id = glCreateShader(type);
  glShaderSource(id, 1, &source, NULL);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char *message = (char *)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    fprintf(stderr, "Fail to compile %s shader!\n",
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
    fprintf(stderr, "%s\n", message);
    glDeleteShader(id);
    return 0;
  }

  return id;
}

static unsigned int CreateShader(const char *vertexShader,
                                 const char *fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
}

int main(int argc, char **argv) {
  if (!glfwInit()) {
    fprintf(stderr, "Error initializing glfw!\n");
  }

  glfwSetErrorCallback(error_callback);

  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Error creating window\n");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSwapInterval(1);

  float positions[8] = {0.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.1f, 0.0f};

  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

  const char *vertexShader = "#version 330 core\n"
                             "\n"
                             "layout(location = 0) in vec4 position;\n"
                             "\n"
                             "void main()\n"
                             "{\n"
                             "  gl_Position = position;\n"
                             "}\n";
  const char *fragmentShader = "#version 330 core\n"
                               "\n"
                               "layout(location = 0) out vec4 color;\n"
                               "\n"
                               "void main()\n"
                               "{\n"
                               "  color = vec4(1.0, 1.0, 1.0, 1.0);\n"
                               "}\n";

  unsigned int shader = CreateShader(vertexShader, fragmentShader);
  glUseProgram(shader);

  while (!glfwWindowShouldClose(window)) {

    // Render here
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_QUADS, 0, 4);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
