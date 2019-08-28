#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <unordered_map>

template <typename _Key_t, typename _Value_t>
class HashTable
{
    using BaseStorage = std::unordered_map<_Key_t, _Value_t>;
public:
    using iterator = typename BaseStorage::iterator;
    using const_iterator = typename BaseStorage::const_iterator;

    std::pair<iterator, bool> add(const _Key_t &key, const _Value_t &value) { return storage.insert({ key, value }); }

    size_t remove(const _Key_t &key) { return storage.erase(key); }
    iterator remove(iterator pos) { return storage.erase(pos); }
    iterator remove(const_iterator pos) { return storage.erase(pos); }

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

#endif // HASH_TABLE_H_

