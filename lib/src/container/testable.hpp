
#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class TestableContainer: virtual public Container {
    // Must extend Container

    private:

      // ...

    protected:

      TestableContainer() = default; // Default constructor

    public:

      // Destructor
      virtual ~TestableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual TestableContainer& operator=(const TestableContainer&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual TestableContainer& operator=(const TestableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const TestableContainer&) = delete; // Comparison of abstract types is not possible.
      virtual bool operator!=(const TestableContainer&) = delete; // Comparison of abstract types is not possible.

      /* ************************************************************************ */

      // Specific member function

      virtual bool Exists(const Data&) noexcept = 0; // (concrete function should not throw exceptions)

  };

  /* ************************************************************************** */

}

#endif
