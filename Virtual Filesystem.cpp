//============================================================================
// Name         : Assignment_02
// Author       : Akhat Suleimenov
// Version      : 1.0
// Date Created : 25/03/21
// Date Modified: 07/04/21
// Copyright    : All rights are reserved
// Description  : Virtual Filesystem in C++
//============================================================================

#include<iostream>
#include<fstream>
#include<string>
#include <ctime>
using namespace std;

time_t now = time(0);
tm *ltm = localtime(&now);
string TIME = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_year - 100); // current date

template <typename T>
class Vector
{
	private:
		T *data;						//pointer to int(array) to store elements
		int v_size;						//current size of Vector (number of elements in Vector)
		int v_capacity;					//capacity of Vector
	public:
		Vector();						//No argument constructor
		Vector(int cap);				//One Argument Constructor
		Vector(Vector& other);			//Copy Constructor
		~Vector();						//Destructor
		void push_back(T element);		//Add an element at the end of Vector
		void erase(int t);
		T& operator[](int index); 				//return reference to the element at index
		int size() const;				//Return current size of Vector
		int capacity() const;			//Return capacity of Vector
		bool empty() const; 			//Rturn true if the Vector is empty, False otherwise
};
//===================================================
template <typename T> Vector<T>::Vector() {
	data = new T[0];
	v_size = 0;
	v_capacity = 0;
}
//===================================================
template <typename T> Vector<T>::Vector(int cap) {
	data = new T[cap];
	v_size = 0;
	v_capacity = cap;
}
//===================================================
template <typename T> Vector<T>::Vector(Vector& other) {
	v_size = other.size();
	v_capacity = other.capacity();
	data = new T[v_capacity];
	for (int i = 0; i < other.size(); i++)
		data[i] = other.data[i];
}
//===================================================
template <typename T> Vector<T>::~Vector() {
	delete[] data;
}
//===================================================
template <typename T> void Vector<T>::erase(int t) {
	for (int i = t; i < v_size - 1; i++)
		data[i] = data[i + 1];
	v_size--;
}
//===================================================
template <typename T> void Vector<T>::push_back(T element) {
	if(this->v_size == 0) {
		this->v_capacity = 1;
		this->data = new T[v_capacity];
	}
	else if(this->v_size==this->v_capacity) {
		v_capacity = v_capacity*2;
		T *data2 = new T[v_capacity];
		for(int i=0; i<v_size; i++)
			data2[i]=data[i];
		delete[] data;
		data = data2;
	}
	this->data[v_size++]=element;
}
//===================================================
template <typename T> T& Vector<T>::operator[](int index) {
	if (index >= v_size || index < 0)
		throw out_of_range("Out of bounds");
	return data[index];
}
//===================================================
template <typename T> int Vector<T>::size() const {
	return v_size;
}
//===================================================
template <typename T> int Vector<T>::capacity() const {
	return v_capacity;
}
//===================================================
template <typename T> bool Vector<T>::empty() const {
	return (v_size == 0);
}
//===================================================
template <typename T>
class Stack
{
	private:
		T *array;
		int n;	//number of current elements in the Stack
		int N;	//Array Size (Capacity)
	public:
		Stack(int N=100); //we set default capacity of stack as 50
		~Stack();
		void push(T);	//Push an elemet in the stack
		void pop();	//pop/remove the element at the tos 
		T& top();	//return reference of the top element
		int size();	//return current size of Stack
		bool empty();	//returns true if the stack is Empty
};
//===================================================
template <typename T>
Stack<T>::Stack(int N) : N(N), n(0) {
	array = new T[N];
}
//===================================================
template <typename T>
Stack<T>::~Stack() {
	if(array!=nullptr)		delete[] array;
}
//===================================================
template <typename T>
void Stack<T>::push(T element)	{
	if(n<N)		array[n++] = element;
	else 		throw runtime_error("Stack Overflow");
}
//===================================================
template <typename T>
void Stack<T>::pop() {
	if(n>0)		n--;
	else 		throw runtime_error("Stack is Empty");
}
//===================================================
template <typename T>
T& Stack<T>::top() {
	if(n>0)		return array[n-1];
	else 		throw runtime_error("Stack is Empty");	
}
//===================================================
template <typename T>
int Stack<T>::size() {
	return n;
}
//===================================================
template <typename T>
bool Stack<T>::empty() {
	return n==0;
}
//===================================================
template <typename T>
class Queue
{
	private:
		T *array;
		int n;	//number of current elements in the Queue
		int N;	//Array Size (Capacity)
		int f;	//index of front element
		int r;	//index where a new element will be added
	public:
		Queue(int N);
		~Queue();
		void enqueue(T); 
		T dequeue();
		T& front();
		bool isEmpty();
		bool isFull();
		void display();
};

