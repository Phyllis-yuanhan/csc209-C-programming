// TODO: Implement populate_array
/*
 * Convert a 9 digit int to a 9 element int array.
 */
int populate_array(int sin, int *sin_array) {
    for(int i = 0; i < 9; ++i, sin /= 10){
        sin_array[i] = sin % 10;
    }
    return 0;
}

// TODO: Implement check_sin
/*
 * Return 0 if the given sin_array is a valid SIN, and 1 otherwise.
 */
int check_sin(int *sin_array) {
    // find sum of all digit after * 121212121
    int sum = 0;
    if(sin_array[0] == 0){
        return 1;
    }
    for (int i = 0; i < 9; i++){
        if (i%2 == 0){
            sum += sin_array[i];
        }else{
            int new = sin_array[i]*2;
            if(new < 10){
                sum += sin_array[i];
            }else{
                int first = new / 10;
                int second = new - (new / 10) * 10;
                sum += first+second;
                }
        }
    }
    // check if the total will be divisible by 10
    if (sum % 10 == 0){
        return 0;
    }
    return 1;
}
