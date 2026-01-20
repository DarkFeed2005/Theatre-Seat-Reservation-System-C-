#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <ctime>
using namespace std;


struct Show {
    string showname;
    string date;
    string time;
    string gate;
    double price;
};

struct Seat {
    string name;
    int booking_ID;
    int seats;
    char row;
    int col;
    bool isBooked;
    int showIndex; 
};


Show shows[5] = {
    {"Dune: Part Two", "15-03-2024", "18:00", "1", 12.50},
    {"Oppenheimer", "20-03-2024", "20:30", "2", 15.00},
    {"Barbie", "22-03-2024", "19:00", "3", 12.00},
    {"Deadpool & Wolverine", "25-03-2024", "21:00", "4", 14.50},
    {"Inside Out 2", "28-03-2024", "17:30", "5", 11.00}
};

Seat theater[5][4][5]; 
int booking_ID = 1000;
int currentShow = 0;

void initializeTheater();
void displayMainMenu();
void selectShow();
void displayShowMenu();
void booking();
void cancelBooking();
void viewSeats();
void viewRecords();
void generateTicket(int row, int col);
void saveTicketToFile(int row, int col);
void displayBanner();
string getCurrentDateTime();


int main() {
    initializeTheater();
    displayMainMenu();
    return 0;
}

void initializeTheater() {
    for (int s = 0; s < 5; s++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                theater[s][i][j].isBooked = false;
                theater[s][i][j].row = 'A' + i;
                theater[s][i][j].col = j + 1;
                theater[s][i][j].booking_ID = 0;
                theater[s][i][j].seats = 0;
                theater[s][i][j].showIndex = s;
            }
        }
    }
}

void displayBanner() {
    cout << "\n";
    cout << "\t================================================\n";
    cout << "\t    PREMIUM THEATRE SEAT RESERVATION SYSTEM    \n";
    cout << "\t================================================\n";
}

void displayMainMenu() {
    system("clear || cls");
    displayBanner();
    
    cout << "\n\t+--------------------------------------------+\n";
    cout << "\t|        MAIN MENU - SELECT OPTION           |\n";
    cout << "\t+--------------------------------------------+\n";
    cout << "\t|  1 -> Select Movie & Show Time             |\n";
    cout << "\t|  2 -> Book Seats                           |\n";
    cout << "\t|  3 -> Cancel Reservation                   |\n";
    cout << "\t|  4 -> View Seat Layout                     |\n";
    cout << "\t|  5 -> View All Records                     |\n";
    cout << "\t|  6 -> Exit System                          |\n";
    cout << "\t+--------------------------------------------+\n";
    
    int choice;
    cout << "\n\tEnter your choice: ";
    
   
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\t[ERROR] Invalid input! Please enter a number.\n";
        cout << "\tPress Enter to continue...";
        cin.get();
        displayMainMenu();
        return;
    }
    
    switch(choice) {
        case 1: selectShow(); break;
        case 2: booking(); break;
        case 3: cancelBooking(); break;
        case 4: viewSeats(); break;
        case 5: viewRecords(); break;
        case 6: 
            cout << "\n\t[SUCCESS] Thank you for using our system!\n\n";
            exit(0);
        default:
            cout << "\n\t[ERROR] Invalid choice! Please try again.\n";
            cout << "\tPress Enter to continue...";
            cin.ignore();
            cin.get();
            displayMainMenu();
    }
}

void selectShow() {
    system("clear || cls");
    displayBanner();
    
    cout << "\n\t+----------------------------------------------------------+\n";
    cout << "\t|                    NOW SHOWING                           |\n";
    cout << "\t+----------------------------------------------------------+\n";
    
    for (int i = 0; i < 5; i++) {
        cout << "\t| " << (i + 1) << ". " << left << setw(30) << shows[i].showname 
             << " | LKR" << setw(6) << fixed << setprecision(2) << shows[i].price << "  |\n";
        cout << "\t|    Date: " << setw(12) << shows[i].date 
             << " Time: " << setw(8) << shows[i].time 
             << " Hall: " << shows[i].gate << "        |\n";
        if (i < 4) cout << "\t+----------------------------------------------------------+\n";
    }
    
    cout << "\t+----------------------------------------------------------+\n";
    
    int choice;
    cout << "\n\tSelect a show (1-5): ";
    
    // BUG FIX: Validate input
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\t[ERROR] Invalid input!\n";
        cout << "\tPress Enter to continue...";
        cin.get();
        selectShow();
        return;
    }
    
    if (choice >= 1 && choice <= 5) {
        currentShow = choice - 1;
        cout << "\n\t[SUCCESS] You selected: " << shows[currentShow].showname << "\n";
        cout << "\tPress Enter to continue...";
        cin.ignore();
        cin.get();
        displayMainMenu();
    } else {
        cout << "\n\t[ERROR] Invalid selection!\n";
        cout << "\tPress Enter to continue...";
        cin.ignore();
        cin.get();
        selectShow();
    }
}

