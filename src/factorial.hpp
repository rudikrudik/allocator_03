#pragma once

int factorialCalc(int number){
    int result = 1;
    for(int i = 2; i <= number; i++){
        result *= i;
    }
    return result;
}