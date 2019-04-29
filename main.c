#include <stdio.h>
#include <string.h>

void rotationEncrypt(char *x, int key);
void rotationDecrypt(char *x, int key);
void substitutionEncrypt(char *x, char *key);
void substitutionDecrypt(char *x, char *key);
void rotationNoKey(char *x, int option);

int main() {
    int rotationKey, menuOption; // variables used to retreive rotation key from user and menu option input respectively
    char x[100], substitutionKey[30]; // variables used to retreive message input and substitution key respectively
    
    printf("Welcome to ENG1003 Assessment 1\n");
    
    do{
        printf("Please select a encryption/decryption function:\n"); //User Menu will continue displaying until manual exit
        printf("Rotation Method:     (1) Encrypt (2) Decrypt\n");
        printf("Substitution method: (3) Encrypt (4) Decrypt\n");
        printf("(5) Rotation without key (0) Exit program\n");
        scanf("%d", &menuOption);
        
        switch(menuOption){
            case 1:
                printf("Enter message for encryption:\n");
                scanf(" %[^\n]s", x); // [^\n] tells scanf to keep reading until it encounters a new line
                printf("Enter encryption key:");
                scanf("%d", &rotationKey);
                rotationEncrypt(x, rotationKey);
                printf("Your encrypted text:\n");
                printf("%s\n", x);
                break;
            case 2:
                printf("Enter message for decryption: ");
                scanf( " %[^\n]s", x); // [^\n] tells scanf to keep reading until it encounters a new line
                printf("Enter decryption key: ");
                scanf("%d", &rotationKey);
                rotationDecrypt(x, rotationKey);
                printf("Your decrypted text:\n");
                printf("%s\n", x);
                break;
            case 3:
                printf("Enter message for encryption:\n");
                scanf(" %[^\n]s", x); // [^\n] tells scanf to keep reading until it encounters a new line
                printf("Enter encryption key:");
                scanf(" %[^\n]s", substitutionKey);
                substitutionEncrypt(x, substitutionKey);
                printf("Your encrypted text:\n");
                printf("%s\n", x);
                break;
            case 4:
                printf("Enter message for decryption:\n");
                scanf( " %[^\n]s", x); // [^\n] tells scanf to keep reading until it encounters a new line
                printf("Enter decryption key: ");
                scanf("%s", substitutionKey);
                substitutionDecrypt(x, substitutionKey);
                printf("Your decrypted text:\n");
                printf("%s\n", x);
                break;
            case 5:
                printf("Enter message for decryption: ");
                scanf( " %[^\n]s", x); // [^\n] tells scanf to keep reading until it encounters a new line
                int option = 1;               
                char y_n = 'N';
                while(y_n == 'N' && option <= 5){ //allows user to keep checking for other likely decryption keys
                    rotationNoKey(x, option);
                    printf("Your decrypted text:\n");
                    printf("%s\n", x);
                    printf("Does the above look correct? Y/N\n");
                    scanf(" %c", &y_n);
                    option++;
                }
                if(option == 6) 
                    printf("Message may have too few letters or is a statistical outlier.\n");
                break;
            case 0:
                break;
            default: printf("Please try again\n");
        }
    
    }while(menuOption != 0); //Menu will keep running until a 0 is entered
  
  return 0;
}

void rotationEncrypt(char *x, int key){
    int i; //Array index 
    for(i=0; x[i] != '\0'; i++){ //loop terminates when it reaches the end of the array (NULL)
        if(x[i] >= 65 && x[i] <= 90){ //checks for upper-case in ASCII
			x[i] -= 65;
			x[i] = (x[i] + key) % 26; //encryption as per provided formula
			x[i] += 65; // convert back to upper-case ASCII
        }
        
        if(x[i] >= 97 && x[i] <= 122){ //checks for lower-case in ASCII
			x[i] -= 97;
			x[i] = (x[i] + key) % 26; //encryption as per provided formula
			x[i] += 65; //convert back to upper-case ASCII
        }
        
    }
}

