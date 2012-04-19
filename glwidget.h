#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtGui>
#include <QtOpenGL/QtOpenGL>
#include "glut.h"

#include "bubbles.h"

static const int timer_step_ = 40; //step in ms when circles move
static const float min_speed_ = 50;//speed of biggest bubble in pixels per second(lowest)
//score step applies to the score formulae used in this game
static const int score_step_ = 5;

class GLWidget : public QGLWidget {
  Q_OBJECT

public:
  //give most of parameters of game on widget initialization
  GLWidget(const QRect& geom, const int generation_ms, const int min_bubble_size = 0, const int max_bubble_size = 0, const float relative_speed = 1.0, QGLWidget *parent = 0);
  virtual ~GLWidget();
protected:
  virtual void initializeGL();
  virtual void paintGL();
  virtual void mousePressEvent(QMouseEvent *event);
  void timerEvent(QTimerEvent *);

  //generate new bubble randomly
  virtual Bubble GenerateBubble();

  inline int GetMinBubbleSize() { return min_bubble_size_; }
  inline int GetMaxBubbleSize() { return max_bubble_size_; }
  inline int GetGenerationMs() { return generation_ms_; }
  inline int GetRelativeSpeed() { return relative_speed_; }
  inline int GetTimerStep() { return timer_step_; }
private:
  QColor clear_color_;
  QRect window_rect_;
  Bubbles bubbles_;
  int min_bubble_size_, max_bubble_size_;
  int generation_ms_;
  float relative_speed_; //speed difference between smallest bubble and biggest in pixels per second

  int cur_time_;//time from last baloon added
  QTime timer;//timer for counting milliseconds from initialization of application

  int score_;

  bool mouse_clicked_;
  QPoint click_position_;
};

#endif // GLWIDGET_H
