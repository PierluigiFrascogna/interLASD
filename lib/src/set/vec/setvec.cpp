
namespace lasd {

    /* ************************************************************************** */

    // Default constructor
    template <typename Data>
    SetVec<Data>::SetVec() {
        ulong initSize = 8;
        elements = new Data[initSize];
        memorySize = initSize;
    }

    // SetVec from a TraversableContainer
    template <typename Data>
    SetVec<Data>::SetVec(const TraversableContainer<Data>& travCont): SetVec() {
        travCont.Traverse(
            [this](const Data& data) {
                Insert(data);
            }
        );
    }

    // SetVec from a MappableContainer
    template <typename Data>
    SetVec<Data>::SetVec(MappableContainer<Data>&& mapCont): SetVec() {
        mapCont.Map(
            [this](Data&& data) {
                Insert(std::move(data));
            }
        );
    }

    // Copy constructor
    template <typename Data>
    SetVec<Data>::SetVec(const SetVec& copySet) {
        memorySize = copySet.memorySize;
        head = copySet.head;
        elements = new Data[copySet.memorySize];
        std::copy(copySet.elements, copySet.elements + copySet.memorySize, elements);
        size = copySet.size;
    }

    // Move constructor
    template <typename Data>
    SetVec<Data>::SetVec(SetVec&& moveSet) noexcept {
        std::swap(elements, moveSet.elements);
        std::swap(size, moveSet.size);
        std::swap(head, moveSet.head);
        std::swap(memorySize, moveSet.memorySize);
    }

    // Destructor
    template <typename Data>
    SetVec<Data>::~SetVec() {
        delete[] elements;
        elements = nullptr;
        size = 0;
        head = 0;
        memorySize = 0;
    }

    // Copy assignment
    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(const SetVec& copySet) {
        if(this != &copySet) {
            SetVec<Data>* tmp = copySet;
            std::swap(*this, *tmp);
            delete tmp;
        }
        return *this;
    }

    // Move assignment
    template <typename Data>
    SetVec<Data>& SetVec<Data>::operator=(SetVec&& moveSet) noexcept {
        if(this != &moveSet) {
            std::swap(elements, moveSet.elements);
            std::swap(size, moveSet.size);
            std::swap(head, moveSet.head);
            std::swap(memorySize, moveSet.memorySize);
        }
        return *this;
    }

