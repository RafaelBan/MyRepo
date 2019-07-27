#ifndef RBLAVLITERATOR_H
#define RBLAVLITERATOR_H

#include "rblavlnode.h"

#include <iterator>

#ifndef ptrdiff_t
#define __need_ptrdiff_t
#include <cstddef>
#endif // ptrdiff_t

#ifndef size_t
#define __need_size_t
#include <cstddef>
#endif // size_t


namespace rbl
{
    template <typename SomeType>
    class AvlTree;

    template<typename tag, typename tp, typename diff = ptrdiff_t,
             typename ptr = tp *, typename ref = tp &>
    struct iterator
    {
        using iterator_category = tag;
        using value_type = tp;
        using difference_type = diff;
        using pointer = ptr;
        using reference = ref;
    };

    template <typename SomeType>
    struct ConstAvlIterator : public rbl::iterator<std::bidirectional_iterator_tag, SomeType,
                                                   ptrdiff_t, const SomeType *, const SomeType &>
    {
        friend class AvlTree<SomeType>;

    public:
        using base_iterator =  typename rbl::iterator<std::bidirectional_iterator_tag, SomeType,
                                                      ptrdiff_t, const SomeType *, const SomeType &>;

        using typename base_iterator::iterator_category;
        using typename base_iterator::value_type;
        using typename base_iterator::difference_type;
        using typename base_iterator::pointer;
        using typename base_iterator::reference;

        using AvlTNode = AvlNode<SomeType>;
        using self = ConstAvlIterator<SomeType>;
        using sptr = typename AvlTNode::sptr;
        using wptr = typename AvlTNode::wptr;

        explicit
        ConstAvlIterator(typename AvlHeader::hsptr header, sptr node = nullptr);

        ConstAvlIterator(const self &it);

        self &
        operator=(const self &it);

        reference
        operator*() const;
        pointer
        operator->() const;

        self &
        operator++();
        self
        operator++(int);

        self &
        operator--();
        self
        operator--(int);

        bool
        operator==(const self &it) const;
        bool
        operator!=(const self &it) const;

        operator bool() const;

    private:
        typename AvlHeader::hwptr header;
        wptr currentNode;

        static
        self
        begin(typename AvlHeader::hsptr header);
        static
        self
        end(typename AvlHeader::hsptr header);
    };
}

#include "rblavliterator.hh"

#endif // RBLAVLITERATOR_H
