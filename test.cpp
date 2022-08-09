#include "node.h"
#include<iostream>

int main() {
    Node<int, std::string> *n = new Node<int, std::string>(1, "2", 3);
    std::cout << n->get_key() << n->get_value() << std::endl;
    n->set_value("234");
    std::cout << n->get_key() << n->get_value() << std::endl;
}