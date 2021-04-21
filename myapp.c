#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

// Make them global

GtkWidget	*window;
GtkWidget	*fixed1;

GtkWidget	*button1;
GtkWidget	*start_button;

GtkWidget	*redo_button;

GtkWidget	*finish_button;

GtkWidget	*label1;
GtkWidget	*label2;
GtkWidget	*combo1;
GtkEntry	*entry1;

GtkWidget	*dialog1;
GtkWidget	*box1;
GtkWidget	*ok_button;
GtkListStore	*liststore2;

GtkEntry	*entry2;

//fereastra Testeaza
GtkWidget	*radio1;
GtkWidget	*radio2;
GtkWidget	*radio3;

GtkBuilder	*builder; 


GtkWidget	*combo2;
GtkEntry	*entry3;
GtkListStore	*liststore1;

//fereastra Limba
GtkWidget	*radioRO;
GtkWidget	*radioEN;

//fereastra Detalii
GtkWidget	*rateButton;
GtkWidget	*powerButton;
GtkWidget	*dupButton;

GtkWidget	*detImage;
GtkWidget	*detBox;


//fereastra Rezultat
GtkWidget	*rezButton;
GtkWidget	*rezImage;
GtkWidget	*rezBox;
GtkWidget	*topLabel;
GtkWidget	*legendLabel;

GtkWidget	*label_nr_sesiunii;

GtkWidget	*rezButtonAnalitic;

GtkWidget	*all_rooms_added_button;

int numberOfIterations = 1;
int numberOfRedos;

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk
	FILE *nr_sesiunii;
	char * nr_ses;
	int nr;
	char line[1024];
	char text_label[500];
	
	FILE * fp;
   	char * line2 = NULL;
    	size_t len = 0;
    	ssize_t read;
    	char *line_without_enter;
   	char command[100];

   	GtkTreeIter iter;

