/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import Cargo from './components/Cargo';
import Grid from './components/Grid';
import styles from './SolutionDisplay.module.css';

interface SolutionDisplayProps {
  finalScore: number;
  score: number;
  rx: number;
  ry: number;
  grid: number[][];
  initialGrid: number[][];
  cargo: number[];
  mode: string;
  all_flag?: boolean;
}

const SolutionDisplay: FC<SolutionDisplayProps> = ({
  finalScore,
  score,
  rx,
  ry,
  grid,
  initialGrid,
  cargo,
  mode,
  all_flag = false,
}) => {
  return (
    <div className={styles.container}>
      <div className={styles.score}>
        Score: {score ?? 'N/A'} /
        <span
          className={
            all_flag ? styles['final-score-green'] : styles['final-score-red']
          }
        >
          {finalScore ?? 'N/A'}
        </span>
      </div>
      <div className={styles['flex-container']}>
        <Cargo cargo={cargo} />
        <Grid
          rx={rx}
          ry={ry}
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
