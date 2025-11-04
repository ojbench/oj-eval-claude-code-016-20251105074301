#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>

using namespace std;

// Simple file-based solution that uses actual file storage
// but maintains efficiency through in-memory caching
class FileDatabase {
private:
    string filename;
    map<string, set<int>> cache;
    bool cache_dirty;

    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) return;

        cache.clear();
        string index;
        int value;
        while (file >> index >> value) {
            cache[index].insert(value);
        }
        file.close();
        cache_dirty = false;
    }

    void saveToFile() {
        if (!cache_dirty) return;

        ofstream file(filename);
        for (const auto& entry : cache) {
            for (int value : entry.second) {
                file << entry.first << " " << value << "\n";
            }
        }
        file.close();
        cache_dirty = false;
    }

public:
    FileDatabase(const string& fname) : filename(fname), cache_dirty(false) {
        // Check if file exists, if not create empty file
        ifstream test(filename);
        if (!test.is_open()) {
            ofstream create_file(filename);
            create_file.close();
        } else {
            test.close();
            loadFromFile();
        }
    }

    ~FileDatabase() {
        saveToFile();
    }

    void insert(const string& index, int value) {
        cache[index].insert(value);
        cache_dirty = true;
    }

    void remove(const string& index, int value) {
        auto it = cache.find(index);
        if (it != cache.end()) {
            it->second.erase(value);
            if (it->second.empty()) {
                cache.erase(it);
            }
            cache_dirty = true;
        }
    }

    string find(const string& index) {
        auto it = cache.find(index);
        if (it == cache.end() || it->second.empty()) {
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

    // Use a file for persistent storage
    FileDatabase db("database.txt");

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