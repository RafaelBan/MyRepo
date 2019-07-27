#include "rblavlnode.h"

rbl::AvlNodeBase::AvlNodeBase() :
    height(0),

    parent(sptr(nullptr)),
    left(sptr(nullptr)),
    right(sptr(nullptr))
{
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::getLeft(sptr node)
{
    return node->left;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::getRight(sptr node)
{
    return node->right;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::getParent(sptr node)
{
    return node->parent.lock();
}

void
rbl::AvlNodeBase::setLeft(sptr parent, sptr left)
{
    if (parent->left)
    {
        parent->left->parent = sptr(nullptr);
    }

    parent->left = left;

    if (left)
    {
        if (left->parent.lock())
        {
            if (left == left->parent.lock()->left)
            {
                left->parent.lock()->left = sptr(nullptr);
            }

            if (left == left->parent.lock()->right)
            {
                left->parent.lock()->right = sptr(nullptr);
            }
        }

        left->parent = parent;
    }
}

void
rbl::AvlNodeBase::setRight(sptr parent, sptr right)
{
    if (parent->right)
    {
        parent->right->parent = sptr(nullptr);
    }

    parent->right = right;

    if (right)
    {
        if (right->parent.lock())
        {
            if (right == right->parent.lock()->left)
            {
                right->parent.lock()->left = sptr(nullptr);
            }

            if (right == right->parent.lock()->right)
            {
                right->parent.lock()->right = sptr(nullptr);
            }
        }

        right->parent = parent;
    }
}

int
rbl::AvlNodeBase::balanceFactor(sptr node)
{
    return (int(getHeight(node->right)) - int(getHeight(node->left)));
}

size_t
rbl::AvlNodeBase::getHeight(sptr node)
{
    return (node ? node->height : 0);
}

void
rbl::AvlNodeBase::fixHeight(sptr node)
{
    size_t hr = getHeight(node->right);
    size_t hl = getHeight(node->left);

    node->height = (hr > hl ? (hr) : (hl)) + 1; // max(hr, hl) + 1
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::getMin(sptr node)
{
    if (!node)
    {
        return  node;
    }

    while (node->left)
    {
        node = node->left;
    }

    return  node;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::getMax(sptr node)
{
    if (!node)
    {
        return  node;
    }

    while (node->right)
    {
        node = node->right;
    }

    return  node;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::increment(sptr node)
{
    if (node->right)
    {
        node = node->right;

        while (node->left)
        {
            node = node->left;
        }

        return node;
    }

    while (getParent(node) && getRight(getParent(node)) == node)
    {
        node = getParent(node);
    }

    node = getParent(node);

    return node;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::decrement(sptr node)
{
    if (node->left)
    {
        node = node->left;

        while (node->right)
        {
            node = node->right;
        }

        return node;
    }

    while (getParent(node) && getLeft(getParent(node)) == node)
    {
        node = getParent(node);
    }

    node = getParent(node);

    return node;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::rotateRight(sptr p)
{
    sptr q = getLeft(p);
    sptr parent = getParent(p);

    if (parent && getRight(parent) == p)
    {
        setRight(parent, q);
    }
    if (parent && getLeft(parent) == p)
    {
        setLeft(parent, q);
    }
    q->parent = parent;

    setLeft(p, getRight(q));
    setRight(q, p);

    fixHeight(p);
    fixHeight(q);

    return q;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::rotateLeft(sptr q)
{
    sptr p = getRight(q);
    sptr parent = getParent(q);

    if (parent && getRight(parent) == q)
    {
        setRight(parent, p);
    }
    if (parent && getLeft(parent) == q)
    {
        setLeft(parent, p);
    }
    p->parent = parent;

    setRight(q, getLeft(p));
    setLeft(p, q);

    fixHeight(q);
    fixHeight(p);

    return p;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::balance(sptr node)
{
    fixHeight(node);

    if (balanceFactor(node) == +2)
    {
        if (balanceFactor(getRight(node)) < 0)
        {
            setRight(node, rotateRight(getRight(node)));
        }

        return rotateLeft(node);
    }
    if (balanceFactor(node) == -2)
    {
        if (balanceFactor(getLeft(node)) > 0)
        {
            setLeft(node, rotateLeft(getLeft(node)));
        }

        return rotateRight(node);
    }

    return node;
}

typename rbl::AvlNodeBase::sptr
rbl::AvlNodeBase::dropMin(sptr node)
{
    sptr startParent = getParent(node);

    while (getLeft(node))
    {
        node = getLeft(node);
    }

    sptr minNode = node;

    sptr parent = getParent(minNode);
    node = getRight(minNode);

    if (parent)
    {
        setLeft(parent, node);
    }
    else if (node)
    {
        node->parent = parent;
    }

    while (parent != startParent)
    {
        node = balance(parent);
        parent = getParent(node);
    }

    return node;
}

rbl::AvlHeader::AvlHeader() :
    root(typename AvlNodeBase::sptr(nullptr)),
    counter(0)
{
}

void
rbl::AvlHeader::moveData(AvlHeader &header)
{
    this->root = header.root;
    this->counter = header.counter;

    header.reset();
}

void
rbl::AvlHeader::reset()
{
    this->root = typename AvlNodeBase::sptr(nullptr);
    this->counter = 0;
}
