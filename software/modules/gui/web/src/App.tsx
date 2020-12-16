import { Input } from "@material-ui/core";
import React, { FunctionComponent, useContext, useState } from "react";
import "./App.css";
import Arena from "./components/arena/Arena";
import * as stateProvider from "./components/StateProvider";
import * as communicationProvider from "./components/CommunicationProvider";
import Joystick from "./components/arena/Joystick";

const TextField = require("@material-ui/core/TextField/TextField").default;
const Table = require("@material-ui/core/Table/Table").default;
const Paper = require("@material-ui/core/Paper/Paper").default;
const TableBody = require("@material-ui/core/TableBody/TableBody").default;
const TableCell = require("@material-ui/core/TableCell/TableCell").default;
const TableContainer = require("@material-ui/core/TableContainer/TableContainer")
  .default;
const TableRow = require("@material-ui/core/TableRow/TableRow").default;
const TableHead = require("@material-ui/core/TableHead/TableHead").default;

const ROUND_RATIO = 1000;

function createData(name: string, value: number) {
  return { name, value };
}

const App: FunctionComponent = () => {
  const {
    state: { x_m: x, y_m: y, orientation_rad: angleRad },
  } = useContext(stateProvider.context);

  const { dispatch: communicationProviderDispatch } = useContext(
    communicationProvider.context
  );

  const rows = [
    createData(
      "Absolute position X",
      Math.round(x * ROUND_RATIO) / ROUND_RATIO
    ),
    createData(
      "Absolute position Y",
      Math.round(y * ROUND_RATIO) / ROUND_RATIO
    ),
    createData(
      "Absolute angle (radian)",
      Math.round(angleRad * ROUND_RATIO) / ROUND_RATIO
    ),
  ];

  const [
    selectedPosition,
    setSelectedPosition,
  ] = useState<stateProvider.IRobotPosition>({
    x_m: 0,
    y_m: 0,
    orientation_rad: 0,
  });

  return (
    <div className={"container"}>
      <div className={"area"}>
        <Arena onPositionSelected={setSelectedPosition} />
      </div>
      <div className={"data-view"}>
        <Paper style={{ padding: "16px" }}>
          <h2>Couscous position</h2>
          <TableContainer>
            <Table aria-label="simple table">
              <TableHead>
                <TableRow>
                  <TableCell>Data</TableCell>
                  <TableCell align="right">Value</TableCell>
                </TableRow>
              </TableHead>
              <TableBody>
                {rows.map((row) => (
                  <TableRow key={row.name}>
                    <TableCell component="th" scope="row">
                      {row.name}
                    </TableCell>
                    <TableCell align="right">{row.value}</TableCell>
                  </TableRow>
                ))}
              </TableBody>
            </Table>
          </TableContainer>

          <h2>Set position</h2>
          <form
            noValidate
            autoComplete="off"
            className={"form-set-position"}
            onSubmit={(e) => {
              e.preventDefault();
              communicationProviderDispatch({
                type: communicationProvider.Action.SET_ABSOLUTE_POSITION,
                position: selectedPosition,
              });
            }}
          >
            <TextField
              label="Pos X"
              variant="outlined"
              type={"number"}
              value={
                Math.round(selectedPosition.x_m * ROUND_RATIO) / ROUND_RATIO
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
            <TextField
              label="Pos Y"
              variant="outlined"
              type={"number"}
              value={
                Math.round(selectedPosition.y_m * ROUND_RATIO) / ROUND_RATIO
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
            <div>
              <Input type="submit" value="Set position"></Input>
            </div>
          </form>
          <Joystick></Joystick>
        </Paper>
      </div>
    </div>
  );
};

export default App;
