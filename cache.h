#ifndef CACHE_H
#define CACHE_H

#include <bits/stdc++.h>
#include <string>
#include <shared_mutex>
#include <mutex>
#include <thread>

template <typename K, typename V>
class node
{
public:
    K key;
    V val;
    node *next;
    node *prev;
    node(K _key, V _val)
    {
        key = _key;
        val = _val;
    }
};

template <typename K, typename V>
class Cache
{
public:
    virtual V get(K _key) = 0;
    virtual void put(K key_, V value) = 0;

    int cap;
    std::unordered_map<K, node<K, V> *> m;
    node<K, V> *head;
    node<K, V> *tail;
    mutable std::shared_mutex mutex_;

    Cache(int capacity);
    void addNode(node<K, V> *newnode);
    void deleteNode(node<K, V> *delnode);
};

template <typename K, typename V>
class LRUCache : public Cache<K, V>
{
public:
    LRUCache(int capacity);
    V get(K key_) override;
    void put(K key_, V value) override;
};

template <typename K, typename V>
class FIFOCache : public Cache<K, V>
{
public:
    FIFOCache(int capacity);
    V get(K key_) override;
    void put(K key_, V value) override;
};

template <typename K, typename V>
class LIFOCache : public Cache<K, V>
{
public:
    LIFOCache(int capacity);
    V get(K key_) override;
    void put(K key_, V value) override;
};

#include "cache.tpp"

#endif // CACHE_H
