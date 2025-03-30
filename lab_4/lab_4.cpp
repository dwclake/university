/*
 Devon Webb CSCI 41
 lab_4.cpp
*/

#include <string>
#include <iostream>

class Movie {
public:
    Movie();
    Movie(int, std::string, std::string);
    int get_date() {return this->date;}
    void set_date(int year) {this->date = year;}
    std::string get_title() {return this->title;}
    void set_title(std::string title) {this->title = title;}
    std::string get_genre() {return this->genre;}
    void set_genre(std::string genre) {this->genre = genre;}
private:
    int date{ 0 };
    std::string title{ " " };
    std::string genre{ " " };
};

Movie::Movie() {
}

Movie::Movie(int year, std::string title, std::string genre) {
    this->date = year;
    this->title = title;
    this->genre = genre;
}

class Movies {
public:
    Movies();
    ~Movies();
    void add_movie(Movie);
    void remove_movie(int);
    void search_by_year(); // Display all that match
    void search_by_title(); // Display all that match
    void search_by_genre(); // Display all that match
    void sort_by_year();
    void sort_by_title();
    void sort_by_genre();
    void display_movies();
    
private:
    Movie* movies;
    int num_of_movies{ 0 };
};

Movies::Movies() {
    movies = nullptr;
}

Movies::~Movies() {
    delete[] movies;
}

void Movies::add_movie(Movie movie) {
    Movie* temp = new Movie[num_of_movies + 1];
    for (int i = 0; i < num_of_movies; i++) {
        temp[i] = movies[i];
    }
    temp[num_of_movies] = movie;
    movies = temp;
    num_of_movies++;
}

void Movies::display_movies() {
    for (int i = 0; i < num_of_movies; i++) {
        Movie movie = movies[i];
        std::cout << movie.get_date() << " : " << movie.get_title() << " : " << movie.get_genre() << std::endl;
    }
}

int main() {
    Movies my_movies;
    Movie fast_and_furious(
            2001,
            "The Fast and the Furious",
            "Action"
    );
    Movie fast_and_furious2(
            2003,
            "2 Fast 2 Furious",
            "Action"
    );
    my_movies.add_movie(fast_and_furious);
    my_movies.add_movie(fast_and_furious2);
    
    my_movies.display_movies();
    return 0;
}