#include "exo5_10.c"

int main (int argc, char *argv[]){
	if (argc != 3) {
        printf("Utilisation:\n\t./main SOURCE DESTINATION\n");
        return 0;
    }
    // Si argv[1] n'est pas un répertoire
    if (!is_directory(argv[1])){
      printf("Assurez-vous que %s est un répertoire valide \n", argv[1]);
      exit (1);
    }
    mkdir(argv[2],0777);
    // Si argv[2] n'est pas un répertoire
    if (!is_directory(argv[2])){
      printf("Assurez-vous que %s est un répertoire valide \n", argv[2]);
      exit (1);
    }

    int ret = copie_arbre(argv[1], argv[2]);
    if (ret < 0) {
        printf("Erreur pendant la copie du répertoire\n");
        ret = -ret;
    } else {
        printf("Copie du répertoire : Succès\n");
    }
    printf("%d processus utilisés \n", ret);

    return 0;
}