//===================================================
template <typename T> Queue<T>::Queue(int N) {
	array = new T[N];
	this->N = N;
	n = 0;
	f = 0;
	r = 0;
}
//===================================================
template <typename T> Queue<T>::~Queue() {
	delete[] array;
}
//===================================================
template <typename T> void Queue<T>::enqueue(T t){
	if (isFull()) throw(runtime_error("Queue is Full"));
	array[r] = t;
	r = (r + 1) % N;
	n++;
}
//===================================================
template <typename T> T Queue<T>::dequeue(){
	if (isEmpty()) throw(runtime_error("Queue is Empty"));
	f = (f + 1) % N;
	n--;
	return array[(f - 1) % N];
}
//===================================================
template <typename T> T& Queue<T>::front() {
	if (isEmpty()) throw (runtime_error("Queue is Empty"));
	return array[f];
}
//===================================================
template <typename T> bool Queue<T>::isEmpty() {
	if (n == 0)
		return true;
	return false;
}
//===================================================
template <typename T> bool Queue<T>::isFull() {
	if (n == N)
		return true;
	return false;
}
//===================================================
class Inode {
public:
	string name;
	int size;
	string date;
	bool isFolder;
	
	Inode* parent = nullptr;
	Vector<Inode*> children;
public:
	Inode(string n, int s, string d, bool isFol);
};
//===================================================
Inode::Inode(string n, int s, string d, bool isFol) {
	size = s;
	name = n;
	date = d;
	isFolder = isFol;
}
//===================================================
bool contains(string s, char c) { // checking if char is in string s
	for (int i = 0; i < s.size(); i++)
		if (s[i] == c)
			return true;
	return false;
}
//===================================================
class Tree {
public:
	string path(Inode* node); // returns string path of the node in current directory 
	Inode* string_to_node(string file); // string to node conversion
	bool file_exists(string filename, Inode* node); //checking if file exists
	void file_exists_path(string filename, Inode* node, Vector<Inode*> *temp_Vector); // path of all the files that exist
	void check_name(Inode* node, string file); // check if file exists in the current directory

	void pwd();
	string realpath(string filename);
	void ls(string parameter);
	void mkdir(string foldername);
	void touch(string filename, int s);
	void cd(string file);
	void find(string file);
	void mv(string filename, string foldername);
	void rm(string file);
	
	int size(string file);
	int size_helper(Inode* node, int& total); // recursion to calculate size
	
	void emptybin();
	void showbin();
	void recover();
	
