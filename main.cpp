#include "mainwindow.h"

#include <QApplication>

/**
 * @author Mohamed Ilahi
 * @brief Einstiegspunkt der Anwendung.
 *
 * Erstellt die Qt-Anwendung, erzeugt das Hauptfenster
 * und startet die Ereignisschleife.
 *
 * @param argc Anzahl der Kommandozeilenparameter.
 * @param argv Kommandozeilenparameter.
 *
 * @return Rückgabewert der Qt-Ereignisschleife.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
