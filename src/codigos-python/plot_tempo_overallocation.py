import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator

ranges = []
alloc_values = []
pre_alloc_values = []

for i in range(23):
    ranges.append(fr"$2^{{{i}}}$")

with open("dadosAnaliseTempo4.txt", "r") as file:
    for line in file:
        alloc, pre_alloc = map(float, line.split())
        alloc_values.append(alloc)
        pre_alloc_values.append(pre_alloc)

fig, ax = plt.subplots()
ax.set_xscale('linear')
ax.set_yscale('linear')

ax.plot(ranges, alloc_values, "-g", label='Overallocation')
ax.plot(ranges, pre_alloc_values, "-b", label='Pre-allocation')

ax.set_title("Comparação tempo de execução")
ax.set_xlabel("Elementos adicionados")
ax.set_ylabel("Tempo em Segundos")

ax.xaxis.set_major_locator(MultipleLocator(1))
ax.grid(True)
ax.legend()

plt.show()
