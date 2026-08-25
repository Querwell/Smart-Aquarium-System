#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

int temp = 24;
int food = 10;
float dirt = 20.0;

void system_status() {
    printf("\nAquarium Status\n\n");
    printf("Temperature Status:   %dC\n\n", temp);
    printf("Current Food Status:  %dGram\n\n", food);
    printf("Aquarium Dirt Level:  %.1f%%\n\n", dirt);
}

void show_menu() {
    printf("==================================================\n");
    printf("  SMART AQUARIUM & AUTOMATIC FEEDING SYSTEM v1.0  \n");
    printf("  Developed by: Timur Kabatash                    \n");
    printf("==================================================\n\n");
    printf("Please Select One Of The Options Below:\n\n");
    printf("1-View Aquarium Status\n\n");
    printf("2-Feed Fish\n\n");
    printf("3-Heat/Cool Water\n\n");
    printf("4-Filter Cleaning Level\n\n");
    printf("5-Exit System\n\n");
}

int main() {
system("COLOR E0");
setlocale(LC_ALL, "English");

int choice;

while(1) {
    system("cls");
    show_menu();
    printf("\nYour Choice: ");
    if (scanf("%d",&choice) != 1){
        while (getchar() != '\n');
        printf("\nInvalid Number.\n\n");
        system("pause");
        continue;
    }

    switch (choice) {
    case 1:
        system_status();
        system("pause");
        break;

    case 2:
    if (food>0){
        food = food - 1;
        dirt = (dirt + 5.0f) * 1.20;
        if (dirt > 100.0f){
            dirt = 100.0f;
        }
        printf("\nFish Fed. Food Decreased By 1.\n\n");
        printf("Remaining Food: %d Gram\n\n",food);
    }
    else{
        printf("\n\nFood Stock Empty Please Add Food.\n\n");
    }
    system("pause");
    break;

case 3:
    int decision,newTemp;
    printf("\n\nCurrent Water Temperature: ");
    printf("%d C\n\n",temp);
    printf("Please Select The Action You Want To Perform: \n\n");
    printf("1-Cooling\n\n");
    printf("2-Heating\n\n");

    if (scanf("%d",&decision) != 1){
        while (getchar() != '\n');
        printf("\n\nInvalid Number.\n\n");
        system("pause");
        break;
    }

 if (decision == 1) {
        printf("\n\nEnter the new temperature you want to cool to: ");
        if (scanf("%d",&newTemp) != 1){
                while (getchar() != '\n');
        printf("\n\nInvalid Number.\n\n");
        }

        else if (newTemp >= temp){
            printf("\n\nTarget Temperature Must Be Lower Than Current Temperature (%d C).\n\n",temp);
        }

         else if (newTemp <= 10) {
            printf("\n\nCritical cold limit exceeded. System restored to factory default.\n\n");
        } else {
            temp = newTemp;
            printf("\n\nSystem successfully cooled to target level.\n\n");
        }
    }
    else if (decision == 2) {
        printf("\n\nEnter the new temperature you want to heat to: ");
        if (scanf("%d",&newTemp) != 1){
            while (getchar() != '\n');
            printf("\n\nInvalid Number.\n\n");
        }
        else if (newTemp <= temp){
            printf("\n\nTarget Temperature Must Be Higher Than Current Temperature (%d C).\n\n",temp);
        }
         else if (newTemp >= 35) {
            printf("\n\nCritical heat limit exceeded. System restored to factory default.\n\n");
        } else {
            temp = newTemp;
            printf("\n\nSystem successfully heated to target level.\n\n");
        }
    }
    else {
        printf("You entered an invalid number.\n");
    }
    system("pause");
    break;

case 4:
    int cleanLevelFnc;
    printf("\n\nCurrent Filter Cleaning Percentage: %.1f%%\n\n", dirt);
    printf("1-Quick Clean %%50\n\n");
    printf("2-Deep Clean %%70\n\n");
    printf("3-Extreme Clean %%100\n\n");
    printf("\n\nPlease Select Your Preferred Cleaning Mode:");

    if (scanf("%d",&cleanLevelFnc) != 1){
        while (getchar() != '\n');
        printf("\n\nInvalid Number.\n\n");
        system("pause");
        break;
    }

    if (cleanLevelFnc == 1 ){
        dirt = dirt / 2;
        printf("\n\nQuick clean applied.\n\n");
        printf("Current Filter Dirt Level: %.1f%%\n\n", dirt);
    }
    else if (cleanLevelFnc == 2) {
        dirt = dirt * 0.30;
        if (dirt <= 0.0f){
            dirt = 0.0f;
        }
        printf("\n\nDeep Clean Applied.\n\n");
        printf("Current Filter Dirt Level: %.1f%%\n\n", dirt);
    }
    else if (cleanLevelFnc == 3) {
        dirt = 0.0f;
        printf("\n\nExtreme Clean Applied.\n\n");
        printf("Current Filter Dirt Level: %.1f%%\n\n", dirt);
    }
    else {
        printf("\n\nYou Entered An Invalid Number.\n\n");
    }
    system("pause");
    break;

case 5:
    printf("\n\nUser successfully exited the program.\n\n");
    return 0;
    break;
}
}
return 0;
}
