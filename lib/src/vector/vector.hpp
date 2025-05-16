
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class Vector: virtual public MutableLinearContainer<Data>, virtual public ResizableContainer {
    // Must extend MutableLinearContainer<Data>,
    //             ResizableContainer

    private:

      // ...

    protected:

      using Container::size;

      Data* elements = nullptr;

    public:

      // Default constructor
      Vector() = default;

      /* ************************************************************************ */

      // Specific constructors
      Vector(const ulong size); // A vector with a given initial dimension
      Vector(const TraversableContainer<Data>& travCont); // A vector obtained from a TraversableContainer
      Vector(const MappableContainer<Data>& mapCont); // A vector obtained from a MappableContainer

      /* ************************************************************************ */

      // Copy constructor
      Vector(const Vector& copyVec);

      // Move constructor
      Vector(Vector&& moveVec) noexcept;

      /* ************************************************************************ */

      // Destructor
      ~Vector();

      /* ************************************************************************ */

      // Copy assignment
      Vector& operator=(const Vector& copyVec);

      // Move assignment
      Vector& operator=(Vector&&) noexcept;

      /* ************************************************************************ */

      // Comparison operators
      bool operator==(const Vector&) const noexcept;
      bool operator!=(const Vector&) const noexcept;

      /* ************************************************************************ */

      // Specific member functions (inherited from MutableLinearContainer)

      Data& operator[](ulong index) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

      Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

      Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

      /* ************************************************************************ */

      // Specific member functions (inherited from LinearContainer)

      const Data& operator[](ulong index) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

      const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

      const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

      /* ************************************************************************ */

      // Specific member function (inherited from ResizableContainer)

      void Resize(ulong newSize) noexcept override; // Override ResizableContainer member

      /* ************************************************************************ */

      // Specific member function (inherited from ClearableContainer)

      void Clear() noexcept override; // Override ClearableContainer member

    protected:

      // Auxiliary functions, if necessary!

  };

  /* ************************************************************************** */

  template <typename Data>
  class SortableVector {
    // Must extend Vector<Data>,
    //             SortableLinearContainer<Data>

    private:

      // ...

    protected:

      // using Container::???;

      // ...

    public:

      // Default constructor
      // SortableVector() specifiers;

      /* ************************************************************************ */

      // Specific constructors
      // SortableVector(argument) specifiers; // A vector with a given initial dimension
      // SortableVector(argument) specifiers; // A vector obtained from a TraversableContainer
      // SortableVector(argument) specifiers; // A vector obtained from a MappableContainer

      /* ************************************************************************ */

      // Copy constructor
      // SortableVector(argument) specifiers;

      // Move constructor
      // SortableVector(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~SortableVector() specifiers;

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

    protected:

      // Auxiliary functions, if necessary!

  };

  /* ************************************************************************** */

}

#include "vector.cpp"

#endif
