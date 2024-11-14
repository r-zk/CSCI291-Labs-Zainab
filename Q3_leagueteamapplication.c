#include <stdio.h> //import standard I/O functions
#include <string.h> //string manipulation
#include <stdlib.h> //imports standard library
#include <ctype.h> //character handling
#include <time.h> //date time maipulation

#define NUM_TEAMS 8 //max number of teams
#define SQUAD_SIZE 11 //max squad size
#define MAX_NAME 25 //max name length
#define MAX_TEAM_NAME 20 //max team length
#define MIN_KIT_NUM 1 //min kit number allowed
#define MAX_KIT_NUM 99 //max kit number allowed


//struct for player ages
typedef struct {
    int day;
    int month;
    int year;
} age_t;

//struct for player attributes
typedef struct {
    char name[MAX_NAME]; //name of plyaer
    int kit_number; //kit number
    char club[MAX_TEAM_NAME]; //club
    age_t dob; //date of birth
    char position[11]; //position in field
} player_t;


//struct for teams
typedef struct {
    char name[MAX_TEAM_NAME]; //team name
    player_t players[SQUAD_SIZE]; //array of players in team
    int active_size; //current team with players
} team_t;

team_t teams[NUM_TEAMS]; //array of teams
int num_enrolled_teams = 0; //track number of enrolled teams
int current_year; //holds current year

void display_menu(); //main menu
void enroll_club(); //function to eroll new club
void add_player(); //add player to club function
void search_update(); //searchs and updates a player's info
void display_club_statistics(); //func to disp club stats
void handle_error(const char* message); //error message
int is_kit_number_unique(const char* restrict club_name, int kit_number); //unique kit check
int is_name_unique(const char* restrict club_name, const char* restrict player_name); //unique name check
float calculate_average_age(player_t* restrict players, int num_players); //calculates average age 

int main() {
    // Set current year once for age calculations
    time_t t = time(NULL); //get current time
    struct tm* current_time = localtime(&t); //convert to local
    current_year = current_time->tm_year + 1900; //get current year

    int choice; //menu
    while (1) { //infintie loop
        display_menu(); //displays all options
        scanf("%d", &choice); //read user choice
        getchar(); //clear new line

        switch (choice) { //execute based on choice
            case 1:
                enroll_club(); //enrolls club
                break;
            case 2:
                add_player(); //adds new player
                break;
            case 3:
                search_update(); //searches and updates player info
                break;
            case 4:
                display_club_statistics(); //display club stats
                break;
            default:
                printf("Exiting program.\n"); //exit
                return 0; //end program
        }
    }
}

void display_menu() {
    //main menu option display
    printf("\n--- Football League Team Application ---\n");
    printf("1. Enroll Club\n2. Add Player\n3. Search/Update Player\n4. Display Club Statistics\n5. Exit\n");
    printf("Enter your choice: ");
}

void handle_error(const char* message) {
    //shows error message
    printf("Error: %s\n", message);
}

void enroll_club() {
    //enrolls new club into team array if space is there
    if (num_enrolled_teams >= NUM_TEAMS) { //checks is max number of teams are already enrolled
        handle_error("Maximum NUmber of Teams Enrolled.");
        return;
    }

    printf("Enter Club Name: "); //enter club name
    fgets(teams[num_enrolled_teams].name, MAX_TEAM_NAME, stdin); //get club name
    strtok(teams[num_enrolled_teams].name, "\n"); //remove new line

    teams[num_enrolled_teams].active_size = 0; //set active size to 0
    num_enrolled_teams++; //increment enrolled clubs count
    printf("Club Enrolled Successfully!\n"); //confirmation
}

int is_kit_number_unique(const char* restrict club_name, int kit_number) {
    //checks if kit number is unique 
    for (int i = 0; i < num_enrolled_teams; i++) { //loop for enrolled teams
        if (strcmp(teams[i].name, club_name) == 0) { //checks for same team names
            for (int j = 0; j < teams[i].active_size; j++) { //loop for enrolled players
                if (teams[i].players[j].kit_number == kit_number) { //find
                    return 0; //not unique
                }
            }
            break; //ends when team is found
        }
    }
    return 1; //unique kit number
}

int is_name_unique(const char* restrict club_name, const char* restrict player_name) {
    //checks is player is unique to club
    for (int i = 0; i < num_enrolled_teams; i++) { //loops through teams
        if (strcmp(teams[i].name, club_name) == 0) { //matches
            for (int j = 0; j < teams[i].active_size; j++) { //loops through club players
                if (strcasecmp(teams[i].players[j].name, player_name) == 0) { //matches
                    return 0; //not unique
                }
            }
            break; //stop once team is found
        }
    }
    return 1; //unique name
}

