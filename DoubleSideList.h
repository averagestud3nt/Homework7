#pragma once
#include <iostream>

struct DSNode
{
	int value;
	DSNode* next;
	DSNode* previous;

	DSNode(int value) : value{ value }, next{ nullptr }, previous{ nullptr } {}

};


class DoubleSideList
{
private:
	DSNode* m_head;
	DSNode* m_tail;

public:
	DoubleSideList() : m_head(nullptr), m_tail(nullptr) {}

	void add(int value, std::string side)
	{
		if (m_head == nullptr && m_tail == nullptr)
		{
			DSNode* newNode = new DSNode(value);
			m_head = newNode;
			m_tail = newNode;
			return;
		}
		if (side == "head")
		{
			DSNode* newNode = new DSNode(value);
			newNode->previous = m_head;
			m_head->next = newNode;
			m_head = newNode;
			return;
		}
		if (side == "tail")
		{
			DSNode* newNode = new DSNode(value);
			newNode->next = m_tail;
			m_tail->previous = newNode;
			m_tail = newNode;
			return;
		}
	}

	void remove(std::string side)
	{
		if (side == "head")
		{
			DSNode* temp = m_head;
			m_head = m_head->previous;
			delete temp;
		}
		if (side == "tail")
		{
			DSNode* temp = m_tail;
			m_tail = m_tail->next;
			delete temp;
		}
	}

	DSNode* find(int value,std::string startPoint)
	{
		if (startPoint == "head")
		{
			DSNode* current = m_head;
			while (current != nullptr)
			{
				if (current->value == value)
				{
					return current;
				}

				current = current->previous;
			}
			return nullptr;
		}
		if (startPoint == "tail")
		{
			DSNode* current = m_tail;
			while (current != nullptr)
			{
				if (current->value == value)
				{
					return current;
				}

				current = current->next;
			}
			return nullptr;
		}
	}

	void addAfter(int value, int after)
	{
		DSNode* afterNode = find(after,"head");
		if (afterNode == nullptr)
		{
			add(value, "head");
			return;
		}
		DSNode* node = new DSNode(value);

		DSNode* next = afterNode->next;
		afterNode->next = node;
		node->next = next;
		node->previous = afterNode;
		next->previous = node;

	}

	void addBefore(int value, int before)
	{
		DSNode* beforeNode = find(before, "tail");
		if (beforeNode == nullptr)
		{
			add(value, "tail");
			return;
		}
		DSNode* node = new DSNode(value);

		DSNode* previous = beforeNode->previous;
		beforeNode->previous = node;
		node->previous = previous;
		node->next = beforeNode;
		previous->next = node;
	}

	void removeAfter(int after)
	{
		DSNode* afterNode = find(after,"head");
		if (afterNode == nullptr)
		{
			return;
		}

		DSNode* temp = afterNode->next;
		afterNode->next = afterNode->next->next;
		afterNode->next->previous = afterNode;
		delete temp;
	}

	void removeBefore(int before)
	{
		DSNode* beforeNode = find(before, "tail");
		if (beforeNode == nullptr)
		{
			return;
		}

		DSNode* temp = beforeNode->previous;
		beforeNode->previous = beforeNode->previous->previous;
		beforeNode->previous->next = beforeNode;
		delete temp;
	}

	void clear()
	{
		while (m_head != nullptr) remove("head");
	}

