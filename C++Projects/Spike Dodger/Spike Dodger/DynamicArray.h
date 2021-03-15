#pragma once

// The class is to provide a template dynamic array class that can resize itself.
template <typename T>
class DynamicArray
{
private:
	// The num of current elements in the array
	int elements_num_;

	// The total capacity of the array 
	int array_capacity_;

	// The array pointer
	T* array_;

	inline bool get_is_index_valid(int index) { return 0 <= index && index < elements_num_; }

public:
	// Constructor 
	DynamicArray(int size, T default_value)
		: array_capacity_(size)
		, elements_num_(0)
		, array_(new T[array_capacity_])
	{
	}

	DynamicArray() = default;

	// Destructor
	~DynamicArray() { delete[] array_; }

	// Add an element into the array
	void Add(T element);

	// Get the element at the index
	T Get(int index) { return get_is_index_valid(index) ? array_[index] : NULL; }

	// Remove the element at the index
	void Remove(int index);

	// Operator overloading
	inline T operator[](int index) {return get_is_index_valid(index) ? array_[index] : NULL;}
};

template<typename T>
void DynamicArray<T>::Add(T element)
{
	// If there is any open slot (elements<size)
	if (elements_num_ < array_capacity_)
	{
		array_[elements_num_] = element;
		elements_num_++;
	}
	// If there is no open slot. 
	else
	{
		// Make a new array with double size 
		T* newArray = new T[array_capacity_ * 2];

		// Copy everything from the old array 
		memcpy(newArray, array_, sizeof(T) * array_capacity_);

		// Add the new element in to the new array 
		newArray[elements_num_] = element;

		// Delete the old used memory
		delete[] array_;

		// Set the 1st index of the new array as our array pointer
		array_ = newArray;

		// Update trackers
		array_capacity_ *= 2;

		elements_num_++;
	}
}

template<typename T>
void DynamicArray<T>::Remove(int index)
{
	// Move every element after the element at the index one slot up 
	for (int i = index; i < elements_num_ - 1; ++i)
	{
		array_[i] = array_[i + 1];
	}
	
	// Update the index tracker
	elements_num_--;
}
