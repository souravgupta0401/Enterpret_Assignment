#include <iostream>
#include "cache.h"

using namespace std;

int main()
{
    int option;
    cout << "Enter the Eviction Policy you want to implement:" << endl
         << "1. FIFO" << endl
         << "2. LRU" << endl
         << "3. LIFO" << endl;
    cin >> option;

    switch (option)
    {
    case 1:
    {
        int element;
        FIFOCache<int, int> fifoCache(2, -1); // Capacity 2, default value -1
        fifoCache.put(1, 1);                  // 1
        fifoCache.put(2, 2);                  // 2 1
        element = fifoCache.get(1);           // 2 1
        cout << element << " ";               // Output: 1
        fifoCache.put(3, 3);                  // 3 2
        element = fifoCache.get(2);           // 2
        cout << element << " ";               // Output: 2
        fifoCache.put(4, 4);                  // 4 3
        element = fifoCache.get(1);           // -1 (cache miss)
        cout << element << " ";               // Output: -1
        element = fifoCache.get(3);           // 3
        cout << element << " ";               // Output: 3
        element = fifoCache.get(4);           // 4
        cout << element << " ";               // Output: 4
        break;
    }

    case 2:
    {
        int element;
        LRUCache<int, int> lruCache(2, -1); // Capacity 2, default value -1
        lruCache.put(1, 1);                 // 1
        lruCache.put(2, 2);                 // 2 1
        element = lruCache.get(1);          // 1 2
        cout << element << " ";             // Output: 1
        lruCache.put(3, 3);                 // 3 1
        element = lruCache.get(2);          // -1 (cache miss)
        cout << element << " ";             // Output: -1
        lruCache.put(4, 4);                 // 4 3
        element = lruCache.get(1);          // -1 (cache miss)
        cout << element << " ";             // Output: -1
        element = lruCache.get(3);          // 3 4
        cout << element << " ";             // Output: 3
        element = lruCache.get(4);          // 4 3
        cout << element << " ";             // Output: 4
        break;
    }

    case 3:
    {
        int element;
        LIFOCache<int, int> lifoCache(2, -1); // Capacity 2, default value -1
        lifoCache.put(1, 1);                  // 1
        lifoCache.put(2, 2);                  // 2 1
        element = lifoCache.get(1);           // 1
        cout << element << " ";               // Output: 1
        lifoCache.put(3, 3);                  // 3 1
        element = lifoCache.get(2);           // -1 (cache miss)
        cout << element << " ";               // Output: -1
        lifoCache.put(4, 4);                  // 4 1
        element = lifoCache.get(1);           // 1
        cout << element << " ";               // Output: 1
        element = lifoCache.get(3);           // -1 (cache miss)
        cout << element << " ";               // Output: -1
        element = lifoCache.get(4);           // 4
        cout << element << " ";               // Output: 4
        break;
    }

    default:
        cout << "Enter valid option!";
    }

    return 0;
}
