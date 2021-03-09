import React, { FunctionComponent, useContext } from "react";
import { context, IPosition } from "../StateProvider";

const Target: FunctionComponent<IPosition> = ({ x_m, y_m }) => {
  const stateContext = useContext(context);

  return (
    <g transform={`translate(${x_m},${y_m})`}>
      <circle
        style={{ fill: "red" }}
        r={0.05}
        onDoubleClick={() => stateContext.proxy.removeTargetPosition()}
      ></circle>
    </g>
  );
};

export default Target;
