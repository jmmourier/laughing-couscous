import { PositionPromiseClient } from "generated_grpc_sources/robot_grpc_web_pb";
import {
  Empty,
  OrientationRequest,
  RobotDataRequest,
  PositionRequest,
  SpeedRequest,
} from "generated_grpc_sources/robot_pb";
import React, {
  Dispatch,
  FunctionComponent,
  Reducer,
  useContext,
  useEffect,
  useReducer,
} from "react";
import { ISpeed } from "../interfaces/size";
import * as stateProvider from "./StateProvider";

type IState = {};

type IAction =
  | {
      type: Action.SET_ABSOLUTE_POSITION;
      robotData: stateProvider.IRobotData;
    }
  | {
      type: Action.SET_TARGET_POSITION;
      position: stateProvider.IPosition;
    }
  | {
      type: Action.SET_TARGET_ORIENTATION;
      orientation_rad: number;
    }
  | { type: Action.SET_SPEED; speed: ISpeed };

const serverUrl: string = `${process.env.REACT_APP_PROXY_URL}:${process.env.REACT_APP_PROXY_PORT}`;
const defaultState: IState = {
  position: { x: 0, y: 0, orientationRad: 0 },
};

const client: PositionPromiseClient = new PositionPromiseClient(serverUrl);

/**
 * Available callable actions
 */
enum Action {
  SET_ABSOLUTE_POSITION = "SET_ABSOLUTE_POSITION",
  SET_TARGET_POSITION = "SET_TARGET_POSITION",
  SET_TARGET_ORIENTATION = "SET_TARGET_ORIENTATION",
  SET_SPEED = "SET_SPEED",
  UPDATE_POSITION = "UPDATE_POSITION",
}

const reducer: Reducer<IState, IAction> = async (
  state: IState,
  action: IAction
) => {
  switch (action.type) {
    case Action.SET_ABSOLUTE_POSITION: {
      const robotDataRequest = new RobotDataRequest();
      robotDataRequest.setPosXM(action.robotData.x_m);
      robotDataRequest.setPosYM(action.robotData.y_m);
      robotDataRequest.setOrientationRad(action.robotData.orientation_rad);
      await client.setAbsolutePositionRequest(robotDataRequest);
      return { ...state };
    }
    case Action.SET_TARGET_POSITION: {
      const positionRequest = new PositionRequest();
      positionRequest.setPosXM(action.position.x_m);
      positionRequest.setPosYM(action.position.y_m);
      await client.setTargetPositionRequest(positionRequest);
      return { ...state };
    }
    case Action.SET_TARGET_ORIENTATION: {
      const orientationRequest = new OrientationRequest();
      orientationRequest.setOrientationRad(action.orientation_rad);
      await client.setTargetOrientationRequest(orientationRequest);
      return { ...state };
    }
    case Action.SET_SPEED: {
      const speedMsg = new SpeedRequest();
      speedMsg.setMotor1(action.speed.motor1);
      speedMsg.setMotor2(action.speed.motor2);

      client.setSpeedRequest(speedMsg);
    }
  }
};

interface ICommunicationProvider {
  initialState?: IState;
  children: any;
}

type CommunicationContext = {
  state: IState;
  dispatch: Dispatch<IAction>;
};

const context = React.createContext<CommunicationContext>({
  state: defaultState,
  dispatch: () => null,
});

const CommunicationProvider: FunctionComponent<ICommunicationProvider> = ({
  initialState,
  children,
}) => {
  const [state, dispatch] = useReducer<Reducer<IState, IAction>>(
    reducer,
    initialState || defaultState
  );

  const { Provider } = context;

  const stateContext = useContext(stateProvider.context);

  useEffect(() => {
    const position_stream = client.registerRobotDataObserver(new Empty());
    position_stream.on("data", (robotDataRequest: RobotDataRequest) => {
      stateContext.proxy.setRobotPosition({
        x_m: robotDataRequest.getPosXM(),
        y_m: robotDataRequest.getPosYM(),
        orientation_rad: robotDataRequest.getOrientationRad(),
        battery_v: robotDataRequest.getBatteryV(),
      });
    });
  }, [stateContext.proxy]);

  // type: stateProvider.ActionEnum.UPDATE_POSITION,
  return <Provider value={{ state, dispatch }}>{children}</Provider>;
};

export type { IState };
export { context, defaultState, Action };
export default CommunicationProvider;
