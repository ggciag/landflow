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
	//entra_var = fopen("param.txt", "r");
	
	long Nx=3300,Ny=4380,Nxy,i,j,cont,verif,verif2;
	
	long ii,jj,im,jm;
	
	//fscanf(entra_var,"%ld%ld",&Nx,&Ny);
	
	//fclose(entra_var);



	Nxy=Nx*Ny;
	
	double **x,**y,**z,**f;
	
	long **c,**mar,**indx,**indy,**vc;
	
	
	x = Aloc_matrix_real(Nx,Ny);
	y = Aloc_matrix_real(Nx,Ny);
	z = Aloc_matrix_real(Nx,Ny);
	f = Aloc_matrix_real(Nx,Ny);
	
	c = Aloc_matrix_long(Nx,Ny);
	mar = Aloc_matrix_long(Nx,Ny);
	vc = Aloc_matrix_long(Nx,Ny);
	indx = Aloc_matrix_long(Nx,Ny);
	indy = Aloc_matrix_long(Nx,Ny);
	
	FILE *entra;
	
	entra = fopen("ETOPO1_SouthAmerica.xyz","r");
	
	cont = 0;
	verif=0;
	for (j=0;j<Ny;j++){
		for (i=0;i<Nx;i++){
			fscanf(entra,"%lf%lf%lf",&x[i][j],&y[i][j],&z[i][j]);
			f[i][j]=1.0;
			
			indx[i][j]=i;
			indy[i][j]=j;
			
			if (z[i][j]<-50) {
				verif=1;
				//z[i][j]=-1;
				mar[i][j]=1;
				c[i][j]=1;
				cont++;
			}
			
			/*else if (i==0 || i==Nx-1 || j==0 || j==Ny-1){
				c[i][j]=1;
				z[i][j]=10000.0;
				cont++;
			}*/
		}
	}
	
	
	/*if (verif==0){//force the upper right node to be under the sea if no point is under -200 m
		c[Nx-1][0]=1;
		mar[Nx-1][0]=1;
		cont++;
	}*/
	
	fclose(entra);
	
	double topo_aux,topo_min,base_level=0;
	
	printf("Check the connectivity with the sea\n");
	
	verif=0;
	while(verif==0){
		verif=1;
		for (i=1;i<Nx-1;i++){
			for (j=1;j<Ny-1;j++){
				if (z[i][j]<0){
					if (c[i][j]==0){
						verif2=0;
						for (ii=i-1;ii<i+2;ii++){
							for (jj=j-1;jj<j+2;jj++){
								if (c[ii][jj]==1){
									verif2=1;
									verif=0;
								}
							}
						}
						if (verif2==1){
							c[i][j]=1;
							mar[i][j]=1;
							cont++;
						}
					}
				}
			}
		}
	}
	
	for (j=0;j<Ny;j++){
		for (i=0;i<Nx;i++){
			if (i==0 || i==Nx-1 || j==0 || j==Ny-1){
				if (c[i][j]==0){
					c[i][j]=1;
					z[i][j]=-1.0;
					cont++;
				}
			}
		}
	}
	
	
	
	
	long vbase_level,cont_ant=0;
	
	printf("ccont = %ld de %ld\n",cont, Nxy);
	
	while (cont<Nxy){
	//while (cont<540000){
		vbase_level=0;
		for (i=1;i<Nx-1;i++){
			for (j=1;j<Ny-1;j++){
				if (c[i][j]==0){
					im = i;
					jm = j;
					for (ii=i-1;ii<i+2;ii++){
						for (jj=j-1;jj<j+2;jj++){
							if (z[ii][jj]<=base_level && c[ii][jj]==1){
								im=ii;
								jm=jj;
							}
						}
					}
					if (im!=i || jm!=j){
						c[i][j]=1;
						cont++;
						indx[i][j]=im;
						indy[i][j]=jm;
						vbase_level=1;
					}
				
				}
			}
		}
		if (vbase_level==0){
			base_level+=1.0;
		}
		printf("cont = %ld de %ld, %lf\n",cont, Nxy,base_level);
		//if (cont_ant==cont) {printf("igual\n"); exit(-1);}
		cont_ant=cont;
	}
	
	printf("Done\n");
	
	
	
	/////////////////////////////
	
	for (j=0;j<Ny;j++){
		for (i=0;i<Nx;i++){
			f[i][j]=0;
		}
	}
	
	for (j=0;j<Ny;j++){
		for (i=0;i<Nx;i++){
			im = i;
			jm = j;
			
			f[im][jm]+=1.0;
			
			while(im!=indx[im][jm] || jm!=indy[im][jm]){
				ii = indx[im][jm];
				jj = indy[im][jm];
				im = ii;
				jm = jj;
				f[im][jm]+=1.0;
			}
		}
		printf("%ld de %ld\n",j,Ny-1);
		
	}
	

	/*
	
	cont = 0;
	for (j=0;j<Ny;j++){
		for (i=0;i<Nx;i++){
			f[i][j]=1.0;
			
			//indx[i][j]=i;
			//indy[i][j]=j;
			
			if (z[i][j]<0) {
				z[i][j]=0;
				c[i][j]=1;
				cont++;
			}
			
			else if (i==0 || i==Nx-1 || j==0 || j==Ny-1){
				c[i][j]=1;
				z[i][j]=10000.0;
				cont++;
			}
		}
	}
	
	
	base_level=0;
	
	while (cont<Nxy){
		
		
		for (i=1;i<Nx-1;i++){
			for (j=1;j<Ny-1;j++){
				vc[i][j]=0;
			}
		}
		
		
		for (i=1;i<Nx-1;i++){
			for (j=1;j<Ny-1;j++){
				if (c[i][j]==0){
					vc[indx[i][j]][indy[i][j]]=1;
				}
			}
		}
		
		for (i=1;i<Nx-1;i++){
			for (j=1;j<Ny-1;j++){
				if (c[i][j]==0 && vc[i][j]==0){
					f[indx[i][j]][indy[i][j]]+=f[i][j];
					c[i][j]=1;
					cont++;
				}
			}
		}
		printf("cont = %ld de %ld\n",cont, Nxy);
	}
	printf("FIM\n");

	*/
	

	
	
	
	
	FILE *sai,*sai_a;
	
	sai = fopen("net7.xyz","w");
	
	sai_a = fopen("sai_a.txt","w");
	
	cont = 0;
	for (j=0;j<Ny;j++){
		for (i=0;i<Nx;i++){
			//if (i==indx[i][j] && j==indy[i][j]) f[i][j]=0;
			//else f[i][j]=1;
			
			if (mar[i][j]==1) f[i][j]*=-1.0;
			
			fprintf(sai,"%lf %lf %lf %lf %ld %ld %ld %ld\n",x[i][j],y[i][j],f[i][j],z[i][j],i,j,indx[i][j],indy[i][j]);
			
		}
	}
	
	fclose(sai);
	
	fclose(sai_a);
	
	return 0;
	
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