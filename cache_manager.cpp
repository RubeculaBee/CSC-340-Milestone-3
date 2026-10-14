/**
 * @file cache_manager.cpp
 * @brief Implementation of a Cache Manager that interacts with a FIFO list and a Hash table.
 *
 * @date 10/14/2026 - initial creation
 * @author Robin Lane
 */

#include "dll_node.h"
#include "doubly_linked_list.h"
#include "hash_table.h"
#include "cache_manager.h"

//TODO: Comment
HashTable* CacheManager::getTable()
{
    return this->hashTable;
}

//TODO: Comment
DoublyLinkedList* CacheManager::getList()
{
    return this->doublyLinkedList;
}

//TODO: Comment
int CacheManager::getSize()
{
    return this->doublyLinkedList->getSize();
}

//TODO: Comment
bool CacheManager::isEmpty()
{
    //TODO: Implement
    return false;
}

//TODO: Comment
bool CacheManager::add(int curKet, DllNode* myNode)
{
    //TODO: Implement
    return false;
}

//TODO: Comment
bool CacheManager::remove(int curKet)
{
    //TODO: Implement
    return false;
}

//TODO: Comment
void CacheManager::clear()
{
    //TODO: Implement
    return;
}

//TODO: Comment
DllNode* CacheManager::getItem(int curKet)
{
    //TODO: Implement
    return nullptr;
}

//TODO: Comment
int CacheManager::getMaxCacheSize()
{
    //TODO: Implement
    return 0;
}

//TODO: Comment
bool CacheManager::contains(int curKet)
{
    //TODO: Implement
    return false;
}

//TODO: Comment
void CacheManager::printCache()
{
    //TODO: Implement
    return;
}