//---------------------------------------------------------------------
// establish contact with xml code used to adjust widget settings
//---------------------------------------------------------------------
 
	builder = gtk_builder_new_from_file ("myapp.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
	label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
	combo1 = GTK_WIDGET(gtk_builder_get_object(builder, "combo1"));
	entry1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));

	dialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "dialog1"));
	box1 = GTK_WIDGET(gtk_builder_get_object(builder, "box1"));
	ok_button = GTK_WIDGET(gtk_builder_get_object(builder, "ok_button"));
	liststore2 = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore2"));

	entry2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry2"));

	start_button = GTK_WIDGET(gtk_builder_get_object(builder, "start_button"));

	redo_button = GTK_WIDGET(gtk_builder_get_object(builder, "redo_button"));

	finish_button = GTK_WIDGET(gtk_builder_get_object(builder, "finish_button"));
	
	//fereastra Testeaza
	radio1 = GTK_WIDGET(gtk_builder_get_object(builder, "radio1"));
	radio2 = GTK_WIDGET(gtk_builder_get_object(builder, "radio2"));
	radio3 = GTK_WIDGET(gtk_builder_get_object(builder, "radio3"));

	combo2 = GTK_WIDGET(gtk_builder_get_object(builder, "combo2"));
	entry3 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3"));
	liststore1 = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
	all_rooms_added_button = GTK_WIDGET(gtk_builder_get_object(builder, "all_rooms_added_button"));

	//fereastra Detalii
	rateButton = GTK_WIDGET(gtk_builder_get_object(builder, "rateButton"));
	powerButton = GTK_WIDGET(gtk_builder_get_object(builder, "powerButton"));
	dupButton = GTK_WIDGET(gtk_builder_get_object(builder, "dupButton"));
	
	detBox = GTK_WIDGET(gtk_builder_get_object(builder, "detBox"));
	detImage = GTK_WIDGET(gtk_builder_get_object(builder, "detImage"));
	
	//fereastra Rezultat
	rezBox = GTK_WIDGET(gtk_builder_get_object(builder, "rezBox"));
	rezImage = GTK_WIDGET(gtk_builder_get_object(builder, "rezImage"));
	legendLabel = GTK_WIDGET(gtk_builder_get_object(builder, "legendLabel"));
	rezButton = GTK_WIDGET(gtk_builder_get_object(builder, "rezButton"));
	topLabel = GTK_WIDGET(gtk_builder_get_object(builder, "topLabel"));
	rezButtonAnalitic = GTK_WIDGET(gtk_builder_get_object(builder, "rezButtonAnalitic"));
	
	//fereastra Limba
	radioRO = GTK_WIDGET(gtk_builder_get_object(builder, "radioRO"));
	radioEN = GTK_WIDGET(gtk_builder_get_object(builder, "radioEN"));
	
	


	label_nr_sesiunii  = GTK_WIDGET(gtk_builder_get_object(builder, "label_nr_sesiunii"));
	
	gtk_widget_show(window);

	g_object_unref(G_OBJECT(builder));
	
	//verific daca e prima sesiune sau nu, ca sa stiu daca mai este necesar sa introduc incaperile
	
        nr_sesiunii = fopen("nr_sesiunii.txt", "r");
        if (nr_sesiunii == 0)
        {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", nr_sesiunii, errno, strerror(errno));
        }

	   //iau fiecare linie
    	while ((fgets(line, 1024, nr_sesiunii)) != NULL)
   	 {
    		nr_ses = strtok(line,"\n"); //iar numele incaperii
		nr = atof(nr_ses); //convertesc indicele in double
	}
	
	printf("\n Numarul sesiunii = %d. \n", nr);
	
	if(nr == 1)
	{
	        strcpy(text_label, "Aceasta este prima sesiune de testare!\nIntroduceti incaperile.");
		gtk_label_set_text (GTK_LABEL (label_nr_sesiunii), (const gchar* ) text_label); 
		gtk_widget_show(label_nr_sesiunii); 
		
		gtk_widget_show((GtkWidget*) entry2); 
		gtk_widget_show(ok_button); 
		gtk_widget_show(all_rooms_added_button);
	}
	else	//daca nu e prima sesiune, ascund partea de introducere a incaperilor
	{
		
		gtk_widget_hide((GtkWidget*) entry2); 
		gtk_widget_hide(ok_button); 
		gtk_widget_hide(all_rooms_added_button);
		
		sprintf(text_label, "Aceasta este sesiunea %d de testare!\nIncaperile au fost deja introduse.\nPuteti incepe testarea.",nr);
		gtk_label_set_text (GTK_LABEL (label_nr_sesiunii), (const gchar* ) text_label); 
		gtk_widget_show(label_nr_sesiunii); 
		
		//iau incaperile din fisierul cu incaperi si le trimit catre drop-down list-ul din tab-ul de testare
		//  (ceea ce face de fapt on_all_rooms_added_button)
	
   		 fp = fopen("incaperi.txt", "r");
   		 if (fp == NULL)
     			   exit(EXIT_FAILURE);

    		while ((read = getline(&line2, &len, fp)) != -1) { //iau toate incaperile adaugate in incaperi.txt 
			//printf("%s", line);
			line_without_enter = strtok(line2,"\n"); //iau doar numele incaperii, fara \n
			gtk_list_store_append(liststore2, &iter);
			gtk_list_store_set(liststore2, &iter, 0, line2, -1);	//si le append-ui in storelist 

    		}
	
  		 strcpy(command,"echo 1 > nr_retestari.txt");
   		 system(command);	//pun initial 1 in nr_retestari, si daca nu se aleg 2 sau 3 retestari din radio buttons, ramane acest 1		
	}
	
	
	gtk_main();

	return EXIT_SUCCESS;

	}


//se apeleaza atunci cand in listsore (acel drop down list) se selecteaza o noua incapere pentru a fi testata
void	on_entry1_changed(GtkEntry *e) {

	gtk_widget_hide(redo_button); ///ascund butonul de redo
	
	gtk_widget_show(start_button); ///il fac vizibil pe cel de start

	char incapere[100];

	sprintf(incapere, "Doriti sa testati ''%s'' ?\nDaca da, apasati START si asteptati.", gtk_entry_get_text(e));
	gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

	}

