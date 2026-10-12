#include "statisticsdialog.h"
#include "ui_statisticsdialog.h"

#include <QHeaderView>
#include <QTableWidgetItem>

/**
 * @author Mohamed Ilahi
 * @brief Erstellt das Statistikfenster des Minesweeper-Spiels.
 *
 * Der Dialog zeigt alle bisher gespeicherten Spielstatistiken
 * in tabellarischer Form an. Für jede Spielfeldkonfiguration
 * werden die Anzahl gespielter Spiele, gewonnener Spiele,
 * verlorener Spiele sowie die beste erreichte Zeit dargestellt.
 *
 * @param data Statistikdaten des Spiels.
 *             Der Schlüssel enthält die Spielfeldkonfiguration.
 *             Die Werte enthalten:
 *             - Anzahl gespielter Spiele
 *             - Anzahl gewonnener Spiele
 *             - Anzahl verlorener Spiele
 *             - Beste Gewinnzeit
 *
 * @param parent Zeiger auf das übergeordnete Widget.
 */
StatisticsDialog::StatisticsDialog(
    std::map<QString, std::tuple<int,int,int,int>> data,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::StatisticsDialog)
{
    ui->setupUi(this);

    // Fenstertitel festlegen.
    setWindowTitle("Statistik");

    // Tabelle auf fünf Spalten konfigurieren.
    ui->tableStats->setColumnCount(5);

    // Spaltenüberschriften setzen.
    ui->tableStats->setHorizontalHeaderLabels(
        {
            "Konfiguration",
            "Gespielt",
            "Gewonnen",
            "Verloren",
            "Beste Zeit"
        });

    // Anzahl der Zeilen entsprechend der Statistikdaten festlegen.
    ui->tableStats->setRowCount(data.size());

    int row = 0;

    // Alle Statistikdaten in die Tabelle eintragen.
    for (auto &d : data)
    {
        // Spielfeldkonfiguration anzeigen.
        ui->tableStats->setItem(
            row,
            0,
            new QTableWidgetItem(d.first));

        // Anzahl gespielter Spiele anzeigen.
        ui->tableStats->setItem(
            row,
            1,
            new QTableWidgetItem(
                QString::number(std::get<0>(d.second))));

        // Anzahl gewonnener Spiele anzeigen.
        ui->tableStats->setItem(
            row,
            2,
            new QTableWidgetItem(
                QString::number(std::get<1>(d.second))));

        // Anzahl verlorener Spiele anzeigen.
        ui->tableStats->setItem(
            row,
            3,
            new QTableWidgetItem(
                QString::number(std::get<2>(d.second))));

        // Beste Gewinnzeit auslesen.
        int bestTime = std::get<3>(d.second);

        if (bestTime == -1)
        {
            // Noch kein gewonnenes Spiel vorhanden.
            ui->tableStats->setItem(
                row,
                4,
                new QTableWidgetItem("-"));
        }
        else
        {
            // Beste Gewinnzeit anzeigen.
            ui->tableStats->setItem(
                row,
                4,
                new QTableWidgetItem(
                    QString::number(bestTime) + " s"));
        }

        row++;
    }

    // Spaltenbreiten automatisch anpassen.
    ui->tableStats->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    // Zeilennummern ausblenden.
    ui->tableStats->verticalHeader()->setVisible(false);

    // Bearbeiten der Zellen verhindern.
    ui->tableStats->setEditTriggers(
        QAbstractItemView::NoEditTriggers);

    // Auswahl von Tabellenzellen deaktivieren.
    ui->tableStats->setSelectionMode(
        QAbstractItemView::NoSelection);

    // Standardgröße des Fensters festlegen.
    resize(700, 300);
}

/**
 * @author Mohamed Ilahi
 * @brief Zerstört das Statistikfenster.
 *
 * Gibt die vom Qt-Designer erzeugte Benutzeroberfläche frei.
 */
StatisticsDialog::~StatisticsDialog()
{
    delete ui;
}
