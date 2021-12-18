#include "spreadsheet.h"

spreadSheet::spreadSheet(QWidget *parent)
    : QMainWindow(parent)
{
    /* --- Main Window --- */
    spreadsheet = new QTableWidget;
    spreadsheet->setRowCount(200);
    spreadsheet->setColumnCount(100);
    setCentralWidget(spreadsheet);

    /* --- create actions --- */
    createActions();

    /* --- create menus --- */
    createMenus();

    /* --- create toolBar --- */
    createToolBars();

    /* --- connect --- */
    makeConnexions();


    //creating the labels for the satus bar (should be in its proper function)
    cellLocation = new QLabel("(1, 1)");
    cellFormula = new QLabel("");
    statusBar()->addPermanentWidget(cellLocation);
    statusBar()->addPermanentWidget(cellFormula);

    //Changer les label du spreadsheet
    QStringList labels;

    //Remplir la liste des label
    for(char letter = 'A'; letter <='Z'; letter++)
        labels <<QString(letter);
    spreadsheet->setVerticalHeaderLabels(labels);

    //Initier le champ de currenFile et de prevFile
    currentFile = nullptr;
    prevFile = nullptr;

    //Titre de la fenetre
    setWindowTitle("Untiteld");

    //clipboard
    clipboard = QApplication::clipboard();
}

spreadSheet::~spreadSheet()
{
    delete spreadsheet;

    delete newFile;
    delete openCoordinateFile;
    delete openCSVFile;
    delete saveFile;
    delete saveAsFile;
    delete quit;

    delete cutFile;
    delete  copy;
    delete paste;
    delete Delete;
    delete row;
    delete column;
    delete all;    
    delete findText;
    delete goCell;

    delete recalculate;
    delete sort;

    delete showGrid;
    delete autoRecalculate;

    delete about;
    delete aboutQt;

    delete fileMenu;
    delete editMenu;
    delete toolsMenu;
    delete optionsMenu;
    delete helpMenu;
}

void spreadSheet::createActions()
{
    //Pour construire une action, il nous faut en générale 4 étapes

    //Etape 1 : Lui choisir une icone    
    QPixmap newIcon(":/icons/new_file.png");
    QPixmap openIcon(":/icons/open_file.png");
    QPixmap saveIcon(":/icons/save_file");
    QPixmap quitIcon(":/icons/quit_icon.png");

    QPixmap cutIcon(":/icons/cut_icon.png");
    QPixmap copyIcon(":/icons/copy_icon.png");
    QPixmap pasteIcon(":/icons/paste_icon.png");
    QPixmap delIcon(":/icons/delete.png");
    QPixmap goIcon(":/icons/go_to_icon.png");
    QPixmap searchIcon(":/icons/search_icon.png");
    QPixmap csvIcon(":/icons/openCSV.png");

    //Etape 2 : Creer l'action   
    newFile = new QAction(newIcon,"&New",this);
    openCoordinateFile = new QAction(openIcon, "&Open Coordinate File...",this);
    openCSVFile = new QAction(csvIcon, "Open CSV File", this);
    saveFile = new QAction(saveIcon, "&Save",this);
    saveAsFile = new QAction(saveIcon, "Save &As...",this);
    quit = new QAction(quitIcon, "&Quit", this);

    cutFile = new QAction(cutIcon, "&Cut",this);
    copy = new QAction(copyIcon, "&Copy", this);
    paste = new QAction(pasteIcon, "&Paste", this);
    Delete = new QAction(delIcon, "&Delete", this);
    row = new QAction("&Row",this);
    column = new QAction("&Column",this);
    all = new QAction("&All",this);
    findText = new QAction(searchIcon,"&Find...",this);
    goCell = new QAction(goIcon,"&Go to Cell...",this);

    recalculate = new QAction("&Recalculate", this);
    sort = new QAction("&Sort...", this);

    showGrid = new QAction("Show Grid",this);
    showGrid->setCheckable(true);
    showGrid->setChecked(spreadsheet->showGrid());
    autoRecalculate = new QAction("Auto-Recalculate", this);
    autoRecalculate->setCheckable(true);

    about = new QAction("About",this);
    aboutQt = new QAction("About &Qt",this);

    //Etape 3 : Lui choisir un racourci
    newFile->setShortcut(tr("Ctrl+N"));
    openCoordinateFile->setShortcut(tr("Ctrl+O"));
    saveFile->setShortcut(tr("Ctrl+S"));
    saveAsFile->setShortcut(tr("Ctrl+Shift+S"));
    quit->setShortcut(tr("Ctrl+Q"));

    cutFile->setShortcut(tr("Ctrl+X"));
    copy->setShortcut(tr("Ctrl+C"));
    paste->setShortcut(tr("Ctrl+V"));
    Delete->setShortcut(tr("Del"));
    all->setShortcut(tr("Ctrl+A"));
    findText->setShortcut(tr("Ctrl+F"));
    goCell->setShortcut(tr("F5"));
    recalculate->setShortcut(tr("F9"));

    /* --- RecentFile actions --- */
    for (int i = 0; i < 5; ++i) {
           recentFileActions.push_back(new QAction(this));
           recentFileActions[i]->setVisible(false);
       }
}

