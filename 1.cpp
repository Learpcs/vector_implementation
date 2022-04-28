#include <bits/stdc++.h>

template <typename T, typename Alloc = std::allocator<T>>
class NotSimpleVector
{
	public:
	class NotSimpleIterator
	{
		public:
		using value_type = T;
		using ptr_type = T*;
		NotSimpleIterator(ptr_type p)
		{
			ptr = p;
		}
		NotSimpleIterator& operator++()
		{
			++ptr;
			return *this;
		}
		NotSimpleIterator operator++(int)
		{
			NotSimpleIterator cpy = *this;
			++(*this);
			return cpy;
		}
		value_type operator*()
		{
			return *ptr;
		}

		bool operator==(const NotSimpleIterator& rhs) const
		{
			return this->ptr == rhs.ptr;
		}

		bool operator!=(const NotSimpleIterator& rhs) const
		{
			return !(*this == rhs);
		}

		private:
		T* ptr; 	
	};
	using iterator = NotSimpleIterator;
	NotSimpleVector()
	{
		sz = 0;
		cp = 2;
		arr = std::allocator_traits<Alloc>::allocate(alloc, 2);
	}

	size_t size() const noexcept
	{
		return sz;
	}

	size_t capacity() const noexcept
	{
		return cp;
	}

	void push_back(const T& a)
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
	
	void pop_back()
	{
		--sz;
	}

	void insert()
	{
		++sz;
		
	}


	T& operator[](size_t index)
	{
		return arr[index];
	}
	

	iterator begin()
	{
		return iterator(arr);
	}
	NotSimpleIterator end()
	{
		return iterator(arr + sz);
	}
	private:
	T* arr;
	Alloc alloc;
	size_t sz;
	size_t cp;
};


int main()
{
	NotSimpleVector<int> a;
	int n;
	std::cin >> n;
	for(int i = 0; i < n; ++i)
	{
		int x;
		std::cin >> x;
		a.push_back(x);
	}
	for(int x : a)
		std::cout << x << ' ';
}
	

