#include <stdio.h>
#include <ctype.h>
#define max 100

double atof(char s[]){
	double val, power, epower;
	int i = 0;
	
	for(i = 0; s[i] == ' '; i++);
	int sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0; isdigit(s[i]); i++){
		val = 10.0 * val + (s[i] - '0');
	}
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]); i++){
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if(s[i] == 'e' || s[i] == 'E')
		i++;
	int esign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '-' || s[i] == '+')
		i++;
	for(epower = 0.0; isdigit(s[i]); i++){
		epower = 10.0 * epower + (s[i] - '0');
	}
	val = sign * val / power;
	if(esign > 0){
		while(epower--)
			val *= 10.0;
	}
	else{
		while(epower--)
			val /= 10.0;
	}
	
	return val;
}

int getl(char s[]){
	int c, i = 0;
	
	while((c=getchar()) != EOF && c != '\n'){
		s[i++] = c;
	}
	
	return i;
}

int main(){
	char line[max];
	double sum = 0;
	
	while(getl(line)>0){
		printf("%g\n", atof(line));
	}
	
	return 0;
}
