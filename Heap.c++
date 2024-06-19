#include <iostream>
#include <vector>
#include <unordered_map>

template<typename T>
class Heap {
private:
    std::vector<T> data;
    std::unordered_map<T, int> map;

    void upheapify(int ci) {
        int pi = (ci - 1) / 2;
        if (ci > 0 && isLarger(data[ci], data[pi]) > 0) {
            swap(pi, ci);
            upheapify(pi);
        }
    }

    void downheapify(int pi) {
        int lci = 2 * pi + 1;
        int rci = 2 * pi + 2;
        int mini = pi;
        int size = data.size();

        if (lci < size && isLarger(data[lci], data[mini]) > 0) {
            mini = lci;
        }

        if (rci < size && isLarger(data[rci], data[mini]) > 0) {
            mini = rci;
        }

        if (mini != pi) {
            swap(mini, pi);
            downheapify(mini);
        }
    }

    void swap(int i, int j) {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;

        map[data[i]] = i;
        map[data[j]] = j;
    }

    int isLarger(T t, T o) {
        // Assuming T has operator> overloaded or is Comparable
        return (t > o) ? 1 : ((t == o) ? 0 : -1);
    }

public:
    void add(T item) {
        data.push_back(item);
        map[item] = data.size() - 1;
        upheapify(data.size() - 1);
    }

    void display() {
        for (const auto &item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    int size() {
        return data.size();
    }

    bool isEmpty() {
        return data.empty();
    }

    T remove() {
        swap(0, data.size() - 1);
        T rv = data.back();
        data.pop_back();
        downheapify(0);

        map.erase(rv);
        return rv;
    }

    T get() {
        return data.front();
    }

    void updatePriority(T pair) {
        int index = map[pair];
        upheapify(index);
    }
};
