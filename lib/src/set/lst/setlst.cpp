
namespace lasd {

    /* ************************************************************************** */

    // SetLst from a TraversableContainer
    template <typename Data>
    SetLst<Data>::SetLst(const TraversableContainer<Data>& travCont) {
        travCont.Traverse(
            [this](const Data& data) {
                Insert(data);
            }
        );
    }

    // SetLst from a MappableContainer
    template <typename Data>
    SetLst<Data>::SetLst(MappableContainer<Data>&& mapCont) {
        mapCont.Map(
            [this](Data&& data) {
                Insert(std::move(data));
            }
        );
    }

    // Copy constructor
    template <typename Data>
    SetLst<Data>::SetLst(const SetLst& copySet): List<Data>(copySet) { }

    // Move constructor
    template <typename Data>
    SetLst<Data>::SetLst(SetLst&& moveSet) noexcept: List<Data>(std::move(moveSet)) { }

    // Destructor
    template <typename Data>
    SetLst<Data>::~SetLst() {
        Clear();
    }

    // Copy assignment
    template <typename Data>
    SetLst<Data>& SetLst<Data>::operator=(const SetLst& copySet) {
        if(this != &copySet) {
            List<Data>::operator=(copySet);
        }
        return *this;
    }

    // Move assignment
    template <typename Data>
    SetLst<Data>& SetLst<Data>::operator=(SetLst&& moveSet) noexcept {
        if(this != &moveSet) {
            List<Data>::operator=(std::move(moveSet));
        }
        return *this;
    }

    // Equality operator
    template <typename Data>
    bool SetLst<Data>::operator==(const SetLst& compSetList) const noexcept {
        return List<Data>::operator==(compSetList);
    }

    // Inequality operator
    template <typename Data>
    bool SetLst<Data>::operator!=(const SetLst& compSetList) const noexcept {
        return !operator==(compSetList);
    }

    // Min
    template <typename Data>
    const Data& SetLst<Data>::Min() const {
        if(Empty()) { throw std::length_error("Set is empty"); }
        return List<Data>::Front();
    }

    // Min and remove
    template <typename Data>
    Data SetLst<Data>::MinNRemove() {
        if(Empty()) { throw std::length_error("Set is empty"); }
        return List<Data>::FrontNRemove();
    }

    // Remove min
    template <typename Data>
    void SetLst<Data>::RemoveMin() {
        if(Empty()) { throw std::length_error("Set is empty"); }
        List<Data>::RemoveFromFront();
    }

    // Max
    template <typename Data>
    const Data& SetLst<Data>::Max() const {
        if(Empty()) { throw std::length_error("Set is empty"); }
        return List<Data>::Back();
    }

    // Max and remove
    template <typename Data>
    Data SetLst<Data>::MaxNRemove() {
        if(Empty()) { throw std::length_error("Set is empty"); }
        return List<Data>::BackNRemove();
    }

    // Remove max
    template <typename Data>
    void SetLst<Data>::RemoveMax() {
        if(Empty()) { throw std::length_error("Set is empty"); }
        List<Data>::RemoveFromBack();
    }

    // Predecessor
    template <typename Data>
    const Data& SetLst<Data>::Predecessor(const Data& predKey) const {
        return (*PredecessorNode(predKey))->key;
    }

    // Predecessor and remove
    template <typename Data>
    Data SetLst<Data>::PredecessorNRemove(const Data& predKey) {
        Node** predNodePtrPtr = PredecessorNode(predKey);
        Data predData = (*predNodePtrPtr)->key;
        
        const bool isLastNode = predKey > Max();
        RemoveNode(predNodePtrPtr);

        if(isLastNode) {
            tail = [*this]() {
                Node* curr = head;
                for(ulong i=1;i<size;i++) curr = curr->next;
                return curr;
            }();
            std::cout << "Tail updated to: " << tail->key << std::endl;
            tail->next = nullptr;
        }

        return predData;
    }

