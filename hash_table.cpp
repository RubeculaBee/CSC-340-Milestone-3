/**
 * @author Robin Lane
 * @file hash_table.cpp
 * @brief This is the implementation file for HashTable, using hash_table.h
 *
 * @date 09-22-26 - Created File
 * @date 010-14-26 - Updated for milestone 3
 */

#include "hash_table.h"
#include "hash_node.h"
#include "milestone3.h"
#include <string>

// TODO: Comment
HashNode** HashTable::getTable()
{
	return table;
}

// TODO: Comment
int HashTable::getSize()
{
	return numberOfBuckets;
}

// TODO: Comment
int HashTable::calculateHashCode(int currentKey)
{
	return currentKey % getSize();
}

// TODO: Comment
bool HashTable::isEmpty()
{
	for(int i = 0; i< numberOfBuckets; i++)
	{
		if(table[i] != nullptr)
			return false;
	}
	return true;
}

// TODO: Comment
int HashTable::getNumberOfItems()
{
	int num = 0;
	for(int i = 0; i< numberOfBuckets; i++)
	{
		if(table[i] != nullptr)
			num++;
	}
	return num;
}

// TODO: Comment
bool HashTable::add(int curKey, HashNode* mynode)
{
	int code = calculateHashCode(curKey);
	table[code] = mynode;
	return true;
}

// TODO: Comment
bool HashTable::remove(int curKey)
{
	int code = calculateHashCode(curKey);
	if(table[code]->key == curKey)
	{
		delete table[code];
		table[code] = nullptr;
		return true;
	}

	return false;
}

// TODO: Comment
void HashTable::clear()
{
	for(int i = 0; i< numberOfBuckets; i++)
	{
		if(table[i] != nullptr)
		{
			delete table[i];
			table[i] = nullptr;
		}
	}
}

// TODO: Comment
HashNode* HashTable::getItem(int curKey)
{
	int code = calculateHashCode(curKey);
	return table[code];
}

// TODO: Comment
bool HashTable::contains(int curKey)
{
	int code = calculateHashCode(curKey);
	return table[code];
}

// TODO: Comment
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
			table[i]->printNode(true);
		}
	}

	logToFileAndConsole("End of table\n");
}