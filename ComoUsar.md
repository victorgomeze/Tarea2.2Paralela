# Tarea2.2Paralela

# Para compilar utilice :
# mpiCC "nombre_Archivo".cpp -o "nombreEjecutable"
# EJEMPLO : mpiCC T2.cpp -o T2
# 
# Para ejecutar utilice
# mpi run -np "Numero de Procesadores" ./"NombreEjecutable" "RutaArchivoCSV"
# EJEMPLO : mpirun -np 4 ./T2 /home/kototeus/Escritorio/utem.csv
#
# En caso de no saber la ruta del archivo CSV utilice
# readlink -f "nombre_archivo"
# readlink -f utem.csv
