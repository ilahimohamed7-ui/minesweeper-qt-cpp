#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenuBar>
#include <QStatusBar>
#include "settingsdialog.h"
#include "statisticsdialog.h"
#include "helpdialog.h"
#include <map>
#include <tuple>
#include <QMessageBox>
/**
 * @author Mohamed Ilahi
 * @brief Erstellt das Hauptfenster des Minesweeper-Spiels.
 *
 * Initialisiert die vom Qt-Designer erzeugte Benutzeroberfläche,
 * richtet alle grafischen Komponenten ein, erstellt den Spieltimer
 * und startet ein neues Spiel.
 *
 * @param parent Zeiger auf das übergeordnete Widget.
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupUI();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);

    newGame();
}

/**
 * @author Mohamed Ilahi
 * @brief Zerstört das Hauptfenster.
 *
 * Gibt alle dynamisch reservierten Ressourcen frei.
 */
MainWindow::~MainWindow()
{
    delete ui;
    if (board) delete board;
}

/**
 * @author Mohamed Ilahi
 * @brief Initialisiert die grafische Benutzeroberfläche.
 *
 * Erstellt Layouts, konfiguriert das Erscheinungsbild der Widgets,
 * verbindet Signale mit Slots und initialisiert die Statusanzeige.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::setupUI()
{
    gridLayout = new QGridLayout(ui->widget);
    gridLayout->setSpacing(2);
    gridLayout->setContentsMargins(4, 4, 4, 4);
    ui->widget->setLayout(gridLayout);

    // Spielfeld-Widget bekommt einen eingerahmten Hintergrund
    ui->widget->setStyleSheet(
        "QWidget {"
        "  background-color: #c0c0c0;"
        "  border: 2px inset #808080;"
        "}"
        );

    // Buttons stylen
    ui->btnNeu->setStyleSheet(
        "QPushButton {"
        "  background-color: #e8e8e8;"
        "  border: 1px solid #999;"
        "  border-radius: 4px;"
        "  padding: 4px 14px;"
        "  font-weight: bold;"
        "  color: #1a5fa8;"
        "}"
        "QPushButton:hover  { background-color: #d0e4f7; }"
        "QPushButton:pressed{ background-color: #b0ccec; }"
        );

    ui->btnPause->setStyleSheet(
        "QPushButton {"
        "  background-color: #e8e8e8;"
        "  border: 1px solid #999;"
        "  border-radius: 4px;"
        "  padding: 4px 14px;"
        "  font-weight: bold;"
        "  color: #a06010;"
        "}"
        "QPushButton:hover  { background-color: #faeedd; }"
        "QPushButton:pressed{ background-color: #f5d9a0; }"
        );

    ui->btnBeenden->setStyleSheet(
        "QPushButton {"
        "  background-color: #e8e8e8;"
        "  border: 1px solid #999;"
        "  border-radius: 4px;"
        "  padding: 4px 14px;"
        "  font-weight: bold;"
        "  color: #a03020;"
        "}"
        "QPushButton:hover  { background-color: #fae8e8; }"
        "QPushButton:pressed{ background-color: #f5b0b0; }"
        );

    // Status-Labels stylen
    QString statusLabelStyle =
        "QLabel {"
        "  font-family: 'Courier New', monospace;"
        "  font-size: 12px;"
        "  font-weight: bold;"
        "  background-color: #1a1a1a;"
        "  color: #ff4444;"
        "  border: 1px inset #555;"
        "  border-radius: 2px;"
        "  padding: 2px 8px;"
        "  min-width: 90px;"
        "}";

    // Menüleiste stylen
    menuBar()->setStyleSheet(
        "QMenuBar {"
        "  background-color: #2c2c2a;"
        "  color: #d3d1c7;"
        "  font-family: 'Segoe UI', sans-serif;"
        "  font-size: 12px;"
        "  padding: 2px 4px;"
        "  border-bottom: 1px solid #444441;"
        "}"
        "QMenuBar::item {"
        "  background: transparent;"
        "  padding: 4px 12px;"
        "  border-radius: 3px;"
        "}"
        "QMenuBar::item:selected {"
        "  background-color: #185fa5;"
        "  color: #e6f1fb;"
        "}"
        "QMenuBar::item:pressed {"
        "  background-color: #0c447c;"
        "  color: #e6f1fb;"
        "}"
        "QMenu {"
        "  background-color: #444441;"
        "  color: #d3d1c7;"
        "  border: 1px solid #5f5e5a;"
        "  font-size: 12px;"
        "}"
        "QMenu::item {"
        "  padding: 6px 24px 6px 16px;"
        "}"
        "QMenu::item:selected {"
        "  background-color: #185fa5;"
        "  color: #e6f1fb;"
        "}"
        "QMenu::separator {"
        "  height: 1px;"
        "  background: #5f5e5a;"
        "  margin: 3px 8px;"
        "}"
        );

    ui->lblMinen->setStyleSheet(statusLabelStyle);
    ui->lblMarken->setStyleSheet(statusLabelStyle);
    ui->lblZeit->setStyleSheet(statusLabelStyle);

    // Verbindungen
    connect(ui->btnNeu,    &QPushButton::clicked, this, &MainWindow::newGame);
    connect(ui->btnPause,  &QPushButton::clicked, this, &MainWindow::pauseGame);
    connect(ui->btnBeenden,&QPushButton::clicked, this, &MainWindow::endGame);

    connect(ui->actionEinstellungen, &QAction::triggered, this, &MainWindow::openSettings);
    connect(ui->actionStatistik,     &QAction::triggered, this, &MainWindow::openStats);
    connect(ui->actionHilfe,         &QAction::triggered, this, &MainWindow::openHelp);

    container = ui->widget;
    lblMines  = ui->lblMinen;
    lblFlags  = ui->lblMarken;
    lblTime   = ui->lblZeit;
}
/**
 * @author Mohamed Ilahi
 * @brief Startet ein neues Spiel.
 *
 * Erstellt ein neues Spielfeld mit den aktuellen Einstellungen,
 * setzt alle Spielwerte zurück und startet den Spieltimer.
 *
 * @return Kein Rückgabewert.
 */

