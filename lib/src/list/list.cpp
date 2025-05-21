
namespace lasd {

    /* ************************************************************************** */

    // Constructor for a list obtained from a TraversableContainer
    template <typename Data>
    List<Data>::List(const TraversableContainer<Data>& travCont) {
        travCont.Traverse(
            [this](const Data& data){
                InsertAtBack(data);
            }
        );
    }

    // Constructor for a list obtained from a MappableContainer
    template <typename Data>
    List<Data>::List(MappableContainer<Data>&& mapCont) {
        mapCont.Map(
            [this](Data& data){
                InsertAtBack(std::move(data));
            }
        );
    }

    // Copy constructor
    template <typename Data>
    List<Data>::List(const List& copyList) {
        copyList.Traverse(
            [this](const Data& data) {
                InsertAtBack(data);
            }
        );
    }

    // Move constructor
    template <typename Data>
    List<Data>::List(List&& moveList) noexcept {
        std::swap(head, moveList.head);
        std::swap(tail, moveList.tail);
        std::swap(size, moveList.size);
    }

    // Destructor
    template <typename Data>
    List<Data>::~List() {
        Clear();
    }

    // Copy assignment
    template <typename Data>
    List<Data>& List<Data>::operator=(const List& copyList) {
        if (*this != copyList) {
            Clear();
            copyList.Traverse(
                [this](const Data& data) {
                    InsertAtBack(data);
                }
            );
        }
        return *this;
    }

    // Move assignment
    template <typename Data>
    List<Data>& List<Data>::operator=(List&& moveList) noexcept {
        if (this != &moveList) {
            std::swap(head, moveList.head);
            std::swap(tail, moveList.tail);
            std::swap(size, moveList.size);
        }
        return *this;
    }

    // Equality operator
    template <typename Data>
    bool List<Data>::operator==(const List& compList) const noexcept {
        if (Empty() && compList.Empty()) { return true; }
        if (this == &compList) { return true; }
        if (size != compList.size) { return false; }

        Node* listCurrNode = head;
        Node* compListCurrNode = compList.head;
        for(ulong i = 0; i < size; i++) {
            if (listCurrNode->key != compListCurrNode->key) { return false; }
            listCurrNode = listCurrNode->next;
            compListCurrNode = compListCurrNode->next;
        }
        return true;
    }

    // Inequality operator
    template <typename Data>
    bool List<Data>::operator!=(const List& compList) const noexcept {
        return !operator==(compList);
    }

    // Insert at front (copy)
    template <typename Data>
    void List<Data>::InsertAtFront(const Data& data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        if(Empty()) { tail = newNode; }
        size++;
    }

    // Insert at front (move)
    template <typename Data>
    void List<Data>::InsertAtFront(Data&& data) {
        Node* newNode = new Node(std::move(data));
        newNode->next = head;
        head = newNode;
        if(Empty()) { tail = newNode; }
        size++;
    }

    // Remove from front
    template <typename Data>
    void List<Data>::RemoveFromFront() {
        if (Empty()) { throw std::length_error("List is empty"); }
        Node* delNode = head;
        head = head->next;
        delete delNode;
        if (Size() == 1) { tail = nullptr; }
        size--;
    }

    // Front and remove
    template <typename Data>
    Data List<Data>::FrontNRemove() {
        if (Empty()) { throw std::length_error("List is empty"); }
        Data frontData = Front();
        RemoveFromFront();
        return frontData;
    }

    // Insert at back (copy)
    template <typename Data>
    void List<Data>::InsertAtBack(const Data& data) {
        Node* newNode = new Node(data);
        if (Empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Insert at back (move)
    template <typename Data>
    void List<Data>::InsertAtBack(Data&& data) {
        Node* newNode = new Node(std::move(data));
        if (Empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Remove from back
    template <typename Data>
    void List<Data>::RemoveFromBack() {
        if (Empty()) { throw std::length_error("List is empty"); }
        if (size == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        size--;
    }

    // Back and remove
    template <typename Data>
    Data List<Data>::BackNRemove() {
        if (Empty()) { throw std::length_error("List is empty"); }
        Data backData = Back();
        RemoveFromBack();
        return backData;
    }

    // index operator (mutable version)
    template <typename Data>
    inline Data& List<Data>::operator[](ulong index) {
        return const_cast<Data&>(static_cast<const List<Data>*>(this)->operator[](index));
    }

    // Front element (mutable version)
    template <typename Data>
    inline Data& List<Data>::Front() {
        return const_cast<Data&>(static_cast<const List<Data>*>(this)->Front());
    }

    // Back element (mutable version)
    template <typename Data>
    inline Data& List<Data>::Back() {
        return const_cast<Data&>(static_cast<const List<Data>*>(this)->Back());
    }

    // index operator (non-mutable version)
    template <typename Data>
    inline const Data& List<Data>::operator[](ulong index) const {
        if (index >= size) { throw std::out_of_range("Index out of range"); }

        Node* currNode = head;
        for (ulong i = 0; i < index; i++) {
            currNode = currNode->next;
        }
        return currNode->key;
    }

    // Front element (non-mutable version)
    template <typename Data>
    inline const Data& List<Data>::Front() const {
        if (Empty()) { throw std::length_error("List is empty"); }
        return head->key;
    }

    // Back element (non-mutable version)
    template <typename Data>
    inline const Data& List<Data>::Back() const {
        if (Empty()) { throw std::length_error("List is empty"); }
        return tail->key;
    }

    // Map function
    template <typename Data>
    void List<Data>::Map(MapFun func) {
        PreOrderMap(func);
    }

    // PreOrderMap function
    template <typename Data>
    void List<Data>::PreOrderMap(MapFun func) {
        Node* currNode = head;
        while (currNode != nullptr) {
            func(currNode->key);
            currNode = currNode->next;
        }
    }

    // PostOrderMap function
    template <typename Data>
    void List<Data>::PostOrderMap(MapFun func) {
        Node* currNode = head;
        PostOrderMapHelper(func, currNode);
    }

    // Traverse function
    template <typename Data>
    void List<Data>::Traverse(TraverseFun func) const {
        PreOrderTraverse(func);
    }

    // PreOrderTraverse function
    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun func) const {
        Node* currNode = head;
        while (currNode != nullptr) {
            func(currNode->key);
            currNode = currNode->next;
        }
    }

    // PostOrderTraverse function
    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun func) const {
        Node* currNode = head;
        PostOrderTraverseHelper(func, currNode);
    }

    // Clear function
    template <typename Data>
    void List<Data>::Clear() noexcept {
        Node *currNode = head;
        while (currNode != nullptr) {
            Node* delNode = currNode;
            currNode = currNode->next;
            delete delNode;
        }
        head = tail = nullptr;
        size = 0;
    }

    /* ************************************************************************** */

    // PostOrderMap helper function
    template <typename Data>
    void List<Data>::PostOrderMapHelper(MapFun func, Node* node) {
        if (node == nullptr) { return; }
        PostOrderMapHelper(func, node->next);
        func(node->key);
    }

    // PostOrderTraverse helper function
    template <typename Data>
    void List<Data>::PostOrderTraverseHelper(TraverseFun func, Node* node) const {
        if (node == nullptr) { return; }
        PostOrderTraverseHelper(func, node->next);
        func(node->key);
    }

    /* ************************************************************************** */

}
