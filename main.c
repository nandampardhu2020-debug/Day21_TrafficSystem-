#include <stdio.h>
#include <stdlib.h>

#define MAX 30


void inputData(int vehicleID[], int speed[], int lane[], int *n);
int countSpeedViolations(int speed[], int n);
int countLaneViolations(int vehicleID[], int lane[], int n);
int busiestLane(int laneCount[]);
int leastBusyLane(int laneCount[]);
void displayReport(int vehicleID[], int speed[], int lane[], int n);

int main() {
    int vehicleID[MAX], speed[MAX], lane[MAX];
    int laneCount[4] = {0};
    int n, i;

    // 1) INPUT DATA
    inputData(vehicleID, speed, lane, &n);

    // COUNT vehicles per lane
    for(i = 0; i < n; i++) {
        laneCount[lane[i] - 1]++;
    }

    // 2) SPEED VIOLATIONS
    int speedViolations = countSpeedViolations(speed, n);

    // 3) LANE VIOLATIONS
    int laneViolations = countLaneViolations(vehicleID, lane, n);

    // 4) Density analysis
    int busiest = busiestLane(laneCount);
    int leastBusy = leastBusyLane(laneCount);

    // 5) FINAL REPORT
    displayReport(vehicleID, speed, lane, n);

    printf("\n=== SUMMARY ===\n");
    printf("Total Speed Violations : %d\n", speedViolations);
    printf("Total Lane Violations  : %d\n", laneViolations);
    printf("Busiest Lane           : %d\n", busiest);
    printf("Least Busy Lane        : %d\n", leastBusy);
    printf("Total Traffic Volume   : %d\n", n);

    return 0;
}


void inputData(int vehicleID[], int speed[], int lane[], int *n) {
    int i;

    printf("Enter number of vehicles (max 30): ");
    scanf("%d", n);

    if(*n > MAX) *n = MAX;

    for(i = 0; i < *n; i++) {
        printf("\nVehicle %d:\n", i + 1);

        printf("Enter Vehicle ID (4-digit): ");
        scanf("%d", &vehicleID[i]);

        do {
            printf("Enter Speed (positive): ");
            scanf("%d", &speed[i]);
        } while(speed[i] <= 0);

        do {
            printf("Enter Lane (1-4): ");
            scanf("%d", &lane[i]);
        } while(lane[i] < 1 || lane[i] > 4);
    }
}

(int speed[], int n) {
    int count = 0, i;

    for(i = 0; i < n; i++) {
        if(speed[i] > 80) count++;
    }

    return count;
}


int countLaneViolations(int vehicleID[], int lane[], int n) {
    int count = 0, i;

    for(i = 0; i < n; i++) {
        if(vehicleID[i] % 4 != lane[i]) {
            count++;
        }
    }
    return count;
}


int busiestLane(int laneCount[]) {
    int max = laneCount[0], lane = 1, i;
    for(i = 1; i < 4; i++) {
        if(laneCount[i] > max) {
            max = laneCount[i];
            lane = i + 1;
        }
    }
    return lane;
}


int leastBusyLane(int laneCount[]) {
    int min = laneCount[0], lane = 1, i;
    for(i = 1; i < 4; i++) {
        if(laneCount[i] < min) {
            min = laneCount[i];
            lane = i + 1;
        }
    }
    return lane;
}


void displayReport(int vehicleID[], int speed[], int lane[], int n) {
    int i;
    printf("\n--------------------------------------------------\n");
    printf("VehID   Speed   Lane   SpeedViol   LaneViol\n");
    printf("--------------------------------------------------\n");

    for(i = 0; i < n; i++) {
        int sv = (speed[i] > 80) ? 1 : 0;
        int lv = (vehicleID[i] % 4 != lane[i]) ? 1 : 0;

        printf("%4d   %5d    %2d        %d          %d\n",
               vehicleID[i], speed[i], lane[i], sv, lv);
    }
}
