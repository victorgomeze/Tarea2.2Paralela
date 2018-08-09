#include<stdio.h>
#include<mpi.h>
#include<fstream>
#include <iostream>
using namespace std;


int LargoArchivo(char *texto)
{
	int contador=-1,n[2];
	string linea;
	ifstream fichero(texto);
	MPI_Recv(n, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);   //cuenta cada proc
    fichero.seekg(n[0]);
	while(n[1]>=fichero.tellg() && fichero.tellg()!=-1)
		{
			getline(fichero,linea);
			contador++;
		}
	fichero.close();
	return contador;
}



int main(int argc, char* argv[]){

  	int c_proces, proc, Total=-1,final,cxproce,AuxProces,n[2];
  	MPI_Init(&argc,&argv);
  	MPI_Comm_size(MPI_COMM_WORLD, &c_proces); //Cantidad de procesadores
  	MPI_Comm_rank(MPI_COMM_WORLD, &proc);//Guarda el procesador

	
	if(proc==0)
	{
		int Total=-1, n[2], cxproce,final,AuxProces;
	string linea;
	ifstream fichero(argv[1]);
	fichero.seekg(0, fichero.end); 
	final = fichero.tellg();
	cxproce=final/c_proces;
	    
	if(final%c_proces==0){
		Total--;
	} //cuando el resto es 0 se resta 1 para que el calculo sea exacto
	    

	fichero.seekg(0);
	for(int i=1;i<c_proces;i++) //Obtenemos los rangos a utilizar segun cantidad de proces
	{
	    n[0]=cxproce*i;
	    n[1]=cxproce*(i+1);
	    MPI_Send(n, 2, MPI_INT, i, 0, MPI_COMM_WORLD);

	}

    while(cxproce>=fichero.tellg()) //Utilizamos el proce 0
	{
		getline(fichero,linea);
		Total++;
	}
	cout<<"Proce 0 ="<<" "<<Total<<endl;
	for(int i=1;i<c_proces;i++)
	{
		 MPI_Recv(&AuxProces, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		 cout<<"Proce "<<i<<" = "<<AuxProces<<endl;
		 Total=AuxProces+Total;
	}
	cout<<"Total Archivo = "<<Total<<endl;

    fichero.close();
	}
	else
	{
		AuxProces=LargoArchivo(argv[1]);
		MPI_Send(&AuxProces, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}


  MPI_Finalize();
}