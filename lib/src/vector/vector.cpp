
namespace lasd {

    /* ************************************************************************** */

    // Constructor for a vector with a given initial dimension
    template <typename Data>
    Vector<Data>::Vector(const ulong newSize) {
        elements = new Data[newSize];
        size = newSize;
    }

    // Constructor for a vector obtained from a TraversableContainer
    template <typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data>& travCont): Vector(travCont.Size()){
        ulong index=0; 
        travCont.Traverse(
            [this, &index](const Data& data){
                elements[index++] = data; 
            }
        );
    }

    // Constructor for a vector obtained from a MappableContainer
    template <typename Data>
    Vector<Data>::Vector(const MappableContainer<Data>& mapCont): Vector(mapCont.Size()) {
        ulong index = 0;
        mapCont.Map(
            [this, &index](Data& data){
                elements[index++] = data;
            }
        );
    }

    // Copy constructor
    template <typename Data>
    Vector<Data>::Vector(const Vector& copyVec) {
        size = copyVec.size;
        elements = new Data[size];
        std::copy(copyVec.elements, copyVec.elements + copyVec.size, elements);
    } 

    // Move constructor
    template <typename Data>
    Vector<Data>::Vector(Vector&& moveVec) noexcept {
        std::swap(elements, moveVec.elements);
        std::swap(size, moveVec.size);
    }

    // Destructor
    template <typename Data>
    Vector<Data>::~Vector() {
        delete[] elements;
    }

    // Copy assignment
    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector& copyVec) {
        if(this != &copyVec) {
            delete[] elements;
            elements = new Data[copyVec.size];
            size = copyVec.size;
            std::copy(copyVec.elements, copyVec.elements + size, elements);
        }
        return *this;
    }

    // Move assignment
    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector&& moveVec) noexcept {
        std::swap(elements, moveVec.elements);
        std::swap(size, moveVec.size);
        return *this;
    }

    // Equality operator
    template <typename Data>
    bool Vector<Data>::operator==(const Vector& compVec) const noexcept {
        if(size != compVec.size) {
            return false;
        }
        for(ulong i = 0; i < size; i++) {
            if(elements[i] != compVec.elements[i]) {
                return false;
            }
        }
        return true;
    }

    // Inequality operator
    template <typename Data>
    bool Vector<Data>::operator!=(const Vector& compVec) const noexcept {
        return !(*this == compVec);
    }
    
    // Index operator (mutable version)
    template <typename Data>
    inline Data& Vector<Data>::operator[](ulong index) {
        return const_cast<Data&>(static_cast<const Vector<Data>*>(this)->operator[](index));
    }

    // Front element (mutable version)
    template <typename Data>
    inline Data& Vector<Data>::Front() {
        return const_cast<Data&>(static_cast<const Vector<Data>*>(this)->Front());
    }

    // Back element (mutable version)
    template <typename Data>
    inline Data& Vector<Data>::Back() {
        return const_cast<Data&>(static_cast<const Vector<Data>*>(this)->Back());
    }

    // Index operator (non-mutable version)
    template <typename Data>
    inline const Data& Vector<Data>::operator[](ulong index) const {
        if(index >= size) throw std::out_of_range("Index out of range");
        return elements[index];
    }

    // Front element (non-mutable version)
    template <typename Data>
    inline const Data& Vector<Data>::Front() const {
        if(Empty()) throw std::length_error("Vector is empty");
        return elements[0];
    }

    // Back element (non-mutable version)
    template <typename Data>
    inline const Data& Vector<Data>::Back() const {
        if(Empty()) throw std::length_error("Vector is empty");
        return elements[size - 1];
    }

    // Resize function
    template <typename Data>
    void Vector<Data>::Resize(ulong newSize) noexcept {
        if(newSize == size) return;

        if(newSize == 0) {
            Clear();
            return;
        }

        Data* newElements = new Data[newSize];
        ulong minSize = (newSize < size) ? newSize : size;
        for(ulong i = 0; i < minSize; i++) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        size = newSize;
    }

    // Clear function
    template <typename Data>
    void Vector<Data>::Clear() noexcept {
        delete[] elements;
        elements = nullptr;
        size = 0;
    }

    /* ************************************************************************** */

    // Constructor for a vector with a given initial dimension
    template <typename Data>
    SortableVector<Data>::SortableVector(const ulong newSize): Vector<Data>(newSize) { }

    // Constructor for a vector obtained from a TraversableContainer
    template <typename Data>
    SortableVector<Data>::SortableVector(const TraversableContainer<Data>& travCont): Vector<Data>(travCont.Size()) { }

    // Constructor for a vector obtained from a MappableContainer
    template <typename Data>
    SortableVector<Data>::SortableVector(const MappableContainer<Data>& mapCont): Vector<Data>(mapCont.Size()) { }

    // Copy constructor
    template <typename Data>
    SortableVector<Data>::SortableVector(const SortableVector& copyVec): Vector<Data>(copyVec) { }

    // Move constructor
    template <typename Data>
    SortableVector<Data>::SortableVector(SortableVector&& moveVec) noexcept: Vector<Data>(std::move(moveVec)) { }

    // Copy assignment
    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector& copyVec) {
        Vector<Data>::operator=(copyVec);
        return *this;
    }

    // Move assignment
    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector&& moveVec) noexcept {
        Vector<Data>::operator=(std::move(moveVec));
        return *this;
    }

    /* ************************************************************************** */

}
