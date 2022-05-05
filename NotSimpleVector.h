#pragma once
#include <memory>
#include <iterator>
#include <algorithm>
#include <iostream>

template <typename T>
class NotSimpleIterator
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type*;

	NotSimpleIterator(T* p);

	NotSimpleIterator& operator++();
	NotSimpleIterator operator++(int);
	NotSimpleIterator& operator--();
	NotSimpleIterator operator--(int);
	NotSimpleIterator& operator+=(int n);
	NotSimpleIterator& operator-=(int n);
	NotSimpleIterator operator+(int n);
	NotSimpleIterator operator-(int n);
	ptrdiff_t operator-(const NotSimpleIterator& rhs);
	T& operator*();
	bool operator==(const NotSimpleIterator& rhs) const;
	bool operator!=(const NotSimpleIterator& rhs) const;

private:
	T* ptr;
};

template <typename T, typename Alloc = std::allocator<T>>
class NotSimpleVector
{
public:
	using iterator = NotSimpleIterator<T>;
	NotSimpleVector();

	size_t size() const noexcept;
	size_t capacity() const noexcept;
	void push_back(const T& a);
	void pop_back();
	void pop_back(size_t n);
	void insert(NotSimpleIterator<T> it, const T& value);
	void erase(NotSimpleIterator<T> first, NotSimpleIterator<T> last);
	void erase(NotSimpleIterator<T> first);
	T& back();
	T& operator[](size_t index);
	iterator begin();
	iterator end();

private:
	T* arr;
	Alloc alloc;
	size_t sz;
	size_t cp;
};


template<typename T, typename Alloc>
NotSimpleVector<T, Alloc>::NotSimpleVector() : sz(0), cp(2), arr(std::allocator_traits<Alloc>::allocate(alloc, 2)) {}

template<typename T, typename Alloc>
size_t NotSimpleVector<T, Alloc>::size() const noexcept { return sz; }
template<typename T, typename Alloc>
size_t NotSimpleVector<T, Alloc>::capacity() const noexcept { return cp; }

template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::push_back(const T& a)
{
	if (sz == cp)
	{
		T* new_arr = std::allocator_traits<Alloc>::allocate(alloc, 2 * cp);
		for (int i = 0; i < sz; ++i)
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
template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::pop_back() { pop_back(1); }

template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::pop_back(size_t n) { sz -= n; }

template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::insert(NotSimpleIterator<T> it, const T& value)
{
	NotSimpleVector<T, Alloc>::push_back(value);
	auto end = NotSimpleVector::end();
	for (auto i = it; i != end; ++i)
		std::swap(*i, this->back());
}

template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::erase(NotSimpleIterator<T> first, NotSimpleIterator<T> last)
{
	while (last != NotSimpleVector<T, Alloc>::end())
	{
		++last;
		++first;
		for (auto it = last - 1; it != first; --it)
		{
			std::swap(*it, *(it - 1));
		}
		std::swap(*first, *(first - 1));
	}
	pop_back(last - first);
}

template<typename T, typename Alloc>
void NotSimpleVector<T, Alloc>::erase(NotSimpleIterator<T> first){ NotSimpleVector<T, Alloc>::erase(first, first + 1);}

template<typename T, typename Alloc>
T& NotSimpleVector<T, Alloc>::back(){ return *std::prev(this->end()); }

template<typename T, typename Alloc>
T& NotSimpleVector<T, Alloc>::operator[](size_t index) { return arr[index]; }
template<typename T, typename Alloc>
NotSimpleIterator<T> NotSimpleVector<T, Alloc>::begin() { return NotSimpleIterator<T>(arr); }
template<typename T, typename Alloc>
NotSimpleIterator<T> NotSimpleVector<T, Alloc>::end() { return NotSimpleIterator<T>(arr + sz); }

template<typename T>
NotSimpleIterator<T>::NotSimpleIterator(T* p) { ptr = p; }
template<typename T>
NotSimpleIterator<T>& NotSimpleIterator<T>::operator++(){ ++ptr; return *this; }

template<typename T>
NotSimpleIterator<T> NotSimpleIterator<T>::operator++(int){ NotSimpleIterator<T> cpy = *this; ++(*this); return cpy;}

template<typename T>
NotSimpleIterator<T>& NotSimpleIterator<T>::operator--(){ --ptr; return *this;}

template<typename T>
NotSimpleIterator<T> NotSimpleIterator<T>::operator--(int){ NotSimpleIterator<T> cpy = *this; --(*this); return cpy; }

template<typename T>
NotSimpleIterator<T>& NotSimpleIterator<T>::operator+=(int n){ ptr += n; return *this; }

template<typename T>
NotSimpleIterator<T>& NotSimpleIterator<T>::operator-=(int n) {	ptr -= n; return *this; }

template<typename T>
NotSimpleIterator<T> NotSimpleIterator<T>::operator+(int n){ NotSimpleIterator<T> res = *this; res += n; return res; }

template<typename T>
NotSimpleIterator<T> NotSimpleIterator<T>::operator-(int n){ NotSimpleIterator<T> res = *this; res -= n; return res;}

template<typename T>
ptrdiff_t NotSimpleIterator<T>::operator-(const NotSimpleIterator<T>& rhs){	return this->ptr - rhs.ptr; }



template<typename T>
T& NotSimpleIterator<T>::operator*() { return *ptr; }
template<typename T>
bool NotSimpleIterator<T>::operator==(const NotSimpleIterator<T>& rhs) const { return this->ptr == rhs.ptr; }
template<typename T>
bool NotSimpleIterator<T>::operator!=(const NotSimpleIterator<T>& rhs) const { return !(*this == rhs); }
