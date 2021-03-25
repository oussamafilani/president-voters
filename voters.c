#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct president president;
struct president
{
    char name[20];
    int countvote ;
    float vote_per_cent;
    int skip;
	//int eliminated;
};

typedef struct voters voters;
struct voters
{
    char cin[20];
};

void vote_count_instial(president * arr_president, int MAX)
{
	int i;
   
	for(i = 0; i < MAX; i++ )
	{
		arr_president[i].countvote = 0;	            
	}
}


void afficher(president * arr_president, int MAX)
{
	int i;
	printf("Name \n");

    printf("\n\n ### Please choose your president ####\n\n");
   
	for(i = 0; i < MAX; i++ )
	{
        printf("%d . %s\n",i+1, 
		arr_president[i].name);	            
	}
}

void saisire(president * arr_president, voters * arr_voters, int MAX,int MAXV)
{
	int i,j;

    for( i = 0; i < MAX; i++ )
    {
        printf("\nEnter details of president %d\n\n", i+1);

        printf("Enter name: ");
        scanf("%s", arr_president[i].name);
        
    }
   
	for(j = 0; j < MAXV; j++ )
    {
        printf("\nEnter details of Voters %d\n\n", j+1);

        printf("Enter Votre CIN: ");
        scanf("%s", arr_voters[j].cin);

    }
}

void choix(president * arr_president, voters * arr_voters, int MAXV, int MAX)
{
	int i;
	int choice;
	
	int t ;
	
	do{
		for(i = 0; i < MAXV; i++ )
	    {
	    	printf("\nCIN %s votting on : ",
	        arr_voters[i].cin);
	    	scanf("%d",&choice);
	    	
	    	while( 1 ) {
	    		if ( choice >= 1 && choice <= MAX ) {
	    			printf("\nyour vote has been processed\n");
	    			break;
				}
				
				printf("\nInvalid Choice, please try again.\n");
				printf("\nCIN %s votting on : ",arr_voters[i].cin);
				scanf("%d", &choice);
			}

			arr_president[choice-1].countvote++;			
		}
		
		
	t = equal(arr_president, MAX);
	if(t == MAX)
	{
		printf("\n\n ##### The Presidents have the same number of votes Try Again ####");
		vote_count_instial(arr_president,MAX);
	}
					
	}while(t == MAX);
	    	
}


int  equal(president * arr_president, int MAX)
{
	int t=0;
	int i;
	int choice;

	int equal = arr_president[0].countvote;
	for(i=0; i<MAX; i++)
	{
		if(arr_president[i].countvote == equal)
		{
			t++;
		}
	}
	return t;
}


int  round1_selection(president *  arr_president, president * arr_president_round2, int MAX, int MAXV)
{
	printf("\n\n ##### Result First Round ####");
	int s = 0;
	int i;
	for(i = 0; i < MAX; i++ )
	{		
		arr_president[i].vote_per_cent = arr_president[i].countvote;
		if(arr_president[i].vote_per_cent/MAXV*100 > 15)
		{
		
			printf("\n%d .|  %s -| %d| ",i+1, arr_president[i].name, arr_president[i].countvote);
			
			strcpy(arr_president_round2[s].name,arr_president[i].name);
			s++;	
		}		            
	}
	return s;
	
}



int  round2_selection(president *  arr_president, president *  arr_president_round2, president * arr_president_round3, int s, int MAXV)
{
	printf("\n\n ##### Result Second Round ####");
	int i;
	int min = indiceMin(arr_president_round2, s);
	int c = 0;
	for(i = 0; i < s; i++ )
		{
			if (arr_president_round2[i].countvote != min)
			{ 
			printf("\n%d .  %s - %d ",i, arr_president_round2[i].name, arr_president_round2[i].countvote); 
			strcpy(arr_president_round3[c].name,arr_president_round2[i].name);
			arr_president_round3[i].skip = 3;
			c++;
			}	        
	    }	
	
	return c;
}

