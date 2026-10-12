#include "cellbutton.h"

/**
 * @author Mohamed Ilahi
 * @brief Erstellt einen neuen CellButton.
 *
 * Konstruktor der Klasse CellButton. Der Button repräsentiert
 * ein einzelnes Feld des Minesweeper-Spielfeldes.
 *
 * @param parent Zeiger auf das übergeordnete Widget.
 */
CellButton::CellButton(QWidget *parent)
    : QPushButton(parent)
{
}

/**
 * @author Mohamed Ilahi
 * @brief Verarbeitet Mausklick-Ereignisse auf dem Button.
 *
 * Erkennt insbesondere Klicks mit der mittleren Maustaste und
 * löst in diesem Fall das Signal middleClicked() aus.
 * Alle anderen Mausklicks werden an die Standardimplementierung
 * von QPushButton weitergeleitet.
 *
 * @param event Zeiger auf das ausgelöste Mausereignis.
 *
 * @return Kein Rückgabewert.
 *
 * @note Kann das Signal middleClicked() auslösen und dadurch
 *       den Zustand des Spiels beeinflussen.
 */
void CellButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
    {
        emit middleClicked();
        return;
    }

    QPushButton::mousePressEvent(event);
}
