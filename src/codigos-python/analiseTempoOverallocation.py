import timeit

# Função de inserção de elementos sem pre-alocação; 
def overallocation(r):
    lista = []
    for i in range(r):
        lista.append(i)

# Função de inserção de elementos com a a lista pre-alocada
def pre_allocation(lista, r):
    for i in range(r):
        lista[i] = i

# Mede o tempo aproximado em segundos da inserção n de elementos em uma lista 
for i in range(10):
    r = 2 ** i
    lista_pre = [None] * r
    time_overallocation = timeit.timeit(lambda: overallocation(r), number=1000)
    time_pre_allocation = timeit.timeit(lambda: pre_allocation(lista_pre, r), number=1000)
    print(f"{time_overallocation:.4f} {time_pre_allocation:.4f}")
    
