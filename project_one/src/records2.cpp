#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <functional>
#include <tuple>
#include <vector>
#include <list>

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

struct MenuBuilder;
struct Menu {
    Menu() {}
    Menu(MenuBuilder*);

    void operator() () {
        m_page(this);
    }

    string title() { return this->m_title; }
    string stitle() { return this->m_stitle; }
    vector<Menu>* sub_menus() { return &this->m_sub_menus; }
    Menu* get_sub(int idx) { return &this->m_sub_menus[idx]; }
    function<void(Menu*)>* user_input() { return &this->m_user_input; }
    
    void for_each(function<void(Menu)> fn) {
        for(Menu sub: m_sub_menus) {
            fn(sub);
        }
    }

    private:
    string m_title;
    string m_stitle;
    vector<Menu> m_sub_menus;
    function<void(Menu*)> m_user_input;
    function<void(Menu*)> m_page;
};

struct MenuBuilder {

    static MenuBuilder* create() { return new MenuBuilder; }
    MenuBuilder* title(string);
    MenuBuilder* page_fn(function<void(Menu*)>); 
    MenuBuilder* input_fn(function<void(Menu*)>);
    MenuBuilder* sub_menu(Menu);
    MenuBuilder* stitle(string);
    Menu build();

    string title() { return this->m_title; }
    string stitle() { return this->m_stitle; }
    vector<Menu>* sub_menus() { return &this->m_sub_menus; }
    function<void(Menu*)>* user_input() { return &this->m_user_input; }
    function<void(Menu*)>* page() { return &this->m_page; }
    
    private:
    string m_title{""};
    string m_stitle{""};
    vector<Menu> m_sub_menus;
    function<void(Menu*)> m_page{[](Menu*){}};
    function<void(Menu*)> m_user_input{[](Menu*){}};
};

MenuBuilder* MenuBuilder::title(string title) {
    this->m_title = std::move(title);
    return this;
}

MenuBuilder* MenuBuilder::page_fn(function<void(Menu*)> fn) {
    this->m_page = std::move(fn);
    return this;
}

MenuBuilder* MenuBuilder::input_fn(function<void(Menu*)> fn) {
    this->m_user_input = std::move(fn);
    return this;
}

MenuBuilder* MenuBuilder::sub_menu(Menu menu) {
    m_sub_menus.push_back(std::move(menu));
    return this;
}

MenuBuilder* MenuBuilder::stitle(string stitle) {
    this->m_stitle = std::move(stitle);
    return this;
}

Menu MenuBuilder::build() {
    Menu temp;
    temp = this;
    delete this;
    return temp;
}

Menu::Menu(MenuBuilder* builder) {
        this->m_title = builder->title();
        this->m_stitle = builder->stitle();
        this->m_sub_menus = *builder->sub_menus();
        this->m_page = *builder->page();
        this->m_user_input = *builder->user_input();
};

template<typename T>
bool check_input(T response, vector<T> &args) {
    for(T arg: args) {
        if(arg == response) return true;
    }

    return false;
}

template<typename T, typename... S>
void get_input(T &response, T arg,  S... args) {
    vector<T> vec{arg, args...};
    do {
        cin >> response;

        if(!check_input(response, vec)) {
            printf("Input not recognized, please try again\n> ");
        }
    } while(!check_input(response, vec));
}

int main() {
    bool exit = false;
    list<Student> student_list;

    Menu add_menu = MenuBuilder::create()
        ->stitle("\033[31mA\033[0mdd Record\n")
        ->title("   -- Add Record --\n")
        ->page_fn([](Menu* menu) {
            system("clear");

            printf("%s\n", menu->title().c_str());
        
            (*menu->user_input())(menu);
        })
        ->input_fn([&](Menu* menu){
            system("clear");
            
            Student student;

            printf("Enter FIRST name\n> ");
            string response;
            cin >> response;
            student.first_name = response;

            printf("Enter LAST name\n> ");
            cin >> response;
            student.last_name = response;

            printf("Enter CLASS\n> ");
            int response2;
            cin >> response2;
            student.grade = response2;

            printf("Enter Age\n> ");
            cin >> response2;
            student.age = response2;

            printf("Enter ID\n> ");
            cin >> response2;
            student.id = response2;

            system("clear");

            student.display();
            
            char response3;
            printf("Do you want to add this student? (y/n)\n> ");
            get_input(response3, 'y', 'n', 'Y', 'N');

            switch (response3) {
                case 'y':
                    //student_list.push_back(std::move(student));
                    printf("Student added\n");
                    break;
                case 'Y':
                    //student_list.push_back(std::move(student));
                    printf("Student added\n");
                    break;
                default:
                    printf("Student not added");
                    break;
            }

            system("clear");
        })
        ->build();
    
    Menu remove_menu = MenuBuilder::create()
        ->stitle("\033[31mR\033[0memove Record\n")
        ->build();
    
    Menu update_menu = MenuBuilder::create()
        ->stitle("\033[31mU\033[0mpdate Record\n")
        ->build();
    
    Menu display_menu = MenuBuilder::create()
        ->stitle("\033[31mD\033[0misplay Record\n")
        ->build();

    Menu exit_menu = MenuBuilder::create()
        ->stitle("\033[31mE\033[0mxit\n")
        ->page_fn([&exit](Menu*){
            exit = true;
        })
        ->build();

    Menu main_menu = MenuBuilder::create()
        ->title("   -- Main Menu --\n")
        ->page_fn([](Menu* menu){
            system("clear");

            printf("%s", menu->title().c_str());
            menu->for_each([](Menu sub){
                printf("%s", sub.stitle().c_str());        
            });

            (*menu->user_input())(menu);
        })
        ->input_fn([](Menu* menu){
            printf("\nChoose an option\n> ");
            char response;
            get_input(response, 'a', 'r', 'u', 'd', 'e');
            response = tolower(response);

            switch(response) {
                case 'a':
                    (*menu->get_sub(0))();
                    break;
                case 'r':
                    (*menu->get_sub(1))();
                    break;
                case 'u':
                    (*menu->get_sub(2))();
                    break;
                case 'd':
                    (*menu->get_sub(3))();
                    break;
                case 'e':
                    (*menu->get_sub(4))();
                    break;
            }

            system("clear");
        })
        ->sub_menu(add_menu)
        ->sub_menu(remove_menu)
        ->sub_menu(update_menu)
        ->sub_menu(display_menu)
        ->sub_menu(exit_menu)
        ->build();

    while(!exit) main_menu();
    
    return 0;
}
