import { PositionPromiseClient } from "generated_grpc_sources/robot_grpc_web_pb";
import { Empty, PositionMsg, SpeedMsg } from "generated_grpc_sources/robot_pb";
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
      position: stateProvider.IRobotPosition;
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
  SET_SPEED = "SET_SPEED",
  UPDATE_POSITION = "UPDATE_POSITION",
}

const reducer: Reducer<IState, IAction> = async (
  state: IState,
  action: IAction
) => {
  switch (action.type) {
    case Action.SET_ABSOLUTE_POSITION:
      const positionMsg = new PositionMsg();
      positionMsg.setPosXM(action.position.x_m);
      positionMsg.setPosYM(action.position.y_m);
      positionMsg.setOrientationRad(action.position.orientation_rad);
      await client.setAbsolutePositionRequest(positionMsg);
      return { ...state };
    case Action.SET_SPEED: {
      const speedMsg = new SpeedMsg();
      speedMsg.setMotor1(action.speed.motor1);
      speedMsg.setMotor2(action.speed.motor2);

      console.log(action.speed.motor1, action.speed.motor2);
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

  const { dispatch: stateProviderDispatch } = useContext(stateProvider.context);

  useEffect(() => {
    const position_stream = client.registerPositionObserver(new Empty());
    position_stream.on("data", (positionMsg: PositionMsg) => {
      stateProviderDispatch({
        type: stateProvider.Action.UPDATE_POSITION,
        position: {
          x_m: positionMsg.getPosXM(),
          y_m: positionMsg.getPosYM(),
          orientation_rad: positionMsg.getOrientationRad(),
        },
      });
    });
  }, []);

  // type: stateProvider.ActionEnum.UPDATE_POSITION,
  return <Provider value={{ state, dispatch }}>{children}</Provider>;
};

export type { IState };
export { context, defaultState, Action };
export default CommunicationProvider;
