
str_list = list("Mundo")  # Equivalente a char str[] = "Mundo"
buffer = [None] * 3       # Equivalente a char buffer[3]
      
# Tentativa de copiar str para buffer (que é menor)
for i in range(len(str_list)):
        buffer[i] = str_list[i] # Index Error para i = 3
    

