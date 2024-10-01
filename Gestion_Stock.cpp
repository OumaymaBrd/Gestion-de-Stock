#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
int link = 0;
// Couleur en C
#define c31 "\033[1;31m"
#define c32 "\033[1;32m"
#define c33 "\033[1;33m"
#define c34 "\033[1;34m"
#define c35 "\033[1;35m"
#define c0 "\033[0m"
#define max 100

// D?finition de struct 
typedef struct {
    char Nom[max][500];
    char tel[max][20];
    char email[max][500]; char id[500][10]; 
} Contact;

void affichage_Menu() {
    printf("\tLes Menus propos?s dans notre programme sont: \n\n");
    printf(c34 "\t\t1. Ajouter un Contact\n");
    printf("\t\t2. Afficher Tous les Contacts\n");
    printf("\t\t3. Modifier un Contact\n");
    printf("\t\t4. Supprimer un Contact\n");
    printf("\t\t5. Rechercher un Contact\n");
    printf("\t\t0. Quitter\n\n" c0);
}

bool isValidEmail(char email[]) {
    int atIndex = -1, dotIndex = -1, len = strlen(email);
    for (int i = 0; i < len; i++) {
        if (email[i] == '@') atIndex = i;
        else if (email[i] == '.' && atIndex != -1) dotIndex = i;
    }
    return (atIndex > 0 && dotIndex > atIndex + 1 && dotIndex < len - 1);
}

void saisir_et_verifier_nb_choix(int *nb_saisir, int borne_inferieure, int borne_superieure) {
    char saisie[100];
    while (1) {
        printf("\n\n\tChoisir un entier (%d ou %d) : ", borne_inferieure, borne_superieure);
        fgets(saisie, sizeof(saisie), stdin);
        if (sscanf(saisie, "%d", nb_saisir) == 1 && *nb_saisir >= borne_inferieure && *nb_saisir <= borne_superieure)
            break;
        else
            printf(c31 "\n\n\tErreur : Veuillez entrer un nombre entre %d et %d.\n" c0, borne_inferieure, borne_superieure);
    }
}

bool verifier_alphanumerique(char name[]) {
    for (int j = 0; j < strlen(name); j++) {
        if (!isalnum(name[j]) && name[j] != ' ') {
            printf(c31 "\n\n\tErreur : Le caract?re '%c' n'est pas valide.\n\n" c0, name[j]);
            return false;
        }
    }
    return true;
}

bool verifier_numero_tel(char name[]) {
    if (name[0] != '+') {
        printf(c31 "\n\n\tErreur : Le num?ro doit commencer par '+'.\n\n" c0);
        return false;
    }
    for (int j = 1; j < strlen(name); j++) {
        if (!isdigit(name[j]) && name[j] != ' ') {
            printf(c31 "\n\n\tErreur : Le caract?re '%c' n'est pas valide.\n\n" c0, name[j]);
            return false;
        }
    }
    return true;
}

bool contact_existe(Contact *C, int nb_total_contacts, const char *nom, const char *tel, const char *email) {
    for (int i = 0; i < nb_total_contacts; i++) {
        if (strcmp(C->Nom[i], nom) == 0 || strcmp(C->tel[i], tel) == 0 || strcmp(C->email[i], email) == 0) {
            return true; // Le contact existe déjà
        }
    }
    return false; // Le contact n'existe pas
}

void saisir_structure(Contact *C, int nb_saisir, int nb_total_contacts) {
    for (int i = 0; i < nb_saisir; i++) {
        int index = link + i;  // Insertion à partir du dernier contact saisi
         
         
        char nom[500], tel[20], email[500];

        // Génération de l'identifiant au format YC0000, YC0001, etc.
        sprintf(C->id[index], "YC%04d", index); // Formatage de l'identifiant

        // Saisie du nom
        while (1) {
            printf("\n\n\t Entrer les informations de Contact %d ", index + 1);
            printf("\n\t\tEntrez le nom du contact : ");
            fgets(nom, sizeof(nom), stdin);
            nom[strcspn(nom, "\n")] = '\0';  // Supprimer le retour à la ligne

            if (verifier_alphanumerique(nom)) break;
            else printf(c31 "\n\n\tErreur : Le nom saisi n'est pas valide. Veuillez réessayer.\n\n" c0);
        }

        // Saisie du numéro de téléphone
        while (1) {
            printf("\n\t\tEntrez le numéro de téléphone du contact (avec indicatif +) : ");
            fgets(tel, sizeof(tel), stdin);
            tel[strcspn(tel, "\n")] = '\0';

            if (verifier_numero_tel(tel)) break;
            else printf(c31 "\n\n\tErreur : Le numéro de téléphone saisi n'est pas valide. Veuillez réessayer.\n\n" c0);
        }

        // Saisie de l'email
        while (1) {
            printf("\n\t\tEntrez l'email du contact : ");
            fgets(email, sizeof(email), stdin);
            email[strcspn(email, "\n")] = '\0';

            if (isValidEmail(email)) break;
            else printf(c31 "\n\n\tErreur : L'email saisi n'est pas valide. Veuillez réessayer.\n\n" c0);
        }

        // Vérifier si le contact existe déjà
        if (contact_existe(C, nb_total_contacts, nom, tel, email)) {
            printf(c31 "\n\n\tErreur : Ce contact existe déjà. Veuillez saisir un nouveau contact.\n\n" c0);
            i--; // Réduire l'index pour reprendre la saisie
            continue; // Revenir au début de la boucle pour saisir à nouveau
        }

        // Si le contact n'existe pas, stocker les informations
        strcpy(C->Nom[index], nom);
        strcpy(C->tel[index], tel);
        strcpy(C->email[index], email);
    }
}