    // Equality operator
    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec& compSetVec) const noexcept {
        if(Empty() && compSetVec.Empty()) return true;
        if(size != compSetVec.size) return false;

        for(ulong i = 0; i < size; i++) {
            if((*this)[i] != compSetVec[i]) {
                return false;
            }
        }

        return true;
    }

    // Inequality operator
    template <typename Data>
    bool SetVec<Data>::operator!=(const SetVec& compSetVec) const noexcept {
        return !operator==(compSetVec);
    }

    // Min
    template <typename Data>
    const Data& SetVec<Data>::Min() const {
        if(Empty()) { throw std::length_error("Set is empty"); }
        return (*this)[0];
    }

    // Min and remove
    template <typename Data>
    Data SetVec<Data>::MinNRemove() {
        Data minData = Min();
        RemoveMin();
        return minData;
    }

    // Remove min
    template <typename Data>
    void SetVec<Data>::RemoveMin() {
        if(Empty()) { throw std::length_error("Set is empty"); }
        head++;
        size--;
    }

    // Max
    template <typename Data>
    const Data& SetVec<Data>::Max() const {
        if(Empty()) { throw std::length_error("Set is empty"); }
        return (*this)[size - 1];
    }

    // Max and remove
    template <typename Data>
    Data SetVec<Data>::MaxNRemove() {
        Data maxData = Max();
        RemoveMax();
        return maxData;
    }

    // Remove max
    template <typename Data>
    void SetVec<Data>::RemoveMax() {
        if(Empty()) { throw std::length_error("Set is empty"); }
        size--;
    }

    // Predecessor
    template <typename Data>
    const Data& SetVec<Data>::Predecessor(const Data& predKey) const {
        if(Empty()) { throw std::length_error("Set is empty"); }
        if(predKey <= Min()) { throw std::length_error("No predecessor found"); }
        
        ulong index = BinarySearchIndex(predKey);
        return (*this)[index - 1];
    }

    // Predecessor and remove
    template <typename Data>
    Data SetVec<Data>::PredecessorNRemove(const Data& predKey) {
        Data predData = Predecessor(predKey);
        Remove(predData);
        return predData;
    }

    // Remove predecessor
    template <typename Data>
    void SetVec<Data>::RemovePredecessor(const Data& predKey) {
        PredecessorNRemove(predKey);
    }

    // Successor
    template <typename Data>
    const Data& SetVec<Data>::Successor(const Data& succKey) const {
        if(Empty()) { throw std::length_error("Set is empty"); }
        if(succKey >= Max()) { throw std::length_error("No successor found"); }
        
        ulong index = BinarySearchIndex(succKey);
        return (*this)[index] > succKey ? (*this)[index] : (*this)[index + 1];
    }

    // Successor and remove
    template <typename Data>
    Data SetVec<Data>::SuccessorNRemove(const Data& succKey) {
        Data succData = Successor(succKey);
        Remove(succData);
        return succData;
    }

    // Remove successor
    template <typename Data>
    void SetVec<Data>::RemoveSuccessor(const Data& succKey) {
        SuccessorNRemove(succKey);
    }

    // Insert (copy)
    template <typename Data>
    bool SetVec<Data>::Insert(const Data& insertKey) {
        ulong index = BinarySearchIndex(insertKey);

        if(index < size && (*this)[index] == insertKey) {
            return false; // Element already exists
        }

        if(size == memorySize) { Resize(memorySize * 2); }

        if(!Empty() && (*this)[index] < insertKey) { index++; }; 

        index < size/2 ? ShiftFromIndexToHead(index) : ShiftFromIndexToTail(index);

        (*this)[index] = insertKey;
        return true;
    }

    // Insert (move)
    template <typename Data>
    bool SetVec<Data>::Insert(Data&& insertKey) {
        ulong index = BinarySearchIndex(insertKey);

        if(index < size && (*this)[index] == insertKey) {
            return false; // Element already exists
        }

        if(size == memorySize) { Resize(memorySize * 2); }

        if((*this)[index] < insertKey) { index++; }; 

        index < size/2 ? ShiftFromIndexToHead(index) : ShiftFromIndexToTail(index);

        (*this)[index] = std::move(insertKey);
        return true;
    }

    // Remove
    template <typename Data>
    bool SetVec<Data>::Remove(const Data& delKey) {
        ulong index = BinarySearchIndex(delKey);

        if(index >= size || (*this)[index] != delKey) {
            return false; // Element not found
        }

        index < size/2 ? ShiftFromHeadToIndex(index) : ShiftFromTailToIndex(index);
        return true;
    }

    // index operator (const version)
    template <typename Data>
    const Data& SetVec<Data>::operator[](ulong index) const {
        if(index >= size) { throw std::out_of_range("Index out of range"); }
        return elements[(head + index) % memorySize];
    }

    // Exists
    template <typename Data>
    bool SetVec<Data>::Exists(const Data& keyToSearch) const noexcept {
        if(Empty() || keyToSearch < Min() || keyToSearch > Max()) {
            return false;
        }

        if(keyToSearch == Min() || keyToSearch == Max()) {
            return true;
        }

        return (*this)[BinarySearchIndex(keyToSearch)] == keyToSearch;
    }

    // Clear
    template <typename Data>
    void SetVec<Data>::Clear() noexcept {
        SetVec<Data>* tmp = new SetVec<Data>();
        std::swap(*this, *tmp);
        delete tmp;
    }

    /* ************************************************************************** */

    // Binary search
    template <typename Data>
    ulong SetVec<Data>::BinarySearchIndex(const Data& keyToSearch) const noexcept {
        if(Empty()) { return 0; }

        ulong start = 0, end = size - 1;

        while(start < end) {
            ulong mid = start + (end - start) / 2;
            if((*this)[mid] < keyToSearch) {
                start = mid + 1;
            } else if((*this)[mid] > keyToSearch) {
                end = mid;
            } else {
                return mid;
            }
        }
        return start;

    }

    // Resize
    template <typename Data>
    inline void SetVec<Data>::Resize(ulong newMemorySize) noexcept {
        if(newMemorySize == memorySize) return;

        if(newMemorySize == 0) {
            Clear();
            return;
        }

        Data* newElements = new Data[newMemorySize];
        for(ulong i = 0; i < size; i++) {
            newElements[i] = (*this)[i];
        }
        delete[] elements;
        elements = newElements;
        memorySize = newMemorySize;
        head = 0;
    }

    // Shift the elements from index to the left
    template <typename Data>
    inline void SetVec<Data>::ShiftFromIndexToHead(ulong index) noexcept {
        size++;
        head = (head != 0) ? head-1 : memorySize-1;
        for(ulong i = 0; i < index; i++) {
            (*this)[i] = std::move((*this)[i + 1]);
        }
    }

    // Shift the elements from index to the right
    template <typename Data>
    inline void SetVec<Data>::ShiftFromIndexToTail(ulong index) noexcept {
        size++;
        for(ulong i = size-1; i > index; i--) {
            (*this)[i] = std::move((*this)[i - 1]);
        }
    }

    // Shift the elements from left to index
    template <typename Data>
    inline void SetVec<Data>::ShiftFromHeadToIndex(ulong index) noexcept {
        for(ulong i = index; i > 0; i--) {
            (*this)[i] = std::move((*this)[i - 1]);
        }
        size--;
        head++;
    }

    // Shift the elements from right to index
    template <typename Data>
    inline void SetVec<Data>::ShiftFromTailToIndex(ulong index) noexcept {
        for(ulong i = index; i < size-1; i++) {
            (*this)[i] = std::move((*this)[i + 1]);
        }
        size--;
    }

    // index operator (mutable version)
    template<typename Data>
    Data& SetVec<Data>::operator[](ulong index){
        return const_cast<Data&>(static_cast<const SetVec<Data>*>(this)->operator[](index));
    }

    /* ************************************************************************** */

}
