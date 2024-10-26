#include <iostream>
#include <string>
#include <windows.h> // this header file Used to pause the code from running (Sleep)
#include <fstream>   // to create files
using namespace std;

void login_page();
void Register();
void menu();
void Add_player();
void Display_players();
void Search_player();
void main_page();
void Manage_Teams();
void add_team();
void Assign_players();
void view_teams();
void delete_teams();
void edit_playerteam();

// Main page where you log in to the system
void main_page()
{
    int select;
    cout << "                                                  ---Welcome to Upcountry Warriors---\t\t\t\n";
    cout << "                                                              1.Login\n";
    cout << "                                                              2.Register\n";
    cout << "                                                              3.Exit\n";
    cout << "                                                              select(1/2/3): ";
    cin >> select;

    system("cls"); // clearing the screen
    switch (select)
    {
    case 1:
        login_page();
        break;
    case 2:
        Register();
        break;
    case 3:
        exit(0);
        break;
    default:
        cout << "                                                  input correct number";
        cin.clear();  // clears the inputed value earlier
        cin.ignore(); // make sure that the earlier input doesnt affect next input(it was looping)
        Sleep(2000);  // it delays the code being executed for 2 second
        system("cls");
        main_page();
    }
}

void login_page()
{
    string username, password, id, pass;
    bool correct = false; // declared since unpredictble issue
    cout << "                                                  ---Log in to your account---\n";
    cout << "                                                           1.username: ";
    cin >> username;
    cout << "                                                           2.password: ";
    cin >> password;

    ifstream LoginFile;
    LoginFile.open("Login_Details.txt");
    while (LoginFile >> id >> pass) // this is how you read from the file
    {
        if (id == username && pass == password)
        {
            correct = true;
            break;
        }
    }
    LoginFile.close();

    /*didn't use below if statement inside the above while loop since after the first run of the while loop when it doesnt
    finds the credentials to be right then it automatically breaks out the loop without checking the whole file.*/
    if (correct)
    {
        system("cls");
        menu();
    }
    else
    {
        cout << "                                                  Please check your login details";
        Sleep(2000);
        system("cls");
        main_page();
    }
}

void Register()
{
    string rusername, rpassword, id, pass;
    bool already_registered = false;
    cout << "                                                  ---Register ---\n";
    cout << "                                                    1.username: ";
    cin >> rusername;
    cout << "                                                    2.password: ";
    cin >> rpassword;

    ifstream LoginFile; // to read data from file.
    LoginFile.open("Login_Details.txt");
    if (LoginFile.is_open())
    {
        while (LoginFile >> id >> pass)
        {
            if (id == rusername && pass == rpassword)
            {
                already_registered = true;
                LoginFile.close();
                break;
            }
        }
    }
    if (already_registered)
    {
        cout << endl
             << endl;
        cout << "                                                  you are already registerd";
        Sleep(2000);
        system("cls");
        login_page();
    }
    else
    {
        ofstream LoginFile;                            // write data to file.
        LoginFile.open("Login_Details.txt", ios::app); // app means append mode where it add data with the existing data
        if (LoginFile.is_open())
        {
            LoginFile << rusername << ' ' << rpassword << endl;
            LoginFile.close();
        }
        system("cls");
        cout << endl
             << endl;
        cout << "                                                  Registration is completed";
        Sleep(2000);
        system("cls");
        menu();
    }
}

// Main menu is where all the features will be displayed
void menu()
{
    int select;
    cout << "                                                  1.Add new players\n";
    cout << "                                                  2.Display Players information\n";
    cout << "                                                  3.Manage Teams\n";
    cout << "                                                  4.Search players\n";
    cout << "                                                  5.Log out\n";
    cout << "                                                  6.Exit\n";
    cout << "                                                  Select(1/2/3/4/5/6): ";
    cin >> select;
    system("cls");
    switch (select)
    {
    case 1:
        Add_player();
        break;

    case 2:
        Display_players();
        break;

    case 3:
        Manage_Teams();
        break;

    case 4:
        Search_player();
        break;

    case 5:
        main_page();
        break;

    case 6:
        exit(0);
        break;

    default:
        cout << "                                                  \n\n\n\n\t\t\t\tInvalid Input";
        Sleep(1000);
        system("cls");
        cin.clear();  // clears the inputed value earlier
        cin.ignore(); // ignore the input where it will not affect the next cin
        menu();
    }
}

