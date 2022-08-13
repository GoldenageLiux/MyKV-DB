/**
 * @Author: liuxin
 * @Date:   2022-08-12 15:11:54
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-08-13 15:45:05
 */
#include <iostream>
#include "skiplist.h"

using namespace std;


int main(int argc, char const *argv[])
{
    /* code */

    Skiplist<int, std::string> skiplist(5);
    
    // Skiplist<std::string, std::string> skiplist(5);
    
    skiplist.loadFromFile();
    // skiplist.insert_element(1, "1");
    // skiplist.insert_element(2, "12");
    // skiplist.insert_element(3, "123");
    // skiplist.insert_element(4, "1234");
    // skiplist.insert_element(5, "12345");
    skiplist.search_element(1);
    skiplist.search_element(7);
    skiplist.delete_element(5);
    skiplist.delete_element(6);
    skiplist.display_list();
    skiplist.dumpToFile();
    return 0;
}