//se apeleaza atunci cand apesi START pentru a incepe testarea
void on_start_button_clicked(GtkButton *b) {

	numberOfRedos = 1;  //pentru fiecare noua incapere,  reinitializez numarul de retestari

	char incapere[100];
	char command[100],command2[100],command3[100];
	FILE *finalFile, *auxFile;

	snprintf(command2, sizeof(command2), "echo %d > nr_deja_reluate.txt", numberOfRedos);
	system(command2);

        finalFile = fopen("rezultate_partiale.txt", "a");
        if (finalFile == 0)
        {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", finalFile, errno, strerror(errno));
        }

	auxFile = fopen("aux.txt", "w");
        if (auxFile == 0)
        {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", auxFile, errno, strerror(errno));
        }

        const gchar *buttonName = gtk_entry_get_text(entry1);
	snprintf(command3, sizeof(command), "echo %s > se_testeaza_acum.txt", buttonName);
	system(command3);

	snprintf(command, sizeof(command), "echo \"$(echo %s)\" >> rezultate_partiale.txt", buttonName);
	system(command);

	//pornesc testele apeland un script
	strcpy( command2, "setsid sudo bash testeaza.sh && exit" );
        //snprintf(command, sizeof(command), "echo (\"$(echo %s)\" > rezultate_finale.txt, buttonName ; echo da>rezultate_finale.txt)");	
	system(command2);
	

	if (numberOfRedos == numberOfIterations)
	{	
		//schimb textul label-ului
		sprintf(incapere, "Incaperea ''%s'' a fost testata 1 data.\nAlegeti o alta incapere.", gtk_entry_get_text(entry1));
		gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

		gtk_widget_hide(redo_button); ///ascund butonul de redo
	
		gtk_widget_show(start_button); ///il fac vizibil pe cel de start

	}
	else
	{
		//schimb textul label-ului pentru a anunta ca s-a efectuat testarea in incaperea selectata
		sprintf(incapere, "Incaperea ''%s'' a fost testata 1 data.\nVa rugam sa reluati testul!", gtk_entry_get_text(entry1));
		gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

		gtk_widget_hide(start_button); ///ascund butonul de start pentru a ramane doar cel de redo
	
		gtk_widget_show(redo_button); ///il fac vizibil pe cel de redo, care initial este ascuns
	}
	
	
	}


void on_ok_button_clicked(GtkButton *b2){
	char text_label[128], incapere[100];
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
	int ok;

	ok=1;
	sprintf(incapere, "%s\n", gtk_entry_get_text(entry2));	//incapere = ceea ce adaug in fisierul text


	FILE * file;
	  if ( (file = fopen("incaperi.txt", "a+") ) == NULL ) //deschid fisierul pentru append sau pentru read (a+)
  	{
    	 printf("Error: can't create file") ;
    	exit(1);
 	 }
	
	//verific ca incaperea pe care vreau sa o adaug sa nu fie deja introdusa
	while ((read = getline(&line, &len, file)) != -1) {
		if (!strcmp(line, incapere)) {
            		sprintf(text_label, "Incaperea ''%s'' a fost deja adaugata!\nIntroduceti o alta incapere!\n", gtk_entry_get_text(entry2)); // text_label = ceea ce pun in label
            		ok = 0;
			gtk_label_set_text (GTK_LABEL (label1), (const gchar* ) text_label); //schimb textul label-ului
			break;
		}
    	}

	//pun in fisierul "incaperi" incaprea adaugata, daca nu a fost adaugata anterior (daca ok==1)
	if (ok == 1) {
		fprintf(file,"%s",incapere);
		sprintf(text_label, "Incaperea \"%s\" a fost adaugata cu succes!\n", gtk_entry_get_text(entry2)); // text_label = ceea ce pun in label
		gtk_label_set_text (GTK_LABEL (label1), (const gchar* ) text_label); //schimb textul label-ului
	}

	fclose(file);
}


//dupa ce am adaugat toate incaperile, apas pe "Am terminat de adaugat incaperi"

void on_all_rooms_added_button_clicked(GtkButton *b3){

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *line_without_enter;
    char text_label[100];
    char command[100];

    GtkTreeIter iter;
	
    fp = fopen("incaperi.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) { //iau toate incaperile adaugate in incaperi.txt 
	//printf("%s", line);
	line_without_enter = strtok(line,"\n"); //iau doar numele incaperii, fara \n
	gtk_list_store_append(liststore2, &iter);
	gtk_list_store_set(liststore2, &iter, 0, line, -1);	//si le append-ui in storelist 

    }

   sprintf(text_label, "Toate incaperile au fost adaugate!\nPuteti incepe testele!", gtk_entry_get_text(entry2)); // text_label = ceea ce pun in label
		gtk_label_set_text (GTK_LABEL (label1), (const gchar* ) text_label); //schimb textul label-ului
	
   strcpy(command,"echo 1 > nr_retestari.txt");
   system(command);	//pun initial 1 in nr_retestari, si daca nu se aleg 2 sau 3 retestari din radio buttons, ramane acest 1

}



