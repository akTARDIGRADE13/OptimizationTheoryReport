import random
import math

def generate_input(N, K, Q, seed, x_range=(1, 10000), y_range=(1, 10000), d_range=(1, 10), r_range=(70, 100)):
    random.seed(seed)
    # 配送センターと顧客の座標を生成
    coordinates = [(random.randint(*x_range), random.randint(*y_range)) for _ in range(N+1)]
    while(len(set(coordinates)) != len(coordinates)):
        coordinates = [(random.randint(*x_range), random.randint(*y_range)) for _ in range(N+1)]
    
    # 各顧客の荷物の大きさを生成
    demands = [random.randint(*d_range) for _ in range(N)]
    
    # 距離行列を生成
    cost_matrix = [[0] * (N + 1) for _ in range(N + 1)]
    for i in range(N + 1):
        for j in range(N + 1):
            if i != j:
                x1, y1 = coordinates[i]
                x2, y2 = coordinates[j]
                distance = math.sqrt(((x1 - x2) ** 2 + (y1 - y2) ** 2) / 200000000)
                r = random.uniform(*r_range)
                cost_matrix[i][j] = math.floor(distance * r)
    
    # データを出力形式で整形して返す
    data = f"{N} {K} {Q}\n"
    data += " ".join(map(str, demands)) + "\n"
    for row in cost_matrix:
        data += " ".join(map(str, row)) + "\n"
    
    return data, coordinates

def save_input_to_file(filename, data):
    with open(filename, "w") as f:
        f.write(data)

def save_coordinates_to_file(filename, coordinates):
    with open(filename, "w") as f:
        for x, y in coordinates:
            f.write(f"{x} {y}\n")

def save_input_to_file(filename, data):
    with open(filename, "w") as f:
        f.write(data)

def save_coordinates_to_file(filename, coordinates, N):
    with open(filename, "w") as f:
        f.write(f"{N}\n")
        for x, y in coordinates:
            f.write(f"{x} {y}\n")

if __name__ == "__main__":
    # 定数の設定
    N = 200  # 顧客数
    K = 5    # 配送車数
    Q = 100  # 各配送車の容量
    
    # 各テストケースの乱数シードを設定
    seeds = [42, 123, 456]
    
    # 各テストケースについて入力データと座標を生成しファイルに保存
    for i, seed in enumerate(seeds):
        input_data, coordinates = generate_input(N, K, Q, seed)
        
        input_filename = f"input_case_{i+1}.txt"
        coordinates_filename = f"coordinates_case_{i+1}.txt"
        
        save_input_to_file(input_filename, input_data)
        save_coordinates_to_file(coordinates_filename, coordinates, N)
        
        print(f"入力データが '{input_filename}' に生成されました。")
        print(f"座標データが '{coordinates_filename}' に生成されました。")