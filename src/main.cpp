#include "tree.hpp"

int main()
{
    tree<int> t;
    t.insert(7);
    t.insert(15);
    t.insert(4);
    t.insert(20);
    t.insert(10);
    t.insert(73);
    t.insert(17);
    t.insert(120);
    t.insert(23);
    t.insert(16);
    std::cout << "In-order traverse is     : ";
    t.in_order();
    std::cout << std::endl;
    std::cout << "Pre-order traverse is    : ";
    t.pre_order();
    std::cout << std::endl;
    std::cout << "Post-order traverse is   : ";
    t.post_order();
    std::cout << std::endl;
    t.level_order();
    t.remove(15);
    std::cout << "15 deleted" << std::endl;
    std::cout << "Pre-order traverse is    : ";
    t.pre_order();
    std::cout << std::endl;
    if (t.search(11)) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }
    std::cout << "Depth of the tree is: " << t.max_depth() << std::endl;
}
