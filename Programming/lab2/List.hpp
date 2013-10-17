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
};

class EmptyListException
{
  // just simple for head and tail calls
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

  T const & head() const  override
  {
    return _head->_data;
  }

  size_t add(T const & item)
  {
    nodeptr current = _head;
    nodeptr prev = NULL;
    nodeptr node(new Node(item));

    while (current)
    {
      prev = current;
      current = current->_next;
    }

    if (prev)
      prev->_next = node;
    else
      _head = node;
    ++_size;

    return 0;
  }

  bool remove(T const & item) override
  {
    nodeptr current = _head;
    nodeptr prev    = NULL;

    bool found = false;
    while (!(found = current->_data == item)
	   && current->_next)
    {
      prev = current;
      current = current->_next;
    }

    if (found)
    {
      if (prev) // not head
	prev->_next = current->_next;
      else // item is head
	_head = current->_next;
      --_size;

      return true;
    }
    return false;
  }

  T const & operator[](size_t index) const
  {
    if (index > _size)
      throw IndexOutOfRangeException(index, _size);

    if (index > 0)
      return (*tail())[index - 1];
    else
      return head();
  }

  T & operator[](size_t index)
  {
    if (index > _size)
      throw IndexOutOfRangeException(index, _size);

    if (index > 0)
      return (*tail())[index - 1];
    else
      return head();
  }

  shared_ptr<SLList<T>> const tail() const
  {
    if (isEmpty()) throw EmptyListException();
    return shared_ptr<SLList<T>>(new SLList(_head->_next, _size-1));
  }

  shared_ptr<SLList<T>> tail()
  {
    if (isEmpty()) throw EmptyListException();
    return shared_ptr<SLList<T>>(new SLList(_head->_next, _size-1));
  }
};

namespace listalg
{
  template <typename T>
  T _max(T max, shared_ptr<SLList<T>> const & list)
  {
    if (list->isEmpty())
      return max;
    else return _max(max > list->head() ? max : list->head(), list->tail());
  }

  template <typename T>
  T max(shared_ptr<SLList<T>> const & list)
  {
    return _max(list->head(), list->tail());
  }
}