// Used a structure for player where we store player details
struct Player
{
    int PlayerId;
    string fname;
    string lname;
    string DOB;
    string runs;
};
Player info[30];
int playercount;
void Add_player()
{
    cout << "                                                  ---Add new Player---\n\n\n";
    fstream playerrecords_in;
    playerrecords_in.open("records.txt", ios::in); // in means we are reading the data from the file
    if (playerrecords_in.is_open())
    {
        while (playerrecords_in >> info[playercount].PlayerId >> info[playercount].fname >> info[playercount].lname >> info[playercount].DOB >> info[playercount].runs)
        {
            info[playercount].PlayerId++;
        }
        playerrecords_in.close();
    }

    cout << "                                                     Player Id: " << info[playercount].PlayerId << endl;
    cout << "                                                     Enter player first name: ";
    cin >> info[playercount].fname;
    cout << "                                                     Enter player last name: ";
    cin >> info[playercount].lname;
    cout << "                                                     Enter player Date of Birth(YYYY/MM/DD): ";
    cin >> info[playercount].DOB;
    cout << "                                                     Enter player runs scored: ";
    cin >> info[playercount].runs;
    system("cls");
    cout << endl
         << endl;
    cout << "                                                   Player Details added successfully!";
    Sleep(2000);
    system("cls");

    ofstream playerrecords_out;
    playerrecords_out.open("records.txt", ios::app); // adding user input without replacing slready existing data
    if (playerrecords_out.is_open())
    {
        playerrecords_out << info[playercount].PlayerId << endl;
        playerrecords_out << info[playercount].fname << endl;
        playerrecords_out << info[playercount].lname << endl;
        playerrecords_out << info[playercount].DOB << endl;
        playerrecords_out << info[playercount].runs << endl
                          << endl;
        playerrecords_out.close();
    }
    system("cls");
    menu();
}

void Display_players()
{
    cout << "                                                  -----Players Information-----\n";
    ifstream playerrecords_in;
    playerrecords_in.open("records.txt", ios::in); // ios::in used because we are reading data from the file
    if (playerrecords_in.is_open())                // checking wheter the file is open
    {
        int i = 0;
        while (playerrecords_in >> info[i].PlayerId >> info[i].fname >> info[i].lname >> info[i].DOB >> info[i].runs)
        {
            // Outputing from the file
            cout << "                                        --------------------------------------------------\n";
            cout << "                                                       Player ID: " << info[i].PlayerId << endl;
            cout << "                                                       First name: " << info[i].fname << endl;
            cout << "                                                       Last name: " << info[i].lname << endl;
            cout << "                                                       Date of Birth: " << info[i].DOB << endl;
            cout << "                                                       runs: " << info[i].runs << endl
                 << endl;
            i++;
        }
        playerrecords_in.close();
    }
    cout << endl
         << endl;
    menu();
}

void Search_player()
{
    cout << "                                                   -----Search Player-----\n\n\n";
    string name;
    int id;
    cout << "                                                  Input Player First name: ";
    cin >> name;
    cout << "                                                  Input player ID: ";
    cin >> id;
    fstream playerrecords_in;
    playerrecords_in.open("records.txt", ios::in);
    bool found = false;
    if (playerrecords_in.is_open())
    {
        int i = 0;
        while (playerrecords_in >> info[i].PlayerId >> info[i].fname >> info[i].lname >> info[i].DOB >> info[i].runs)
        {
            if (info[i].PlayerId == id && info[i].fname == name)
            {
                found = true;
                break;
            }
            i++;
        }
        if (found)
        {
            system("cls");
            cout << "                                                  Player Found\n\n";
            cout << "                                                  Player ID: " << info[id].PlayerId << endl;
            cout << "                                                  Name: " << info[id].fname << " " << info[id].lname << endl;
            cout << "                                                  Date of Birth: " << info[id].DOB << endl;
            cout << endl
                 << endl;
        }
        else
        {
            system("cls");
            cout << "                                                  Player Not Found\n\n";
            cout << endl
                 << endl;
        }
    }
    playerrecords_in.close();
    menu();
}

