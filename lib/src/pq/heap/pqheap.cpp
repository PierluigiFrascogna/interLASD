
namespace lasd {

    /* ************************************************************************** */

    // Default constructor
    template <typename Data>
    PQHeap<Data>::PQHeap(): HeapVec<Data>() {
        memorySize = 0;
    }

    // Constructor from TraversableContainer
    template <typename Data>
    PQHeap<Data>::PQHeap(const TraversableContainer<Data>& travCont): HeapVec<Data>(travCont) {
        memorySize = size;
    }

    // Constructor from MappableContainer
    template <typename Data>
    PQHeap<Data>::PQHeap(MappableContainer<Data>&& mapCont): HeapVec<Data>(std::move(mapCont)) {
        memorySize = size;
    }

    // Copy constructor
    template <typename Data>
    PQHeap<Data>::PQHeap(const PQHeap& copyPQHeap): HeapVec<Data>(copyPQHeap) {
        memorySize = copyPQHeap.memorySize;
    }

    // Move constructor
    template <typename Data>
    PQHeap<Data>::PQHeap(PQHeap&& movePQHeap) noexcept: HeapVec<Data>(std::move(movePQHeap)) {
        std::swap(memorySize, movePQHeap.memorySize);
    }

    // Copy assignment
    template <typename Data>
    PQHeap<Data>& PQHeap<Data>::operator=(const PQHeap& copyPQHeap) {
        if (this != &copyPQHeap) {
            HeapVec<Data>::operator=(copyPQHeap);
            memorySize = copyPQHeap.memorySize;
        }
        return *this;
    }

    // Move assignment
    template <typename Data>
    PQHeap<Data>& PQHeap<Data>::operator=(PQHeap&& movePQHeap) noexcept {
        if (this != &movePQHeap) {
            HeapVec<Data>::operator=(std::move(movePQHeap));
            std::swap(memorySize, movePQHeap.memorySize);
        }
        return *this;
    }

    // Tip function
    template <typename Data>
    const Data& PQHeap<Data>::Tip() {
        if (Empty()) throw std::length_error("Priority queue is empty.");
        return elements[0];
    }

    // RemoveTip function
    template <typename Data>
    void PQHeap<Data>::RemoveTip() {
        if (Empty()) throw std::length_error("Priority queue is empty.");
        elements[0] = elements[--size];
        HeapifyDown(0);
    }

    // TipNRemove function
    template <typename Data>
    Data PQHeap<Data>::TipNRemove() {
        if (Empty()) throw std::length_error("Priority queue is empty.");
        Data tipValue = std::move(Tip());
        RemoveTip();
        return tipValue;
    }

    // Insert function (copy)
    template <typename Data>
    void PQHeap<Data>::Insert(const Data& value) {
        if(memorySize == 0) { Resize(8); }
        if (size == memorySize) { Resize(memorySize * 2); }
        elements[size++] = value;
        HeapifyUp(size - 1);
    }

    // Insert function (move)
    template <typename Data>
    void PQHeap<Data>::Insert(Data&& value) noexcept {
        if(memorySize == 0) { Resize(8); }
        if (size == memorySize) { Resize(memorySize * 2); }
        elements[size++] = std::move(value);
        HeapifyUp(size - 1);
    }

    // Change function (copy)
    template <typename Data>
    void PQHeap<Data>::Change(ulong indexToChange, const Data& newValue) {
        if(indexToChange >= size) { throw std::out_of_range("Index out of range."); }
        Data oldValue = elements[indexToChange];
        elements[indexToChange] = newValue;
        if(newValue > oldValue) {
            HeapifyUp(indexToChange);
        } else if(newValue < oldValue) {
            HeapifyDown(indexToChange);
        }
    }

    // Change function (move)
    template <typename Data>
    void PQHeap<Data>::Change(ulong indexToChange, Data&& newValue) {
        if(indexToChange >= size) { throw std::out_of_range("Index out of range."); }
        Data oldValue = std::move(elements[indexToChange]);
        elements[indexToChange] = std::move(newValue);
        if(newValue > oldValue) {
            HeapifyUp(indexToChange);
        } else if(newValue < oldValue) {
            HeapifyDown(indexToChange);
        }
    }

    /* ************************************************************************** */

    // HeapifyUp function
    template <typename Data>
    void PQHeap<Data>::HeapifyUp(ulong index) noexcept {
        const std::function<ulong(ulong)> ParentIndex = [](ulong index) {
            return index == 0 ? 0 : (index - 1) / 2;
        };
        for(ulong parentIndex = ParentIndex(index); elements[index] > elements[parentIndex]; parentIndex = ParentIndex(index)) {
            std::swap(elements[index], elements[parentIndex]);
            index = parentIndex;
        }
    }

    // HeapifyDown function
    template <typename Data>
    void PQHeap<Data>::HeapifyDown(ulong index) noexcept {
       HeapVec<Data>::Heapify(index);
    }

    /* ************************************************************************** */

}
