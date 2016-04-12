#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);
  m_gl = new NGLScene(this);
  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,1,1);



}

MainWindow::MainWindow(Renderer* renderer, QWidget *parent) :
  QMainWindow(parent),
  m_ui(new Ui::MainWindow)
{

  m_ui->setupUi(this);
  this-> renderer = renderer;
  m_gl = new NGLScene(renderer, this);
  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,2);

  //......................................................
  connect(m_ui->SaveImageBoolean,SIGNAL(toggled(bool)),m_gl,SLOT(togglesave(bool)));
  connect(m_ui->m_RenderButton,SIGNAL(clicked()),m_gl,SLOT(renderbutton()));
}

MainWindow::~MainWindow()
{
  delete m_ui;
}