///butnul ce reia testul pentru aceeasi incapere
void on_redo_button_clicked(GtkButton *b){

	char incapere[100];
	char command[1000];
	char command2[100];

	strcpy(incapere,gtk_entry_get_text(entry1)); ///pun in "incapere" numele incaperii luat din entry field

	numberOfRedos++; //numar de cate ori am testat aceeasi incapere
        
	snprintf(command2, sizeof(command2), "echo %d > nr_deja_reluate.txt", numberOfRedos);
	system(command2);

	//pornesc testele apeland un script
	strcpy( command, "setsid sudo bash testeaza.sh && exit" );
        //snprintf(command, sizeof(command), "echo (\"$(echo %s)\" > rezultate_finale.txt, buttonName ; echo da>rezultate_finale.txt)");	
	system(command);
	
	//schimb textul label-ului pentru a anunta ca s-a efectuat testarea in incaperea selectata
	sprintf(incapere, "Incaperea ''%s'' a fost retestata de %d ori.\nVa rugam sa reluati testul!", gtk_entry_get_text(entry1),numberOfRedos);
	gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

	
	if (numberOfRedos == numberOfIterations)  //daca am retestat deja de cate ori mi-am propus
	{

		gtk_widget_hide(redo_button); ///ascund butonul de redo pentru a ramane doar cel de redo
		gtk_widget_show(start_button); ///il fac vizibil pe cel de start, care initial este ascuns
	
		//schimb labelul
		sprintf(incapere, "Incaperea ''%s'' a fost retestata de %d ori.\nAlegeti o alta incapere.", gtk_entry_get_text(entry1),numberOfRedos);
		gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);

        }


}


void	on_radio1_toggled(GtkRadioButton *b) {

	char command[100];
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));

	if (T) //daca radio1 e activ
	   numberOfIterations = 1;

	strcpy(command,"echo 1 > nr_retestari.txt");
	system(command);

	}

void	on_radio2_toggled(GtkRadioButton *b) {

	char command[100];
	FILE *nr_retestari;
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));

	if (T)
	   numberOfIterations = 2;

	strcpy(command,"echo 2 > nr_retestari.txt");
	system(command);


	}

void	on_radio3_toggled(GtkRadioButton *b) {

	char command[100];
	FILE *nr_retestari;
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
	if (T) 
	   numberOfIterations = 3;

	strcpy(command,"echo 3 > nr_retestari.txt");
	system(command);

	}


void on_finish_button_clicked(GtkButton *b){

	char command[100], command2[100];
	FILE *fp;
	char * line = NULL;
        size_t len = 0;
	char *line_without_enter;
	ssize_t read;

	GtkTreeIter iter;

	strcpy(command,"sudo gcc cumuleaza_retestari.c -o cumuleaza; sudo ./cumuleaza rezultate_partiale.txt");
	system(command);

	strcpy(command2,"sudo gcc listeaza_toate_testele.c -o listeaza; sudo ./listeaza");
	system(command2);

	 fp = fopen("toate_testele.txt", "r");
  	 if (fp == NULL)
      		 exit(EXIT_FAILURE);

    	while ((read = getline(&line, &len, fp)) != -1) { //iau toate incaperile adaugate in toate_testele.txt 
		//printf("%s", line);
		line_without_enter = strtok(line,"\n"); //iau doar numele incaperii, fara \n
		gtk_list_store_append(liststore1, &iter);
		gtk_list_store_set(liststore1, &iter, 0, line, -1);	//si le append-ui in storelist 

    }


}

void on_rateButton_clicked(GtkButton *b){


	char incapere[100];
	char *aux_incapere;
	char *nr_test;
	char rata[100];
	char test[100];
	char line[100];
	char command[100], command1[100];
	int len=0;
	char save_room[100];

	strcpy(rata,"_rata_");

	sprintf(incapere, "%s\n", gtk_entry_get_text(entry3));	//iau ce am in drop down list, de ex: incapere_test1
	strcpy(save_room,incapere); //salvez incaperea sa nu o pierd cu strtok

	aux_incapere = strtok(incapere,"_"); // aux_incapere = "incapere"

    	//iau lungimea incaperii si sar peste ea, dar si peste "_rata_"
    	len = strlen(incapere);

    	strcpy(test,save_room + len + 1); 

	strcat(aux_incapere,rata); 	
	nr_test = test;
	strcat(aux_incapere,nr_test);	//voi avea ceva de genul: incapere_rata_testX 
	aux_incapere = strtok(aux_incapere,"\n"); //elimin \n	
	strcat(aux_incapere,".txt");	//am format numele fisierului 	



	//ascund celelalte imagini
	gtk_widget_hide(detImage);

	//strcpy(command,"cp %s data.txt",aux_incapere);
	snprintf(command, sizeof(command), "cp %s data.txt",aux_incapere);
	system(command);
	
	//execut scriptul ce face plotul
	strcpy(command1, "setsid sudo gnuplot rata.p" );	
	system(command1);
	
	//afisez imaginea
	detImage = gtk_image_new_from_file("data.png");
	gtk_container_add (GTK_CONTAINER (detBox), detImage);
	gtk_widget_show (detImage);
	gtk_widget_show (detBox);



}


