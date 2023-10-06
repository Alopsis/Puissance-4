#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <MLV/MLV_all.h>

#define TAILLE 10
int tableau[TAILLE][TAILLE];

///////////////////// Partie MLV 


void init_window(){
    MLV_create_window 	( "Puissance 4","Puissance 4",100 + 55*TAILLE ,350 + 55 * TAILLE);
    MLV_clear_window(MLV_COLOR_BLACK); 	
}


void mlv_afficher_tableau(){
    MLV_clear_window(MLV_COLOR_BLACK);
    int i;
    int j;
    MLV_draw_filled_rectangle(50,200,57*TAILLE,57*TAILLE,MLV_COLOR_BLUE);
    for(i=0;i<TAILLE;i++){
        for(j=0;j<TAILLE;j++){
            if(tableau[i][j] == 0){
                MLV_draw_filled_circle(57*j+50+25,57*i+200+30,20,MLV_COLOR_WHITE);
            }else if(tableau[i][j] == 1){
                MLV_draw_filled_circle(57*j+50+25,57*i+200+30,20,MLV_COLOR_YELLOW);
            }else if (tableau[i][j] == 2){
                MLV_draw_filled_circle(57*j+50+25,57*i+200+30,20,MLV_COLOR_RED);
            }
        }
    }
    MLV_actualise_window();
}


void mlv_afficher_joueur(int joueur){
    MLV_draw_text(50,50,"Le joueur %d doit jouer",MLV_COLOR_WHITE,joueur);
    MLV_actualise_window();
}



int mlv_recup_coup(){
    int i;
    for(i=0;i<TAILLE;i++){
        MLV_draw_rectangle(57*i+50+5,150,50,50,MLV_COLOR_ANTIQUE_WHITE);
    }
    MLV_actualise_window();
    return mlv_clic_btn();

}

int mlv_clic_btn(){
    int x;
    int y;
    int i;
    while(1){
        MLV_wait_mouse(&x,&y);
        /*if((x > 50 && y > 150) && (x < 100 && y < 200)){
            return 1;
            break;
        }else if((x > 113 && y > 150) && (x < 160 && y < 200)){
            return 2;
            break;
        }else
                if((x > 170 && y > 150) && (x < 218 && y < 200)){
            return 3;
            break;
        }else
                if((x > 225 && y > 150) && (x < 274 && y < 200)){
            return 4;
            break;
        }else
                if((x > 280 && y > 150) && (x < 330 && y < 200)){
            return 5;
            break;
        }else
                if((x > 340 && y > 150) && (x < 390 && y < 200)){
            return 6;
            break;
        }else
                if((x > 400 && y > 150) && (x < 445 && y < 200)){
            return 7;
            break;
        }*/
        for(i=1;i<=TAILLE;i++){
            if((x > 56*i && y > 150) && (x < 56*i+50 && y < 200)){
                return i;
            }
        }
    }
}



















/////////////////////// Partie en C
void init_tableau()
{
    int i;
    int j;
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < 7; j++)
        {
            tableau[i][j] = 0;
        }
    }
}
int verif_ligne()
{
    int i;
    int j;
    for (i = 0; i <= TAILLE - 4; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            if (tableau[i][j] == tableau[i + 1][j] && tableau[i + 1][j] == tableau[i + 2][j] && tableau[i + 2][j] == tableau[i + 3][j] && tableau[i][j] != 0)
            {
                return 1;
            }
        }
    }
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j <= TAILLE - 4; j++)
        {
            if (tableau[j][i] == tableau[j + 1][i] && tableau[j + 1][i] == tableau[j + 2][i] && tableau[j + 2][i] == tableau[j + 3][i] && tableau[j][i] != 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int verif_diago()
{
    int i, j;

    // Vérification des diagonales montantes
    for (i = 0; i <= TAILLE - 4; i++)
    {
        for (j = 0; j <= TAILLE - 4; j++)
        {
            if (tableau[i][j] != 0 &&
                tableau[i][j] == tableau[i + 1][j + 1] &&
                tableau[i + 1][j + 1] == tableau[i + 2][j + 2] &&
                tableau[i + 2][j + 2] == tableau[i + 3][j + 3])
            {
                return 1;
            }
        }
    }

    // Vérification des diagonales descendantes
    for (i = 3; i < TAILLE; i++)
    {
        for (j = 0; j <= TAILLE - 4; j++)
        {
            if (tableau[i][j] != 0 &&
                tableau[i][j] == tableau[i - 1][j + 1] &&
                tableau[i - 1][j + 1] == tableau[i - 2][j + 2] &&
                tableau[i - 2][j + 2] == tableau[i - 3][j + 3])
            {
                return 1;
            }
        }
    }

    return 0; // Aucune séquence gagnante trouvée
}

int verif_tab()
{
    int i;
    int j;
    if (verif_ligne() || verif_diago())
    {
        return 1;
    }

    return 0;
}
int coup_correct(int coup, int joueur)
{
    int i;
    printf("Verif coup = %d et joueur = %d\n", coup, joueur);
    for (i = TAILLE - 1; i >= 0; i--)
    {
        if (tableau[i][coup] == 0)
        {
            printf("Insertion Unitaire 1\n");
            tableau[i][coup] = joueur + 1;
            return 1;
        }
    }

    printf("Coup impossible ! \n");
    return 0;
}
void afficher_tableau()
{
    int i;
    int j;
    for (i = 0; i < TAILLE; i++)
    {
        for (j = 0; j < TAILLE; j++)
        {
            printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    init_tableau();
    init_window();
    int tour = 1;
    int coup;
    afficher_tableau();
    mlv_afficher_tableau();
    do
    {


        mlv_afficher_joueur(tour%2);


        while (1)
        {
            coup = mlv_recup_coup();
            if (coup_correct(coup - 1, tour % 2))
            {
                break;
            }
        }

        afficher_tableau();
        mlv_afficher_tableau();

        tour++;
    } while (verif_tab() == 0);

    if (verif_tab() == -1)
    {
        printf("La partie n'a pas de gagnant !\n");
    }
    else
    {
        printf("Le joueur %d a gagné !\n", tour % 2);
    }
}
