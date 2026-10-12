#include "cell.h"

/**
 * @author Mohamed Ilahi
 * @brief Erstellt eine neue Spielfeldzelle.
 *
 * Initialisiert alle Attribute der Zelle mit ihren Standardwerten.
 * Eine neu erzeugte Zelle enthält keine Mine, ist weder aufgedeckt
 * noch markiert und besitzt keine benachbarten Minen.
 *
 * @return Kein Rückgabewert.
 *
 * @note Der Zustand der Zelle entspricht einem vollständig
 *       verdeckten und unverminten Feld.
 */
Cell::Cell()
{
    hasMine = false;
    revealed = false;
    flagged = false;
    exploded = false;

    neighboringMines = 0;
}
