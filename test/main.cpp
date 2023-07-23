#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "fsm.h"

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

const auto transitions = std::vector<fsm::Transition<Event, State, Action>>{
    {
        .state = Top,
        .actions =
            {
                {
                    .event = ButtonUp,
                },
                {
                    .event = ButtonDown,
                    .action = MoveDown,
                    .newState = Bottom,
                },
            },
    },
    {
        .state = Bottom,
        .actions =
            {
                {
                    .event = ButtonDown,
                },
                {
                    .event = ButtonUp,
                    .action = MoveUp,
                    .newState = Top,
                },
            },
    },
};

auto elevator = fsm::Fsm<Event, State, Action>{
    .state = Top,
    .transitions = transitions,
};

TEST_CASE("Create an FSM") {
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
