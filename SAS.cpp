#include <stdio.h>
#include <string.h>
#include <time.h>
     //+++++++++++++++++++++++++++++STRUCTURES+++++++++++++++++++++++++++++++++++++++++
	 
typedef struct {
    int jour;
    int mois;
    int annee;
} date;	 
struct Tache {
        int id;
        char titre[50];
        char description[200];
        date deadline;
        char statut[20];
};



// ===================================Déclarations =========================================
           struct Tache taches[1000];
            int nbTaches = 0;
            int prochainID = 1;
//++++++++++++++++++++++++++++++++++AFFICHAGE+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void afficherMenu() {
    printf("\nMenu :\n");
    printf("1. Ajouter une nouvelle tâche\n");
    printf("2. jouter plusieurs taches\n");
    printf("3. Afficher la liste de toutes les tâches\n");
    printf("4. Modifier une tâche\n");
    printf("5. Supprimer une tâche\n");
    printf("6. Rechercher des tâches\n");
    printf("7. Afficher les statistiques\n");
    printf("8. Trier les Taches par titre\n");
    printf("9. Trier les Taches par deadline\n");
    printf("0. Quitter\n");
}

//+++++++++++++++++++AJOUTERTACHE+++++++++++++++++++++++++++++

  void ajouterTache() {
    int status;
    struct Tache nouvelleTache;
    nouvelleTache.id = prochainID++;
    printf("Titre de la tâche : ");
    scanf(" %[^\n]s", nouvelleTache.titre);
    printf("Description de la tâche : ");
    scanf(" %[^\n]s", nouvelleTache.description);
do {
        printf("Entrez le deadline de la tache (jour/mois/annee) :\n");
        scanf("%d%d%d", &nouvelleTache.deadline.jour, &nouvelleTache.deadline.mois, &nouvelleTache.deadline.annee);
    } while (nouvelleTache.deadline.jour > 31 || nouvelleTache.deadline.jour < 1 || nouvelleTache.deadline.mois > 12 || nouvelleTache.deadline.mois < 1 || nouvelleTache.deadline.annee < 2023);
    int choix_statut;
    do {
        printf("Choisissez le statut de la tache:\n");
        printf("1. a realiser\n");
        printf("2. En cours de realisation\n");
        printf("3. Finalisee\n");
        printf("Choix: ");
        scanf("%d", &choix_statut);

        switch (choix_statut) {
            case 1:
                strcpy(nouvelleTache.statut, "a realiser");
                break;
            case 2:
                strcpy(nouvelleTache.statut, "En cours de realisation");
                break;
            case 3:
                strcpy(nouvelleTache.statut, "Finalisee");
                break;
            default:
            printf("Choix invalide. Veuillez choisir parmi les options disponibles.\n");
        }
    } while (choix_statut < 1 || choix_statut > 3);

    taches[nbTaches++] = nouvelleTache;
    printf("Tâche ajoutée avec succès.\n");
    
}



 

    

//++++++++++++++++++AJOUTERPLUSIEURSTACHES+++++++++++++++++++++++++++
  
  void ajouterplusieurstaches(){
  	 
  	 	int i;
        int nombreTachesAAjouter;
        printf("Combien de tâches voulez-vous ajouter ? : ");
        scanf("%d", &nombreTachesAAjouter);
        for( i= 0; i < nombreTachesAAjouter; i++){
            ajouterTache();
            printf("%d tâches ajoutées avec succès.\n", nombreTachesAAjouter);
        }

        
    
  }
  
  //+++++++++++++++++++++++++++++AFFICHAGE++++++++++++++++++++++++++++++++++
  
  
void afficherToutesLesTaches() {
    printf("\nListe de toutes les tâches :\n");
    int i;
    for(i = 0; i < nbTaches; i++) {
        printf("ID : %d\n", taches[i].id);
        printf("Titre : %s\n", taches[i].titre);
        printf("Description : %s\n", taches[i].description);
        printf("Deadline : %d-%d-%d\n", taches[i].deadline.jour,taches[i].deadline.mois,taches[i].deadline.annee);
        printf("Statut : %s\n", taches[i].statut);
        printf("-----------\n");
    }
}
  //++++++++++++++++++++++++++++++++++ Tri ++++++++++++++++++++
