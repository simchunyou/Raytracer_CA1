#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>

#include <ngl/Vec3.h>
#include <vector>
#include <ngl/Util.h>
#include <ngl/ShaderLib.h>
#include <GL/glut.h>
#include "Renderer.h"

NGLScene::NGLScene(QWidget *_parent ) : QOpenGLWidget(_parent )
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  //setTitle("CYrenderer");
  setFocus();
  this -> resize(_parent->size());
}

NGLScene::NGLScene(Renderer* renderer, QWidget *_parent) : QOpenGLWidget(_parent )
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  //setTitle("CYrenderer");
  setFocus();
  this -> renderer = renderer;
  this -> resize(_parent->size());

  //.........................................
  savemode = renderer->getsaveimage();
}

NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
  glDeleteTextures(1,&m_textureName);
}

void NGLScene::resizeGL(QResizeEvent *_event)
{
  m_width=_event->size().width()*devicePixelRatio();
  m_height=_event->size().height()*devicePixelRatio();
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();
}

void NGLScene::generateTexture()
{
  /*QImage image;
  bool loaded=image.load("test9.jpg");
  if(loaded == true)
  {
    int width=image.width();
    int height=image.height();

    unsigned char *data = new unsigned char[ width*height*3];
    unsigned int index=0;
    QRgb colour;
    for( int y=0; y<height; ++y)
    {
      for( int x=0; x<width; ++x)
      {
        colour=image.pixel(x,y);

        data[index++]=qRed(colour);
        data[index++]=qGreen(colour);
        data[index++]=qBlue(colour);
      }
    }*/

  int width=renderer->image.width();
  int height=renderer->image.height();
  unsigned char *data = new unsigned char[width*height*3];
  unsigned int index=0;
  QRgb colour;
  for(int y = 0; y <height; ++y)
  {
    for(int x = 0; x<width; ++x)
    {
      colour=renderer->image.pixel(x,y);

      data[index++]=qRed(colour);
      data[index++]=qGreen(colour);
      data[index++]=qBlue(colour);
    }
  }

  glGenTextures(1,&m_textureName);
  glBindTexture(GL_TEXTURE_2D,m_textureName);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);

  //glGenerateMipmap(GL_TEXTURE_2D); //  Allocate the mipmaps
  //}
}


void NGLScene::createScreen()
{
  GLfloat vertices[] =
  { -1,-1,0,   //4
    -1,1,0,    //1
    1,-1,0,   //3
    1,-1,0,   //5
    1,1,0,    //2
    -1,1,0     //6
  };

  GLfloat texture[] =
  { 0,1,    //4
    0,0,    //1
    1,1,    //3
    1,1,    //5
    1,0,    //2
    0,0     //6
  };


  //Create a vertex array object
  glGenVertexArrays(1, &m_vaoID);

  //Making the vao active
  glBindVertexArray(m_vaoID);

  //Generate 2 VBOs
  GLuint vboID[2];
  glGenBuffers(2, &vboID[0]);
  //Binding array buffer to the first one
  glBindBuffer(GL_ARRAY_BUFFER,vboID[0]);
  //Copy data over
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  //Now we bind vertex attrib pointer for this object
  glVertexAttribPointer(0,3,GL_FLOAT,false,0,0);
  glEnableVertexAttribArray(0);

  //Binding array buffer to the second one
  glBindBuffer(GL_ARRAY_BUFFER,vboID[1]);
  //Copy data over
  glBufferData(GL_ARRAY_BUFFER, sizeof(texture)*sizeof(GLfloat), texture, GL_STATIC_DRAW);
  //Now we bind vertex attrib pointer for this object
  glVertexAttribPointer(1,2,GL_FLOAT,false,0,0);
  glEnableVertexAttribArray(1);
  //Turn bind vertex array off
  //glBindVertexArray(0);
}

void NGLScene::createShader()
{

  /*
   * Assigning shaders
   * */
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader->createShaderProgram("Render");
  //create shaders
  shader->attachShader("RenderVertex", ngl::ShaderType::VERTEX);
  shader->attachShader("RenderFragment",ngl::ShaderType::FRAGMENT);
  //load source
  shader->loadShaderSource("RenderVertex", "shaders/RenderVertex.glsl");
  shader->loadShaderSource("RenderFragment","shaders/RenderFragment.glsl");
  //compile
  shader->compileShader("RenderVertex");
  shader->compileShader("RenderFragment");
  //Attach shaders to program
  shader->attachShaderToProgram("Render","RenderVertex");
  shader->attachShaderToProgram("Render","RenderFragment");
  //link
  shader->linkProgramObject("Render");
  shader->use("Render");

}

void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);


  createShader();
  createScreen();


}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_width,m_height);

  //Check for change in render settings from UI
  if(savemode != renderer->getsaveimage())
  {
    renderer->setSaveImage(savemode);
  }

  generateTexture();
  //Set Values for window scaling
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader->use("Render");
  //Bind back vertex array object
  glBindVertexArray(m_vaoID);
  glBindTexture(GL_TEXTURE_2D,m_textureName);
  glDrawArrays(GL_TRIANGLES,0,6);

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent (QMouseEvent * _event)
{

}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent ( QMouseEvent * _event)
{

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent ( QMouseEvent * _event )
{

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent(QWheelEvent *_event)
{

}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break; //Wireframe mode
  case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break; //Shaded mode

  default : break;
  }
  // finally update the GLWindow and re-draw

    update();

}

//----------------------------------------------------------------------------------------------------------------------
//public slots
  void NGLScene::togglesave(bool _mode)
  {
    savemode = _mode;
    update();
  }

  void NGLScene::renderbutton()
  {
    renderer->render();
    update();
  }
