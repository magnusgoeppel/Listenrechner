#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Zahl, Operator oder Klammer
enum node_type
{
    number_type = 1, operator_type, parenthesis_type
};

// Liste
struct node
{
    char operator;
    int number;
    enum node_type type;
    struct node* next;
};

struct node* inputToNode(const char *input);
struct node* createParenthesisNode(char operator);
struct node* createOperatorNode(char operator);
struct node* createNumberNode(int number);
struct node* calculation(struct node* head, struct node *number);

// Fügt die Zahlen, Operatoren und Klammern in eine Liste ein
struct node *inputToNode(const char *input)
{
    int number = atoi(input);

    if (number != 0)
    {
        return createNumberNode(number);
    }
    if (input[0] == '0')
    {
        return createNumberNode(0);
    }
    if (strcmp(input, "(") == 0 ||
        strcmp(input, ")") == 0)
    {
        return createParenthesisNode(input[0]);
    }

    if (strcmp(input, "+") == 0 ||
        strcmp(input, "-") == 0 ||
        strcmp(input, "*") == 0 ||
        strcmp(input, "/") == 0)
    {
        return createOperatorNode(input[0]);
    }
    return NULL;
}

// Erstellt eine Klammer
struct node* createParenthesisNode(char operator)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode -> type = parenthesis_type;
    newNode -> operator = operator;
    newNode -> next = NULL;
    return newNode;
}

// Erstellt einen Operator
struct node* createOperatorNode(char operator)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode -> type = operator_type;
    newNode -> operator = operator;
    newNode -> next = NULL;
    return newNode;
}

// Erstellt eine Zahl
struct node* createNumberNode(int number)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode -> type = number_type;
    newNode -> number = number;
    newNode -> next = NULL;
    return newNode;
}

// Findet den ersten PunktOperator in der Liste
struct node *findFirstPointOperator(struct node *head)
{
    // Wenn die Liste leer ist, gibt es keinen PunktOperator
    struct node *currentNode = head;

    // Wenn die Liste nicht leer ist, wird der erste PunktOperator gesucht
    while (currentNode -> next != NULL)
    {
        // Wenn der nächste Knoten ein PunktOperator ist, wird er zurückgegeben
        if (currentNode -> next -> type == operator_type && (currentNode -> next -> operator == '*' || currentNode -> next -> operator == '/'))
        {
            return currentNode;
        }
        // Wenn der nächste Knoten kein PunktOperator ist, wird der nächste Knoten überprüft
        currentNode = currentNode -> next;
    }
    // Wenn kein PunktOperator gefunden wurde, wird NULL zurückgegeben
    return NULL;
}

// Findet den ersten StrichOperator in der Liste
struct node *findFirstDashOperator(struct node *head)
{
    // Wenn die Liste leer ist, gibt es keinen StrichOperator
    struct node *currentNode = head;

    // Wenn die Liste nicht leer ist, wird der erste StrichOperator gesucht
    while (currentNode -> next != NULL)
    {
        // Wenn der nächste Knoten ein StrichOperator ist, wird er zurückgegeben
        if (currentNode -> next -> type == operator_type && (currentNode -> next -> operator == '+' || currentNode -> next -> operator == '-'))
        {
            return currentNode;
        }
        // Wenn der nächste Knoten kein StrichOperator ist, wird der nächste Knoten überprüft
        currentNode = currentNode -> next;
    }
    // Wenn kein StrichOperator gefunden wurde, wird NULL zurückgegeben
    return NULL;
}

// Findet die erste Klammer in der Liste
struct node *findLastParenthesis(struct node *head)
{
    // Wenn die Liste leer ist, gibt es keine Klammer
    struct node *currentNode = head;

    // Wenn die Liste nicht leer ist, wird die erste Klammer gesucht
    while (currentNode -> next != NULL)
    {
        // Wenn der nächste Knoten eine Klammer ist, wird er zurückgegeben
        if (currentNode -> next -> type == parenthesis_type)
        {
            return currentNode;
        }
        // Wenn der nächste Knoten keine Klammer ist, wird der nächste Knoten überprüft
        currentNode = currentNode -> next;
    }
    // Wenn keine Klammer gefunden wurde, wird NULL zurückgegeben
    return NULL;
}

// Fügt eine Zahl am Ende der Liste ein
struct node* addLast(struct node *head, struct node *newHead)
{
    // Aktueller Knoten
    struct node* current = head;

    // Wenn die Liste nicht leer ist, wird die Zahl am Ende eingefügt
    if (current == NULL)
    {
        return newHead;
    }

    // Wenn die Liste leer ist
    while (current -> next != NULL)
    {
        // Wenn der nächste Knoten nicht der letzte Knoten ist, wird der nächste Knoten überprüft
        current = current -> next;
    }
    // Wenn der nächste Knoten der letzte Knoten ist, wird die Zahl am Ende eingefügt
    current -> next = newHead;
    // Setze den nächsten Knoten auf NULL
    newHead -> next = NULL;

    // Gibt die Liste zurück
    return head;
}

