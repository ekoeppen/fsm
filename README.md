# FSM

A simple finite state machine implementation in a single header in C++14 for
use in embedded targets.

## Design

The FSM uses a list of possible transitions which are defined as a tuple
of:

- the state to which the transition applies
- the event which will trigger the transition
- an optional action identifier
- an optional new state if the transition is activated

The transition is a templated `struct`, which takes the event, state and
action types as template parameters. The state and event types need to
support the `==` operator (in C++20 terms `equality_comparable`).

An FSM is a `struct` containing the transitions as well as the current state,
and it provides one member function (`input`). The `input` function takes
an event as parameter, and returns the optional action for the matching
transition. It also changes the state of the FSM accordingly.

## Implementation

The implementation is aimed at embedded targets, and therefore uses dedicated
datatypes for the `Optional` and `Array` data structures instead of the C++
standard library. The transitions are initialized from a C array of the
`Transition` structure.

Unit tests are implemented using [doctest](https://github.com/doctest/doctest)

## Example

The file [test/elevator.h](test/elevator.h) contains an FSM for a simple elevator
with two stops. It uses `enum`s for the state, action and event types:

```c++
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
```

The possible transitions are defined in a C style array:

```c++
constexpr fsm::Transition<Event, State, Action> transitions[] = {
    {.state = Top, .event = ButtonUp},
    {.state = Top, .event = ButtonDown, .action = MoveDown, .newState = Bottom},
    {.state = Bottom, .event = ButtonDown},
    {.state = Bottom, .event = ButtonUp, .action = MoveUp, .newState = Top},
};
```

The actual FSM ties together the transitions and the state with its initial
value:

```c++
auto elevator = fsm::Fsm<Event, State, Action>{
    .state = Top,
    .transitions = transitions,
};
```

On handling the `ButtonDown` event, the FSM's `input` function returns `MoveDown`
as the action and changes the state to `Botton`:

```c++
CHECK(elevator.input(ButtonDown) == MoveDown);
CHECK(elevator.state == Bottom);
```
