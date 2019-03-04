// Rosu Gabriel - David, 311CD
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Structura unui pixel
struct pixel
{
	int r;
	int g;
	int b;
};
typedef struct pixel Pixel;

// Alocare de memorie pentru o matrice de pixeli
Pixel*** alocare(Pixel ***a, int nl, int nc)
{
	int i, j;
	a = (Pixel ***)malloc(nl * sizeof(int **));
	for(i = 0; i < nl; i++)
		a[i] = (Pixel **)malloc(nc * sizeof(int *));
	for(i = 0; i < nl; i++)
		for(j = 0; j < nc; j++)
		a[i][j] = (Pixel *)malloc(sizeof(Pixel));

return a;
}

// Afisarea unei matrice de pixeli
void afisare(Pixel ***a, int nl, int nc)
{	
	fflush(stderr);
	int i, j;
	printf("%d %d\n", nc, nl);
	for(i = 0; i < nl; i++)
	{
		for(j = 0; j < nc; j++)
			{
				printf("%d ", a[i][j]->r);
				printf("%d ", a[i][j]->g);
				printf("%d ", a[i][j]->b);
			}
		printf("\n");
	}
}

// Eliberarea memoriei alocate pentru matricea de pixeli
Pixel*** eliberare(Pixel ***a, int nl, int nc)
{
	int i, j;

	for(i = 0; i < nl; i++)
		for(j = 0; j < nc; j++)
			free((Pixel *)a[i][j]);

	for(i = 0; i < nl; i++)
		free((Pixel **)a[i]);

	free((Pixel ***)a);

return a;
}

// Citirea unei matrice de pixeli
void citire(Pixel ***a, int nl, int nc)
{
	int i, j;

	for(i = 0; i < nl; i++)
		for(j = 0; j < nc; j++)
		{
			scanf("%d", &a[i][j]->r);
			scanf("%d", &a[i][j]->g);
			scanf("%d", &a[i][j]->b);
			if(a[i][j]->r < 0 || a[i][j]->r > 255)
			{
				fprintf(stderr, "%d\n", 2);
				a = eliberare(a, nl, nc);
				exit(EXIT_FAILURE);
			}
		}
}

