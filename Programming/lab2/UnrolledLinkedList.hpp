#include <stdlib.h>

namespace dk
{

  template <class T, size_t capacity>
  class Node
  {
  private:
    Node<T, capacity> * _next;
    size_t _size;
    T _data[capacity];

  public:
    size_t Size() { return _size; }
    size_t Capacity() { return capacity; }
    Node<T, capacity> * Next() { return _next; }
    void CreateNext() { _next = new Node<T, capacity>(); }

    Node()
      : _next(NULL)
    {}

    ~Node()
    {
      if (_next)
	delete _next;
      _next = NULL;
    }
  };

  template <class T, size_t nodeCapacity>
  class UnrolledLinkedList
  {
  private:
    Node<T, nodeCapacity> * _head;
    size_t _size;
    size_t _capacity;

  public:

    UnrolledLinkedList()
    {
      _head = new Node<T, nodeCapacity>();
      _size = 0;
      _capacity = nodeCapacity;
    }

    size_t Add(T const & item);
    bool Remove(T const & item);

    T const & Get(size_t index) const;
    T & Get(size_t index);

    void Insert(size_t position, T const & item);
    bool RemoveAt(size_t position);

  private:
    bool HasSpace() { return _size < _capacity; }
    // Adds more space
    bool EnsureCapacity()
    {
      GetNodeForIndex(_capacity - 1)->CreateNext();
      _capacity += nodeCapacity;
    }
    // Reduces number of nodes
    bool Shrink()
    {
      delete GetNodeForIndex(_size - 1)->Next();
      // TODO: change capacity
    }

    Node<T, nodeCapacity> * GetNodeForIndex(size_t index)
    {
      size_t const nodeOrder = index/nodeCapacity;

      Node<T, nodeCapacity> * node = _head;
      for (size_t nodeIndex = 0; nodeIndex != nodeOrder; ++nodeIndex)
	node = node->Next();

      return node;
    }

    size_t NodeIndex(size_t index)
    {
      return index % nodeCapacity;
    }
  };


}