// Ausgabe der Liste
void printList(struct node *head, int mode)
{
    // Aktueller Knoten
    struct node *current = head;

    // Print Term
    if (mode == 0)
    {
        printf("\nTerm: ");
    }
        // Print Result
    else if (mode == 1)
    {
        printf("\nResulting term: ");
    }

    // Wenn die Liste nicht leer ist, wird sie ausgegeben
    while (current != NULL)
    {
        // Wenn der aktuelle Knoten eine Zahl ist, wird die Zahl ausgegeben
        if (current -> type == number_type)
        {
            printf("%d", current -> number);
        }
            // Wenn der aktuelle Knoten ein Operator ist, wird der Operator ausgegeben
        else
        {
            printf("%c", current -> operator);
        }
        // Setze den aktuellen Knoten auf den nächsten Knoten
        current = current -> next;
    }
}

// Ergebnis der Berechnung
int result(int number1, int number2, char operator)
{
    // Überprüft den Operator und gibt das Ergebnis zurück
    switch (operator)
    {
        case '+':
            return number1 + number2;
        case '-':
            return number1 - number2;
        case '*':
            return number1 * number2;
        case '/':
            // Division durch 0 ist gleich 1
            if (number2 == 0)
            {
                number2 = 1;
            }
            return number1 / number2;
            // Bei falschem Operator wird 0 zurückgegeben
        default:
            return 0;
    }
}

struct node* findMatchingOpenParenthesis(struct node *head, struct node *closeParen) {
    struct node *currentNode = head;
    int count = 0;

    // Iterate through the list until the close parenthesis is found
    while (currentNode != closeParen) {
        if (currentNode->type == parenthesis_type) {
            if (currentNode->operator == '(') {
                count++;
            } else if (currentNode->operator == ')') {
                count--;
            }
        }
        if (count == 0) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

struct node* evaluateWithinParentheses(struct node *openParen, struct node *closeParen) {
    struct node *currentNode = openParen->next;
    struct node *resultNode = NULL;
    struct node *pointOperator = NULL;
    struct node *dashOperator = NULL;

    // Find the first point and dash operator in the list
    pointOperator = findFirstPointOperator(currentNode);
    dashOperator = findFirstDashOperator(currentNode);

    // Evaluate the point operators first
    while (pointOperator != NULL)
    {
        resultNode = calculation(currentNode, pointOperator->next);
        pointOperator->next = resultNode;
        pointOperator = findFirstPointOperator(currentNode);
    }
    // Evaluate the dash operators
    while (dashOperator != NULL) {
        resultNode = calculation(currentNode, dashOperator->next);
        dashOperator->next = resultNode;
        dashOperator = findFirstDashOperator(currentNode);
    }

    // If there are no operators left, return the number node
    if (resultNode == NULL) {
        return currentNode;
    }
    // Otherwise, return the result node
    return resultNode;
}



struct node* calculation(struct node* head, struct node *number)
{
    // Aktueller Knoten
    struct node *current = head;

    // Wenn der aktuelle Knoten keine Nummer ist, wird der nächste Knoten überprüft
    while (current != number)
    {
        current = current -> next;
    }
    // Der aktuelle Knoten ist die erste Nummer
    struct node *firstNumber = current;
    // Der nächste Knoten ist der Operator
    struct node *operator = current -> next;
    // Der übernächste Knoten ist die zweite Nummer
    struct node *secondNumber = current -> next -> next;

    // Berechnung der beiden Zahlen
    number -> number = result(firstNumber -> number, secondNumber -> number, operator -> operator);
    // Gehe zum nächsten Operator (führt die Liste zusammen)
    number -> next = secondNumber -> next;

    // Löscht den Operator
    free(operator);
    // Löscht die zweite Zahl
    free(secondNumber);

    // Gibt die Liste aus
    printList(head, 1);

    // Gibt die Liste zurück
    return head;
}


// Löscht die Liste
void deleteList(struct node* head)
{
    // Aktueller Knoten
    struct node* current = head;
    // Nächster Knoten
    struct node* next;

    // Wenn die Liste nicht leer ist
    while (current != NULL)
    {
        // Nächster Knoten ist der nächste Knoten vom aktuellen Knoten
        next = current -> next;
        // Löscht den aktuellen Knoten
        free(current);
        // Setzt den aktuellen Knoten auf den nächsten Knoten
        current = next;
    }
}

int main()
{
    // Kopf der Liste
    struct node* head = NULL;
    // Aktueller Knoten
    struct node* current = NULL;
    // Eingabe
    char input[24];

    // Term
    while (1)
    {
        printf("\nInput:");
        scanf("%s", input);

        // "=" beendet die Eingabe
        if (strcmp(input, "=") == 0)
        {
            break;
        }
        // Erstellt den aktuellen Knoten
        current = inputToNode(input);
        // Fügt den aktuellen Knoten am Ende der Liste ein
        head = addLast(head, current);
        // Gibt die Liste aus
        printList(head, 0);
    }
    // Resulting term (PointOperator)
    while (1)
    {
        // Aktueller Knoten ist der erste Knoten vor einem PunktOperator
        current = findFirstPointOperator(head);

        // Wenn kein PunktOperator gefunden wurde, wird die Liste berechnet
        if (current == NULL)
        {
            break;
        }
        // Berechnet die Liste
        head = calculation(head, current);
    }
    // Resulting term (DashOperator)
    while (1)
    {
        // Aktueller Knoten ist der erste Knoten vor einem DashOperator
        current = findFirstDashOperator(head);

        // Wenn kein DashOperator gefunden wurde, wird die Liste berechnet
        if (current == NULL)
        {
            break;
        }
        // Berechnet die Liste
        head = calculation(head, current);
    }
    // Liste löschen
    deleteList(head);

    return 0;
}