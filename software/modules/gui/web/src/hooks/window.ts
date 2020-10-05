import { useEffect, useState } from "react";
import ISize from "../interfaces/size";

const useWindow = (): ISize => {
  const [windowSize, setWindowSize] = useState<ISize>({
    width: window.innerWidth,
    height: window.innerHeight,
  });

  const handleWindowResize = (_e: UIEvent) => {
    setWindowSize({
      width: window.innerWidth,
      height: window.innerHeight,
    });
  };

  useEffect(() => {
    window.addEventListener("resize", handleWindowResize);

    return () => {
      window.removeEventListener("resize", handleWindowResize);
    };
  }, []);

  return windowSize;
};

export default useWindow;
