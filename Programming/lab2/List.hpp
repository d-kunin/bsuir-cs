#include <stdlib.h>
#include <memory>

using std::shared_ptr;

template <typename T>
class List
{

public:
  virtual ~List() {};

  virtual T const & head() const = 0;
  virtual T & head() = 0;

  virtual size_t size() const = 0;
  virtual bool   isEmpty() const = 0;

  virtual size_t add(T const & item) = 0;
  virtual bool   remove(T const & item) = 0;

  virtual T const & get(size_t index) const = 0;
  virtual T &       get(size_t index) = 0;
};

class EmptyListException
{
  // исключение на случай вызова head, tail для пустого списка
};

class IndexOutOfRangeException
{
public:
  size_t _index;
  size_t _size;

  IndexOutOfRangeException(size_t index, size_t size)
    : _index(index), _size(size) {}
};

template <typename T>
class SLLNode
{
public:
  T _data;
  shared_ptr<SLLNode<T>>  _next;

  SLLNode()
    : _next(NULL) {}

  SLLNode(T const & item)
    : _data(item), _next(NULL) {}

  SLLNode(T const & item, shared_ptr<SLLNode> const & next)
    : _data(item), _next(next) {}
};

template <typename T>
class SLList : public List<T>
{
private:
  typedef SLLNode<T> Node;
  typedef shared_ptr<Node> nodeptr;
  typedef shared_ptr<SLList<T>> listptr;

  nodeptr _head;
  size_t _size;

  SLList(nodeptr const & head, size_t size)
    : _head(head), _size(size) {}

public:
  SLList()
    : _head(NULL), _size(0) {}

  bool isEmpty() const override  { return _head.get() == NULL; }
  size_t  size() const override  { return _size; }

  T & head() override
  {
    return _head->_data;
  }

  T const & head() const override
  {
    if (isEmpty())
      throw EmptyListException();

    return _head->_data;
  }

  size_t add(T const & item)
  {
    if (isEmpty())
    {
      _head.reset(new Node(item));
       return ++_size; 
    }

    nodeptr current = _head; 
    while (current->_next)
      current = current->_next;

    current->_next = nodeptr(new Node(item));
    return ++_size;
  }

  bool remove(T const & item) override
  {
    if (isEmpty())
      return false;

    if (head() == item)
    {
      _head = _head->_next;
       --_size;
       return true;
    }

    nodeptr current = _head;
    while (current->_next && current->_next->_data != item)
      current = current->_next;
    
    if (current->_next)
    {
       current->_next = current->_next->_next;
      --_size;
      return true;
    }

    return false;
  }

  T & get(size_t index) override
  {
    if (index >= _size)
      throw IndexOutOfRangeException(index, _size);

    nodeptr node = _head;
    for (size_t step = 0; step < index; ++step, node = node->_next);

    return node->_data;
  }

  T const & get(size_t index) const override 
  {
    if (index >= _size)
      throw IndexOutOfRangeException(index, _size);

    nodeptr node = _head;
    for (size_t step = 0; step < index; ++step, node = node->_next);

    return node->_data;
  }

  T const & operator[](size_t index) const
  {
    if (index >= _size)
      throw IndexOutOfRangeException(index, _size);

    if (index > 0)
      return (*tail())[index - 1];
    else
      return head();
  }

  T & operator[](size_t index)
  {
    if (index >= _size)
      throw IndexOutOfRangeException(index, _size);

    if (index > 0)
      return (*tail())[index - 1];
    else
      return head();
  }

  listptr const tail() const
  {
    if (isEmpty()) 
      throw EmptyListException();
    return new listptr(new SLList(_head->_next, _size-1));
  }

  listptr tail()
  {
    if (isEmpty()) 
      throw EmptyListException();
    return listptr(new SLList(_head->_next, _size-1));
  }
};

namespace listalg
{
  template <typename T>
  T rec_max(T max, shared_ptr<SLList<T>> const & list)
  {
    if (list->isEmpty())
      return max;
    else return rec_max(max > list->head() ? max : list->head(), list->tail());
  }

  template <typename T>
  T max(shared_ptr<SLList<T>> const & list)
  {
    return rec_max(list->head(), list->tail());
  }
}
