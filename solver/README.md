# solverの説明

## 動作環境

WSL2で動作確認しています。

- `ubuntu 22.04`
- `CMake 3.22.1`
- `gcc 11.40`

## 使い方

1. solverディレクトリ（このREADME.mdが置かれているディレクトリ）に移動する
2. `mkdir build && cd build`でビルドディレクトリを作成し、移動する
3. `cmake ..`でビルドファイルを作成する
4. `make`でビルドする
5. `./DeliveryRobot <solver_name> <input_file_path>`で実行する（例えば`./DeliveryRobot solver1 ../../testcase/0000.txt`）

## ファイルの説明

- `main.cpp`: メイン関数が書かれているファイル。
- `common.cpp`: 全体で使われる関数や型定義が書かれているファイル。
- `problem.cpp`: 入力を受け取るクラスが書かれているファイル。
- `solver_base.cpp`: ソルバーの基底クラスが書かれているファイル。
- `solution.cpp`: 出力する解の集合を管理するクラスが書かれているファイル。
- `validator.cpp`: 解が問題の条件を満たしているかを判定するクラスが書かれているファイル。

## ソルバーの作り方

例として`SolverExample`を作成しているので、それを参考にしてください。

1. `./algorithm`の下にソルバーのディレクトリを作成する。
2. vscodeで作業している場合は`./vscode/c_cpp_properties.json`にパスを追加する。ワークスペースがどこかによってパスが異なるので、よく確認すること。
3. `SolverBase`を継承した派生クラスを作成する。
4. 派生クラスの`Solve`関数を実装する。このとき、引数は`const Problem&`、戻り値は`Solution`とする。
5. `./src/main.cpp`をよしなに書き換える。
6. `./CMakeLists.txt`をよしなに書き換える。
7. `./algorithm/<new_solver>/CMakeLists.txt`を作成する。