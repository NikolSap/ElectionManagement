#pragma once
#include <iostream>

using namespace std;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

template<class T>
class List
{
protected:
	struct ListNode {
		T		  _data;
		ListNode* _next;
		ListNode* _prev;
	};

	ListNode* _head;
	ListNode* _tail;
	int len;

private:
	void swap(ListNode* prev, ListNode* p1, ListNode* p2)
	{/*swaps 2 ajasent nodes
	 p2=p1->next
	 p1=prev->next*/
		if (this->_tail == p2)
		{
			p2->_prev = p1->_prev;
			p2->_next = p1;
			p1->_prev = p2;
			p1->_next = nullptr;
			this->_tail = p1;
		}
		else {
			ListNode* next = p2->_next;
			prev->_next = p2;
			p2->_prev = prev;
			p2->_next = p1;
			p1->_prev = p2;
			p1->_next = next;
			next->_prev = p1;
		}
	}
	void swap(ListNode* p1, ListNode* p2)
	{/*p1=lstP.getHead()*/
		ListNode* next = p2->_next;
		p2->_prev = nullptr;
		p2->_next = p1;
		p1->_prev = p2;
		p1->_next = next;
		next->_prev = p1;
	}

public:

	int getLen() const { return this->len; }

	List& operator=(const List& lst)
	{
		ListNode* curr = lst._head;
		while (curr)
		{
			ListNode* n = new ListNode();
			n->_data = curr->_data;
			n->_next = n->_prev = nullptr;
			this->addToTail(n);
		}
		return *this;
	}
	bool operator==(const List& lst)
	{
		ListNode* curr = this->head, * other = lst.head;
		while (curr && other) {
			if (!(curr == other))
				return false;
			other = other->getNext();
			curr = curr->getNext();
		}
		if ((!curr) && (!other))
			return true;
		return false;
	}
	void PrintList()
	{
		ListNode* curr = this->_head;
		while (curr)
		{
			cout << *(curr->_data);
			cout << endl;
			curr = curr->_next;

		}
	}

	void bubbleSort()
	{
		int swapped;
		ListNode* ptr1, * prev = nullptr;
		ListNode* lptr = NULL;

		/* Checking for empty list */
		if (this->_head == NULL)
			return;

		do
		{
			swapped = 0;
			ptr1 = this->_head;

			while (ptr1 != nullptr && ptr1->_next != lptr)
			{
				if (ptr1->_data->getValueForSort() < ptr1->_next->_data->getValueForSort())
				{
					if (ptr1 == this->_head)
						this->swap(ptr1, ptr1->_next);
					else swap(prev, ptr1, ptr1->_next);/*prev will not be nullptr, if prev is nullptr, p1 is the list head*/
					swapped = 1;
				}
				prev = ptr1;
				ptr1 = ptr1->_next;
			}
			lptr = ptr1;
		} while (swapped);
	}


	class Iterator
	{
	public:
		ListNode* _ptr;
		Iterator(ListNode* ptr) :_ptr(ptr) {}

		void operator++() {
			_ptr = _ptr->_next;
		}
		Iterator operator++(int)
		{
			Iterator temp = _ptr;
			_ptr = _ptr->_next;
			return temp;
		}
		bool operator !=(const Iterator& other) {
			return (this->_ptr != other._ptr);
		}
		T& operator*() {
			return _ptr->_data;
		}
	};
	class Const_Iterator
	{
		public:
		const ListNode* _ptr;
		Const_Iterator(const ListNode* ptr) :_ptr(ptr) {}

		void operator++() const {
			_ptr = _ptr->_next;
		}
		Iterator operator++(int)const
		{
			const Iterator temp= _ptr;
			_ptr = _ptr->_next;
			return temp;
		}
		void operator--() const {
			_ptr = _ptr->_prev;
		}
		bool operator !=(const Iterator& other) const {
			return (this->_ptr != other._ptr);
		}
		T& operator*() const {
			return _ptr->_data;
		}
	};
	class Reverse_Iterator
	{
		public:
		ListNode* _ptr;
		Reverse_Iterator(ListNode* ptr) :_ptr(ptr) {}

		void operator++() {
			_ptr = _ptr->_prev;
		}
		Iterator operator++(int)
		{
			Iterator temp = _ptr;
			_ptr = _ptr->_prev;
			return temp;
		}
		void operator--() {
			_ptr = _ptr->_next;
		}
		bool operator !=(const Iterator& other) {
			return (this->_ptr != other._ptr);
		}
		T& operator*() {
			return _ptr->_data;
		}
	};

	List(T* data, int size) :_head(nullptr), _tail(nullptr) {/*array of size variabels*/
		for (int i = 0; i < size; i++)
		{
			addToTail(data[i]);
		}
	}
	List() :_head(nullptr), _tail(nullptr) {}

	void addToTail(T data) 
	{
		ListNode* n = new ListNode;
		n->_data = data;
		n->_next = nullptr;
		n->_prev = nullptr;
		if (!_head)
		{
			_head = _tail = n;
		}
		else
		{
			_tail->_next = n;
			n->_prev = _tail;
			_tail = n;
		}
		(this->len)++;
	}

	List<T>::Iterator begin() {return List<T>::Iterator(_head);}
	List<T>::Iterator end() {return List<T>::Iterator(nullptr);}

	List<T>::Const_Iterator cbegin() { return List<T>::Iterator(_head); }
	List<T>::Const_Iterator cend() { return List<T>::Iterator(nullptr); }

	List<T>::Reverse_Iterator rbegin() { return List<T>::Iterator(nullptr); }
	List<T>::Reverse_Iterator rend() { return List<T>::Iterator(_head); }

	//returns an iterator that points to the first of the newly inserted elements.
	Iterator Insert(Iterator itr, T data) {
		if (itr == end())
			throw std::out_of_range("ooops nullptr");

		ListNode* tmp = itr._ptr->_next;
		itr._ptr->_next = new ListNode;
		itr._ptr->_next->_data = data;
		itr._ptr->_next->_next = tmp;

		return Iterator(itr._ptr->_next);
	}

	Iterator erase(const Iterator& iter)
	{
		if (iter == end())
			throw std::out_of_range("ooops nullptr");
		Iterator temp = iter._ptr->_next;
		iter._ptr->_prev->_next = iter.__ptr->_next;
		iter._ptr->_next->_prev = iter._ptr->_prev;
		delete iter;
		return temp;
	}
	Iterator erase(const Iterator& first, const Iterator& last)
	{
		List<int>::Iterator itr1 = first;
		while(itr1 != last )
		{
			itr1=erase(itr1);
		}
		return itr1;
	}

	void save(ostream& out) const
	{
		out.write(rcastcc(&this->len), sizeof(int));
		ListNode* curr = this->_head;
		while (curr)
		{
			curr->_data->save(out);
			curr = curr->_next;
		}
	}
};