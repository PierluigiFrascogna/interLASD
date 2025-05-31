
#ifndef PQ_HPP
#define PQ_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class PQ: virtual public LinearContainer<Data>, virtual public ClearableContainer {
    // Must extend LinearContainer<Data>,
    //             ClearableContainer

    private:

    protected:

    public:

      // Destructor
      ~PQ() = default;

      /* ************************************************************************ */

      // Copy assignment
      PQ& operator=(const PQ&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      PQ& operator=(PQ&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Specific member functions

      const Data& Tip() = 0; // (concrete function must throw std::length_error when empty)
      void RemoveTip() = 0; // (concrete function must throw std::length_error when empty)
      Data TipNRemove() = 0; // (concrete function must throw std::length_error when empty)

      void Insert(const Data&) = 0; // Copy of the value
      void Insert(Data&&) noexcept = 0; // Move of the value

      void Change(const Data&) = 0; // Copy of the value
      void Change(Data&&) noexcept = 0; // Copy of the value

  };

  /* ************************************************************************** */

}

#endif
