#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QPushButton>
#include <QSpinBox>

/**
 * @author Mohamed Ilahi
 * @brief Erstellt das Einstellungsfenster des Minesweeper-Spiels.
 *
 * Der Dialog ermöglicht die Konfiguration der Spielfeldgröße
 * (Zeilen und Spalten) sowie der Anzahl der Minen.
 *
 * @param r Referenz auf die Anzahl der Zeilen.
 * @param c Referenz auf die Anzahl der Spalten.
 * @param m Referenz auf die Anzahl der Minen.
 * @param parent Zeiger auf das übergeordnete Widget.
 */
SettingsDialog::SettingsDialog(int &r, int &c, int &m, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::SettingsDialog),
    rows(r),
    cols(c),
    mines(m)
{
    ui->setupUi(this);

    ui->btnCancel->setStyleSheet(
        "QPushButton {"
        "  background-color: #e8e5df;"
        "  color: #2c2c2a;"
        "  border: 1px solid #b4b2a9;"
        "  border-radius: 4px;"
        "  padding: 5px 18px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #fae8e8;"
        "  color: #a03020;"
        "  border-color: #cc2200;"
        "}"
        );

    ui->btnOk->setStyleSheet(
        "QPushButton {"
        "  background-color: #185fa5;"
        "  color: #e6f1fb;"
        "  border: 1px solid #0c447c;"
        "  border-radius: 4px;"
        "  padding: 5px 18px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: #0c447c;"
        "}"
        );

    // Fenstereigenschaften
    setWindowTitle("Einstellungen");
    setFixedWidth(280);
    setModal(true);

    // Gestaltung des Dialogfensters
    setStyleSheet(
        "QDialog {"
        "  background-color: #f0ede8;"
        "}"
        "QGroupBox {"
        "  font-family: 'Segoe UI', sans-serif;"
        "  font-size: 12px;"
        "  font-weight: bold;"
        "  color: #2c2c2a;"
        "  border: 1px solid #b4b2a9;"
        "  border-radius: 6px;"
        "  margin-top: 10px;"
        "  padding-top: 6px;"
        "}"
        "QGroupBox::title {"
        "  subcontrol-origin: margin;"
        "  subcontrol-position: top left;"
        "  padding: 0 6px;"
        "  left: 10px;"
        "}"
        "QLabel {"
        "  font-family: 'Segoe UI', sans-serif;"
        "  font-size: 12px;"
        "  color: #2c2c2a;"
        "}"
        "QSpinBox {"
        "  font-family: 'Courier New', monospace;"
        "  font-size: 12px;"
        "  font-weight: bold;"
        "  background-color: #ffffff;"
        "  border: 1px solid #b4b2a9;"
        "  border-radius: 4px;"
        "  padding: 3px 6px;"
        "  min-width: 64px;"
        "  color: #1a1a1a;"
        "}"
        "QSpinBox:focus {"
        "  border: 1px solid #185fa5;"
        "}"
        "QPushButton {"
        "  font-family: 'Segoe UI', sans-serif;"
        "  font-size: 12px;"
        "  border-radius: 4px;"
        "  padding: 5px 18px;"
        "  border: 1px solid #b4b2a9;"
        "}"
        );

    // Aktuelle Werte übernehmen
    ui->sbRows->setRange(2, 30);
    ui->sbCols->setRange(2, 50);

    ui->sbRows->setValue(rows);
    ui->sbCols->setValue(cols);

    ui->sbMines->setRange(1, rows * cols - 1);
    ui->sbMines->setValue(mines);

    // Maximale Minenanzahl automatisch anpassen
    auto updateMineLimit = [=]()
    {
        int maxMines = ui->sbRows->value() * ui->sbCols->value() - 1;

        ui->sbMines->setMaximum(maxMines);

        if (ui->sbMines->value() > maxMines)
            ui->sbMines->setValue(maxMines);
    };

    connect(ui->sbRows,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            updateMineLimit);

    connect(ui->sbCols,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            updateMineLimit);

    // Abbrechen
    connect(ui->btnCancel,
            &QPushButton::clicked,
            this,
            &QDialog::reject);

    // Einstellungen übernehmen
    connect(ui->btnOk,
            &QPushButton::clicked,
            this,
            [=]()
            {
                rows  = ui->sbRows->value();
                cols  = ui->sbCols->value();
                mines = ui->sbMines->value();

                accept();
            });
}

/**
 * @author Mohamed Ilahi
 * @brief Zerstört das Einstellungsfenster.
 */
SettingsDialog::~SettingsDialog()
{
    delete ui;
}
