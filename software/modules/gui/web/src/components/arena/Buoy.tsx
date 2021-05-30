import { FunctionComponent } from "react";
import { ARENA_HEIGHT } from "./Arena";

enum BuoyColor {
  RED = 0,
  GREEN = 1,
}

interface IBuoy {
  color: BuoyColor;
  x: number;
  y: number;
}

const buoyList: Array<IBuoy> = [
  { color: BuoyColor.RED, x: 0.3, y: 0.4 },
  { color: BuoyColor.GREEN, x: 0.445, y: 0.515 },
  { color: BuoyColor.RED, x: 0.445, y: 1.085 },
  { color: BuoyColor.GREEN, x: 0.3, y: 1.2 },
  { color: BuoyColor.RED, x: 0.67, y: 0.1 },
  { color: BuoyColor.GREEN, x: 0.956, y: 0.4 },
  { color: BuoyColor.RED, x: 1.1, y: 0.8 },
  { color: BuoyColor.GREEN, x: 1.27, y: 1.2 },
  { color: BuoyColor.GREEN, x: 1.065, y: 1.655 },
  { color: BuoyColor.RED, x: 1.335, y: 1.655 },
  { color: BuoyColor.RED, x: 1.005, y: 1.955 },
  { color: BuoyColor.GREEN, x: 1.395, y: 1.955 },
];

const Buoy: FunctionComponent<IBuoy> = ({ color, x, y }) => (
  <g transform={`translate(${x},${y})`}>
    <circle
      style={{ fill: color === BuoyColor.GREEN ? "green" : "red" }}
      r={0.036}
    />
  </g>
);

export default Buoy;
export { BuoyColor, buoyList };
