
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class PQHeap: virtual public PQ<Data>, virtual protected HeapVec<Data> {
    // Must extend PQ<Data>,
    // Could extend HeapVec<Data>

    private:

      // ...

    protected:

      // using Container::???;

      using Vector<Data>::Resize;

      using HeapVec<Data>::size;
      using HeapVec<Data>::elements;
      using HeapVec<Data>::IsHeap;

      ulong memorySize = 0;

    public:

      // Default constructor
      PQHeap();

      /* ************************************************************************ */

      // Specific constructors
      PQHeap(const TraversableContainer<Data>&); // A priority queue obtained from a TraversableContainer
      PQHeap(MappableContainer<Data>&&); // A priority queue obtained from a MappableContainer

      /* ************************************************************************ */

      // Copy constructor
      PQHeap(const PQHeap&);

      // Move constructor
      PQHeap(PQHeap&&) noexcept;

      /* ************************************************************************ */

      // Destructor
      ~PQHeap();

      /* ************************************************************************ */

      // Copy assignment
      PQHeap& operator=(const PQHeap&);

      // Move assignment
      PQHeap& operator=(PQHeap&&) noexcept;

      /* ************************************************************************ */

      // Specific member functions (inherited from PQ)

      const Data& Tip(); // Override PQ member (must throw std::length_error when empty)
      void RemoveTip(); // Override PQ member (must throw std::length_error when empty)
      Data TipNRemove(); // Override PQ member (must throw std::length_error when empty)

      void Insert(const Data&); // Override PQ member (Copy of the value)
      void Insert(Data&&) noexcept; // Override PQ member (Move of the value)

      void Change(ulong, const Data&); // Override PQ member (Copy of the value)
      void Change(ulong, Data&&) noexcept; // Override PQ member (Move of the value)

    protected:

      // Auxiliary functions, if necessary!

      // Heapify from index to the root
      void HeapifyUp(ulong) noexcept;

      // Heapify from index to the leaves
      void HeapifyDown(ulong) noexcept;

  };

  /* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