void rotationDecrypt(char *x, int key){
    int i;
    for(i=0; x[i] != '\0'; i++){
        if(x[i] >= 65 && x[i] <= 90){ //checks for upper-case in ASCII
            x[i] -= 39; //minus 65 + 26 to avoid passing negative number to modulus operator
			x[i] = (x[i] - key) % 26; //encryption as per provided formula
			x[i] += 65; //convert back to ascii
        }
        
        if(x[i] >= 97 && x[i] <= 122){ //checks for lower-case in ASCII
			x[i] -= 71; //minus 65 + 26 to avoid passing negative number to modulus operator
			x[i] = (x[i] - key) % 26; //encryption as per provided formula
			x[i] += 65; //convert back to upper-case ascii
        }
    }
}

void substitutionEncrypt(char *x, char *key){
    int i;
    for(i=0; x[i] != '\0'; i++){ 
        if(x[i] >= 65 && x[i] <= 90){ // upper case ascii
            x[i] -= 65;
            int temp = x[i];
    		x[i] = key[temp]; //replaces each letter of message with key letter
        }
        
        if(x[i] >= 97 && x[i] <= 122){ // lower case ascii
            x[i] -= 97; 
            int temp = x[i];
    		x[i] = key[temp]; //replaces each letter of message with key letter
        }
    }
}

void substitutionDecrypt(char *x, char *key){
    char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for(i=0; x[i] != '\0'; i++){
        if(x[i] >= 65 && x[i] <= 90){ //upper case ascii
            int d;
    		for (d=0; key[d] != '\0'; d++){ 
    		    if(x[i] == key[d]){ //for each letter in message checks position in key
    		        x[i] = alpha[d]; //replaces encrypted letter with one from the same position in the alphabet (key position = 2 then letter = b)
    		        break;
    		    }
    		}
        }
        
        if(x[i] >= 97 && x[i] <= 122){ //lower case ascii
    		int d;
    		for (d=0; key[d] != '\0'; d++){
    		    if(x[i] == key[d]){ //for each letter in message checks position in key
    		        x[i] = alpha[d]; //replaces encrypted letter with one from the same position in the alphabet (key position = 2 then letter = b)
    		        break;
    		    }
		    }
        }
    }
}

void rotationNoKey(char *x, int option){ //function has multiple outputs for x based on option; 1-5 with 1 being most likely decryption
    int i, key, count[26] = {0}, e;
    for(i = 0; x[i] != '\0'; i++){
        if (x[i] >= 'A' && x[i] <= 'Z') { //UPPER-CASE ASCII
            e = x[i] - 'A'; // determines letters position in array count
            count[e]++; // adds 1 count to letters occurence in string
        }
    }
    
    int max = 0;
    
    for (i = 0; i < 26; i++){
        if(count[i] > max){
            switch(option){
                case 1:
                    key = (i + 1) + 26 - 5; // Assumes that the most commonly occuring letter is E (5th position in alphabet)
                    max = count[i]; //sets the new maximum
                    break;
                case 2:
                    key = (i + 1) + 26 - 20; // Takes second most commonly occuring letter T (20th position in alphabet)
                    max = count[i]; //sets the new maximum
                    break;
                case 3:
                    key = (i + 1) + 26 - 1; // Takes third most commonly occuring letter A (1st position in alphabet)
                    max = count[i]; //sets the new maximum
                    break;
                case 4:
                    key = (i + 1) + 26 - 15; // Takes fourth most commonly occuring letter O (15th position in alphabet)
                    max = count[i]; //sets the new maximum
                case 5:
                    key = (i + 1) + 26 - 9; // Takes fifth most commonly occuring letter I (9th position in alphabet)
                    max = count[i]; //sets the new maximum
                    break;
                default:
                    key = (i + 1) + 26 - 5; // Default assumes E is most commonly occuring
                    max = count[i]; //sets the new maximum
                    break;
            }
        }
    }
    rotationDecrypt(x, key);
}