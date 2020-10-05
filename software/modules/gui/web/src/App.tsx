import { Input } from "@material-ui/core";
import React, {
  FunctionComponent,
  useContext,
  useEffect,
  useState,
} from "react";
import "./App.css";
import Arena from "./components/arena/Arena";
import { ActionEnum, context } from "./components/StateProvider";
import IPosition from "./interfaces/position";
import { PositionPromiseClient } from "generated_grpc_sources/robot_grpc_web_pb";
import { PositionMsg, Empty } from "generated_grpc_sources/robot_pb";

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

const client: PositionPromiseClient = new PositionPromiseClient(
  "http://localhost:8080"
);

interface Position {
  pos_x_m: number;
  pos_y_m: number;
  orientation_rad: number;
}

const App: FunctionComponent = () => {
  const {
    state: { x, y, angleRad },
    dispatch,
  } = useContext(context);

  useEffect(() => {
    const position_stream = client.onAbsolutePositionUpdated(new Empty());
    position_stream.on("data", (positionMsg: PositionMsg) => {
      dispatch({
        type: ActionEnum.UPDATE_POSITION,
        position: {
          x: positionMsg.getPosXM(),
          y: positionMsg.getPosYM(),
          angleRad: positionMsg.getOrientationRad(),
        },
      });
    });
  }, []);

  const rows = [
    // createData(
    //   "Left wheel speed (rad/s)",
    //   Math.round(leftWheelRadPs * ROUND_RATIO) / ROUND_RATIO
    // ),
    // createData(
    //   "Right wheel speed (rad/s)",
    //   Math.round(rightWheelRadPs * ROUND_RATIO) / ROUND_RATIO
    // ),
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

  const [selectedPosition, setSelectedPosition] = useState<IPosition>({
    pos_x_m: 0,
    pos_y_m: 0,
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
              const position_request = new PositionMsg();
              position_request.setPosXM(selectedPosition.pos_x_m);
              position_request.setPosYM(selectedPosition.pos_y_m);
              position_request.setOrientationRad(selectedPosition.pos_y_m);
              client.setAbsolutePosition(position_request);
            }}
          >
            <TextField
              label="Pos X"
              variant="outlined"
              type={"number"}
              value={
                Math.round(selectedPosition.pos_x_m * ROUND_RATIO) / ROUND_RATIO
              }
              onChange={({
                target: { value },
              }: React.ChangeEvent<HTMLInputElement>) => {
                setSelectedPosition({
                  ...selectedPosition,
                  pos_x_m: parseFloat(value),
                });
              }}
            />
            <TextField
              label="Pos Y"
              variant="outlined"
              type={"number"}
              value={
                Math.round(selectedPosition.pos_y_m * ROUND_RATIO) / ROUND_RATIO
              }
              onChange={({
                target: { value },
              }: React.ChangeEvent<HTMLInputElement>) => {
                setSelectedPosition({
                  ...selectedPosition,
                  pos_y_m: parseFloat(value),
                });
              }}
            />
            {/* <TextField
              label="Orientation"
              variant="outlined"
              type={"number"}
              value={
                Math.round(selectedPosition.orientation_rad * ROUND_RATIO) /
                ROUND_RATIO
              }
              onChange={({
                target: { value },
              }: React.ChangeEvent<HTMLInputElement>) => {
                setSelectedPosition({
                  ...selectedPosition,
                  orientation_rad: parseFloat(value),
                });
              }}
            /> */}
            <div>
              <Input type="submit" value="Set position"></Input>
            </div>
          </form>
        </Paper>
      </div>
    </div>
  );
};

export default App;
