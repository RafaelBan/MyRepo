#ifndef RBLAVLTREE_H
#define RBLAVLTREE_H

#include "rblavliterator.hpp"
#include "rblavlnode.hpp"


namespace rbl
{
    class AvlTreeBase
    {
    public:
        explicit
        AvlTreeBase();

        virtual void
        clear();

        virtual bool
        empty() const;

        virtual size_t
        size() const;

        virtual
        ~AvlTreeBase();

    protected:
        typename AvlHeader::hsptr header;
    };

    template <typename SomeType>
    class AvlTree: public AvlTreeBase
    {
        using AvlTNode = AvlNode<SomeType>;

    public:
        using iterator = ConstAvlIterator<SomeType>;
        using const_iterator = ConstAvlIterator<SomeType>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        explicit
        AvlTree();

        AvlTree(const AvlTree &tree);
        AvlTree(AvlTree &&tree);
        AvlTree &
        operator=(const AvlTree &tree);
        AvlTree &
        operator=(AvlTree &&tree);

        ~AvlTree() override;

        void
        copy(const AvlTree &tree);
        void
        move(AvlTree &tree);
        void
        swap(AvlTree &tree);

        const_iterator
        find(const SomeType &key) const;

        bool
        insert(const SomeType &key);

        const_iterator
        erase(const_iterator it);

        iterator
        begin();
        const_iterator
        begin() const;
        iterator
        end();
        const_iterator
        end() const;

        const_iterator
        cbegin();
        const_iterator
        cbegin() const;
        const_iterator
        cend();
        const_iterator
        cend() const;

        reverse_iterator
        rbegin();
        const_reverse_iterator
        rbegin() const;
        reverse_iterator
        rend();
        const_reverse_iterator
        rend() const;

        const_reverse_iterator
        crbegin();
        const_reverse_iterator
        crbegin() const;
        const_reverse_iterator
        crend();
        const_reverse_iterator
        crend() const;
    };
}

#endif // RBLAVLTREE_H
