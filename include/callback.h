#ifndef CALLBACK_H_INCLUDED
#define CALLBACK_H_INCLUDED

void getSrcIP(GtkWidget *pButton, gpointer data);

void getSrcPort(GtkWidget *pButton, gpointer data);

void getDstIP(GtkWidget *pButton, gpointer data);

void getDstPort(GtkWidget *pButton, gpointer data);

void boxInAction(void);

void msgBox(void);

void startUDPFlooding(void);

void startTCPFlooding(void);

void warningDiag(void);

void threadErrorDiag(void);

void quit(GtkWidget *pButton, gpointer data);


#endif


