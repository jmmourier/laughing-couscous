import React, { FunctionComponent, useContext } from "react";
import * as communicationProvider from "../CommunicationProvider";

const FIX_SEED = 500;

const Joystick: FunctionComponent = () => {
  const { dispatch: communicationProviderDispatch } = useContext(
    communicationProvider.context
  );

  return (
    <div className="flex flex-col p-4">
      <button
        className="flex-1 w-1/6 self-center bg-gray-700 text-white rounded-xl"
        onClick={() => {
          communicationProviderDispatch({
            type: communicationProvider.Action.SET_SPEED,
            speed: { motor1: FIX_SEED, motor2: FIX_SEED },
          });
        }}
      >
        <svg
          xmlns="http://www.w3.org/2000/svg"
          fill="none"
          viewBox="0 0 24 24"
          stroke="currentColor"
        >
          <path
            stroke-linecap="round"
            stroke-linejoin="round"
            stroke-width="2"
            d="M5 15l7-7 7 7"
          />
        </svg>
      </button>
      <div className="flex justify-around">
        <button
          className="w-1/6 bg-gray-700 text-white rounded-xl"
          onClick={() => {
            communicationProviderDispatch({
              type: communicationProvider.Action.SET_SPEED,
              speed: { motor1: -FIX_SEED, motor2: FIX_SEED },
            });
          }}
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            fill="none"
            viewBox="0 0 24 24"
            stroke="currentColor"
          >
            <path
              stroke-linecap="round"
              stroke-linejoin="round"
              stroke-width="2"
              d="M15 19l-7-7 7-7"
            />
          </svg>
        </button>
        <button
          className="w-1/6 bg-gray-700 text-white rounded-xl"
          onClick={() => {
            communicationProviderDispatch({
              type: communicationProvider.Action.SET_SPEED,
              speed: { motor1: FIX_SEED, motor2: -FIX_SEED },
            });
          }}
        >
          <svg
            xmlns="http://www.w3.org/2000/svg"
            fill="none"
            viewBox="0 0 24 24"
            stroke="currentColor"
          >
            <path
              stroke-linecap="round"
              stroke-linejoin="round"
              stroke-width="2"
              d="M9 5l7 7-7 7"
            />
          </svg>
        </button>
      </div>
      <button
        className="flex-1 w-1/6 self-center bg-gray-700 text-white rounded-xl"
        onClick={() => {
          communicationProviderDispatch({
            type: communicationProvider.Action.SET_SPEED,
            speed: { motor1: -FIX_SEED, motor2: -FIX_SEED },
          });
        }}
      >
        <svg
          xmlns="http://www.w3.org/2000/svg"
          fill="none"
          viewBox="0 0 24 24"
          stroke="currentColor"
        >
          <path
            stroke-linecap="round"
            stroke-linejoin="round"
            stroke-width="2"
            d="M19 9l-7 7-7-7"
          />
        </svg>
      </button>
    </div>
  );
};

export default Joystick;
