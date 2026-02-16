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
};

