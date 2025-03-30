#include <iostream>
#include <cstdio>
#include <random>

using namespace std;

// Holds the students attributes.
struct Student {
    string first_name;
    string last_name;
    unsigned int grade;
    unsigned int age;
    unsigned int id; // ID 0 is used as a sentinel value when a student was  not found.

    Student(): id(0) {}
    Student(unsigned int i): id(i) {}
    Student(string fn, string ln, unsigned int g, uint8_t a, uint8_t i): first_name(fn), 
                                                                         last_name(ln), 
                                                                         grade(g), 
                                                                         age(a), 
                                                                         id(i) {}
    // Copy Constructor.
    Student(Student &student) {
        first_name = student.first_name;
        last_name = student.last_name;
        grade = student.grade;
        age = student.age;
        id = student.id;
    }

    void display(bool);
};

// Prints out the students info, if red is true, the text is printed in red.
void Student::display(bool red = false) {
    if (red) {
        printf("\033[31mFirst Name : %s \033[0m\n", this->first_name.c_str());
        printf("\033[31mLast Name  : %s \033[0m\n", this->last_name.c_str());
        printf("\033[31mGrade      : %d \033[0m\n", this->grade);
        printf("\033[31mAge        : %d \033[0m\n", this->age);
        printf("\033[31mID Number  : %d \033[0m\n\n", this->id);
    } else {
        printf("First Name : %s \n", this->first_name.c_str());
        printf("Last Name  : %s \n", this->last_name.c_str());
        printf("Grade      : %d \n", this->grade);
        printf("Age        : %d \n", this->age);
        printf("ID Number  : %d \n\n", this->id);
    }
}

struct Node {
    Node* next;
    Node* prev;
    Student student;

    Node(): next(nullptr), prev(nullptr) {}
    Node(Student data): next(nullptr), prev(nullptr), student(data) {}
};

class List {
    Node* head;
    Node* tail;
    int size;
    public:
    List(): head(nullptr), tail(nullptr), size(0) {}
    ~List();

    void insert(Student);
    void remove(unsigned int);
    Student* fetch(unsigned int); // Returns a pointer to the student struct.
                                  // that matches ID passed in.
    void sort();
    void print();                 // Prints out each student in the list.
    bool check_id(unsigned int);            // Checks if the ID entered as a argument 
                                            // exists in the list already.
    unsigned int generate_id();             // Generates a random ID.
    Node* get_head() { return this->head; }
    Node* get_tail() { return this->tail; }
    int get_size() { return this->size; }
};

