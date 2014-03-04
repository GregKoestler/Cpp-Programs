/*
Greg Koestler
ID: 103400581
Assignment 2A
This is an implementation of a staticly allocated bool array 
*/
#include <cstddef> // For std::size_t, same as #include <stddef.h> in C
#include <limits>  // For std::numeric_limits<T>
#include <cstring> // Equivalent to #include <string.h> in C.
#include <iostream> // For cin/cout
using namespace std;

template <std::size_t N>
struct bool_array
{
public:
	//Type aliasses // same as typedef
	using size_type = std::size_t;
	using value_type = bool;

	//Constructor
	bool_array()
	{
		memset(bits_, 0, MAX);	//Sets all the bits to 0
	}

	//Copy constructor... It has a constant reference to the class type
	bool_array(bool_array const& a)
	{
		memcpy(bits_, a.bits_, MAX);
	}
	
	
	//Copy assignment 
	bool_array& operator =(bool_array const& a)
	{
		memcpy(bits_, a.bits_, MAX);
		return *this;
	}
	
	//Destructor
	~bool_array() = default;
	
	//A size() function for the bool_array
	constexpr size_type size() const
	{
		return N;
	}
	
private:

	//Bit proxy class
	class bit_proxy
	{
	private:
		unsigned char& datum_;
		size_type const offset_;
		
	public:
		bit_proxy() = delete;
		//default copy constructor & assignment...
		bit_proxy(bit_proxy const&) = default;
		bit_proxy& operator =(bit_proxy const&) = default;
		
		//Default move constructor & assignment
		bit_proxy(bit_proxy&&) = default;
		bit_proxy& operator =(bit_proxy&&) =  default;
		
		//Default destructor
		~bit_proxy() = default;
		
		
		bit_proxy(unsigned char& datum, size_type offset) : datum_(datum), offset_(offset)		//after the : is to initialize the variables
		{}
		
		bit_proxy& operator =(bool b)
		{
			unsigned char value = 1;
			value <<= offset_;
			
			if(b == true)
			{
				datum_ |= value;	//set a bit
			
			}else //b is false
			{
				datum_ &= ~value;	//Deselect the bit
			}		
			
			return *this;	//Resturn this object (which is an L-Value)
		}
		
		operator bool() const
		{
			unsigned char value = 1;
			value <<= offset_;
			return (datum_ & value) != 0;
		}
		
	};
	
public:
	bit_proxy operator [](size_type i)
  	{
    	return bit_proxy{ bits_[i / std::numeric_limits<unsigned char>::digits], 
        	i % std::numeric_limits<unsigned char>::digits };
    }
	

private:
	static constexpr auto MAX =
	N / std::numeric_limits<unsigned char>::digits
	+ (N % std::numeric_limits<unsigned char>::digits != 0);
	
	//Array to hold the bool values
	unsigned char bits_[MAX];
};

int main()
{
  using namespace std;

  bool_array<13> test;

  for (unsigned i=0; i != 13; ++i)
    cout << i << ": " << test[i] << '\n';

  for (unsigned i=0; i != 13; ++i)
  {
    cout << i << ": " << test[i] << "; ";
    test[i] = true;
    cout << test[i] << '\n';
  }

  for (unsigned i=0; i != 13; ++i)
    cout << i << ": " << test[i] << '\n';

  for (unsigned i=0; i != 13; ++i)
  {
    cout << i << ": " << test[i] << "; ";
    test[i] = false;
    cout << test[i] << '\n';
  }

  for (unsigned i=0; i != 13; ++i)
    cout << i << ": " << test[i] << '\n';

  cout << "\n\n";
  
  bool_array<13> test2;
  test2 = test;
  
  for (unsigned i=0; i < 13; i+=3)
	test2[i] = true;

  for (unsigned i=0; i != 13; ++i)
    cout << i << ": " << test2[i] << '\n';

  for (unsigned i=0; i < 13; i+=2)
	test2[i] = true;
	
  test2[7] = true;
  for (unsigned i=0; i != 13; ++i)
    cout << i << ": " << test2[i] << '\n';
  
}