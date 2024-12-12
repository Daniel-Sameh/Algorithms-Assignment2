#include <bits/stdc++.h>
using namespace std;

// (a) Division Method
int divisionHash(int key, int tableSize)
{
    return key % tableSize;
}

// (b) Multiplication Method
int multiplicationHash(int key, int tableSize)
{
    double A = 0.555; // A constant between 0 and 1
    double fractionalPart = key * A - int(key * A);
    return int(tableSize * fractionalPart);
}

// (c) Mid Square Method
int midSquareHash(int key, int tableSize)
{
    int digits = to_string(tableSize - 1).length();
    string str = to_string(key * key); // 6  123456
    int mid = 0;
    if (str.length() >= digits)
    {
        mid = stoi(str.substr(str.length() / 2 - digits / 2, digits));
    }
    else
    {
        mid = key * key;
    }
    return mid % tableSize;
}

// (d) Folding Method
int foldingHash(int key, int tableSize)
{
    int sum = 0;
    while (key > 0)
    {
        sum += key % 100; // Extract last two digits
        key /= 100;
    }
    return sum % tableSize;
}

// (a) Chaining Method
class ChainingHashTable
{
    vector<list<int>> table;
    int tableSize;

public:
    ChainingHashTable(int size) : tableSize(size), table(size) {}

    void insert(int key)
    {
        int index = divisionHash(key, tableSize);
        table[index].push_back(key);
    }

    bool search(int key)
    {
        int index = divisionHash(key, tableSize);
        for (int item : table[index])
        {
            if (item == key)
                return true;
        }
        return false;
    }