void on_powerButton_clicked(GtkButton *b){

	char incapere[100];
	char *aux_incapere;
	char *nr_test;
	char rata[100];
	char test[100];
	char line[100];
	char command[100], command1[100];
	int len=0;
	char save_room[100];

	strcpy(rata,"_putere_");

	sprintf(incapere, "%s\n", gtk_entry_get_text(entry3));	//iau ce am in drop down list, de ex: incapere_test1
	strcpy(save_room,incapere); //salvez incaperea sa nu o pierd cu strtok

	aux_incapere = strtok(incapere,"_"); // aux_incapere = "incapere"

    	//iau lungimea incaperii si sar peste ea, dar si peste "_rata_"
    	len = strlen(incapere);

    	strcpy(test,save_room + len + 1); 

	strcat(aux_incapere,rata); 	
	nr_test = test;
	strcat(aux_incapere,nr_test);	//voi avea ceva de genul: incapere_rata_testX 
	aux_incapere = strtok(aux_incapere,"\n"); //elimin \n	
	strcat(aux_incapere,".txt");	//am format numele fisierului 	
	
	//ascund celelalte imagini
	gtk_widget_hide(detImage);

	//strcpy(command,"cp %s data.txt",aux_incapere);
	snprintf(command, sizeof(command), "cp %s data.txt",aux_incapere);
	system(command);
	
	//execut scriptul ce face plotul
	strcpy(command1, "setsid sudo gnuplot putere.p" );	
	system(command1);
	
	//afisez imaginea
	detImage = gtk_image_new_from_file("data.png");
	gtk_container_add (GTK_CONTAINER (detBox), detImage);
	gtk_widget_show (detImage);
	gtk_widget_show (detBox);

}



void on_dupButton_clicked(GtkButton *b){

	char incapere[100];
	char *aux_incapere;
	char *nr_test;
	char rata[100];
	char test[100];
	char line[100];
	char command[100], command1[100];
	int len=0;
	char save_room[100];

	strcpy(rata,"_dup_");

	sprintf(incapere, "%s\n", gtk_entry_get_text(entry3));	//iau ce am in drop down list, de ex: incapere_test1
	strcpy(save_room,incapere); //salvez incaperea sa nu o pierd cu strtok

	aux_incapere = strtok(incapere,"_"); // aux_incapere = "incapere"

    	//iau lungimea incaperii si sar peste ea, dar si peste "_rata_"
    	len = strlen(incapere);

    	strcpy(test,save_room + len + 1); 

	strcat(aux_incapere,rata); 	
	nr_test = test;
	strcat(aux_incapere,nr_test);	//voi avea ceva de genul: incapere_rata_testX 
	aux_incapere = strtok(aux_incapere,"\n"); //elimin \n	
	strcat(aux_incapere,".txt");	//am format numele fisierului 	

	//ascund celelalte imagini
	gtk_widget_hide(detImage);

	//strcpy(command,"cp %s data.txt",aux_incapere);
	snprintf(command, sizeof(command), "cp %s data.txt",aux_incapere);
	system(command);
	
	//execut scriptul ce face plotul
	strcpy(command1, "setsid sudo gnuplot duplicate.p" );	
	system(command1);
	
	//afisez imaginea
	detImage = gtk_image_new_from_file("data.png");
	gtk_container_add (GTK_CONTAINER (detBox), detImage);
	gtk_widget_show (detImage);
	gtk_widget_show (detBox);

}



