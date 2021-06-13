import React, { FunctionComponent, useMemo, useState } from "react";
import {
  Empty,
  OrientationRequest,
  RobotDataRequest,
  PositionRequest,
  SpeedRequest,
  ActionType,
} from "generated_grpc_sources/robot_pb";

export const TICKS_PER_ROTATION = 360;
export const WHEEL_WIDTH = 0.05;
export const WHEEL_RADIUS_M = 0.05;
export const WHEEL_PERIMETER = Math.PI * 2 * WHEEL_RADIUS_M;
export const SPACE_BETWEEN_WHEELS = 0.252;
export const ROBOT_FRAME_LENGTH = 0.155;
export const ROBOT_FRAME_WIDTH = SPACE_BETWEEN_WHEELS - 2 * WHEEL_RADIUS_M;

export type IPosition = {
  x_m: number;
  y_m: number;
};

export type IRobotData = {
  x_m: number;
  y_m: number;
  orientation_rad: number;
  battery_v: number;
  is_grabber_open: boolean;
  mission_started_at: number;
  mission_ended_at: number;
  current_action: ActionType;
};

interface IState {
  robotData: IRobotData;
  targetPosition?: IPosition;
}

const defaultState: IState = {
  robotData: {
    x_m: 0,
    y_m: 0,
    orientation_rad: 0,
    battery_v: 0,
    is_grabber_open: true,
    mission_started_at: 0,
    mission_ended_at: 0,
    current_action: ActionType.UNKNOWN,
  },
};

/**
 * Available callable actions
 */
enum Action {
  UPDATE_POSITION = "UPDATE_POSITION",
  SET_TARGET_POSITION = "SET_TARGET_POSITION",
}

interface IProxy {
  setRobotPosition: (robotPosition: IRobotData) => void;
  setTargetPosition: (targetPosition: IPosition) => void;
  removeTargetPosition: () => void;
}

interface IStateProvider {
  proxy?: IProxy;
  state?: IState;
}

const defaultProxy: IProxy = {
  setRobotPosition: () => {},
  setTargetPosition: () => {},
  removeTargetPosition: () => {},
};

interface IStateContext {
  proxy: IProxy;
  state: IState;
}

const context = React.createContext<IStateContext>({
  state: defaultState,
  proxy: defaultProxy,
});

const StateProvider: FunctionComponent<IStateProvider> = ({
  state: initialState,
  children,
}) => {
  const [state, setState] = useState<IState>(defaultState);

  const { Provider } = context;

  const proxy: IProxy = useMemo(
    () => ({
      setRobotPosition: (robotPosition: IRobotData) =>
        setState((previousState) => ({
          ...previousState,
          robotData: robotPosition,
        })),
      setTargetPosition: (targetPosition: IPosition) =>
        setState((previousState) => ({
          ...previousState,
          targetPosition,
        })),
      removeTargetPosition: () =>
        setState((previousState) => ({
          ...previousState,
          targetPosition: undefined,
        })),
    }),
    []
  );

  return <Provider value={{ proxy, state }}>{children}</Provider>;
};

export { context, Action };
export default StateProvider;
