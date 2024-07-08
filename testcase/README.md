# generator.pyの使い方
Python3で動作します。`generator.py`が存在するディレクトリに移動したのち、以下のコマンドで実行できます。

```bash
python3 generator.py <number_of_cases> <seed> [output_directory]
```

- `number_of_cases` : 生成するテストケースの数
- `seed` : 乱数生成のシード
- `output_directory` : テストケースを出力するディレクトリ

第三引数は省略可能です。省略した場合はカレントディレクトリにテストケースが出力されます。

例えば、以下のように実行します。

```python
python3 generator.py 10 1234 testcase
```

この場合、`testcase`ディレクトリに`0000.txt`から`0009.txt`までのテストケースが10個生成されます。`testcase`ディレクトリが存在しない場合は自動的に作成されます。

このリポジトリの`testcase`ディレクトリにあるテストケースは、以下のコマンドで生成されました。

```bash
python3 generator.py 10 1234
```
