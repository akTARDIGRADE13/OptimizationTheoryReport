export interface State {
  finalScore: number;
  score: number;
  rx: number;
  ry: number;
  grid: number[][];
  cargo: number[];
  all_flag?: boolean;
  horizontalPath?: number[][];
  verticalPath?: number[][];
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
      value: { finalScore: 0, rx: 0, ry: 0, score: -1, grid: [], cargo: [] },
    };
  }
  let cargoCount = 0;
  let finalScore = 0;
  let score = 0;
  let x = 0,
    y = 0;
  const grid = initialGrid.map((row) => row.slice());
  const horizontalPath: number[][] = Array.from({ length: N }, () =>
    Array.from({ length: N - 1 }, () => 0),
  );
  const verticalPath: number[][] = Array.from({ length: N - 1 }, () =>
    Array.from({ length: N }, () => 0),
  );

  if (turn === 0) {
    return {
      success: true,
      value: {
        finalScore,
        rx: x,
        ry: y,
        score,
        grid,
        cargo: [],
        horizontalPath,
        verticalPath,
      },
    };
  }
  const cargo: number[] = [];
  const dx: number[] = [0, 0, 1, -1];
  const dy: number[] = [1, -1, 0, 0];
  let turnCount = 1;
  operations.forEach((operation) => {
    if (operation[0] === '+') {
      cargoCount++;
      finalScore++;
    } else if (operation[0] === '-') {
      cargoCount--;
      finalScore++;
    } else {
      finalScore += cargoCount + 1;
    }
  });

  for (const operation of operations.slice(0, turn)) {
    let k = -1;
    if (operation === 'R') k = 0;
    else if (operation === 'L') k = 1;
    else if (operation === 'D') k = 2;
    else if (operation === 'U') k = 3;

    score += 1;
    if (k === -1) {
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
      if (k === 0 || k === 1) {
        horizontalPath[x][Math.min(y, ny)] += cargo.length + 1;
      } else {
        verticalPath[Math.min(x, nx)][y] += cargo.length + 1;
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
    value: {
      finalScore,
      rx: x,
      ry: y,
      score,
      grid,
      cargo,
      all_flag,
      horizontalPath,
      verticalPath,
    },
  };
};
