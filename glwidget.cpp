#include <stdlib.h>
#include "glwidget.h"

#define PI 3.1415926

//generate random number from first to second
int GetRandom(const int& first, const int& second) {
  return qrand() % ((second + 1) - first) + first;
}

GLWidget::GLWidget(const QRect& geom, const int generation_ms, const int min_bubble_size, const int max_bubble_size, const float relative_speed, QGLWidget *parent)
    : QGLWidget(parent) {
  this->setGeometry(geom);
  this->setFixedSize(geom.width(), geom.height());
  window_rect_ = geom;
  generation_ms_ = generation_ms;

  min_bubble_size_ = min_bubble_size;
  max_bubble_size_ = max_bubble_size;

  //is one of sizes is zero or bigger than one fourth of window width then we reset it
  if(min_bubble_size_ == 0 || min_bubble_size_ > window_rect_.width()/4) {
    min_bubble_size_ = 1;
  }
  if(max_bubble_size_ == 0 || max_bubble_size_ > window_rect_.width()/4) {
    max_bubble_size_ = window_rect_.width()/4;
  }

  relative_speed_ = relative_speed;

  //initialize randomization
  QTime time = QTime::currentTime();
  qsrand((uint)time.msec());

  score_ = 0;//start score
}

GLWidget::~GLWidget() {
}

Bubble GLWidget::GenerateBubble() {
  Bubble bub;
  bub.radius_ = GetRandom(min_bubble_size_, max_bubble_size_);
  //stert from outside of the screen
  bub.y_ = -bub.radius_;

  //make bubbles not to cover window sides
  bub.x_ = GetRandom(bub.radius_, window_rect_.width()-bub.radius_);

  //rgb components start from 50 not to be too dark
  bub.color_ = QColor(GetRandom(50,255), GetRandom(50,255), GetRandom(50,255));

  //set speed bigger for smaller bubbles according to relative speed
  bub.speed_= min_speed_ + relative_speed_/(max_bubble_size_-min_bubble_size_)*(max_bubble_size_-bub.radius_);
  return bub;
}

void GLWidget::timerEvent(QTimerEvent * event)
{
  cur_time_ += timer_step_;
  Bubbles::iterator end = bubbles_.end();
  //go through bubbles list and erase those that disappeared from screen
  for(Bubbles::iterator it = bubbles_.begin(); it != end; ++it) {
    it->y_ += it->speed_;
    if(it->y_ > (window_rect_.height() + it->radius_)) {
      bubbles_.Erase(it);
    }
  }

  //generate new bubble when it's time has come
  if(cur_time_>=generation_ms_) {
    Bubble bub = GenerateBubble();
    bubbles_.Add(bub);
    cur_time_ = 0;
  }
  //repaint
  updateGL();
}

void GLWidget::initializeGL() {
  setMouseTracking(true);

  glColor3f(1, 1, 1);
  clear_color_ = Qt::black;
  glPolygonMode(GL_FRONT, GL_FILL);

  //set all window as a viewport
  glViewport(0, 0, window_rect_.width(), window_rect_.height());

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //set gl coordinates to work with them like with window coordinates
  glOrtho(0, window_rect_.width(), window_rect_.height(), 0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);

  cur_time_ = 0;
  startTimer(timer_step_);
}

void GLWidget::paintGL() {
  qglClearColor(clear_color_);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  Bubbles::iterator end = bubbles_.end();
  QColor color;
  //draw all bubbles. later added are drawn over earlier ones
  for(Bubbles::iterator it = bubbles_.begin(); it != end; ++it) {
    color = it->color_;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(color.redF(), color.greenF(), color.blueF());
    for(float angle = 0; angle<2*PI; angle+=PI/36) {
      glVertex2f(it->x_ + sin(angle) * it->radius_, it->y_ + cos(angle) * it->radius_);
    }
    glEnd();
  }

  //draw score with glut
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2i(10, window_rect_.height()-30);
  char s[20];
  itoa(score_, s, 10);
  void * font = GLUT_BITMAP_HELVETICA_18;
  for (int i=0; i<strlen(s); ++i) {
    char c = s[i];
    glutBitmapCharacter(font, c);
  }
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  float x = event->x(), y = event->y();
  Bubbles::reverse_iterator end = bubbles_.rend();
  //go from the end of list because later added elements cover earlier ones
  for(Bubbles::reverse_iterator it = bubbles_.rbegin(); it != end; ++it) {
    //success if distance from mouse to center of bubble is less than it's radius
    if(pow(it->x_-x,2.0)+pow(it->y_-y,2.0) < pow(it->radius_,2.0)) {
      //sore formulae that gives 10 for biggest bubble and increase
      //it's value by score step with each pixel smaller bubble radius
      score_ += 10 + (max_bubble_size_ - it->radius_)*score_step_;
      bubbles_.Erase(it);
      break;
    }
  }
  updateGL();
}
