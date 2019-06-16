#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gsl/gsl_fit.h>
 
#define MAX_LINE_SIZE 25
 
int main(int argc, const char * argv[]) {
    
    char file_name[] = "./data/spring_data.csv";
    FILE *fp;
    fp = fopen(file_name, "r");
    
    if (!fp) {
        fprintf(stderr, "failed to open file for reading\n");
        return 1;
    }
    
    char line[MAX_LINE_SIZE];
    char *result = NULL;
    double D[19];
    double M[19];
    int x = 0;
    int y = 0;
        
    while(fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        
    result = strtok(line, ",");
    int i = 0;
    while( result != NULL ) {
    if(i!=0){
      if(atof(result)>0){
        M[x] = atof(result);
        x++;
        }
    }
    else{
      if(atof(result)>0){
        D[y] = atof(result);
        y++;
        }
      i++;
    }
    result = strtok(NULL, ",");
    }
  }
    fclose (fp);
    for (int n=0;n<19;n++)
      {
        M[n]= M[n]*9.81;
      }
    double c0, c1, cov00, cov01, cov11, sumsq;
    gsl_fit_linear (M, 1, D, 1, 19,
                   &c0, &c1, &cov00, &cov01, &cov11,
                   &sumsq);
    printf ("# best fit: Y = %g + %g X\n", c0, c1);
    printf ("covariance matrix:\n");
    printf ("[ %g, %g\n  %g, %g]\n", cov00, cov01, cov01, cov11);
    printf ("sumsq = %g\n", sumsq);
    printf ("\n");


    FILE *pipe = popen("gnuplot -persist", "w");  
    int n = 19;
    if (pipe) {  
      fprintf(pipe, "set term wx\n");                 
      fprintf(pipe, "set datafile separator ','\n"); 
      fprintf(pipe, "set xlabel '|Force| (Newtons)'\n");
      fprintf(pipe, "set ylabel 'Distance (meters)'\n");
      fprintf(pipe, "set title '<X,Y> and Linear fit:y=%.4f*x+%.4f'\n",c1,c0);

      fprintf(pipe, "plot './data/spring_data.csv' using  ($2*9.81):1 title '(Force,Distance)',0.0656286 + 0.046432*x, \n");
     
      fflush(pipe); 
      fprintf(pipe,"exit \n"); 
      pclose(pipe);   
    }
    return 0;
}
