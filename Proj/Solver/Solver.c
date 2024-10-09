#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

typedef struct
{
  int x0, y0, x1, y1;
} Position;

Position* solv_horizontal_r(char** matrice, char* mot, int i, int j, int h_len)
{
  int k = 0;
  Position* result = (Position*)malloc(sizeof(Position));
  result->x0 = i;
  result->y0 = j;
  result->x1 = i;
  int w_len = strlen(mot);
    
  while (k < w_len && j + k < h_len && matrice[i][j + k] == mot[k])
  {
      k++;
  }
    
  if (k == w_len)
  {
      result->y1 = j + k - 1;
      return result;
  }
    
  return NULL;
}

Position* solv_diag_dr(char** matrice,char* mot, int i, int j, int v_len, int h_len)
{
  int k = 0;
  Position* result = (Position*)malloc(sizeof(Position));
  result->x0 = i;
  result->y0 = j;
  int w_len = strlen(mot);
  while(k < w_len && i+k < v_len && j+k < h_len && matrice[i+k][j+k] == mot[k])
  {
    k++;
  }

  if(k = w_len)
  {
    result->x1 = i + k - 1;
    result->y1 = j + k - 1;
    return result;
  }
  return NULL;
}

Position* solv_diag_dl(char** matrice, char* mot, int i, int j)
{
  int k = 0;
  Position* result = (Position*)malloc(sizeof(Position));
  result->x0 = i;
  result->y0 = j;
  int w_len = strlen(mot);
    
  while (k < w_len && i - k >= 0 && j + k < w_len && matrice[i - k][j + k] == mot[k])
  {
    k++;
  }
    
  if (k == w_len)
  {
      result->x1 = i - k + 1;
      result->y1 = j + k - 1;
      return result;
  }
    
  return NULL;
}

Position* solv_diag_ur(char** matrice, char* mot, int i, int j)
{
  int k = 0;
  Position* result = (Position*)malloc(sizeof(Position));
  result->x0 = i;
  result->y0 = j;
  int w_len = strlen(mot);
    
  while (k < w_len && i + k < w_len && j - k >= 0 && matrice[i + k][j - k] == mot[k])
  {
    k++;
  }
    
  if (k == w_len)
  {
      result->x1 = i + k - 1;
      result->y1 = j - k + 1;
      return result;
  }
    
  return NULL;
}

//needs to implements 4 more function

Position* solv_vertical_d(char** matrice, char* mot, int i, int j, int v_len)
{
  int k = 0;
  Position* result = (Position*)malloc(sizeof(Position));
  result->x0 = i;
  result->y0 = j;
  int w_len = strlen(mot);
    
  while (k < w_len && i + k < v_len && matrice[i + k][j] == mot[k])
  {
      k++;
  }
    
  if (k == w_len)
  {
      result->x1 = i + k - 1;
      result->y1 = j;
      return result;
  }
    
    return NULL;
}


Position* solv_horizontal_l(char** matrice, char* mot, int i, int j)
{
  int k = 0;
  Position* result = (Position*)malloc(sizeof(Position));
  result->x0 = i;
  result->y0 = j;
  int w_len = strlen(mot);
    
  while (k < w_len && j - k >= 0 && matrice[i][j - k] == mot[k])
  {
    k++;
  }
    
  if (k == w_len)
  {
    result->x1 = i;
    result->y1 = j - k + 1;
    return result;
  }
    
  return NULL;
}


Position* solv_diag_ul(char** matrice, char* mot, int i, int j)
{
  int k = 0;
  Position* result = (Position*)malloc(sizeof(Position));
  result->x0 = i;
  result->y0 = j;
  int w_len = strlen(mot);
    
  while (k < w_len && i - k >= 0 && j - k >= 0 && matrice[i - k][j - k] == mot[k])
  {
    k++;
  }
    
  if (k == w_len)
  {
    result->x1 = i - k + 1;
    result->y1 = j - k + 1;
    return result;
  }
    
  return NULL;
}


Position* solv_vertical_u(char** matrice, char* mot, int i, int j)
{
  int k = 0;
  Position* result = (Position*)malloc(sizeof(Position));
  result->x0 = i;
  result->y0 = j;
  int w_len = strlen(mot);
    
  while (k < w_len && i - k >= 0 && matrice[i - k][j] == mot[k])
  {
    k++;
  }
    
  if (k == w_len)
  {
    result->x1 = i - k + 1;
    result->y1 = j;
    return result;
  }
    
  return NULL;
}



