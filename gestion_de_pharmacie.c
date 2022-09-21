#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// **************Gestion de pharmacie (Projet SAS)****Mohcine-Khribech****************

typedef struct{
    char date[10];
    float prixTTC;
    int QA;//quantite achete
}infoP;
typedef struct {
   char Nom[50];
   char code[50];
   int Quntite;
   float prix;
   infoP IP;
}Produit;

Produit Pr[1000];
Produit change;


int Np=0;//nombre de produit
int Nnp=0 ;//Nnp : nombre de nouveau produit
float tp=0; //total des prix des produits vendus en journee courante
float PV=0; //nombre des produits vendus
int i,j;
char codech[50];


//fonction pour ajouter un ou plusieurs produits
void Ajouter(){
    int testcode = 0;
    printf("combien de produit vous-voulez ajouter :");
    scanf("%d",&Nnp);
    for(i=Np;i<(Np+Nnp);i++){
        printf("\t-Donne le Nom de Produit N%d :",i+1);
         scanf("%s",&Pr[i].Nom);
        do{
           testcode = 0;
           printf("\t-Donne le Code de Produit N%d :",i+1);
            scanf("%s",&Pr[i].code);
            for(j=0;j<i;j++){
               if(strcmp(Pr[i].code,Pr[j].code)==0){
                   testcode = 1;
                   printf("\t !ce code est deja exist !\n");
                  }
                }
         }while(testcode == 1);
        printf("\t-La Quantite que vous avez de ce Produit N%d :",i+1);
         scanf("%d",&Pr[i].Quntite);
        printf("\t-Donne le prix de Produit N%d :",i+1);
         scanf("%f",&Pr[i].prix);
        system("CLS");
    }
    Np+=Nnp;
}

//fonction pour calcule TTC
float TTC(float p){
     p+=p*0.15;
     return p;
}

//fonction pour affichage
void Affichage(){
    printf("\n\n");
    for(i=0;i<Np;i++){
        printf("Nom : %s     Prix : %.2fDH     Prix TTC : %.2fDH      Code : %s      Quantite : %d\n\n",Pr[i].Nom,Pr[i].prix,TTC(Pr[i].prix),Pr[i].code,Pr[i].Quntite);
    }
}
//LPOA : fonction pour lister tous les produits selon l'ordre Alphabetique croissant du nom
void LPOA(){
        for(i=1;i<Np;i++){
        j=i;
        while(strcmp(Pr[j-1].Nom,Pr[j].Nom)>0&&j>=0){
            change=Pr[j-1];
            Pr[j-1]=Pr[j];
            Pr[j]=change;
            j--;
        }
}Affichage();
   }


//LPOP : fonction pour lister tous les produits selon l'ordre decroissant du prix
void LPOP(){
   for(i=0;i<Np;i++){
        j=0;
        while(Pr[j].prix<Pr[j+1].prix){
            change=Pr[j+1];
            Pr[j+1]=Pr[j];
            Pr[j]=change;
            j++;
        }
}Affichage();
}

//Rechercher les produits par code
void Recherche_code(){
   int test = 0;
   printf("enter le code de produit que vous voulez chercher : ");
   scanf("%s",&codech);
   for(i=0;i<Np;i++){
    if(strcmp(codech,Pr[i].code)==0){
         printf("Nom: %s \tPrix:%.2f \tQuantite:%d\n",Pr[i].Nom,Pr[i].prix,Pr[i].Quntite);
         test = 1;
         break;
    }
   }
   if(test == 0) printf("Desole, les produits que vous recherchez sont introuvables  :( \n");
}

//Rechercher les produits par Quantite
void Recherche_quantite(){
    int Q,test=0;
    printf("enter la Quantite des produits que vous voulez chercher : ");
    scanf("%d",&Q);
       for(i=0;i<Np;i++){
    if(Pr[i].Quntite==Q){
        printf("Nom: %s \tPrix:%.2f \tQuantite:%d\n",Pr[i].Nom,Pr[i].prix,Pr[i].Quntite);
        test = 1;
    }
   }
   if(test == 0) printf("Desole, le produits que vous recherchez sont introuvables  :( \n");
}

