
namespace lasd {

    /* ************************************************************************** */
    
    template <typename Data>
    bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& travCont) {
        bool allInserted = true;
        travCont.Traverse(
            [this, &allInserted](const Data& val) {
                allInserted &= Insert(val);
            }
        );
        return allInserted;
    };
    
    template <typename Data>
    bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& mapCont) {
        bool allInserted = true;
        mapCont.Map(
            [this, &allInserted](Data& val) {
                allInserted &= Insert(std::move(val));
            }
        );
        return allInserted;
    };
    
    template <typename Data>
    bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& travCont) {
        bool allRemoved = true;
        travCont.Traverse(
            [this, &allRemoved](const Data& val) {
                allRemoved &= Remove(val);
            }
        );
        return allRemoved;
    };
    
    template <typename Data>
    bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& travCont) {
        bool someInserted = false;
        travCont.Traverse(
            [this, &someInserted](const Data& val) {
                someInserted |= Insert(val);
            }
        );
        return someInserted;
    };
    
    template <typename Data>
    bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& mapCont) {
        bool someInserted = false;
        mapCont.Map(
            [this, &someInserted](Data& val) {
                someInserted |= Insert(std::move(val));
            }
        );
        return someInserted;
    };
    
    template <typename Data>
    bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& travCont) {
        bool someRemoved = false;
        travCont.Traverse(
            [this, &someRemoved](const Data& val) {
                someRemoved |= Remove(val);
            }
        );
        return someRemoved;
    };

    /* ************************************************************************** */

}
