import matplotlib.pyplot as plt
import json

# Load data from the JSON file

try:
    file_path = "output_variable_n_random_elements.json"
    with open(file_path, 'r') as file:
        data = json.load(file)
        data = data["Average time and percentage of optimal solution for different amounts of items"]

    # Extract data for plotting
    n_values = [int(result[0][0].split('=')[1]) for result in data]
    algorithms = ["Greedy", "Weighted Greedy", "Dynamic", "Force"]

    # Create subplots
    fig, axs = plt.subplots(1, 2, figsize=(16, 6))

    # Plotting time as points
    for i, algorithm in enumerate(algorithms):
        times = [float(result[i + 1][0].split('=')[1][:-3]) for result in data]
        axs[0].scatter(n_values, times, label=f"{algorithm} Time")

    axs[0].set_title('Algorithm Execution Time for Different Values of n')
    axs[0].set_xlabel('Number of Items (n)')
    axs[0].set_ylabel('Execution Time (µs)')
    axs[0].legend()
    axs[0].set_yscale('log')  # Use log scale for better visualization for time values

    # Plotting percentage as points
    for i, algorithm in enumerate(algorithms):
        percentages = [float(result[i + 1][1][:-1]) for result in data]
        axs[1].scatter(n_values, percentages, alpha=1, label=f"{algorithm} Percentage")

    axs[1].set_title('Percentage of Optimal Solution for Different Values of n')
    axs[1].set_xlabel('Number of Items (n)')
    axs[1].set_ylabel('Percentage of Optimal Solution')
    axs[1].legend()

    plt.savefig("output_variable_n_random_elements.png")
except Exception as e:
    pass
try:
    file_path_2 = "output_const_n_random_elements.json"

    with open(file_path_2, 'r') as file_2:
        data_2 = json.load(file_2)
        data_2 = data_2["Average time and percentage of optimal solution."]

    # Extract data for plotting
    n_values = [int(result[0][0].split('=')[1]) for result in data_2]
    algorithms = ["Greedy", "Weighted Greedy", "Dynamic", "Force"]

    # Create subplots
    fig, axs = plt.subplots(1, 2, figsize=(16, 6))

    # Plotting time as points
    for i, algorithm in enumerate(algorithms):
        times = [float(result[i + 1][0].split('=')[1][:-3]) for result in data_2]
        axs[0].scatter(n_values, times, label=f"{algorithm} Time")

    axs[0].set_title('Algorithm Execution Time for Different Values of n')
    axs[0].set_xlabel('Number of Items (n)')
    axs[0].set_ylabel('Execution Time (µs)')
    axs[0].legend()
    axs[0].set_yscale('log')  # Use log scale for better visualization for time values

    # Plotting percentage as points
    for i, algorithm in enumerate(algorithms):
        percentages = [float(result[i + 1][1][:-1]) for result in data_2]
        axs[1].scatter(n_values, percentages, alpha=0.5, label=f"{algorithm} Percentage")

    axs[1].set_title('Percentage of Optimal Solution for Different Values of n')
    axs[1].set_xlabel('Number of Items (n)')
    axs[1].set_ylabel('Percentage of Optimal Solution')
    axs[1].legend()
    plt.savefig("output_const_n_random_elements.png")
except Exception as e:
    pass

try:
    file_path = "output_variable_n_elements_from_file.json"
    with open(file_path, 'r') as file:
        data = json.load(file)
        data = data["Average time and percentage of optimal solution for different amounts of items"]

    # Extract data for plotting
    n_values = [int(result[0][0].split('=')[1]) for result in data]
    algorithms = ["Greedy", "Weighted Greedy", "Dynamic", "Force"]

    # Create subplots
    fig, axs = plt.subplots(1, 2, figsize=(16, 6))

    # Plotting time as points
    for i, algorithm in enumerate(algorithms):
        times = [float(result[i + 1][0].split('=')[1][:-3]) for result in data]
        axs[0].scatter(n_values, times, label=f"{algorithm} Time")

    axs[0].set_title('Algorithm Execution Time for Different Values of n')
    axs[0].set_xlabel('Number of Items (n)')
    axs[0].set_ylabel('Execution Time (µs)')
    axs[0].legend()
    axs[0].set_yscale('log')  # Use log scale for better visualization for time values

    # Plotting percentage as points
    for i, algorithm in enumerate(algorithms):
        percentages = [float(result[i + 1][1][:-1]) for result in data]
        axs[1].scatter(n_values, percentages, alpha=1, label=f"{algorithm} Percentage")

    axs[1].set_title('Percentage of Optimal Solution for Different Values of n')
    axs[1].set_xlabel('Number of Items (n)')
    axs[1].set_ylabel('Percentage of Optimal Solution')
    axs[1].legend()

    plt.savefig("output_variable_n_elements_from_file.png")
except Exception as e:
    pass

try:
    file_path_2 = "output_const_n_elements_from_file.json"

    with open(file_path_2, 'r') as file_2:
        data_2 = json.load(file_2)
        data_2 = data_2["Average time and percentage of optimal solution."]

    # Extract data for plotting
    n_values = [int(result[0][0].split('=')[1]) for result in data_2]
    algorithms = ["Greedy", "Weighted Greedy", "Dynamic", "Force"]

    # Create subplots
    fig, axs = plt.subplots(1, 2, figsize=(16, 6))

    # Plotting time as points
    for i, algorithm in enumerate(algorithms):
        times = [float(result[i + 1][0].split('=')[1][:-3]) for result in data_2]
        axs[0].scatter(n_values, times, label=f"{algorithm} Time")

    axs[0].set_title('Algorithm Execution Time for Different Values of n')
    axs[0].set_xlabel('Number of Items (n)')
    axs[0].set_ylabel('Execution Time (µs)')
    axs[0].legend()
    axs[0].set_yscale('log')  # Use log scale for better visualization for time values

    # Plotting percentage as points
    for i, algorithm in enumerate(algorithms):
        percentages = [float(result[i + 1][1][:-1]) for result in data_2]
        axs[1].scatter(n_values, percentages, alpha=0.5, label=f"{algorithm} Percentage")

    axs[1].set_title('Percentage of Optimal Solution for Different Values of n')
    axs[1].set_xlabel('Number of Items (n)')
    axs[1].set_ylabel('Percentage of Optimal Solution')
    axs[1].legend()
    plt.savefig("output_const_n_elements_from_file.png")
except Exception as e:
    pass