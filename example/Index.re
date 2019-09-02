open State;

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

module CounterDisplay = {
  [@react.component]
  let make = () => {
    let counter = CounterContainer.useContainer();
    <div>
      {React.string("count: ")}
      {counter.count |> string_of_int |> React.string}
      <button onClick={_ => counter.inc()}> {React.string("+1")} </button>
      <button onClick={_ => counter.dec()}> {React.string("-1")} </button>
    </div>;
  };
};

ReactDOMRe.renderToElementWithId(
  <div>
    <CounterContainer.Provider initialState=0>
      <CounterDisplay />
      <CounterDisplay />
      <CounterContainer.Provider initialState=3>
        <CounterDisplay />
        <CounterDisplay />
      </CounterContainer.Provider>
    </CounterContainer.Provider>
    <StateContainer.Provider initialState="hello">
      <StateDisplay />
      <StateDisplay />
    </StateContainer.Provider>
  </div>,
  "app",
);