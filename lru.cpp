#include <iostream>
#include <unordered_map>
#include <list>

class MFU {
private:
    struct Page {
        int key;
        int value;
        int frequency;
        std::list<int>::iterator frequencyIt;

        Page(int k, int v, const std::list<int>::iterator& it)
            : key(k), value(v), frequency(0), frequencyIt(it) {}
    };

    int capacity;
    std::unordered_map<int, Page> cache;
    std::unordered_map<int, std::list<int>> frequencyMap;

public:
    MFU(int cap) : capacity(cap) {}

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;  // 页面不存在
        }

        auto& page = cache[key];
        int value = page.value;
        int frequency = page.frequency;

        // 更新页面的访问频率
        frequencyMap[frequency].erase(page.frequencyIt);
        if (frequencyMap[frequency].empty()) {
            frequencyMap.erase(frequency);
        }

        ++frequency;
        frequencyMap[frequency].push_front(key);
        page.frequency = frequency;
        page.frequencyIt = frequencyMap[frequency].begin();

        return value;
    }

    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }

        if (get(key) != -1) {
            // 页面已存在，更新值即可
            cache[key].value = value;
            return;
        }

        if (cache.size() >= capacity) {
            // 达到缓存容量上限，淘汰最经常使用的页面
            auto& pageList = frequencyMap.rbegin()->second;
            int lastKey = pageList.back();
            pageList.pop_back();
            cache.erase(lastKey);
            if (pageList.empty()) {
                frequencyMap.erase(frequencyMap.rbegin()->first);
            }
        }

        // 插入新的页面到频率为1的列表中
        frequencyMap[1].push_front(key);
        cache[key] = {key, value, 1, frequencyMap[1].begin()};
    }
};

int main() {
    MFU cache(2);  // 创建容量为2的MFU缓存

    cache.put(1, 10);
    cache.put(2, 20);

    std::cout << cache.get(1) << std::endl;  // 输出: 10

    cache.put(3, 30);  // 缓存已满，会淘汰访问频率最高的缓存项(1, 10)

    std::cout << cache.get(1) << std::endl;  // 输出: -1

    return 0;
}
