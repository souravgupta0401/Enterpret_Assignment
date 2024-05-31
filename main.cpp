#include <iostream>
#include "cache.h"
using namespace std;
int main()
{
    int option;
    cout << "Enter the Eviction Policy you want to implement:" << endl
              << "1.FIFO" << endl
              << "2.LRU" << endl
              << "3.LIFO" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
    {
        int element;
        FIFOCache<int, int> fifocache(2);
        fifocache.put(1, 1);        // 1
        fifocache.put(2, 2);        // 2 1
        element = fifocache.get(1); // 2 1
        cout << element << " ";
        fifocache.put(3, 3);        // 3 2
        element = fifocache.get(2); // 2
        cout << element << " ";
        fifocache.put(4, 4); // 4 3
        element = fifocache.get(1);
        cout << element << " ";
        element = fifocache.get(3); // 3
        cout << element << " ";
        element = fifocache.get(4); // 4
        cout << element << " ";
        break;
    }

    case 2:
         {
        int element;
        LRUCache<int, int> lruCache(2);
        lruCache.put(1, 1);        // 1
        lruCache.put(2, 2);        // 2 1
        element = lruCache.get(1); // 1 2
        cout << element << " ";
        lruCache.put(3, 3);        // 3 1
        element = lruCache.get(2); // 3 1
        cout << element << " ";
        lruCache.put(4, 4); // 4 3
        element = lruCache.get(1);
        cout << element << " ";
        element = lruCache.get(3); // 3 4
        cout << element << " ";
        element = lruCache.get(4); // 4 3
        cout << element << " ";
        break;
    }

    case 3:
    {
        int element;
        LIFOCache<int, int> lifocache(2);
        lifocache.put(1, 1);        // 1
        lifocache.put(2, 2);        // 2 1
        element = lifocache.get(1); // 1
        cout << element << " ";
        lifocache.put(3, 3);        // 3 1
        element = lifocache.get(2); //-1
        cout << element << " ";
        lifocache.put(4, 4);        // 4 1
        element = lifocache.get(1); // 1
        cout << element << " ";
        element = lifocache.get(3); // -1
        cout << element << " ";
        element = lifocache.get(4); // 4
        cout << element << " ";
        break;
    }

    default:
        cout << "Enter valid option!";
    }

    return 0;
}


