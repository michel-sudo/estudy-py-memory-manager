import ctypes
import sys

# Estrutura de uma lista no CPython (simplificada)
class PyListObject(ctypes.Structure):
    _fields_ = [
        ("ob_refcnt", ctypes.c_ssize_t),
        ("ob_type", ctypes.py_object),
        ("ob_size", ctypes.c_ssize_t),
        ("ob_item", ctypes.POINTER(ctypes.py_object)),
        ("allocated", ctypes.c_ssize_t),
    ]

# Obtém o endereço da lista
lista = []
list_address = id(lista)

# Converte o endereço para um ponteiro da estrutura PyListObject
list_struct = ctypes.cast(list_address, ctypes.POINTER(PyListObject)).contents

# Acessa o campo 'allocated'
print(len(lista), list_struct.allocated)
#print(f"Elementos: {len(lista)}, Alocação: {list_struct.allocated} ")

for i in range(20):
    lista.append(i)
    list_address = id(lista)
    list_struct = ctypes.cast(list_address, ctypes.POINTER(PyListObject)).contents
    print(len(lista), list_struct.allocated)
    #print(f"Elementos: {len(lista)}, Alocação: {list_struct.allocated} ")
    