	void loadData();
	void quitProgram();
	void quit_helper(Inode* temp, ofstream& file); // recursion to iterate through all inodes
private:
	Queue<Inode*> myQueue = Queue<Inode*>(10);
	Inode* root = new Inode("", 0, TIME, true);
	Inode* curr_node = root;
	Inode* prev = curr_node; // keep track of prev inode
	Inode* temp; // dummy inode to use in the future
};
//===================================================
string Tree::path(Inode* node) {
	string s = "/";
	Stack<Inode*> st;
	temp = node;
	while(temp->parent != nullptr) { // pushing inode ancestorcs to the stack
		st.push(temp);
		temp = temp->parent;
	}
	while(st.size() != 0) { // creating path of the inode
		s += st.top()->name;
		st.pop();
		if (st.size() != 0)
			s += "/";
	}
	return s;
}
//===================================================
Inode* Tree::string_to_node(string file) {
	for (int i = 0; i < curr_node->children.size(); i++) {
		if (curr_node->children[i]->name == file) {
			return curr_node->children[i];
		}
	}
	throw runtime_error("No such file/folder!");
}
//===================================================
bool Tree::file_exists(string filename, Inode* node) {
	if(node->name == filename) {
		temp = node;
		return true;
	}
	for (int i = 0; i < node->children.size(); i++) // iterating through all children of the inode
		if (file_exists(filename, node->children[i]))
			return true;
	return false;
}
//===================================================
void Tree::file_exists_path(string filename, Inode* node, Vector<Inode*> *temp_Vector) {
	if(node->name == filename)
		temp_Vector->push_back(node); // pushing all inodes with the same name
	for (int i = 0; i < node->children.size(); i++)
		file_exists_path(filename, node->children[i], temp_Vector);
}
//===================================================
void Tree::pwd() {
	cout << path(curr_node) << endl;
}
//===================================================
string Tree::realpath(string filename) {
	bool flag = false;
	for (int i = 0; i < curr_node->children.size(); i++) {
		if(curr_node->children[i]->name == filename && !curr_node->children[i]->isFolder) { // saving the inode file to temp
			flag = true;
			temp = curr_node->children[i];
		}
	}
	if (!flag)
		throw runtime_error("File doesn't exist!");
	return path(temp); // getting the path of the file
}
//===================================================
void Tree::ls(string parameter) {
	Vector<Inode*> sort_vec;
	for (int i = 0; i < curr_node->children.size(); i++) // vec that holds all the children inodes
		sort_vec.push_back(curr_node->children[i]);
	if (parameter == "sort") {
		for (int i = 0; i < sort_vec.size() - 1; i++) { // bubble sort
			for (int j = i + 1; j < sort_vec.size(); j++) {
				if (sort_vec[i]->size < sort_vec[j]->size) {
					temp = sort_vec[i];
					sort_vec[i] = sort_vec[j];
					sort_vec[j] = temp;
				}
			}
		}
	}
	for (int i = 0; i < sort_vec.size(); i++) { // printing the inodes information
		if (sort_vec[i]->isFolder)
			cout << "dir ";
		else 
			cout << "file ";
		cout << sort_vec[i]->name << " ";
		cout << sort_vec[i]->date << " ";
		cout << sort_vec[i]->size << "bytes" << endl;
	}
}
//===================================================
void Tree::check_name(Inode* node, string file) {
	for (int i = 0; i < node->children.size(); i++)
		if (node->children[i]->name == file)
			throw runtime_error("Same name already exists!");
}
//===================================================
void Tree::mkdir(string foldername) {
	for (int i = 0; i < foldername.size(); i++)
		if (!isalnum(foldername[i])) // making sure folder is alphanumeric
			throw runtime_error("Not appropriate characters!");
	check_name(curr_node, foldername); // check if that folder already exists
	Inode* folder = new Inode(foldername, 10, TIME, true);
	curr_node->children.push_back(folder); // updating current directories children vector
	folder->parent = curr_node; // making current directory folder's parent
}
//===================================================
void Tree::touch(string filename, int size) {
	if (!contains(filename, '.'))
		throw runtime_error("File should have an extension!");
	for (int i = 0; i < filename.size(); i++)
		if (!isalnum(filename[i]) && filename[i] != '.') // making sure file is alphanumeric
			throw runtime_error("Not appropriate file name!");
	check_name(curr_node, filename);
	Inode* folder = new Inode(filename, size, TIME, false);
	curr_node->children.push_back(folder);
	folder->parent = curr_node;
}
//===================================================
void Tree::cd(string filename) {
	Inode* tmp = curr_node;
	if (filename == "..") {
		if (curr_node != root) // don't go over the root
			curr_node = curr_node->parent;
	}
	else if (filename == "-") {
		curr_node = prev;
	}
	else if (contains(filename, '.')) {
		throw runtime_error("Can't move into file!");
	}
	else if (!contains(filename, '/') && filename != "") { // cd into current directory's children
		for (int i = 0; i < curr_node->children.size(); i++) {
			if(curr_node->children[i]->name == filename)
				curr_node = curr_node->children[i];
		}
		if (tmp == curr_node)
			throw runtime_error("Folder doesn't exist!"); // if current directory didn't change throw error
	}
	else if (filename != "") { // cd into some arbiraty path
		Vector<string> f_path;
		string s = "";
		for (int i = 1; i <= filename.size(); i++) { // converting path to vector of strings
			if (filename[i] == '/' || i == filename.size()) {
				f_path.push_back(s);
				s = "";
			}
			else
				s += filename[i];
		}
		int j = 0;
		bool flag;
		temp = curr_node;
		while (j != f_path.size()) { // iterating until all nodes of the path are visited
			flag = true; // flag if path doesn't exist
			for (int i = 0; i < temp->children.size(); i++) {
				if (temp->children[i]->name == f_path[j]) {
					temp = temp->children[i]; // going inside the inode
					j++;
					flag = false;
					break;
				}
			}
			if (flag)
				throw runtime_error("No such path found!");
		}
		curr_node = temp;
	}
	else
		curr_node = root; // if simply cd
	prev = tmp; // updating prev inode
}
//===================================================
void Tree::find(string file) {
	Vector<Inode*> temp_Vector;
	if (!file_exists(file, root))
		throw runtime_error("File doesn't exist");
	file_exists_path(file, root, &temp_Vector); // all paths saving to temp vector
	for(int i = 0; i < temp_Vector.size(); i++)
		cout << path(temp_Vector[i]) << endl; // printing each path
}
//===================================================
void Tree::mv(string filename, string foldername) {
	Inode* tmp_file = string_to_node(filename); // converting string to node
	Inode* tmp_folder = string_to_node(foldername); // converting string to node
	if (tmp_file->isFolder)
		throw runtime_error("Can't move folder!");
	if (!tmp_folder->isFolder)
		throw runtime_error("Can't move into file!");
	check_name(tmp_folder,tmp_file->name);
	tmp_folder->children.push_back(tmp_file);
	tmp_file->parent = tmp_folder;
	for(int i = 0; i < curr_node->children.size(); i++) {
		if (curr_node->children[i]->name == tmp_file->name) {
			curr_node->children.erase(i); // deleting file from old folder
		}
	}
}
//===================================================
void Tree::rm(string file) {
	temp = string_to_node(file); // converting string to node
	for(int i = 0; i < curr_node->children.size(); i++) {
		if (curr_node->children[i]->name == temp->name) {
			myQueue.enqueue(temp); // adding node to the bin
			curr_node->children.erase(i); // deleting from folder
		}
	}	
}
//===========================================
int Tree::size_helper(Inode* temp, int& total) {
	total += temp->size; // recursively adding all sizes
	for (int i = 0; i < temp->children.size(); i++)
		size_helper(temp->children[i], total);
	return total;
}
//===========================================
int Tree::size(string file) {
	int total = 0;
	temp = string_to_node(file);
	return size_helper(temp, total);
}
//===========================================
void Tree::emptybin() {
	while (!myQueue.isEmpty())
		myQueue.dequeue();
}
//===========================================
void Tree::showbin() {
	if (myQueue.isEmpty()) {
		cout << "The bin is empty" << endl;
		return;
	}
	cout << "Next Element to remove: " << path(myQueue.front())
		 <<	" (" << myQueue.front()->size << " bytes, " 
		 << myQueue.front()->date << ")" << endl;
}
//===========================================
void Tree::recover() {
	bool flag;
	Stack<Inode*> st;
	temp = myQueue.front();
	while(temp->parent != nullptr) { // pushing inodes to the stack
		st.push(temp);
		temp = temp->parent;
	}
	while(st.size() != 1) { // iterating until we get to the inode we want to recover
		flag = false;
		for (int i = 0; i < temp->children.size(); i++) {
			if (temp->children[i]->name == st.top()->name) { // checking if path still exists
				temp = temp->children[i];
				flag = true;
				break;
			}
		}
		if(!flag)
			throw runtime_error("Path doesn't exists anymore!");
		st.pop();
	}
	check_name(temp,st.top()->name);
	temp->children.push_back(st.top()); // adding inode to the current folder
	myQueue.dequeue(); // removing it from the bin
}
//===========================================
void Tree::loadData() {
	ifstream file("vfs.dat");
	if (file.is_open()){
		string PATH, SIZE, DATE;
		while (file.good()) {
			getline(file, PATH, ',');
			getline(file, SIZE, ',');
			getline(file, DATE, '\n');

			if (PATH == "/")
				root->date = DATE; // if it's root than only updating time
			else {
				bool flag;
				Inode* new_node = new Inode("", 0, "", true); // creating new inode
				Vector<string> f_path;
				string s = "";
				
				curr_node = root;
				for (int i = 1; i <= PATH.size(); i++) { // saving it's path
					if (PATH[i] == '/' || i == PATH.size()) {
						f_path.push_back(s);
						s = "";
					}
					else
						s += PATH[i];
				}
				for (int i = 0; i < f_path.size(); i++) {
					flag = false;
					for (int j = 0; j < curr_node->children.size(); j++)
						if (curr_node->children[j]->name == f_path[i])
							flag = true;
					if (!flag) { // if the file hasn't been created yet then update its attributes
						new_node->name = f_path[i];
						new_node->size = stoi(SIZE);
						new_node->date = DATE;
						new_node->isFolder = !contains(f_path[i], '.');
						curr_node->children.push_back(new_node);
						new_node->parent = curr_node;
					}
					temp = string_to_node(f_path[i]);
					if (temp->isFolder)
						curr_node = temp; // moving to the next node
				}
			}
		}
		curr_node = root;
		file.close();
	}
}
//===========================================
void Tree::quit_helper(Inode* temp, ofstream& file) {
	for (int i = 0; i < temp->children.size(); i++) { // recursively saving all the data to the file
		file << path(temp->children[i]) << ","
			 << temp->children[i]->size << ","
			 << temp->children[i]->date << endl;
		quit_helper(temp->children[i], file);
	}
}
//===========================================
void Tree::quitProgram() {
	ofstream file("vfs.dat");
	if (file.is_open()){
		file << "/," << root->size << "," << root->date << endl; // saving the root information to the file
		quit_helper(root, file);
		file.close();
	}
}
//===========================================
void commands() {
	cout << "List of available Commands:" << endl
	<<"help                             	: Prints all the commands"<<endl
	<<"pwd                              	: Prints the path of the current inode"<<endl
	<<"realpath <filename>              	: Prints the full path of a given file"<<endl
	<<"ls                               	: Prints all the items of the current folder"<<endl
	<<"mkdir <foldername>               	: Creates a folder in the current folder"<<endl
	<<"cd <folder>                      	: Changes the location to the specified one"<<endl
	<<"find <foldername> or <filename>  	: Returns the path of the item"<<endl
	<<"mv <filename> <foldername>       	: Moves inode to the folder"<<endl
	<<"rm <foldername> or <filename>    	: Deletes the item"<<endl
	<<"size <foldername> or <filename>  	: Returns the total size"<<endl
	<<"emptybin                         	: Empties the bin"<<endl
	<<"showbin                          	: Shows the oldest deleted inode"<<endl
	<<"recover                          	: Recover the last inode"<<endl
	<<"exit                             	: Quit the Program"<<endl;
}
//===========================================
int main() {
	string user_input;
	string command;
	string parameter;
	string parameter_2;
	Tree* tree = new Tree;
	tree->loadData();
	
	cout << "Welcome wanderer!\n" << endl;
	commands();
	do
	{
		cout<<">";
		getline(cin,user_input);
		command = user_input.substr(0,user_input.find(" "));
		if (user_input.find(" ") > user_input.size()) // making sure that parametr doesn't equal the command
			parameter = "";
		else {
			parameter = user_input.substr(user_input.find(" ")+ 1);
			parameter_2 = parameter.substr(parameter.find(" ") + 1);
			parameter = parameter.substr(0, parameter.find(" "));
		}
		try {
			if(command=="help")				commands();
			else if(command=="pwd")			tree->pwd();
			else if(command=="realpath")	cout << tree->realpath(parameter) << endl;
			else if(command=="ls")			tree->ls(parameter);
			else if(command=="mkdir")		tree->mkdir(parameter);
			else if(command=="touch")		tree->touch(parameter, stoi(parameter_2));
			else if(command=="cd")			tree->cd(parameter);
			else if(command=="find")		tree->find(parameter);
			else if(command=="mv")			tree->mv(parameter, parameter_2);
			else if(command=="rm")			tree->rm(parameter);
			else if(command=="size")		cout << tree->size(parameter) << " bytes" << endl;
			else if(command=="emptybin")	tree->emptybin();
			else if(command=="showbin")		tree->showbin();
			else if(command=="recover")		tree->recover();
			else if(command=="exit") 		{tree->quitProgram(); break;}
			else 							cout<<"Invalid Commad !!"<<endl; }
		catch (exception &e) {cout<<"Exception: "<<e.what()<<endl;}
	} while(!(command == "exit"));
	return 0;
}