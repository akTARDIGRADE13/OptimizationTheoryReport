/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import Cargo from './components/Cargo';
import Grid from './components/Grid';
import styles from './SolutionDisplay.module.css';

interface SolutionDisplayProps {
  score: number;
  grid: number[][];
  initialGrid: number[][];
  cargo: number[];
  mode: string;
  all_flag?: boolean;
}

const SolutionDisplay: FC<SolutionDisplayProps> = ({
  score,
  grid,
  initialGrid,
  cargo,
  mode,
  all_flag = false,
}) => {
  return (
    <div className={styles.container}>
      <div className={styles.score}>Score: {score ?? 'N/A'}</div>
      <div className={styles['flex-container']}>
        <Cargo cargo={cargo} />
        <Grid
          grid={grid}
          initialGrid={initialGrid}
          mode={mode}
          all_flag={all_flag}
        />
      </div>
    </div>
  );
};

export default SolutionDisplay;
