#pragma once

#include <optional>
#include <vector>

namespace fsm {

template <typename E, typename S, typename A> struct Action {
  std::optional<E> event{};
  std::optional<A> action{};
  std::optional<S> newState{};
};

template <typename E, typename S, typename A> struct Transition {
  S state;
  std::vector<Action<E, S, A>> actions;
};

template <typename E, typename S, typename A> struct Fsm {
  S state;
  std::vector<Transition<E, S, A>> transitions;

  auto input(E event) -> std::optional<A> {
    for (auto t : transitions) {
      if (t.state == state) {
        for (auto a : t.actions) {
          if (!a.event || a.event == event) {
            if (a.newState) {
              state = a.newState.value();
            }
            return a.action;
          }
        }
      }
    }
    return {};
  }
};

}; // namespace fsm
