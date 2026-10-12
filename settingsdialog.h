#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

/**
 * @class SettingsDialog
 * @author Mohamed Ilahi
 * @brief Dialogfenster zur Konfiguration der Spieleinstellungen.
 *
 * Diese Klasse stellt ein Fenster bereit, in dem der Benutzer die
 * Größe des Spielfeldes sowie die Anzahl der Minen festlegen kann.
 * Die gewählten Werte werden direkt über Referenzen an die
 * Hauptanwendung zurückgegeben.
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt ein neues Einstellungsfenster.
     *
     * Der Dialog ermöglicht die Konfiguration der Anzahl von Zeilen,
     * Spalten und Minen für ein neues Spiel.
     *
     * @param r Referenz auf die Anzahl der Zeilen.
     * @param c Referenz auf die Anzahl der Spalten.
     * @param m Referenz auf die Anzahl der Minen.
     * @param parent Zeiger auf das übergeordnete Widget.
     */
    SettingsDialog(int &r, int &c, int &m, QWidget *parent = nullptr);

    /**
     * @author Mohamed Ilahi
     * @brief Zerstört das Einstellungsfenster.
     */
    ~SettingsDialog();

private:

    /// Von Qt Designer erzeugte Benutzeroberfläche.
    Ui::SettingsDialog *ui;

    /// Referenz auf die aktuelle Anzahl der Zeilen.
    int &rows;

    /// Referenz auf die aktuelle Anzahl der Spalten.
    int &cols;

    /// Referenz auf die aktuelle Anzahl der Minen.
    int &mines;
};

#endif // SETTINGSDIALOG_H
