import React, { FunctionComponent, useContext, useState } from "react";
import Arena from "./components/arena/Arena";
import Joystick from "./components/arena/Joystick";
import Block from "./components/Block";
import * as communicationProvider from "./components/CommunicationProvider";
import * as stateProvider from "./components/StateProvider";

const ROUND_RATIO = 1000;

function createData(name: string, value: number) {
  return { name, value };
}

const App: FunctionComponent = () => {
  const {
    state: { robotPosition },
    proxy,
  } = useContext(stateProvider.context);

  const { dispatch: communicationProviderDispatch } = useContext(
    communicationProvider.context
  );

  const rows = [
    createData(
      "Absolute position X",
      Math.round(robotPosition.x_m * ROUND_RATIO) / ROUND_RATIO
    ),
    createData(
      "Absolute position Y",
      Math.round(robotPosition.y_m * ROUND_RATIO) / ROUND_RATIO
    ),
    createData(
      "Absolute angle (radian)",
      Math.round(robotPosition.orientation_rad * ROUND_RATIO) / ROUND_RATIO
    ),
  ];

  const [
    selectedPosition,
    setSelectedPosition,
  ] = useState<stateProvider.IPosition>({
    x_m: 0,
    y_m: 0,
  });
  const [selectedOrientation, setSelectedOrientation] = useState<number>(0);

  return (
    <main className={"flex h-full bg-gray-200 gap-4 p-4"}>
      <div className={"w-8/12"}>
        <Arena onPositionSelected={setSelectedPosition} />
      </div>
      <div className={"flex-1 rounded-xl flex flex-col gap-4"}>
        <Block title="position">
          <table className="table-auto w-full whitespace-no-wrap table-striped relative">
            <tbody>
              {rows.map((row, index) => (
                <tr key={index}>
                  <td className="order-gray-200 userId">
                    <span className="text-gray-700 px-6 py-3 flex items-center">
                      {row.name}
                    </span>
                  </td>
                  <td className="border-gray-200 userId">
                    <span className="text-gray-700 px-6 py-3 flex items-center">
                      {row.value}
                    </span>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </Block>
        <Block title="set position">
          <div className="flex">
            <div className="p-4">
              <form
                noValidate
                autoComplete="off"
                onSubmit={(e) => {
                  e.preventDefault();
                  communicationProviderDispatch({
                    type: communicationProvider.Action.SET_ABSOLUTE_POSITION,
                    position: {
                      ...selectedPosition,
                      orientation_rad: robotPosition.orientation_rad,
                    },
                  });
                }}
              >
                <div className="flex gap-4">
                  <label className="flex-1">
                    <span className="text-gray-700">Position X</span>
                    <input
                      type="number"
                      className="mt-2 w-full rounded-lg p-4 border-2 border-gray-700 bg-gray-50 text-gray-700"
                      placeholder="Position X"
                      value={
                        Math.round(selectedPosition.x_m * ROUND_RATIO) /
                        ROUND_RATIO
                      }
                      onChange={({
                        target: { value },
                      }: React.ChangeEvent<HTMLInputElement>) => {
                        setSelectedPosition({
                          ...selectedPosition,
                          x_m: parseFloat(value),
                        });
                      }}
                    />
                  </label>
                  <label className="flex-1">
                    <span className="text-gray-700">Position Y</span>
                    <input
                      type="number"
                      className="mt-2 w-full rounded-lg p-4 border-2 border-gray-700 bg-gray-50 text-gray-700"
                      placeholder="Position Y"
                      value={
                        Math.round(selectedPosition.y_m * ROUND_RATIO) /
                        ROUND_RATIO
                      }
                      onChange={({
                        target: { value },
                      }: React.ChangeEvent<HTMLInputElement>) => {
                        setSelectedPosition({
                          ...selectedPosition,
                          y_m: parseFloat(value),
                        });
                      }}
                    />
                  </label>
                </div>
                <div className="flex gap-4">
                  <button
                    type="submit"
                    className="w-full rounded-xl p-4 uppercase bg-gray-700 shadow text-white mt-4"
                  >
                    Apply
                  </button>
                  <button
                    type="button"
                    className="w-full rounded-xl p-4 uppercase bg-gray-700 shadow text-white mt-4"
                    onClick={(e) => {
                      e.preventDefault();
                      proxy.setTargetPosition(selectedPosition);
                      communicationProviderDispatch({
                        type: communicationProvider.Action.SET_TARGET_POSITION,
                        position: selectedPosition,
                      });
                    }}
                  >
                    set target
                  </button>
                </div>
              </form>
            </div>
            <div className="p-4">
              <form
                noValidate
                autoComplete="off"
                onSubmit={(e) => {
                  e.preventDefault();
                  communicationProviderDispatch({
                    type: communicationProvider.Action.SET_TARGET_ORIENTATION,
                    orientation_rad: (selectedOrientation * Math.PI) / 180,
                  });
                }}
              >
                <label className="flex-1">
                  <span className="text-gray-700">Orientation (deg)</span>
                  <input
                    max={359}
                    min={0}
                    type="number"
                    className="mt-2 w-full rounded-lg p-4 border-2 border-gray-700 bg-gray-50 text-gray-700"
                    placeholder="Orientation"
                    value={selectedOrientation}
                    onChange={({
                      target: { value },
                    }: React.ChangeEvent<HTMLInputElement>) => {
                      setSelectedOrientation(parseInt(value));
                    }}
                  />
                </label>
                <div className="flex gap-4">
                  <button
                    type="submit"
                    className="w-full rounded-xl p-4 uppercase bg-gray-700 shadow text-white mt-4"
                  >
                    set Orientation
                  </button>
                </div>
              </form>
            </div>
          </div>
        </Block>
        <Block title="Joystick">
          <Joystick />
        </Block>
      </div>
    </main>
  );
};

export default App;
