
namespace lasd {

    /* ************************************************************************** */
    
    template <typename Data>
    template <typename Accumulator>
    inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> func, Accumulator acc) const {
        Traverse(
            [func, &acc](const Data& val) {
                acc = func(val, acc);
            }
        );
        return acc;
    };

    template <typename Data>
    inline bool TraversableContainer<Data>::Exists(const Data& val) const noexcept {
        bool exists = false;
        Traverse(
            [val, &exists](const Data& currVal) {
                exists |= (val == currVal);
            }
        );
        return exists;
    }
    

    /* ************************************************************************** */

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> func, Accumulator acc) const {
        Traverse(
            [func, &acc](const Data& val) {
                acc = func(val, acc);
            }
        );
        return acc;
    };

    /* ************************************************************************** */

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> func, Accumulator acc) const {
        Traverse(
            [func, &acc](const Data& val) {
                acc = func(val, acc);
            }
        );
        return acc;
    };

    /* ************************************************************************** */

}