void Manage_Teams()
{
    int select;
    cout << "                                                  1.Add a Team \n";
    cout << "                                                  2.Assign Players\n";
    cout << "                                                  3.View team details\n";
    cout << "                                                  4.Delete teams\n";
    cout << "                                                  5.Edit player's teams\n";
    cout << "                                                  6.Main Menu\n";
    cout << "                                                  Select(1/2/3/4/5/6): ";
    cin >> select;
    system("cls");
    switch (select)
    {
    case 1:
        add_team();
        break;

    case 2:
        Assign_players();
        break;

    case 3:
        view_teams();
        break;

    case 4:
        delete_teams();
        break;

    case 5:
        edit_playerteam();
        break;

    case 6:
        menu();
        break;

    default:
        cout << "                                                  \n\n\n\n\t\t\t\tInvalid Input";
        Sleep(1000);
        system("cls");
        cin.clear();  // clears the inputed value earlier
        cin.ignore(); //(numeric_limits<streamsize>::max(), '\n');
        Manage_Teams();
    }
}

// creating an array for the teams
string teams[5];
void add_team()
{
    int i = 0;
    cout << "                                                      -----Add Teams-----\n\n\n";
    // opening the teams file just to initialize the which one is it in the array
    fstream teamfiles;
    teamfiles.open("teams.txt", ios::in);
    if (teamfiles.is_open())
    {
        while (teamfiles >> teams[i])
        {
            i++;
        }
        teamfiles.close();
    }
    if (i == 5)
    {
        cout << "                                                Maximum number of Teams reached\n\n";
        Sleep(3000);
        system("cls");
        Manage_Teams();
    }
    else
    {
        cout << "                                                Number of teams Added: " << i << endl;
        cout << "                                                  Input Team Name: ";
        cin >> teams[i];
    }

    fstream teamsfile;
    teamsfile.open("teams.txt", ios::out | ios::app);
    if (teamsfile.is_open())
    {
        teamsfile << teams[i] << endl;
    }
    teamsfile.close();
    system("cls");
    Manage_Teams();
}

void Assign_players()
{
    int AID;
    string Assteam1, Assteam2;
    bool available = false;

    cout << "                                                -----Assign Players-----\n\n\n";
    cout << "                                                     Input Player ID: ";
    cin >> AID;
    cout << endl;

    fstream recordfile;
    recordfile.open("records.txt", ios::in);

    if (recordfile.is_open())
    {
        int i = 0;
        while (recordfile >> info[i].PlayerId >> info[i].fname >> info[i].lname >> info[i].DOB >> info[i].runs)
        {
            if (info[i].PlayerId == AID)
            {
                available = true;
                break;
            }
            i++;
        }
        recordfile.close();
    }

    if (available)
    {
        fstream playerteamsfile;
        playerteamsfile.open("playerteams.txt", ios::in);
        bool check = false;

        if (playerteamsfile.is_open())
        {
            int f = 0;
            while (playerteamsfile >> info[f].PlayerId >> info[f].fname >> Assteam1 >> Assteam2)
            {
                if (info[f].PlayerId == AID)
                {
                    check = true;
                    break;
                }
                f++;
            }
            playerteamsfile.close();
        }

        if (check)
        {
            cout << "                                                This player is already assigned";
            Sleep(2000);
            system("cls");
            Manage_Teams();
        }
        else
        {
            fstream teamsfile;
            teamsfile.open("teams.txt", ios::in);
            if (teamsfile.is_open())
            {
                cout << "                                                         Teams List\n";
                int l = 0;
                while (teamsfile >> teams[l])
                {
                    cout << "                                                     Team: " << teams[l] << endl;
                    l++;
                }
                teamsfile.close();

                cout << "                                                Assign Player's first team: ";
                cin >> Assteam1;
                cout << "                                                Assign Player's second team: ";
                cin >> Assteam2;

                playerteamsfile.open("playerteams.txt", ios::out | ios::app);
                if (playerteamsfile.is_open())
                {
                    playerteamsfile << info[AID].PlayerId << " " << info[AID].fname << " " << Assteam1 << " " << Assteam2 << endl;
                    playerteamsfile.close();
                }

                system("cls");
                cout << endl
                     << endl;
                cout << "                                                Player is successfully assigned to the teams";
                Sleep(2000);
                system("cls");
                Manage_Teams();
            }
        }
    }
    else
    {
        cout << "                                                A player doesn't exist with that ID\n";
        Manage_Teams();
    }
}

