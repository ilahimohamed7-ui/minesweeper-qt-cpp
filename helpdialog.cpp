#include "helpdialog.h"
#include "ui_helpdialog.h"

/**
 * @author Mohamed Ilahi
 * @brief Erstellt das Hilfefenster des Minesweeper-Spiels.
 *
 * Der Dialog informiert den Benutzer über die Bedienung des Spiels,
 * insbesondere über die Funktionen der verschiedenen Maustasten
 * sowie das Spielziel.
 *
 * @param parent Zeiger auf das übergeordnete Widget.
 */
HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);

    setWindowTitle("Hilfe");

    setStyleSheet(
        "QDialog {"
        "  background-color: #f0ede8;"
        "}"
        "QLabel {"
        "  font-family: 'Segoe UI';"
        "  font-size: 12px;"
        "  color: #2c2c2a;"
        "}"
        );

    ui->lblHelp->setWordWrap(true);

    resize(320, 220);
}

/**
 * @author Mohamed Ilahi
 * @brief Zerstört das Hilfefenster.
 */
HelpDialog::~HelpDialog()
{
    delete ui;
}
