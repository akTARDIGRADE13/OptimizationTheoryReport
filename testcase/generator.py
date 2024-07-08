import random
import sys
import os

def generate_problem_instance(N, K):
    grid = [[0] * N for _ in range(N)]
    all_positions = [(i, j) for i in range(N) for j in range(N)]
    all_positions.remove((0, 0))  # Remove the initial robot position

    # Generate half of the positions for placing items
    half_positions = random.sample(all_positions, (N * N - 1) // 2)

    # Assign positive numbers for items
    for idx, (i, j) in enumerate(half_positions, 1):
        grid[i][j] = idx

    # Assign the destinations for the items
    remaining_positions = [pos for pos in all_positions if pos not in half_positions]
    random.shuffle(remaining_positions)

    for idx, (i, j) in enumerate(remaining_positions, 1):
        grid[i][j] = -idx

    return N, K, grid

def print_problem_instance_to_file(N, K, grid, filename):
    with open(filename, 'w') as file:
        file.write(f"{N} {K}\n")
        for row in grid:
            file.write(' '.join(map(str, row)) + '\n')

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python generator.py <number_of_cases> <seed> [output_directory]")
        sys.exit(1)

    num_cases = int(sys.argv[1])
    seed = int(sys.argv[2])

    # Use the current directory if no output directory is provided
    output_directory = sys.argv[3] if len(sys.argv) == 4 else "."

    # Ensure the output directory exists
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    random.seed(seed)

    N = 21
    K = 10

    for i in range(num_cases):
        filename = os.path.join(output_directory, f"{i:04d}.txt")
        N, K, grid = generate_problem_instance(N, K)
        print_problem_instance_to_file(N, K, grid, filename)
        print(f"Problem instance {i} has been written to {filename}")
