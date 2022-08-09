/**
 * @Author: liuxin
 * @Date:   2022-08-09 11:09:38
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-08-09 11:14:35
 */
#include <stdint.h>
#include <cstring>

#ifndef __NODE_H__
#define __NODE_H__

template <typename K, typename V>
class Node
{
    
private:
    K key;
    V value;

public:
    Node();
    Node(K k, V v, int);
    ~Node();

    K get_key() const;
    V get_value() const;
    void set_value(V);

    Node<K, V> **forward;

    int node_level;

};

template <typename K, typename V>
Node<K, V>::Node(const K k, const V v, int level)
{
    this->key = k;
    this->value = v;
    this->node_level = level;
    this->forward = new Node<K, V> *[level+1];

    memset(this->forward, 0, sizeof(Node<K, V>*) * (level+1));
}

template <typename K, typename V>
Node<K, V>::~Node()
{
    delete []forward;
}

template <typename K, typename V>
K Node<K, V>::get_key() const
{
    return key;
}

template <typename K, typename V>
V Node<K, V>::get_value() const
{
    return value;
}

template <typename K, typename V>
void Node<K, V>::set_value(V value)
{
    this->value = value;
}



#endif /* __NODE_H__ */
