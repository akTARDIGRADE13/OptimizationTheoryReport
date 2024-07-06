# OptimizationTheoryReport
最適化理論の発表のために作成したプログラムをまとめたリポジトリ

# 問題設定: 配送経路最適化問題

## 問題概要
複数の配送車を用いて、配送センターから複数の顧客への配送を行う際の最適な経路を求める問題。配送車は容量制約を持ち、各顧客への配送には距離に応じたコストがかかる。なるべく総コストが小さくなるような経路を求める。

より具体的には、以下のような問題設定を考える。

> 頂点数 $V$ のグラフ $G = (V, E)$ が与えられる。頂点 $0$ は配送センターを表し、頂点 $1, 2, \ldots, N$ は顧客を表す。各辺 $(i, j) \in E$ には移動にかかる時間 $c_{ij}$ が与えられる。さらに、各顧客 $i$ には配送する荷物の大きさ $d_{i}$ が与えられる。配送車の数は $K$ 台で、各配送車の容量は $Q$ である。配送車は配送センターから出発し、各顧客に対して配送を行い、最後に配送センターに戻る。このとき、各配送車の経路のコストの総和が最小となるような配送経路を求めよ。

## 制約
- $N = 200$
- $K = 5$
- $Q = 100$
- $d_{i} \in [1, 10]$
- $c_{ij} \in [1, 100]$

## 入力形式
```
N K Q
d_{1} d_{2} \ldots d_{N}
c_{11} c_{12} \ldots c_{1N}
c_{21} c_{22} \ldots c_{2N}
...
c_{N1} c_{N2} \ldots c_{NN}
```

## 出力形式
$i$番目の配送車の経路長を $L_{i}$ とすると、以下のような形式で出力する。
```
L_{1}
v_{11} v_{12} ... v_{1L_{1}}
L_{2}
v_{21} v_{22} ... v_{2L_{2}}
...
L_{K}
v_{K1} v_{K2} ... v_{KL_{K}}
```
ただし、$v_{ij}$ は配送車 $i$ が $j$ 番目に訪れる頂点を表す。

## 入力の生成方法
$N, K, Q$ は定数。

$d_{i}$ は $[1, 10]$ の一様乱数。

$c_{ij}$ については、以下のように生成する。

まず、2次元平面上から $0 < x < 10000, 0 < y < 10000$ の範囲で $N+1$ 個の格子点を生成する。このとき、x座標とy座標は独立に $(1, 10000)$ の一様乱数で生成する。ただし、同一の座標を持つ格子点が選ばれた場合は再度生成し直す。

次に、$0 \leq i, j \leq N$ を満たす全ての $i, j$ について、$r_{ij}$ を $[0.8, 1.2]$ の一様乱数で生成し、$c_{ij}$ を以下のように定義する。
```
c_{ij} = round(\sqrt{(x_{i} - x_{j})^{2} + (y_{i} - y_{j})^{2}} \times r_{ij}) \quad (i \neq j)
c_{ij} = 0 \quad (i = j)
```
より具体的な生成方法については、[generator.py](generator.py) を参照のこと。
