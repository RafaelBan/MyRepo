#include "rblset.h"

rbl::SetBase::SetBase()
{
}

rbl::SetBase::~SetBase()
{
}

bool
rbl::SetBase::empty() const
{
    return (size() == 0);
}
