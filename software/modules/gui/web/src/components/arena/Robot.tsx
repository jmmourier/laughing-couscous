import React, { FunctionComponent, useContext } from "react";
import {
  context,
  SPACE_BETWEEN_WHEELS,
  WHEEL_RADIUS_M,
  WHEEL_WIDTH,
} from "../StateProvider";

const Robot: FunctionComponent = () => {
  const { state } = useContext(context);

  return (
    <g
      transform={`translate(${state.x},${state.y})
        rotate(${(state.angleRad * 180) / Math.PI})`}
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
      <rect
        x={-0.005}
        y={-SPACE_BETWEEN_WHEELS / 2}
        height={SPACE_BETWEEN_WHEELS}
        width={0.01}
        style={{ fill: "black" }}
      />
      <circle style={{ fill: "green" }} r={0.01}></circle>
    </g>
  );
};

export default Robot;
