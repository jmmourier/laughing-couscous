import React, { FunctionComponent, useContext } from "react";
import {
  context,
  ROBOT_FRAME_LENGTH,
  SPACE_BETWEEN_WHEELS,
  WHEEL_RADIUS_M,
  WHEEL_WIDTH,
} from "../StateProvider";
import { ARENA_HEIGHT } from "./Arena";
import Buoy, { buoyList } from "./Buoy";

const GRABBER_Y_POSITION_FROM_CENTER = 0.025;

interface IGrabber {
  isOpen: boolean;
}

const Grabber: FunctionComponent<IGrabber> = ({ isOpen }) => {
  const grabberRotationAngle = isOpen ? 0 : 60;
  return (
    <g>
      <polyline
        transform={`rotate(${grabberRotationAngle},${ROBOT_FRAME_LENGTH},-${GRABBER_Y_POSITION_FROM_CENTER})`}
        fill="none"
        stroke="red"
        strokeWidth="0.01"
        points={`${ROBOT_FRAME_LENGTH},-${GRABBER_Y_POSITION_FROM_CENTER} ${
          ROBOT_FRAME_LENGTH + 0.01
        },-${0.1} ${ROBOT_FRAME_LENGTH + 0.04}, -${0.12}`}
      />
      <polyline
        transform={`rotate(-${grabberRotationAngle},${ROBOT_FRAME_LENGTH},${GRABBER_Y_POSITION_FROM_CENTER})`}
        fill="none"
        stroke="red"
        strokeWidth="0.01"
        points={`${ROBOT_FRAME_LENGTH},${GRABBER_Y_POSITION_FROM_CENTER} ${
          ROBOT_FRAME_LENGTH + 0.01
        },${0.1} ${ROBOT_FRAME_LENGTH + 0.04}, ${0.12}`}
      />
    </g>
  );
};

const RobotFrame: FunctionComponent = () => (
  <rect
    x={0}
    y={-SPACE_BETWEEN_WHEELS / 2}
    height={SPACE_BETWEEN_WHEELS}
    width={ROBOT_FRAME_LENGTH}
    style={{ fill: "black" }}
  />
);

const Robot: FunctionComponent = () => {
  const { state } = useContext(context);

  return (
    <g
      transform={`translate(${state.robotData.x_m},${
        ARENA_HEIGHT - state.robotData.y_m
      })
      rotate(${(-state.robotData.orientation_rad * 180) / Math.PI})`}
    >
      <rect
        x={-WHEEL_RADIUS_M}
        y={-(SPACE_BETWEEN_WHEELS / 2) - WHEEL_WIDTH / 2}
        height={WHEEL_WIDTH}
        width={WHEEL_RADIUS_M * 2}
        style={{ fill: "blue" }}
      />

      <rect
        x={-WHEEL_RADIUS_M}
        y={SPACE_BETWEEN_WHEELS / 2 - WHEEL_WIDTH / 2}
        height={WHEEL_WIDTH}
        width={WHEEL_RADIUS_M * 2}
        style={{ fill: "red" }}
      />
      <RobotFrame />
      <Grabber isOpen={state.robotData.is_grabber_open} />
      <circle style={{ fill: "green" }} r={0.01}></circle>
    </g>
  );
};

export default Robot;
