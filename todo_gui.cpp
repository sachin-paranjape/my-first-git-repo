#include<FL/Fl.H>
#include<FL/Fl_Window.H>
#include<FL/Fl_Input.H>
#include<FL/Fl_Button.H>
#include<FL/Fl_Browser.H>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

vector<string> tasks;
Fl_Browser* browser;

//Function to read tasks from file
void loadTasks(){
    tasks.clear();
    ifstream infile("tasks.txt");
    string line;
    while(getline(infile,line)){
        tasks.push_back(line);
    }
    infile.close();
}

//Function to write tasks to file
void saveTasks(){
    ofstream outfile("tasks.txt");
    for(auto& task:tasks){
        outfile<<task<<endl;
    }    
    outfile.close();
}

//Function to refresh the GUI task list
void updateOutput(){
    browser->clear();
    for(int i=0;i<tasks.size();i++){
        browser->add((to_string(i+1)+". "+tasks[i]).c_str());
    }
} 

//Callback for Add button
void add_cb(Fl_Widget* w,void *data){
    Fl_Input* input=(Fl_Input*)data;
    string task = input->value();
    if(!task.empty()){
        tasks.push_back(task);
        saveTasks();
        updateOutput();
        input->value("");
    }
}

//Callback for delete button
void delete_cb(Fl_Widget*,void*){
    int selected=browser->value();
    if(selected>0 && selected<=tasks.size()){
        tasks.erase(tasks.begin()+selected-1);
        saveTasks();
        updateOutput();
    }
}

//Callback for done button
void done_cb(Fl_Widget*,void*){

    int selected=browser->value();
    if(selected>0 && selected<=tasks.size()){
        if(tasks[selected-1].find("[DONE]")==string::npos){
            tasks[selected-1]+="[DONE]";
            saveTasks();
            updateOutput();
        }
    }
}

int main(int argc,char** argv){
    loadTasks();
    Fl_Window* window=new Fl_Window(400,300,"To-Do App");
    Fl_Input* input=new Fl_Input(100,10,200,25,"New Task: ");
    Fl_Button* add=new Fl_Button(310,10,70,25,"Add");
    add->callback(add_cb,input);

    browser=new Fl_Browser(20,50,360,150);
    browser->type(FL_HOLD_BROWSER);
    updateOutput();

    Fl_Button* done= new Fl_Button(80,220,80,30,"Mark Done");
    done->callback(done_cb);

    Fl_Button* del=new Fl_Button(160,220,80,30,"Delete");
    del->callback(delete_cb);

    Fl_Button* exit_btn=new Fl_Button(240,220,80,30,"Exit");
    exit_btn->callback([](Fl_Widget*,void*){ exit(0);});

    window->end();
    window->show(argc,argv);
    return Fl::run();
}
