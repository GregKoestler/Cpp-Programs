#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>


using namespace std;

//Function to find the middle of the list for the pivot point
template <typename BidiIter>
BidiIter middle(BidiIter first, BidiIter last)
{
	BidiIter iter1 = first;
	BidiIter iter2 = first;
	BidiIter middleIter;
	
	//have iter1 travers the list once. It increments by 2 every time
	//Iter2 will increment by one and will end up in the middle of the list
	if (first  == last)
		return first;
	
	for( ; iter1 != prev(prev(last)) && iter1 != prev(last); ++iter1)
	{
		++iter2;
		++iter1;
	}
	
	//cout << "\n the middle found is: " << *iter2 <<'\n';
	middleIter = iter2;
	return middleIter;
}

//Quicksort function using partition
template <typename BidiIter>
void quick_sort(BidiIter first, BidiIter last)
{
	//If the list is empty then return
	if(first == last)
		return;	
	
	//find the middle 
	BidiIter middleIter = middle(first, last);
	//cout << "MIDDLE ITER IS: " << *middleIter <<'\n';
	
	
	//swap it with the first element to establish the range and partition (alg4.cxx)
	iter_swap(first, middleIter);
	
	BidiIter newMid = partition(
    	next(first), last,
    	[=](typename BidiIter::value_type const& i) { return i < *first; }
  	);	
	
	if (newMid != first)
		iter_swap(prev(newMid), first);
		
	
	quick_sort(first, prev(newMid)); //recursive call on the first half
	quick_sort(newMid, last); //recursive call on the second half
	
	
}


int main()
{
	string i;
	list<string> mylist;
	
	while(cin >> i)
	{
		mylist.push_back(i);
	}
	
	quick_sort(begin(mylist), end(mylist));
	
	//Display the contents of the list
	for(auto const& elem : mylist)
	{
		cout << elem << '\n';
	}
}