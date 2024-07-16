/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import styles from './Path.module.css';

interface PathProps {
  rows: number; // 行数
  columns: number; // 列数
  horizontalPath: number[][]; // 水平方向の移動を示す
  verticalPath: number[][]; // 垂直方向の移動を示す
}

const Path: FC<PathProps> = ({
  rows,
  columns,
  horizontalPath,
  verticalPath,
}) => {
  const cellSize = 32; // セルのサイズ (ピクセル)

  const getColorIntensity = (cost: number) => {
    // const maxCost = Math.max(...horizontalPath.flat(), ...verticalPath.flat());
    const maxCost = 30;
    const intensity = Math.min(cost / maxCost, 1) * 255;
    return `rgb(255, ${255 - intensity}, ${255 - intensity})`;
  };

  return (
    <div
      className={styles['path-container']}
      style={{
        width: columns * cellSize,
        height: rows * cellSize,
      }}
    >
      {horizontalPath.map((row, i) =>
        row.map((cost, j) => (
          <div
            key={`h-${i}-${j}`}
            className={styles['path-horizontal']}
            style={{
              left: j * cellSize,
              top: i * cellSize,
              width: cellSize,
              backgroundColor:
                cost > 0 ? getColorIntensity(cost) : 'transparent',
            }}
          />
        )),
      )}
      {verticalPath.map((row, i) =>
        row.map((cost, j) => (
          <div
            key={`v-${i}-${j}`}
            className={styles['path-vertical']}
            style={{
              left: j * cellSize,
              top: i * cellSize,
              height: cellSize,
              backgroundColor:
                cost > 0 ? getColorIntensity(cost) : 'transparent',
            }}
          />
        )),
      )}
    </div>
  );
};

export default Path;
