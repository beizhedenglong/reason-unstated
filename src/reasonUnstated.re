exception Error(string);

module type ContainerType = {
  type state;
  type value;
  let useHook: state => value;
};

module MakeContainer = (Container: ContainerType) => {
  module Provider = {
    module ContextProvider = {
      let context = React.createContext(None);
      let makeProps = (~initialState, ~children, ()) => {
        "value": initialState,
        "children": children,
      };
      let make = React.Context.provider(context);
    };
    [@react.component]
    let make = (~initialState, ~children) => {
      let value = Container.useHook(initialState);
      <ContextProvider initialState={Some(value)}>
        children
      </ContextProvider>;
    };
  };

  let useContainer = () => {
    let value = React.useContext(Provider.ContextProvider.context);
    switch (value) {
    | None =>
      raise(Error("Component must be wrapped with Container.Provider"))
    | Some(v) => v
    };
  };
};