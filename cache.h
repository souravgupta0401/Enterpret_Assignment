#ifndef CACHE_H
#define CACHE_H

#include <bits/stdc++.h>

using namespace std;

template <typename K, typename V>
class node
{
public:
    K key;
    V val;
    node *next;
    node *prev;
    node(K _key, V _val) : key(_key), val(_val), next(nullptr), prev(nullptr) {}
};

template <typename K, typename V>
class Cache
{
public:
    virtual V get(K _key) = 0;
    virtual void put(K key_, V value) = 0;

    int cap;
    V default_value;
    unordered_map<K, node<K, V> *> m;
    node<K, V> *head;
    node<K, V> *tail;
    mutable shared_mutex mutex_;

    Cache(int capacity, V default_val) : cap(capacity), default_value(default_val)
    {
        head = new node<K, V>(K(), V());
        tail = new node<K, V>(K(), V());
        head->next = tail;
        tail->prev = head;
    }

    void addNode(node<K, V> *newnode)
    {
        node<K, V> *temp = head->next;
        newnode->next = temp;
        newnode->prev = head;
        head->next = newnode;
        temp->prev = newnode;
    }

    void deleteNode(node<K, V> *delnode)
    {
        node<K, V> *delprev = delnode->prev;
        node<K, V> *delnext = delnode->next;
        delprev->next = delnext;
        delnext->prev = delprev;
        delete delnode;
    }
};

template <typename K, typename V>
class LRUCache : public Cache<K, V>
{
public:
    LRUCache(int capacity, V default_val) : Cache<K, V>(capacity, default_val) {}

    V get(K key_) override
    {
        shared_lock<shared_mutex> lock(this->mutex_);
        if (this->m.find(key_) != this->m.end())
        {
            node<K, V> *resnode = this->m[key_];
            V res = resnode->val;
            lock.unlock();

            unique_lock<shared_mutex> uniquelock(this->mutex_);
            this->m.erase(key_);
            this->deleteNode(resnode);
            this->addNode(new node<K, V>(key_, res));
            this->m[key_] = this->head->next;
            return res;
        }

        return this->default_value;
    }

    void put(K key_, V value) override
    {
        unique_lock<shared_mutex> uniquelock(this->mutex_);
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
};

template <typename K, typename V>
class FIFOCache : public Cache<K, V>
{
public:
    FIFOCache(int capacity, V default_val) : Cache<K, V>(capacity, default_val) {}

    V get(K key_) override
    {
        shared_lock<shared_mutex> lock(this->mutex_);
        if (this->m.find(key_) != this->m.end())
        {
            node<K, V> *resnode = this->m[key_];
            return resnode->val;
        }
        return this->default_value;
    }

    void put(K key_, V value) override
    {
        unique_lock<shared_mutex> uniquelock(this->mutex_);
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
};

template <typename K, typename V>
class LIFOCache : public Cache<K, V>
{
public:
    LIFOCache(int capacity, V default_val) : Cache<K, V>(capacity, default_val) {}

    V get(K key_) override
    {
        shared_lock<shared_mutex> lock(this->mutex_);
        if (this->m.find(key_) != this->m.end())
        {
            node<K, V> *resnode = this->m[key_];
            return resnode->val;
        }
        return this->default_value;
    }

    void put(K key_, V value) override
    {
        unique_lock<shared_mutex> uniquelock(this->mutex_);
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
};

#endif // CACHE_H