    // Remove predecessor
    template <typename Data>
    void SetLst<Data>::RemovePredecessor(const Data& predKey) {
        PredecessorNRemove(predKey);
    }

    // Successor
    template <typename Data>
    const Data& SetLst<Data>::Successor(const Data& succKey) const {
        return (*SuccessorNode(succKey))->key;
    }

    // Successor and remove
    template <typename Data>
    Data SetLst<Data>::SuccessorNRemove(const Data& succKey) {
        Node** predNodePtrPtr = SuccessorNode(succKey);
        Data succData = (*predNodePtrPtr)->next->key;

        const bool isLastNode = succData == Max();
        RemoveNode(&((*predNodePtrPtr)->next));

        if(isLastNode) {
            tail = *predNodePtrPtr;
            tail->next = nullptr;
        }

        return succData;
    }

    // Remove successor
    template <typename Data>
    void SetLst<Data>::RemoveSuccessor(const Data& succKey) {
        SuccessorNRemove(succKey);
    }

    // Insert (copy)
    template <typename Data>
    bool SetLst<Data>::Insert(const Data& data) {
        Node** predNodePtrPtr = BinarySearchPred(data);

        if(ExistsNodeFromPred(predNodePtrPtr, data)) { return false; }

        Node* newNode = new Node(data);

        if(predNodePtrPtr == nullptr) {
            // Insert at the beginning
            newNode->next = head;
            head = newNode;
        } else {
            // Insert after the predecessor
            Node** newNodePtrPtr = Walk(predNodePtrPtr, 1);
            
            newNode->next = *newNodePtrPtr;
            *newNodePtrPtr = newNode;
        }
        
        if(newNode->next == nullptr) { tail = newNode; }

        size++;
        return true;
    }

    // Insert (move)
    template <typename Data>
    bool SetLst<Data>::Insert(Data&& data) {
        if(Exists(data)) { return false; }

        Node** predNodePtrPtr = BinarySearchPred(data);
        Node* newNode = new Node(std::move(data));

        if(predNodePtrPtr == nullptr) {
            // Insert at the beginning
            newNode->next = head;
            head = newNode;
        } else {
            // Insert after the predecessor
            Node** newNodePtrPtr = Walk(predNodePtrPtr, 1);
            
            newNode->next = *newNodePtrPtr;
            *newNodePtrPtr = newNode;
        }

        if(newNode->next == nullptr) { tail = newNode; }

        size++;
        return true;
    }

    // Remove
    template <typename Data>
    bool SetLst<Data>::Remove(const Data& delKey) {
        Node** predNodePtrPtr = BinarySearchPred(delKey);
        if(!ExistsNodeFromPred(predNodePtrPtr, delKey)) {
            return false; // Element not found
        }
        
        Node** delNodePtrPtr = Walk(predNodePtrPtr, 1);

        const bool isRemoved = RemoveNode(delNodePtrPtr);
        if(isRemoved && (*predNodePtrPtr)->next == nullptr) {
            tail = *predNodePtrPtr;
            tail->next = nullptr;
        }

        return isRemoved;
    }

    // Index operator (const version)
    template <typename Data>
    const Data& SetLst<Data>::operator[](ulong index) const {
        return List<Data>::operator[](index);
    }

    // Exists
    template <typename Data>
    bool SetLst<Data>::Exists(const Data& keyToSearch) const noexcept {
        Node** predNodePtrPtr = BinarySearchPred(keyToSearch);
        return ExistsNodeFromPred(predNodePtrPtr, keyToSearch);
    }

    // Clear
    template <typename Data>
    void SetLst<Data>::Clear() noexcept {
        List<Data>::Clear();
    }

    /* ************************************************************************** */

    // Binary search const version
    template<typename Data>
    SetLst<Data>::Node** SetLst<Data>::BinarySearchPred(const Data& keyToSearch) const noexcept{
        return const_cast<SetLst<Data>*>(this)->BinarySearchPred(keyToSearch);
    }

