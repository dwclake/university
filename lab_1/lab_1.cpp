#include <string>
#include <iostream>
#include <cmath>

using namespace std;

bool check_if_even_if( int number ) {
    if ((number % 2) == 0) {
        return true;
    } else {
        return false;
    }
}

bool check_if_even_tertiary( int number ) {
    bool is_even;
    ((number % 2) == 0)? ( is_even = true ) : ( is_even = false );
    
    return is_even;
}

string get_month_string_with_if( int month_number ) {
    if (month_number == 1) {
        return "January";
    } else if (month_number == 2) {
        return "February";
    } else if (month_number == 3) {
        return "March";
    } else if (month_number == 4) {
        return "April";
    } else if (month_number == 5) {
        return "May";
    } else if (month_number == 6) {
        return "June";
    } else if (month_number == 7) {
        return "July";
    } else if (month_number == 8) {
        return "August";
    } else if (month_number == 9) {
        return "September";
    } else if (month_number == 10) {
        return "October";
    } else if (month_number == 11) {
        return "November";
    } else if (month_number == 12) {
        return "December";
    }
}

string get_month_string_with_switch( int month_number ){
    string month;
    switch ( month_number ) {
        case 1:
            month = "January";
            break;
        case 2:
            month = "February";
            break;
        case 3:
            month = "March";
            break;
        case 4:
            month = "April";
            break;
        case 5:
            month = "May";
            break;
        case 6:
            month = "June";
            break;
        case 7:
            month = "July";
            break;
        case 8:
            month = "August";
            break;
        case 9:
            month = "September";
            break;
        case 10:
            month = "October";
            break;
        case 11:
            month = "November";
            break;
        case 12:
            month = "December";
            break;
        default:
            break;
    }
    return month;
}

float sum_1_for( int n ) {
    float sum{0.0};
    
    for (int i{1}; i <= n; i++) {
        sum += float( i ) / float( i + 1 );
    }
    return sum;
}

float sum_1_while( int n ) {
    float sum{0.0};
    
    n--;
    while (n > 0) {
        sum += float( n ) / float( n + 1 );
        n--;
    }
    
    return sum;
}

int sum_2_for( int n ) {
    int sum{0};
    
    for (int i{1}; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            sum += i * j;
        }
    }
    return sum;
}

int sum_2_while( int n ) {
    int sum{0};
    int i = n;
    int j = i;
    
    while (i > 0) {
        while (j > 0) {
            sum += i * j;
            j--;
        }
        i--;
        j = i;
    }
    
    return sum;
}

double sum_3_for( int n ){
    double sum{0.0};
    
    for (int i{1}; i <= n; i++) {
        for (int j{1}; j <= n; j++) {
            for (int k{1}; k <= n; k++) {
                sum += double( 1 ) / sqrt( i + j + k);
            }
        }
    }
    
    return sum;
}

double sum_3_while( int n ){
    double sum{0.0};
    int i{1};
    int j{1};
    int k{1};
    
    while (i <= n) {
        while (j <= n) {
            while (k <= n) {
                sum += double( 1 ) / sqrt( i + j + k );
                k++;
            }
            j++;
            k = 1;
        }
        i++;
        j = 1;
    }
    
    return sum;
}

int sum_4_for( int n ){
    int sum_j{0};
    int sum_i{1};
    
    for (int j{1}; j <= n; j++) {
        sum_j += j;
    }
    
    for (int i{1}; i <= n; i++) {
        sum_i *= ( i * sum_j );
    }
    
    return sum_i;
}

int sum_4_while( int n ){
    int sum_j{0};
    int sum_i{1};
    int i{1};
    int j{1};
    
    while (j <= n) {
        sum_j += j;
        j++;
    }
    
    while (i <= n) {
        sum_i *= ( i * sum_j );
        i++;
    }
    
    return sum_i;
}

int sum_5_for( int n ){
    int sum{0};
    
    for (int i{1}; i <= n; i++) {
        if ( check_if_even_if(i) ) {
            sum += 9;
        } else {
            sum += 4;
        }
    }
    
    return sum;
}

int sum_5_while( int n ){
    int sum{0};
    int i{1};
    
    while (i <= n) {
        if ( check_if_even_tertiary(i) ) {
            sum += 9;
        } else {
            sum += 4;
        }
        
        i++;
    }
    
    return sum;
}

int main() {
    bool is_even_if = check_if_even_if( 4 );
    cout << is_even_if << endl << endl;
    
    bool is_even_tertiary = check_if_even_tertiary( 5 );
    cout << is_even_tertiary << endl << endl;
    
    string month_if = get_month_string_with_if( 3 );
    cout << month_if << endl << endl;
    
    string month_switch = get_month_string_with_switch( 12 );
    cout << month_switch << endl << endl;
    
    float first_sum_for = sum_1_for( 10 );
    cout << first_sum_for << endl;
    first_sum_for = sum_1_for( 100 );
    cout << first_sum_for << endl;
    first_sum_for = sum_1_for( 1000 );
    cout << first_sum_for << endl << endl;
    
    float first_sum_while = sum_1_while( 10 );
    cout << first_sum_while << endl;
    first_sum_while = sum_1_while( 100 );
    cout << first_sum_while << endl;
    first_sum_while = sum_1_while( 1000 );
    cout << first_sum_while << endl << endl;
    
    int second_sum_for = sum_2_for( 10 );
    cout << second_sum_for << endl;
    second_sum_for = sum_2_for( 100 );
    cout << second_sum_for << endl;
    second_sum_for = sum_2_for( 1000 );
    cout << second_sum_for << endl << endl;
    
    int second_sum_while = sum_2_while( 10 );
    cout << second_sum_while << endl;
    second_sum_while = sum_2_while( 100 );
    cout << second_sum_while << endl;
    second_sum_while = sum_2_while( 1000 );
    cout << second_sum_while << endl << endl;
    
    double third_sum_for = sum_3_for( 10 );
    cout << third_sum_for << endl;
    third_sum_for = sum_3_for( 100 );
    cout << third_sum_for << endl;
    third_sum_for = sum_3_for( 1000 );
    cout << third_sum_for << endl << endl;
    
    double third_sum_while = sum_3_while( 10 );
    cout << third_sum_while << endl;
    third_sum_while = sum_3_while( 100 );
    cout << third_sum_while << endl;
    third_sum_while = sum_3_while( 1000 );
    cout << third_sum_while << endl << endl;
    
    int fourth_sum_for = sum_4_for( 10 );
    cout << fourth_sum_for << endl;
    fourth_sum_for = sum_4_for( 100 );
    cout << fourth_sum_for << endl;
    fourth_sum_for = sum_4_for( 1000 );
    cout << fourth_sum_for << endl << endl;
    
    int fourth_sum_while = sum_4_while( 10 );
    cout << fourth_sum_while << endl;
    fourth_sum_while = sum_4_while( 100 );
    cout << fourth_sum_while << endl;
    fourth_sum_while = sum_4_while( 1000 );
    cout << fourth_sum_while << endl << endl;
    
    int fifth_sum_for = sum_5_for( 10 );
    cout << fifth_sum_for << endl;
    fifth_sum_for = sum_5_for( 100 );
    cout << fifth_sum_for << endl;
    fifth_sum_for = sum_5_for( 1000 );
    cout << fifth_sum_for << endl << endl;
    
    int fifth_sum_while = sum_5_while( 10 );
    cout << fifth_sum_while << endl;
    fifth_sum_while = sum_5_while( 100 );
    cout << fifth_sum_while << endl;
    fifth_sum_while = sum_5_while( 1000 );
    cout << fifth_sum_while << endl << endl;
}