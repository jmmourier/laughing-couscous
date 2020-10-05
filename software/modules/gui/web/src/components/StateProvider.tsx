import React, { Dispatch, FunctionComponent, Reducer, useReducer } from "react";
import { act } from "react-dom/test-utils";

export const TICKS_PER_ROTATION = 360;
export const WHEEL_WIDTH = 0.02;
export const WHEEL_RADIUS_M = 0.05;
export const WHEEL_PERIMETER = Math.PI * 2 * WHEEL_RADIUS_M;
export const SPACE_BETWEEN_WHEELS = 0.2;

type IRobotPositionState = {
  x: number;
  y: number;
  angleRad: number;
};

export type IAction = {
  type: ActionEnum.UPDATE_POSITION;
  position: IRobotPositionState;
};

const initialState: IRobotPositionState = {
  x: 0,
  y: 0,
  angleRad: 0,
};

/**
 * Available callable actions
 */
enum ActionEnum {
  UPDATE_POSITION = "UPDATE_POSITION",
}

const context = React.createContext<{
  state: IRobotPositionState;
  dispatch: Dispatch<IAction>;
}>({
  state: initialState,
  dispatch: () => null,
});

const reducer: Reducer<IRobotPositionState, IAction> = (
  state: IRobotPositionState,
  action: IAction
) => {
  switch (action.type) {
    case ActionEnum.UPDATE_POSITION:
      console.log(action.position.x);
      return {
        x: action.position.x,
        y: action.position.y,
        angleRad: action.position.angleRad,
      };
    default:
      throw new Error();
  }
};

const StateProvider: FunctionComponent = ({ children }) => {
  const [state, dispatch] = useReducer<Reducer<IRobotPositionState, IAction>>(
    reducer,
    initialState
  );

  const { Provider } = context;

  return <Provider value={{ state, dispatch }}>{children}</Provider>;
};

export { context, ActionEnum };
export default StateProvider;
