#include "List.hpp"

#include <iostream>
#include <iomanip>
#include <string>

#include <cassert>

using namespace std;

template <typename T>
void _rec_list_to_cout(shared_ptr<SLList<T>> const & list)
{
  if (!list->isEmpty())
  {
    cout << setw(2) << list->head();
    _rec_list_to_cout(list->tail());
  }
}

template <typename T>
void list_to_cout(shared_ptr<SLList<T>> const & list)
{
  cout << "List: ["; _rec_list_to_cout(list); cout << "]" << endl;
}

int main()
{
  shared_ptr<SLList<int>> intList(new SLList<int>());
  shared_ptr<SLList<string>> strList(new SLList<string>);

  cout << "Empty lists:" << endl;
  list_to_cout(intList);
  list_to_cout(strList);

  for (size_t i = 0; i < 10; ++i)
  {
    intList->add(i);
    // проверка основных функций доступа к данным
    assert(intList->size() == i + 1);
    assert(intList->get(i) == i);
    assert(intList->head() == 0);
  }

  cout << "Int list:" << endl;
  list_to_cout(intList);

  assert(intList->remove(2));
  assert(!intList->remove(42));
  intList->remove(0);
  intList->remove(9);
  //  После удаления 2,9,0
  list_to_cout(intList);

  // Проверка на получение исключений при недопустимых операциях
  try
  {
    (*intList)[42];
  }
  catch (IndexOutOfRangeException e)
  {
    cout << "Tried to get index " << e._index << " when size is " << e._size << endl; 
  }
  try
  {
    strList->tail();
  }
  catch (EmptyListException e)
  {
    cout << "Tail is not supported for empty lists." << endl;
  }

  // Работа со списком строк
  strList->add("Hello");
  strList->add(",");
  strList->add("World");
  strList->add("!");
  list_to_cout(strList);

  strList->remove("World");
  strList->remove(",");
  list_to_cout(strList);

  // Проверка шаблонных функций
  cout << "Max is: " << listalg::max(intList) << endl;
  cout << "Max string is: " << listalg::max(strList) << endl;


  cout << "Done!" << endl;
  return 0;
}
