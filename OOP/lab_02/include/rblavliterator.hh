#ifndef RBLAVLITERATOR_HH
#define RBLAVLITERATOR_HH

#include "rblavliterator.h"
#include "rblexception.h"

template <typename SomeType>
rbl::ConstAvlIterator<SomeType>::ConstAvlIterator(typename AvlHeader::hsptr header, sptr node) :
    header(header),
    currentNode(node)
{
}

template <typename SomeType>
rbl::ConstAvlIterator<SomeType>::ConstAvlIterator(const self &it) :
    header(it.header),
    currentNode(it.currentNode)
{
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::self &
rbl::ConstAvlIterator<SomeType>::operator=(const self &it)
{
    this->header = it.header;
    this->currentNode = it.currentNode;

    return *this;
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::reference
rbl::ConstAvlIterator<SomeType>::operator*() const
{
    if (!currentNode.lock())
    {
        throw rbl::EndIteratorRead("At inderection");
    }

    return (AvlTNode::getKey(currentNode.lock()));
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::pointer
rbl::ConstAvlIterator<SomeType>::operator->() const
{
    return &(AvlTNode::getKey(currentNode.lock()));
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::self &
rbl::ConstAvlIterator<SomeType>::operator++()
{
    if (currentNode.lock())
    {
        currentNode = AvlTNode::increment(currentNode.lock());
    }
    else
    {
        throw rbl::IteratorOutOfRange("At prefix increment");

        currentNode = AvlTNode::getMin(AvlTNode::toSelf(header.lock()->root));
    }

    return *this;
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::self
rbl::ConstAvlIterator<SomeType>::operator++(int)
{
    self temp = *this;

    if (currentNode.lock())
    {
        currentNode = AvlTNode::increment(currentNode.lock());
    }
    else
    {
        throw rbl::IteratorOutOfRange("At postfix increment");

        currentNode = AvlTNode::getMin(AvlTNode::toSelf(header.lock()->root));
    }

    return  temp;
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::self &
rbl::ConstAvlIterator<SomeType>::operator--()
{
    if (currentNode.lock())
    {
        sptr next = AvlTNode::decrement(currentNode.lock());

        if (!next)
        {
            throw rbl::IteratorOutOfRange("At prefix decrement");
        }

        currentNode = next;
    }
    else
    {
        currentNode = AvlTNode::getMax(AvlTNode::toSelf(header.lock()->root));
    }

    return *this;
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::self
rbl::ConstAvlIterator<SomeType>::operator--(int)
{
    self temp = *this;

    if (currentNode.lock())
    {
        sptr next = AvlTNode::decrement(currentNode.lock());

        if (!next)
        {
            throw rbl::IteratorOutOfRange("At postfix decrement");
        }

        currentNode = next;
    }
    else
    {
        currentNode = AvlTNode::getMax(AvlTNode::toSelf(header.lock()->root));
    }

    return  temp;
}

template <typename SomeType>
bool
rbl::ConstAvlIterator<SomeType>::operator==(const self &it) const
{
    return (currentNode.lock() == it.currentNode.lock()) &&
           (header.lock()->root == it.header.lock()->root);
}

template <typename SomeType>
bool
rbl::ConstAvlIterator<SomeType>::operator!=(const self &it) const
{
    return !(*this == it);
}

template <typename SomeType>
rbl::ConstAvlIterator<SomeType>::operator bool() const
{
    return (currentNode.use_count() != 0);
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::self
rbl::ConstAvlIterator<SomeType>::begin(typename AvlHeader::hsptr header)
{
    return self(header, AvlTNode::getMin(AvlTNode::toSelf(header->root)));
}

template <typename SomeType>
typename rbl::ConstAvlIterator<SomeType>::self
rbl::ConstAvlIterator<SomeType>::end(typename AvlHeader::hsptr header)
{
    return self(header, nullptr);
}

#endif // RBLAVLITERATOR_HH
