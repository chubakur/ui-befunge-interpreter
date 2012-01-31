#include <interpreter.h>
#include <GUInterpreter.h>
#include <stdio.h>
GUInterpreter::GUInterpreter(){
    debug = false;
    GUIEnvironment = new GUIWidget();
    interpreter = new BefungeInterpreter(GUIEnvironment);
    loadscriptAction = new QAction(tr("Load Script"),this);
    quitAction = new QAction(tr("Quit"),this);
    runScriptAction = new QAction(tr("Run"), this);
    startDebugAction = new QAction(tr("Start debug"), this);;
    stepAction = new QAction(tr("&Step Next"), this);
    connect(loadscriptAction,SIGNAL(triggered()),this,SLOT(loadscript()));
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(runScriptAction, SIGNAL(triggered()),this,SLOT(runscript()));
    connect(startDebugAction,SIGNAL(triggered()),this,SLOT(runscriptSbS()));
    connect(stepAction,SIGNAL(triggered()),this,SLOT(step()));
    menu = menuBar()->addMenu(tr("Interpreter"));
    menu->addAction(loadscriptAction);
    menu->addSeparator();
    menu->addAction(quitAction);
    menu_runtime = menuBar()->addMenu(tr("Runtime"));
    menu_runtime->addAction(runScriptAction);
    menu_debug = menuBar()->addMenu(tr("&Debug"));
    menu_debug->addAction(startDebugAction);
    menu_debug->addAction(stepAction);
    setCentralWidget(GUIEnvironment);
}
GUInterpreter::~GUInterpreter(){
    delete interpreter;
    delete loadscriptAction;
    delete menu;
    delete quitAction;
    delete startDebugAction;
    delete stepAction;
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
            item->setFlags(Qt::ItemIsEnabled);//делаем его неизменяемым
        }
    }
    GUIEnvironment->scripttable->resizeColumnsToContents();//подгоняем размеры
    GUIEnvironment->scripttable->resizeRowsToContents();
}
void GUInterpreter::runscript(){
    interpreter->Run();
}
void GUInterpreter::runscriptSbS(){
    if(!debug){
        GUIEnvironment->print("Debug started.\n");
        startDebugAction->setText("Stop debug");
    }
    else{
        startDebugAction->setText("Start debug");
        GUIEnvironment->print("Debug ended.\n");
    }
    debug = !debug;
    if(debug)
        GUIEnvironment->tableValues[0]->setBackgroundColor(QColor(193,155,232,200));
    else
        GUIEnvironment->tableValues[x+y*interpreter->size_x]->setBackgroundColor(QColor(255,255,255,200));
    x = 0;
    y = 0;
}
void GUInterpreter::step(){
    if(!debug)
        return;
    GUIEnvironment->tableValues[x+y*interpreter->size_x]->setBackgroundColor(QColor(255,255,255,200));
    direction = interpreter->Execute(x,y);
    //printf("%d %d\n",x,y);
    if(direction == 0) x--;
    else if(direction == 1) x++;
    else if(direction == 2) y--;
    else if(direction == 3) y++;
    else {
        debug = false;
        GUIEnvironment->print("\nDebug ended.\n");
        startDebugAction->setText("Start debug");
        return;
    }
    GUIEnvironment->tableValues[x+y*interpreter->size_x]->setBackgroundColor(QColor(193,155,232,200));
    if(interpreter->GetCharFromMatrix(x,y) == ' ') step();
}
