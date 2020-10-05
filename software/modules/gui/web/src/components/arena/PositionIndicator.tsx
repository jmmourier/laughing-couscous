import React from "react";
import { FunctionComponent } from "react";
import { ARENA_HEIGHT, ARENA_WIDTH, IArenaMouseState } from "./Arena";

const STROKE_DASHARRAY_VALUE = 0.01;
const STROKE_WITDH_M = 0.001;
const STROKE_COLOR = "black";
const LABEL_FONT_SIZE = 0.05;
const LABEL_LABEL_PADDING = 0.025;
const ROUND_RATIO = 1000;

interface IPositionIndicators {
  ratioPixelsMeters: number;
  mouseState: IArenaMouseState;
}

const PositionIndicator: FunctionComponent<IPositionIndicators> = ({
  mouseState,
  ratioPixelsMeters,
}) => {
  const mouseAbsolutePositionXM =
    mouseState.position.pos_x_m * ratioPixelsMeters;
  const mouseAbsolutePositionYM =
    mouseState.position.pos_y_m * ratioPixelsMeters;
  return (
    <>
      <line
        stroke-dasharray={STROKE_DASHARRAY_VALUE}
        style={{ strokeWidth: STROKE_WITDH_M }}
        width={STROKE_WITDH_M}
        x1={mouseAbsolutePositionXM}
        y1={0}
        x2={mouseAbsolutePositionXM}
        y2={ARENA_HEIGHT}
        stroke={STROKE_COLOR}
      />
      <line
        stroke-dasharray={STROKE_DASHARRAY_VALUE}
        style={{ strokeWidth: STROKE_WITDH_M }}
        width={STROKE_WITDH_M}
        x1={0}
        y1={mouseAbsolutePositionYM}
        x2={ARENA_WIDTH}
        y2={mouseAbsolutePositionYM}
        stroke={STROKE_COLOR}
      />

      <text
        fontSize={LABEL_FONT_SIZE}
        x={0}
        y={mouseAbsolutePositionYM - LABEL_LABEL_PADDING}
      >
        {Math.round(mouseAbsolutePositionYM * ROUND_RATIO) / ROUND_RATIO} m
      </text>
      <text
        fontSize={LABEL_FONT_SIZE}
        x={LABEL_LABEL_PADDING + mouseAbsolutePositionXM}
        y={LABEL_FONT_SIZE}
      >
        {Math.round(mouseAbsolutePositionXM * ROUND_RATIO) / ROUND_RATIO} m
      </text>
    </>
  );
};

export default PositionIndicator;
