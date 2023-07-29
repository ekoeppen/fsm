#pragma once

#include <cstddef>

namespace fsm {

template <typename T> struct Optional {
  T value;
  bool hasValue;

  constexpr Optional() : value{}, hasValue(false) {}
  constexpr Optional(T t) : value(t), hasValue(true) {}
  operator bool() const { return hasValue; }
  auto operator==(T t) const -> bool { return hasValue && value == t; }
  auto operator!=(T t) const -> bool { return !hasValue || value != t; }
};

template <typename T> struct Array {
  typedef const T *const_pointer;
  typedef const T *const_iterator;

  template <size_t initSize>
  constexpr Array(T const (&initPtr)[initSize])
      : beginPtr(initPtr), endPtr(initPtr + initSize) {}

  const_iterator begin() { return beginPtr; }
  const_iterator end() const { return endPtr; }

  const_pointer beginPtr;
  const_pointer endPtr;
};

template <typename E, typename S, typename A> struct Transition {
  S state;
  Optional<E> event{};
  Optional<A> action{};
  Optional<S> newState{};
};

template <typename E, typename S, typename A> struct Fsm {
  S state;
  Array<Transition<E, S, A>> transitions;

  auto input(E event) -> Optional<A> {
    for (auto t : transitions) {
      if (t.state == state && (!t.event || t.event == event)) {
        if (t.newState) {
          state = t.newState.value;
        }
        return t.action;
      }
    }
    return Optional<A>{};
  }
};

}; // namespace fsm
