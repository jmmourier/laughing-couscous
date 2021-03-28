import React, { FunctionComponent, useContext } from "react";
import * as communicationProvider from "../CommunicationProvider";

const FIX_SPEED = 20;
const ZERO_SPEED = 128;

const Joystick: FunctionComponent = () => {
  const { dispatch: communicationProviderDispatch } = useContext(
    communicationProvider.context
  );

  return (
    <div className="flex flex-col p-4 gap-4">
      <button
        className="flex-1 w-1/6 self-center bg-gray-700 text-white rounded-xl"
        onClick={() => {
          communicationProviderDispatch({
            type: communicationProvider.Action.SET_SPEED,
            speed: {
              motor1: FIX_SPEED + ZERO_SPEED,
              motor2: FIX_SPEED + ZERO_SPEED,
            },
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
              speed: {
                motor1: ZERO_SPEED - FIX_SPEED,
                motor2: ZERO_SPEED + FIX_SPEED,
              },
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
              speed: {
                motor1: ZERO_SPEED,
                motor2: ZERO_SPEED,
              },
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
              d="M21 12a9 9 0 11-18 0 9 9 0 0118 0z"
            />
            <path
              stroke-linecap="round"
              stroke-linejoin="round"
              stroke-width="2"
              d="M9 10a1 1 0 011-1h4a1 1 0 011 1v4a1 1 0 01-1 1h-4a1 1 0 01-1-1v-4z"
            />
          </svg>
        </button>
        <button
          className="w-1/6 bg-gray-700 text-white rounded-xl"
          onClick={() => {
            communicationProviderDispatch({
              type: communicationProvider.Action.SET_SPEED,
              speed: {
                motor1: ZERO_SPEED + FIX_SPEED,
                motor2: ZERO_SPEED - FIX_SPEED,
              },
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
            speed: {
              motor1: ZERO_SPEED - FIX_SPEED,
              motor2: ZERO_SPEED - FIX_SPEED,
            },
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
