#ifndef RBLAVLTREE_HH
#define RBLAVLTREE_HH

#include "rblavltree.h"


template <typename SomeType>
rbl::AvlTree<SomeType>::AvlTree()
{
}

template <typename SomeType>
rbl::AvlTree<SomeType>::AvlTree(const AvlTree &tree)
{
    this->copy(tree);
}

template <typename SomeType>
rbl::AvlTree<SomeType>::AvlTree(AvlTree &&tree)
{
    this->move(tree);
}

template <typename SomeType>
rbl::AvlTree<SomeType> &
rbl::AvlTree<SomeType>::operator=(const AvlTree &tree)
{
    this->copy(tree);
}

template <typename SomeType>
rbl::AvlTree<SomeType> &
rbl::AvlTree<SomeType>::operator=(AvlTree &&tree)
{
    this->move(tree);
}

template <typename SomeType>
rbl::AvlTree<SomeType>::~AvlTree()
{
}

template <typename SomeType>
void
rbl::AvlTree<SomeType>::copy(const AvlTree &tree)
{
    this->clear();

    for (SomeType key: tree)
    {
        this->insert(key);
    }
}

template <typename SomeType>
void
rbl::AvlTree<SomeType>::move(AvlTree &tree)
{
    this->header->moveData(*tree.header);
}

template <typename SomeType>
void
rbl::AvlTree<SomeType>::swap(AvlTree &tree)
{
    typename AvlHeader::hsptr temp = this->header;

    this->header = tree.header;
    tree.header = temp;
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_iterator
rbl::AvlTree<SomeType>::find(const SomeType &key) const
{
    return const_iterator(header, AvlTNode::find(AvlTNode::toSelf(header->root), key));
}

template <typename SomeType>
bool
rbl::AvlTree<SomeType>::insert(const SomeType &key)
{
    bool added;

    header->root = AvlTNode::insert(AvlTNode::toSelf(header->root), key, &added);

    if (added)
    {
        header->counter++;
    }

    return  added;
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_iterator
rbl::AvlTree<SomeType>::erase(const_iterator it)
{
    if (it.header.lock()->root != this->header->root)
    {
        throw rbl::StrangeIterator("at AvlTree erasing");
    }

    if (it == this->end())
    {
        return it;
    }

    const_iterator next = it;
    next++;

    header->root = AvlTNode::erase(AvlTNode::toSelf(header->root), it.currentNode.lock());
    header->counter--;

    return  next;
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::iterator
rbl::AvlTree<SomeType>::begin()
{
    return iterator::begin(header);
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_iterator
rbl::AvlTree<SomeType>::begin() const
{
    return const_iterator::begin(header);
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::iterator
rbl::AvlTree<SomeType>::end()
{
    return iterator::end(header);
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_iterator
rbl::AvlTree<SomeType>::end() const
{
    return const_iterator::end(header);
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_iterator
rbl::AvlTree<SomeType>::cbegin()
{
    return const_iterator::begin(header);
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_iterator
rbl::AvlTree<SomeType>::cbegin() const
{
    return const_iterator::begin(header);
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_iterator
rbl::AvlTree<SomeType>::cend()
{
    return const_iterator::end(header);
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_iterator
rbl::AvlTree<SomeType>::cend() const
{
    return const_iterator::end(header);
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::reverse_iterator
rbl::AvlTree<SomeType>::rbegin()
{
    return reverse_iterator(end());
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_reverse_iterator
rbl::AvlTree<SomeType>::rbegin() const
{
    return const_reverse_iterator(end());
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::reverse_iterator
rbl::AvlTree<SomeType>::rend()
{
    return reverse_iterator(begin());
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_reverse_iterator
rbl::AvlTree<SomeType>::rend() const
{
    return const_reverse_iterator(begin());
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_reverse_iterator
rbl::AvlTree<SomeType>::crbegin()
{
    return const_reverse_iterator(cend());
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_reverse_iterator
rbl::AvlTree<SomeType>::crbegin() const
{
    return const_reverse_iterator(cend());
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_reverse_iterator
rbl::AvlTree<SomeType>::crend()
{
    return const_reverse_iterator(cbegin());
}

template <typename SomeType>
typename rbl::AvlTree<SomeType>::const_reverse_iterator
rbl::AvlTree<SomeType>::crend() const
{
    return const_reverse_iterator(cbegin());
}

#endif // RBLAVLTREE_HH
