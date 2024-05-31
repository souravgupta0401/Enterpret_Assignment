#include "cache.h"

template <typename K, typename V>
Cache<K, V>::Cache(int capacity) : cap(capacity)
{
    head = new node<K, V>(K(), V());
    tail = new node<K, V>(K(), V());
    head->next = tail;
    tail->prev = head;
}

template <typename K, typename V>
void Cache<K, V>::addNode(node<K, V> *newnode)
{
    node<K, V> *temp = head->next;
    newnode->next = temp;
    newnode->prev = head;
    head->next = newnode;
    temp->prev = newnode;
}

template <typename K, typename V>
void Cache<K, V>::deleteNode(node<K, V> *delnode)
{
    node<K, V> *delprev = delnode->prev;
    node<K, V> *delnext = delnode->next;
    delprev->next = delnext;
    delnext->prev = delprev;
    delete delnode;
}

template <typename K, typename V>
LRUCache<K, V>::LRUCache(int capacity) : Cache<K, V>(capacity) {}

template <typename K, typename V>
V LRUCache<K, V>::get(K key_)
{
    std::shared_lock<std::shared_mutex> lock(this->mutex_);
    if (this->m.find(key_) != this->m.end())
    {
        node<K, V> *resnode = this->m[key_];
        V res = resnode->val;
        lock.unlock();

        std::unique_lock<std::shared_mutex> uniquelock(this->mutex_);
        this->m.erase(key_);
        this->deleteNode(resnode);
        this->addNode(new node<K, V>(key_, res));
        this->m[key_] = this->head->next;
        return res;
    }

    return V();
}

template <typename K, typename V>
void LRUCache<K, V>::put(K key_, V value)
{
    std::unique_lock<std::shared_mutex> uniquelock(this->mutex_);
    if (this->m.find(key_) != this->m.end())
    {
        node<K, V> *existingNode = this->m[key_];
        this->m.erase(key_);
        this->deleteNode(existingNode);
    }
    if (this->m.size() == this->cap)
    {
        this->m.erase(this->tail->prev->key);
        this->deleteNode(this->tail->prev);
    }

    this->addNode(new node<K, V>(key_, value));
    this->m[key_] = this->head->next;
}

template <typename K, typename V>
FIFOCache<K, V>::FIFOCache(int capacity) : Cache<K, V>(capacity) {}

template <typename K, typename V>
V FIFOCache<K, V>::get(K key_)
{
    std::shared_lock<std::shared_mutex> lock(this->mutex_);
    if (this->m.find(key_) != this->m.end())
    {
        node<K, V> *resnode = this->m[key_];
        return resnode->val;
    }
    return V();
}

template <typename K, typename V>
void FIFOCache<K, V>::put(K key_, V value)
{
    std::unique_lock<std::shared_mutex> uniquelock(this->mutex_);
    if (this->m.find(key_) != this->m.end())
    {
        node<K, V> *existingNode = this->m[key_];
        this->m.erase(key_);
        this->deleteNode(existingNode);
    }
    if (this->m.size() == this->cap)
    {
        this->m.erase(this->tail->prev->key);
        this->deleteNode(this->tail->prev);
    }

    this->addNode(new node<K, V>(key_, value));
    this->m[key_] = this->tail->prev;
}

template <typename K, typename V>
LIFOCache<K, V>::LIFOCache(int capacity) : Cache<K, V>(capacity) {}

template <typename K, typename V>
V LIFOCache<K, V>::get(K key_)
{
    std::shared_lock<std::shared_mutex> lock(this->mutex_);
    if (this->m.find(key_) != this->m.end())
    {
        node<K, V> *resnode = this->m[key_];
        return resnode->val;
    }
    return V();
}

template <typename K, typename V>
void LIFOCache<K, V>::put(K key_, V value)
{
    std::unique_lock<std::shared_mutex> uniquelock(this->mutex_);
    if (this->m.find(key_) != this->m.end())
    {
        node<K, V> *existingNode = this->m[key_];
        this->m.erase(key_);
        this->deleteNode(existingNode);
    }
    if (this->m.size() == this->cap)
    {
        this->m.erase(this->head->next->key);
        this->deleteNode(this->head->next);
    }

    this->addNode(new node<K, V>(key_, value));
    this->m[key_] = this->head->next;
}
