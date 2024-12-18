#include <stdio.h>
#include "Include/raylib.h"
#include <math.h>
#include "recursive.c"
#include <string.h>
#include <time.h>


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define DISK_WIDTH 100
#define DISK_HEIGHT 20
#define MOVE_DELAY 30 // Delay in frames between moves

int numMoves = 0; // Assign the desired value to this variable
float timeComplexity = 0.0f; // Time complexity in seconds
int numDisks = 0; // Number of disks on the first tower 

// Base properties
int rectX = 100;
int rectY = SCREEN_HEIGHT - 150;
int rectWidth = SCREEN_WIDTH - 200;
int rectHeight = 18;
Color rectColor = DARKPURPLE;
float roundness = 0.2f;
// Tower properties
int vertRectWidth = 25;
int vertRectHeight = 350;
Color vertRectColor = DARKPURPLE;

struct timespec start1 , end1;
long long elapsed_time;

// Disk struct
typedef struct {
    int width;
    int height;
    Color color;
    float roundness;
    Vector2 position;
} Disk;

// Define a structure to represent a tower
typedef struct {
    char name; // Tower name (A, B, C)
    int numDisks; // Number of disks on the tower
    Disk disks[30]; // Array of disks on the tower (maximum 10 disks)
} Tower;

// Function prototypes
void drawTowersAndDisks(Tower *towers);
Color getRandomColor(); // Function to generate a random color



// Function to move a single disk from source tower to destination tower
void moveDisk(Tower *sourceTower, Tower *destTower, Sound moveSound) {

    
    // Move disk from source tower to destination tower
    destTower->disks[destTower->numDisks] = sourceTower->disks[sourceTower->numDisks - 1];
    destTower->numDisks++;
    sourceTower->numDisks--;

    // Print move information
    printf("Move disk from tower %c to tower %c\n", sourceTower->name, destTower->name);

     // Play the sound effect
    PlaySound(moveSound);

    
}

void verifyTowerOfHanoi(Tower *finalTower, Tower towers[3]) {
    Sound redDiskSound = LoadSound("reddisk.ogg");
    Sound correct = LoadSound("correct.wav");

    int delay = 20; // Delay in frames between disk color changes
    int resetDelay = 40; // Delay in frames before resetting the disk color

    // Store the original colors of the disks
    Color originalColors[30];
    for (int i = 0; i < finalTower->numDisks; i++) {
        originalColors[i] = finalTower->disks[i].color;
    }

    for (int i = 0; i < finalTower->numDisks; i++) {
        finalTower->disks[i].color = RED; // Change the disk color to red
        PlaySound(redDiskSound); // Play the sound effect

        for (int j = 0; j < delay; j++) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            drawTowersAndDisks(towers); // Draw the towers with the updated disk color
            DrawText("Verification algorithm in process...", GetScreenWidth() / 2 - MeasureText("Verification algorithm in process...", 40) / 2, rectY + rectHeight + 20, 40, DARKPURPLE);
            EndDrawing();
        }

        // Reset the disk color after a delay
        for (int j = 0; j < resetDelay; j++) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            drawTowersAndDisks(towers); // Draw the towers with the original disk color
            EndDrawing();
        }

        finalTower->disks[i].color = originalColors[i]; // Restore the original color
    }

    int textY = rectY + rectHeight + 20; // Adjust the offset as needed

    // Wait for some time before closing the window
    PlaySound(correct); // Play the sound effect
    for (int i = 0; i < 250; i++) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        drawTowersAndDisks(towers);
        DrawText("The solution is correct!", GetScreenWidth() / 2 - MeasureText("The solution is correct!", 40) / 2, textY, 40, GREEN);
        EndDrawing();
    }
}

// Function to solve Tower of Hanoi problem given an array of moves
void solveTowerOfHanoi(char moves[], int numMoves, Tower towers[3]) {
    // Load the sound effect
    Sound moveSound = LoadSound("move-self.ogg");
    for (int i = 0; i < numMoves; i += 2) {
        char sourceTowerName = moves[i];
        char destTowerName = moves[i + 1];

        Tower *sourceTower = NULL;
        Tower *destTower = NULL;

        // Find source and destination towers based on tower names
        for (int j = 0; j < 3; j++) {
            if (towers[j].name == sourceTowerName) {
                sourceTower = &towers[j];
            }
            if (towers[j].name == destTowerName) {
                destTower = &towers[j];
            }
        }

        // Check if source and destination towers are found
        if (sourceTower != NULL && destTower != NULL) {
            moveDisk(sourceTower, destTower, moveSound);
        } else {
            printf("Invalid move: Tower not found\n");
        }

        // Wait a few frames before the next move
        for (int i = 0; i < MOVE_DELAY; i++) {
            // Update and draw nothing for one frame
            BeginDrawing();
            ClearBackground(RAYWHITE);
            drawTowersAndDisks(towers);
            EndDrawing();
        }
    }
    // Perform the verification sequence
    verifyTowerOfHanoi(&towers[2],towers);
}

