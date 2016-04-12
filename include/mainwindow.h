#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NGLScene.h"
#include "Renderer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  explicit MainWindow(Renderer *renderer, QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *m_ui;
  /// @brief our openGL widget
  NGLScene *m_gl;
  Renderer *renderer;
};

#endif // MAINWINDOW_H