//Acheter Produit
void AP(){
    int qa;//quantite acheter
    int test = 0;
    int testcode=0;
    do{
       testcode = 0;
       printf("entrer le code de produits : ");
       scanf("%s",&codech);
    for(i=0;i<Np;i++){
    if(strcmp(codech,Pr[i].code)==0){
                   testcode = 1;
                  }
    }if(testcode == 0)printf("\t !ce code n'existe pas!\n");
         }while(testcode == 0);
    printf("Combien de quantite que vous voulez acheter : ");
    scanf("%d",&qa);
    for(i=0;i<Np;i++){
        if(strcmp(codech,Pr[i].code)==0){
           if(qa>Pr[i].Quntite) printf("La quantite que vous souhaitez acheter est plus grande que la quantite restante :( \n");
           if(Pr[i].Quntite>=qa){
            printf("enregistrement de la date d'achat et le prixTTC(enregitrement de prixTTC est automatique) \n");
            printf("\n entrer la date d'acheter :");
            scanf("%s",Pr[i].IP.date);
            Pr[i].IP.QA=qa;
            Pr[i].Quntite-=qa;
            Pr[i].IP.prixTTC=TTC(Pr[i].prix)*qa;
            printf("Totale : %.2fDH\n",Pr[i].IP.prixTTC);
            printf("L'achat a ete avec succes :)\n");
           }else if(Pr[i].Quntite==0) printf("Aucune quantite ne reste de ce produit en stock .\n");
        }
    }
}

//etat de stock(affiche les produits(quantite<3))
void EDS(){
    int testEDS=0;
    for(i=0;i<Np;i++){
    if(Pr[i].Quntite<3){
        printf("Nom: %s \tPrix:%.2fDH \tQuantite:%d\n",Pr[i].Nom,Pr[i].prix,Pr[i].Quntite);
        testEDS=1;
    }
   }
   if(testEDS==0 && Np>0) printf("tous les produits dans le stock sont > 3 \n ");
}

//Alimenter le stock : mettre a jour la quantite
void ALS(){
    int test =0;
    int nq;//nouveau quantite
    printf("entrer le code de produits : ");
    scanf("%s",&codech);
    for(i=0;i<Np;i++){
    if(strcmp(codech,Pr[i].code)==0){
         printf("entrer la nouveau quantite de %s :",Pr[i].Nom);
         scanf("%d",&nq);
         Pr[i].Quntite=nq;
         test = 1;
        break;
    }
}
  if(test == 1) printf("La quantite a ete misa a jour avec succes :)\n");
   else("ce produit n'existe pas :(\n");
}

//Sumpprimer un produit
void Supprimer(){
    int test = 0;
     printf("entrer le code de produits : ");
      scanf("%s",&codech);
     for(i=0;i<Np;i++){
    if(strcmp(codech,Pr[i].code)==0){
         for(int j=i;j<Np;j++){
            Pr[j]=Pr[j+1];
         }
         test=1;
         Np--;
        break;
    }
}
if(test==1) printf("Le precessus de suppression s'est termine avec succes :) \n");
  else printf("Le produit que vous souhaitez supprimer n'existe pas \n");
}