void  round3_selection(president * arr_president_round3, int c,voters * arr_voters,int MAXV)
{
	
	int i;
	int max = indiceMax(arr_president_round3, c);
	int t = equal(arr_president_round3, c);
	
	for(i = 0; i < c; i++ )
	{
	
		//tmp and inice max 
		while( 1 ) {
	    		if (arr_president_round3[i].countvote == max && t <= 2 && arr_president_round3[i].skip == 3) {
	    				printf("\n\n ##### The Winner President  number %d ####",i);
						printf("\n%d .  %s - %d ",i, arr_president_round3[i].name, arr_president_round3[i].countvote); 
	    			break;
				}
				
				printf("\n\n ##### You have more than one Presidents Try Again ####");
				vote_count_instial(arr_president_round3, c);
				choix(arr_president_round3,arr_voters, MAXV, c);
				round3_selection(arr_president_round3, c,arr_voters, MAXV);
			}		
		        
	}
}

int indiceMin(president *  arr_president, int n)
{
	int i;
	int min = arr_president[0].countvote;
	for(i=0; i<n; i++)
	
	{
		if(arr_president[i].countvote < min)
		{
			min=arr_president[i].countvote;
		}
	}
	return min;
}

int indiceMax(president *  arr_president, int n)
{
	int i;
	int max = arr_president[0].countvote;
	
	for(i=0; i<n; i++)
	{
		if(arr_president[i].countvote > max)
		{
			max=arr_president[i].countvote;
		}
	}
	return max;
}

void affiche_pre_round(president *  arr_president, int n)
{
	int i;
	for(i = 0; i < n; i++ )
		{
		
			printf("\n%d .  %s - %d ",i+1, arr_president[i].name, arr_president[i].countvote);         
		}
}
int main()
{
	
	int MAX, MAXV ,choice ;
	printf("Enter the number of list presidents :  ");
	
    scanf("%d", &MAX);
    while (MAX < 5)
    {
    	printf("Enter the number again :  ");
    	scanf("%d", &MAX);
    	
	}
	
	printf("Enter the number of list voters:  ");
	
    scanf("%d", &MAXV);
    while (MAXV < 10)
    {
    	printf("Enter the number again :  ");
    	scanf("%d", &MAXV);
    	
	}
	
//********************************************

    voters* arr_voters;
	arr_voters= (voters*)malloc(MAXV * sizeof(voters));	
    
    president* arr_president;
    arr_president= (president*)malloc(MAX * sizeof(president));
    
    president* arr_president_round2;
    arr_president_round2= (president*)malloc(MAX * sizeof(president));
    
    president* arr_president_round3;
    arr_president_round3= (president*)malloc(MAX * sizeof(president));
    

	vote_count_instial(arr_president,  MAX);
    vote_count_instial(arr_president_round2,  MAX);
    vote_count_instial(arr_president_round3,  MAX);
 
    saisire(arr_president,arr_voters,MAX,MAXV);
 
	afficher(arr_president,MAX);

		    
	printf("\nRound 1 Input your choice (1 - %d) : \n",MAX);
	
	choix(arr_president,arr_voters, MAXV,MAX);
   
   

   int s = round1_selection(arr_president, arr_president_round2, MAX, MAXV);

	
   //Round 1 
	printf("\n\n ### Round 2 Please choose your president ####\n\n");
	affiche_pre_round(arr_president_round2, s);



   //Round 2
   
	printf("\nRound 2 Input your choice (1 - %d) : \n",s);
	
	choix(arr_president_round2,arr_voters, MAXV, s);
  
	int c =  round2_selection(arr_president, arr_president_round2, arr_president_round3,s,MAXV);
		

    //Round 3
		
	printf("\n\n ### Round 3 Please choose your president ####\n\n"); 
	affiche_pre_round(arr_president_round3, c); 
	
	printf("\nRound 3 Input your choice (1 - %d) : \n",c);
	choix(arr_president_round3,arr_voters, MAXV, c);

	round3_selection(arr_president_round3, c, arr_voters, MAXV);
	
//********************************************

    return 0;
}
