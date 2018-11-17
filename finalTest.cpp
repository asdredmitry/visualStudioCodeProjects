#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int> v;
    v.resize(1000);
    cout << v.capacity() << endl;
    for(int i = 0; i < 200; i++)
        v.push_back(i);
    cout << v.size() << " " << v.capacity() << endl;
    v.clear();
    cout << v.size() << " " << v.capacity() << endl;
    return 0;
}