// Destructor
List::~List() {
    Node* temp = this->head;
    while (temp != this->tail) { // While temp does not equal tail, iterate and delete temp.
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    delete temp; // Deletes the tail.
}

// Prints out all students in the list.
void List::print() {
    if (this->size == 0) return;

    Node* current = this->head;
    do {    // Iterates through the list and displays student.
        current->student.display();
        current = current->next;
    } while(current != this->head);
}

// Swaps two students attributes.
void swap(Student &one, Student &two) {
    Student tmp = one;
    one = two;
    two = tmp;
}

// Moves all students with ID's  smaller than the pivot to the left.
Node* partition(Node* lo, Node* hi) {
    Node* i = lo->prev;
    unsigned int pivot = hi->student.id;
    Node* j = lo;

    while (j != hi) {
        if (j->student.id < pivot) {
            if (i == nullptr) {
                i = lo;
            } else {
                i = i->next;
            }
            
            swap(j->student,i->student);
        }
        j = j->next;
    }
    if (i == nullptr) {
        i = lo;
    } else {
        i = i->next;
    }
    
    swap(i->student, hi->student);
    return i;
}

// Sorts list based on the ID of the students, in asscending order.
void quicksort(Node* lo, Node* hi) {
    if (hi != nullptr && lo != hi && lo != hi->next) {

        Node* pivot = partition(lo, hi); // Partition and get pivot.
        quicksort(lo, pivot->prev); // Sort from lo up to but not including pivot.
        quicksort(pivot->next, hi); // Sort from the node after the pivot to hi.
    }        
}

// Wrapper function around quicksort that automatically starts lo and hi as head and tail.
//      Also temporarily breaks the link between head and tail so that loops can loop 
// until they find a nullptr.
void List::sort() {
    Node* lo = this->head;
    Node* hi = this->tail;
    lo->prev = nullptr;
    hi->next = nullptr;
    
    quicksort(lo, hi);
    
    this->head->prev = this->tail;
    this->tail->next = this->head;
}
        
// Generates a random ID, loops until a ID which doesn't already 
// exist in the list is picked.
unsigned int List::generate_id() {
    default_random_engine generator(time(nullptr));
    uniform_int_distribution<unsigned int> distribution;
    
    unsigned int id;
    do {
        id = distribution(generator);
    } while(this->check_id(id)); // If ID aready exists, continue loop.

    return id;
};

// Checks if ID already exists.
bool List::check_id(unsigned int id) {
    if (this->size == 0) return false;

    Node* current = this->head;

    do { // Loops through list and returns true if a match is found.
        if (current->student.id == id) { return true; }
        current = current->next;
        
    } while(current != this->head);

    return false; // Returns false if no match is found.
}

// Adds a student to the list
void List::insert(Student student) { 
    if (this->size == 0) { // If list is empty, new student is both 
                           // the head and the tail.
        this->head = new Node(student);
        this->tail = this->head;

        this->head->prev = this->tail;
        this->tail->next = this->head;
    
        this->size++;
    } else { // If list not empty, adds student to the end of the list.
        Node* tmp = new Node(student);
        
        this->head->prev = tmp;
        tmp->next = this->head;
        this->head = tmp;

        this->head->prev = this->tail;
        this->tail->next = this->head;

        this->size++;
    }
} 

// Removes a student from the list.
void List::remove(unsigned int id) {
    if (this->size == 0) { // If list is empty, there is nothing that can be removed.
        printf("Cannot remove student, list is empty.\n");
    } else if(this->size == 1) { // If list has only one student, 
                                 // then it is both head and tail.
        Node* temp = this->head;
        this->head = nullptr;
        this->tail = nullptr;

        delete temp;
        this->size--;
    } else { // Otherwise iterate through list until student is found.
        Node* current = this->head;

        do { // Loops through list to look for a match.
            if (current->student.id == id) {
                if (current == this->head) { // If current is head, set second 
                                             // in list as new head.
                    current->next->prev = this->tail;
                    this->tail->next = current->next;
                    this->head = current->next;
                    
                    delete current;
                    this->size--;
                    return;
                } else if (current == this->tail) { // If current is tail, set second last 
                                                    // as new tail and delete current.
                    current->prev->next = this->head;
                    this->head->prev = current->prev;
                    this->tail = current->prev;

                    delete current;
                    this->size--;
                    return;
                } else { // Otherwise link the students one before and one after to 
                         // eachother and delete current.
                    current->next->prev = current->prev;
                    current->prev->next = current->next;

                    delete current;
                    this->size--;
                    return;
                }
            }
            current = current->next;
        } while (current != this->head);
    }
}

// TODO: implement binary search
// Returns pointer to the student with matching ID.
Student* List::fetch(unsigned int id) {
    if (this->size == 0) return nullptr; // If list empty, return nullptr.
    Node* current = this->head;

    do {
        if (current->student.id == id) {
            return &current->student;
        }
        current = current->next;

    } while(current != this->head);

    return nullptr; // Student was not found so return nullptr
}

// Menu for adding a student to the list.
void add_menu(List* student_list) {
    
    printf("   -- Add Menu --\n");

    // Get first name and convert to lowercase, with first letter capitalized.
    printf("Enter Student's FIRST Name\n> ");
    string first_name;
    cin >> first_name;
    for (char &c : first_name) {
        c = tolower(c);
    }
    first_name[0] = toupper(first_name[0]);

    // Get last name and convert to lowercase, with first letter capitalized.
    printf("Enter Student's LAST Name\n> ");
    string last_name;
    cin >> last_name;
    for (char &c : last_name) {
        c = tolower(c);
    }
    last_name[0] = toupper(last_name[0]);

    // Get grade/year in school.
    printf("Enter Student's GRADE (1-12)\n> ");
    unsigned int grade;
    cin >> grade;
    // Prompts user to enter a grade between 1-12.
    while(grade > 12 || grade == 0) {
        printf("Grade must be 1-12, please try again\n> ");
        cin >> grade;
    }

    // Get age.
    printf("Enter Student's AGE\n> ");
    unsigned int age;
    cin >> age;
    // Prompts user to enter a age greater than 0.
    while(age == 0) {
        printf("Age must be greater than 0, please try again\n> ");
        cin >> age;
    }
    
    // Generates a unique ID for new student.
    unsigned int id = student_list->generate_id();
    
    // Creates new student object with entered information
    Student new_student(first_name, last_name, grade, age, id);
    system("clear");
    // Displays new student to user
    printf("    -- Add Menu --\n");
    new_student.display();
    
    // Prompts user whether to add the student created or not, incase mistakes were made.
    char answer;
    do {
        printf("ADD this student? (y/n)\n> ");
        cin >> answer;
        answer = tolower(answer);

        switch (answer) {
            case 'y': // If user enters y, add the student to the list, then sort.
                student_list->insert(new_student);
                student_list->sort();
                printf("Student added.\n\n");
                break;
            case 'n': // If user enters n, do not add student.
                printf("Student not added.\n\n");
                break;
            default: // else input is not recognized so prompts user for another try.
                printf("Input not recognized, try again\n\n");
                break;
        }
    } while (answer != 'n' && answer != 'y');
    
    // Waits for the user to hit enter.
    printf("Press ENTER to continue");
    while(getchar() !='\n'); // clears input buffer so any previous '\n' wont end next loop prematurely
    while(cin.get() !='\n'); // loops until user hits enter

    system("clear");

}

// Menu for removing students from list.
void remove_menu(List* student_list) {
    printf("   -- Remove Menu --\n");
    // Gets the ID of the student to be removed.
    printf("Enter the ID of the STUDENT to REMOVE\n> ");
    unsigned int id;
    cin >> id;
    
    Student* student;
    // Loops until the user enters an ID which exists in the list.
    while(!student_list->check_id(id)) {
        system("clear");
        printf("   -- Remove Menu --\n");
        printf("ID does not exist, try again or enter 0 to go to menu\n> ");
        cin >> id;
        if(id == 0) break; // If user enters 0, break the loop.
    }

    if(id != 0) { // If ID entered is not 0, get the student from the list and display it.
        student = student_list->fetch(id);
        student->display();
    } else { // If ID entered is 0, return early to go back to menu.
        system("clear");
        return;
    }
   
    // Prompt user whether to delete the student chosen.
    char answer;
    do {
        printf("DELETE this student? (y/n)\n> ");
        cin >> answer;
        answer = tolower(answer);

        switch (answer) {
            case 'y': // If user answered y, removed student.
                student_list->remove(id);
                printf("Student successfully removed.\n\n");
                break;
            case 'n': // If user answered n, do not remove student.
                printf("Student not removed.\n\n");
                break;
            default: // If input not recognized, prompt user to try again.
                printf("Input not recognized, try again\n\n");
                break;
        }
    } while (answer != 'n' && answer != 'N' && answer != 'y' && answer != 'Y');
    
    // Wait until user hits enter.
    printf("Press ENTER to continue");
    while(getchar() !='\n'); // clears input buffer so any previous '\n' wont end next loop prematurely
    while(cin.get() !='\n'); // loops until user hits enter

    system("clear");
}

// Menu to update a student record.
void update_menu(List* student_list) {
    printf("   -- Update Menu --\n");

    // Get ID of student to edit.
    printf("Enter the ID of the STUDENT to EDIT\n> ");
    unsigned int student_id;
    cin >> student_id;
    
    while(!student_list->check_id(student_id)) {
        system("clear");
        printf("   -- Update Menu --\n");
        printf("Student not found, please try again, or enter 0 to return to menu\n> ");
        cin >> student_id;

        if(student_id == 0) { // If user enters zero, return to menu,
            system("clear");
            return;
        }
    }
    Student* student = student_list->fetch(student_id);

    string response;
    string first_name;
    string last_name;
    unsigned int grade;
    unsigned int age;

    student->display(); // Display students current attributes.

    // Promt user to enter new first name, or keep it the same.
    printf("ENTER new FIRST name (ENTER 0 to keep the same)\n> ");
    cin >> response;
    for (char &c : response) {
        c = tolower(c);
    }
    response[0] = toupper(response[0]);

    if (response != "0") { // If user enters a new name, store the string.
        first_name = response;        
    } else { // If user enters 0, use students current first name.
        first_name = student->first_name;
    }

    // Prompt user to enter a new last name, or keep it the same.
    printf("ENTER new LAST name (ENTER 0 to keep the same)\n> ");
    cin >> response;
    for (char &c : response) {
        c = tolower(c);
    }
    response[0] = toupper(response[0]);

    if (response != "0") { // If user enters a new name, store it.
        last_name = response;
    } else { // If user enters zero, use students current name;
        last_name = student->last_name;
    }

    // Prompt user to enter new grade, or keep it the same.
    unsigned int num_response;
    printf("ENTER new GRADE (1-12, enter 0 to keep the same)\n> ");
    cin >> num_response;

    if (num_response != 0) { // If user doesn't enter 0, check that entered grade is valid.
        while(num_response > 12) {
            printf("Grade must be between 1-12, please try again\n> ");
            cin >> num_response;
        }
        grade = num_response;
    } else { // If user entered 0, use students current grade.
        grade = student->grade;
    }
    
    // Prompt user to enter new age, or keep it the same.
    printf("ENTER new Age (ENTER 0 to keep the same)\n> ");
    cin >> num_response;

    if (num_response != 0) { // If user doesn't enter 0, store that age.
        age = num_response;
    } else {
        age= student->age; // If user enters 0, use students current age.
    }

    system("clear");

    // Create temporary student object using entered data.
    Student temp;
    temp.first_name = first_name;
    temp.last_name = last_name;
    temp.grade = grade;
    temp.age = age;
    temp.id = student->id;
    
    // Display current student in the list and new student to show changes.
    printf("   -- Update Menu --\n");
    printf("Original student:\n");
    student->display();
    printf("Student with changes shown:\n");
    temp.display();
    
    // Prompt user to save the changes made or not.
    char answer;
    do {
        printf("SAVE these changes? (y/n)\n> ");
        cin >> answer;
        answer = tolower(answer);

        switch (answer) {
            case 'y': // If user enters y, update student in list.
                student->first_name = temp.first_name;
                student->last_name = temp.last_name;
                student->age = temp.age;

                printf("Student edited successfully.\n\n");
                break;
            case 'n': // If user enters n, do not update student in list.
                printf("Changes not saved.\n\n");
                break;
            default: // If input unrecognized, prompt user to try again.
                printf("Input not recognized, try again\n\n");
                break;
        }
    } while (answer != 'n' && answer != 'y');
    
    // Wait for uer to hit enter.
    printf("Press ENTER to continue");
    while(getchar() !='\n'); // clears input buffer so any previous '\n' wont end next loop prematurely
    while(cin.get() !='\n'); // loops until user hits enter

    system("clear");
}

// Displays one student at a time, allowing user to traverse list forwards and backwards.
void display_menu(List* student_list) {
    // If list is empty, inform user and return to menu.
    if (student_list->get_size() == 0) {

        printf("   -- Display Menu --\n");
        printf("No records to view, records are empty.\n\n");

        printf("Press ENTER to continue");
        while(getchar() !='\n'); // clears input buffer so any previous '\n' wont end next loop prematurely.
        while(cin.get() !='\n'); // loops until user hits enter.

        system("clear");
        return;
    }

    // Create pointer to currently displayed student, starting at the head.
    Node* current = student_list->get_head();
    bool go_to_menu = false; // Indicates whether the user has chosen to leave menu.
    bool finished_loop = false; // Indicates that the user had returned to the head.

    // Loop while user hasn't chosen to go to menu
    while (!go_to_menu) {
        printf("   -- Display Menu --\n");
        current->student.display(finished_loop); // Display current student, if finished_loop is true,
                                                 // will be displayed in red.

        // Prompt user to choose between next, prev, or menu.
        printf("Enter P for previous, N for next, M to return to menu (p/n/m)\n> ");
        char response = cin.get();
        response = tolower(response);

        switch (response) {
            case 'n': // If user enters n, go to next student.
                current = current->next;
                if (current == student_list->get_head()) { // If the student switched to
                                                           // is the head, set finished_loop
                                                           // to true.
                    finished_loop = true;
                } else {
                    finished_loop = false;
                }
                break;
            case 'p': // If user enters p, go to prev student.
                current = current->prev;
                if (current == student_list->get_head()) { // If the student switched to
                                                           // is the head, set finished_loop
                                                           // to true.
                    finished_loop = true;
                } else {
                    finished_loop = false;
                }
                break;
            case 'm': // If user entered m, return to menu.
                go_to_menu = true;
                break;
            default: // If input unrecognized, do nothing.
                break;
        }
        system("clear");
    }
}

// Main Menu which shows all the options available to the user.
void main_menu(List* student_list,bool &exit) {
    // Print out the sub menus available to the student.
    printf("    -- Main Menu --\n");
    printf("\033[31mA\033[0mdd Record\n");
    printf("\033[31mR\033[0memove Record\n");
    printf("\033[31mU\033[0mpdate Record\n");
    printf("\033[31mD\033[0misplay Record\n");
    printf("\033[31mE\033[0mxit\n\n");
    
    // Prompt user to choose a sub menu;
    printf("Choose an option\n> ");
    char response;
    cin >> response;; 
    response = towlower(response);

    // Go to the sub menu chosen.
    switch (response) {
        case 'a':
            system("clear");
            add_menu(student_list);
            break;
        case 'r':
            system("clear");
            remove_menu(student_list);
            break;
        case 'u':
            system("clear");
            update_menu(student_list);
            break;
        case 'd':
            system("clear");
            display_menu(student_list);
            break;
        case 'e':
            system("clear");
            exit = true;
            break;
        default: // If input not recognized just clear screen.
            system("clear");
            break;
    }
}

int main() {
    bool exit = false;
    List* student_list = new List;

    while (!exit) { // Loop while exit is false.
        system("clear");
        main_menu(student_list, exit);
    }
    delete student_list; // Free memory allocated for student_list.
    return 0;
}
