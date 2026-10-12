#include "board.h"
#include <cstdlib>
#include <ctime>

/**
 * @author Mohamed Ilahi
 * @brief Erstellt ein neues Minesweeper-Spielfeld.
 *
 * Initialisiert die Spielfeldgröße, reserviert Speicher für alle
 * Zellen und erzeugt anschließend die Minenverteilung sowie die
 * Nachbarzahlen.
 *
 * @param r Anzahl der Zeilen.
 * @param c Anzahl der Spalten.
 * @param m Anzahl der Minen.
 *
 * @note Initialisiert den Zufallsgenerator für die Minenplatzierung.
 */
Board::Board(int r, int c, int m)
    : rows(r), cols(c), mineCount(m)
{
    grid.resize(rows, std::vector<Cell>(cols));

    std::srand(std::time(nullptr));

    generateMines();
    calculateNumbers();
}

/**
 * @author Mohamed Ilahi
 * @brief Verteilt die Minen zufällig auf dem Spielfeld.
 *
 * Solange noch nicht alle Minen gesetzt wurden, werden zufällige
 * Positionen ausgewählt und mit Minen belegt.
 *
 * @return Kein Rückgabewert.
 *
 * @note Verändert den Zustand des Spielfeldes.
 */
void Board::generateMines()
{
    int placed = 0;

    while (placed < mineCount)
    {
        int r = std::rand() % rows;
        int c = std::rand() % cols;

        if (!grid[r][c].hasMine)
        {
            grid[r][c].hasMine = true;
            placed++;
        }
    }
}

/**
 * @author Mohamed Ilahi
 * @brief Berechnet die Anzahl benachbarter Minen.
 *
 * Für jede nicht verminte Zelle wird ermittelt, wie viele Minen
 * sich in den angrenzenden Feldern befinden.
 *
 * @return Kein Rückgabewert.
 *
 * @note Speichert das Ergebnis in neighboringMines.
 */
void Board::calculateNumbers()
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c].hasMine)
            {
                grid[r][c].neighboringMines = -1;
                continue;
            }

            int count = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int nr = r + i;
                    int nc = c + j;

                    if (nr >= 0 && nr < rows &&
                        nc >= 0 && nc < cols &&
                        grid[nr][nc].hasMine)
                    {
                        count++;
                    }
                }
            }

            grid[r][c].neighboringMines = count;
        }
    }
}

/**
 * @author Mohamed Ilahi
 * @brief Deckt ein Feld auf.
 *
 * Das ausgewählte Feld wird aufgedeckt. Enthält das Feld eine Mine,
 * wird dieses als explodiert markiert. Besitzt das Feld keine
 * benachbarten Minen, werden die Nachbarfelder rekursiv ebenfalls
 * aufgedeckt.
 *
 * @param r Zeilenindex des Feldes.
 * @param c Spaltenindex des Feldes.
 *
 * @return Kein Rückgabewert.
 *
 * @note Verändert den Zustand mehrerer Zellen des Spielfeldes.
 */
void Board::reveal(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return;

    if (grid[r][c].revealed || grid[r][c].flagged)
        return;

    grid[r][c].revealed = true;

    if (grid[r][c].hasMine)
    {
        grid[r][c].exploded = true;
        return;
    }

    if (grid[r][c].neighboringMines == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    reveal(r + i, c + j);
                }
            }
        }
    }
}

/**
 * @author Mohamed Ilahi
 * @brief Deckt alle Felder des Spielfeldes auf.
 *
 * Diese Funktion wird insbesondere bei Spielende verwendet,
 * um den gesamten Spielfeldinhalt sichtbar zu machen.
 *
 * @return Kein Rückgabewert.
 */
void Board::revealAll()
{
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            grid[r][c].revealed = true;
        }
    }
}

/**
 * @author Mohamed Ilahi
 * @brief Setzt oder entfernt eine Markierung.
 *
 * Ist das Feld bereits markiert, wird die Markierung entfernt.
 * Andernfalls wird eine neue Markierung gesetzt.
 *
 * @param r Zeilenindex des Feldes.
 * @param c Spaltenindex des Feldes.
 *
 * @return Kein Rückgabewert.
 *
 * @note Bereits aufgedeckte Felder können nicht markiert werden.
 */
void Board::toggleFlag(int r, int c)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        return;

    if (grid[r][c].revealed)
        return;

    grid[r][c].flagged = !grid[r][c].flagged;
}

/**
 * @author Mohamed Ilahi
 * @brief Prüft, ob alle Felder bearbeitet wurden.
 *
 * Ein Feld gilt als bearbeitet, wenn es entweder aufgedeckt oder
 * markiert wurde.
 *
 * @return true, wenn alle Felder bearbeitet wurden,
 *         andernfalls false.
 */
bool Board::allCellsProcessed() const
{
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            const Cell& cell = grid[r][c];

            if(!cell.revealed && !cell.flagged)
                return false;
        }
    }

    return true;
}

/**
 * @author Mohamed Ilahi
 * @brief Prüft, ob alle Minen korrekt markiert wurden.
 *
 * Kontrolliert, ob jede Mine markiert wurde und keine
 * unverminten Felder fälschlicherweise markiert sind.
 *
 * @return true bei korrekter Markierung aller Minen,
 *         sonst false.
 */
bool Board::allMinesCorrectlyFlagged() const
{
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
        {
            const Cell& cell = grid[r][c];

            if(cell.hasMine && !cell.flagged)
                return false;

            if(!cell.hasMine && cell.flagged)
                return false;
        }
    }

    return true;
}

/**
 * @author Mohamed Ilahi
 * @brief Liefert eine bestimmte Zelle des Spielfeldes.
 *
 * @param r Zeilenindex der Zelle.
 * @param c Spaltenindex der Zelle.
 *
 * @return Konstante Referenz auf die angeforderte Zelle.
 */
const Cell& Board::getCell(int r, int c) const
{
    return grid[r][c];
}
