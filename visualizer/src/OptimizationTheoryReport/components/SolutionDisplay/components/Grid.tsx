/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import styles from './Grid.module.css';

interface GridProps {
  grid: number[][];
  initialGrid: number[][];
  mode: string;
  all_flag: boolean;
}

const Grid: FC<GridProps> = ({ grid, initialGrid /*, mode, all_flag*/ }) => {
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

  return (
    <div
      className={styles['grid-container']}
      style={{ gridTemplateColumns: `repeat(${grid[0].length}, 2em)` }}
    >
      {grid.map((row, i) =>
        row.map((cell, j) => (
          <div
            key={`${i}-${j}`}
            className={`${styles['grid-cell']} ${getCellStyle(cell, initialGrid[i][j])}`}
          >
            {Math.abs(cell)}
          </div>
        )),
      )}
    </div>
  );
};

export default Grid;