    // Binary search
    template <typename Data>
    SetLst<Data>::Node** SetLst<Data>::BinarySearchPred(const Data& keyToSearch) noexcept {

        if(Empty() || keyToSearch <= Min()) { return nullptr; }
        if(keyToSearch > Max()) { return &tail; }

        Node** prevNodePtrPtr = &head;
        ulong steps = size;

        while(steps > 1) {
            steps /= 2;
            Node** midPrevNodePtrPtr = Walk(prevNodePtrPtr, steps);

            Node* midPrevNodePtr = *midPrevNodePtrPtr;
            if(midPrevNodePtr->key < keyToSearch) {
                prevNodePtrPtr = midPrevNodePtrPtr; // è sbagliato, devi cambiarlo
            }
        }

        const Node* prevNodePtr = *prevNodePtrPtr;
        const bool isNotThePredecessorYet = (prevNodePtr->next != nullptr && prevNodePtr->next->key < keyToSearch);
        if(isNotThePredecessorYet) {
            prevNodePtrPtr = Walk(prevNodePtrPtr, 1);
        }

        return prevNodePtrPtr;

    }

    // Walk the list N steps forward
    template <typename Data>
    SetLst<Data>::Node** SetLst<Data>::Walk(Node** nodePtrPtr, ulong steps) const noexcept {
        for(ulong i = 0; i < steps; ++i) {
            nodePtrPtr = &((*nodePtrPtr)->next);
        }
        return nodePtrPtr;
    }

    // Remove single Node
    template <typename Data>
    bool SetLst<Data>::RemoveNode(Node** delNodePtrPtr) noexcept {
        if(Empty()) { return false; }
        if(*delNodePtrPtr == head) {
            List<Data>::RemoveFromFront();
            return true;
        }

        Node* delNodePtr = *delNodePtrPtr;

        *delNodePtrPtr = (*delNodePtrPtr)->next; // Link the node to the successor

        delete delNodePtr;
        size--;
        return true;
    }

    // Exists single Node
    template <typename Data>
    bool SetLst<Data>::ExistsNodeFromPred(Node** predNodePtrPtr, const Data& keyToSearch) const noexcept {
        if(Empty() || keyToSearch < Min() || keyToSearch > Max()) {
            return false;
        }

        if(keyToSearch == Min() || keyToSearch == Max()) {
            return true;
        }

        Node* predNodePtr = *predNodePtrPtr;
        return predNodePtr->next->key == keyToSearch;
    }

    // Predecessor atomic function
    template <typename Data>
    SetLst<Data>::Node** SetLst<Data>::PredecessorNode(const Data& predKey) const {
        if(Empty()) { throw std::length_error("Set is empty"); }
        if(predKey <= Min()) { throw std::length_error("No predecessor found"); }

        return BinarySearchPred(predKey);
    }

    // Successor atomic function (const version)
    template <typename Data>
    SetLst<Data>::Node** SetLst<Data>::SuccessorNode(const Data& succKey) const {
        return const_cast<SetLst<Data>*>(this)->SuccessorNode(succKey);
    }

    // Successor atomic function
    template <typename Data>
    SetLst<Data>::Node** SetLst<Data>::SuccessorNode(const Data& succKey) {
        if(Empty()) { throw std::length_error("Set is empty"); }
        if(succKey >= Max()) { throw std::length_error("No successor found"); }

        if(succKey < Min()) { return &head; }
        if(succKey == Min()) { return &(head->next); }
        
        Node** predNodePtrPtr = BinarySearchPred(succKey);

        Node* predNodePtr = *predNodePtrPtr;
        Node* currNodePtr = predNodePtr->next;
        if(currNodePtr->key == succKey) {
            return &((*predNodePtrPtr)->next);
        } else if(currNodePtr->key > succKey) {
            return predNodePtrPtr;
        } else {
            throw std::length_error("No successor found");
        }
    }

    /* ************************************************************************** */

}
