#ifndef BUBBLES_H
#define BUBBLES_H

#include <QtGui>
#include <list>

//struct with each bubble information
struct Bubble {
  Bubble() {
    x_ = y_ = radius_ = 0;
    color_ = QColor("Black");
    speed_ = 0;
  }

  float x_, y_;
  int radius_;
  QColor color_;

  float speed_;
};

//class to work with list of bubbles
class Bubbles {
public:
  //iterator with functionality close to std::list<>::iterator
  class iterator {
  public:
    iterator(std::list<Bubble>::iterator it) {
      it_ = it;
    }
    iterator(const iterator& bubble_it) {
      it_ = bubble_it.it_;
    }
    iterator & operator = (iterator const &) {
      return *this;
    }
    bool operator==(const iterator& right) {
        return it_ == right.it_;
    }
    bool operator!=(const iterator& right) {
      return it_ != right.it_;
    }
    iterator & operator ++() {
      ++it_;
      return *this;
    }
    const iterator operator ++(int) {
      iterator tmp(*this);
      ++it_;
      return tmp;
    }
    Bubble& operator*() const
    {
      return *it_;
    }
    Bubble* operator->() const
    {
      return &(*it_);
    }
    inline std::list<Bubble>::iterator GetListIterator() {
      return it_;
    }
    inline void SetListIterator(std::list<Bubble>::iterator list_it) {
      it_ = list_it;
    }
  private:
    std::list<Bubble>::iterator it_;
  };
  //reverse iterator to go through bubbles list from it's end
  class reverse_iterator {
    public:
      reverse_iterator(std::list<Bubble>::reverse_iterator it) {
        it_ = it;
      }
      reverse_iterator(const reverse_iterator& bubble_it) {
        it_ = bubble_it.it_;
      }
      reverse_iterator & operator = (reverse_iterator const &) {
        return *this;
      }
      bool operator==(const reverse_iterator& right) {
          return it_ == right.it_;
      }
      bool operator!=(const reverse_iterator& right) {
        return it_ != right.it_;
      }
      reverse_iterator & operator ++() {
        ++it_;
        return *this;
      }
      const reverse_iterator operator ++(int) {
        reverse_iterator tmp(*this);
        ++it_;
        return tmp;
      }
      Bubble& operator*() const
      {
        return *it_;
      }
      Bubble* operator->() const
      {
        return &(*it_);
      }
      inline std::list<Bubble>::reverse_iterator GetListReverseIterator() {
        return it_;
      }
      inline void SetListReverseIterator(std::list<Bubble>::reverse_iterator list_it) {
        it_ = list_it;
      }
    private:
      std::list<Bubble>::reverse_iterator it_;
    };

  //return begin and end for both kinds of iterators
  iterator begin() {
    return all_bubbles_.begin();
  }
  iterator end() {
    return all_bubbles_.end();
  }

  reverse_iterator rbegin() {
    return all_bubbles_.rbegin();
  }
  reverse_iterator rend() {
    return all_bubbles_.rend();
  }

  Bubbles();
  virtual ~Bubbles();

  //add and erase one element from bubbles list
  void Add(Bubble bub);
  void Erase(iterator& it);
  void Erase(reverse_iterator& it);
private:
  std::list<Bubble> all_bubbles_;
};

#endif // BUBBLES_H
