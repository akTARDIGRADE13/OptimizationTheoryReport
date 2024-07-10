/* eslint-disable react/react-in-jsx-scope */
import { FC } from 'react';
import BaseVisualizer from 'components/BaseVisualizer/BaseVisualizer';
import Layout from 'components/Layout/Layout';
import Container from 'components/Container/Container';
import SolutionDisplay from 'components/SolutionDisplay/SolutionDisplay';
import { useVisualizerInfo } from 'components/BaseVisualizer/context/useVisualizerInfo';
import { parseInput } from './parseInput';
import { parseOutput } from './parseOutput';
import { State, Result, updateGrid } from './updateGrid';

const Home: FC = () => {
  const { mode, currentSolution, currentFrame, inputContent, fileContent } =
    useVisualizerInfo();

  // inputContentをパース
  const { N, K, initialGrid } = parseInput(inputContent);

  console.log(N, K, initialGrid, 19);

  // fileContentをパース
  const solutions: string[][] = parseOutput(fileContent);

  console.log(N, K, initialGrid, 24, currentFrame, solutions, currentSolution);

  // 指定された盤面の状態を求める
  const result: Result<State> = updateGrid(
    N,
    K,
    initialGrid,
    solutions[currentSolution],
    currentFrame,
  );

  console.log(N, K, solutions[currentSolution], 35);

  return (
    <Layout>
      <Container large>
        <BaseVisualizer>
          {result.success ? (
            N === 0 ? (
              <div>There is no grid.</div>
            ) : (
              <SolutionDisplay
                finalScore={result.value.finalScore}
                score={result.value.score}
                rx={result.value.rx}
                ry={result.value.ry}
                grid={result.value.grid}
                initialGrid={initialGrid}
                cargo={result.value.cargo}
                mode={mode}
              />
            )
          ) : (
            <div>{result.error || 'An error occurred.'}</div>
          )}
        </BaseVisualizer>
      </Container>
    </Layout>
  );
};

export default Home;
