open ReasonUnstated;

module StateContainer =
  MakeContainer({
    type state = string;
    type value = (string, (string => string) => unit);
    let useHook = initial => React.useState(() => initial);
  });

module StateDisplay = {
  [@react.component]
  let make = () => {
    let (s, set) = StateContainer.useContainer();
    <div onClick={_ => set(prev => prev ++ "s")}> {React.string(s)} </div>;
  };
};