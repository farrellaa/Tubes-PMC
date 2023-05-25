#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 32
#define MAX_PHONE_LENGTH 13

struct Contact {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    struct Contact* next;
};

struct Contact* head = NULL;

// Variabel global untuk menyimpan data kontak yang sedang diinput
char tempName[MAX_NAME_LENGTH];
char tempPhone[MAX_PHONE_LENGTH];

// Fungsi untuk mencetak pesan prompt di Serial Monitor
void printPrompt() {
    Serial.println();
    Serial.println("Phone Book Menu:");
    Serial.println("1. Create");
    Serial.println("2. Read");
    Serial.println("3. Update");
    Serial.println("4. Delete");
    Serial.println("Enter your choice (1-4):");
}

// Fungsi untuk membuat kontak baru
void createContact() {
    Serial.println("Enter name (max 32 characters):");
    while (Serial.available() == 0)
        ;
    String name = Serial.readStringUntil('\n');
    name.trim();
    name.toCharArray(tempName, MAX_NAME_LENGTH);

    Serial.println("Enter phone number (max 13 characters):");
    while (Serial.available() == 0)
        ;
    String phone = Serial.readStringUntil('\n');
    phone.trim();
    phone.toCharArray(tempPhone, MAX_PHONE_LENGTH);

    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
    if (newContact == NULL) {
        Serial.println("Memory allocation failed!");
        return;
    }

    strcpy(newContact->name, tempName);
    strcpy(newContact->phone, tempPhone);
    newContact->next = NULL;

    if (head == NULL) {
        head = newContact;
    } else {
        struct Contact* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newContact;
    }

    Serial.println("Contact created successfully!");
}

// Fungsi untuk membaca semua kontak
void readContacts() {
    if (head == NULL) {
        Serial.println("Phone book is empty!");
        return;
    }

    struct Contact* current = head;
    Serial.println("Phone Book Contents:");
    while (current != NULL) {
        Serial.print("Name: ");
        Serial.println(current->name);
        Serial.print("Phone: ");
        Serial.println(current->phone);
        Serial.println("---------------");
        current = current->next;
    }
}

// Fungsi untuk mencari kontak berdasarkan nama
struct Contact* findContact(const char* name) {
    struct Contact* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Fungsi untuk mengupdate kontak
void updateContact() {
    Serial.println("Enter the name of the contact to update:");
    while (Serial.available() == 0)
        ;
    String name = Serial.readStringUntil('\n');
    name.trim();
    struct Contact* contactToUpdate = findContact(name.c_str());

    if (contactToUpdate == NULL) {
        Serial.println("Contact not found!");
        return;
    }

    Serial.println("Enter new name (max 32 characters):");
    while (Serial.available() == 0)
        ;
    String newName = Serial.readStringUntil('\n');
    newName.trim();
    newName.toCharArray(contactToUpdate->name, MAX_NAME_LENGTH);

    Serial.println("Enter new phone number (max 13 characters):");
    while (Serial.available() == 0)
        ;
    String newPhone = Serial.readStringUntil('\n');
    newPhone.trim();
    newPhone.toCharArray(contactToUpdate->phone, MAX_PHONE_LENGTH);

    Serial.println("Contact updated successfully!");
}

// Fungsi untuk menghapus kontak
void deleteContact() {
    Serial.println("Enter the name of the contact to delete:");
    while (Serial.available() == 0)
        ;
    String name = Serial.readStringUntil('\n');
    name.trim();

    if (head == NULL) {
        Serial.println("Phone book is empty!");
        return;
    }

    struct Contact* contactToDelete = head;
    struct Contact* prev = NULL;

    while (contactToDelete != NULL) {
        if (strcmp(contactToDelete->name, name.c_str()) == 0) {
            if (prev == NULL) {
                head = contactToDelete->next;
            } else {
                prev->next = contactToDelete->next;
            }
            free(contactToDelete);
            Serial.println("Contact deleted successfully!");
            return;
        }
        prev = contactToDelete;
        contactToDelete = contactToDelete->next;
    }

    Serial.println("Contact not found!");
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available() > 0) {
        int choice = Serial.parseInt();
        switch (choice) {
            case 1:
                createContact();
                break;
            case 2:
                readContacts();
                break;
            case 3:
                updateContact();
                break;
            case 4:
                deleteContact();
                break;
            default:
                Serial.println("Invalid choice!");
                break;
        }
        printPrompt();
    }
}
