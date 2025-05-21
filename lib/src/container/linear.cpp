
namespace lasd {

    /* ************************************************************************** */

    // Equality operator
    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer& compLinearCont) const noexcept {
        if (this == &compLinearCont) { return true; }
        if (Empty() && compLinearCont.Empty()) { return true; }
        if (size != compLinearCont.size) { return false; }
        for(ulong i = 0; i < size; i++) {
            if(operator[](i) != compLinearCont[i]) {
                return false;
            }
        }
        return true;
    }

    // Inequality operator
    template <typename Data>
    bool LinearContainer<Data>::operator!=(const LinearContainer& compLinearCont) const noexcept {
        return !operator==(compLinearCont);
    }

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
            throw std::length_error("Container is empty");
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
            Data key=this->operator[](i);
            ulong j=i;

            while (j>0 && this->operator[](j-1)>key){
                this->operator[](j)=this->operator[](j-1);
                j--;
            }
            this->operator[](j)=key;
        }
    }

    /* ************************************************************************** */

}
