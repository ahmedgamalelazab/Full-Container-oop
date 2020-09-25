#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include<algorithm>
template<typename Object>
class Vector
{

private:
	//in this section i'm going to type the core of the class
	//=====================Core==========================================
	Object* objects; //expect to have a dynamic array
	//=====================core==========================================

public:
	//this will be the controlling section of the class
	//=================================================CONTROLLING======================================
	Vector(int initialVal = 0):TheSize(initialVal),TheCapacity(initialVal+SPARE_CAPACITY),objects(nullptr)
	{
		objects = new Object[TheCapacity];
	};
	Vector(const Vector& rhs):TheSize(rhs.TheSize),TheCapacity(rhs.TheCapacity),objects(nullptr)
	{
		for (int i = 0 ; i < TheSize ; i++)
		{
			objects[i] = rhs.objects[i]; //something like it does the transfer well by copying in another memo
		};
	};
	Vector&operator=(const Vector& rhs)
	{
		Vector copy = rhs;
		std::swap(*this , copy);
		return *this;
	};
	~Vector()
	{
		delete [] objects;
	};	
	//=================================================CONTROLLING======================================
	//public section for inner classes
	//====================================================inner class for iterators==================
public:
	class const_iterator
	{

	public:
		
		const_iterator():current(nullptr){};
		
		const Object& operator*()const
		{
			return *current;
		};

		//here how the job being done
		const_iterator& operator++()
		{
			current = current + 1 ;
			return *this;
		};
		const_iterator& operator++(int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		};
		bool operator==(const const_iterator& rhs)
		{
			return current == rhs.current;
		};

		bool operator !=(const const_iterator& rhs)
		{
			return !(*this == rhs);
		};

	protected:

		Object* current;
		const_iterator(Object* p):current(p){};
		friend  class Vector<Object>;

	};

	//section of the main class here
	class iterator : public const_iterator
	{
	public:
		//building the blocks of the class here
		Object& operator*()
		{
			return *this->current;
		};
		const iterator& operator*()const
		{
			return const_iterator::operator*();
		};
		iterator& operator++()
		{
			this->current = this->current+1;
			return *this;
		};
		iterator& operator++(int)
		{
			iterator old = *this;
			++(*this);
			return old;
		};

	protected:
		iterator(Object* p):const_iterator(p){};
		friend class Vector<Object>;
	};

	//====================================================inner class for iterators==================

	//==========================================classes CONTROLLING======================================
	//==========================================classes CONTROLLING======================================
		iterator begin()
		{
			return iterator(&objects[0]);
		};

		const_iterator begin()const
		{
			return const_iterator(&objects[0]);
		};
		iterator end()
		{
			return iterator(&objects[TheSize]);
		};

		const_iterator end()const
		{
			return const_iterator(&objects[TheSize]);
		};
	
	////==========================================classes CONTROLLING======================================
		void push_back(const Object& x)
		{
			if(size() == capacity())
			{
				reserve(2*TheCapacity+1);
			};
			insert(end(),x);
		};
		void pop_back()
			{
				TheSize--;
			};
	/////==========================================classes CONTROLLING======================================
	//essential callBacks()============================================================================
		int size()const
		{
			return TheSize;
		};
		bool isEmpty()const
		{
			return TheSize == 0;
		};
		int capacity()const
		{
			return TheCapacity;
		};
		void resize(int newsize)
		{
			if(newsize > TheCapacity)
			{
				reserve(2*TheCapacity);
			};
			TheSize = newsize;
		};
		void reserve(int newCapacity)
		{
			if(newCapacity < TheSize)
			{
				return;
			};
			Object* newArr  = objects;
			objects = new Object[newCapacity];
			for (int i = 0 ; i < size() ; i++)
			{
				objects[i] = newArr[i];
			};
			TheCapacity = newCapacity;
			std::swap(objects , newArr);
			delete [] newArr;
		};
		Object& operator[](int index)
		{
			return objects[index];
		};
		const Object& operator[](int index)const
		{
			return objects[index];
		};
	//essential callBacks()============================================================================
private:
	//in this section we will design the patterns of controlling the app
	//=====================TRACKERS==========================================
	int TheSize;
	int TheCapacity;
	static const int SPARE_CAPACITY = 16;
	//=====================TRACKERS==========================================
	//================================================core building=====================================
		iterator insert(iterator itr , const Object& x)
		{
			Object* p  = itr.current;
			TheSize ++;
			return iterator(&(*p = x));
		};
	//================================================core building=====================================
};
#endif
