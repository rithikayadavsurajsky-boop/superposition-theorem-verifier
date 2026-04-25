 #include <stdio.h>
#include <math.h>

// -------- Functions --------

// V1 active, V2 shorted
void solve_source1(float V1, float R1, float R2, float R3,
                   float *Va, float *I1, float *I2, float *I3) {
    float R_parallel = (R2 * R3) / (R2 + R3);

    *I1 = V1 / (R1 + R_parallel);
    *Va = (*I1) * R_parallel;
    *I2 = (*Va) / R2;
    *I3 = (*Va) / R3;
}

// V2 active, V1 shorted
void solve_source2(float V2, float R1, float R2, float R3,
                   float *Va, float *I1, float *I2, float *I3) {
    float R_parallel = (R1 * R3) / (R1 + R3);

    *I2 = V2 / (R2 + R_parallel);
    *Va = (*I2) * R_parallel;
    *I1 = (*Va) / R1;
    *I3 = (*Va) / R3;
}

// Actual circuit
void solve_actual(float V1, float V2, float R1, float R2, float R3,
                  float *Va, float *I1, float *I2, float *I3) {
    float G1 = 1.0 / R1;
    float G2 = 1.0 / R2;
    float G3 = 1.0 / R3;

    *Va = (V1 * G1 + V2 * G2) / (G1 + G2 + G3);

    *I1 = (V1 - *Va) / R1;
    *I2 = (V2 - *Va) / R2;
    *I3 = (*Va) / R3;
}

// -------- Main --------
int main() {

    float V1, V2, R1, R2, R3;
    float Va1, I1a, I2a, I3a;
    float Va2, I1b, I2b, I3b;
    float Va_s, I1_s, I2_s, I3_s;
    float Va, I1, I2, I3;

    printf("========================================\n");
    printf(" SUPERPOSITION THEOREM VERIFIER\n");
    printf("========================================\n");
 
 printf("\nCIRCUIT TOPOLOGY\n");
    printf("--------------------------------------------------\n");

    printf("        V1(+)                          (+)V2\n");
    printf("          |                              |\n");
    printf("          |                              |\n");
    printf("         [R1]                          [R2]\n");
    printf("          |                              |\n");
    printf("          |---------( Va )---------------|\n");
    printf("                     |\n");
    printf("                    [R3]\n");
    printf("                     |\n");
    printf("                    GND\n");

    printf("--------------------------------------------------\n");

    // Input
    printf("\nEnter V1: ");
    scanf("%f", &V1);

    printf("Enter V2: ");
    scanf("%f", &V2);

    printf("Enter R1: ");
    scanf("%f", &R1);

    printf("Enter R2: ");
    scanf("%f", &R2);

    printf("Enter R3: ");
    scanf("%f", &R3);

    // Check for zero resistance
    if (R1 == 0 || R2 == 0 || R3 == 0) {
        printf("Error: Resistance cannot be zero\n");
        return 0;
    }

    // Step 1
    solve_source1(V1, R1, R2, R3, &Va1, &I1a, &I2a, &I3a);
    printf("\nSTEP 1 (V1 only)\n");
    printf("Va = %.4f V\n", Va1);
    printf("I1 = %.4f A\n", I1a);
    printf("I2 = %.4f A\n", I2a);
    printf("I3 = %.4f A\n", I3a);

    // Step 2
    solve_source2(V2, R1, R2, R3, &Va2, &I1b, &I2b, &I3b);
    printf("\nSTEP 2 (V2 only)\n");
    printf("Va = %.4f V\n", Va2);
    printf("I1 = %.4f A\n", I1b);
    printf("I2 = %.4f A\n", I2b);
    printf("I3 = %.4f A\n", I3b);

    // Superposition
    Va_s = Va1 + Va2;
    I1_s = I1a + I1b;
    I2_s = I2a + I2b;
    I3_s = I3a + I3b;

    printf("\nSTEP 3 (Superposition)\n");
    printf("Va = %.4f V\n", Va_s);
    printf("I1 = %.4f A\n", I1_s);
    printf("I2 = %.4f A\n", I2_s);
    printf("I3 = %.4f A\n", I3_s);

    // Actual
    solve_actual(V1, V2, R1, R2, R3, &Va, &I1, &I2, &I3);

    printf("\nSTEP 4 (Actual)\n");
    printf("Va = %.4f V\n", Va);
    printf("I1 = %.4f A\n", I1);
    printf("I2 = %.4f A\n", I2);
    printf("I3 = %.4f A\n", I3);
// -------- VERIFICATION --------
printf("\n========================================\n");
printf(" VERIFICATION\n");
printf("========================================\n");

float errVa = fabs(Va_s - Va);
float errI1 = fabs(I1_s - I1);
float errI2 = fabs(I2_s - I2);
float errI3 = fabs(I3_s - I3);

printf("Va Error = %.6f\n", errVa);
printf("I1 Error = %.6f\n", errI1);
printf("I2 Error = %.6f\n", errI2);
printf("I3 Error = %.6f\n", errI3);

if (errVa < 0.0001 && errI1 < 0.0001 && errI2 < 0.0001 && errI3 < 0.0001)
    printf("\nTHEOREM VERIFIED\n");
else
    printf("\nTHEOREM NOT VERIFIED\n");


// -------- POWER ANALYSIS --------
printf("\n========================================\n");
printf(" POWER ANALYSIS\n");
printf("========================================\n");

float P_R1 = I1 * I1 * R1;
float P_R2 = I2 * I2 * R2;
float P_R3 = I3 * I3 * R3;

float P_V1 = V1 * I1;
float P_V2 = V2 * I2;

printf("Power in R1 = %.4f W\n", P_R1);
printf("Power in R2 = %.4f W\n", P_R2);
printf("Power in R3 = %.4f W\n", P_R3);

printf("Power by V1 = %.4f W\n", P_V1);
printf("Power by V2 = %.4f W\n", P_V2);

float total_dissipated = P_R1 + P_R2 + P_R3;
float total_supplied = P_V1 + P_V2;

printf("\nTotal Power Dissipated = %.4f W\n", total_dissipated);
printf("Total Power Supplied   = %.4f W\n", total_supplied);

if (fabs(total_dissipated - total_supplied) < 0.0001)
    printf("\nPOWER VERIFIED (Conservation holds)\n");
else
    printf("\nPOWER MISMATCH\n");

    // Verification
    if (fabs(Va_s - Va) < 0.0001)
        printf("\nTHEOREM VERIFIED\n");
    else
        printf("\nNOT VERIFIED\n");

    return 0;
}
