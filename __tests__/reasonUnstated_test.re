open Jest;
open Expect;
open ReasonHooksTestingLibrary.Testing;
type counterType = {
  count: int,
  set: (int => int) => unit,
  inc: unit => unit,
  dec: unit => unit,
};
let useCounter = initial => {
  let (count, set) = React.useState(() => initial);
  {
    count,
    set,
    inc: () => set(prev => prev + 1),
    dec: () => set(prev => prev - 1),
  };
};

module CounterContainer =
  ReasonUnstated.MakeContainer({
    type state = int;
    type value = counterType;
    let useHook = useCounter;
  });

module App = {
  [@react.component]
  let make = (~children) =>
    <CounterContainer.Provider initialState=0>
      children
    </CounterContainer.Provider>;
};

describe("useContext", () => {
  open Result;

  let options = Options.t(~wrapper=App.make, ());

  let container = renderHook(CounterContainer.useContainer, ~options, ());
  test("counter is 0", () =>
    expect(container->result->current.count) |> toEqual(0)
  );
  test("counter is 1", () => {
    act(() => container->result->current.set(prev => prev + 1));
    expect(container->result->current.count) |> toEqual(1);
  });
  test("counter is 2", () => {
    act(() => container->result->current.set(prev => prev + 1));
    expect(container->result->current.count) |> toEqual(2);
  });
});