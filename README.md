# OptimizationTheoryReport
最適化理論の発表のために作成したプログラムをまとめたリポジトリ

[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://akTARDIGRADE13.github.io/OptimizationTheoryReport/)

# 荷物配送ロボットの最小コスト問題

## 問題概要
 $N \times N$ のグリッドグラフ（ $N$ は奇数）が与えられます。 $(0,0)$ のマスにはロボットが配置されており、その他のマスのうち $\frac{(N \times N - 1)}{2}$ 個のマスには荷物が一つずつ置かれています。
 
 ロボットに積載されている荷物が $k$ 個以下のとき、ロボットは自身の居るマスに上下左右に隣接した四つのマスのいずれかに移動することができます。ただし、グリッドの外に出るような移動はできません。
 
 それぞれの荷物には指定された宛先のマスがあります。あなたの目標はロボットを操作してすべての荷物を宛先に届けることです。

より具体的には、 $\frac{-(N \times N - 1)}{2}$ から $\frac{(N \times N - 1)}{2}$ までの整数が一つずつ書かれた $N \times N$ のグリッドグラフが与えられます。 $i$ 行目 $j$ 列目の値を $d_{ij}$ とします。 $d_{00}$ は $0$ です。 $d_{ij}$ が正の場合、そのマスには荷物が置かれており、その荷物の番号は $d_{ij}$ です。 $d_{ij}$ が負の場合、そのマスには何も置かれておらず、 $abs(d_{ij})$ がそのマスに届けるべき荷物の番号です。

1回の操作のコストは次のように計算されます：
- 荷物を持ち上げる： $+1$
- 荷物を降ろす： $+1$
- $a$ 個の荷物を持って移動する： $+(a+1)$

一つのマスには最大で一つの荷物しか置くことができません。また、最終的に宛先のマスに届けられれば、途中で別のマスに荷物を置くことは許されます。

目標を達成する操作列であって、なるべくコストの総和が小さいものを求めてください。

## 制約
- $N = 21$
- $K = 10$
- $d_{00} = 0$
- $\frac{-(N \times N - 1)}{2} \leq d_{ij} \leq \frac{(N \times N - 1)}{2} \quad (i, j \neq 0)$
- $d_{ij} \neq d_{kl} \quad ((i, j) \neq (k, l))$

## 入力形式

$$
\begin{align*}
&N \quad K \\
&d_{11} \quad d_{12} \quad \ldots \quad d_{1N} \\
&d_{21} \quad d_{22} \quad \ldots \quad d_{2N} \\
&\vdots \\
&d_{N1} \quad d_{N2} \quad \ldots \quad d_{NN}
\end{align*}
$$

## 出力形式
各操作を以下のように表現します。
- 荷物 $i$ を積む：`+i`
- 荷物 $i$ を降ろす：`-i`
- 上に移動：`U`
- 下に移動：`D`
- 左に移動：`L`
- 右に移動：`R`

全体で $Q$ 回の操作を行うとき、以下のように全ての操作を一列に空白区切りで並べて出力してください。

$$
\begin{align*}
&op_1 \ op_2 \ \ldots \ op_Q
\end{align*}
$$

## 入力の生成方法

[generator.py](/testcase/generator.py) を参照のこと。
