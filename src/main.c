#include "../include/headers.h"
#include "../include/prototypes.h"
#include "../include/callback.h"

GtkWidget *mainWindow = NULL;

GtkWidget* textViewLabel = NULL;
gchar *sUtf8 = NULL;
GtkWidget *zone = NULL;

int udpActif;
int tcpActif;

int flood_on = 0;


int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    setWindow();

    return EXIT_SUCCESS;
}

void setWindow(void)
{
    GtkWidget *TCPButton    = NULL;
    GtkWidget *UDPButton    = NULL;
    GtkWidget *addSrcIP     = NULL;
    GtkWidget *addSrcPort   = NULL;
    GtkWidget *addDstIP     = NULL;
    GtkWidget *addDstPort   = NULL;

    GtkWidget *image    = NULL;
    //GtkWidget *zone     = NULL;

    GtkWidget *srcIPEntry   = NULL;
    GtkWidget *srcPortEntry = NULL;
    GtkWidget *dstIPEntry   = NULL;
    GtkWidget *dstPortEntry = NULL;

    GtkWidget* srcIPLabel   = NULL;
    GtkWidget* srcPortLabel = NULL;
    GtkWidget* dstIPLabel   = NULL;
    GtkWidget* dstPortLabel = NULL;

    //GtkWidget *textView     = NULL;
    GtkWidget* TitleLabel   = NULL;
    //GtkWidget* textViewLabel = NULL;


    //har *sUtf8 = NULL;

/*********************** Definition de la fenêtre *****************************************************************************/

    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(mainWindow), 800, 600);
    gtk_window_set_title(GTK_WINDOW(mainWindow), "TCP/UDP Flooder");
    gtk_window_set_position(GTK_WINDOW(mainWindow),  GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(mainWindow), "destroy", G_CALLBACK(quit), NULL);

    zone = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(mainWindow), zone);

/************************* Chargement de l'image a partir d'un fichier ***********************************************************/

    image = gtk_image_new_from_file("images/hack_800_600.jpg");
    gtk_fixed_put(GTK_FIXED(zone), image, 0, 0);

/******************************* Création des entrées de saisis ******************************************************************/

    /* Source IP and Port  */
    srcIPEntry = gtk_entry_new_with_max_length(21);
    gtk_fixed_put(GTK_FIXED(zone), srcIPEntry, 30, 40);
    gtk_widget_set_size_request(srcIPEntry, 161, 30);

    srcPortEntry = gtk_entry_new_with_max_length(5);
    gtk_fixed_put(GTK_FIXED(zone), srcPortEntry, 630, 40);
    gtk_widget_set_size_request(srcPortEntry, 100, 30);

    /* Destination IP and Port  */
    dstIPEntry = gtk_entry_new_with_max_length(21);
    gtk_fixed_put(GTK_FIXED(zone), dstIPEntry, 30, 175);
    gtk_widget_set_size_request(dstIPEntry, 161, 30);

    dstPortEntry = gtk_entry_new_with_max_length(5);
    gtk_fixed_put(GTK_FIXED(zone), dstPortEntry, 630, 175);
    gtk_widget_set_size_request(dstPortEntry, 100, 30);

/********************************** Création des boutons **************************************************************************/

    TCPButton = gtk_button_new_with_label("TCP Flood");
    gtk_fixed_put(GTK_FIXED(zone), TCPButton, 30, 275);
    gtk_widget_set_size_request(TCPButton, 161, 40);

    g_signal_connect(G_OBJECT(TCPButton), "clicked", G_CALLBACK(msgBox), NULL);
    g_signal_connect(G_OBJECT(TCPButton), "clicked", G_CALLBACK(startTCPFlooding), NULL);

    UDPButton = gtk_button_new_with_label("UDP Flood");
    gtk_fixed_put(GTK_FIXED(zone), UDPButton, 600, 275);
    gtk_widget_set_size_request(UDPButton, 161, 40);

    g_signal_connect(G_OBJECT(UDPButton), "clicked", G_CALLBACK(msgBox), NULL);
    g_signal_connect(G_OBJECT(UDPButton), "clicked", G_CALLBACK(startUDPFlooding), NULL);

    addSrcIP = gtk_button_new_with_label("Add Source IP");
    gtk_fixed_put(GTK_FIXED(zone), addSrcIP, 30, 90);
    gtk_widget_set_size_request(addSrcIP, 161, 30);

    g_signal_connect(G_OBJECT(addSrcIP), "clicked", G_CALLBACK(getSrcIP), srcIPEntry);

    addSrcPort = gtk_button_new_with_label("Add Source Port");
    gtk_fixed_put(GTK_FIXED(zone), addSrcPort, 600, 90);
    gtk_widget_set_size_request(addSrcPort, 161, 30);

    g_signal_connect(G_OBJECT(addSrcPort), "clicked", G_CALLBACK(getSrcPort), srcPortEntry);

    addDstIP = gtk_button_new_with_label("Add Destination IP");
    gtk_fixed_put(GTK_FIXED(zone), addDstIP, 30, 220);
    gtk_widget_set_size_request(addDstIP, 161, 35);

    g_signal_connect(G_OBJECT(addDstIP), "clicked", G_CALLBACK(getDstIP), dstIPEntry);

    addDstPort = gtk_button_new_with_label("Add Destination Port");
    gtk_fixed_put(GTK_FIXED(zone), addDstPort, 600, 220);
    gtk_widget_set_size_request(addDstPort, 161, 35);

    g_signal_connect(G_OBJECT(addDstPort), "clicked", G_CALLBACK(getDstPort), dstPortEntry);

