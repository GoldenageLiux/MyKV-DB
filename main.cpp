/**
 * @Author: liuxin
 * @Date:   2022-08-12 15:11:54
 * @Last Modified by:   liuxin
 * @Last Modified time: 2022-08-12 17:09:52
 */
#include <iostream>
#include "skiplist.h"

using namespace std;


int main(int argc, char const *argv[])
{
    /* code */

    Skiplist<int, std::string> skiplist(5);
    
    // Skiplist<std::string, std::string> skiplist(5);
    skiplist.insert_element(1, "1");
    skiplist.insert_element(1, "123");
    skiplist.dumpToFile();
    // skiplist.loadFromFile();
    return 0;
}