void spreadSheet::createMenus()
{
    //Creer le menu file
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newFile);
    auto open = fileMenu->addMenu("Open");
    open->addAction(openCoordinateFile);
    open->addAction(openCSVFile);
    fileMenu->addAction(saveFile);
    fileMenu->addAction(saveAsFile);
    fileMenu->addSeparator();
    for (int i = 0; i < 5; ++i)
            fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(quit);

    //Creer le menu d'édition
    editMenu = menuBar()->addMenu("&Edit");
    editMenu->addAction(cutFile);
    editMenu->addAction(copy);
    editMenu->addAction(paste);
    editMenu->addAction(Delete);
    auto select = editMenu->addMenu("Select");
    select->addAction(row);
    select->addAction(column);
    select->addAction(all);
    editMenu->addSeparator();
    editMenu->addAction(findText);
    editMenu->addAction(goCell);

    //Ccréer le menu d'outils
    toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction(recalculate);
    toolsMenu->addAction(sort);

    //Creer le menu options
    optionsMenu = menuBar()->addMenu("&Options");
    optionsMenu->addAction(showGrid);
    optionsMenu->addAction(autoRecalculate);

    //Creer le menu help
    helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(about);
    helpMenu->addAction(aboutQt);;
}

void spreadSheet::makeConnexions()
{
    //Etape 4 : Lui choisir un slot

    connect(quit, &QAction::triggered, this, &QMainWindow::close);

    connect(aboutQt, &QAction::triggered, this, &spreadSheet::aboutQtSlot);

    connect(all, &QAction::triggered, spreadsheet, &QTableWidget::selectAll);

    connect(row, &QAction::triggered, spreadsheet, &QTableWidget::selectRow);

    connect(cutFile, &QAction::triggered, this, &spreadSheet::cutSlot);

    connect(copy, &QAction::triggered, this, &spreadSheet::copySlot);

    connect(paste, &QAction::triggered, this, &spreadSheet::pasteSlot);

    /* --- Connect newFile action --- */
    connect(newFile, &QAction::triggered, this, &spreadSheet::newFileSlot);

    connect(column, &QAction::triggered, spreadsheet, &QTableWidget::selectColumn);

    connect(showGrid, &QAction::triggered, spreadsheet, &QTableWidget::setShowGrid);

    //connectting the changee of any element in the spreadsheet with the update status bar
    connect(spreadsheet, &QTableWidget::cellClicked, this,  &spreadSheet::updateStatusBar);

    //Connection pour le go to cell
    connect(goCell, &QAction::triggered,this, &spreadSheet::goCellSlot);

    //Connection pour le find text
    connect(findText, &QAction::triggered, this, &spreadSheet::findTextSlot);

    //Connecter le save Action au save Slot
    connect(saveFile, &QAction::triggered, this, &spreadSheet::saveSlot);

    //Connecter le load Action au load Slot
    connect(openCoordinateFile, &QAction::triggered, this, &spreadSheet::loadSlot);

    //Connecter openCSVFile Action au loadCSVSlot
    connect(openCSVFile, &QAction::triggered, this, &spreadSheet::loadCSVSlot);

    //Connecter le saveAs action au saveAsSlot
    connect(saveAsFile, &QAction::triggered, this, &spreadSheet::saveAsSlot);

    /* --- Connect RecentFile actions --- */
    for (int i = 0; i < 5; ++i) {
           connect(recentFileActions[i], &QAction::triggered,
                   this, &spreadSheet::openRecentFile);
       }
}

void spreadSheet::createToolBars()
{
    auto toolBar1 = addToolBar("Tool Bar1");
    toolBar1->addAction(newFile);
    toolBar1->addAction(saveFile);
    toolBar1->addAction(quit);

    auto toolBar2 = addToolBar("Tool Bar2");
    toolBar2->addAction(findText);
    toolBar2->addAction(goCell);
}

void spreadSheet::newFileSlot()
{
    spreadsheet->clear();
    currentFile = nullptr;
    setWindowTitle("Untiteld");
}

void spreadSheet::loadContent(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QString line;

        while (!in.atEnd())
        {
            line = in.readLine();
            auto tokens = line.split(',');
            int row = tokens[0].toInt();
            int col = tokens[1].toInt();
            spreadsheet->setItem(row,col, new QTableWidgetItem(tokens[2]));
        }
    }

    file.close();
}

