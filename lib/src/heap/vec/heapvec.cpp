
namespace lasd {

    /* ************************************************************************** */

    // Default constructor
    template <typename Data>
    HeapVec<Data>::HeapVec(): Vector<Data>() { }

    // Constructor from TraversableContainer
    template <typename Data>
    HeapVec<Data>::HeapVec(const TraversableContainer<Data>& travCont): Vector<Data>(travCont) {
        Heapify();
    }

    // Constructor from MappableContainer
    template <typename Data>
    HeapVec<Data>::HeapVec(MappableContainer<Data>&& mapCont): Vector<Data>(std::move(mapCont)) {
        Heapify();
    }

    // Copy constructor
    template <typename Data>
    HeapVec<Data>::HeapVec(const HeapVec& copyHeap): Vector<Data>(copyHeap) { }

    // Move constructor
    template <typename Data>
    HeapVec<Data>::HeapVec(HeapVec&& moveHeap) noexcept: Vector<Data>(std::move(moveHeap)) { }

    // Destructor
    template <typename Data>
    HeapVec<Data>::~HeapVec() {
        Vector<Data>::Clear();
    }

    // Copy assignment
    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec& copyHeap) {
        Vector<Data>::operator=(copyHeap);
        return *this;
    }

    // Move assignment
    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(HeapVec&& moveHeap) noexcept {
        Vector<Data>::operator=(std::move(moveHeap));
        return *this;
    }

    // Equality operator
    template <typename Data>
    bool HeapVec<Data>::operator==(const HeapVec& compHeapVec) const noexcept {
        if (Empty() && compHeapVec.Empty()) return true;
        if (Size() != compHeapVec.Size()) return false;
        for (ulong i = 0; i < size; ++i) {
            if (elements[i] != compHeapVec.elements[i]) return false;
        }
        return true;
    }

    // Inequality operator
    template <typename Data>
    bool HeapVec<Data>::operator!=(const HeapVec& compHeapVec) const noexcept {
        return !operator==(compHeapVec);
    }

    // isHeap function
    template <typename Data>
    bool HeapVec<Data>::IsHeap() const noexcept {
        if (Empty()) return true; // An empty heap is a valid heap
        for (ulong parentIndex = 0; parentIndex < size/2; parentIndex++) {
            ulong leftChildIndex = 2 * parentIndex + 1;
            ulong rightChildIndex = 2 * parentIndex + 2;
            if (leftChildIndex < size && elements[parentIndex] < elements[leftChildIndex]) return false;
            if (rightChildIndex < size && elements[parentIndex] < elements[rightChildIndex]) return false;
        }
        return true;
    }

    // Heapify function (build the heap from the current vector)
    template <typename Data>
    void HeapVec<Data>::Heapify() noexcept {
        if (Empty()) return;
        for (ulong i = Size()/2; i > 0; i--) {
            Heapify(i-1);
        }
    }

    // Sort function using heap sort
    template <typename Data>
    void HeapVec<Data>::Sort() noexcept {
        if (Empty()) return;
        Heapify();
        ulong tmpSize = size;
        for (ulong i = size-1; i > 0; i--) {
            std::swap(elements[0], elements[i]);
            size--;
            Heapify(0);
        }
        size = tmpSize; // Restore original size after sorting
    }

    /* ************************************************************************** */

    // Heapify with index function
    template <typename Data>
    void HeapVec<Data>::Heapify(ulong index) noexcept {
        if (Empty()) return;
        ulong leftChildIndex = 2 * index + 1;
        ulong rightChildIndex = 2 * index + 2;
        ulong largestIndex = index;
        if (leftChildIndex < size && elements[leftChildIndex] > elements[largestIndex]) {
            largestIndex = leftChildIndex;
        }
        if (rightChildIndex < size && elements[rightChildIndex] > elements[largestIndex]) {
            largestIndex = rightChildIndex;
        }
        if (largestIndex != index) {
            std::swap(elements[index], elements[largestIndex]);
            Heapify(largestIndex);
        }
    }

    /* ************************************************************************** */

}