// Function to generate a random color
Color getRandomColor() {
    Color color;
    color.r = GetRandomValue(100, 255); // Random red component (100-255)
    color.g = GetRandomValue(100, 255); // Random green component (100-255)
    color.b = GetRandomValue(100, 255); // Random blue component (100-255)
    color.a = 255; // Alpha component set to maximum (255)
    return color;
}

// Function to draw the screen





void DrawScreen() {
    ClearBackground(RAYWHITE);
    DrawText("Tower of Hanoi", GetScreenWidth() / 2 - MeasureText("Tower of Hanoi", 80) / 2, 50, 80, DARKPURPLE);

    // Draw the horizontal rectangle with rounded corners
    DrawRectangleRounded((Rectangle){ rectX, rectY, rectWidth, rectHeight }, roundness * fmax(rectWidth, rectHeight) / 2, 0, rectColor);

    // Draw the vertical rectangles
    int spacing = (rectWidth - 3 * vertRectWidth) / 6;
    int vertRectX = rectX + spacing;
    for (int i = 0; i < 3; i++) {
        DrawRectangle(vertRectX, rectY - vertRectHeight, vertRectWidth, vertRectHeight, vertRectColor);
        vertRectX += vertRectWidth + 2 * spacing;
    }

    // Draw red text in the bottom left corner
    DrawText("Time complexity in milliSeconds: ", 10, GetScreenHeight() - 60, 20, RED);
    DrawText(TextFormat("%.4f milSec", timeComplexity), MeasureText("Time complexity in milliSeconds: ", 20) + 15, GetScreenHeight() - 60, 20, RED);

    // Draw red text for number of moves
    DrawText("Number of moves: ", 10, GetScreenHeight() - 30, 20, RED);
    DrawText(TextFormat("%d", numMoves), MeasureText("Number of moves: ", 20) + 15, GetScreenHeight() - 30, 20, RED);

    // Draw red text for number of disks in the bottom-right corner
    int textWidth = MeasureText(TextFormat("Number of disks: %d", numDisks), 20);
    DrawText(TextFormat("Number of disks: %d", numDisks), GetScreenWidth() - textWidth - 10, GetScreenHeight() - 30, 20, RED);
}

// Function to draw towers and disks
void drawTowersAndDisks(Tower *towers) {
    DrawScreen();

    // Draw disks on each tower
    int spacing = (rectWidth - 3 * vertRectWidth) / 6;
    int towerX = rectX + spacing;
    for (int i = 0; i < 3; i++) {
        int diskY = rectY;
        for (int j = 0; j < towers[i].numDisks; j++) {
            // Draw disk
            DrawRectangleRounded(
                (Rectangle){ towerX + (vertRectWidth - towers[i].disks[j].width) / 2, diskY - towers[i].disks[j].height, towers[i].disks[j].width, towers[i].disks[j].height },
                towers[i].disks[j].roundness, 0, towers[i].disks[j].color);
            diskY -= towers[i].disks[j].height; // Move up for the next disk
        }
        towerX += vertRectWidth + 2 * spacing; // Move to the next tower position
    }
}

