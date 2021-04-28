import React, {
  FunctionComponent,
  useCallback,
  useContext,
  useState,
} from "react";
import useWindow from "../../hooks/window";
import { ISize } from "../../interfaces/size";
import * as stateProvider from "../StateProvider";
import { context } from "../StateProvider";
import PositionIndicator from "./PositionIndicator";
import Robot from "./Robot";
import Target from "./Target";

const ARENA_HEIGHT = 2;
const ARENA_WIDTH = 3;

interface IArena {
  onPositionSelected(position: stateProvider.IPosition): void;
}

export interface IArenaMouseState {
  isDown: boolean;
  position: stateProvider.IPosition;
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

const Arena: FunctionComponent<IArena> = ({ onPositionSelected }) => {
  const [areaSize, setAreaSize] = useState<ISize>({ width: 0, height: 0 });
  const [mouseState, setMouseState] = useState<IArenaMouseState>({
    isDown: false,
    position: { x_m: 0, y_m: 0 },
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

  const { state } = useContext(context);
  return (
    <svg
      className="bg-gradient-to-r from-gray-100 via-gray-50 to-gray-100 rounded-md shadow"
      ref={svgAreaRef}
      viewBox={`0 0 ${ARENA_WIDTH} ${ARENA_HEIGHT}`}
      onDoubleClick={(e) => {
        const positionSelected = {
          x_m:
            (e.clientX - e.currentTarget.getBoundingClientRect().x) *
            ratioPixelToMeter,
          y_m:
            ARENA_HEIGHT -
            (e.clientY - e.currentTarget.getBoundingClientRect().y) *
              ratioPixelToMeter,
        };
        onPositionSelected(positionSelected);
      }}
      onMouseMove={(e) => {
        setMouseState({
          ...mouseState,
          position: {
            x_m: e.clientX - e.currentTarget.getBoundingClientRect().x,
            y_m: e.clientY - e.currentTarget.getBoundingClientRect().y,
          },
        });
      }}
      onMouseDown={() => setMouseState({ ...mouseState, isDown: true })}
    >
      <g>
        <Robot />
        <PositionIndicator
          mouseState={mouseState}
          ratioPixelsMeters={ratioPixelToMeter}
        />
        {state.targetPosition && (
          <Target
            x_m={state.targetPosition.x_m}
            y_m={state.targetPosition.y_m}
          />
        )}
      </g>
    </svg>
  );
};

export { ARENA_WIDTH, ARENA_HEIGHT };
export default Arena;
