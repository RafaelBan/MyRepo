#include "rblavltree.h"

rbl::AvlTreeBase::AvlTreeBase() :
    header(typename AvlHeader::hsptr(new AvlHeader))
{
}

rbl::AvlTreeBase::~AvlTreeBase()
{
}

void
rbl::AvlTreeBase::clear()
{
    header->reset();
}

bool
rbl::AvlTreeBase::empty() const
{
    return (size() == 0);
}

size_t
rbl::AvlTreeBase::size() const
{
    return (header->counter);
}
