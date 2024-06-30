#ifndef DYNAMICLIST_HPP
#define DYNAMICLIST_HPP

#include <vector>
#include <algorithm> //for find

template <typename T>
class DynamicList {
private:
    std::vector<T> items;
    
public:
    void add(T item) { // add something
        items.push_back(item); 
    }

    void remove(T item) {
        auto thing = std::find(items.begin(), items.end(), item); 
        if (thing != items.end()) { // check if thing is in vector
            items.erase(thing); // then get rid of it!
        }
    }

    std::vector<T> getItems() const {
        return items; // give back stuff in vector
    }
};

#endif