    bool remove(int key)
    {
        int index = divisionHash(key, tableSize);
        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        {
            if (*it == key)
            {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }
};

// (b) Open Addressing Method
class OpenAddressingHashTable
{
    vector<int> table;
    int tableSize;
    const int DELETED = -2; // Mark for deleted elements

public:
    OpenAddressingHashTable(int size) : tableSize(size), table(size, -1) {}

    void insert(int key)
    {
        int index = divisionHash(key, tableSize);
        while (table[index] != -1 && table[index] != DELETED)
        { // Linear probing
            index = (index + 1) % tableSize;
        }
        table[index] = key;
    }

    bool search(int key)
    {
        int index = divisionHash(key, tableSize);
        int startIndex = index;
        while (table[index] != -1)
        {
            if (table[index] == key)
                return true;
            index = (index + 1) % tableSize;
            if (index == startIndex)
                break; // Loop detected
        }
        return false;
    }

    bool remove(int key)
    {
        int index = divisionHash(key, tableSize);
        int startIndex = index;

        while (table[index] != -1)
        {
            if (table[index] == key)
            {
                table[index] = DELETED; // Mark as deleted
                return true;
            }
            index = (index + 1) % tableSize;
            if (index == startIndex)
                break; // Loop detected
        }
        return false;
    }
};

// (c) Double Hashing
class DoubleHashingHashTable
{
    vector<int> table;
    int tableSize;
    const int DELETED = -2; // Mark for deleted elements

    int hash2(int key)
    {
        return 1 + (key % (tableSize - 1));
    }

public:
    DoubleHashingHashTable(int size) : tableSize(size), table(size, -1) {}

    void insert(int key)
    {
        int index = divisionHash(key, tableSize);
        int step = multiplicationHash(key, tableSize);

        while (table[index] != -1 && table[index] != DELETED)
        {
            index = (index + step) % tableSize;
        }
        table[index] = key;
    }

    bool search(int key)
    {
        int index = divisionHash(key, tableSize);
        int step = multiplicationHash(key, tableSize);
        int startIndex = index;

        while (table[index] != -1)
        {
            if (table[index] == key)
                return true;
            index = (index + step) % tableSize;
            if (index == startIndex)
                break; // Loop detected
        }
        return false;
    }

    bool remove(int key)
    {
        int index = divisionHash(key, tableSize);
        int step = multiplicationHash(key, tableSize);
        int startIndex = index;

        while (table[index] != -1)
        {
            if (table[index] == key)
            {
                table[index] = DELETED; // Mark as deleted
                return true;
            }
            index = (index + step) % tableSize;
            if (index == startIndex)
                break; // Loop detected
        }
        return false;
    }
};

// (d) Quadratic Probing
class QuadraticProbingHashTable
{
    vector<int> table;
    int tableSize;
    const int DELETED = -2; // Mark for deleted elements

public:
    QuadraticProbingHashTable(int size) : tableSize(size), table(size, -1) {}

    void insert(int key)
    {
        int index = divisionHash(key, tableSize);
        int i = 0; // Quadratic probing increment

        while (table[index] != -1 && table[index] != DELETED)
        {
            i++;
            index = (divisionHash(key, tableSize) + i * i) % tableSize; // Quadratic probing
            if (i >= tableSize)
            { // If we've tried all possible positions
                cout << "Table is full or no valid position found for " << key << "\n";
                return;
            }
        }
        table[index] = key;
    }

    bool search(int key)
    {
        int index = divisionHash(key, tableSize);
        int i = 0;
        int startIndex = index;

        do
        {
            if (table[index] == key)
                return true;
            if (table[index] == -1)
                return false; // Empty slot means key not found

            i++;
            index = (divisionHash(key, tableSize) + i * i) % tableSize;
        } while (index != startIndex && i < tableSize);

        return false;
    }

    bool remove(int key)
    {
        int index = divisionHash(key, tableSize);
        int i = 0;
        int startIndex = index;

        do
        {
            if (table[index] == key)
            {
                table[index] = DELETED;
                return true;
            }
            if (table[index] == -1)
                return false; // Empty slot means key not found

            i++;
            index = (divisionHash(key, tableSize) + i * i) % tableSize;
        } while (index != startIndex && i < tableSize);

        return false;
    }

    void display()
    {
        cout << "Hash Table Contents:\n";
        for (int i = 0; i < tableSize; i++)
        {
            cout << i << ": ";
            if (table[i] == -1)
                cout << "Empty";
            else if (table[i] == DELETED)
                cout << "Deleted";
            else
                cout << table[i];
            cout << "\n";
        }
    }
};

int main()
{
    int tableSize = 10;

    // Test Chaining Hash Table
    ChainingHashTable chainingTable(tableSize);
    cout << "Testing Chaining Hash Table:\n";
    chainingTable.insert(5);
    chainingTable.insert(15);
    chainingTable.insert(25);
    cout << "Search for 15: " << (chainingTable.search(15) ? "Found" : "Not Found") << "\n";
    cout << "Delete 15: " << (chainingTable.remove(15) ? "Deleted" : "Not Found") << "\n";
    cout << "Search for 15 after deletion: " << (chainingTable.search(15) ? "Found" : "Not Found") << "\n\n";

    // Test Open Addressing Hash Table (Linear Probing)
    OpenAddressingHashTable openTable(tableSize);
    cout << "Testing Open Addressing Hash Table (Linear Probing):\n";
    openTable.insert(5);
    openTable.insert(15);
    openTable.insert(25);
    cout << "Search for 15: " << (openTable.search(15) ? "Found" : "Not Found") << "\n";
    cout << "Delete 15: " << (openTable.remove(15) ? "Deleted" : "Not Found") << "\n";
    cout << "Search for 15 after deletion: " << (openTable.search(15) ? "Found" : "Not Found") << "\n";
    cout << "Insert 35 in freed space: ";
    openTable.insert(35);
    cout << (openTable.search(35) ? "Successful" : "Failed") << "\n\n";

    // Test Quadratic Probing Hash Table
    QuadraticProbingHashTable quadTable(tableSize);
    cout << "Testing Quadratic Probing Hash Table:\n";
    cout << "Initial table:\n";
    quadTable.display();
    cout << "\nInserting 5, 15, 25, 35:\n";
    quadTable.insert(5);
    quadTable.insert(15);
    quadTable.insert(25);
    quadTable.insert(35);
    quadTable.display();
    cout << "\nSearch for 15: " << (quadTable.search(15) ? "Found" : "Not Found") << "\n";
    cout << "Delete 15: " << (quadTable.remove(15) ? "Deleted" : "Not Found") << "\n";
    cout << "Table after deleting 15:\n";
    quadTable.display();
    cout << "\nSearch for 15 after deletion: " << (quadTable.search(15) ? "Found" : "Not Found") << "\n";
    cout << "Insert 45 in freed space:\n";
    quadTable.insert(45);
    quadTable.display();
    cout << "\n";

    // Test Double Hashing Hash Table
    DoubleHashingHashTable doubleTable(tableSize);
    cout << "Testing Double Hashing Hash Table:\n";
    doubleTable.insert(5);
    doubleTable.insert(15);
    doubleTable.insert(25);
    cout << "Search for 15: " << (doubleTable.search(15) ? "Found" : "Not Found") << "\n";
    cout << "Delete 15: " << (doubleTable.remove(15) ? "Deleted" : "Not Found") << "\n";
    cout << "Search for 15 after deletion: " << (doubleTable.search(15) ? "Found" : "Not Found") << "\n";
    cout << "Insert 35 in freed space: ";
    doubleTable.insert(35);
    cout << (doubleTable.search(35) ? "Successful" : "Failed") << "\n";

    return 0;
}