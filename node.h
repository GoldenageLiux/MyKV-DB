/**
 * @Author: liuxin
 * @Date:   2022-08-09 11:09:38
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-08-09 11:14:35
 */
#include <stdint.h>

#ifndef __NODE_H__
#define __NODE_H__

template <typename K, typename V>
class Node
{
    
private:
    K key;
    V value;

public:
    Node() {}
    Node(K k, V v, int);
    ~Node();
};

template <typename K, typename V>
Node<K, V>::Node(const K k, const V v, int level)
{

}

template <typename K, typename V>
Node<K, V>::~Node()
{

}


#endif /* __NODE_H__ */