//statique de vente
void SDV(){
    int test=0;
   float Max=0,Min;// max et min des prix des produits vendus
   char Dch[10];
   printf("entrer la date  : ");
   scanf("%s",&Dch);
   for(i=0;i<Np;i++){
    if(strcmp(Dch,Pr[i].IP.date)==0){
        tp+=Pr[i].prix*Pr[i].IP.QA;
        PV+=Pr[i].IP.QA;
        test=1;
        if(Pr[i].prix>Max){
            Max=Pr[i].prix;
        }
    }
   }
   Min=Max;
   for(i=0;i<Np;i++)
    if(strcmp(Dch,Pr[i].IP.date)==0)
        if(Pr[i].prix<Min) Min = Pr[i].prix;
if(test == 1){
    printf("\n\nle total des prix des produits vendu dans %s est %.2fDH (TTC)\n\n",Dch,TTC(tp));
     printf("                *     *     *     *     *     *\n\n");
   printf("la moyenne des prix des produits vendu dans %s est %.2fDH (TTC)\n\n",Dch,TTC(tp/PV));
    printf("                *     *     *     *     *     *\n\n");
    printf("Max des prix des produits vendu dans %s est %.2fDH (TTC)\n\n",Dch,TTC(Max));
     printf("                *     *     *     *     *     *\n\n");
    printf("Min des prix des produits vendu dans %s est %.2fDH (TTC)\n\n",Dch,TTC(Min));
         printf("                *     *     *     *     *     *\n\n");
}else
      printf("Aucun produit n'a ete achete a cette date\n");
}

int main(){
    int rch=0;//retourne a choix
    char choix[50];
    char choix2[50];
    int test3=0;
    int c;

    do{
        rch = 0;
    do{
       test3=0;
      system("CLS");
    printf("\n       ********************     GESTION DE PHARMACIE     ********************\n");
    printf("       *                                                                    *\n");
    printf("       *        (1):Ajouter des produits        (2):Affiche les Produit     *\n");
    printf("       *                                                                    *\n");
    printf("       *        (3):Acheter produit             (4):Rechercher les Produit  *\n");
    printf("       *                                                                    *\n");
    printf("       *        (5):Etat du stock               (6):Alimenter le stock      *\n");
    printf("       *                                                                    *\n");
    printf("       *        (7):Supprimer un produit        (8):Statique de vente       *\n");
    printf("       *                                                                    *\n");
    printf("       *                                                @Mohcine_Khribech   *\n");
    printf("       **********************************************************************\n");
       printf("entrer votre choix :");
       scanf("%s",choix);
       c=atoi(choix);
       if(!isdigit(choix)&& strlen(choix)>1 ||(c > 8 || c < 1 )){
        test3=1;
       }
    }while(test3==1);

    switch(c){

      case 1 : system("CLS");Ajouter() ; break;

      case 2 : do{
                  system("CLS");
                    test3 = 0;
                    printf("entrer (1) pour afficher les produits on order Alphabetique croissant .\n");
                    printf("entrer (2) pour afficher les produits on ordre decroissant du prix .\n");
                    printf("-->  ");
                      scanf("%s",&choix2);
                        c = atoi(choix2);
                      if(!isdigit(choix2)&& strlen(choix2)>1 ||(c > 2 || c < 1 )){
                        test3=1;
                        }
                 }while(test3 == 1);
                if(c == 1) LPOA();
                 else if(c == 2)LPOP();
                 break;

      case 3 : system("CLS"); AP() ; break;

      case 4 : do{
                 system("CLS");
                 test3=0;
                 printf("pour chercher les produit par Code entrer (1)\n");
                 printf("pour chercher les produits par quantite entrer (2)\n");
                 scanf("%s",&choix2);
                 c = atoi(choix2);
                 if(!isdigit(choix2)&& strlen(choix2)>1 ||(c > 2 || c < 1 )){
                        test3=1;
                    }
                 }while(test3 == 1);
                 if(c == 1) Recherche_code();
                  else if(c==2) Recherche_quantite();
                  break;

      case 5 : system("CLS"); EDS(); break;

      case 6 : system("CLS"); ALS(); break;

      case 7 : system("CLS"); Supprimer(); break;

      case 8 : system("CLS"); SDV(); break ;
    }
    if(Np ==0 ) printf("Il n'ya pas de produit pour le moment :(\n");
    printf("pour afficher les choix entrer (1) (any) pour quitter :");
    scanf("%d",&rch);
}while(rch==1);
return 0;
}


