#ifndef RBLAVLNODE_H
#define RBLAVLNODE_H

#include <memory>
#include <ostream>

#ifndef size_t
#define __need_szie_t
#include <cstddef>
#endif // size_t


namespace rbl
{
    class AvlNodeBase
    {
        friend struct AvlHeader;

    private:
        size_t height;

    protected:
        using sptr = std::shared_ptr<AvlNodeBase>;
        using wptr = std::weak_ptr<AvlNodeBase>;

        wptr parent;
        sptr left;
        sptr right;

    public:
        explicit
        AvlNodeBase();

        static
        sptr
        getParent(sptr node);
        static
        sptr
        getRight(sptr node);
        static
        sptr
        getLeft(sptr node);

        static
        void
        setRight(sptr parent, sptr right);
        static
        void
        setLeft(sptr parent, sptr left);

        static
        int
        balanceFactor(sptr node);
        static
        void
        fixHeight(sptr node);
        static
        size_t
        getHeight(sptr node);

        static
        sptr
        getMin(sptr node);
        static
        sptr
        getMax(sptr node);

        static
        sptr
        increment(sptr node);
        static
        sptr
        decrement(sptr node);

        static
        sptr
        rotateRight(sptr p);
        static
        sptr
        rotateLeft(sptr q);
        static
        sptr
        balance(sptr node);

        static
        sptr
        dropMin(sptr node);
    };

    template <typename SomeType>
    class AvlNode : public AvlNodeBase
    {
    public:
        using Self = AvlNode<SomeType>;
        using sptr = std::shared_ptr<Self>;
        using wptr = std::weak_ptr<Self>;

        static
        typename AvlNodeBase::sptr
        toBase(sptr node);

        static
        sptr
        toSelf(typename AvlNodeBase::sptr node);

    private:
        SomeType key;

    public:
        explicit
        AvlNode(const SomeType &key);

        static
        sptr
        getLeft(sptr node);
        static
        sptr
        getRight(sptr node);
        static
        sptr
        getParent(sptr node);

        static
        SomeType &
        getKey(sptr node);

        static
        sptr
        getMin(sptr node);
        static
        sptr
        getMax(sptr node);

        static
        sptr
        increment(sptr node);
        static
        sptr
        decrement(sptr node);

        static
        sptr
        balance(sptr node);

        static
        sptr
        dropMin(sptr node);

        static
        sptr
        find(sptr node, const SomeType &key);

        static
        sptr
        insert(sptr node, const SomeType &key, bool *added = nullptr, sptr *newNode = nullptr);
        static
        sptr
        insert(sptr node, sptr *newNode, bool *added);

        static
        sptr
        erase(sptr node, const SomeType &key, sptr *deleted = nullptr);
        static
        sptr
        erase(sptr node, sptr deleted);

        static
        void
        toDot(sptr node, std::ostream &fout)
        {
            if (!node)
            {
                return;
            }

            if (getParent(node))
            {
                fout << "    " << getParent(node)->key << " -> " << node->key << ";" << '\n';
            }

            toDot(toSelf(node->left), fout);
            toDot(toSelf(node->right), fout);
        }

        static
        void
        toDotFile(sptr node, std::ostream &fout)
        {
            fout << "digraph AVLTree {" << '\n';

            toDot(node, fout);

            fout << "}" << '\n';
        }
    };

    struct AvlHeader
    {
        using hsptr = std::shared_ptr<AvlHeader>;
        using hwptr = std::weak_ptr<AvlHeader>;

        typename AvlNodeBase::sptr root;
        size_t counter;

        explicit
        AvlHeader();

        void
        moveData(AvlHeader &header);

        void
        reset();
    };
}

#include "rblavlnode.hh"

#endif /*RBLAVLNODE_H*/