void spreadSheet::loadSlot()
{
    //1. Tester si on possède un nom de fichier

        //Creer factory design
        QFileDialog D; //factory

        //Creer un dialoque pour abtenir le nom du fichier
        auto fileName = D.getOpenFileName();

        if(fileName != "")
        {
            //Changer le nom du fichier courant
            currentFile = new QString(fileName);

            //2. charger le contrenu
            loadContent(*currentFile);
        }

        //Get the name of the file without the directory
        QFileInfo fi(*currentFile);
        QString baseName = fi.completeBaseName();

        //Mettre à jour le titre de la fenêtre
        setWindowTitle(baseName);

        //show the file in recentFileMenu
        if(count == 0)
        {
            recentFileActions[count]->setText(*currentFile);
            recentFileActions[count]->setVisible(true);
            prevFile = currentFile;
            count++;
        }
        else if(*prevFile != *currentFile && count != 0)
        {
            recentFileActions[count]->setText(*currentFile);
            recentFileActions[count]->setVisible(true);
            prevFile = currentFile;
            count++;
        }
         if(count > 5)
            count = 0;
}

void spreadSheet::loadCSVFile(QString fileName){
   //Pointer sur le fichier d'intéret
    QFile file(fileName);

    //Tester si on a un fichier csv à lire
    if(!file.open(QFile::ReadOnly | QIODevice::Text))
        return;
    else
    {
       QTextStream in(&file);
       QStringList list;
       int count = 0;
       while (!in.atEnd())
       {
            QString line = in.readLine();
            for(auto item : line.split(","))
            {
                list.append(item);
            }
            for(int i=0; i<list.size(); i++)
            {
                spreadsheet->setItem(count, i, new QTableWidgetItem(list[i]));
            }
            count++;
            list.clear();
       }
    }

    file.close();
}

void spreadSheet::loadCSVSlot()
{
    //1. Tester si on possède un nom de fichier

            //Creer factory design
            QFileDialog D; //factory

            //Creer un dialoque pour abtenir le nom du fichier
            auto fileName = D.getOpenFileName();

            if(fileName != "")
            {
                //Changer le nom du fichier courant
                currentFile = new QString(fileName);

                //2. charger le contrenu
                loadCSVFile(*currentFile);
            }

            //Get the name of the file without the directory
            QFileInfo fi(*currentFile);
            QString baseName = fi.completeBaseName();

            //Mettre à jour le titre de la fenêtre
            setWindowTitle(baseName);

            //show the file in recentFileMenu
            if(count == 0)
            {
                recentFileActions[count]->setText(*currentFile);
                recentFileActions[count]->setVisible(true);
                prevFile = currentFile;
                count++;
            }
            else if(*prevFile != *currentFile && count < 5)
            {
                recentFileActions[count]->setText(*currentFile);
                recentFileActions[count]->setVisible(true);
                prevFile = currentFile;
                count++;
            }
            if(count > 5)
                    count = 0;
}

void spreadSheet::saveContent(QString fileName)const
{
    //Syntaxe C++
    // ofstream out(fileName)  -------. /out.close();

    //Syntaxe C
    //FILE * fid = fopen(fileName, "w")         fclose(fid);

    //En Qt

    // un pointeur sur le fichier d'interet
    QFile file(fileName);

    //Ouvrir le fichier
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        //Parcourir les cellules et sauvegarder leur contenu
        for ( int i = 0; i < spreadsheet->rowCount() ; i++ )
            for (int j = 0; j < spreadsheet->columnCount() ; j++ )
            {
                auto cell = spreadsheet->item(i,j);
                if (cell)
                {
                    out << i << "," << j << "," <<cell->text() << Qt::endl;
                }
            }
    }

    //Fermer le ficher
    file.close();
}

void spreadSheet::saveSlot()
{
    //1. Tester si on possède un nom de fichier
    if(!currentFile)
    {
        //Creer factory design
        QFileDialog D; //factory

        //Creer un dialoque pour abtenir le nom du fichier
        auto fileName = D.getSaveFileName();

        //Changer le nom du fichier courant
        currentFile = new QString(fileName);

        //2. Sauvegarder le contrenu
        saveContent(*currentFile);
    }

    //Get the name of the file without the directory
    QFileInfo fi(*currentFile);
    QString baseName = fi.completeBaseName();

    //Mettre à jour le titre de la fenêtre
    setWindowTitle(baseName);

    //show the file in recentFileMenu
    if(*currentFile != "")
    {
        if(count == 0)
        {
            recentFileActions[count]->setText(*currentFile);
            recentFileActions[count]->setVisible(true);
            prevFile = currentFile;
            count++;
        }
        else if(*prevFile != *currentFile && count != 0)
        {
            recentFileActions[count]->setText(*currentFile);
            recentFileActions[count]->setVisible(true);
            prevFile = currentFile;
            count++;
        }
        if(count > 5)
        {
            count = 0;
        }
    }
}

