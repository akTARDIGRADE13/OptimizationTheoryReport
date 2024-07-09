export interface State {
  score: number;
  grid: number[][];
  cargo: number[];
  all_flag?: boolean;
}

export type Result<T> = Success<T> | Failure;

interface Success<T> {
  success: true;
  value: T;
}

interface Failure {
  success: false;
  error: string;
}

export const updateGrid = (
  N: number,
  K: number,
  initialGrid: number[][],
  operations: string[],
  turn: number,
): Result<State> => {
  if (N === 0) {
    return {
      success: true,
      value: { score: -1, grid: [], cargo: [] },
    };
  }
  let score = 0;
  let x = 0,
    y = 0;
  const grid = initialGrid.map((row) => row.slice());
  const cargo: number[] = [];
  const dx: number[] = [0, 0, 1, -1];
  const dy: number[] = [1, -1, 0, 0];
  let turnCount = 1;

  for (const operation of operations.slice(0, turn)) {
    let k = -1;
    if (operation === 'R') k = 0;
    else if (operation === 'L') k = 1;
    else if (operation === 'D') k = 2;
    else if (operation === 'U') k = 3;

    if (k === -1) {
      score += 1;
      if (operation[0] === '+') {
        const target = parseInt(operation.slice(1), 10);
        if (grid[x][y] === target) {
          grid[x][y] = Math.min(initialGrid[x][y], 0);
          cargo.push(target);
          if (cargo.length > K) {
            return {
              success: false,
              error: `${turnCount}回目の操作は不正です。積載物が${K}個を超えました。`,
            };
          }
        } else {
          return {
            success: false,
            error: `${turnCount}回目の操作は不正です。(${x}, ${y})には${target}がありません。`,
          };
        }
      } else if (operation[0] === '-') {
        const target = parseInt(operation.slice(1), 10);
        if (grid[x][y] === 0) {
          if (cargo.includes(target)) {
            grid[x][y] = target;
          } else {
            return {
              success: false,
              error: `${turnCount}回目の操作は不正です。荷物${target}を持っていません。`,
            };
          }
        } else {
          return {
            success: false,
            error: `${turnCount}回目の操作は不正です。(${x}, ${y})には既に荷物が置かれています。`,
          };
        }
      } else {
        return {
          success: false,
          error: `${turnCount}回目の操作は不正です。解釈不能です。`,
        };
      }
    } else {
      score += cargo.length;
      const nx = x + dx[k];
      const ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
        return {
          success: false,
          error: `${turnCount}回目の操作は不正です。(${nx}, ${ny})は範囲外です。`,
        };
      }
      x = nx;
      y = ny;
    }
    turnCount++;
  }

  const all_flag = initialGrid.every((row, i) =>
    row.every((cell, j) => cell >= 0 || -cell === grid[i][j]),
  );

  return {
    success: true,
    value: { score, grid, cargo, all_flag },
  };
};