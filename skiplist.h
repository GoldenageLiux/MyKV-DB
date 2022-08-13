/**
 * @Author: liuxin
 * @Date:   2022-07-31 12:03:25
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-08-13 16:15:20
 */
#include <stdint.h>
#include <fstream>
#include <mutex>
#include "node.h"

#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#define DUMPFIEL "store/dumpFile"
std::mutex mtx;
template<typename K, typename V>
class Skiplist
{
private:
    /* data */
    int max_level;
    int current_level;
    Node<K, V> *header;
    int element_count;
    // file operator
    std::ofstream file_writer;
    std::ifstream file_reader;

    /* method */
    void getKeyAndValueFromStr(const std::string& str, std::string* key, std::string* value);
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
Skiplist<K, V>::Skiplist(int max_level) {
    this->max_level = max_level;
    this->current_level = 0;
    this->element_count = 0;
    K k;
    V v;
    this->header = new Node<K, V>(k, v, max_level);
}

template<typename K, typename V>
Skiplist<K, V>::~Skiplist() {
    if (file_writer.is_open()) {
        file_writer.close();
    }
    if (file_reader.is_open()) {
        file_reader.close();
    }
    delete header;
}

// create new node 
template<typename K, typename V>
Node<K, V>* Skiplist<K, V>::create_node(const K k, const V v, int level) {
    Node<K, V> *n = new Node<K, V>(k, v, level);
    return n;
}

template<typename K, typename V>
int Skiplist<K, V>::insert_element(const K key, const V value) {
    mtx.lock();
    Node<K, V> *current = this->header;

    // create update array and initialize it 
    // update is array which put node that the node->forward[i] should be operated later
    Node<K, V> *update[max_level+1];
    memset(update, 0, sizeof(Node<K, V>*)*(max_level+1));  

    // start form highest level of skip list 
    for(int i = current_level; i >= 0; i--) {
        while(current->forward[i] != NULL && current->forward[i]->get_key() < key) {
            current = current->forward[i]; 
        }
        update[i] = current;
    }

    // reached level 0 and forward pointer to right node, which is desired to insert key.
    current = current->forward[0];

    // if current node have key equal to searched key, we get it
    if (current != NULL && current->get_key() == key) {
        std::cout << "key: " << key << ", exists" << std::endl;
        mtx.unlock();
        return 1;
    }

    // two cases:
    // 1) if current is NULL that means we have reached to end of the level 
    // 2) if current's key is not equal to key that means we have to insert node between update[0] and current node 
    if (current == NULL || current->get_key() != key ) {
        
        // Generate a random level for node
        int random_level = getRandomLevel();

        // If random level is greater thar skip list's current level, initialize update value with pointer to header
        if (random_level > current_level) {
            for (int i = current_level+1; i < random_level+1; i++) {
                update[i] = header;
            }
            //update current level
            current_level = random_level;
        }

        // create new node with random level generated 
        Node<K, V>* inserted_node = create_node(key, value, random_level);
        
        // insert node 
        for (int i = 0; i <= random_level; i++) {
            inserted_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = inserted_node;
        }
        std::cout << "Successfully inserted element with key:" << key << ", value:" << value << std::endl;
        element_count++;
    }
    mtx.unlock();
    return 0;
}

template<typename K, typename V>
void Skiplist<K, V>::delete_element(K key) {
    mtx.lock();
    Node<K, V> *current = this->header; 
    Node<K, V> *update[max_level+1];
    memset(update, 0, sizeof(Node<K, V>*)*(max_level+1));

    // start from highest level of skip list
    for (int i = current_level; i >= 0; i--) {
        while (current->forward[i] !=NULL && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];
    if (current != NULL && current->get_key() == key) {
       
        // start for lowest level and delete the current node of each level
        for (int i = 0; i <= current_level; i++) {

            // if at level i, next node is not target node, break the loop.
            if (update[i]->forward[i] != current) 
                break;

            update[i]->forward[i] = current->forward[i];
        }

        // Remove levels which have no elements
        while (current_level > 0 && header->forward[current_level] == nullptr) {
            current_level --; 
        }

        std::cout << "Successfully deleted element with key:"<< key << std::endl;
        current_level--;
        
        mtx.unlock();
        return;
    }
    std::cout << "Failed deleted, No element with key: "<< key << std::endl;
    mtx.unlock();
    return;
}

template<typename K, typename V>
bool Skiplist<K, V>::search_element(K key) {
    Node<K, V> *current = this->header; 

    // start from highest level of skip list
    for (int i = current_level; i >= 0; i--) {
        while (current->forward[i] !=NULL && current->forward[i]->get_key() < key) {
            current = current->forward[i];
        }
    }

    current = current->forward[0];
    if (current != NULL && current->get_key() == key) {

        std::cout << "Successfully found element with key:"<< key << ", value:"<< current->get_value() << std::endl;
        return true;
    }
    std::cout << "Failed searched, No element with key: "<< key << std::endl;
    return false;
}

template<typename K, typename V>
void Skiplist<K, V>::display_list() {
    std::cout << "---Start display the SkipList---" << std::endl;
    for (int i = current_level; i > 0; i--) {
        Node<K, V> * node = this->header->forward[i];
        std::cout << "Level " << i << ": ";
        while (node != nullptr) {
            std::cout << node->get_key() << ":" << node->get_value() << "; ";
            node = node->forward[i];
        }
        std::cout << std::endl;
    }

    std::cout << "---Finish display the SkipList---\n" << std::endl;

}

template<typename K, typename V>
void Skiplist<K, V>::dumpToFile() {
    std::cout << "---Start dump data in memory to file---" << std::endl;
    file_writer.open(DUMPFIEL);
    Node<K, V> *node = this->header->forward[0];

    while (node != nullptr) {
        file_writer << node->get_key() << ":" << node->get_value() << "\n";
        std::cout << node->get_key() << ":" << node->get_value() << ";\n";
        node = node->forward[0];
    }

    file_writer.flush();
    file_writer.close();
    std::cout << "---Finish dump data in memory to file---\n" << std::endl;
    return;
}

template<typename K, typename V>
void Skiplist<K, V>::loadFromFile() {
    std::cout << "---Start load data from file---" << std::endl;
    file_reader.open(DUMPFIEL);

    std::string one_line;
    std::string* key = new std::string();
    std::string* value = new std::string();
    while (getline(file_reader, one_line)) {
        getKeyAndValueFromStr(one_line, key, value);
        if(key->empty() || value->empty()){
            continue;
        }
        int key_int = std::stoi(*key);
        insert_element(key_int, *value);
        // insert_element(*key, *value);
        // std::cout << "key:" << key << "value:" << *value << std::endl;
    }
    file_reader.close();
    std::cout << "---Finish load data from file---\n" << std::endl;
}

template<typename K, typename V>
void Skiplist<K, V>::getKeyAndValueFromStr(const std::string& str, std::string* key, std::string* value) {
    if(!isValidStr(str)) {
        return;
    }

    *key = str.substr(0, str.find(":"));
    *value = str.substr(str.find(":")+1, str.length());
}

template<typename K, typename V>
bool Skiplist<K, V>::isValidStr(const std::string& str) {
    if(str.empty()) {
        return false;
    }

    if(str.find(":") == std::string::npos) {
        return false;
    }
    return true;
}

template<typename K, typename V>
int Skiplist<K, V>::getRandomLevel() {
    int k = 1;
    while (rand() % 2) {
        k++;
    }
    k = (k < max_level) ? k : max_level;
    return k;
}



#endif /* __SKIPLIST_H__ */