void on_rezButton_clicked(GtkButton *b) {
	char command[1000], command2[100];
	
	strcpy(command2,"sudo gcc indice_final.c -o indice_final ; sudo ./indice_final rezultate_finale.txt");	//genereaza rez_partiale.txt
	system(command2);


	gtk_widget_hide(rezImage);///ascund imaginile
	strcpy(command, "setsid sudo gnuplot rezultat.p" );	
	system(command);
	
	//afisez imaginea
	rezImage = gtk_image_new_from_file("data.png");
	gtk_container_add (GTK_CONTAINER (rezBox), rezImage);
	gtk_widget_show (rezImage);
	
	//pun in label incaperile
	FILE * fp;
    	char line[1000];
	char content[1000];
	int i=0;
	char p[5];
	
	
    	fp = fopen("rez_partiale.txt", "r");
    	
    	if (fp == NULL)
        	exit(EXIT_FAILURE);

	strcat(content,"\n");
			
    	while ((fgets(line, 1000, fp)) != NULL){
		sprintf(p,"%d. ", i);
		strcat(content,(const gchar* )p);
		//gtk_label_set_text (GTK_LABEL (legendLabel), (const gchar* ) content);
		strcat(content,line);
		i++;
	}
    	
	gtk_label_set_text (GTK_LABEL (legendLabel), (const gchar* ) content); 
	gtk_widget_show(legendLabel);
}


void on_rezButtonAnalitic_clicked(GtkButton *b) {

	char command[100], command2[100];

	strcpy(command,"sudo gcc indice_final.c -o indice_final ; sudo ./indice_final rezultate_finale.txt");	//genereaza rez_partiale.txt
	system(command);

	strcpy(command2,"sudo gcc top3.c -o top3 ; sudo ./top3 rez_partiale.txt");	//imi genereaza top3.txt
	system(command2);

	
	FILE * fp;
    	char line[1024];
	char content[1000];
	
	
    	fp = fopen("top3.txt","r");
    	if (fp == NULL)
        	exit(EXIT_FAILURE);

    	 while ((fgets(line, 1000, fp)) != NULL){
		strcat(content,line);
	}
	
    	
	gtk_label_set_text (GTK_LABEL (topLabel), (const gchar* ) content); 
	gtk_widget_show(topLabel);


}

//fereastra Limba

void	on_radioRO_toggled(GtkRadioButton *b) {
/*
	char command[100];
	char incapere[100];
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));

	if (T) { //daca radioRO e activ
		//pentru labels
		sprintf(incapere, "Incaperea ''%s'' a fost testata 1 data.\nAlegeti o alta incapere.", gtk_entry_get_text(entry1));
		gtk_label_set_text (GTK_LABEL (label2), (const gchar* ) incapere);
		//pentru butoane
		char *ButtonStance == "Connect";
		gtk_button_set_label(GTK_BUTTON(EntryButton), ButtonStance);
		
	}

	//strcpy(command,"echo 1 > nr_retestari.txt");
	//system(command);
*/
	}

void	on_radioEN_toggled(GtkRadioButton *b) {

	char command[100];
	char incapere[100];
	char * nr_ses;
	int nr;
	char line[1024];
	gboolean T = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));

	if (T) { //daca radioEN e activ
		FILE* nr_sesiunii;
		nr_sesiunii = fopen("nr_sesiunii.txt", "r");
		if (nr_sesiunii == 0)
		{
		fprintf(stderr, "Failed to open file %s (%d: %s)\n", nr_sesiunii, errno, strerror(errno));
		}

		   //iau fiecare linie
	    	while ((fgets(line, 1024, nr_sesiunii)) != NULL)
	   	 {
	    		nr_ses = strtok(line,"\n"); //iar numele incaperii
			nr = atof(nr_ses); //convertesc indicele in double
		}
		
		//pentru labels
		sprintf(incapere, "This is the %dth sesion. \n Rooms were added. \n You can start de test.", nr);
		gtk_label_set_text (GTK_LABEL (label_nr_sesiunii), (const gchar* ) incapere); 
		gtk_widget_show(label_nr_sesiunii); 
		//pentru butoane
		char *ButtonStance = "RATE";
		gtk_button_set_label(GTK_BUTTON(rateButton), ButtonStance);
		//Pentru ferestre
		//ButtonStance = "RATE";
		//gtk_button_set_text(GTK_STACK(stk_sw0), ButtonStance);
		
	}

	//strcpy(command,"echo 1 > nr_retestari.txt");
	//system(command);

	}
