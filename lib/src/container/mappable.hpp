
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class MappableContainer: virtual public TraversableContainer<Data> {
    // Must extend TraversableContainer<Data>

    private:

      // ...

    protected:

      // ...

    public:

      // Destructor
      virtual ~MappableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual MappableContainer& operator=(const MappableContainer&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual MappableContainer& operator=(const MappableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const MappableContainer&) = delete; // Comparison of abstract types is not possible.
      virtual bool operator!=(const MappableContainer&) = delete; // Comparison of abstract types is not possible.

      /* ************************************************************************ */

      // Specific member function

      using MapFun = std::function<void(Data &)>;

      void Map(MapFun) = 0;

  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderMappableContainer: virtual public MappableContainer<Data>, virtual public PreOrderTraversableContainer<Data> {
    // Must extend MappableContainer<Data>,
    //             PreOrderTraversableContainer<Data>

    private:

      // ...

    protected:

      // ...

    public:

      // Destructor
      virtual ~PreOrderMappableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual const PreOrderMappableContainer& operator=(const PreOrderMappableContainer&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual const PreOrderMappableContainer& operator=(const PreOrderMappableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const MappableContainer&) specifiers; // Comparison of abstract types is not possible.
      virtual bool operator!=(const MappableContainer&) specifiers; // Comparison of abstract types is not possible.

      /* ************************************************************************ */

      // Specific member function

      using typename MappableContainer<Data>::MapFun;

      virtual void PreOrderMap(MapFun) = 0;

      /* ************************************************************************ */

      // Specific member function (inherited from MappableContainer)

      inline void Map(MapFun) override {
        PreOrderMap(func);
      }; // Override MappableContainer member

  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderMappableContainer: virtual public MappableContainer<Data>, virtual public PostOrderTraversableContainer<Data> {
    // Must extend MappableContainer<Data>,
    //             PostOrderTraversableContainer<Data>

    private:

      // ...

    protected:

      // ...

    public:

      // Destructor
      virtual ~PostOrderMappableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual const PostOrderMappableContainer& operator=(const PostOrderMappableContainer&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual const PostOrderMappableContainer& operator=(const PostOrderMappableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const PostOrderMappableContainer) = delete; // Comparison of abstract types is not possible.
      virtual bool operator!=(const PostOrderMappableContainer) = delete; // Comparison of abstract types is not possible.

      /* ************************************************************************ */

      // Specific member function

      using typename MappableContainer<Data>::MapFun;

      virtual void PostOrderMap(MapFun) = 0;

      /* ************************************************************************ */

      // Specific member function (inherited from MappableContainer)

      inline void Map(MapFun) override {
        PostOrderMap(func);
      }; // Override MappableContainer member

  };

  /* ************************************************************************** */

}

#include "mappable.cpp"

#endif
