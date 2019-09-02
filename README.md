# Reason Unstated 
![badge](https://action-badges.now.sh/beizhedenglong/reason-unstated)

`Reason Unstated` is a reason implementation of [`unstated-next`](https://github.com/jamiebuilds/unstated-next).
A simple state management library that help you share `hook` state and logical easily.

- **Hooks:** Use them for all your state management.
- **Small Size:** It only contains dozens of lines code. 
- **Familiar API:** Just use React as intended.
- **Minimal API:** It only contains one API.
  
## Installation
1. `yarn add reason-unstated`
2. add `reason-unstated` to `bs-dependencies` in your `bsconfig.json`:
  ```json
    "bs-dependencies": [
      "reason-react",
      "reason-unstated"
    ],
  ```
## Example

```reason
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
  </div>,
  "app",
);
```
