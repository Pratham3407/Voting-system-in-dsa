#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATES 5
#define MAX_VOTERS 100

struct Candidate {
    char name[50];
    int votes;
};

struct Voter {
    char name[50];
    int votedFor;
};

struct Candidate candidates[MAX_CANDIDATES] = {
    {"Candidate 1", 0},
    {"Candidate 2", 0},
    {"Candidate 3", 0},
    {"Candidate 4", 0},
    {"Candidate 5", 0}
};

struct Voter voters[MAX_VOTERS];
int numVoters = 0;
int numCandidates = MAX_CANDIDATES;

int stack[MAX_VOTERS];
int top = -1;

int queue[MAX_VOTERS];
int front = -1, rear = -1;

// Stack Functions
int isStackEmpty() {
    return top == -1;
}

void push(int data) {
    if (top < MAX_VOTERS - 1) {
        stack[++top] = data;
    } else {
        printf("Error: Stack is full\n");
    }
}

int pop() {
    if (!isStackEmpty()) {
        return stack[top--];
    } else {
        printf("Error: Stack is empty\n");
        return -1;
    }
}

// Queue Functions
int isQueueEmpty() {
    return (front == -1 && rear == -1);
}

int isQueueFull() {
    return ((front == 0 && rear == MAX_VOTERS - 1) || (rear == (front - 1) % (MAX_VOTERS - 1)));
}

void enqueue(int data) {
    if (isQueueFull()) {
        printf("Error: Queue is full\n");
    } else {
        if (front == -1) front = rear = 0;
        else rear = (rear + 1) % (MAX_VOTERS - 1);
        queue[rear] = data;
    }
}

int dequeue() {
    int data;
    if (isQueueEmpty()) {
        printf("Error: Queue is empty\n");
        return -1;
    } else {
        data = queue[front];
        if (front == rear) front = rear = -1;
        else front = (front + 1) % (MAX_VOTERS - 1);
        return data;
    }
}

void addVoter() {
    if (numVoters < MAX_VOTERS) {
        printf("Enter voter name: ");
        scanf("%s", voters[numVoters].name);
        voters[numVoters].votedFor = 0;
        numVoters++;
    } else {
        printf("Error: Maximum number of voters reached.\n");
    }
}

void castVote() {
    if (numVoters == 0) {
        printf("Error: No voters registered.\n");
        return;
    }

    printf("Registered Voters:\n");
    for (int i = 0; i < numVoters; i++) {
        printf("%d. %s\n", i + 1, voters[i].name);
    }

    int voterIndex;
    printf("Enter the number of the voter who is voting: ");
    scanf("%d", &voterIndex);

    if (voterIndex >= 1 && voterIndex <= numVoters) {
        if (voters[voterIndex - 1].votedFor == 0) {
            printf("Candidates:\n");
            for (int i = 0; i < numCandidates; i++) {
                printf("%d. %s\n", i + 1, candidates[i].name);
            }

            int candidateIndex;
            printf("Enter the number of the candidate you are voting for: ");
            scanf("%d", &candidateIndex);

            if (candidateIndex >= 1 && candidateIndex <= numCandidates) {
                candidates[candidateIndex - 1].votes++;
                voters[voterIndex - 1].votedFor = candidateIndex;
                printf("Thank you for voting!\n");
            } else {
                printf("Invalid candidate number.\n");
            }
        } else {
            printf("Error: This voter has already voted.\n");
        }
    } else {
        printf("Invalid voter number.\n");
    }
}

void displayResults() {
    printf("Results:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("%s : %d votes\n", candidates[i].name, candidates[i].votes);
    }
}

void displayWinner() {
    int maxVotes = -1;
    int winnerIndex = -1;

    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
        } else if (candidates[i].votes == maxVotes) {
            winnerIndex = -1; // Tie
        }
    }

    if (winnerIndex != -1) {
        printf("The winner is %s with %d votes!\n", candidates[winnerIndex].name, candidates[winnerIndex].votes);
    } else {
        printf("It's a tie! No clear winner.\n");
    }
}

int main() {
    printf("Welcome to the DSA Voting System!\n");

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add Voter\n");
        printf("2. Vote\n");
        printf("3. Display Results\n");
        printf("4. Display Winner\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addVoter();
                break;
            case 2:
                castVote();
                break;
            case 3:
                displayResults();
                break;
            case 4:
                displayWinner();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 5);

    return 0;
}
