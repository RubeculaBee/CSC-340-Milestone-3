/**
 * @author Robin Lane
 * @file hash_table.cpp
 * @brief This is the implementation file for HashTable, using hash_table.h
 *
 * @date 09-22-26 - Created File
 * @date 09-22-26 - Implemented Methods
 * @date 09-22-26 - Added comment documentation to methods 
 * @date 10-14-26 - Updated for Milestone 3
 */

#include "hash_table.h"
#include "hash_node.h"
#include "milestone3.h"
#include <string>

/**
 * Gets the array of buckets.
 * @return The pointer to the table array
 */
HashNode** HashTable::getTable()
{
	return table;
}

/**
 * Gets the size of the table.
 * @return The amount of buckets in the array
 */
int HashTable::getSize()
{
	return numberOfBuckets;
}

/**
 * Calculates a hash number equal to the given key modulus the array size.
 * @param currentKey: the key to of the node to hash
 * @return A hash code
 */
int HashTable::calculateHashCode(int currentKey)
{
	return currentKey % getSize();
}

/**
 * Checks whether there is at least one node in the hash table.
 * @return True if it is empty, false otherwise
 */
bool HashTable::isEmpty()
{
	for(int i = 0; i< numberOfBuckets; i++)
	{
		if(table[i] != nullptr)
			return false;
	}
	return true;
}

/**
 * Gets the amount of nodes in the hash table, including those occupying the same bucket in a linked chain.
 * @return The amount of nodes
 */
int HashTable::getNumberOfItems()
{
	int num = 0;
	for(int i = 0; i < numberOfBuckets; i++)
	{
		// Count each node in the bucket's chain
		for(HashNode* currentNode = table[i]; currentNode != nullptr; currentNode = currentNode->next)
			num++;
	}
	return num;
}

/**
 * Adds a node with a given key to the hash table
 * @param curKey: The key from the node that determines the hash code
 * @param mynode: The node to be added
 * @return True if it the node was added, false if the key already exists in the hash table.
 */
bool HashTable::add(int curKey, HashNode* mynode)
{
	int code = calculateHashCode(curKey);
	// If bucket is empty, simple add
	if(table[code] == nullptr)
		table[code] = mynode;
	else
	{
		HashNode* currentNode;
		// Iterate through bucket's linked chain until it reaches the last node
		for (currentNode = table[code]; currentNode->next != nullptr; currentNode = currentNode->next)
			// If the key to be added is already in the table, fail to add
			if(currentNode->key == curKey)
				return false;
		// For loop doesnt check key of last node, it is checked here
		// If the loop continued past the last node, we would lose the reference to the final node and couldnt add 
		if(currentNode->key == curKey)
				return false;
		// append new node to end of chain
		currentNode->next = mynode;
		mynode->prev = currentNode;
	}
	return true;
}

/**
 * Removes a node with the given key from the hash table.
 * @param curKey the key to search for
 * @return True if an item was removed, false if an item with the given key could not be found
 */
bool HashTable::remove(int curKey)
{
	int code = calculateHashCode(curKey);
	//Special case when removing first node in bucket
	if(table[code]->key == curKey)
	{
		HashNode* temp = table[code]->next;
		delete table[code];
		table[code] = temp;
		if(table[code] != nullptr)
			table[code]->prev = nullptr;
		return true;
	}
	
	// Otherwise search through linked chain
	for(HashNode* currentNode = table[code]; currentNode->next != nullptr; currentNode = currentNode->next)
	{
		if(currentNode->next->key == curKey)
		{
			HashNode* temp = currentNode->next->next;
			delete currentNode->next;
			currentNode->next = temp;
			if(currentNode->next != nullptr)
				currentNode->next->prev = currentNode;
			return true;
		}
	}

	// If no nodes have curKey and loop ends, fail to remove.
	return false;
}

/**
 * Frees the memory of every node in the hash table
 * @return void
 */
void HashTable::clear()
{
	for(int i = 0; i< numberOfBuckets; i++)
	{
		if(table[i] != nullptr)
		{
			// This shoud probably be a while loop, for better control over program flow.
			for(HashNode* currentNode = table[i]; ; currentNode = currentNode->next)
			{
				if(currentNode->prev != nullptr)
					delete currentNode->prev;
				if(currentNode->next == nullptr)
				{
					delete currentNode;
					break;
				}
			}
			table[i] = nullptr;
		}
	}
}
/**
 * Searches for an item with a particular key.
 * @param curKey the key to search for
 * @return The item with that key, or nullptr if the item is not found
 */
HashNode* HashTable::getItem(int curKey)
{
	int code = calculateHashCode(curKey);
	for(HashNode* currentNode = table[code]; currentNode != nullptr; currentNode = currentNode->next)
		if(currentNode->key == curKey)
			return currentNode;

	return nullptr;
}

/**
 * Checks whether there is an item with a particular key in the hash table.
 * @param curKey the key to search for
 * @return True if it is found, false otherwise
 */
bool HashTable::contains(int curKey)
{
	int code = calculateHashCode(curKey);
	for(HashNode* currentNode = table[code]; currentNode != nullptr; currentNode = currentNode->next)
		if(currentNode->key == curKey)
			return true;

	return false;
}

/**
 * Logs (to file and console) each bucket in the table, and each node in each bucket.
 * @return void
 */
void HashTable::printTable()
{
	logToFileAndConsole("\nHere are the Hash Table contents (" + std::to_string(getNumberOfItems()) + " entries):");

	for(int i = 0; i< numberOfBuckets; i++)
	{
		if(table[i] == nullptr)
			logToFileAndConsole("Bucket " + std::to_string(i) + ": Empty");
		else
		{
			logToFileAndConsole("Bucket " + std::to_string(i) + ": ");
			for(HashNode* currentNode = table[i]; currentNode != nullptr; currentNode = currentNode->next)
				currentNode->printNode(true);
		}
	}

	logToFileAndConsole("End of table\n");
}