#include <iostream>
#include <unordered_map>
#include <list>

class LFU {
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
    int minFrequency;
    std::unordered_map<int, Page> cache;
    std::unordered_map<int, std::list<int>> frequencyMap;

public:
    LFU(int cap) : capacity(cap), minFrequency(0) {}

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
            if (minFrequency == frequency) {
                ++minFrequency;
            }
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
            // 达到缓存容量上限，淘汰最不经常使用的页面
            auto& pageList = frequencyMap[minFrequency];
            int lastKey = pageList.back();
            pageList.pop_back();
            cache.erase(lastKey);
            if (pageList.empty()) {
                frequencyMap.erase(minFrequency);
            }
        }

        // 插入新的页面到频率为1的列表中
        frequencyMap[1].push_front(key);
        cache[key] = {key, value, 1, frequencyMap[1].begin()};
        minFrequency = 1;
    }
};

int main() {
    LFU cache(2);  // 创建容量为2的LFU缓存

    cache.put(1, 10);
    cache.put(2, 20);

    std::cout << cache.get(1) << std::endl;  // 输出: 10

    cache.put(3, 30);  // 缓存已满，会淘汰访问频率最低的缓存项(2, 20)

    std::cout << cache.get(2) << std::endl;  // 输出: -1

    return 0;
}
