#ifndef STATISTICSDIALOG_H
#define STATISTICSDIALOG_H

#include <QDialog>
#include <map>
#include <tuple>

namespace Ui {
class StatisticsDialog;
}

/**
 * @class StatisticsDialog
 * @author Mohamed Ilahi
 * @brief Dialogfenster zur Anzeige der Spielstatistiken.
 *
 * Diese Klasse stellt ein Fenster bereit, in dem die gesammelten
 * Statistiken aller gespielten Minesweeper-Partien angezeigt werden.
 * Für jede Kombination aus Spielfeldgröße und Minenanzahl werden
 * Informationen über gespielte, gewonnene und verlorene Spiele
 * sowie die beste erzielte Zeit dargestellt.
 */
class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt ein neues Statistikfenster.
     *
     * @param data Statistikdaten des Spiels.
     * @param parent Zeiger auf das übergeordnete Widget.
     */
    StatisticsDialog(
        std::map<QString, std::tuple<int,int,int,int>> data,
        QWidget *parent = nullptr);

    /**
     * @author Mohamed Ilahi
     * @brief Zerstört das Statistikfenster.
     */
    ~StatisticsDialog();

private:

    /// Vom Qt-Designer erzeugte Benutzeroberfläche.
    Ui::StatisticsDialog *ui;
};

#endif // STATISTICSDIALOG_H