void afficher_contacts(Contact C, int nb_contacts) {
    if (nb_contacts == 0) {
        printf(c31 "\n\n\tOops, pas encore de contacts ajoutés !\n" c0);
    } else {
        printf("\n\t\tListe des contacts :\n");
        printf("\t---------------------------------------------------\n");
        printf("\t%-10s %-30s %-15s %-50s\n", "ID", "Nom", "Téléphone", "Email");
        printf("\t---------------------------------------------------\n");

        for (int i = 0; i < nb_contacts; i++) {
            printf("\t%-10s %-30s %-15s %-50s\n", C.id[i], C.Nom[i], C.tel[i], C.email[i]);
        }

        printf("\t---------------------------------------------------\n");
    }
}

void modifier_contact(Contact *C, int nb_total_contacts) {
    if (nb_total_contacts == 0) {
        printf(c31 "\n\n\tOops, pas encore de contacts ? modifier !\n" c0);
        return;
    }

    char nom_recherche[500];
    printf("\n\n\tEntrez le nom du contact ? modifier : ");
    fgets(nom_recherche, 500, stdin);
    nom_recherche[strcspn(nom_recherche, "\n")] = '\0';  // Supprimer le retour ? la ligne

    int index = -1;

    // Rechercher le contact par nom
    for (int i = 0; i < nb_total_contacts; i++) {
        if (strcmp(C->Nom[i], nom_recherche) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf(c31 "\n\n\tErreur : Contact avec le nom '%s' introuvable.\n\n" c0, nom_recherche);
        return;
    }

    printf(c33 "\n\n\tModification du contact %s\n\n" c0, C->Nom[index]);

    // Saisie du nouveau nom (avec validation)
    while (1) {
        printf("\n\tEntrez le nouveau nom du contact (laisser vide pour garder l'ancien) : ");
        char nouveau_nom[500];
        fgets(nouveau_nom, 500, stdin);
        nouveau_nom[strcspn(nouveau_nom, "\n")] = '\0';

        if (strlen(nouveau_nom) == 0 || verifier_alphanumerique(nouveau_nom)) {
            if (strlen(nouveau_nom) > 0) {
                strcpy(C->Nom[index], nouveau_nom);  // Si un nouveau nom a ?t? entr?, on le copie
            }
            break;
        } else {
            printf(c31 "\n\n\tErreur : Le nom saisi n'est pas valide. Veuillez r?essayer.\n\n" c0);
        }
    }

    // Saisie du nouveau num?ro de t?l?phone (avec validation)
    while (1) {
        printf("\n\tEntrez le nouveau num?ro de t?l?phone (laisser vide pour garder l'ancien) : ");
        char nouveau_tel[20];
        fgets(nouveau_tel, 20, stdin);
        nouveau_tel[strcspn(nouveau_tel, "\n")] = '\0';

        if (strlen(nouveau_tel) == 0 || verifier_numero_tel(nouveau_tel)) {
            if (strlen(nouveau_tel) > 0) {
                strcpy(C->tel[index], nouveau_tel);  // Si un nouveau num?ro a ?t? entr?, on le copie
            }
            break;
        } else {
            printf(c31 "\n\n\tErreur : Le num?ro de t?l?phone saisi n'est pas valide. Veuillez r?essayer.\n\n" c0);
        }
    }

    // Saisie du nouvel e-mail (avec validation)
    while (1) {
        printf("\n\tEntrez le nouvel e-mail (laisser vide pour garder l'ancien) : ");
        char nouvel_email[500];
        fgets(nouvel_email, 500, stdin);
        nouvel_email[strcspn(nouvel_email, "\n")] = '\0';

        if (strlen(nouvel_email) == 0 || isValidEmail(nouvel_email)) {
            if (strlen(nouvel_email) > 0) {
                strcpy(C->email[index], nouvel_email);  // Si un nouvel e-mail a ?t? entr?, on le copie
            }
            break;
        } else {
            printf(c31 "\n\n\tErreur : L'e-mail saisi n'est pas valide. Veuillez r?essayer.\n\n" c0);
        }
    }

    printf(c32 "\n\n\tLe contact a ?t? modifi? avec succ?s.\n\n" c0);
}
void supprimer_contact(Contact *C, int *nb_total_contacts) {
    if (*nb_total_contacts == 0) {
        printf(c31 "\n\n\tOops, pas encore de contacts ? supprimer !\n" c0);
        return;
    }

    char nom_recherche[500];
    printf("\n\n\tEntrez le nom du contact ? supprimer : ");
    fgets(nom_recherche, 500, stdin);
    nom_recherche[strcspn(nom_recherche, "\n")] = '\0';  // Supprimer le retour ? la ligne

    int index = -1;

    // Rechercher le contact par nom
    for (int i = 0; i < *nb_total_contacts; i++) {
        if (strcmp(C->Nom[i], nom_recherche) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf(c31 "\n\n\tErreur : Contact avec le nom '%s' introuvable.\n\n" c0, nom_recherche);
        return;
    }

    printf(c33 "\n\n\tSuppression du contact %s\n\n" c0, C->Nom[index]);

    // D?placer tous les contacts suivants d'une position pour combler le trou
    for (int i = index; i < *nb_total_contacts - 1; i++) {
        strcpy(C->Nom[i], C->Nom[i + 1]);
        strcpy(C->tel[i], C->tel[i + 1]);
        strcpy(C->email[i], C->email[i + 1]);
    }

    (*nb_total_contacts)--;  // D?cr?menter le nombre total de contacts
    printf(c32 "\n\n\tLe contact a ?t? supprim? avec succ?s.\n\n" c0);
}
void rechercher_contact(Contact C, int nb_total_contacts) {
    if (nb_total_contacts == 0) {
        printf(c31 "\n\n\tOops, pas encore de contacts ? rechercher !\n" c0);
        return;
    }

    char nom_recherche[500];
    printf("\n\n\tEntrez le nom du contact ? rechercher : ");
    fgets(nom_recherche, 500, stdin);
    nom_recherche[strcspn(nom_recherche, "\n")] = '\0';  // Supprimer le retour ? la ligne

    int trouve = 0;  // Flag pour savoir si le contact est trouv?

    // Rechercher le contact par nom
    for (int i = 0; i < nb_total_contacts; i++) {
        if (strcmp(C.Nom[i], nom_recherche) == 0) {
            printf(c32 "\n\n\tContact trouv? !\n\n" c0);
            printf("\tNom : %s\n", C.Nom[i]);
            printf("\tT?l?phone : %s\n", C.tel[i]);
            printf("\tEmail : %s\n", C.email[i]);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf(c31 "\n\n\tErreur : Le contact avec le nom '%s' est introuvable.\n" c0, nom_recherche);
    }
}


int main() {
    int choix;          // Variable choix pour le menu
    Contact C;          // D?claration de la structure Contact
    int nb_total_contacts = 0;  // Variable pour le nombre total de contacts

    printf(c33 "\n\n\n\t\tBienvenue dans le menu d'ajout de contacts \n\n" c0);

    do {
        affichage_Menu();
        saisir_et_verifier_nb_choix(&choix, 0, 5); 
        int nb_saisir;

        switch (choix) {
            case 1: { 
                printf(c33 "\n\n\n\t\tBienvenue dans le menu d'ajout de contacts \n\n" c0);
                saisir_et_verifier_nb_choix(&nb_saisir, 1, 100); 
                saisir_structure(&C, nb_saisir, nb_total_contacts); 
                nb_total_contacts += nb_saisir; 
                break;
            }
            case 2:{
                printf("\n\n\tModification d'un contact :\n");
                modifier_contact(&C, nb_total_contacts);
                
                break;
            }
            
            case 3:{
                 printf("\n\n\tSuppression d'un contact :\n");
                supprimer_contact(&C, &nb_total_contacts);
                break;
            }
            case 4: { 
                printf("\n\n\tAffichage des contacts ajout?s :\n");
                afficher_contacts(C, nb_total_contacts);
                break;
            }
            case 5:{
                printf("\n\n\tRecherche d'un contact :\n");
                rechercher_contact(C, nb_total_contacts);
                break;
            }
            case 0: {
                printf("Fin du programme ");
                break;
            }
            
        }
    } while (choix > 0);

    return 0;
}

