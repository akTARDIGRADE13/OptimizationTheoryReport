/* eslint-disable react/react-in-jsx-scope */
import { useState, useEffect, useCallback } from 'react';
import { ChangeEvent } from 'react';
import Container from 'components/Container/Container';
import FileInput from './components/FileInput';
import MarkdownContent from 'components/MarkdownContent/MarkdownContent';
import PlayButton from './components/PlayButton';
import SelectBox from './components/SelectBox';
import Slider from './components/Slider';
import styles from './BaseVisualizer.module.css';
import { useVisualizerInfo } from 'components/BaseVisualizer/context/useVisualizerInfo';

interface BaseVisualizerProps {
  children: React.ReactNode;
  // drawSvg: (fileContent: string) => string[];
}

const BaseVisualizer: React.FC<BaseVisualizerProps> = ({
  children,
}: BaseVisualizerProps) => {
  const [changeSolution, setChangeSolution] = useState(false);
  const [isPlaying, setIsPlaying] = useState(false);
  const [speed, setSpeed] = useState(100); // 再生速度（フレーム/秒）
  const [maxSolution, setMaxSolution] = useState(0);
  const [maxFrame, setMaxFrame] = useState(0);
  const {
    // inputContent,
    setInputContent,
    mode,
    setMode,
    currentSolution,
    setCurrentSolution,
    currentFrame,
    setCurrentFrame,
    fileContent,
    setFileContent,
  } = useVisualizerInfo();

  const handleFileChange = useCallback(
    (e: ChangeEvent<HTMLTextAreaElement>) => {
      const file = e.target.value;
      if (!file) {
        setFileContent('');
        setMaxFrame(0);
        setCurrentFrame(0);
        setMaxSolution(0);
        setCurrentSolution(0);
      } else {
        setFileContent(file);
        const solutions = file.trim().split('\n');
        setMaxSolution(solutions.length - 1);
        setCurrentSolution(0);
        setMaxFrame(solutions[0].split(/\s/).length);
        setCurrentFrame(0);
      }
    },
    [
      setFileContent,
      setMaxFrame,
      setCurrentFrame,
      setMaxSolution,
      setCurrentSolution,
    ],
  );

  // useEffectを使ってfileContentの変更を監視し、textareaに反映
  useEffect(() => {
    const textarea = document.getElementById('textArea') as HTMLTextAreaElement;
    if (textarea) {
      textarea.value = fileContent;
    }
  }, [fileContent]);

  // ソリューション変更処理
  const updateSolution = useCallback(
    (newSolution: number) => {
      const updatedSolution = Math.max(0, Math.min(maxSolution, newSolution));
      setCurrentSolution(updatedSolution);
      const solution = fileContent.trim().split('\n')[updatedSolution];
      const solutionFrames = solution.split(/\s/).length;
      setMaxFrame(solutionFrames);
      setCurrentFrame(solutionFrames);
      if (updatedSolution >= maxSolution) {
        setChangeSolution(false);
      }
    },
    [
      maxSolution,
      fileContent,
      setCurrentSolution,
      setMaxFrame,
      currentFrame,
      setCurrentFrame,
    ],
  );

  // ソリューションの自動再生処理
  useEffect(() => {
    let interval: NodeJS.Timeout | null = null;

    if (changeSolution) {
      setIsPlaying(false);
      interval = setInterval(() => {
        updateSolution(currentSolution + 1);
      }, 1000 / speed);
    }

    return () => {
      if (interval) clearInterval(interval);
    };
  }, [changeSolution, currentSolution, speed, updateSolution]);

  // フレーム更新処理
  const updateFrame = useCallback(
    (newFrame: number) => {
      setCurrentFrame(() => {
        return Math.max(0, Math.min(maxFrame, newFrame));
      });
      if (newFrame >= maxFrame) {
        setIsPlaying(false);
      }
    },
    [maxFrame, setCurrentFrame],
  );

  // 自動再生処理
  useEffect(() => {
    let interval: NodeJS.Timeout | null = null;

    if (isPlaying) {
      setChangeSolution(false);
      interval = setInterval(() => {
        updateFrame(currentFrame + 1);
      }, 1000 / speed);
    }

    return () => {
      if (interval) clearInterval(interval);
    };
  }, [isPlaying, currentFrame, speed, updateFrame]);

  return (
    <div className={styles.container}>
      <div className={styles['setting-container']}>
        <div className={styles['buttons-container']}>
          <textarea
            id="textArea"
            className={styles.textbox}
            placeholder="Enter text here..."
            onChange={(e) => handleFileChange(e)}
            value={fileContent}
          />
        </div>
        <div className={styles['sliders-container']}>
          <Slider
            label="Solution"
            min={0}
            max={maxSolution}
            value={currentSolution}
            onChange={updateSolution}
          />
          <Slider
            label="Frame"
            min={0}
            max={maxFrame}
            value={currentFrame}
            onChange={updateFrame}
          />
          <Slider
            label="Speed"
            min={1}
            max={300}
            value={speed}
            onChange={setSpeed}
          />
          <div className={styles['play-button-container']}>
            <PlayButton
              isPlaying={changeSolution}
              onClick={() => setChangeSolution(!changeSolution)}
              type={2}
            />
            <PlayButton
              isPlaying={isPlaying}
              onClick={() => setIsPlaying(!isPlaying)}
            />
          </div>
        </div>
        <div className={styles['sliders-container']}>
          <FileInput
            onFileChange={(inputContent) => setInputContent(inputContent ?? '')}
          />
          <SelectBox
            label="mode"
            options={['Grid', 'Path']}
            value={mode}
            onChange={(value) => {
              setMode(value as string);
            }}
          />
        </div>
      </div>
      <div className={styles['svg-wrapper']}>{children}</div>
      <Container>
        <MarkdownContent mdPath={`/OptimizationTheoryReport/md/howto.md`} />
      </Container>
    </div>
  );
};

export default BaseVisualizer;
