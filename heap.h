#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> container;
  int m;
  PComparator comp;
  void heapifyUp(size_t idx);
  void heapifyDown(size_t idx);

  void swap(T &a, T &b);
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m(m), comp(c) {
  if(m < 2) {
    throw std::invalid_argument("Heap must be > 2");
  }
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
  return container.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return container.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::swap(T &a, T&b) {
  T temp = a;
  a = b;
  b = temp;
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::underflow_error("Empty Heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return container[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::underflow_error("Empty Heap");
  }
  container[0] = container.back();
  container.pop_back();
  if(!empty()){
    heapifyDown(0);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  container.push_back(item);
  heapifyUp(container.size() - 1);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyUp(size_t idx)
{
  while(idx > 0){
    size_t parent = (idx - 1) / m;
    if(comp(container[idx], container[parent])){
      swap(container[idx], container[parent]);
        idx = parent;
      } else {
        break;
      }
    }
  }

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapifyDown(size_t idx)
{
  while(true) {
    size_t bestChild = idx;
    for(int j = 1; j <= m; j++){
      size_t child = m * idx + j;
      if(child < container.size() && comp(container[child], container[bestChild])){
        bestChild = child;
      }
    }
    if(bestChild != idx) {
      swap(container[idx], container[bestChild]);
      idx = bestChild;
    } else {
      break;
    }
  }
}

template<typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {

}

#endif

