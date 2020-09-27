import React, { useState } from "react";
import "./App.css";

import { MotionServicePromiseClient } from "generated_grpc_sources/robot_grpc_web_pb";
import { SpeedRequest, SpeedResponse } from "generated_grpc_sources/robot_pb";

const client: MotionServicePromiseClient = new MotionServicePromiseClient(
  "http://localhost:8080"
);

function App() {
  const [speed, setSpeed] = useState(10);
  return (
    <div className="App">
      <header className="App-header">
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

        <button
          onClick={async () => {
            const speedRequest = new SpeedRequest();
            speedRequest.setSpeed(speed);
            const speedResponse: SpeedResponse = await client.startMove(
              speedRequest
            );
            alert(speedResponse.getSpeed());
          }}
        >
          send speed
        </button>
      </header>
    </div>
  );
}

export default App;