	void doForEach(void(*funcPtr)(DSNode* node))
	{
		DSNode* current = m_tail;
		while (current != nullptr)
		{
			funcPtr(current);
			current = current->next;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const DoubleSideList& list)
	{
		DSNode* current = list.m_head;
		while (current != nullptr)
		{
			os << current->value << ' ';
			current = current->next;
		}
		return os;
	}

	DoubleSideList* clone(DoubleSideList* List)
	{
		DoubleSideList* newList = new DoubleSideList();

		DSNode* addedList1 = List->m_tail;
		while (addedList1 != nullptr)
		{
			newList->add(addedList1->value, "head");
			addedList1 = addedList1->next;
		}

		return newList;
	};

	DoubleSideList* operator+(DoubleSideList* List)
	{
		DoubleSideList* newList = new DoubleSideList();

		DSNode* addedList1 = this->m_tail;
		while (addedList1 != nullptr)
		{
			newList->add(addedList1->value,"head");
			addedList1 = addedList1->next;
		}

		DSNode* addedList2 = List->m_tail;
		while (addedList2 != nullptr)
		{
			newList->add(addedList2->value, "head");
			addedList2 = addedList2->next;
		}

		return newList;
	}

	DoubleSideList* operator*(DoubleSideList* list)
	{
		DoubleSideList* newList = new DoubleSideList();

		DSNode* addedList1 = this->m_tail;
		while (addedList1 != nullptr)
		{
			if (list->find(addedList1->value,"tail"))
			{
				newList->add(addedList1->value, "head");
			}
			addedList1 = addedList1->next;
		}

		DSNode* addedList2 = list->m_tail;
		while (addedList2 != nullptr)
		{
			if (this->find(addedList2->value, "tail"))
			{
				newList->add(addedList2->value, "head");
			}
			addedList2 = addedList2->next;
		}

		return newList;
	}
};

template <class T>
class Array
{
private:
	T* m_array;
	int m_hiddenSize;
	int m_arraySize;
	int m_growFactor;
public:
	Array() : Array(5, 5){}

	Array(int size, int grow) : m_arraySize(size), m_growFactor(grow),m_hiddenSize(m_arraySize)
	{ 
		m_array = new T[m_arraySize];
	}


	int getSize() const { return m_arraySize; }

	void setSize(int newSize, int newGrowFactor)
	{
		if (m_arraySize < newSize)
		{
			T* newArray = new T[newSize];
			for (int i = 0; i < m_arraySize; ++i)
			{
				newArray = m_array[i];
			}
			delete[] m_array;
			m_array = newArray;
		}
		m_hiddenSize = m_arraySize;
		m_arraySize = newSize;
		m_growFactor = newGrowFactor;
	}

	int getUppperBound() const
	{
		int highestIndex = -1;
		for (int i = 0; i < m_arraySize; ++i)
		{
			if (m_array[i] != nullptr)
				highestIndex = i;
		}
		return highestIndex;
	}

	bool isEmpty() const
	{
		for (int i = 0; i < m_arraySize; ++i)
		{
			if (m_array[i] == nullptr)
				return false;
		}
		return true;
	}

	bool freeExtra()
	{
		if (m_hiddenSize > m_arraySize)
		{
			for (int i = m_arraySize; i < m_hiddenSize; i++)
			{
				delete m_array[i];
			}
		}
	}

	bool removeAll()
	{
		for (int i = 0; i < m_arraySize; ++i)
		{
			delete m_array[i];
			m_array[i] = nullptr;
		}
	}

	T getAt(int index) const {return m_array[index];}

	T* getData() const { return m_array; }



	void setAt(T element, int index)
	{
		m_array[index] = element;
	}

	void insertAt(T element, int index)
	{
		T* newArray = new T[m_arraySize + m_growFactor];
		for (int i = 0; i < index; i++)
		{
			newArray[i] = m_array[i];
		}
		for (int i = index ; i < m_arraySize + m_growFactor - 1; i++)
		{
			newArray[i + 1] = m_array[i];
		}
		newArray[index] = element;
		delete[] m_array;
		m_array = newArray;
	}

	void removeAt(T element, int index)
	{
		delete m_array[index];
	}

	T operator[](int index)
	{
		return (m_array[index])*;
	}

	void Add(T element)
	{
		for (int i = 0; i < m_arraySize; ++i)
		{
			if (m_array[i] == nullptr)
			{
				m_array[i] = element;
				return;
			}
		}
		T* newArr = new T[m_arraySize + m_growFactor];
		for (int i = 0; i < m_arraySize; i++)
		{
			newArr = m_array[i]
		}
		m_arraySize += m_growFactor;
		m_hiddenSize = m_arraySize;
		newArr[m_arraySize / 2] = element;
		delete[] m_array;
		m_array = newArr;
	}

	void Append(Array arr)
	{
		int newSize = (arr.getUppperBound() + 1) + m_arraySize;
		T* newArray = new T[newSize];
		
		int counter;
		for (int i = 0; i < m_arraySize; i++)
		{
			newArray[counter++] = m_array[i];
		}
		for (int i = 0; i < arr.getUppperBound() + 1; i++)
		{
			newArray[counter++] = arr[i];
		}

		delete[] m_array;
		m_array = newArray;
	}
};

