#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct {
    char site[MAX];
    char username[MAX];
    char password[MAX];
} Credential;

// The credential store, this would ideally be some form of database
Credential credentials[MAX];
int num_credentials = 0;

char master_password[MAX] = "master_password"; // The master password, in a real password manager this would be hashed and stored securely

void encrypt_decrypt(char* input, int key) {
    // A simple Caesar cipher for "encryption", not safe for actual use
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        input[i] = input[i] ^ key;
    }
}

void save_credentials() {
    FILE* file = fopen("credentials.txt", "w");
    for (int i = 0; i < num_credentials; i++) {
        // Encrypt data before saving
        Credential c = credentials[i];
        encrypt_decrypt(c.site, 1);
        encrypt_decrypt(c.username, 1);
        encrypt_decrypt(c.password, 1);
        fwrite(&c, sizeof(Credential), 1, file);
    }
    fclose(file);
}

void load_credentials() {
    FILE* file = fopen("credentials.txt", "r");
    Credential c;
    while (fread(&c, sizeof(Credential), 1, file)) {
        // Decrypt data after loading
        encrypt_decrypt(c.site, 1);
        encrypt_decrypt(c.username, 1);
        encrypt_decrypt(c.password, 1);
        add_credential(c);
    }
    fclose(file);
}

void generate_password(char* password, int length) {
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        password[i] = '!' + rand() % 93; // ASCII 33-126: includes numbers, letters, and special characters
    }
    password[length] = '\0';
}

void view_credential(char* site) {
    for (int i = 0; i < num_credentials; i++) {
        if (strcmp(credentials[i].site, site) == 0) {
            printf("Site: %s, Username: %s, Password: %s\n", credentials[i].site, credentials[i].username, credentials[i].password);
            break;
        }
    }
}

int main() {
    int running = 1;
    char entered_password[MAX];
    printf("Enter the master password: ");
    fgets(entered_password, MAX, stdin);
    entered_password[strcspn(entered_password, "\n")] = 0; // Remove the newline character
    
    if (strcmp(master_password, entered_password) != 0) {
        printf("Incorrect master password!\n");
        return 1;
    }
    
    while (running) {
        printf("1. Add credential\n");
        printf("2. Delete credential\n");
        printf("3. Update credential\n");
        printf("4. View credential\n");
        printf("5. List credentials\n");
        printf("6. Save credentials to file\n");
        printf("7. Load credentials from file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
        
        char site[MAX], username[MAX], password[MAX];
        Credential c;
        
        switch (choice) {
            case 1:
                printf("Enter site: ");
                scanf("%s", site);
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                strcpy(c.site, site);
                strcpy(c.username, username);
                strcpy(c.password, password);
                add_credential(c);
                break;
            case 2:
                printf("Enter site to delete: ");
                scanf("%s", site);
                delete_credential(site);
                break;
            case 3:
                printf("Enter site to update: ");
                scanf("%s", site);
                printf("Enter new username: ");
                scanf("%s", username);
                printf("Enter new password: ");
                scanf("%s", password);
                strcpy(c.site, site);
                strcpy(c.username, username);
                strcpy(c.password, password);
                update_credential(c);
                break;
            case 4:
                printf("Enter site to view: ");
                scanf("%s", site);
                view_credential(site);
                break;
            case 5:
                list_credentials();
                break;
            case 6:
                save_credentials();
                printf("Credentials saved to file.\n");
                break;
            case 7:
                num_credentials = 0; // reset the credential count
                load_credentials();
                printf("Credentials loaded from file.\n");
                break;
            case 0:
                running = 0;
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
    }
    
    return 0;
}
