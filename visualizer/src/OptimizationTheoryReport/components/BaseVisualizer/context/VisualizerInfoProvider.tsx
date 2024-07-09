import React from 'react';
import { type ReactNode, type Dispatch, type SetStateAction } from 'react';
import { createContext, useState } from 'react';

export interface VisualizerInfoContextProps {
  inputContent: string;
  setInputContent: Dispatch<SetStateAction<string>>;
  mode: string;
  setMode: Dispatch<SetStateAction<string>>;
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
  const [currentFrame, setCurrentFrame] = useState<number>(0);
  const [fileContent, setFileContent] = useState<string>('');

  return (
    <VisualizerInfoContext.Provider
      value={{
        inputContent,
        setInputContent,
        mode,
        setMode,
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
