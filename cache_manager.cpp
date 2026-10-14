/**
 * @file cache_manager.cpp
 * @brief Implementation of a Cache Manager that interacts with a FIFO list and a Hash table.
 *
 * @date 10/14/2026 - initial creation
 * @author Robin Lane
 */

#include "dll_node.h"
#include "doubly_linked_list.h"
#include "hash_node.h"
#include "hash_table.h"
#include "cache_manager.h"
#include "milestone3.h"

//TODO: Comment
HashTable* CacheManager::getTable()
{
    return hashTable;
}

//TODO: Comment
DoublyLinkedList* CacheManager::getList()
{
    return doublyLinkedList;
}

//TODO: Comment
int CacheManager::getSize()
{
    return doublyLinkedList->getSize();
}

//TODO: Comment
bool CacheManager::isEmpty()
{
    return doublyLinkedList->isEmpty();
}

//TODO: Comment
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

//TODO: Comment
bool CacheManager::remove(int curKey)
{
    if(!hashTable->remove(curKey))
        return false;
    doublyLinkedList->remove(curKey);
    return true;
}

//TODO: Comment
void CacheManager::clear()
{
    hashTable->clear();;
    doublyLinkedList->clear();
}

//TODO: Comment
DllNode* CacheManager::getItem(int curKey)
{
    return hashTable->getItem(curKey)->fifoNode;
}

//TODO: Comment
int CacheManager::getMaxCacheSize()
{
    return maxCacheSize;
}

//TODO: Comment
bool CacheManager::contains(int curKey)
{
    return hashTable->contains(curKey);
}

//TODO: Comment
void CacheManager::printCache()
{
    doublyLinkedList->printList();
    hashTable->printTable();
}