import { FunctionComponent } from "react";

interface IBlock {
  title: string;
}

const Block: FunctionComponent<IBlock> = ({ title, children }) => (
  <div className={"rounded-xl shadow bg-white"}>
    <header className="rounded-t-xl bg-gray-700">
      <p className="text-center p-2 text-white uppercase">{title}</p>
    </header>
    {children}
  </div>
);

export default Block;
