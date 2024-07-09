// inputContentをパースする
export const parseInput = (
  input: string,
): { N: number; K: number; initialGrid: number[][] } => {
  if (input.length === 0) {
    return { N: 0, K: 0, initialGrid: [] };
  }
  // 行ごとに分割
  const lines = input.trim().split('\n');

  // 最初の行からNとKを取得
  const [N, K] = lines[0].split(/\s+/).map(Number);

  // 残りの行からグリッドデータを取得
  const initialGrid: number[][] = lines
    .slice(1)
    .map((line) => line.trim().split(/\s+/).map(Number));

  return { N, K, initialGrid };
};
