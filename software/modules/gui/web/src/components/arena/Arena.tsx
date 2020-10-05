import React, { FunctionComponent, useCallback, useState } from "react";
import ISize from "../../interfaces/size";
import useWindow from "../../hooks/window";
import Robot from "./Robot";
import PositionIndicator from "./PositionIndicator";
import IPosition from "../../interfaces/position";

const ARENA_HEIGHT = 2;
const ARENA_WIDTH = 3;

interface IArenaProps {
  onPositionSelected(position: IPosition): void;
}

export interface IArenaMouseState {
  isDown: boolean;
  position: IPosition;
}

interface IBuoyProps {
  position: IPosition;
  color: string;
}

// const buoyList: Array<IBuoyProps> = [
//   { color: "green", position: { pos_x_m: 2, pos_y_m: 1 } },
//   { color: "green", position: { pos_x_m: 2, pos_y_m: 1.5 } },
// ];

const Buoy: FunctionComponent<IBuoyProps> = ({
  position: { pos_x_m: x, pos_y_m: y },
  color,
}) => {
  return <circle style={{ fill: color }} r={0.036} cx={x} cy={y} />;
};

const getRatioPixelToMeter = (areaSize: ISize): number => {
  const pixelAreaDiagonal = Math.sqrt(
    Math.pow(areaSize.width, 2) + Math.pow(areaSize.height, 2)
  );

  const meterAreaDiagonal = Math.sqrt(
    Math.pow(ARENA_WIDTH, 2) + Math.pow(ARENA_HEIGHT, 2)
  );
  return meterAreaDiagonal / pixelAreaDiagonal;
};

const Arena: FunctionComponent<IArenaProps> = ({ onPositionSelected }) => {
  const [areaSize, setAreaSize] = useState<ISize>({ width: 0, height: 0 });
  const [selectedPosition, setSelectedPosition] = useState<IPosition>({
    pos_x_m: 0,
    pos_y_m: 0,
    orientation_rad: 0,
  });
  const [mouseState, setMouseState] = useState<IArenaMouseState>({
    isDown: false,
    position: { pos_x_m: 0, pos_y_m: 0, orientation_rad: 0 },
  });

  /**
   * When resizing the window, the dom first has to render
   * the SVG and the useCallback is call afterward to get the element size
   */
  const windowSize = useWindow();

  const svgAreaRef = useCallback(
    (node: any) => {
      if (node !== null) {
        setAreaSize({
          width: node.getBoundingClientRect().width,
          height: node.getBoundingClientRect().height,
        });
      }
    },
    [windowSize]
  );

  const ratioPixelToMeter = getRatioPixelToMeter(areaSize);

  return (
    <svg
      ref={svgAreaRef}
      viewBox={`0 0 ${ARENA_WIDTH} ${ARENA_HEIGHT}`}
      style={{
        position: "absolute",
        backgroundColor: "#e3e3e3",
        width: "100%",
      }}
      onDoubleClick={(e) => {
        onPositionSelected({
          pos_x_m:
            (e.clientX - e.currentTarget.getBoundingClientRect().x) *
            ratioPixelToMeter,
          pos_y_m:
            (e.clientY - e.currentTarget.getBoundingClientRect().y) *
            ratioPixelToMeter,
          orientation_rad: selectedPosition.orientation_rad,
        });
      }}
      onMouseMove={(e) => {
        setMouseState({
          ...mouseState,
          position: {
            pos_x_m: e.clientX - e.currentTarget.getBoundingClientRect().x,
            pos_y_m: e.clientY - e.currentTarget.getBoundingClientRect().y,
            orientation_rad: selectedPosition.orientation_rad,
          },
        });
      }}
      onMouseDown={() => setMouseState({ ...mouseState, isDown: true })}
    >
      <svg style={{ position: "absolute", backgroundColor: "#e3e3e3" }}>
        <Robot />
        {/* {buoyList.map(({ color, position: { pos_x_m: x, pos_y_m: y } }) => (
          <Buoy color={color} position={{ pos_x_m: x, pos_y_m: y }} />
        ))} */}

        <PositionIndicator
          mouseState={mouseState}
          ratioPixelsMeters={ratioPixelToMeter}
        />
      </svg>
    </svg>
  );
};

export { ARENA_WIDTH, ARENA_HEIGHT };
export default Arena;