/********************************** Widget des log textView ***********************************************************************/

/*
    textView = gtk_text_view_new();

    gtk_fixed_put(GTK_FIXED(zone), textView, 0, 450);
    gtk_widget_set_size_request(textView, 800, 150);

    gtk_text_view_set_border_window_size (GTK_TEXT_VIEW(textView), GTK_TEXT_WINDOW_LEFT, 10);
    gtk_text_view_set_border_window_size (GTK_TEXT_VIEW(textView), GTK_TEXT_WINDOW_RIGHT, 10);
    gtk_text_view_set_border_window_size (GTK_TEXT_VIEW(textView), GTK_TEXT_WINDOW_TOP, 10);
*/

/******************************************* Création des labels *******************************************************************/

    /* Title */
    TitleLabel = gtk_label_new("TCP/UDP Flooder");

    sUtf8 = g_locale_to_utf8("<span face=\"Purisa\"><big><u><b>TCP/UDP Flooder.</b></u></big></span>", -1, NULL, NULL, NULL);

    gtk_label_set_markup(GTK_LABEL(TitleLabel), sUtf8);
    g_free(sUtf8);

    gtk_fixed_put(GTK_FIXED(zone), TitleLabel, 300, 5);

    /* Source IP and Port */

    /* Source IP */
    srcIPLabel = gtk_label_new("Source IP :");

    sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><big><b>Source IP</b></big></span>", -1, NULL, NULL, NULL);

    gtk_label_set_markup(GTK_LABEL(srcIPLabel), sUtf8);
    g_free(sUtf8);

    gtk_fixed_put(GTK_FIXED(zone), srcIPLabel, 55, 10);

    /* Source Port */
    srcPortLabel = gtk_label_new("Source Port :");

    sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><big><b>Src Port</b></big></span>", -1, NULL, NULL, NULL);

    gtk_label_set_markup(GTK_LABEL(srcPortLabel), sUtf8);
    g_free(sUtf8);

    gtk_fixed_put(GTK_FIXED(zone), srcPortLabel, 637, 10);

    /* Destination IP and Port */

    /* Destination IP */
    dstIPLabel = gtk_label_new("Source IP :");

    sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><big><b>Destination IP</b></big></span>", -1, NULL, NULL, NULL);

    gtk_label_set_markup(GTK_LABEL(dstIPLabel), sUtf8);
    g_free(sUtf8);

    gtk_fixed_put(GTK_FIXED(zone), dstIPLabel, 35, 150);


    /* Destination Port */

    dstPortLabel = gtk_label_new("Source Port :");

    sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><big><b>Dst Port</b></big></span>", -1, NULL, NULL, NULL);

    gtk_label_set_markup(GTK_LABEL(dstPortLabel), sUtf8);
    g_free(sUtf8);

    gtk_fixed_put(GTK_FIXED(zone), dstPortLabel, 637, 150);

    /* Label textView */
    if(flood_on == 0)
    {
        textViewLabel = gtk_label_new("Flood OFF");

        sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><big><b>Flood OFF</b></big></span>", -1, NULL, NULL, NULL);

        gtk_label_set_markup(GTK_LABEL(textViewLabel), sUtf8);
        g_free(sUtf8);

        gtk_fixed_put(GTK_FIXED(zone), textViewLabel, 30, 430);
    }


/****************************** Affiche tout les widgets de la fenêtre et FIN  *****************************************************/

    gtk_widget_show_all(mainWindow);

    gtk_main();

    return;
}


void createUDPThread(void)
{
    pthread_t udpThread;


    /*if(tcpActif == 1)
    {
        boxInAction();
        return;
    }*/

    if(pthread_create(&udpThread, NULL, (void*(*)(void*))udpFlood, NULL) == -1)
    {
        threadErrorDiag();
        printf("Erreur création du thread udp.\nErreur Numero %d\nErreur Message %s", errno, strerror(errno));
        exit(errno);
    }

    return;
}


void createTCPThread(void)
{
    pthread_t tcpThread;

    /*if(udpActif == 1)
    {
        boxInAction();
        return;
    }*/

    if(pthread_create(&tcpThread, NULL, (void*(*)(void*))tcpFlood, NULL) == -1)
    {
        threadErrorDiag();
        //printf("Erreur création du thread udp.\nErreur Numero %d\nErreur Message %s", errno, strerror(errno));
        //exit(errno);
    }

    return;
}














