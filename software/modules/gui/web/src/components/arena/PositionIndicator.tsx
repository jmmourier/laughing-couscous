import React, { FunctionComponent } from "react";
import { ARENA_HEIGHT, ARENA_WIDTH, IArenaMouseState } from "./Arena";

const STROKE_DASHARRAY_VALUE = 0.01;
const STROKE_WITDH_M = 0.001;
const STROKE_COLOR = "black";
const LABEL_FONT_SIZE = 0.05;
const LABEL_PADDING = 0.025;
const ROUND_RATIO = 1000;

interface IPositionIndicators {
  ratioPixelsMeters: number;
  mouseState: IArenaMouseState;
}

const PositionIndicator: FunctionComponent<IPositionIndicators> = ({
  mouseState,
  ratioPixelsMeters,
}) => {
  const mouseAbsolutePositionXM = mouseState.position.x_m * ratioPixelsMeters;
  const mouseAbsolutePositionYM = mouseState.position.y_m * ratioPixelsMeters;
  return (
    <>
      <g transform={`translate(${mouseAbsolutePositionXM})`}>
        <line
          strokeDasharray={STROKE_DASHARRAY_VALUE}
          style={{ strokeWidth: STROKE_WITDH_M }}
          width={STROKE_WITDH_M}
          x1={0}
          y1={0}
          x2={0}
          y2={ARENA_HEIGHT}
          stroke={STROKE_COLOR}
        />
        <text fontSize={LABEL_FONT_SIZE} x={LABEL_PADDING} y={LABEL_FONT_SIZE}>
          {Math.round(mouseAbsolutePositionXM * ROUND_RATIO) / ROUND_RATIO} m
        </text>
      </g>
      <g transform={`translate(0,${mouseAbsolutePositionYM})`}>
        <line
          strokeDasharray={STROKE_DASHARRAY_VALUE}
          style={{ strokeWidth: STROKE_WITDH_M }}
          width={STROKE_WITDH_M}
          x1={0}
          y1={0}
          x2={ARENA_WIDTH}
          y2={0}
          stroke={STROKE_COLOR}
        />
        <text fontSize={LABEL_FONT_SIZE} x={0} y={-LABEL_PADDING}>
          {Math.round((ARENA_HEIGHT - mouseAbsolutePositionYM) * ROUND_RATIO) /
            ROUND_RATIO}
          m
        </text>
      </g>
    </>
  );
};

export default PositionIndicator;
