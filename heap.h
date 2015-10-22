#ifndef HEAP_H																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																		
#define HEAP_H																																																																									z
#include <stdexcept>
#include <vector>

template <typename T, typename Comparator >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c);

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
  std::vector<T>heap;
  Comparator c;
  int m;
  void trickleUp(int loc);
  void heapify(int loc);


};

template <typename T, typename Comparator >
Heap<T,Comparator>::Heap(int m, Comparator c)
{
	this->m = m;
	this->c = c;
}

template <typename T, typename Comparator >
Heap<T,Comparator>::~Heap()
{

}

template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const
{
	return heap.empty();
}

// Add implementation of member functions here


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
	return heap.front();  	

  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item)
{

	heap.push_back(item);
	trickleUp(heap.size()-1);
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::trickleUp(int loc)
{
	int location = loc;
	int parent = ((loc-1)/m);
	while(parent >= 0 && c(heap[location],heap[parent]))
	{
		std::swap(heap[parent],heap[location]);
		location = parent;
		parent = ((location-1)/m);
	}
}
// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  else
  {
  	heap[0] = heap.back();
  	heap.pop_back();
  	heapify(0);
  }


}

template <typename T, typename Comparator>
void Heap<T,Comparator>::heapify(int loc)
{
	//check if it's a leaf
	if(loc*m+1 > heap.size())
	{
		return;
	}
	//set left child as smallerchild
	int smallerchild = loc*m + 1;
	//declare otherchild
	int otherchild = smallerchild;
	for(int i = 1; i<m; i++)
	{
		//increment by 1
		otherchild++;
		//checking
		if(otherchild < heap.size())
		{
			if(c(heap[otherchild],heap[smallerchild]))
			{
				smallerchild = otherchild;
			}
		}
	}
	if(c(heap[smallerchild],heap[loc]))
	{
		std::swap(heap[loc],heap[smallerchild]);
		heapify(smallerchild);
	}

}
#endif

