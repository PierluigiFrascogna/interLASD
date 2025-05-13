
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  class Container {

    private:

      // ...

    protected:

      ulong size = 0;

      /* ************************************************************************ */

      // Default constructor
      Container() = default;

    public:

      // Destructor
      virtual ~Container() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual Container& operator=(const Container&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual Container& operator=(Container&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const Container&) = delete; // Comparison of abstract types is not possible.
      virtual bool operator!=(const Container&) = delete; // Comparison of abstract types is not possible.

      /* ************************************************************************ */

      // Specific member functions

      virtual bool Empty() const noexcept {
        return size == 0;
      }; // (concrete function should not throw exceptions)

      virtual ulong Size() const noexcept {
        return size;
      }; // (concrete function should not throw exceptions)

  };

  /* ************************************************************************** */

  class ClearableContainer: virtual public Container {
    // Must extend Container

    private:

      // ...

    protected:

      ClearableContainer() = default; // Default constructor

    public:

      // Destructor
      virtual ~ClearableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual ClearableContainer& operator=(const ClearableContainer&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual ClearableContainer& operator=(ClearableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const ClearableContainer&) = delete; // Comparison of abstract types is not possible.
      virtual bool operator!=(const ClearableContainer&) = delete; // Comparison of abstract types is not possible.

      /* ************************************************************************ */

      // Specific member functions

      virtual void Clear() noexcept = 0;

  };

  /* ************************************************************************** */

  class ResizableContainer: virtual public ClearableContainer {
    // Must extend ClearableContainer

    private:

      // ...

    protected:

      ResizableContainer() = default; // Default constructor

    public:

      // Destructor
      virtual ~ResizableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual ResizableContainer& operator=(const ResizableContainer&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual ResizableContainer& operator=(ResizableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const ResizableContainer&) = delete; // Comparison of abstract types is not possible.
      virtual bool operator!=(const ResizableContainer&) = delete; // Comparison of abstract types is not possible.

      /* ************************************************************************ */

      // Specific member functions

      virtual void Resize(ulong newSize) noexcept = 0;

      /* ************************************************************************ */

      // Specific member function (inherited from ClearableContainer)

      virtual void Clear() noexcept override = 0; // Override ClearableContainer member

  };

  /* ************************************************************************** */

}

#endif
