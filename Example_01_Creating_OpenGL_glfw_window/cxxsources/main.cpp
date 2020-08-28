#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <iostream>

char ROTATION_AXIS {};
int ROTATION_DIRECTION {}; // ( 0) - No Rotation, (-1) - Anticlockwise, ( 1) - Clockwise

void controls(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(action == GLFW_PRESS){
    std::cout << "Current Axis of Rotation is " << ROTATION_AXIS << std::endl;
    switch(key){
      case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE);
      break;
      case GLFW_KEY_SPACE: ROTATION_DIRECTION = 0;
      break;
      case GLFW_KEY_LEFT: ROTATION_DIRECTION = -1;
      break;
      case GLFW_KEY_RIGHT: ROTATION_DIRECTION = 1;
      break;
      case GLFW_KEY_X: ROTATION_AXIS = 'X';
      break;
      case GLFW_KEY_Y: ROTATION_AXIS = 'Y';
      break;
      case GLFW_KEY_Z: ROTATION_AXIS = 'Z';
      break;
      default: std::cout << "Unknown key Pressed" << std::endl;
    }
    std::cout << "Axis of Rotation is now " << ROTATION_AXIS << '\n';
  }
}

GLFWwindow* initWindow(const int resX, const int resY)
{
  ROTATION_AXIS = 'X';
  ROTATION_DIRECTION = 0;

  if(!glfwInit())
  {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return NULL;
  }
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

  // Open a window and create its OpenGL context
  GLFWwindow* window = glfwCreateWindow(resX, resY, "SIMULANDA", NULL, NULL);
  glfwSetWindowSizeLimits(window, resX, resY, GLFW_DONT_CARE, GLFW_DONT_CARE);

  if(window == NULL)
  {
    fprintf(stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, controls);

  // Get info of GPU and supported OpenGL version
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

  glEnable(GL_DEPTH_TEST); // Depth Testing
  glDepthFunc(GL_LEQUAL);
  glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  return window;
}

void drawCube()
{
  GLfloat vertices[] =
  {
    -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
    1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
    -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
    -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
    -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
    -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
  };

  GLfloat colors[] =
  {
    0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
    1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
    0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
    0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
    0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
    0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
  };

  static float x_angle = 0;
  static float y_angle = 0;
  static float z_angle = 0;

  //attempt to rotate cube
  glRotatef(x_angle, 1, 0, 0);
  glRotatef(y_angle, 0, 1, 0);
  glRotatef(z_angle, 0, 0, 1);

  /* We have a color array and a vertex array */
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glColorPointer(3, GL_FLOAT, 0, colors);

  /* Send data : 24 vertices */
  glDrawArrays(GL_QUADS, 0, 24);

  /* Cleanup states */
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  
  switch (ROTATION_AXIS) {
    case 'X': x_angle = x_angle+ROTATION_DIRECTION*1;
    break;
    case 'Y': y_angle = y_angle+ROTATION_DIRECTION*1;
    break;
    case 'Z': z_angle = z_angle+ROTATION_DIRECTION*1;
    break;
  }
  std::cout << "Angle: " << x_angle << ", " << y_angle << ", " << z_angle << std::endl;
}

void display( GLFWwindow* window )
{
  while(!glfwWindowShouldClose(window))
  {
    // Scale to window size
    GLint windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    // Draw stuff
    glClearColor(0.0, 0.8, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    gluPerspective( 60, (double)windowWidth / (double)windowHeight, 0.1, 100 );

    glMatrixMode(GL_MODELVIEW_MATRIX);
    glTranslatef(0,0,-5);

    drawCube();

    // Update Screen
    glfwSwapBuffers(window);

    // Check for any input, or window movement
    glfwPollEvents();
  }
}

int main(int argc, char** argv)
{
  GLFWwindow* window = initWindow(1024, 620);
  if(window != NULL)
  {
    display(window);
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
