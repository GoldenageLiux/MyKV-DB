/**
 * @Author: liuxin
 * @Date:   2022-07-31 12:03:25
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-08-10 11:26:56
 */
#include <stdint.h>
#include "node.h"

#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

template<typename K, typename V>
class Skiplist
{
private:
    /* data */
    int max_level;
    int current_level;
    Node<K, V> *header;
    int element_count;

    /* method */
    void getKeyAndValueFromStr(const std::string& str, std::string& key, std::string& value);
    bool isValidStr(const std::string& str);

public:
    Skiplist(int);
    ~Skiplist();

    Node<K, V>* create_node(K, V, int);
    int insert_element(K, V);
    bool search_element(K);
    void delete_element(K);
    void display_list();

    int getRandomLevel();
    void dumpToFile();
    void loadFromFile();
    int getSkipListSize();
};

template<typename K, typename V>
Skiplist<K, V>::Skiplist(int)
{

}

template<typename K, typename V>
Skiplist<K, V>::~Skiplist()
{

}


#endif /* __SKIPLIST_H__ */