void MainWindow::newGame()
{
    if (board) delete board;

    board = new Board(rows, cols, mines);

    seconds   = 0;
    paused    = false;
    gameOver  = false;
    flagCount = 0;
    won       = false;
    statisticsSaved = false;

    timer->start(1000);

    rebuildBoard();
    refreshStatus();
}
/**
 * @author Mohamed Ilahi
 * @brief Erstellt die Spielfeldanzeige neu.
 *
 * Entfernt vorhandene Buttons und erzeugt für jede Zelle des
 * Spielfeldes einen neuen Button inklusive aller notwendigen
 * Signal-Slot-Verbindungen.
 *
 * @return Kein Rückgabewert.
 *
 * @note Verändert die gesamte Darstellung des Spielfeldes.
 */
void MainWindow::rebuildBoard()
{
    // Altes Spielfeld leeren
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)))
    {
        delete item->widget();
        delete item;
    }

    if (buttons)
    {
        for (int r = 0; r < allocatedRows; r++)
            delete[] buttons[r];

        delete[] buttons;
    }

    buttons = new CellButton**[rows];

    for (int r = 0; r < rows; r++)
    {
        buttons[r] = new CellButton*[cols];

        for (int c = 0; c < cols; c++)
        {
            CellButton* btn = new CellButton();
            btn->setFixedSize(28, 28);
            btn->setFont(QFont("Courier New", 9, QFont::Bold));

            // Verdeckter Zustand — Standard
            btn->setStyleSheet(
                "QPushButton {"
                "  background-color: #b4b2a9;"
                "  border: 1px solid #888780;"
                "  border-radius: 2px;"
                "  font-weight: bold;"
                "  font-family: 'Courier New', monospace;"
                "  font-size: 10px;"
                "}"
                "QPushButton:hover {"
                "  background-color: #d3d1c7;"
                "}"
                "QPushButton:pressed {"
                "  background-color: #9a9890;"
                "  border: 1px inset #666;"
                "}"
                );

            buttons[r][c] = btn;
            gridLayout->addWidget(btn, r, c);

            // Linker Mausklick — Feld aufdecken
            connect(btn, &QPushButton::clicked, this, [=]()
                    {
                        if (paused || gameOver) return;

                        board->reveal(r, c);

                        if (board->getCell(r, c).hasMine)
                        {
                            gameOver = true;
                            won      = false;

                            updateStatistics();
                            statisticsSaved = true;

                            timer->stop();
                            board->revealAll();
                            updateUI();

                            QMessageBox::warning(this,
                                                 "Spiel beendet",
                                                 "Sie haben eine Mine getroffen und verloren.");
                        }

                        updateUI();
                        refreshStatus();
                    });

            // Mittlerer Mausklick — Markierung entfernen
            connect(btn, &CellButton::middleClicked, this, [=]()
                    {
                        if (paused || gameOver) return;

                        if (board->getCell(r, c).flagged)
                        {
                            board->toggleFlag(r, c);
                            if (flagCount > 0) flagCount--;
                            updateUI();
                            refreshStatus();
                        }
                    });

            // Rechter Mausklick — Markierung setzen
            btn->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(btn, &QPushButton::customContextMenuRequested, this, [=]()
                    {
                        if (paused || gameOver) return;

                        // Nur setzen, wenn noch keine Flagge vorhanden ist
                        if (!board->getCell(r, c).flagged)
                        {
                            board->toggleFlag(r, c);
                            flagCount++;

                            updateUI();
                            refreshStatus();
                        }
                    });
        }
    }

    allocatedRows = rows;
    allocatedCols = cols;

    // Fenstergröße anpassen (30px pro Zelle + Ränder)
    resize(cols * 30 + 80, rows * 30 + 160);
    setMinimumSize(400, 300);
}
/**
 * @author Mohamed Ilahi
 * @brief Farbschema für die Nachbarzahlen im Minesweeper-Spiel.
 *
 * Enthält die klassischen Farben für die Werte 1 bis 8.
 */
