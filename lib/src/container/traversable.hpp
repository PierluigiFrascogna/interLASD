
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

  /* ************************************************************************** */

  template <typename Data>
  class TraversableContainer: virtual public TestableContainer<Data> {
    // Must extend TestableContainer<Data>

    private:

      // ...

    protected:

      TraversableContainer() = default;

    public:

      // Destructor
      virtual ~TraversableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual TraversableContainer& operator=(const TraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual TraversableContainer& operator=(TraversableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const TraversableContainer&) = delete; // Comparison of abstract types might be possible.
      virtual bool operator!=(const TraversableContainer&) = delete; // Comparison of abstract types might be possible.

      /* ************************************************************************ */

      // Specific member function

      using TraverseFun = std::function<void(const Data &)>;

      virtual void Traverse(TraverseFun) const = 0;

      template <typename Accumulator>
      using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

      template <typename Accumulator>
      virtual Accumulator Fold(FoldFun<Accumulator> func, Accumulator acc) const;

      /* ************************************************************************ */

      // Specific member function (inherited from TestableContainer)

      bool Exists(const Data&) const override; // Override TestableContainer member

  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderTraversableContainer: virtual public TraversableContainer<Data> {
    // Must extend TraversableContainer<Data>

    private:

      // ...

    protected:

      PreOrderTraversableContainer() = default;

    public:

      // Destructor
      virtual ~PreOrderTraversableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual PreOrderTraversableContainer& operator=(const PreOrderTraversableContainer& ) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual PreOrderTraversableContainer& operator=(PreOrderTraversableContainer&&) noexcept= delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual bool operator==(const TraversableContainer&) = delete; // Comparison of abstract types might be possible.
      virtual bool operator!=(const TraversableContainer&) = delete; // Comparison of abstract types might be possible.

      /* ************************************************************************ */

      // Specific member function

      using typename TraversableContainer<Data>::TraverseFun;

      virtual void PreOrderTraverse(TraverseFun) const = 0;

      template <typename Accumulator>
      using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

      template <typename Accumulator>
      inline Accumulator PreOrderFold(FoldFun<Accumulator> func, Accumulator acc) const;

      /* ************************************************************************ */

      // Specific member function (inherited from TraversableContainer)

      inline void Traverse(TraverseFun) const override {
        PreOrderTraverse(func);
      }; // Override TraversableContainer member

  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderTraversableContainer: virtual public TraversableContainer<Data> {
    // Must extend TraversableContainer<Data>

    private:

      // ...

    protected:

      // ...

    public:

      // Destructor
      virtual ~PostOrderTraversableContainer() = default;

      /* ************************************************************************ */

      // Copy assignment
      virtual PostOrderTraversableContainer& operator=(const PostOrderTraversableContainer&) = delete; // Copy assignment of abstract types is not possible.

      // Move assignment
      virtual PostOrderTraversableContainer& operator=(PostOrderTraversableContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

      /* ************************************************************************ */

      // Comparison operators
      virtual void operator==(const PostOrderTraversableContainer&) = delete; // Comparison of abstract types might be possible.
      virtual void operator!=(const PostOrderTraversableContainer&) = delete; // Comparison of abstract types might be possible.

      /* ************************************************************************ */

      // Specific member function

      using typename TraversableContainer<Data>::TraverseFun;

      virtual void PostOrderTraverse(TraverseFun) = 0;

      template <typename Accumulator>
      using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;

      template <typename Accumulator>
      virtual Accumulator PostOrderFold(FoldFun<Accumulator> func, Accumulator acc) const;

      /* ************************************************************************ */

      // Specific member function (inherited from TraversableContainer)

      inline void Traverse(TraverseFun func) const override {
        PostOrderTraverse(func);
      }; // Override TraversableContainer member

  };

  /* ************************************************************************** */

}

#include "traversable.cpp"

#endif
