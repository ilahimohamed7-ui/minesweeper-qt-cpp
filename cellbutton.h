#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

/**
 * @class CellButton
 * @author Mohamed Ilahi
 * @brief Spezialisierter Button zur Darstellung eines Spielfeldfeldes.
 *
 * Diese Klasse erweitert QPushButton um die Erkennung eines mittleren
 * Mausklicks. Sie wird für die Interaktion mit einzelnen Feldern des
 * Minesweeper-Spielfeldes verwendet.
 */
class CellButton : public QPushButton
{
    Q_OBJECT

public:

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt einen neuen CellButton.
     *
     * Konstruktor der Klasse CellButton.
     *
     * @param parent Zeiger auf das übergeordnete Widget.
     */
    explicit CellButton(QWidget *parent = nullptr);

signals:

    /**
     * @author Mohamed Ilahi
     * @brief Signal für einen mittleren Mausklick.
     *
     * Wird ausgelöst, wenn der Benutzer die mittlere Maustaste
     * auf dem Button betätigt.
     */
    void middleClicked();

protected:

    /**
     * @author Mohamed Ilahi
     * @brief Verarbeitet Mausklick-Ereignisse.
     *
     * Überschreibt die Standardimplementierung von QPushButton,
     * um zusätzlich mittlere Mausklicks zu erkennen und das
     * entsprechende Signal auszulösen.
     *
     * @param event Zeiger auf das ausgelöste Mausereignis.
     *
     * @return Kein Rückgabewert.
     *
     * @note Kann das Signal middleClicked() auslösen.
     */
    void mousePressEvent(QMouseEvent *event) override;
};

#endif