Position* solver(char** matrice, char* mot, int v_len)
{
    int h_len = 0;

    // Compter le nombre de colonnes dans la première ligne
    while(matrice[0][h_len] != 0) 
    {
        h_len++;
    }

    int i = 0;
    int j = 0;
    while(i < v_len)
    {
        while(j < h_len - 1)
        {
            if(matrice[i][j] == mot[0])
            {
                if(j + 1 < h_len && matrice[i][j + 1] == mot[1])
                {
                    Position* result = solv_horizontal_r(matrice, mot, i, j, h_len);
                    if(result != NULL)
                    {
                        return result;
                    }
                }

                if(i + 1 < v_len && j + 1 < h_len && matrice[i + 1][j + 1] == mot[1])
                {
                    Position* result = solv_diag_dr(matrice, mot, i, j, v_len, h_len);
                    if(result != NULL)
                    {
                        return result;
                    }
                }

                if(i + 1 < v_len && matrice[i + 1][j] == mot[1])
                {
                    Position* result = solv_vertical_d(matrice, mot, i, j, v_len);
                    if(result != NULL)
                    {
                        return result;
                    }
                }

                if(j - 1 >= 0 && matrice[i][j - 1] == mot[1])
                {
                    Position* result = solv_horizontal_l(matrice, mot, i, j);
                    if(result != NULL)
                    {
                        return result;
                    }
                }

                if(i - 1 >= 0 && j - 1 >= 0 && matrice[i - 1][j - 1] == mot[1])
                {
                    Position* result = solv_diag_ul(matrice, mot, i, j);
                    if(result != NULL)
                    {
                        return result;
                    }
                }

                if(i - 1 >= 0 && matrice[i - 1][j] == mot[1])
                {
                    Position* result = solv_vertical_u(matrice, mot, i, j);
                    if(result != NULL)
                    {
                        return result;
                    }
                }

                if(i - 1 >= 0 && j + 1 < h_len && matrice[i - 1][j + 1] == mot[1])
                {
                    Position* result = solv_diag_dl(matrice, mot, i, j);
                    if(result != NULL)
                    {
                        return result;
                    }
                }

                if(i + 1 >= v_len && j - 1 >= 0 && matrice[i + 1][j - 1] == mot[1])
                {
                    Position* result = solv_diag_ur(matrice, mot, i, j);
                    if(result != NULL)
                    {
                        return result;
                    }
                }
            }
            // printf("matrice[%i][%i] = %c\n", j, i, matrice[i][j]);
            j++;
        }    
        j = 0;
        i++;
    }
    return NULL;
}


void toUpperCase(char *str) {
  while(*str){
    *str = toupper((unsigned char) *str);
    str++;
  }
}


int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    printf("Usage: %s <grid> <command>\n", argv[0]);
    return 1;
  }

  FILE *file;
  char line[MAX_LINE_LENGTH];
  char **lines = NULL;
  size_t count = 0;

  //open files in lecture mode

  file = fopen(argv[1], "r");
  if(file == NULL){
    fprintf(stderr, "Impossible d'ouvrire le fichier\n");
    return 1;
  }

  //read the file line by line
  // Lire le fichier ligne par ligne
  while (fgets(line, sizeof(line), file)) 
  {
    // Allouer de la mémoire pour une nouvelle ligne
    char *new_line = strdup(line);
    if (new_line == NULL) 
    {
      fprintf(stderr, "Erreur d'allocation de mémoire\n");
      fclose(file);
      return 1;
    }

    // Ajouter la nouvelle ligne au tableau
    char **temp = realloc(lines, sizeof(char *) * (count + 1));
    if (temp == NULL) 
    {
      fprintf(stderr, "Erreur d'allocation de mémoire\n");
      free(new_line);
      fclose(file);
      return 1;
    }
    lines = temp;
    toUpperCase(new_line);
    lines[count] = new_line;      // a check
    count++;
  }

  fclose(file);

  char *command = argv[2];
  toUpperCase(command);

  Position* result = solver(lines, command, count);
  if(result == NULL) 
  {
    printf("Not found\n");
  } 
  else 
  {
    printf("(%i,%i)(%i,%i)\n", result->y0, result->x0, result->y1, result->x1);
  }

  for (size_t i = 0; i < count; i++) 
  {
    //printf("%s", lines[i]);
    free(lines[i]); // Libérer la mémoire de chaque ligne
  }
  free(lines); // Libérer la mémoire du tableau de lignes

  return result;
}
