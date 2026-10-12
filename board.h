#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"

/**
 * @class Board
 * @author Mohamed Ilahi
 * @brief Verwaltet das gesamte Spielfeld des Minesweeper-Spiels.
 *
 * Diese Klasse speichert die Größe des Spielfeldes, die Anzahl der Minen
 * sowie alle enthaltenen Zellen. Sie stellt Funktionen zur Erzeugung der
 * Minen, Berechnung der Nachbarzahlen und Verwaltung des Spielzustands bereit.
 */
class Board
{
private:
    /// Anzahl der Zeilen des Spielfeldes.
    int rows;

    /// Anzahl der Spalten des Spielfeldes.
    int cols;

    /// Gesamtanzahl der Minen im Spielfeld.
    int mineCount;

    /// Zweidimensionaler Vektor zur Speicherung aller Spielfeldzellen.
    std::vector<std::vector<Cell>> grid;

public:

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt ein neues Spielfeld.
     *
     * Initialisiert ein Spielfeld mit der angegebenen Größe und Anzahl
     * an Minen.
     *
     * @param r Anzahl der Zeilen.
     * @param c Anzahl der Spalten.
     * @param m Anzahl der Minen.
     */
    Board(int r, int c, int m);

    /**
     * @author Mohamed Ilahi
     * @brief Verteilt die Minen zufällig auf dem Spielfeld.
     *
     * Die Minen werden auf zufälligen Feldern platziert.
     *
     * @return Kein Rückgabewert.
     */
    void generateMines();

    /**
     * @author Mohamed Ilahi
     * @brief Berechnet die Anzahl benachbarter Minen für jede Zelle.
     *
     * Für jedes Feld wird bestimmt, wie viele Minen sich in den
     * angrenzenden Feldern befinden.
     *
     * @return Kein Rückgabewert.
     */
    void calculateNumbers();

    /**
     * @author Mohamed Ilahi
     * @brief Deckt ein Feld auf.
     *
     * Deckt das angegebene Feld auf. Falls keine benachbarten Minen
     * vorhanden sind, werden angrenzende Felder rekursiv aufgedeckt.
     *
     * @param r Zeilenindex des Feldes.
     * @param c Spaltenindex des Feldes.
     *
     * @return Kein Rückgabewert.
     *
     * @note Verändert den Zustand des Spielfeldes.
     */
    void reveal(int r, int c);

    /**
     * @author Mohamed Ilahi
     * @brief Deckt alle Felder des Spielfeldes auf.
     *
     * Wird beispielsweise bei Spielende verwendet.
     *
     * @return Kein Rückgabewert.
     */
    void revealAll();

    /**
     * @author Mohamed Ilahi
     * @brief Setzt oder entfernt eine Markierung auf einem Feld.
     *
     * Ist das Feld bereits markiert, wird die Markierung entfernt.
     * Andernfalls wird eine neue Markierung gesetzt.
     *
     * @param r Zeilenindex des Feldes.
     * @param c Spaltenindex des Feldes.
     *
     * @return Kein Rückgabewert.
     *
     * @note Verändert den Zustand der ausgewählten Zelle.
     */
    void toggleFlag(int r, int c);

    /**
     * @author Mohamed Ilahi
     * @brief Prüft, ob alle Minen korrekt markiert wurden.
     *
     * @return true, wenn alle Minen korrekt markiert wurden,
     *         sonst false.
     */
    bool allMinesCorrectlyFlagged() const;

    /**
     * @author Mohamed Ilahi
     * @brief Prüft, ob alle Felder bearbeitet wurden.
     *
     * Ein Feld gilt als bearbeitet, wenn es entweder aufgedeckt
     * oder markiert wurde.
     *
     * @return true, wenn alle Felder bearbeitet wurden,
     *         sonst false.
     */
    bool allCellsProcessed() const;

    /**
     * @author Mohamed Ilahi
     * @brief Liefert eine Zelle des Spielfeldes zurück.
     *
     * @param r Zeilenindex der gewünschten Zelle.
     * @param c Spaltenindex der gewünschten Zelle.
     *
     * @return Konstante Referenz auf die angeforderte Zelle.
     */
    const Cell& getCell(int r, int c) const;
};

#endif // BOARD_H
