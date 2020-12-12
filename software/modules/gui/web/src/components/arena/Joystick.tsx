import React, { FunctionComponent } from "react";
const Theme = require("@material-ui/core/styles/createMuiTheme").default;
const makeStyles = require("@material-ui/core/styles/makeStyles").default;
const ArrowUpwardIcon = require("@material-ui/icons/ArrowUpward").default;
const Button = require("@material-ui/core/Button").default;
const ArrowDownward = require("@material-ui/icons/ArrowDownward").default;
const ArrowForward = require("@material-ui/icons/ArrowForward").default;
const ArrowBack = require("@material-ui/icons/ArrowBack").default;

const useStyles = makeStyles((theme: typeof Theme) => ({
  container: {
    display: "grid",
    gridTemplateColumns: "1fr 1fr 1fr",
    gridTemplateRows: "1fr 1fr 1fr",
  },
  upButton: {
    gridColumn: 2,
    gridRow: 1,
    backgroundColor: "#d2d2d2",
    borderRadius: "5px",
    margin: "auto",
  },
  leftButton: {
    gridColumn: 1,
    gridRow: 2,
    backgroundColor: "#d2d2d2",
    borderRadius: "5px",
    margin: "auto",
  },
  rightButton: {
    gridColumn: 3,
    gridRow: 2,
    backgroundColor: "#d2d2d2",
    borderRadius: "5px",
    margin: "auto",
  },
  bottomButton: {
    gridColumn: 2,
    gridRow: 3,
    backgroundColor: "#d2d2d2",
    borderRadius: "5px",
    margin: "auto",
  },
}));
const Joystick: FunctionComponent = () => {
  const style = useStyles();
  return (
    <div className={style.container}>
      <Button className={style.upButton} variant="contained" color="primary">
        <ArrowUpwardIcon color="primary">Up</ArrowUpwardIcon>
      </Button>
      <Button className={style.leftButton} variant="contained" color="primary">
        <ArrowBack color="primary">Left</ArrowBack>
      </Button>
      <Button className={style.rightButton} variant="contained" color="primary">
        <ArrowForward color="primary">Right</ArrowForward>
      </Button>
      <Button
        className={style.bottomButton}
        variant="contained"
        color="primary"
      >
        <ArrowDownward color="primary">Down</ArrowDownward>
      </Button>
    </div>
  );
};

export default Joystick;
