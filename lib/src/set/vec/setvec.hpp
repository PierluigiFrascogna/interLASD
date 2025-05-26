
#ifndef SETVEC_HPP
#define SETVEC_HPP

/* ************************************************************************** */

#include "../set.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class SetVec: virtual public Set<Data>, virtual protected ResizableContainer, virtual protected Vector<Data> {
    // Must extend Set<Data>,
    //             ResizableContainer

    private:

      // ...

    protected:

      using Container::Empty;
      using Container::size;

      using Vector<Data>::elements;

      ulong head = 0;
      ulong memorySize = 0;

    public:

      // Default constructor
      SetVec();

      /* ************************************************************************ */

      // Specific constructors
      SetVec(const TraversableContainer<Data>&); // A set obtained from a TraversableContainer
      SetVec(MappableContainer<Data>&&); // A set obtained from a MappableContainer

      /* ************************************************************************ */

      // Copy constructor
      SetVec(const SetVec&);

      // Move constructor
      SetVec(SetVec&&) noexcept;

      /* ************************************************************************ */

      // Destructor
      ~SetVec();

      /* ************************************************************************ */

      // Copy assignment
      SetVec& operator=(const SetVec&);

      // Move assignment
      SetVec& operator=(SetVec&&) noexcept;

      /* ************************************************************************ */

      // Comparison operators
      bool operator==(const SetVec&) const noexcept;
      bool operator!=(const SetVec&) const noexcept;

      /* ************************************************************************ */

      // Specific member functions (inherited from OrderedDictionaryContainer)

      const Data& Min() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
      Data MinNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
      void RemoveMin() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

      const Data& Max() const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
      Data MaxNRemove() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)
      void RemoveMax() override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when empty)

      const Data& Predecessor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
      Data PredecessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
      void RemovePredecessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

      const Data& Successor(const Data&) const override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
      Data SuccessorNRemove(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)
      void RemoveSuccessor(const Data&) override; // Override OrderedDictionaryContainer member (concrete function must throw std::length_error when not found)

      /* ************************************************************************ */

      // Specific member functions (inherited from DictionaryContainer)

      bool Insert(const Data&) override; // Override DictionaryContainer member (copy of the value)
      bool Insert(Data&&) override; // Override DictionaryContainer member (move of the value)
      bool Remove(const Data&) override; // Override DictionaryContainer member

      /* ************************************************************************ */

      // Specific member functions (inherited from LinearContainer)

      const Data& operator[](ulong) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

      /* ************************************************************************** */

      // Specific member function (inherited from TestableContainer)

      bool Exists(const Data&) const noexcept override; // Override TestableContainer member

      /* ************************************************************************ */

      // Specific member function (inherited from ClearableContainer)

      void Clear() noexcept override; // Override ClearableContainer member

    protected:

      // Auxiliary functions, if necessary!

      // Binary search
      ulong BinarySearchIndex(const Data&) const noexcept;
      // Resize
      inline void Resize(ulong) noexcept override;

      // Shift the elements from index to the left
      void ShiftFromIndexToHead(ulong) noexcept;

      // Shift the elements from index to the right
      void ShiftFromIndexToTail(ulong) noexcept;

      // Shift the elements from left to index
      void ShiftFromHeadToIndex(ulong) noexcept;

      // Shift the elements from right to index
      void ShiftFromTailToIndex(ulong) noexcept;

      // index operator (mutable version)
      Data& operator[](ulong) override;

  };

  /* ************************************************************************** */

}

#include "setvec.cpp"

#endif
