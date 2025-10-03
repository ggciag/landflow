#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double **Aloc_matrix_real (long p, long n);
long **Aloc_matrix_long (long p, long n);
double *Aloc_vector_real (long n);
long *Aloc_vector_long (long n);


int main()
{
	
	//FILE *entra_var;
	//entra_var = fopen("param2.txt", "r");
	
	long Nx=3300,Ny=4380,i,j;//, Vx,Vy;
	
	long ii,jj;
	
	//fscanf(entra_var,"%ld%ld%ld%ld",&Nx,&Ny,&Vx,&Vy);
	
	//fclose(entra_var);

	
	double **x,**y,**z,**f,**va,**va_f;
	
	
	x = Aloc_matrix_real(Nx,Ny);
	y = Aloc_matrix_real(Nx,Ny);
	z = Aloc_matrix_real(Nx,Ny);
	f = Aloc_matrix_real(Nx,Ny);
	
	va = Aloc_matrix_real(Nx,Ny);
	va_f = Aloc_matrix_real(Nx,Ny);
	
	long **indx,**indy;
	
	indx = Aloc_matrix_long(Nx,Ny);
	indy = Aloc_matrix_long(Nx,Ny);
	
	printf("Reading net7.xyz\n");

	FILE *entra;
	
	entra = fopen("net7.xyz","r");

	
	
	
	for (j=0;j<Ny;j++){
		//printf("aqui\n");
		for (i=0;i<Nx;i++){
			fscanf(entra,"%lf%lf%lf%lf%ld%ld%ld%ld",&x[i][j],&y[i][j],&f[i][j],&z[i][j],&ii,&jj,&indx[i][j],&indy[i][j]);
		}
		//printf("%ld %ld   %lf %lf\n",j,jj, x[Nx-1][j], y[Nx-1][j]);
	}
	
	fclose(entra);
	
	
	
	printf("Done\n");
	
	//double t=0.,t_max=passos_por_mes*nmeses;
	
	double vR;
	
	
	char ss[100];
	
	long cont_step=0;
	
	FILE *saida;
	
	while (cont_step<6000){
		
		printf("cont_step = %ld\n",cont_step);
		
		for (j=0;j<Ny;j++){
			for (i=0;i<Nx;i++){
				vR = 1.0;//prec[int(floor(t/(passos_por_mes)))][domin[i][j]]/1000./(passos_por_mes);
				

				va[i][j]=vR+va_f[i][j];
				va_f[i][j]=0.0;
			}
		}
		
		
		
		for (j=0;j<Ny;j++){
			for (i=0;i<Nx;i++){
				if (i!=indx[i][j] || j!=indy[i][j]){
					va_f[indx[i][j]][indy[i][j]]+=va[i][j];
				}
			}
		}
		//printf("tempo: %lf %lf %lf\n",t*dias_por_mes/passos_por_mes,vR,vR*passos_por_mes);
		
		cont_step++;
		
		if (cont_step%1000==0){
			
			sprintf(ss,"t_%ld.txt",cont_step);
			
			saida = fopen(ss,"w");
			
			for (j=0;j<Ny;j++){
				for (i=0;i<Nx;i++){
					fprintf(saida,"%lf\n",va_f[i][j]);
				}
			}
			
			fclose(saida);
				
		}
		if (cont_step%10==0){
			printf("cont_step = %ld\n",cont_step);
		}
		
		
	}
	
	
	return(0);
	
}


double **Aloc_matrix_real (long p, long n)
{
	double **v;
	long i;
	if(p < 1 || n<1){
		printf("** Erro: Parametro invalido **\n");
		return(NULL);
	}
	v = (double **) calloc(p, sizeof(double *));
	for(i=0; i<p; i++){
		v[i] = (double *) calloc (n, sizeof(double));
		if (v[i] == NULL) {
			printf("** Erro: Memoria Insuficiente **");
			return(NULL);
		}
	}
	return(v);
}
long **Aloc_matrix_long (long p, long n)
{
	long **v;
	long i;
	if(p < 1 || n<1){
		printf("** Erro: Parametro invalido **\n");
		return(NULL);
	}
	v = (long **) calloc(p, sizeof(long *));
	for(i=0; i<p; i++){
		v[i] = (long *) calloc (n, sizeof(long));
		if (v[i] == NULL) {
			printf("** Erro: Memoria Insuficiente **");
			return(NULL);
		}
	}
	return(v);
}
double *Aloc_vector_real (long n)
{
	double *v;
	v = (double *) calloc(n, sizeof(double));
	if (v == NULL){
		printf("* Erro: Memoria Insuficiente *");
		return(NULL);
	}
	return(v);
}

long *Aloc_vector_long (long n)
{
	long *v;
	v = (long *) calloc(n, sizeof(long));
	if (v == NULL){
		printf("* Erro: Memoria Insuficiente *");
		return(NULL);
	}
	return(v);
}