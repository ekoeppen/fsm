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

template <typename E, typename S, typename A> struct Transition {
  S state;
  Optional<E> event{};
  Optional<A> action{};
  Optional<S> newState{};
};

template <typename E, typename S, typename A, auto transitions> struct Fsm {
  S state;

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