void spreadSheet::saveAs(QString fileName)const{
    //Pointer sur le fichier
    QFile file(fileName);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        QString line = "";
        //Parcourir les cellules et sauvegarder leur contenu
        for ( int i = 0; i < spreadsheet->rowCount() ; i++ )
        {
            for (int j = 0; j < spreadsheet->columnCount() ; j++ )
            {
                if(spreadsheet->item(i,j))
                {
                    line += spreadsheet->item(i,j)->text();
                    line += ",";
                }
                else
                {
                    line += " ";
                    line += ",";
                }
            }
            out << line.remove(line.size()-1, 1) << Qt::endl;
            line = "";
        }
    }

    //Fermer le ficher
    file.close();
}

void spreadSheet::saveAsSlot(){
    //1. Tester si on possède un nom de fichier
    if(!currentFile)
    {
        //Creer factory design
        QFileDialog D; //factory

        //Creer un dialoque pour abtenir le nom du fichier
        auto fileName = D.getSaveFileName();

        //Changer le nom du fichier courant
        currentFile = new QString(fileName);

        //Mettre à jour le titre de la fenêtre
        setWindowTitle(*currentFile);
    }

    //2. Sauvegarder le contrenu
    saveAs(*currentFile);

    //show the file in recentFileMenu
    if(count == 0)
    {
        recentFileActions[count]->setText(*currentFile);
        recentFileActions[count]->setVisible(true);
        prevFile = currentFile;
        count++;
    }
    else if(*prevFile != *currentFile && count < 5)
    {
        recentFileActions[count]->setText(*currentFile);
        recentFileActions[count]->setVisible(true);
        prevFile = currentFile;
        count++;
    }
    if(count > 5)
            count = 0;
}


void spreadSheet::openRecentFile()
{
    spreadSheet::newFileSlot();
    QAction *action = dynamic_cast<QAction*>(sender());
    if (action){
        loadContent(action->text());
    }
}

void spreadSheet::cutSlot(){

    //get the last child widget which has been focused and cast it as lie edit
    QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(focusWidget());
    if(lineEdit)
    {
        //it was a line Edit
        lineEdit->cut();
    }
}

void spreadSheet::copySlot()
{
    //get the last child widget which has been focused and cast it as lie edit
    QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(focusWidget());
    if(lineEdit)
    {
        //it was a line Edit
        lineEdit->copy();
    }
}

void spreadSheet::pasteSlot()
{
    //get the last child widget which has been focused and cast it as lie edit
    QLineEdit *lineEdit = dynamic_cast<QLineEdit*>(focusWidget());
    if(lineEdit)
    {
        //it was a line Edit
        lineEdit->paste();
    }
}

void spreadSheet::findTextSlot()
{
    FindDialog dialog;
    auto reply = dialog.exec();
    auto found = false;

    if(reply == FindDialog::Accepted)
    {
        QString text = dialog.getText();

        for(auto i=0; i<spreadsheet->rowCount(); i++)
        {
            for(auto j=0; j<spreadsheet->columnCount(); j++)
            {
                if(spreadsheet->item(i,j))
                {
                     if(spreadsheet->item(i,j)->text() == text){
                         spreadsheet->setCurrentCell(i,j);
                         found = true;
                     }
                }
            }
        }

        if(!found)
            QMessageBox::information(this,"Error", "Not found");
    }
}

void spreadSheet::goCellSlot()
{
    //1. Créer le dialogue
    GoDialog D;

    //2.Exécuter le dialogue
    auto reply = D.exec();

    //3.Verifier si le dialogue a été accepté
    if(reply == GoDialog::Accepted)
    {
        //B32
        //Extraire le texte
        QString cell = D.getCell();

        //a->b->c ------z .......A->b->....L
        //Extraire la ligne
        int row = cell[0].toLatin1() - 'A';

        //Extraire le colonne
        cell = cell.remove(0,1);
        int col = cell.toInt()-1;

        //Changer la cellule
        statusBar()->showMessage("Changing the current cell",2000);
        spreadsheet->setCurrentCell(row,col);
    }
}

void spreadSheet::updateStatusBar(int row,int col)
{
    QString cell{"(%0, %1)"};
    cellLocation->setText(cell.arg(row+1).arg(col+1));
    statusBar()->showMessage("Opening File", 5000);
}

void spreadSheet::aboutQtSlot()
{
    QMessageBox::aboutQt(this, "About Me");
}











