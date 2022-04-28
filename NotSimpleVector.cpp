#pragma once
#include "NotSimpleVector.h"

template <typename T>
using iterator = typename NotSimpleVector<T>::NotSimpleIterator;

template<typename T>
NotSimpleVector<T>::NotSimpleVector() : sz(0), cp(2), arr(std::allocator_traits<Alloc>::allocate(alloc, 2) {}

template<typename T>
size_t NotSimpleVector<T>::size() const noexcept { return sz; }
template<typename T>
size_t NotSimpleVector<T>::capacity() const noexcept { return cp; }

template<typename T>
void NotSimpleVector<T>::push_back(const T& a)
{
	if(sz == cp)
	{
		T* new_arr = std::allocator_traits<Alloc>::allocate(alloc, 2*cp);
		for(int i = 0; i < sz; ++i)
		{
			std::allocator_traits<Alloc>::construct(alloc, new_arr + i, arr[i]);
			std::allocator_traits<Alloc>::destroy(alloc, arr + i);
		}
		std::allocator_traits<Alloc>::deallocate(alloc, arr, sz);
		arr = new_arr;	
	}
	std::allocator_traits<Alloc>::construct(alloc, arr + sz, a);
	++sz;
}
template<typename T>
void NotSimpleVector<T>::pop_back() { --sz; }

template<typename T>
void NotSimpleVector<T>::insert()
{
	++sz;

	
	
}


T& NotSimpleVector<T>::operator[](size_t index) { return arr[index]; }
iterator NotSimpleVector<T>::begin() { return iterator(arr); }
iterator NotSimpleVector<T>::end() { return iterator(arr + sz); }

iterator::iterator(T* p) { ptr = p; }
iterator& operator++() { ++ptr; return *this; }
iterator operator++(int)
{
	NotSimpleIterator cpy = *this;
	++(*this);
	return cpy;
}

iterator::value_type iterator::operator*() { return *ptr; }
bool iterator::operator==(const NotSimpleIterator& rhs) const { return this->ptr == rhs.ptr; }
bool iterator::operator!=(const NotSimpleIterator& rhs) const { return !(*this == rhs); }
