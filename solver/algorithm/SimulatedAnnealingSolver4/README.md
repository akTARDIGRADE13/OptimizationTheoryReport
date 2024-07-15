# SimulatedAnnealingSolver4のアルゴリズム

やっていることはSA3と一緒。

SA3で「累積和+累積和MAX」の（非再帰）セグ木を使っていたところを、Starry Sky Tree + BITで書き直したほうが速いのではと思い、実装した。

実際、SA3と比べて25％くらいイテレーション数を増やすことができた。