/**
 * @file doubly_linked_list.cpp
 * @brief Implementation of a Doubly Linked List, with methods as declared in doubly_linked_list.h.
 *
 * Contains common operations like insertion, deletion, and movement of nodes.
 *
 * @date 09/05/2026 - initial creation
 * @date 09/07/2026 - completed code 
 * @date 09/08/2026 - Added comments
 * @author Robin Lane
 */

#include "milestone3.h"
#include "doubly_linked_list.h"
#include "dll_node.h"
 
// Constructor initialises an empty list
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}
// Destructor deletes every node using clear()
DoublyLinkedList::~DoublyLinkedList() { this->clear(); }

/**
 * checks if there are any nodes in the list
 *
 * @param none
 * @return true if there is at least 1 node, otherwise false
 */
bool DoublyLinkedList::isEmpty() { return !head; }

/**
 * Adds a new node at the front of the list, it becomes the new head.
 *
 * @param key: the value to be stored in the new node
 * @return nothing
 */
void DoublyLinkedList::insertAtHead(int key)
{
	DllNode* new_node = new DllNode(key);
	
	if(isEmpty())
	{
		head = new_node;
		tail = new_node;
		return;
	}

	new_node->next = head;
	head->prev = new_node;
	head = new_node;
}

/**
 * Adds a new node at the back of the list, it becomes the new tail.
 *
 * @param key: the value to be stored in the new node
 * @return nothing
 */
void DoublyLinkedList::insertAtTail(int key)
{
	DllNode* new_node = new DllNode(key);
	
	if(isEmpty())
	{
		head = new_node;
		tail = new_node;
		return;
	}
	
	new_node->prev = tail;
	tail->next = new_node;
	tail = new_node;
}

/**
 * Searches for a node with a specified key and removes that node.
 *
 * @param key: the value in the node to search for.
 * @return nothing
 */
void DoublyLinkedList::remove(int key)
{
	DllNode* current = head;
	while(current)
	{
		if(current->key == key)
		{
			if(current == head)
				removeHeaderNode();
			else if(current == tail)
				removeTailNode();
			else
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
				delete current;
			}
			
			return;
		}
		current = current->next;
	}
}

/**
 * Removes the first node in the list
 *
 * @param none
 * @return nothing
 */
void DoublyLinkedList::removeHeaderNode()
{
	if(head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}

	head = head->next;
	delete head->prev;
	head->prev = nullptr;
}

/**
 * Removes the last node in the list
 *
 * @param none
 * @return nothing
 */
void DoublyLinkedList::removeTailNode()
{
	if(head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}

	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;
}

/**
 * Searches for a node with a specified key and places it at the front of the list, becoming the new head.
 *
 * @param key: the value in the node to search for.
 * @return nothing
 */
void DoublyLinkedList::moveNodeToHead(int key)
{
	remove(key);
	insertAtHead(key);
}

/**
 * Searches for a node with a specified key and places it at the back of the list, becoming the new tail.
 *
 * @param key: the value in the node to search for.
 * @return nothing
 */
void DoublyLinkedList::moveNodeToTail(int key)
{
	remove(key);
	insertAtTail(key);
}


/**
 * Deletes every node in the list, making the list empty again.
 *
 * @param none
 * @return nothing
 */
void DoublyLinkedList::clear()
{
	if(isEmpty())
		return;

	DllNode* current = head;
	while(current->next)
	{
		current = current->next;
		delete current->prev;
	}
	delete tail;
	head = nullptr;
	tail = nullptr;
}

/**
 * Displays the value stored in each node sequentially from head to tail.
 *
 * @param none
 * @return nothing
 */
void DoublyLinkedList::printList()
{
	logToFileAndConsole("\nHere are the List contents:");
	DllNode* current = head;
	while(current)
	{
		logToFileAndConsole("Node key: " + std::to_string(current->key));
		current = current->next;
	}
	logToFileAndConsole("End of List");
}

/**
 * Displays the value stored in each node sequentially from tail to head.
 *
 * @param none
 * @return nothing
 */
void DoublyLinkedList::reversePrintList()
{
	logToFileAndConsole("\nHere are the List contents reversed:");
	DllNode* current = tail;
	while(current)
	{
		logToFileAndConsole("Node key: " + std::to_string(current->key));
		current = current->prev;
	}
	logToFileAndConsole("End of List");
}