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

    SomeType &operator[](size_t idx) { return storage[idx]; };

    void append(const SomeType &data) { storage.push_back(data); }

    iterator remove(iterator pos) { return storage.erase(pos); }
    iterator remove(const_iterator pos) { return storage.erase(pos); }

    void resize(size_t count ) { storage.resize(count); }
    void resize(size_t count, const SomeType& value) { storage.resize(count, value); }

    void clear() { storage.clear(); }

    size_t size() { return storage.size(); }

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

