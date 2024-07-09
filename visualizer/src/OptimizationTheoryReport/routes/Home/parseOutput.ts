export const parseOutput = (output: string): string[][] => {
  // 解の分割（最後の余分な改行を考慮してトリム）
  const solutionBlocks = output.trim().split('\n');

  // 各解をパースしてSolutionオブジェクトの配列を作成
  return solutionBlocks.map((block) => {
    const operations = block.trim().split(/\s+/);
    return operations;
  });
};
