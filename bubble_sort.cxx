#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

template <typename BidiIter>
void bubble_sort(BidiIter first, BidiIter last) 
{
	bool swapped = false;
	BidiIter i = first;

	if (i != last)
    	++i;  // There is MORE than 0 elements!
  	if (i == last)
    	return; // We're done, only one element!


	// We know we have at least 2 elements!
  	do
  	{
  		swapped = false;
  		
  		//Remember that i = next(first) means that i is pointing to the second element
  		//Need this to be able to compair i with the element before i 
    	for (i = next(first); i != last; ++i)
    	{

			//If the previous value is less the the current then, swap the values the iterators point to
	    	if (*prev(i) > *i)
        	{
     	   		iter_swap(prev(i), i);	//Perform swap
           		swapped = true;  
        	}

	    }
  	}
  	while (swapped);
}

int main() 
{	
	string i;
	list<string> mylist;
	
	while(cin >> i) {
		mylist.push_back(i);
	}
	
	//Call the bubble sort method
	bubble_sort(begin(mylist), end(mylist));
	
	// We can also call the method like this without the global functions begin() and end()
	//bubble_sort(mylist.begin(), mylist.end());
	
	//For loop using iterators
	for ( list<string>::iterator i=mylist.begin(), 
    	iEnd=mylist.end();
    	i != iEnd;
    	++i)
  {
    cout << *i << '\n';
  }
	return 0;
}