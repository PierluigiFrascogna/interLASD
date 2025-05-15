
namespace lasd {

    /* ************************************************************************** */

    template <typename Data>
    const Data& LinearContainer<Data>::Front() const {
        if(size == 0) {
            throw std::length_error("Container is empty");
        } else {
            return operator[](0);
        }
    }

    template <typename Data>
    const Data& LinearContainer<Data>::Back() const {
        if(size == 0) {
            throw std::length_error("Container is empty");
        } else {
            return operator[](size - 1);
        }
    }

    template <typename Data>
    void LinearContainer<Data>::Traverse(TraverseFun func) const {
        PreOrderTraverse(func);
    }

    template <typename Data>
    void LinearContainer<Data>::PreOrderTraverse(TraverseFun func) const {
        for(ulong i = 0; i < size; i++) {
            func(operator[](i));
        }
    }

    template <typename Data>
    void LinearContainer<Data>::PostOrderTraverse(TraverseFun func) const {
        for(ulong i = size; i > 0; i--) {
            func(operator[](i-1));
        }
    }

    /* ************************************************************************** */

    template <typename Data>
    Data& MutableLinearContainer<Data>::Front() {
        if(size == 0) {
            throw std::length_error("Container is empty")
        } else {
            return operator[](0);
        }
    }

    template <typename Data>
    Data& MutableLinearContainer<Data>::Back() {
        if(size == 0) {
            throw std::length_error("Container is empty");
        } else {
            return operator[](size - 1);
        }
    }

    template <typename Data>
    void MutableLinearContainer<Data>::Map(MapFun func) {
        PreOrderMap(func);
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PreOrderMap(MapFun func) {
        for(ulong i = 0; i < size; i++) {
            func(operator[](i));
        }
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PostOrderMap(MapFun func) {
        for(ulong i = size; i > 0; i--) {
            func(operator[](i-1));
        }
    }

    /* ************************************************************************** */

    template <typename Data>
    void SortableLinearContainer<Data>::Sort() noexcept {
        for(ulong i=1; i<size; i++){
            Data key=operator[](i);
            ulong j=i;

            while (j>0 && operator[](j-1)>key){
                operator[](j)=operator[](j-1);
                j--;
            }
            operator[](j)=key;
        }
    }

    /* ************************************************************************** */

}
