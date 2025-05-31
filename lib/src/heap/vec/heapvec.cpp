
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
    HeapVec<Data>::HeapVec(const HeapVec& copyHeap): Vector<Data>(copyHeap) {
        Heapify();
    }

    // Move constructor
    template <typename Data>
    HeapVec<Data>::HeapVec(HeapVec&& moveHeap) noexcept: Vector<Data>(std::move(moveHeap)) {
        Heapify();
    }

    // Destructor
    template <typename Data>
    HeapVec<Data>::~HeapVec() {
        Vector<Data>::Clear();
    }

    // Copy assignment
    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(const HeapVec& copyHeap) {
        Vector<Data>::operator=(copyHeap);
        Heapify();
        return *this;
    }

    // Move assignment
    template <typename Data>
    HeapVec<Data>& HeapVec<Data>::operator=(HeapVec&& moveHeap) noexcept {
        Vector<Data>::operator=(std::move(moveHeap));
        Heapify();
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

    // Check if the current vector is a valid heap
    template <typename Data>
    bool HeapVec<Data>::IsHeap() const noexcept {
        if (Empty()) return true; // An empty heap is a valid heap
        for (ulong parentIndex = 0; parentIndex < size; parentIndex++) {
            ulong leftChildIndex = 2 * parentIndex + 1;
            ulong rightChildIndex = 2 * parentIndex + 2;
            if (leftChildIndex < size && elements[parentIndex] < elements[leftChildIndex]) return false;
            if (rightChildIndex < size && elements[parentIndex] < elements[rightChildIndex]) return false;
        }
        return true;
    }

    // Heapify the current vector
    template <typename Data>
    void HeapVec<Data>::Heapify() noexcept {
        if (Empty()) return; // Nothing to heapify in an empty vector
        for(ulong i = 1; i < size; i++) {
            ulong leftChildIndex = 2 * i + 1;
            ulong rightChildIndex = 2 * i + 2;
            ulong largestIndex = i;
            if (leftChildIndex < size && elements[leftChildIndex] > elements[largestIndex]) {
                largestIndex = leftChildIndex;
            }
            if (rightChildIndex < size && elements[rightChildIndex] > elements[largestIndex]) {
                largestIndex = rightChildIndex;
            }
            if (largestIndex != i) {
                std::swap(elements[i], elements[largestIndex]);
                i = largestIndex; // Continue heapifying down from the largest index
            }
        }
    }

    // Sort the current vector using heap sort
    template <typename Data>
    void HeapVec<Data>::Sort() noexcept {
        if (Empty()) return; // Nothing to sort in an empty vector
        Heapify(); // Ensure the vector is a valid heap
        for (ulong i = size - 1; i > 0; i--) {
            std::swap(Front(), elements[i]); // Move the largest element to the end
            size--; // Reduce the size of the heap
            Heapify(); // Restore the heap property
        }
    }

    /* ************************************************************************** */

}