void booking() {
    system("clear || cls");
    displayBanner();
    
    cout << "\n\t================================================\n";
    cout << "\t  SEAT BOOKING - " << shows[currentShow].showname << "\n";
    cout << "\t================================================\n";
    
    // Display current seat layout
    cout << "\n\t     SCREEN\n";
    cout << "\t  ===============\n\n";
    cout << "\t     A  B  C  D  E\n";
    cout << "\t   +--------------+\n";
    
    for (int i = 0; i < 4; i++) {
        cout << "\t " << (i + 1) << " |";
        for (int j = 0; j < 5; j++) {
            if (theater[currentShow][i][j].isBooked) {
                cout << " X ";
            } else {
                cout << " O ";
            }
        }
        cout << "|\n";
    }
    cout << "\t   +--------------+\n";
    cout << "\n\t  O = Available   X = Booked\n";
    
    char row;
    int col;
    string name;
    
    cout << "\n\tEnter seat row (A-D): ";
    cin >> row;
    row = toupper(row);
    
    cout << "\tEnter seat column (1-5): ";
    
    // BUG FIX: Validate column input
    if (!(cin >> col)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\t[ERROR] Invalid seat column!\n";
        cout << "\tPress Enter to continue...";
        cin.get();
        displayMainMenu();
        return;
    }
    
    int rowIndex = row - 'A';
    int colIndex = col - 1;
    
    if (rowIndex < 0 || rowIndex >= 4 || colIndex < 0 || colIndex >= 5) {
        cout << "\n\t[ERROR] Invalid seat selection!\n";
        cout << "\tPress Enter to continue...";
        cin.ignore();
        cin.get();
        displayMainMenu();
        return;
    }
    
    if (theater[currentShow][rowIndex][colIndex].isBooked) {
        cout << "\n\t[ERROR] Sorry, this seat is already booked!\n";
        cout << "\tPress Enter to continue...";
        cin.ignore();
        cin.get();
        displayMainMenu();
        return;
    }
    
    cin.ignore();
    cout << "\tEnter customer name: ";
    getline(cin, name);
    
    // BUG FIX: Validate name
    if (name.empty()) {
        cout << "\n\t[ERROR] Name cannot be empty!\n";
        cout << "\tPress Enter to continue...";
        cin.get();
        displayMainMenu();
        return;
    }
    
    // Book the seat
    theater[currentShow][rowIndex][colIndex].isBooked = true;
    theater[currentShow][rowIndex][colIndex].name = name;
    theater[currentShow][rowIndex][colIndex].booking_ID = ++booking_ID;
    theater[currentShow][rowIndex][colIndex].seats = 1;
    
    // Generate and display ticket
    generateTicket(rowIndex, colIndex);
    
    // Save ticket to file
    saveTicketToFile(rowIndex, colIndex);
    
    cout << "\n\tPress Enter to continue...";
    cin.get();
    displayMainMenu();
}

void generateTicket(int row, int col) {
    cout << "\n\n";
    cout << "\t========================================================\n";
    cout << "\t              ***  BOOKING CONFIRMED  ***               \n";
    cout << "\t========================================================\n";
    cout << "\t  Booking ID    : " << theater[currentShow][row][col].booking_ID << "\n";
    cout << "\t  Customer Name : " << theater[currentShow][row][col].name << "\n";
    cout << "\t========================================================\n";
    cout << "\t  Movie         : " << shows[currentShow].showname << "\n";
    cout << "\t  Date          : " << shows[currentShow].date << "\n";
    cout << "\t  Time          : " << shows[currentShow].time << "\n";
    cout << "\t  Hall          : " << shows[currentShow].gate << "\n";
    cout << "\t  Seat          : " << theater[currentShow][row][col].row << theater[currentShow][row][col].col << "\n";
    cout << "\t  Price         : $" << fixed << setprecision(2) << shows[currentShow].price << "\n";
    cout << "\t========================================================\n";
    cout << "\t  Booked on     : " << getCurrentDateTime() << "\n";
    cout << "\t========================================================\n";
    
    cout << "\n\t[SUCCESS] Ticket saved to: ticket_" << theater[currentShow][row][col].booking_ID << ".txt\n";
}

