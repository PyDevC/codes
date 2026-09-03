#include <vector>

class LRUCache {
public:
    LRUCache(int capacity) {
        std::vector<int> cache(capacity, -1);
        std::vector<int> recent(capacity, -1);
    }
    
    int get(int key) {
    }
    
    void put(int key, int value) {
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