static const char* numberColors[] = {
    "",          // 0 – kein Text
    "#1a5fa8",   // 1 – blau
    "#2d7d1a",   // 2 – grün
    "#cc2200",   // 3 – rot
    "#1a1a7a",   // 4 – dunkelblau
    "#8b1a1a",   // 5 – dunkelrot
    "#1a7a7a",   // 6 – cyan
    "#1a1a1a",   // 7 – schwarz
    "#808080",   // 8 – grau
};

/**
 * @author Mohamed Ilahi
 * @brief Aktualisiert die Darstellung des Spielfeldes.
 *
 * Passt die Anzeige aller Buttons an den aktuellen Zustand
 * der Spielfeldzellen an und prüft, ob das Spiel beendet ist.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::updateUI()
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            const Cell& cell = board->getCell(r, c);
            CellButton* btn  = buttons[r][c];

            btn->setText("");
            btn->setEnabled(true);

            if (gameOver)
            {
                // Korrekt markierte Mine → blau
                if (cell.flagged && cell.hasMine)
                {
                    btn->setText("F");
                    btn->setStyleSheet(
                        "QPushButton {"
                        "  background-color: #b5d4f4;"
                        "  border: 1px solid #185fa5;"
                        "  border-radius: 2px;"
                        "  color: #185fa5;"
                        "  font-weight: bold;"
                        "  font-size: 10px;"
                        "  font-family: 'Courier New', monospace;"
                        "}"
                        );
                    continue;
                }

                // Falsch markiert (Marke ohne Mine) → rot
                if (cell.flagged && !cell.hasMine)
                {
                    btn->setText("F");
                    btn->setStyleSheet(
                        "QPushButton {"
                        "  background-color: #f5c4b3;"
                        "  border: 1px solid #e24b4a;"
                        "  border-radius: 2px;"
                        "  color: #cc2200;"
                        "  font-weight: bold;"
                        "  font-size: 10px;"
                        "  font-family: 'Courier New', monospace;"
                        "}"
                        );
                    continue;
                }
            }

            if (cell.flagged)
            {
                // Markiert → F in blau
                btn->setText("F");
                btn->setStyleSheet(
                    "QPushButton {"
                    "  background-color: #b4b2a9;"
                    "  border: 1px solid #888780;"
                    "  border-radius: 2px;"
                    "  color: #185fa5;"
                    "  font-weight: bold;"
                    "  font-size: 12px;"
                    "  font-family: 'Courier New', monospace;"
                    "}"
                    );
            }
            else if (cell.revealed)
            {
                btn->setEnabled(false);

                if (cell.exploded)
                {
                    // Explodierte Mine → rotes X auf rotem Hintergrund
                    btn->setText("X");
                    btn->setEnabled(true);
                    btn->setStyleSheet(
                        "QPushButton {"
                        "  background-color: #f7c1c1;"
                        "  border: 1px solid #e24b4a;"
                        "  border-radius: 2px;"
                        "  color: #cc0000;"
                        "  font-weight: bold;"
                        "  font-size: 11px;"
                        "  font-family: 'Courier New', monospace;"
                        "}"
                        );
                }
                else if (cell.hasMine)
                {
                    // Aufgedeckte (nicht explodierte) Mine → dunkles X
                    btn->setText("X");
                    btn->setEnabled(true);
                    btn->setStyleSheet(
                        "QPushButton {"
                        "  background-color: #b4b2a9;"
                        "  border: 1px solid #888780;"
                        "  border-radius: 2px;"
                        "  color: #1a1a1a;"
                        "  font-weight: bold;"
                        "  font-size: 11px;"
                        "  font-family: 'Courier New', monospace;"
                        "}"
                        );
                }
                else if (cell.neighboringMines > 0)
                {
                    // Zahl mit klassischer Farbe
                    int n = cell.neighboringMines;
                    QString color = (n >= 1 && n <= 8) ? numberColors[n] : "#1a1a1a";

                    btn->setText(QString::number(n));
                    btn->setStyleSheet(
                        QString(
                            "QPushButton {"
                            "  background-color: #f0ede8;"
                            "  border: 1px solid #ccc;"
                            "  border-radius: 2px;"
                            "  color: %1;"
                            "  font-weight: bold;"
                            "  font-size: 11px;"
                            "  font-family: 'Courier New', monospace;"
                            "}").arg(color)
                        );
                }
                else
                {
                    // Leeres aufgedecktes Feld
                    btn->setStyleSheet(
                        "QPushButton {"
                        "  background-color: #e8e5df;"
                        "  border: 1px solid #ccc;"
                        "  border-radius: 2px;"
                        "}"
                        );
                }
            }
            else
            {
                // Verdecktes Feld (Standard)
                btn->setStyleSheet(
                    "QPushButton {"
                    "  background-color: #b4b2a9;"
                    "  border: 1px solid #888780;"
                    "  border-radius: 2px;"
                    "  font-weight: bold;"
                    "  font-family: 'Courier New', monospace;"
                    "  font-size: 10px;"
                    "}"
                    "QPushButton:hover {"
                    "  background-color: #d3d1c7;"
                    "}"
                    "QPushButton:pressed {"
                    "  background-color: #9a9890;"
                    "}"
                    );
            }
        }
    }
    // Gewinn prüfen
    if (board->allCellsProcessed() && !statisticsSaved)
    {
        gameOver = true;
        timer->stop();

        won = board->allMinesCorrectlyFlagged();
        updateStatistics();
        statisticsSaved = true;

        if(won)
        {
            QMessageBox::information(
                this,
                "Spiel beendet",
                "Herzlichen Glückwunsch! Sie haben gewonnen."
                );
        }
        else
        {
            QMessageBox::warning(
                this,
                "Spiel beendet",
                "Alle Felder wurden bearbeitet, aber die Minen wurden nicht korrekt markiert. Sie haben verloren."
                );
        }
    }
}
/**
 * @author Mohamed Ilahi
 * @brief Aktualisiert die Statusanzeige.
 *
 * Zeigt die Anzahl der Minen, die Anzahl der gesetzten
 * Markierungen sowie die vergangene Spielzeit an.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::refreshStatus()
{
    lblMines->setText("💣 Minen: " + QString::number(mines));

    lblTime->setText("⏱ Zeit:  " + QString::number(seconds) + " s");

    lblFlags->setText("🚩 Marken: " + QString::number(flagCount));

    if (flagCount > mines)
        lblFlags->setStyleSheet(
            "QLabel {"
            "  font-family: 'Courier New', monospace;"
            "  font-size: 12px;"
            "  font-weight: bold;"
            "  background-color: #1a1a1a;"
            "  color: #ff4444;"       // rot: zu viele Marken
            "  border: 1px inset #555;"
            "  border-radius: 2px;"
            "  padding: 2px 8px;"
            "  min-width: 90px;"
            "}"
            );
    else
        lblFlags->setStyleSheet(
            "QLabel {"
            "  font-family: 'Courier New', monospace;"
            "  font-size: 12px;"
            "  font-weight: bold;"
            "  background-color: #1a1a1a;"
            "  color: #4488ff;"       // blau: alles ok
            "  border: 1px inset #555;"
            "  border-radius: 2px;"
            "  padding: 2px 8px;"
            "  min-width: 90px;"
            "}"
            );
}
/**
 * @author Mohamed Ilahi
 * @brief Aktualisiert die Spielzeit.
 *
 * Wird regelmäßig vom Timer aufgerufen und erhöht die
 * vergangene Spielzeit um eine Sekunde.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::updateTimer()
{
    if (!paused && !gameOver)
    {
        seconds++;
        refreshStatus();
    }
}
/**
 * @author Mohamed Ilahi
 * @brief Pausiert oder setzt das Spiel fort.
 *
 * Während der Pause wird der Timer angehalten und das
 * Spielfeld ausgeblendet. Beim Fortsetzen werden beide
 * wieder aktiviert.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::pauseGame()
{
    paused = !paused;

    if (paused)
    {
        timer->stop();
        container->hide();
        ui->btnPause->setText("Weiter");
    }
    else
    {
        timer->start(1000);
        container->show();
        ui->btnPause->setText("Pause");
    }
}
/**
 * @author Mohamed Ilahi
 * @brief Beendet das aktuelle Spiel.
 *
 * Das Spiel wird als verloren gewertet, alle Felder
 * werden aufgedeckt und die Statistik aktualisiert.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::endGame()
{
    if (statisticsSaved)
        return;

    gameOver = true;
    won      = false;

    updateStatistics();
    statisticsSaved = true;

    timer->stop();
    board->revealAll();
    updateUI();
    refreshStatus();
}
/**
 * @author Mohamed Ilahi
 * @brief Aktualisiert die Spielstatistik.
 *
 * Speichert Informationen über gespielte, gewonnene und
 * verlorene Spiele sowie die beste erreichte Zeit für
 * jede Spielfeldkonfiguration.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::updateStatistics()
{
    QString key = QString("%1x%2 (%3)").arg(rows).arg(cols).arg(mines);

    if (statistics.find(key) == statistics.end())
        statistics[key] = std::make_tuple(0, 0, 0, -1);

    auto& entry = statistics[key];
    std::get<0>(entry)++;

    if (won)
    {
        std::get<1>(entry)++;
        int best = std::get<3>(entry);
        if (best == -1 || seconds < best)
            std::get<3>(entry) = seconds;
    }
    else
    {
        std::get<2>(entry)++;
    }
}
/**
 * @author Mohamed Ilahi
 * @brief Öffnet das Einstellungsfenster.
 *
 * Ermöglicht die Änderung von Spielfeldgröße und
 * Minenanzahl.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::openSettings()
{
    SettingsDialog dlg(rows, cols, mines, this);
    if (dlg.exec() == QDialog::Accepted)
        newGame();
}
/**
 * @author Mohamed Ilahi
 * @brief Öffnet das Statistikfenster.
 *
 * Zeigt die gespeicherten Spielstatistiken an.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::openStats()
{
    StatisticsDialog dlg(statistics, this);
    dlg.exec();
}
/**
 * @author Mohamed Ilahi
 * @brief Öffnet das Hilfefenster.
 *
 * Zeigt Informationen zur Bedienung des Spiels an.
 *
 * @return Kein Rückgabewert.
 */
void MainWindow::openHelp()
{
    HelpDialog dlg(this);
    dlg.exec();
}