int GetNumberFromUser()
{
    int number = -1; // Initialize with an invalid value
    char inputText[10] = "";
    bool validInput = false;
    bool showErrorMessage = false;

    // Create a temporary window for input
    InitWindow(400, 300, "Number Input");

    SetTargetFPS(60);

    while (!WindowShouldClose() && !validInput)
    {
        // Update
    
        int key = GetKeyPressed();
        if ((key >= 48 && key <= 57) || IsKeyPressed(KEY_BACKSPACE)) // Check if input is a number or backspace
        {
            if (!IsKeyPressed(KEY_BACKSPACE)) // If input is a number, append it to the string
            {
                int length = TextLength(inputText);
                if (length < 2) inputText[length] = (char)key;
                inputText[length + 1] = '\0';
            }
            else // If input is backspace, remove the last character from the string
            {
                int length = TextLength(inputText);
                if (length > 0) inputText[length - 1] = '\0';
            }
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            number = TextToInteger(inputText);
            if (number >= 1 && number <= 15)
            {
                validInput = true;
            }
            else
            {
                showErrorMessage = true;
            }
            
            inputText[0] = '\0'; // Clear the input text
        }
    

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

    
        DrawText("Enter a number between 1 and 15:", 20, 20, 20, GRAY);
        DrawText(inputText, 20, 60, 40, BLACK);
    
     

        if (showErrorMessage)
        {
            DrawText("Invalid number! Enter a value between 1 and 15.", 20, 100, 20, RED);
            showErrorMessage = false; // Reset the flag after displaying the error message
            int delayCounter = 0; // Initialize a delay counter
            while (delayCounter < 60) // Delay for 1 second (60 frames at 60 FPS)
            {
                delayCounter++;
                EndDrawing();
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Invalid number! Enter a value between 1 and 15.", 20, 100, 20, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return number;
}

void GetUserOption(Pile *p1, Pile *p2, Pile *p3, int n, char T[])
{
    int option = 0;
    Rectangle option1Rect = { 100, 200, 200, 50 };
    Rectangle option2Rect = { 100, 300, 200, 50 };
    bool optionSelected = false;

    // Create a temporary window for input
    InitWindow(400, 500, "Choose an Option");

    SetTargetFPS(60);

    while (!WindowShouldClose() && !optionSelected)
    {
        // Update
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(mousePos, option1Rect))
            {
                option = 1;
                optionSelected = true;
            }
            else if (CheckCollisionPointRec(mousePos, option2Rect))
            {
                option = 2;
                optionSelected = true;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Choose an algorithem:", 20, 20, 20, GRAY);

        DrawRectangleRec(option1Rect, LIGHTGRAY);
        DrawText("Iteratif", option1Rect.x + 10, option1Rect.y + 15, 20, BLACK);

        DrawRectangleRec(option2Rect, LIGHTGRAY);
        DrawText("recursif", option2Rect.x + 10, option2Rect.y + 15, 20, BLACK);

        EndDrawing();
    }

    // Call the corresponding function based on the user's choice
    switch (option)
    {
    case 1:
        printf("Option 1 selected\n");
        // start=clock(); 
        // resolutionIteratif(p1, p2, p3, n,T);
        // end=clock();
        // timeComplexity=(float)((end-start) * 1000 /CLOCKS_PER_SEC);
        // printf("Time complexity in milliSeconds: %.4f\n", timeComplexity);

        
        clock_gettime(CLOCK_MONOTONIC, &start1);

        resolutionIteratif(p1, p2, p3, n,T);

        clock_gettime(CLOCK_MONOTONIC, &end1);

        elapsed_time = (end1.tv_sec - start1.tv_sec) * 1000000000LL + (end1.tv_nsec - start1.tv_nsec);
        timeComplexity = (float)elapsed_time / 1000000.0; // Time complexity in milliseconds

        break;
    case 2:
        printf("Option 2 selected\n");
        // start=clock(); 
        // hanoi(n,'A','B','C',T);
        // end=clock();
        // timeComplexity=(float)((end-start)  * 1000 /CLOCKS_PER_SEC);
        // printf("Time complexity in milliSeconds: %.4f\n", timeComplexity );

        clock_gettime(CLOCK_MONOTONIC, &start1);

        resolutionRecursive(n,'A','B','C',T);

        clock_gettime(CLOCK_MONOTONIC, &end1);

        elapsed_time = (end1.tv_sec - start1.tv_sec) * 1000000000LL + (end1.tv_nsec - start1.tv_nsec);
        timeComplexity = (float)elapsed_time / 1000000.0; // Time complexity in milliseconds

        break;
    }

    CloseWindow();
}

int main() {

    
    numDisks = GetNumberFromUser();
    printf("User entered: %d\n", numDisks);

    

     char T[((1<<numDisks)-1)*2-1];
    
    //l'initialisation des piles
    Pile p1, p2, p3;
    initPile(&p1, numDisks);
    initPile(&p2, numDisks);
    initPile(&p3, numDisks);


    remplir(&p1, numDisks);// remplissage du premier piquet par les n disques 

    GetUserOption(&p1, &p2, &p3, numDisks, T);


    // Initialize Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower of Hanoi");
    SetTargetFPS(60);

    InitAudioDevice(); // Initialize audio device


    // // Example array of moves
    // char moves[] = {'A', 'B', 'A', 'C', 'B', 'C', 'A', 'B', 'C', 'A', 'C', 'B', 'A', 'B', 'A', 'C'};
    // int numMoves = sizeof(moves) / sizeof(moves[0]);

    numMoves = strlen(T) / 2;

    // Initialize towers A, B, and C with the number of disks and sizes
    Tower towers[3] = {
        {'A', numDisks, {{0}}},
        {'B', 0, {{0}}},
        {'C', 0, {{0}}}
    };

    // Initialize disks on Tower A with decreasing widths
    int maxDiskWidth = 280;
    int diskWidth = maxDiskWidth;
    int diskHeight = 30;
    int widthDifference = maxDiskWidth / (numDisks + 1); // Width difference between disks
    for (int i = 0; i < numDisks; i++) {
        towers[0].disks[i].width = diskWidth;
        towers[0].disks[i].height = diskHeight;
        towers[0].disks[i].roundness = 0.9f;
        towers[0].disks[i].color = getRandomColor();
        towers[0].disks[i].position = (Vector2){200, 570 - i * diskHeight};
        diskWidth -= widthDifference; // Decrease the width for the next disk
    }

    // Solve Tower of Hanoi problem
    solveTowerOfHanoi(T, numMoves * 2, towers);

    // Main game loop
    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw towers and disks
        drawTowersAndDisks(towers);
        EndDrawing();
    }
    
    CloseAudioDevice();

    // Close Raylib
    CloseWindow();

    return 0;
}