#ifndef RBLAVLNODE_HPP
#define RBLAVLNODE_HPP

#include "rblavlnode.h"


template <typename SomeType>
rbl::AvlNode<SomeType>::AvlNode(const SomeType &key) :
    AvlNodeBase(),

    key(key)
{
}

template <typename SomeType>
typename rbl::AvlNodeBase::sptr
rbl::AvlNode<SomeType>::toBase(sptr node)
{
    return std::static_pointer_cast<AvlNodeBase>(node);
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::toSelf(typename AvlNodeBase::sptr node)
{
    return std::static_pointer_cast<Self>(node);
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::getLeft(sptr node)
{
    return toSelf(AvlNodeBase::getLeft(toBase(node)));
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::getRight(sptr node)
{
    return toSelf(AvlNodeBase::getRight(toBase(node)));
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::getParent(sptr node)
{
    return toSelf(AvlNodeBase::getParent(toBase(node)));
}

template <typename SomeType>
SomeType &
rbl::AvlNode<SomeType>::getKey(sptr node)
{
    return node->key;
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::getMin(sptr node)
{
    return toSelf(AvlNodeBase::getMin(toBase(node)));
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::increment(sptr node)
{
    return toSelf(AvlNodeBase::increment(toBase(node)));
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::decrement(sptr node)
{
    return toSelf(AvlNodeBase::decrement(toBase(node)));
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::getMax(sptr node)
{
    return toSelf(AvlNodeBase::getMax(toBase(node)));
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::balance(sptr node)
{
    return toSelf(AvlNodeBase::balance(toBase(node)));
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::dropMin(sptr node)
{
    return toSelf(AvlNodeBase::dropMin(toBase(node)));
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::find(sptr node, const SomeType &key)
{
    while (node)
    {
        if (key == getKey(node))
        {
            return node;
        }
        else if (key > getKey(node))
        {
            node = getRight(node);
        }
        else if (key < getKey(node))
        {
            node = getLeft(node);
        }
    }

    return sptr(nullptr);
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::insert(sptr node, const SomeType &key, bool *added, sptr *newNode)
{
    sptr toInsert = sptr(new Self(key));

    sptr res = insert(node, &toInsert, added);

    if (newNode)
    {
        *newNode = toInsert;
    }

    return res;
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::insert(sptr node, sptr *_newNode, bool *added)
{
    if (added)
    {
        *added = true;
    }

    sptr save = node;
    sptr parent = node ? getParent(node) : sptr(nullptr);
    sptr newNode = *_newNode;
    sptr startParent = parent;

    while (node)
    {
        parent = node;

        if (getKey(newNode) == getKey(node))
        {
            if (added)
            {
                *added = false;
            }

            *_newNode = node;

            return  save;
        }
        else if (getKey(newNode) > getKey(node))
        {
            node = getRight(node);
        }
        else if (getKey(newNode) < getKey(node))
        {
            node = getLeft(node);
        }
    }

    node = newNode;

    while (parent != startParent)
    {
        if (getKey(node) > getKey(parent))
        {
            setRight(parent, balance(node));
        }
        if (getKey(node) < getKey(parent))
        {
            setLeft(parent, balance(node));
        }

        node = parent;
        parent = getParent(node);
    }

    return node;
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::erase(sptr node, const SomeType &key, sptr *deleted)
{
    sptr searched = find(node, key);

    if (deleted)
    {
        *deleted = searched;
    }

    if (!searched)
    {
        return node;
    }

    return erase(node, searched);
}

template <typename SomeType>
typename rbl::AvlNode<SomeType>::sptr
rbl::AvlNode<SomeType>::erase(sptr node, sptr deleted)
{
    if (!deleted)
    {
        return node;
    }

    sptr startParent = getParent(node);

    sptr l = getLeft(deleted);
    sptr r = getRight(deleted);
    sptr parent = getParent(deleted);

    if (!r)
    {
        node = l;
    }
    else
    {
        node = getMin(r);

        setRight(node, dropMin(r));
        setLeft(node, l);
        node->parent = sptr(nullptr);

        node = balance(node);
    }

    if (parent)
    {
        if (getKey(deleted) > getKey(parent))
        {
            setRight(parent, node);
        }
        if (getKey(deleted) < getKey(parent))
        {
            setLeft(parent, node);
        }
    }

    while (parent != startParent)
    {
        node = balance(parent);
        parent = getParent(node);
    }

    return node;
}

#endif // RBLAVLNODE_HPP
