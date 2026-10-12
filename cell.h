#ifndef CELL_H
#define CELL_H

/**
 * @class Cell
 * @author Mohamed Ilahi
 * @brief Repräsentiert ein einzelnes Feld des Minesweeper-Spielfeldes.
 *
 * Eine Zelle kann eine Mine enthalten, aufgedeckt oder markiert sein
 * sowie den Zustand einer explodierten Mine speichern. Zusätzlich wird
 * die Anzahl benachbarter Minen verwaltet.
 */
class Cell
{
public:

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt eine neue Zelle.
     *
     * Initialisiert alle Zustände der Zelle mit Standardwerten.
     *
     * @return Kein Rückgabewert.
     *
     * @note Nach der Initialisierung enthält die Zelle keine Mine,
     *       ist weder aufgedeckt noch markiert und besitzt keine
     *       benachbarten Minen.
     */
    Cell();

    /// Gibt an, ob die Zelle eine Mine enthält.
    bool hasMine;

    /// Gibt an, ob die Zelle bereits aufgedeckt wurde.
    bool revealed;

    /// Gibt an, ob die Zelle vom Spieler markiert wurde.
    bool flagged;

    /// Gibt an, ob die Mine dieser Zelle explodiert ist.
    bool exploded;

    /// Anzahl der benachbarten Minen.
    int neighboringMines;
};

#endif // CELL_H
