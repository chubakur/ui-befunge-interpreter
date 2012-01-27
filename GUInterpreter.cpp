#include "GUInterpreter.h"
#include <interpreter.h>
#include <stdio.h>
GUIWidget::GUIWidget(){
    scripttable = new QTableWidget(this);
    console = new QTextEdit(this);
    layout = new QHBoxLayout();
    vlayout = new QVBoxLayout();
    stackView = new QListWidget();
    vlayout->addLayout(layout);
    vlayout->addWidget(console);
    layout->addWidget(scripttable);
    layout->addWidget(stackView);
    setLayout(vlayout);
}
GUIWidget::~GUIWidget(){
    delete scripttable;
    delete stackView;
    delete layout;
    for(int i=0;i<tableValues.size();i++) delete tableValues[i];
}
GUInterpreter::GUInterpreter(){
    interpreter = new BefungeInterpreter();
    GUIEnvironment = new GUIWidget();
    loadscriptAction = new QAction(tr("&Load Script"),this);
    quitAction = new QAction(tr("&Quit"),this);
    runScriptAction = new QAction(tr("Run"), this);
    connect(loadscriptAction,SIGNAL(triggered()),this,SLOT(loadscript()));
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(runScriptAction, SIGNAL(triggered()),this,SLOT(runscript()));
    menu = menuBar()->addMenu(tr("&Interpreter"));
    menu->addAction(loadscriptAction);
    menu->addSeparator();
    menu->addAction(quitAction);
    menu_runtime = menuBar()->addMenu(tr("&Runtime"));
    menu_runtime->addAction(runScriptAction);
    setCentralWidget(GUIEnvironment);
}
GUInterpreter::~GUInterpreter(){
    delete interpreter;
    delete loadscriptAction;
    delete menu;
    delete quitAction;
    delete runScriptAction;
    delete GUIEnvironment;
}
void GUInterpreter::loadscript(){
    for(int i=0;i<GUIEnvironment->tableValues.size();i++) delete GUIEnvironment->tableValues[i];
    GUIEnvironment->tableValues.clear();              //очищаем массив указателей эл-тов таблицы`
    QString scriptfilename = QFileDialog::getOpenFileName(this,tr("Open script"),"",tr("Befunge Files (*.bfg)"));//берем адрес нужного файл
    if(scriptfilename == "") return; //если файл не выбран
    const char* filename = scriptfilename.toAscii().data(); //переводим в const char*
    interpreter->LoadScriptToRuntime(filename);//загружаем файл в интерпретатор
    GUIEnvironment->scripttable->setColumnCount(interpreter->size_x);//устанавливаем кол-во колонок в таблице
    GUIEnvironment->scripttable->setRowCount(interpreter->size_y);//устанавливаем кол-во строк в таблице
    for(int i=0;i<interpreter->size_y;i++){
        for(int j=0;j<interpreter->size_x;j++){
            QTableWidgetItem* item = new QTableWidgetItem();//новый эл-т
            GUIEnvironment->tableValues<<item;//помещаем его в массив эл-тов.
            GUIEnvironment->scripttable->setItem(i,j,item);//добавляем в таблицу
            item->setText(QString(interpreter->GetCharFromMatrix(j,i)));//устанавливаем символ из матрицы интерпретатора
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);//делаем его неизменяемым
        }
    }
    GUIEnvironment->scripttable->resizeColumnsToContents();//подгоняем размеры
    GUIEnvironment->scripttable->resizeRowsToContents();
    GUIEnvironment->tableValues[0]->setBackgroundColor(QColor(15,10,10,200));//выделяем 1-й эл-т таблицы
}
void GUInterpreter::runscript(){
    interpreter->Run();
}
