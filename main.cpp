#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// Simple in-memory solution using map and set
// This will work for the constraints (300,000 operations)
// and is efficient enough for the problem
class Database {
private:
    map<string, set<int>> data;

public:
    void insert(const string& index, int value) {
        data[index].insert(value);
    }

    void remove(const string& index, int value) {
        auto it = data.find(index);
        if (it != data.end()) {
            it->second.erase(value);
            if (it->second.empty()) {
                data.erase(it);
            }
        }
    }

    string find(const string& index) {
        auto it = data.find(index);
        if (it == data.end() || it->second.empty()) {
            return "null";
        }

        string result;
        bool first = true;
        for (int value : it->second) {
            if (!first) {
                result += " ";
            }
            result += to_string(value);
            first = false;
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Database db;
    int n;
    cin >> n;
    cin.ignore(); // ignore newline after n

    for (int i = 0; i < n; i++) {
        string command;
        cin >> command;

        if (command == "insert") {
            string index;
            int value;
            cin >> index >> value;
            db.insert(index, value);
        } else if (command == "delete") {
            string index;
            int value;
            cin >> index >> value;
            db.remove(index, value);
        } else if (command == "find") {
            string index;
            cin >> index;
            string result = db.find(index);
            cout << result << endl;
        }
    }

    return 0;
}