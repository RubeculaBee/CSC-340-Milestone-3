/**
 * @file cache_manager.cpp
 * @brief Implementation of a Cache Manager that interacts with a FIFO list and a Hash table.
 *
 * @date 10/14/2026 - initial creation
 * @date 10/14/2026 - added comments
 * @author Robin Lane
 */

#include "dll_node.h"
#include "doubly_linked_list.h"
#include "hash_node.h"
#include "hash_table.h"
#include "cache_manager.h"
#include "milestone3.h"

/**
 * @brief Gets a pointer to the internal hash table.
 * 
 * @return Pointer to the HashTable object.
 */
HashTable* CacheManager::getTable()
{
    return hashTable;
}

/**
 * @brief Gets a pointer to the internal linked list.
 * 
 * @return Pointer to the DoublyLinkedList object.
 */
DoublyLinkedList* CacheManager::getList()
{
    return doublyLinkedList;
}

/**
 * @brief Gets the amount of item in the cache.
 * 
 * @return The number of items in the cache.
 */
int CacheManager::getSize()
{
    return doublyLinkedList->getSize();
}

/**
 * @brief Gets whether the cache has ay items.
 * 
 * @return true if there is at least one item, false otherwise.
 */
bool CacheManager::isEmpty()
{
    return doublyLinkedList->isEmpty();
}

/**
 * @brief Adds an item to the cache (to both the FIFO list and hash table).
 * 
 * @return true if the item was successfully added, false otherwise.
 */
bool CacheManager::add(int curKey, DllNode* myNode)
{
    if(hashTable->add(curKey, new HashNode(curKey, myNode)))
    {
        doublyLinkedList->insertAtHead(curKey, myNode);
        if(doublyLinkedList->getSize() >= maxCacheSize)
        {
            hashTable->remove(doublyLinkedList->tail->key);
            doublyLinkedList->removeTailNode();
        }
        return true;
    }
    return false;

}

/**
 * @brief Removes an item from the cache (from both the FIFO list and hash table).
 * 
 * @return true if the item was successfully removed, false otherwise.
 */
bool CacheManager::remove(int curKey)
{
    if(!hashTable->remove(curKey))
        return false;
    doublyLinkedList->remove(curKey);
    return true;
}

/**
 * @brief Removes every item in the cache (list and table) until it is empty
 * 
 * @return none
 */
void CacheManager::clear()
{
    hashTable->clear();
    doublyLinkedList->clear();
}

/**
 * @brief Gets an item from the cache with a certain key 
 *        (from hash table for efficiency)
 * 
 * @return The item with the matching key
 */
DllNode* CacheManager::getItem(int curKey)
{
    return hashTable->getItem(curKey)->fifoNode;
}

/**
 * @brief Gets the maximum number of items that can exist in the cache.
 * 
 * @return the maximum cache size.
 */
int CacheManager::getMaxCacheSize()
{
    return maxCacheSize;
}

/**
 * @brief Checks if an item with a specific key exists in the hash manager
 *        (from hash table for efficency)
 * 
 * @return true if the item is found, false otherwise
 */
bool CacheManager::contains(int curKey)
{
    return hashTable->contains(curKey);
}

/**
 * @brief Prints the contents of both the FIFO list and hash table to
 *        the console and the ouput log.
 * 
 * @return none
 */
void CacheManager::printCache()
{
    logToFileAndConsole("\n\nPrinting out the cache contents");

    doublyLinkedList->printList();
    hashTable->printTable();

    logToFileAndConsole("End of cache contents\n");
}