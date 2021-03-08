import React, { Dispatch, FunctionComponent, Reducer, useReducer } from "react";

export const TICKS_PER_ROTATION = 360;
export const WHEEL_WIDTH = 0.02;
export const WHEEL_RADIUS_M = 0.05;
export const WHEEL_PERIMETER = Math.PI * 2 * WHEEL_RADIUS_M;
export const SPACE_BETWEEN_WHEELS = 0.2;

export type IRobotPosition = {
  x_m: number;
  y_m: number;
  orientation_rad: number;
};

export type IAction = {
  type: Action.UPDATE_POSITION;
  position: IRobotPosition;
};

const initialState: IRobotPosition = {
  x_m: 0,
  y_m: 0,
  orientation_rad: 0,
};

/**
 * Available callable actions
 */
enum Action {
  UPDATE_POSITION = "UPDATE_POSITION",
}

const context = React.createContext<{
  state: IRobotPosition;
  dispatch: Dispatch<IAction>;
}>({
  state: initialState,
  dispatch: () => null,
});

const reducer: Reducer<IRobotPosition, IAction> = (
  state: IRobotPosition,
  action: IAction
) => {
  switch (action.type) {
    case Action.UPDATE_POSITION:
      return {
        x_m: action.position.x_m,
        y_m: action.position.y_m,
        orientation_rad: action.position.orientation_rad,
      };
    default:
      throw new Error();
  }
};

const StateProvider: FunctionComponent = ({ children }) => {
  const [state, dispatch] = useReducer<Reducer<IRobotPosition, IAction>>(
    reducer,
    initialState
  );

  const { Provider } = context;

  return <Provider value={{ state, dispatch }}>{children}</Provider>;
};

export { context, Action };
export default StateProvider;
