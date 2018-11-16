#include <iostream>
#include <map>
using namespace std;
int main()
{
    map<int, int> m;
    m[0] = 10;
    m[10] = 0;
    for(auto i = m.begin(); i != m.end(); i++)
        cout << i->first << " " << i->second << endl;
    return 0;
}