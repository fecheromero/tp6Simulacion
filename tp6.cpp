//============================================================================
// Name        : tp6.cpp
// Author      : tumama
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
int cantidadDeColasDeEnvoltura=4;
int cantidadDeColasDeCobro=4;
int tiempoDeProximaLlegada=0;
int tiemposDeProximasEnvolturas[4];
int personasPorColaDeEnvoltura[4];
int personasPorColaDeCobros[4];
int tiemposDeProximosCobros[4];
int tiempoDeProximoCobro=INT_MAX;
int tiempoDeProximaEnvoltura=INT_MAX;
int tiempo=0;
int sumatoriaDeTiemposDeEsperaEnEnvoltura=0;
int sumatoriaDeTiemposDeEsperaEnCobro=0;
int sumatoriaDeTiemposDeEnvoltura=0;
int sumatoriaDeTiemposDeCobro=0;
int totalDePersonas=0;
int controlCobroAnteVaciamientoDeCola=INT_MAX;
int controlEnvolturaAnteVaciamientoDeCola=INT_MAX;
int tiempoFinal=50;
int min(int vector[],int max){
	int posicionMinima=0;
	for(int i=0;i<max;i++){
		if(vector[i]<vector[posicionMinima]){
			posicionMinima=i;
		}
	}
	return posicionMinima;
}
int max(int vector[],int max){
	int maximo=vector[0];
	for(int i=0;i<max;i++){
		if(vector[i]>maximo){
			maximo=vector[i];
		}
	}
	return maximo;
}
void setearVector(int vector[], int max, int valor){
	for(int i=0;i<max;i++){
		vector[i]=valor;
	}
}
float random2(){
	  float i=rand();
	  float j=i/RAND_MAX;
	  return j;
}
int intervaloEntreArribos(){
	return (random2()*3);
};
int tiempoDeEnvoltura(){
	int j= 1+(random2()*7);
	return j;
}
int tiempoDeCobro(){
	 int j=1+ (random2()*10);
	 return j;
}