void trierTachesParTitre() {
	int i,j;
    for (i = 0; i < nbTaches - 1; i++) {
        for (j = i+1; j < nbTaches ; j++) {
            if (strcmp(taches[j].titre, taches[j + 1].titre) < 0) {
                // Échanger les tâches
                struct Tache temp = taches[j];
                taches[j] = taches[i];
                taches[i] = temp;
            }
        }
    }
    printf("Tâches triées par ordre alphabétique du titre :\n");
    afficherToutesLesTaches();
}

// +++++++++++++++++++++++++++++++Fonction pour trier les tâches par deadline+++++++++++++++++++++++++++++++++++++
int CompareDeadlines(const Tache tache1, const Tache tache2) {
    // Comparez d'abord par année, puis par mois et enfin par jour.
    if (tache1.deadline.annee != tache2.deadline.annee) {
        return tache1.deadline.annee - tache2.deadline.annee;
    }
    if (tache1.deadline.mois != tache2.deadline.mois) {
        return tache1.deadline.mois - tache2.deadline.mois;
    }
    return tache1.deadline.jour - tache2.deadline.jour;
}

void TrierTachesParDeadline(Tache taches[], int nbr_tache) {
    // Trier les tâches en fonction de leurs délais
    for (int i = 0; i < nbr_tache - 1; i++) {
        for (int j = 0; j < nbr_tache - i - 1; j++) {
            if (CompareDeadlines(taches[j], taches[j + 1]) > 0) {
                // Swap the tasks
                Tache temp = taches[j];
                taches[j] = taches[j + 1];
                taches[j + 1] = temp;
            }
        }
    }
}

//+++++++++++++++++++MOFIFICATION++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++modifierDescriptionTache++++++++++++++++++++++++++++++++++++++++++++++++++

void modifierDescriptionTache(int id) {
	int i;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            printf("Entrez la nouvelle description pour la tâche %d : ", id);
            scanf("%s", taches[i].description);
            printf("Description mise à jour avec succès.\n");
            return;
        }
    }
    printf("Aucune tâche avec l'identifiant %d n'a été trouvée.\n", id);
}


//++++++++++++++++++++++++++++++++++++++++modifierDeadlineTache++++++++++++++++++++++++++++++++++++++++++++++++++

void modifierDeadlineTache(int id) {
	int i;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            printf("Entrez la nouvelle deadline (date limite) pour la tâche %d : ", id);
            scanf("%s", taches[i].deadline);
            printf("Deadline mise à jour avec succès.\n");
            return;
        }
    }
    printf("Aucune tâche avec l'identifiant %d n'a été trouvée.\n", id);
}

//++++++++++++++++++++++++++++++++++++++++modifierStatutTache++++++++++++++++++++++++++++++++++++++++++++++++++

void modifierStatutTache(int id) {
	int i;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            printf("Entrez le nouveau statut pour la tâche %d : ", id);
            scanf("%s", taches[i].statut);
            printf("Statut mis à jour avec succès.\n");
            return;
        }
    }
    printf("Aucune tâche avec l'identifiant %d n'a été trouvée.\n", id);
}


int modifier(){
	
	  // Sous-menu pour la modification
                int choixModification;
                printf("Menu de modification :\n");
                printf("1. Modifier la description d'une tâche\n");
                printf("2. Modifier le statut d'une tâche\n");
                printf("3. Modifier le deadline d'une tâche\n");
                printf("Entrez votre choix : ");
                scanf("%d", &choixModification);

                int idModification;
                printf("Entrez l'identifiant de la tâche à modifier : ");
                scanf("%d", &idModification);

                switch (choixModification) {
                    case 1:
                        modifierDescriptionTache(idModification);
                        break;
                    case 2:
                        modifierStatutTache(idModification);
                        break;
                    case 3:
                        modifierDeadlineTache(idModification);
                        break;
                    default:
                        printf("Choix invalide pour la modification.\n");
                }
             
	
	
	
}

void modifierTache(int id) {
	int i;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            printf("Nouveau titre de la tâche : ");
            scanf(" %[^\n]s", taches[i].titre);
            printf("Nouvelle description de la tâche : ");
            scanf(" %[^\n]s", taches[i].description);
            printf("Nouveau deadline (YYYY-MM-DD) : ");
            scanf("%s", taches[i].deadline);
            printf("Nouveau statut de la tâche (à réaliser, en cours de réalisation, finalisée) : ");
            scanf("%s", taches[i].statut);
            printf("Tâche modifiée avec succès.\n");
            return;
        }
    }
    printf("Tâche avec l'ID %d non trouvée.\n", id);
}