int main()
{	
	fflush(stdout);
	int nc = 0, 
		nl = 0, 
		ok = 1;
	Pixel ***a;

// Citeste un nou cod, cat timp acesta este diferit de 0
	while(ok == 1)
	{	
		int cod;
		scanf("%d", &cod);

// COD 1
		if(cod == 1)
		{
			if(nc != 0 || nl != 0)
				a = eliberare(a, nl, nc);

			scanf("%d%d", &nc, &nl);

			if(1 <= nc && 1 <= nl && nc <= 1024 && nl <=1024)
			{
				a = alocare(a, nl, nc);
				citire(a, nl, nc);
			}
			else
			{
				if(nl != 0 && nc != 0)
					a = eliberare(a, nl, nc);
				nc = 0;
				nl = 0;
				fflush(stdout);
				fprintf(stderr,"%d\n",2);
				exit(EXIT_FAILURE);
			}
		}
		else
// COD 2
		if(cod == 2)
		{
			int start_line, start_col, end_line, end_col;
			scanf("%d%d%d%d", &start_col, &start_line, &end_col, &end_line);
			
			if(start_line < 0   || start_line > end_line || start_line >= nl ||
				end_line < 0    || end_line > nl         || start_col < 0    ||
				start_col >= nc || start_col > end_col   || end_col < 0      ||
				end_col > nc)
			{
				fflush(stdout);
				fprintf(stderr, "%d\n", 2);
				a = eliberare(a, nl, nc);
				exit(EXIT_FAILURE);
			}

			int ncb, nlb;
			int i, j;
			Pixel ***b;
			
			nlb = end_line - start_line + 1;
			ncb = end_col - start_col + 1;

			b = alocare(b, nlb, ncb);

// Copiere elemente din a in b
			for(i = start_line; i <= end_line; i++)
				for(j = start_col; j <= end_col; j++)
				{
					b[i - start_line][j - start_col]->r = a[i][j]->r;
					b[i - start_line][j - start_col]->g = a[i][j]->g;
					b[i - start_line][j - start_col]->b = a[i][j]->b;	
				}

			a = eliberare(a, nl, nc);
			nl = nlb;
			nc = ncb;
			a = alocare(a, nl, nc);

			for(i = 0; i < nl; i++)
				for(j = 0; j < nc; j++)
				{
					a[i][j]->r = b[i][j]->r;
					a[i][j]->g = b[i][j]->g;
					a[i][j]->b = b[i][j]->b;	
				}
			b = eliberare(b, nlb, ncb);
		}
		else
// COD 3
		if(cod == 3)
		{
			int i, j;
			int ncb, nlb;
			scanf("%d%d", &ncb, &nlb);

			if( nlb < 1 || nlb > 1024 || ncb < 1 || ncb > 1024)
			{
				fprintf(stderr, "%d\n", 2);
				a = eliberare(a, nl, nc);
				exit(EXIT_FAILURE);
			}

			Pixel ***b;
			b = alocare(b, nlb, ncb);

// Culoarea alb pentru toata matricea b			
			for(i = 0; i < nlb; i++)
				for( j = 0; j < ncb; j++)
				{
					b[i][j]->r = 255;
					b[i][j]->g = 255;
					b[i][j]->b = 255;	
				}

// Copierea elementelor din a in b
			for(i = 0; i < nlb && i < nl; i++)
				for(j = 0; j < ncb && j < nc; j++)
				{
					b[i][j]->r = a[i][j]->r;
					b[i][j]->g = a[i][j]->g;
					b[i][j]->b = a[i][j]->b;
				}

			a = eliberare(a, nl, nc);
			nc = ncb;
			nl = nlb;	
			a = alocare(a, nl, nc);	

// Copierea elementelor din b in a
			for(i = 0; i < nl; i++)
				for(j = 0; j < nc; j++)
				{
					a[i][j]->r = b[i][j]->r;
					a[i][j]->g = b[i][j]->g;
					a[i][j]->b = b[i][j]->b;	
				}

			b = eliberare(b, nl, nc);
		}
		else
// COD 4
		if(cod == 4)
		{
			int start_col, start_line, end_col, end_line;
			int r, g, b;
			scanf("%d%d%d%d", &start_col, &start_line, &end_col, &end_line);
			scanf("%d%d%d", &r, &g, &b);
			
			if( start_line < 0   || start_line > nl || end_line < 0          ||
				end_line > nl    || start_col < 0   || start_col > nc        ||
				end_col > nc     || end_col < 0     || start_col > end_col   ||
				r < 0 || g > 255 || r > 255         || start_line > end_line ||
				g < 0 || b > 255 || b < 0 )
			{
				fprintf(stderr,"%d\n",2);
				exit(EXIT_FAILURE);
				a = eliberare(a, nl, nc);
			}
			else
// Colorare zona
			{
				int i, j;
				for(i = start_line; i <= end_line; i++)
					for(j = start_col; j <= end_col; j++)
					{
						a[i][j]->r = r;
						a[i][j]->g = g;
						a[i][j]->b = b;	
					}
			}
		}
		else
// COD 5
		if(cod == 5)
		{
			int nr_iter;
			scanf("%d", &nr_iter);

			if(nl == 0 && nc == 0)
			{
				fflush(stdout);
				fprintf(stderr, "%d\n", 1);
				exit(EXIT_FAILURE);
			}
			else
			if(nr_iter < 0 || nr_iter > 2000)
			{
				a = eliberare(a, nl, nc);
				fflush(stdout);
				fprintf(stderr, "%d\n", 2);
				exit(EXIT_FAILURE);
			}
			
			int count;

			for(count = 1; count <= nr_iter; count++)
			{
				int i, j;
				Pixel ***b;
				b = alocare(b, nl, nc);

// Media elementelor din interior
				for(i = 1; i < nl - 1; i++)
					for(j = 1; j < nc - 1; j++)
					{
						int r,g,bb;
						r  = a[i-1][j]->r +
							 a[i+1][j]->r + 
							 a[i][j-1]->r + 
							 a[i][j+1]->r;
						
						g  = a[i-1][j]->g + 
							 a[i+1][j]->g + 
							 a[i][j-1]->g + 
							 a[i][j+1]->g;
						
						bb = a[i-1][j]->b + 
							 a[i+1][j]->b + 
							 a[i][j-1]->b + 
							 a[i][j+1]->b;
						
						r  = r / 4;
						g  = g / 4;
						bb = bb / 4;

						b[i][j]->r = r;
						b[i][j]->g = g;
						b[i][j]->b = bb;
					}

// Media elementelor de pe prima coloana
				for(i = 1; i < nl - 1; i++)
				{
					int r,g,bb;
					r  = a[i-1][0]->r + 
						 a[i+1][0]->r + 
						 a[i][1]->r;
					
					g  = a[i-1][0]->g + 
						 a[i+1][0]->g + 
						 a[i][1]->g;
					
					bb = a[i-1][0]->b + 
						 a[i+1][0]->b + 
						 a[i][1]->b;
					
					r  = r/3;
					g  = g/3;
					bb = bb/3;	

					b[i][0]->r = r;
					b[i][0]->g = g;
					b[i][0]->b = bb;	
				}

// Media elementelor de pe ultima coloana
				for(i = 1; i < nl - 1; i++)
				{
					int r,g,bb;
					
					r  = a[i-1][nc-1]->r + 
						 a[i+1][nc-1]->r + 
						 a[i][nc-2]->r;
					
					g  = a[i-1][nc-1]->g + 
						 a[i+1][nc-1]->g + 
						 a[i][nc-2]->g;
					
					bb = a[i-1][nc-1]->b + 
						 a[i+1][nc-1]->b + 
						 a[i][nc-2]->b;
					
					r  = r/3;
					g  = g/3;
					bb = bb/3;	
					
					b[i][nc-1]->r = r;
					b[i][nc-1]->g = g;
					b[i][nc-1]->b = bb;	
				}

// Media elementelor de pe prima linie
				for(j = 1; j < nc - 1; j++)
				{
					int r,g,bb;
					r  = a[0][j-1]->r + 
						 a[0][j+1]->r + 
						 a[1][j]->r;
					
					g  = a[0][j-1]->g + 
						 a[0][j+1]->g + 
						 a[1][j]->g;
					
					bb = a[0][j-1]->b + 
						 a[0][j+1]->b + 
						 a[1][j]->b;
					
					r  = r/3;
					g  = g/3;
					bb = bb/3;
					
					b[0][j]->r = r;
					b[0][j]->g = g;
					b[0][j]->b = bb;

				}

// Media elementelor de pe ultima linie
				for(j = 1; j < nc -1; j++)
				{
					int r,g,bb;
					r  = a[nl-1][j-1]->r + 
						 a[nl-1][j+1]->r + 
						 a[nl-2][j]->r;
					
					g  = a[nl-1][j-1]->g + 
						 a[nl-1][j+1]->g + 
						 a[nl-2][j]->g;
					
					bb = a[nl-1][j-1]->b + 
						 a[nl-1][j+1]->b + 
						 a[nl-2][j]->b;
					
					r  = r/3;
					g  = g/3;
					bb = bb/3;
					
					b[nl-1][j]->r = r;
					b[nl-1][j]->g = g;
					b[nl-1][j]->b = bb;
				}

// COLT STANGA SUS
				{
					int r, g, bb;

					r  = a[0][1]->r + a[1][0]->r;
					g  = a[0][1]->g + a[1][0]->g;
					bb = a[0][1]->b + a[1][0]->b;
					
					r  = r/2;
					g  = g/2;
					bb = bb/2;
					
					b[0][0]->r = r;
					b[0][0]->g = g;
					b[0][0]->b = bb;
							
				}

// COLT STANGA JOS
				{
					int r, g, bb;
					r  = a[nl-1][1]->r + a[nl-2][0]->r;
					g  = a[nl-1][1]->g + a[nl-2][0]->g;
					bb = a[nl-1][1]->b + a[nl-2][0]->b;
					
					r  = r/2;
					g  = g/2;
					bb = bb/2;
					
					b[nl-1][0]->r = r;
					b[nl-1][0]->g = g;
					b[nl-1][0]->b = bb;
							
				}

// COLT DREAPTA SUS
				{
					
					int r, g, bb;
					r  = a[0][nc-2]->r + a[1][nc-1]->r;
					g  = a[0][nc-2]->g + a[1][nc-1]->g;
					bb = a[0][nc-2]->b + a[1][nc-1]->b;
					
					r  = r/2;
					g  = g/2;
					bb = bb/2;
					
					b[0][nc-1]->r = r;
					b[0][nc-1]->g = g;
					b[0][nc-1]->b = bb;
							
				}

// COLT DREAPTA JOS
				{
					int r, g, bb;

					r  = a[nl-2][nc-1]->r + a[nl-1][nc-2]->r;
					g  = a[nl-2][nc-1]->g + a[nl-1][nc-2]->g;
					bb = a[nl-2][nc-1]->b + a[nl-1][nc-2]->b;
					
					r  = r/2;
					g  = g/2;
					bb = bb/2;
					
					b[nl-1][nc-1]->r = r;
					b[nl-1][nc-1]->g = g;
					b[nl-1][nc-1]->b = bb;
							
				}

// COPIERE ELEMENTE
				for(i = 0; i < nl; i++)
					for(j = 0; j < nc; j++)
					{
						a[i][j]->r = b[i][j]->r;
						a[i][j]->g = b[i][j]->g;
						a[i][j]->b = b[i][j]->b;
					}
				b = eliberare(b, nl, nc);

			}

					
		}
		else
// COD 6
		if(cod == 6)
		{
			int num_rot, k;
			scanf("%d", &num_rot);

			if(num_rot < 1 || num_rot > 3)
			{
				fflush(stderr);
				fprintf(stderr, "%d\n",2);
				a = eliberare(a, nl, nc);
				exit (EXIT_FAILURE);
			}
			else
			for(k = 1; k <= num_rot; k++)
			{
				int nlb, ncb;
				int i , j;
				Pixel ***b;
				nlb = nc;
				ncb = nl;
				
				b = alocare(b, nlb, ncb);
				
				for(i = 0; i < nlb; i++)
					for(j = 0; j < ncb; j++)
					{
						b[i][j]->r = a[nl - 1 - j][i]->r;
						b[i][j]->g = a[nl - 1 - j][i]->g;
						b[i][j]->b = a[nl - 1 - j][i]->b;	
					}

				a = eliberare(a, nl, nc);
				nl = nlb;
				nc = ncb;
				a = alocare(a, nl, nc);

				for(i = 0; i < nl; i++)
					for(j = 0; j < nc; j++)
					{
						a[i][j]->r = b[i][j]->r;
						a[i][j]->g = b[i][j]->g;
						a[i][j]->b = b[i][j]->b;	
					}

				b = eliberare(b, nl, nc);
			}
		}
		else
// COD 7
		if(cod == 7)
		{
			int start_col, start_line, r, g, b;
			scanf("%d%d%d%d%d", &start_col, &start_line, &r, &g, &b);
			if(start_line > nl || start_col > nc || r < 0 || r > 255 ||
						 g < 0 ||        g > 255 || b < 0 || b > 255)
			{
				a = eliberare(a, nl, nc);
				fflush(stderr);
				fprintf(stderr,"%d\n",2);
				exit(EXIT_FAILURE);
			}
			if( a[start_line][start_col]->r == r &&
				a[start_line][start_col]->g == g && 
				a[start_line][start_col]->b == b)
				{

				}
			else
			{
				int i, k;
				int r2, g2, b2;

				i = 0;
				k = 0;

				r2 = a[start_line][start_col]->r;
				g2 = a[start_line][start_col]->g;
				b2 = a[start_line][start_col]->b;
				
				int *vi, *vj;

				vi = (int *)malloc(1024*1024*sizeof(int));
				vj = (int *)malloc(1024*1024*sizeof(int));
				
				vi[0] = start_line;
				vj[0] = start_col;

//Adaugarea si prelucrarea elementelor din coada, cat timp nu 
//s-a ajuns la finalul acesteia
				while(i <= k)
				{
					if(vi[i] - 1 >= 0)
						if( a[vi[i] - 1 ][vj[i]]->r == r2 && 
							a[vi[i] - 1 ][vj[i]]->g == g2 &&
							a[vi[i] - 1 ][vj[i]]->b == b2)
						{
							a[vi[i] - 1 ][vj[i]]->r = r;
							a[vi[i] - 1 ][vj[i]]->g = g;
							a[vi[i] - 1 ][vj[i]]->b = b;
							k++;
							vi[k] = vi[i] - 1;
							vj[k] = vj[i];
						}
			
					if(vi[i] + 1 < nl)
						if( a[vi[i] + 1 ][vj[i]]->r == r2 && 
							a[vi[i] + 1 ][vj[i]]->g == g2 &&
							a[vi[i] + 1 ][vj[i]]->b == b2)
						{
							a[vi[i] + 1 ][vj[i]]->r = r;
							a[vi[i] + 1 ][vj[i]]->g = g;
							a[vi[i] + 1 ][vj[i]]->b = b;
							k++;
							vi[k] = vi[i] + 1;
							vj[k] = vj[i];
						}
			
					if(vj[i] - 1 >= 0)
						if( a[vi[i]][vj[i] - 1]->r == r2 && 
							a[vi[i]][vj[i] - 1]->g == g2 &&
							a[vi[i]][vj[i] - 1]->b == b2)
						{
							a[vi[i]][vj[i] - 1]->r = r;
							a[vi[i]][vj[i] - 1]->g = g;
							a[vi[i]][vj[i] - 1]->b = b;
							k++;
							vi[k] = vi[i];
							vj[k] = vj[i] - 1;
						}

					if(vj[i] + 1 < nc)
						if( a[vi[i]][vj[i] + 1]->r == r2 && 
							a[vi[i]][vj[i] + 1]->g == g2 &&
							a[vi[i]][vj[i] + 1]->b == b2)
						{
							a[vi[i]][vj[i] + 1]->r = r;
							a[vi[i]][vj[i] + 1]->g = g;
							a[vi[i]][vj[i] + 1]->b = b;
							k++;
							vi[k] = vi[i];
							vj[k] = vj[i] + 1;
						}
						
							i++;
		
				}

				free(vi);
				free(vj);	
				
			}
		}
		else
// COD 8
		if(cod == 8)
			{
				if(nl == 0 && nc == 0)
					{
						fflush(stderr);
						fprintf(stderr, "%d\n", 1);
						exit(EXIT_FAILURE);
					}
				else
				afisare(a, nl, nc);
			}
		else
// COD 0
		if(cod == 0)
			{
				ok = 0;
				a = eliberare(a, nl, nc);
				nl = 0;
				nc = 0;
			}
		else
// COD INVALID
		if( cod < 0 || cod > 8 )
		{
			if( nl != 0 || nc != 0)
				a = eliberare(a, nl, nc);
			fprintf(stderr, "%d\n",EPERM);
			exit(EXIT_FAILURE);
		}
		else
			return 0;
	}
return 0;
}