#include "../include/headers.h"
#include "../include/prototypes.h"
#include "../include/callback.h"


extern GtkWidget *mainWindow;
extern const char *srcIP;
extern const char *srcPort;

const char *dstIP = NULL;
const char *dstPort = NULL;

extern GtkWidget* textViewLabel;
//gchar *sUtf8;
extern GtkWidget *zone;

extern int flood_on;

void getSrcIP(GtkWidget *pButton, gpointer data)
{
    /* Recuperation de l'IP source */
    srcIP = gtk_entry_get_text(GTK_ENTRY(data));

    if(strlen(srcIP) < 7)
        warningDiag();

    printf("srcIP = %s\n", srcIP);

    (void)pButton;
}

void getSrcPort(GtkWidget *pButton, gpointer data)
{
    /* Recuperation du port source*/

    srcPort = gtk_entry_get_text(GTK_ENTRY(data));

    printf("srcPort = %s\n", srcPort);

    (void)pButton;
}

void getDstIP(GtkWidget *pButton, gpointer data)
{
    /* Recuperation de l'IP de destination*/
    dstIP = gtk_entry_get_text(GTK_ENTRY(data));

    /*
    if(strlen(srcIP) < 7)
        warningDiag();
    */

    printf("DstIP = %s\n", dstIP);

    (void)pButton;
}

void getDstPort(GtkWidget *pButton, gpointer data)
{
    /* Recuperation du port de destination*/

    dstPort = gtk_entry_get_text(GTK_ENTRY(data));

    printf("DstPort = %s\n", dstPort);

    (void)pButton;
}


void boxInAction(void)
{
    GtkWidget* activeBox;

    activeBox = gtk_dialog_new_with_buttons("Already Flooding", GTK_WINDOW(mainWindow), GTK_DIALOG_MODAL,
                                        GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);

    gtk_widget_set_size_request(activeBox, 250, 50);

    switch (gtk_dialog_run(GTK_DIALOG(activeBox)))
    {
        case GTK_RESPONSE_CLOSE : gtk_widget_destroy(activeBox); break;

        default : break;
    }
}



void msgBox()
{
    GtkWidget* pBoite;

    if(((srcPort == NULL && srcIP == NULL) && (dstPort == NULL && dstIP == NULL))
       || ((srcPort == NULL || srcIP == NULL) || (dstPort == NULL || dstIP == NULL)))
    {
        pBoite = gtk_dialog_new_with_buttons("IP et Port manquant", GTK_WINDOW(mainWindow), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
        gtk_widget_set_size_request(pBoite, 250, 50);

        switch (gtk_dialog_run(GTK_DIALOG(pBoite)))
        {
            case GTK_RESPONSE_OK : gtk_widget_destroy(pBoite); break;

            default : gtk_widget_destroy(pBoite); break;
        }
    }

    return;
}

void startUDPFlooding(void)
{
    GtkWidget* floodDiag;
    gchar *sUtf8;

    if(((srcPort != NULL && srcIP != NULL) && (dstPort != NULL && dstIP != NULL))
       || ((srcPort != NULL || srcIP != NULL) || (dstPort != NULL || dstIP != NULL)))
    {
        floodDiag = gtk_dialog_new_with_buttons("Start UDP flooding", GTK_WINDOW(mainWindow), GTK_DIALOG_MODAL,
                                            GTK_STOCK_OK, GTK_RESPONSE_OK,GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_widget_set_size_request(floodDiag, 250, 50);

        switch (gtk_dialog_run(GTK_DIALOG(floodDiag)))
        {
            case GTK_RESPONSE_OK :

                gtk_widget_destroy(floodDiag);

                createUDPThread();

                flood_on = 1;

                sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><big><b>Flood ON</b></big></span>", -1, NULL, NULL, NULL);

                gtk_label_set_markup(GTK_LABEL(textViewLabel), sUtf8);
                g_free(sUtf8);

                gtk_fixed_put(GTK_FIXED(zone), textViewLabel, 30, 430);

                break;

            case GTK_RESPONSE_CANCEL : gtk_widget_destroy(floodDiag); break;

            default : break;
        }
    }
    return;
}

void startTCPFlooding(void)
{
    GtkWidget* floodDiag;
    gchar *sUtf8;

    if(((srcPort != NULL && srcIP != NULL) && (dstPort != NULL && dstIP != NULL))
       || ((srcPort != NULL || srcIP != NULL) || (dstPort != NULL || dstIP != NULL)))
    {
        floodDiag = gtk_dialog_new_with_buttons("Start TCP flooding", GTK_WINDOW(mainWindow), GTK_DIALOG_MODAL,
                                            GTK_STOCK_OK, GTK_RESPONSE_OK,GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
        gtk_widget_set_size_request(floodDiag, 250, 50);

        switch (gtk_dialog_run(GTK_DIALOG(floodDiag)))
        {
            case GTK_RESPONSE_OK :

                gtk_widget_destroy(floodDiag);

                createTCPThread();

                flood_on = 1;

                sUtf8 = g_locale_to_utf8("<span face=\"Courier New\"><big><b>Flood ON</b></big></span>", -1, NULL, NULL, NULL);

                gtk_label_set_markup(GTK_LABEL(textViewLabel), sUtf8);
                g_free(sUtf8);

                gtk_fixed_put(GTK_FIXED(zone), textViewLabel, 30, 430);

                break;

            case GTK_RESPONSE_CANCEL : gtk_widget_destroy(floodDiag); break;

            default : break;
        }
    }

    return;

}

void warningDiag(void)
{
    GtkWidget* warningBox;

    warningBox = gtk_dialog_new_with_buttons("IP Non Valide", GTK_WINDOW(mainWindow), GTK_DIALOG_MODAL,
                                        GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);

    gtk_widget_set_size_request(warningBox, 250, 50);

    switch (gtk_dialog_run(GTK_DIALOG(warningBox)))
    {
        case GTK_RESPONSE_CLOSE : gtk_widget_destroy(warningBox); break;

        default : break;
    }
    return;
}

_Noreturn void threadErrorDiag(void)
{
    GtkWidget* threadErrorBox;

    threadErrorBox = gtk_message_dialog_new(GTK_WINDOW(mainWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                                                    "Thread can't be created.\nError NUmber : %d\nError Message : %s", errno, strerror(errno));

    gtk_widget_set_size_request(threadErrorBox, 650, 250);

    switch(gtk_dialog_run(GTK_DIALOG(threadErrorBox)))
    {
        case  GTK_BUTTONS_OK : gtk_widget_destroy(threadErrorBox); exit(1);

        default : gtk_widget_destroy(threadErrorBox); exit(1);
    }

    //gtk_widget_destroy(threadErrorBox);

}

void quit(GtkWidget *pButton, gpointer data)
{
    gtk_main_quit();

    (void)pButton;
    (void)data;
}





