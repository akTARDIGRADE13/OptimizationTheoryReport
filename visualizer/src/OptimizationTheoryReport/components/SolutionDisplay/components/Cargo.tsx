/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import styles from './Cargo.module.css';

interface CargoProps {
  cargo: number[];
}

const Cargo: FC<CargoProps> = ({ cargo }) => {
  return (
    <div className={styles['cargo-container']}>
      <h2 className={styles.heading}>積載物</h2>
      <ul className={styles['cargo-list']}>
        {cargo.map((value, index) => (
          <li key={index} className={styles['cargo-item']}>
            {value}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default Cargo;
