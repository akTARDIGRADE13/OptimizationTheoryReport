import React from 'react';
import { type ReactNode, type Dispatch, type SetStateAction } from 'react';
import { createContext, useState } from 'react';

export interface VisualizerInfoContextProps {
  inputContent: string;
  setInputContent: Dispatch<SetStateAction<string>>;
  mode: string;
  setMode: Dispatch<SetStateAction<string>>;
  currentSolution: number;
  setCurrentSolution: Dispatch<SetStateAction<number>>;
  currentFrame: number;
  setCurrentFrame: Dispatch<SetStateAction<number>>;
  fileContent: string;
  setFileContent: Dispatch<SetStateAction<string>>;
}

export const VisualizerInfoContext = createContext<VisualizerInfoContextProps>({
  inputContent: '',
  setInputContent: () => {},
  mode: 'normal',
  setMode: () => {},
  currentSolution: 0,
  setCurrentSolution: () => {},
  currentFrame: 0,
  setCurrentFrame: () => {},
  fileContent: '',
  setFileContent: () => {},
});

export const VisualizerInfoProvider: React.FC<{ children: ReactNode }> = ({
  children,
}) => {
  const [inputContent, setInputContent] = useState<string>('');
  const [mode, setMode] = useState<string>('normal');
  const [currentSolution, setCurrentSolution] = useState<number>(0);
  const [currentFrame, setCurrentFrame] = useState<number>(0);
  const [fileContent, setFileContent] = useState<string>('');

  return (
    <VisualizerInfoContext.Provider
      value={{
        inputContent,
        setInputContent,
        mode,
        setMode,
        currentSolution,
        setCurrentSolution,
        currentFrame,
        setCurrentFrame,
        fileContent,
        setFileContent,
      }}
    >
      {children}
    </VisualizerInfoContext.Provider>
  );
};
