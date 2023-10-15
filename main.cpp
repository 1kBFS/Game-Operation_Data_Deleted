#include <iostream>
#include <memory>
#include <vector>
struct Test{

};
int main() {
    std::vector<std::unique_ptr<Test>> v;
    auto it = v.begin();
    auto& a = *it;
    return 0;
}
