#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QLabel>
#include <QStatusBar>
#include <QPixmap>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>
#include <QMessageBox>
#include "godialog.h"
#include "finddialog.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QMimeData>
#include <QClipboard>
#include <QLineEdit>

class spreadSheet : public QMainWindow
{
    Q_OBJECT

public:
    spreadSheet(QWidget *parent = nullptr);
    ~spreadSheet();

protected :
    void createActions();
    void createMenus();
    void createToolBars();
    void makeConnexions();
    void saveContent(QString fileName)const;
    void loadContent(QString fileName);
    void loadCSVFile(QString fileName);
    void saveAs(QString fileName)const;

private slots :
    void updateStatusBar(int, int);
    void aboutQtSlot();
    void goCellSlot();
    void findTextSlot();
    void saveSlot();
    void loadSlot();
    void loadCSVSlot();
    void saveAsSlot();
    void openRecentFile();
    void newFileSlot();
    void cutSlot();
    void copySlot();
    void pasteSlot();

private :
    //Pointeur sur le widget principal
    QTableWidget *spreadsheet;

    /* --- fileMenu actions --- */
    QAction * newFile;
    QAction * openCoordinateFile;
    QAction * openCSVFile;
    QAction * saveFile;
    QAction * saveAsFile;
    QAction * quit;

    /* --- editMenu actions --- */
    QAction * cutFile;
    QAction * copy;
    QAction * paste;
    QAction * Delete;
    QAction * row;
    QAction * column;
    QAction * all;
    QAction * findText;
    QAction * goCell;

    /* --- toolsMenu actions --- */
    QAction * recalculate;
    QAction * sort;

    /* --- optionsMenu actions --- */
    QAction * showGrid;  //Action pour
    QAction * autoRecalculate;

    /* --- optionsMenu actions --- */
    QAction * about;
    QAction * aboutQt;

    /* --- recentFiles actions --- */
//    enum { maxRecentFiles = 5 };
//    QAction * recentFileActions[maxRecentFiles];
    QVector <QAction*> recentFileActions;

    //Pointeurs sur les menus
    QMenu * fileMenu;
    QMenu * editMenu;
    QMenu * toolsMenu;
    QMenu * optionsMenu;
    QMenu * helpMenu;

    //Pointeurs sur les labels
    QLabel * cellLocation;
    QLabel * cellFormula;

    //Répertoire du fichier
    QString * currentFile;

    //Nom de base de fichier
    QString baseName;

    //variable for storing the previous file
    QString * prevFile;

    //Counter of maxRecentFile
    int count = 0;

    //Clipboard
    QClipboard *clipboard;


};
#endif // SPREADSHEET_H
