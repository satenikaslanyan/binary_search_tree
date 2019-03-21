#include "tree.hpp"

int main()
{
    tree<int> t;
    t.insert(7);
    t.insert(15);
    t.insert(4);
    t.insert(73);
    t.insert(120);
    t.insert(20);
    std::cout << "In-order traverse is   : ";
    t.in_order();
    std::cout << std::endl;
    std::cout << "Pre-order traverse is  : ";
    t.pre_order();
    std::cout << std::endl;
    std::cout << "Post-order traverse is : ";
    t.post_order();
    std::cout << std::endl;
    if (t.find(11)) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
}
