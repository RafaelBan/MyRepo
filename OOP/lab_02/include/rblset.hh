#ifndef RBLSET_HH
#define RBLSET_HH

#include "rblset.h"
#include <iostream>

template <typename SomeType>
template <typename InputIterator>
rbl::Set<SomeType>::Set(InputIterator first, InputIterator last) :
    Set()
{
    this->insert(first, last);
}

template <typename SomeType>
rbl::Set<SomeType>::Set(std::initializer_list<SomeType> initList) :
    Set()
{
    this->insert(initList);
}

template <typename SomeType>
rbl::Set<SomeType>::Set(const Set &s) :
    Set()
{
    this->copy(s);
}

template <typename SomeType>
rbl::Set<SomeType>::Set(Set &&s) :
    Set()
{
    this->move(s);
}

template <typename SomeType>
rbl::Set<SomeType>::~Set()
{
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator=(const Set &s)
{
    this->copy(s);

    return *this;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator=(Set &&s)
{
    this->move(s);

    return *this;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator<<(const SomeType &key)
{
    this->insert(key);
    return *this;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator>>(const SomeType &key)
{
    this->erase(key);
    return *this;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator>>(const_iterator it)
{
    this->erase(it);
    return *this;
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::operator+(const Set &s) const
{
    return this->unite(s);
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::operator*(const Set &s) const
{
    return this->intersect(s);
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::operator-(const Set &s) const
{
    return this->completeRel(s);
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::operator^(const Set &s) const
{
    return this->completeSym(s);
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator+=(const Set &s)
{
    *this = *this + s;
    return *this;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator*=(const Set &s)
{
    *this = *this * s;
    return *this;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator-=(const Set &s)
{
    *this = *this - s;
    return *this;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator^=(const Set &s)
{
    *this = *this ^ s;
    return *this;
}

template <typename SomeType>
bool
rbl::Set<SomeType>::operator==(const Set &s) const
{
    return this->equal(s);
}

template <typename SomeType>
bool
rbl::Set<SomeType>::operator!=(const Set &s) const
{
    return !this->equal(s);
}

template <typename SomeType>
bool
rbl::Set<SomeType>::operator<(const Set &s) const
{
    return this->strictSubOf(s);
}

template <typename SomeType>
bool
rbl::Set<SomeType>::operator<=(const Set &s) const
{
    return this->subOf(s);
}

template <typename SomeType>
bool
rbl::Set<SomeType>::operator>(const Set &s) const
{
    return s.strictSubOf(*this);
}

template <typename SomeType>
bool
rbl::Set<SomeType>::operator>=(const Set &s) const
{
    return s.subOf(*this);
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::operator+(const SomeType &key) const
{
    Set res = *this;

    res << key;

    return res;
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::operator-(const SomeType &key) const
{
    Set res = *this;

    res >> key;

    return res;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator+=(const SomeType &key)
{
    *this << key;
    return  *this;
}

template <typename SomeType>
rbl::Set<SomeType> &
rbl::Set<SomeType>::operator-=(const SomeType &key)
{
    *this >> key;
    return  *this;
}

template <typename SomeType>
rbl::Set<SomeType>::operator bool()
{
    return !this->empty();
}

template <typename SomeType>
void
rbl::Set<SomeType>::copy(const Set &tree)
{
    storage.copy(tree.storage);
}

template <typename SomeType>
void
rbl::Set<SomeType>::move(Set &tree)
{
    storage.move(tree.storage);
}

template <typename SomeType>
void
rbl::Set<SomeType>::swap(Set &tree)
{
    storage.swap(tree.storage);
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::find(const SomeType &key) const
{
    return storage.find(key);
}

template <typename SomeType>
bool
rbl::Set<SomeType>::insert(const SomeType &key)
{
    return storage.insert(key);
}

template <typename SomeType>
template <class InputIterator>
void
rbl::Set<SomeType>::insert(InputIterator first, InputIterator last)
{
    while (first != last)
    {
        this->insert(*first);

        first++;
    }
}

template <typename SomeType>
void
rbl::Set<SomeType>::insert(std::initializer_list<SomeType> initList)
{
    this->insert(initList.begin(), initList.end());
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::erase(const SomeType &key)
{
    return erase(find(key));
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::erase(const_iterator it)
{
    try
    {
        return storage.erase(it);
    }
    catch (rbl::StrangeIterator e)
    {
        std::cerr << e.what() << '\n' << "which causes" << '\n';

        throw rbl::StrangeIterator("at Set erasing");
    }
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::unite(const Set &s) const
{
    Set res = *this;

    for (SomeType element: s)
    {
        res.insert(element);
    }

    return res;
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::intersect(const Set &s) const
{
    Set res;

    for (SomeType element: s)
    {
        if (this->find(element) != this->end())
        {
            res.insert(element);
        }
    }

    return res;
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::completeRel(const Set &s) const
{
    Set res = *this;

    for (SomeType element: s)
    {
        res.erase(res.find(element));
    }

    return res;
}

template <typename SomeType>
rbl::Set<SomeType>
rbl::Set<SomeType>::completeSym(const Set &s) const
{
    Set res;
    Set intersection = this->intersect(s);

    for (SomeType element: *this)
    {
        if (intersection.find(element) == intersection.end())
        {
            res.insert(element);
        }
    }

    for (SomeType element: s)
    {
        if (intersection.find(element) == intersection.end())
        {
            res.insert(element);
        }
    }

    return res;
}

template <typename SomeType>
bool
rbl::Set<SomeType>::equal(const Set &s) const
{
    if (this->size() != s.size())
    {
        return false;
    }

    for (auto it1 = this->begin(), it2 = s.begin(), end = this->end();
         it1 != end;
         it1++, it2++)
    {
        if (*it1 != *it2)
        {
            return false;
        }
    }

    return true;
}

template <typename SomeType>
bool
rbl::Set<SomeType>::subOf(const Set &s) const
{
    if (this->size() > s.size())
    {
        return false;
    }

    for (SomeType key: *this)
    {
        if (s.find(key) == s.end())
        {
            return false;
        }
    }

    return true;
}

template <typename SomeType>
bool
rbl::Set<SomeType>::strictSubOf(const Set &s) const
{
    if (this->size() >= s.size())
    {
        return false;
    }

    for (SomeType key: *this)
    {
        if (s.find(key) == s.end())
        {
            return false;
        }
    }

    return true;
}

template <typename SomeType>
bool
rbl::Set<SomeType>::contains(const SomeType &key) const
{
    return (this->end() != this->find(key));
}

template <typename SomeType>
void
rbl::Set<SomeType>::clear()
{
    this->storage.clear();
}

template <typename SomeType>
size_t
rbl::Set<SomeType>::size() const
{
    return this->storage.size();
}

template <typename SomeType>
typename rbl::Set<SomeType>::iterator
rbl::Set<SomeType>::begin()
{
    return storage.begin();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::begin() const
{
    return storage.cbegin();
}

template <typename SomeType>
typename rbl::Set<SomeType>::iterator
rbl::Set<SomeType>::end()
{
    return storage.end();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::end() const
{
    return storage.cend();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::cbegin()
{
    return storage.cbegin();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::cbegin() const
{
    return storage.cbegin();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::cend()
{
    return storage.cend();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_iterator
rbl::Set<SomeType>::cend() const
{
    return storage.cend();
}

template <typename SomeType>
typename rbl::Set<SomeType>::reverse_iterator
rbl::Set<SomeType>::rbegin()
{
    return storage.rbegin();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_reverse_iterator
rbl::Set<SomeType>::rbegin() const
{
    return storage.crbegin();
}

template <typename SomeType>
typename rbl::Set<SomeType>::reverse_iterator
rbl::Set<SomeType>::rend()
{
    return storage.rend();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_reverse_iterator
rbl::Set<SomeType>::rend() const
{
    return storage.crend();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_reverse_iterator
rbl::Set<SomeType>::crbegin()
{
    return storage.crbegin();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_reverse_iterator
rbl::Set<SomeType>::crbegin() const
{
    return storage.crbegin();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_reverse_iterator
rbl::Set<SomeType>::crend()
{
    return storage.crend();
}

template <typename SomeType>
typename rbl::Set<SomeType>::const_reverse_iterator
rbl::Set<SomeType>::crend() const
{
    return storage.crend();
}

namespace rbl
{
    template<typename SomeType>
    std::ostream &
    operator<<(std::ostream &sout, const Set<SomeType> &s)
    {
        sout << '{';

        auto it = s.begin();
        auto end = s.end();

        while (it != end)
        {
            auto next = it;
            next++;

            sout << *it;

            if (next != end)
            {
                sout << ',' << ' ';
            }

            it = next;
        }

        sout << '}';

        return sout;
    }
}

#endif /*RBLSET_HH*/
