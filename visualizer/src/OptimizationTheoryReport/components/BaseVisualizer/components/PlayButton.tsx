/* eslint-disable react/react-in-jsx-scope */
import React from 'react';
import styles from './PlayButton.module.css';

interface PlayButtonProps {
  isPlaying: boolean;
  onClick: () => void;
  type?: number;
}

const PlayButton: React.FC<PlayButtonProps> = ({
  isPlaying,
  onClick,
  type = 1,
}) => {
  return (
    <p>
      <input
        type="button"
        value={isPlaying ? 'stop' : 'start'}
        className={type === 1 ? styles['play-button'] : styles['play-button2']}
        onClick={onClick}
      />
    </p>
  );
};

export default PlayButton;
