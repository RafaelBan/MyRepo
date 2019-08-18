#ifndef MAIN_VIEW_CONTAINER_H_
#define MAIN_VIEW_CONTAINER_H_

#include <vector>
#include "MainView.h"

class MainViewContainer
{
    using BaseContainer = typename std::vector<MainView *>;

public:
    using iterator = typename BaseContainer::iterator;
    using const_iterator = typename BaseContainer::const_iterator;

    void append(MainView *view) { storage.push_back(view); }

    iterator remove(iterator pos) { return storage.erase(pos); }
    iterator remove(const_iterator pos) { return storage.erase(pos); }

    iterator begin() { return storage.begin(); }
    const_iterator begin() const { return storage.begin(); }
    const_iterator cbegin() const { return storage.cbegin(); }

    iterator end() { return storage.end(); }
    const_iterator end() const { return storage.end(); }
    const_iterator cend() const { return storage.cend(); }

private:
    BaseContainer storage;
};

#endif // MAIN_VIEW_CONTAINER_H_

