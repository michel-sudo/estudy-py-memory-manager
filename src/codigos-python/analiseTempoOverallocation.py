import timeit

def overallocation(r):
    lista = []
    for i in range(r):
        lista.append(i)
    
def pre_allocation(lista, r):
    for i in range(r):
        lista[i] = i

for i in range(22):
    r = 2 ** i
    lista_pre = [None] * r
    time_overallocation = timeit.timeit(lambda: overallocation(r), number=1000)
    time_pre_allocation = timeit.timeit(lambda: pre_allocation(lista_pre, r), number=1000)
    print(f"{time_overallocation:.4f} {time_pre_allocation:.4f}")
    