void add_player() {
    //adds player to selected club when space
    if (num_enrolled_teams == 0) { //checks if teams are enrolled
        handle_error("No Clubs Enrolled Yet.\n Cannot Enroll Player");
        return;
    }

    printf("\nAvailable Clubs:\n"); //display list of clubs
    for (int i = 0; i < num_enrolled_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name); //print each team
    }

    int club_choice;
    printf("Select Club (1-%d): ", num_enrolled_teams);
    scanf("%d", &club_choice); //get team choice
    getchar();

    if (club_choice < 1 || club_choice > num_enrolled_teams) {
        handle_error("Invalid Club Selection."); //checks for valid selection
        return;
    }

    team_t* restrict selected_team = &teams[club_choice - 1]; //gets selected club
    if (selected_team->active_size >= SQUAD_SIZE) { //checks if squad is full
        handle_error("Squad is Full.");
        return;
    }

    player_t new_player;
    printf("Enter Player Name: "); //get player name
    fgets(new_player.name, MAX_NAME, stdin);
    strtok(new_player.name, "\n"); //remove line

    if (!is_name_unique(selected_team->name, new_player.name)) { //check name uniqueness
        handle_error("Player Name Already Exists in this Club.");
        return;
    }

    printf("Enter Kit Number (1-99): ");
    scanf("%d", &new_player.kit_number); //get kit number
    getchar();

    if (new_player.kit_number < MIN_KIT_NUM || new_player.kit_number > MAX_KIT_NUM ||
        !is_kit_number_unique(selected_team->name, new_player.kit_number)) { //checks if valid
        handle_error("Kit Number is Either Invalid or Already in Use.");
        return;
    }

    printf("Enter Birth Date (DD MM YYYY): "); //gets dob
    scanf("%d %d %d", &new_player.dob.day, &new_player.dob.month, &new_player.dob.year);
    getchar();

    printf("Enter Position: "); //gets player position
    fgets(new_player.position, 15, stdin);
    strtok(new_player.position, "\n"); //removes new line

    selected_team->players[selected_team->active_size++] = new_player; //adds player to team
    printf("Player Added Successfully!\n");
}

void search_update() {
    //searches for player name and allows update
    printf("Enter Player Name to Search: ");
    char search_name[MAX_NAME];
    fgets(search_name, MAX_NAME, stdin);
    strtok(search_name, "\n"); //removes new line

    for (int i = 0; i < num_enrolled_teams; i++) {
        for (int j = 0; j < teams[i].active_size; j++) { //check name
            if (strcasecmp(teams[i].players[j].name, search_name) == 0) {
                printf("\nPlayer Found!\nName: %s\nKit Number: %d\nPosition: %s\nDate of Birth: %d.%d.%d\n",
                       teams[i].players[j].name, teams[i].players[j].kit_number,
                       teams[i].players[j].position, teams[i].players[j].dob.day,
                       teams[i].players[j].dob.month, teams[i].players[j].dob.year);

                printf("Enter New Position: "); //update position
                fgets(teams[i].players[j].position, 15, stdin);
                strtok(teams[i].players[j].position, "\n");

                printf("Player Details Updated.\n");
                return;
            }
        }
    }

    handle_error("Player Not Found."); //player not found message
}

float calculate_average_age(player_t* restrict players, int num_players) {
    //calculates and returns average age 
    if (num_players == 0) return 0;

    int total_age = 0;
    for (int i = 0; i < num_players; i++) {
        total_age += current_year - players[i].dob.year; //calculate age
    }

    return (float)total_age / num_players;
}

void display_club_statistics() {
    //display club stats
    if (num_enrolled_teams == 0) {
        handle_error("No Clubs Enrolled.");
        return;
    }

    for (int i = 0; i < num_enrolled_teams; i++) {
        printf("\n--- %s ---\n", teams[i].name); //print team name
        printf("Number of Players: %d\nAverage Age: %.2f\n", teams[i].active_size,
               calculate_average_age(teams[i].players, teams[i].active_size)); //print player count and average age

        printf("Players:\n"); //lust players
        for (int j = 0; j < teams[i].active_size; j++) {
            printf("%d. %s (Kit Number: %d) - %s\n", j + 1,
                   teams[i].players[j].name, teams[i].players[j].kit_number,
                   teams[i].players[j].position);
        }
    }
}