void saveTicketToFile(int row, int col) {
    string filename = "ticket_" + to_string(theater[currentShow][row][col].booking_ID) + ".txt";
    ofstream file(filename);
    
    if (file.is_open()) {
        file << "========================================================\n";
        file << "              ***  PREMIUM THEATRE TICKET  ***          \n";
        file << "========================================================\n";
        file << "  Booking ID    : " << theater[currentShow][row][col].booking_ID << "\n";
        file << "  Customer Name : " << theater[currentShow][row][col].name << "\n";
        file << "========================================================\n";
        file << "  Movie         : " << shows[currentShow].showname << "\n";
        file << "  Date          : " << shows[currentShow].date << "\n";
        file << "  Time          : " << shows[currentShow].time << "\n";
        file << "  Hall          : " << shows[currentShow].gate << "\n";
        file << "  Seat          : " << theater[currentShow][row][col].row << theater[currentShow][row][col].col << "\n";
        file << "  Price         : $" << fixed << setprecision(2) << shows[currentShow].price << "\n";
        file << "========================================================\n";
        file << "  Booked on     : " << getCurrentDateTime() << "\n";
        file << "========================================================\n";
        file << "  Please arrive 15 minutes before showtime              \n";
        file << "  Present this ticket at the entrance                   \n";
        file << "========================================================\n";
        
        file.close();
    } else {
        cout << "\n\t[ERROR] Could not save ticket to file!\n";
    }
}

void cancelBooking() {
    system("clear || cls");
    displayBanner();
    
    cout << "\n\t================================================\n";
    cout << "\t            CANCEL RESERVATION                  \n";
    cout << "\t================================================\n";
    
    int bookingID;
    cout << "\n\tEnter Booking ID to cancel: ";
    
    // BUG FIX: Validate input
    if (!(cin >> bookingID)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\t[ERROR] Invalid booking ID!\n";
        cout << "\tPress Enter to continue...";
        cin.get();
        displayMainMenu();
        return;
    }
    
    // BUG FIX: Search through all shows
    for (int s = 0; s < 5; s++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                if (theater[s][i][j].isBooked && theater[s][i][j].booking_ID == bookingID) {
                    cout << "\n\tBooking found!";
                    cout << "\n\tCustomer: " << theater[s][i][j].name;
                    cout << "\n\tMovie: " << shows[s].showname;
                    cout << "\n\tSeat: " << theater[s][i][j].row << theater[s][i][j].col;
                    
                    char confirm;
                    cout << "\n\n\tAre you sure you want to cancel? (Y/N): ";
                    cin >> confirm;
                    
                    if (toupper(confirm) == 'Y') {
                        theater[s][i][j].isBooked = false;
                        theater[s][i][j].name = "";
                        theater[s][i][j].booking_ID = 0;
                        
                        cout << "\n\t[SUCCESS] Reservation cancelled successfully!\n";
                    } else {
                        cout << "\n\t[INFO] Cancellation aborted.\n";
                    }
                    
                    cout << "\tPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                    displayMainMenu();
                    return;
                }
            }
        }
    }
    
    cout << "\n\t[ERROR] Booking ID not found!\n";
    cout << "\tPress Enter to continue...";
    cin.ignore();
    cin.get();
    displayMainMenu();
}

void viewSeats() {
    system("clear || cls");
    displayBanner();
    
    cout << "\n\t================================================\n";
    cout << "\t  SEAT LAYOUT - " << shows[currentShow].showname << "\n";
    cout << "\t================================================\n";
    
    cout << "\n\t        SCREEN\n";
    cout << "\t     ===============\n\n";
    cout << "\t        A  B  C  D  E\n";
    cout << "\t      +--------------+\n";
    
    int available = 0;
    for (int i = 0; i < 4; i++) {
        cout << "\t   " << (i + 1) << " |";
        for (int j = 0; j < 5; j++) {
            if (theater[currentShow][i][j].isBooked) {
                cout << " X ";
            } else {
                cout << " O ";
                available++;
            }
        }
        cout << "|\n";
    }
    
    cout << "\t      +--------------+\n";
    cout << "\n\t  O = Available (" << available << ")   X = Booked (" << (20 - available) << ")\n";
    
    cout << "\n\tPress Enter to continue...";
    cin.ignore();
    cin.get();
    displayMainMenu();
}

void viewRecords() {
    system("clear || cls");
    displayBanner();
    
    cout << "\n\t==========================================================\n";
    cout << "\t                ALL BOOKING RECORDS                       \n";
    cout << "\t==========================================================\n\n";
    
    bool found = false;
    
    // BUG FIX: Show records for all movies, not just current show
    for (int s = 0; s < 5; s++) {
        bool showHeader = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                if (theater[s][i][j].isBooked) {
                    if (!showHeader) {
                        cout << "\t  Movie: " << shows[s].showname << "\n";
                        cout << "\t  " << string(56, '-') << "\n";
                        showHeader = true;
                    }
                    found = true;
                    cout << "\t  ID: " << setw(6) << theater[s][i][j].booking_ID 
                         << " | Name: " << setw(20) << theater[s][i][j].name 
                         << " | Seat: " << theater[s][i][j].row << theater[s][i][j].col << "\n";
                }
            }
        }
        if (showHeader) {
            cout << "\n";
        }
    }
    
    if (!found) {
        cout << "\t  No bookings found.\n";
    }
    
    cout << "\n\tPress Enter to continue...";
    cin.ignore();
    cin.get();
    displayMainMenu();
}

string getCurrentDateTime() {
    time_t now = time(0);
    char buffer[80];
    strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", localtime(&now));
    return string(buffer);
}