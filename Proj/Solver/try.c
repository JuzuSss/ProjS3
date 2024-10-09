#include <stdio.h>
#include <ctype.h>  // Pour la fonction toupper()
#include <string.h>

void too_upper(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        // Utiliser toupper() pour convertir en majuscules
        str[i] = toupper(str[i]);
        i++;
    }
}




char* solver(char** matrice, char* word){
   
  int rows = sizeof(matrice) / sizeof(matrice[0]);  
  int cols = strlen(matrice[0]);  
  char first_letter = word[0]; 

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(matrice[i][j]==first_letter){
                finder(matrice,i,j,rows,cols,word);
            }
    }
}

char* finder(char** matrice,int posx, int posy,int rows,int cols, char* word){


    for(int i; i < 9;i++){
        if((posx <= 0 && posx > cols) && (posy <= 0 && posy > rows)) ){

        
            
        }
    }

    // if(posy == 0 && posx == 0){  //coin haut gauche
        
    // }
    // if(posy == 0 && posx == cols - 1){ //coin haut droit
        
    // }
    // if(posy == rows - 1 && posx == 0){ //coin bas gauche
        
    // }
    // if(posx == cols && posy == rows){  //coin bas droit
        
    // }
    // if(posy == 0 && posx < 0 && posx > cols - 1){       //la barre du dessus
        
    // }
    // if(posy == rows && posx < 0 && posx > cols - 1){   // la barre du bas
        
    // }
    // if(posx == 0 && posy < 0 && posy > rows - 1){       //la barre de gauche 
        
    // }
    // if(posx == cols && posy < 0 && posy > rows - 1){   // la barre du droit
        
    // }
    // if((posx < 0 && posx > cols - 1) && (posy < 0 && posy > rows - 1)){        // est cve qu il ets au centre
        
    // }   
    // return "";
}
  

  printf("(%i, %i)\n",1,2);
  return "";
}

int main(int argc, char *argv[]) {
    // Exemple de matrice
    char *matrice[7] = {
        "ABCDE",
        "FGHIJ",
        "KLMNO",
        "PQRST",
        "UVWXY",
        "UVWXY",
        "UIWXY"
    };

solver(matrice,"");

}

