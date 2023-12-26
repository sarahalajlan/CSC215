#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>


struct Taxi {
  int id; 
  char driver[20] , category[20] , plate[7] , color[20];
  float rate , minCharge;
  char state;
  struct Taxi *next;
} *list;


void addTripCar() {
  FILE *fp = fopen("Taxies.txt", "r");
  if (fp == NULL) {
    perror("Error opening file\n");
    return;
  }

int id;
char driver[20] , category[20] , plate[7] , color[20];
float rate , minCharge;
struct Taxi *temp=list , *current;

char *line = (char*)malloc(sizeof(char)*100);
fgets(line, 100, fp);
free(line);

while (fscanf(fp,"%d\t%[^\t]\t%s\t%s\t%s\t%f\t%f\n", &id, driver, category, plate, color, &rate, &minCharge) != EOF) {   
        temp = (struct Taxi*)malloc(sizeof(struct Taxi));
        temp->id = id;
        strcpy(temp->driver, driver);
        strcpy(temp->category, category);
        strcpy(temp->plate, plate);
        strcpy(temp->color, color);
        temp->rate = rate;
        temp->minCharge = minCharge;
        temp->state = 'A';
        temp->next = NULL;
        if(list==NULL){
            list=temp;
            current=list;
        }
        else {
            current->next=temp;
            current=temp;
        }
    }
    if(fclose(fp)!=0)
    perror("Error closing file\n");
}

void setTripCar(char* category, float* rate) { 
    if(list==NULL){
        printf("Empty list\n");
        return;
    }
    struct Taxi *temp = list;

    while(temp!=NULL){
        if((strcmp(temp->category , category) == 0) && (temp->rate == *rate) && (temp->state=='A')){
            temp->state='R';
            return;
        }
            temp=temp->next;

    }
}

void writeCarsInRide (char* fileName){ 
    if(list ==NULL){
        printf("Empty list\n");
        return;
    }
    FILE *fp = fopen(fileName,"a");
    if(fp==NULL){
        perror("Error opening file\n");
        return;
    }

    fprintf(fp,"\n--------------------------------------------------------------------------------------------------------------\nThe Car in Ride:\n");
    fprintf(fp, "%-3s\t%-6s\t%-8s\t%-6s\t%-3s\t%-1s\n", "id", "driver", "category","plate", "rate","state" );
    struct Taxi *temp ;
    temp=list;

    while(temp!=NULL){
        if(temp->state=='R'){
            fprintf(fp,"%-3d\t%-6s\t%-8s\t%-6s\t%-.1f\t%c\n",temp->id,temp->driver,temp->category,temp->plate,temp->rate,temp->state);
        }
        temp=temp->next;
    }

    if(fclose(fp)!=0)
    perror("Error closing file\n");
}

void printList(){
    if(list ==NULL){
        printf("Error list\n");
        return;
    }
    struct Taxi *temp ;
    temp=list;

    while(temp!=NULL){
        printf("%-3d\t%-6s\t%-8s\t%-6s\t%-.1f\t%-.2f\t%c\n",(temp->id),temp->driver,temp->category,temp->plate,(temp->rate),(temp->minCharge),temp->state);
        temp=temp->next;
    }
}


int main(){
    addTripCar();
  int i;
    printf("The Available Trip cars:\n");
    printList();
    printf("--------------------------------------------------------------------------------------------------------------\n");

    char *Categorys[]={"Business","Family","Family","standard","standard"};
    float rates[]={4.5,5.0,4.0,3.4,5.0};
    for( i = 0 ; i < 5 ; i++)
        setTripCar(*(Categorys+i),(rates+i));

    printf("The Cars in Ride:\n");
    printList();

    char *fileName ="Taxies.txt";
    writeCarsInRide(fileName);

    return 0;
}
