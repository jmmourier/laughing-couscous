import React, { useEffect, useState } from "react";
import "./App.css";

import { PositionPromiseClient } from "generated_grpc_sources/robot_grpc_web_pb";
import { PositionMsg, Empty } from "generated_grpc_sources/robot_pb";

const client: PositionPromiseClient = new PositionPromiseClient(
  "http://localhost:8080"
);

interface Position {
  pos_x_m: number;
  pos_y_m: number;
  orientation_rad: number;
}

function App() {
  const [position, setPosition] = useState<Position>({
    pos_x_m: 0,
    pos_y_m: 0,
    orientation_rad: 0,
  });
  useEffect(() => {
    const stream_position = client.onAbsolutePositionUpdated(new Empty());
    stream_position.on("data", (positionMsg: PositionMsg) => {
      console.log(positionMsg.getPosXM());
      setPosition({
        pos_x_m: positionMsg.getPosXM(),
        pos_y_m: positionMsg.getPosYM(),
        orientation_rad: positionMsg.getOrientationRad(),
      });
    });

    return () => {
      stream_position.cancel();
    };
  }, []);
  const [speed, setSpeed] = useState(10);
  return (
    <div className="App">
      <header className="App-header">
        <p>Pos x: {position.pos_x_m}</p>
        <p>Pos y: {position.pos_y_m}</p>
        <p>
          First test with grpc, if you insert a speed, the grpc web server will
          return it multiplied by 2
        </p>
        <input
          defaultValue={speed}
          type="number"
          onChange={({ target: { value } }) => {
            setSpeed(parseInt(value));
          }}
        />
      </header>
    </div>
  );
}

export default App;