void view_teams()
{
    int i = 0;
    int l = 0;
    string Assteam1, Assteam2;

    cout << "                                                   -----Team Details-----\n\n";

    fstream teamsfile;
    teamsfile.open("teams.txt", ios::in);
    if (teamsfile.is_open())
    {
        while (teamsfile >> teams[i])
        {
            cout << "                                                          ---Team " << teams[i] << "---" << endl;

            fstream playerteams;
            playerteams.open("playerteams.txt", ios::in);
            if (playerteams.is_open())
            {
                while (playerteams >> info[l].PlayerId >> info[l].fname >> Assteam1 >> Assteam2)
                {
                    if (teams[i] == Assteam1 || teams[i] == Assteam2)
                    {
                        cout << "                                                        Player Name: " << info[l].fname << endl;
                    }
                    l++;
                }
                cout << "                                             -------------------------------------\n";
                playerteams.close();
            }
            i++;
        }
        teamsfile.close();
    }

    Manage_Teams();
}

void delete_teams()
{
    char choice;
    cout << "                                                   -----Remove Teams-----\n\n\n";
    cout << "                                                  Do you want to delete all the teams(y/n): ";
    cin >> choice;
    if (choice == 'y')
    {
        remove("playerteams.txt");
        remove("teams.txt");
        cout << "                                                      Teams successfully deleted";
        Sleep(2000);
        system("cls");
        Manage_Teams();
    }
    else if (choice == 'n')
    {
        cout << "                                                      Teams didnt get deleted";
        Sleep(2000);
        system("cls");
        Manage_Teams();
    }
}

void edit_playerteam()
{
    int playerId;
    string newTeam1, newTeam2;
    bool playerFound = false;

    cout << "                                                -----Edit Player's Team-----\n\n\n";
    cout << "                                                     Input Player ID: ";
    cin >> playerId;

    fstream playerteamsfile;
    playerteamsfile.open("playerteams.txt", ios::in);
    if (!playerteamsfile.is_open())
    {
        cout << "                                                Unable to open playerteams.txt file.\n";
        Manage_Teams();
        return;
    }

    // Temporary file to store updated team assignments
    fstream tempFile;
    tempFile.open("temp_playerteams.txt", ios::out);
    if (!tempFile.is_open())
    {
        cout << "                                                Unable to open temporary file.\n";
        playerteamsfile.close();
        Manage_Teams();
        return;
    }
    fstream teamsfile;
    teamsfile.open("teams.txt", ios::in);
    if (teamsfile.is_open())
    {
        cout << "                                                       --Teams List--\n";
        int l = 0;
        while (teamsfile >> teams[l])
        {
            cout << "                                                          Team: " << teams[l] << endl;
            l++;
        }
        teamsfile.close();
    }
    int tempPlayerId;
    string tempPlayerName, tempTeam1, tempTeam2;

    while (playerteamsfile >> tempPlayerId >> tempPlayerName >> tempTeam1 >> tempTeam2)
    {
        if (tempPlayerId == playerId)
        {
            playerFound = true;
            cout << "                                                     Current Teams: " << tempTeam1 << ", " << tempTeam2 << endl;
            cout << "                                                     Enter new first team: ";
            cin >> newTeam1;
            cout << "                                                     Enter new second team: ";
            cin >> newTeam2;
            tempFile << tempPlayerId << " " << tempPlayerName << " " << newTeam1 << " " << newTeam2 << endl;
        }
        else
        {
            tempFile << tempPlayerId << " " << tempPlayerName << " " << tempTeam1 << " " << tempTeam2 << endl;
        }
    }

    playerteamsfile.close();
    tempFile.close();

    if (playerFound)
    {
        // Replace original file with the updated one
        remove("playerteams.txt");
        rename("temp_playerteams.txt", "playerteams.txt");
        cout << "                                                Player's team updated successfully.\n";
    }
    else
    {
        cout << "                                                Player not found.\n";
        remove("temp_playerteams.txt");
    }

    Sleep(2000);
    system("cls");
    Manage_Teams();
}

int main()
{
    main_page();

    return 0;
}
