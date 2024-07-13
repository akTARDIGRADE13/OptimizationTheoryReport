/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import styles from './Grid.module.css';

interface GridProps {
  rx: number;
  ry: number;
  grid: number[][];
  initialGrid: number[][];
  all_flag: boolean;
}

const Grid: FC<GridProps> = ({
  rx,
  ry,
  grid,
  initialGrid,
  // all_flag,
}) => {
  const getCellStyle = (cell: number, initialCell: number) => {
    if (cell > 0) {
      if (cell === -initialCell) {
        return styles['fluorescent-green'];
      }
      return styles.red;
    } else if (cell === 0) {
      return styles.gray;
    } else {
      return styles.blue;
    }
  };

  const cellSize = 32; // セルのサイズ (ピクセル)

  return (
    <div
      className={styles['grid-container']}
      style={{
        gridTemplateColumns: `repeat(${grid[0].length}, ${cellSize}px)`,
      }}
    >
      {grid.map((row, i) =>
        row.map((cell, j) => (
          <div
            key={`${i}-${j}`}
            className={`${styles['grid-cell']} ${getCellStyle(cell, initialGrid[i][j])}`}
            style={{ width: cellSize, height: cellSize }}
          >
            {i === rx && j === ry ? '🤖' : Math.abs(cell)}
          </div>
        )),
      )}
    </div>
  );
};

export default Grid;