//+++++++++++++++++++++++++++++++++++SUPPRESSSION++++++++++++++++++++++++++++++++


void supprimerTache(int id) {
	int i,j;
    for (i = 0; i < nbTaches; i++) {
        if (taches[i].id == id) {
            for (j = i; j < nbTaches - 1; j++) {
                taches[j] = taches[j + 1];
            }
            nbTaches--;
            printf("Tâche supprimée avec succès.\n");
            return;
        }
    }
    printf("Tâche avec l'ID %d non trouvée.\n", id);
}

// Fonction pour calculer le nombre de jours restant avant une date limite
int DaysUntilDeadline(date deadline) {
    struct tm deadline_tm = {0};//Cette structure sera utilisée pour représenter la date limite sous une forme que le système peut comprendre.
    deadline_tm.tm_year = deadline.annee - 1900; //la structure tm utilise une année depuis 1900 et les mois sont indexés de 0 à 11.
    deadline_tm.tm_mon = deadline.mois - 1;        
    deadline_tm.tm_mday = deadline.jour;           

    time_t current_timestamp;
    time(&current_timestamp);
    struct tm *current_tm = localtime(&current_timestamp);

    deadline_tm.tm_hour = 0;//Les champs d'heure, minute et seconde de deadline_tm sont ensuite définis à 0,
    deadline_tm.tm_min = 0;//car nous ne nous intéressons qu'à la date, pas à l'heure exacte.
    deadline_tm.tm_sec = 0;

    time_t deadline_timestamp = mktime(&deadline_tm);
    double difference = difftime(deadline_timestamp, mktime(current_tm)) / (60 * 60 * 24); 

    return (int)difference;
}


// Function to calculate the difference in days between two dates
int calculateDateDifference(date date1, date date2) {
    struct tm tm1 = {0};
    tm1.tm_year = date1.annee - 1900;
    tm1.tm_mon = date1.mois - 1;
    tm1.tm_mday = date1.jour;

    struct tm tm2 = {0};
    tm2.tm_year = date2.annee - 1900;
    tm2.tm_mon = date2.mois - 1;
    tm2.tm_mday = date2.jour;

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    double difference = difftime(time1, time2) / (60 * 60 * 24);
    return (int)difference;
}
// Fonction pour créer une structure tm à partir d'une structure date
struct tm date_to_tm(date d) {
    struct tm tm_date = {0};
    tm_date.tm_year = d.annee - 1900;  
    tm_date.tm_mon = d.mois - 1;        
    tm_date.tm_mday = d.jour;           
    return tm_date;
}

void AfficherTachesProches(Tache A) {
    if (nbTaches == 0) {
        printf("La liste est vide !!\n");
        return;
    }

    time_t current_timestamp;
    time(&current_timestamp);

    int tr = 0; // To check if at least one task was found

    printf("Taches dont le deadline est dans 3 jours ou moins :\n");
    for (int i = 0; i < nbTaches; i++) {
    	struct tm deadline_tm = date_to_tm(A.deadline);
        time_t deadline_timestamp = mktime(&deadline_tm);
        int difference = difftime(deadline_timestamp, current_timestamp) / (60 * 60 * 24);
        
        if (difference >= 0 && difference <= 3) {
            printf("| Identifiant: %d | Titre: %s | Deadline: %02d/%02d/%04d\n",
                   A.id, A.titre,
                   A.deadline.jour, A.deadline.mois, A.deadline.annee);
            tr = 1; // Mark that at least one task was found
        }
    }
    if (!tr) {
        printf("Aucune tache dont le deadline est dans 3 jours ou moins n'a ete trouvee.\n");
    }
}

//++++++++++++++++++++++++++++++++++++++++rechercherTacheParId++++++++++++++++++++++++++++++++++++++++++++++++++


void rechercherTacheParId(int id) {
    printf("\nRecherche de la tâche par identifiant %d :\n", id);
    printf("ID\tTitre\tDescription\tDeadline\tStatut\n");
    int i;
    for (i = 0; i < nbTaches; i++) {
        struct Tache tache = taches[i];
        if (tache.id == id) {
            printf("%d\t%s\t%s\t%s\t%s\n", tache.id, tache.titre, tache.description, tache.deadline, tache.statut);
            return;
        }
    }
    printf("Aucune tâche avec l'identifiant %d n'a été trouvée.\n", id);
}



