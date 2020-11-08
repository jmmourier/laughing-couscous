import React, { FunctionComponent, useCallback, useState } from "react";
import ISize from "../../interfaces/size";
import useWindow from "../../hooks/window";
import * as stateProvider from "../StateProvider";
import Robot from "./Robot";
import PositionIndicator from "./PositionIndicator";

const ARENA_HEIGHT = 2;
const ARENA_WIDTH = 3;

interface IArenaProps {
  onPositionSelected(position: stateProvider.IRobotPosition): void;
}

export interface IArenaMouseState {
  isDown: boolean;
  position: stateProvider.IRobotPosition;
}

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
  const [
    selectedPosition,
    setSelectedPosition,
  ] = useState<stateProvider.IRobotPosition>({
    x_m: 0,
    y_m: 0,
    orientation_rad: 0,
  });
  const [mouseState, setMouseState] = useState<IArenaMouseState>({
    isDown: false,
    position: { x_m: 0, y_m: 0, orientation_rad: 0 },
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
          x_m:
            (e.clientX - e.currentTarget.getBoundingClientRect().x) *
            ratioPixelToMeter,
          y_m:
            (e.clientY - e.currentTarget.getBoundingClientRect().y) *
            ratioPixelToMeter,
          orientation_rad: selectedPosition.orientation_rad,
        });
      }}
      onMouseMove={(e) => {
        setMouseState({
          ...mouseState,
          position: {
            x_m: e.clientX - e.currentTarget.getBoundingClientRect().x,
            y_m: e.clientY - e.currentTarget.getBoundingClientRect().y,
            orientation_rad: selectedPosition.orientation_rad,
          },
        });
      }}
      onMouseDown={() => setMouseState({ ...mouseState, isDown: true })}
    >
      <svg style={{ position: "absolute", backgroundColor: "#e3e3e3" }}>
        <Robot />
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
