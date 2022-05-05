#include "NotSimpleVector.h"
#include <iostream>
using namespace std;

template class NotSimpleVector<int>;

int main()
{
    NotSimpleVector<int> a;
    int n;
    cin >> n;
    int x;
    for(int i = 0; i < n; ++i)
    {
        cin >> x;
        a.push_back(x);
    }
    a.erase(a.begin());
    for(int el : a)
        cout << el << ' ';
}
