#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <vector>

template<typename SomeType>
class Container
{
    using BaseStorage = typename std::vector<SomeType>;

public:
    using iterator = typename BaseStorage::iterator;
    using const_iterator = typename BaseStorage::const_iterator;

    void append(const SomeType &data) { storage.push_back(data); }

    iterator remove(iterator pos) { return storage.erase(pos); }
    iterator remove(const_iterator pos) { return storage.erase(pos); }

    iterator begin() { return storage.begin(); }
    const_iterator begin() const { return storage.begin(); }
    const_iterator cbegin() const { return storage.cbegin(); }

    iterator end() { return storage.end(); }
    const_iterator end() const { return storage.end(); }
    const_iterator cend() const { return storage.cend(); }

private:
    BaseStorage storage;
};

#endif // CONTAINER_H_

