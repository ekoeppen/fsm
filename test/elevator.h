#pragma once

#include "doctest.h"
#include "fsm.h"

namespace elevator {

enum State {
  Top,
  Bottom,
};

enum Action {
  MoveUp,
  MoveDown,
};

enum Event {
  ButtonUp,
  ButtonDown,
};

constexpr fsm::Transition<Event, State, Action> transitions[] = {
    {.state = Top, .event = ButtonUp},
    {.state = Top, .event = ButtonDown, .action = MoveDown, .newState = Bottom},
    {.state = Bottom, .event = ButtonDown},
    {.state = Bottom, .event = ButtonUp, .action = MoveUp, .newState = Top},
};

auto elevator = fsm::Fsm<Event, State, Action>{
    .state = Top,
    .transitions = transitions,
};

TEST_CASE("Elevator") {
  CHECK(elevator.state == Top);
  CHECK(!elevator.input(ButtonUp));
  CHECK(elevator.state == Top);
  CHECK(elevator.input(ButtonDown) == MoveDown);
  CHECK(elevator.state == Bottom);
  CHECK(!elevator.input(ButtonDown));
  CHECK(elevator.state == Bottom);
  CHECK(elevator.input(ButtonUp) == MoveUp);
  CHECK(elevator.state == Top);
}

} // namespace elevator