void atenderLlegada(){
	tiempo=tiempoDeProximaLlegada;
	tiempoDeProximaLlegada=tiempo+ intervaloEntreArribos();
	int colaElegida=min(personasPorColaDeEnvoltura,cantidadDeColasDeEnvoltura);
	totalDePersonas++;
	if(personasPorColaDeEnvoltura[colaElegida]==0){
		tiemposDeProximasEnvolturas[colaElegida]=tiempo;
	}
	personasPorColaDeEnvoltura[colaElegida]++;
};
void atenderEnvoltura(int cola){

	sumatoriaDeTiemposDeEsperaEnEnvoltura+=(tiemposDeProximasEnvolturas[cola]-tiempo)*(personasPorColaDeEnvoltura[cola]-1);
	tiempo=tiemposDeProximasEnvolturas[cola];
	int tiempoDeEstaEnvoltura=tiempoDeEnvoltura();
	sumatoriaDeTiemposDeEnvoltura+=tiempoDeEstaEnvoltura;
	tiemposDeProximasEnvolturas[cola]=tiempo+tiempoDeEstaEnvoltura;
	personasPorColaDeEnvoltura[cola]--;
	int colaDeCobrosElegida=min(personasPorColaDeCobros,cantidadDeColasDeCobro);
	if(personasPorColaDeCobros[colaDeCobrosElegida]==0){
		tiemposDeProximosCobros[colaDeCobrosElegida]=tiempo+tiempoDeEstaEnvoltura;
	}
	personasPorColaDeCobros[colaDeCobrosElegida]++;

}
void atenderCobro(int cola){
	sumatoriaDeTiemposDeEsperaEnCobro+=(tiemposDeProximosCobros[cola]-tiempo)*(personasPorColaDeCobros[cola]-1);
tiempo=tiemposDeProximosCobros[cola];
int tiempoDeEsteCobro=tiempoDeCobro();
sumatoriaDeTiemposDeCobro+=tiempoDeEsteCobro;
tiemposDeProximosCobros[cola]=tiempo+ tiempoDeEsteCobro;

personasPorColaDeCobros[cola]--;
}
void imprimirResultados(){
	printf("para %d cajas de envoltura y %d cajas de cobro\n",cantidadDeColasDeEnvoltura,cantidadDeColasDeCobro);
	float promedioDeTiempoOciosoDeCobro= tiempo-(sumatoriaDeTiemposDeCobro/cantidadDeColasDeCobro);
	float promedioDeTiempoOciosoDeEnvoltura= tiempo-(sumatoriaDeTiemposDeEnvoltura/cantidadDeColasDeEnvoltura);
	float promedioDeEsperaEnEnvoltura=sumatoriaDeTiemposDeEsperaEnEnvoltura/totalDePersonas;
	float promedioDeEsperaEnCobro=sumatoriaDeTiemposDeEsperaEnCobro/totalDePersonas;
	printf("promedio de tiempo ocioso de cobro: %f \n",promedioDeTiempoOciosoDeCobro);
	printf("promedio de tiempo ocioso de envoltura: %f \n",promedioDeTiempoOciosoDeEnvoltura);
	printf("promedio de tiempo de espera en cobro: %f \n",promedioDeEsperaEnCobro);
	printf("promedio de tiempo de espera en envoltura: %f \n",promedioDeEsperaEnEnvoltura);

}
int proximaColaDeEnvolturaAAtender(){
	int posicionMinima=0;
	for(int i=0;i<cantidadDeColasDeEnvoltura;i++){
		if(tiemposDeProximasEnvolturas[i]<tiemposDeProximasEnvolturas[posicionMinima] && personasPorColaDeEnvoltura[i]>0){
			posicionMinima=i;
		}
	}
	if(personasPorColaDeEnvoltura[posicionMinima]>0){
	return posicionMinima;
	}
	else{
		return -1;
	}

}
int proximaColaDeCobroAAtender(){
	int posicionMinima=0;
	for(int i=0;i<cantidadDeColasDeCobro;i++){
		if(tiemposDeProximosCobros[i]<tiemposDeProximosCobros[posicionMinima] && personasPorColaDeCobros[i]>0){
			posicionMinima=i;
		}
	}
	if(personasPorColaDeCobros[posicionMinima]>0){
	return posicionMinima;
	}
	else{
		return -1;
	}

}
int main() {
	setearVector(tiemposDeProximasEnvolturas,cantidadDeColasDeEnvoltura,0);
	setearVector(tiemposDeProximosCobros,cantidadDeColasDeCobro,0);
	setearVector(personasPorColaDeCobros,cantidadDeColasDeCobro,0);
	setearVector(personasPorColaDeEnvoltura,cantidadDeColasDeEnvoltura,0);
	while(tiempo<tiempoFinal || max(personasPorColaDeCobros,cantidadDeColasDeCobro)!=0 || max(personasPorColaDeEnvoltura,cantidadDeColasDeEnvoltura)!=0 ){
		if(tiempo>=tiempoFinal){
			tiempoDeProximaLlegada=INT_MAX;
		}
	int colaDeProximaEnvoltura=proximaColaDeEnvolturaAAtender();
if(colaDeProximaEnvoltura==-1){

	tiempoDeProximaEnvoltura=INT_MAX;
}
else{

	tiempoDeProximaEnvoltura=tiemposDeProximasEnvolturas[colaDeProximaEnvoltura];
}
	int colaDeProximoCobro=proximaColaDeCobroAAtender();
	if(colaDeProximoCobro==-1){
		tiempoDeProximoCobro=INT_MAX;
	}
	else{
		tiempoDeProximoCobro=tiemposDeProximosCobros[colaDeProximoCobro];

	}
	if(tiempoDeProximaLlegada
			<=tiempoDeProximaEnvoltura){
		if(tiempoDeProximaLlegada<=tiempoDeProximoCobro){
			atenderLlegada();
		}
		else {
			atenderCobro(colaDeProximoCobro);
		}
	}
	else{
		if(tiempoDeProximaEnvoltura<=tiempoDeProximoCobro){
			atenderEnvoltura(colaDeProximaEnvoltura);
		}
		else{
			atenderCobro(colaDeProximoCobro);
		}

	}
	}
	imprimirResultados();
}
