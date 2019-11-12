FILE* fichier = NULL;
    int caractereActuel = 0;
    int tab_aux[3] = {0,0,0};
    int i = 0, j= 0;
    fichier = fopen("exemples_jeu.txt", "r+");
    if (fichier != NULL)
    {
      do
        {
              caractereActuel = fgetc(fichier); // On lit le caractère
              tab_aux[i]=caractereActuel;
              i++;
              if(i>=3){
                tab_n[j]= new_node(tab_aux[0]-48,tab_aux[1]-48,tab_aux[2]-48); // -48 car tab_aux stocke un caractère -> permet d'avoir un int 
                i = 0;
                j++;
              } // On l'affiche
        } while (caractereActuel != EOF);
      fclose(fichier);
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier.");
    }