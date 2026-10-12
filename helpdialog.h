#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class HelpDialog;
}

/**
 * @class HelpDialog
 * @author Mohamed Ilahi
 * @brief Dialogfenster zur Anzeige der Spielhilfe.
 *
 * Diese Klasse stellt ein Hilfefenster für das Minesweeper-Spiel bereit.
 * Das Fenster informiert den Benutzer über die Bedienung des Spiels,
 * insbesondere über die Funktionen der verschiedenen Maustasten und
 * weitere wichtige Spielregeln.
 */
class HelpDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt ein neues Hilfefenster.
     *
     * Konstruktor der Klasse HelpDialog.
     *
     * @param parent Zeiger auf das übergeordnete Widget.
     */
    explicit HelpDialog(QWidget *parent = nullptr);

    /**
     * @author Mohamed Ilahi
     * @brief Zerstört das Hilfefenster.
     */
    ~HelpDialog();

private:

    /// Von Qt Designer erzeugte Benutzeroberfläche.
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_H
