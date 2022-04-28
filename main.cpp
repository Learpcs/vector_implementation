#include "NotSimpleVector.h"
#include <iostream>
using namespace std;

int main()
{
    template <typename T>
    using myvector<T> = NotSimpleVector<T>;

    myvector<int> a;
    int n;
    cin >> n;
    int x;
    for(int i = 0; i < n; ++i)
    {
        cin >> x;
        a.push_back(x);
    }
    for(int el : a)
        cout << el << ' ';
}