//++++++++++++++++++++++++++++++++++++++++rechercherTacheParTitre++++++++++++++++++++++++++++++++++++++++++++++++++
void rechercherTacheParTitre(char titre[100]) {
    printf("\nRecherche de la tâche par titre '%s' :\n", titre);
    printf("ID\tTitre\tDescription\tDeadline\tStatut\n");
    int trouve = 0;
    int i;
    for (i = 0; i < nbTaches; i++) {
        if (strcmp(taches[i].titre, titre) == 0) {
            printf("%d\t%s\t%s\t%s\t%s\n", taches[i].id, taches[i].titre, taches[i].description, taches[i].deadline, taches[i].statut);
            trouve = 1;
        }
    }
    if (!trouve) {
        printf("Aucune tâche avec le titre '%s' n'a été trouvée.\n", titre);
    }
}



int recherche(){
		int choixRecherche;
		int idRecherche;
		char titreRecherche[20];
		printf("Menu de recherche :\n");
        printf("1. Rechercher une tâche par son Identifiant\n");
        printf("2. Rechercher une tâche par son Titre\n");
		printf("3.Rechercher une ttâche par  "); 
        printf("Entrez votre choix : ");

        scanf("%d", &choixRecherche);
	    

        switch (choixRecherche) {
            case 1:
                
                printf("Entrez l'identifiant de la tâche à rechercher : ");
                scanf("%d", &idRecherche);
                rechercherTacheParId(idRecherche);
                break;
            case 2:
                
                printf("Entrez le titre de la tâche à rechercher : ");
                scanf(" %[^\n]s", titreRecherche);
                rechercherTacheParTitre(titreRecherche);
               break;
            default:
                printf("Choix invalide pour la recherche.\n");
                 break;
		}
}


// +++++++++++++++++++++++++STATISTIQUES+++++++++++++++++++++++++++

// Fonction pour effectuer des statistiques sur les tâches
void FaireDesStatistiques(Tache L[]) {
    if (nbTaches == 0) {
        printf("La liste est vide !!\n");
        return; 
    }

    int total_tasks = nbTaches;
    int completed_tasks = 0;
    int incomplete_tasks = 0;

    printf("*******Statistiques des taches :*******\n");
    printf("\n\tNombre total des taches : %d\n", total_tasks);
    
    for (int i = 0; i < nbTaches; i++) {
        if (strcmp(L[i].statut, "Finalisee") == 0) {
            completed_tasks++;
        } else {
            incomplete_tasks++;
        }

        int days_remaining = DaysUntilDeadline(L[i].deadline);
        printf("\n -->Tache %d\n", L[i].id);
        printf("    Titre: %s\n",L[i].titre);
        printf("    Statut : %s\n", L[i].statut);
        printf("    Deadline : %02d/%02d/%04d\n", L[i].deadline.jour, L[i].deadline.mois, L[i].deadline.annee);
        printf("    Jours restants jusqu'au delai : %d\n", days_remaining);
    }
    printf("\n        Nombre des taches completes : %d\n", completed_tasks);
    printf("        Nombre des taches incompletes : %d\n", incomplete_tasks);    

}

//++++++++++++++++++++++MAIN+++++++++++++++++++++++//


int main(){
	
    while(1){
        int choix,idSuppression;
	afficherMenu();
	printf("Choisir votre choix  :\n");
	scanf("%d",&choix);
	switch (choix) {
            case 1:
                ajouterTache();
                break;
            case 2:
            	ajouterplusieurstaches();
            case 3:
                afficherToutesLesTaches();
                break;
            case 4:
    			modifier();
              	break;
				          
            case 5:
                
                printf("Entrez l'identifiant de la tâche à supprimer : ");
                scanf("%d", &idSuppression);
                supprimerTache(idSuppression);
                break;
            case 6:
                recherche();
            case 7:
                FaireDesStatistiques(taches);
                break;
            case 0:
                printf("Au revoir !\n");
            case 8:
            	printf("\ntrier les taches par titre");
            	trierTachesParTitre();
                break;
            case 9:
            	printf("\ntrier les tache par deadline");
//            	trierTachesParDeadline();
            	break;
            default:
                printf("Choix invalide.\n");
                break;
    }
 
    }
	
	
}

