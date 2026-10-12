#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include "board.h"
#include "cellbutton.h"
#include <map>
#include <tuple>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @author Mohamed Ilahi
 * @brief Hauptfenster des Minesweeper-Spiels.
 *
 * Diese Klasse verwaltet die grafische Benutzeroberfläche des Spiels.
 * Sie verbindet die Spiellogik mit den Qt-Komponenten und stellt die
 * Funktionen zum Starten, Pausieren und Beenden eines Spiels bereit.
 * Außerdem werden die Spielstatistiken, die Statusanzeige sowie die
 * Menüfunktionen für Einstellungen, Hilfe und Statistik verwaltet.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt das Hauptfenster des Spiels.
     *
     * Initialisiert die Benutzeroberfläche und bereitet alle
     * Komponenten für das Spiel vor.
     *
     * @param parent Zeiger auf das übergeordnete Widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @author Mohamed Ilahi
     * @brief Zerstört das Hauptfenster.
     *
     * Gibt alle reservierten Ressourcen frei.
     */
    ~MainWindow();

private slots:

    /**
     * @author Mohamed Ilahi
     * @brief Startet ein neues Spiel.
     *
     * Erstellt ein neues Spielfeld, setzt alle Statuswerte zurück
     * und startet den Spieltimer neu.
     */
    void newGame();

    /**
     * @author Mohamed Ilahi
     * @brief Pausiert oder setzt das aktuelle Spiel fort.
     *
     * Während der Pause wird das Spielfeld ausgeblendet und der
     * Spieltimer angehalten.
     */
    void pauseGame();

    /**
     * @author Mohamed Ilahi
     * @brief Beendet das aktuelle Spiel.
     *
     * Alle Felder werden aufgedeckt und das Spiel wird als verloren
     * gewertet.
     */
    void endGame();

    /**
     * @author Mohamed Ilahi
     * @brief Aktualisiert die Spielzeit.
     *
     * Wird regelmäßig vom Timer aufgerufen und erhöht die
     * vergangene Spielzeit.
     */
    void updateTimer();

    /**
     * @author Mohamed Ilahi
     * @brief Öffnet das Einstellungsfenster.
     *
     * Ermöglicht die Konfiguration von Spielfeldgröße und Minenanzahl.
     */
    void openSettings();

    /**
     * @author Mohamed Ilahi
     * @brief Öffnet das Statistikfenster.
     *
     * Zeigt die bisher gespeicherten Spielstatistiken an.
     */
    void openStats();

    /**
     * @author Mohamed Ilahi
     * @brief Öffnet das Hilfefenster.
     *
     * Zeigt Informationen zur Bedienung des Spiels an.
     */
    void openHelp();

private:

    /// Vom Qt-Designer erzeugte Benutzeroberfläche.
    Ui::MainWindow *ui;

    /// Spielfeldobjekt mit allen Spielinformationen.
    Board* board = nullptr;

    /// Anzahl der Zeilen des Spielfeldes.
    int rows = 10;

    /// Anzahl der Spalten des Spielfeldes.
    int cols = 10;

    /// Anzahl der Minen.
    int mines = 10;

    /// Gibt an, ob das Spiel pausiert ist.
    bool paused = false;

    /// Gibt an, ob das Spiel beendet wurde.
    bool gameOver = false;

    /// Verhindert mehrfaches Speichern derselben Statistik.
    bool statisticsSaved = false;

    /// Vergangene Spielzeit in Sekunden.
    int seconds = 0;

    /// Anzahl aktuell gesetzter Markierungen.
    int flagCount = 0;

    /// Speichert, ob das Spiel gewonnen wurde.
    bool won = false;

    /**
     * Speichert die Spielstatistiken.
     *
     * Schlüssel:
     * Kombination aus Spielfeldgröße und Minenanzahl.
     *
     * Werte:
     * - gespielte Spiele
     * - gewonnene Spiele
     * - verlorene Spiele
     * - beste Zeit
     */
    std::map<QString, std::tuple<int,int,int,int>> statistics;

    /// Timer zur Messung der Spielzeit.
    QTimer* timer = nullptr;

    /// Container für das Spielfeld.
    QWidget* container = nullptr;

    /// Layout zur Anordnung der Spielfeldfelder.
    QGridLayout* gridLayout = nullptr;

    /// Zweidimensionales Feld mit den Spielfeldbuttons.
    CellButton*** buttons = nullptr;

    /// Tatsächlich reservierte Zeilenanzahl des Button-Arrays.
    int allocatedRows = 0;

    /// Tatsächlich reservierte Spaltenanzahl des Button-Arrays.
    int allocatedCols = 0;

    /// Anzeige der Gesamtanzahl an Minen.
    QLabel* lblMines = nullptr;

    /// Anzeige der gesetzten Markierungen.
    QLabel* lblFlags = nullptr;

    /// Anzeige der vergangenen Spielzeit.
    QLabel* lblTime = nullptr;

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt die grafische Benutzeroberfläche.
     *
     * Initialisiert alle Widgets, Layouts und Verbindungen.
     */
    void setupUI();

    /**
     * @author Mohamed Ilahi
     * @brief Erstellt das Spielfeld neu.
     *
     * Baut die Spielfeldanzeige anhand der aktuellen Einstellungen
     * vollständig neu auf.
     */
    void rebuildBoard();

    /**
     * @author Mohamed Ilahi
     * @brief Aktualisiert die Darstellung des Spielfeldes.
     *
     * Synchronisiert die grafische Anzeige mit dem aktuellen
     * Zustand des Spielfeldes.
     */
    void updateUI();

    /**
     * @author Mohamed Ilahi
     * @brief Aktualisiert die Statusanzeige.
     *
     * Zeigt aktuelle Werte für Minen, Markierungen und Zeit an.
     */
    void refreshStatus();

    /**
     * @author Mohamed Ilahi
     * @brief Aktualisiert die Spielstatistik.
     *
     * Speichert Ergebnisse abgeschlossener Spiele und aktualisiert
     * die Statistikdaten.
     */
    void updateStatistics();
};

#endif // MAINWINDOW_H
