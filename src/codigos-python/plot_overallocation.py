import matplotlib.pyplot as plt

# Ler os dados do arquivo
indices = []
valores = []
with open("dadosOverallocation3.txt", "r") as file:
    for line in file:
        index, value = map(int, line.split())
        indices.append(index)
        valores.append(value)

# Plotar os dados
plt.plot(indices, valores, marker='o')
plt.title("Dados de Overallocation")
plt.xlabel("Elementos")
plt.ylabel("Alocação")
plt.grid(True)
plt.show()
