#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int cluster_number;
int i,j;						//Free Variables for looping purposes
int m,n,o;						//For cluster indexing purpose 
int total_rows;						//Rows in file
int sum1,sum2,sum3,sum4,sum5;				//Sum of elements of cluster
int m1,m2,m3,m4,m5;					//Mean of elements of cluster	
int l1,l2,l3;						//Variables for count of cluster labels
int cluster_labels[3];					//Final container to save cluster label
int flag = 0;						// For optional execution of certain commands


//Container to store the data from file
struct data
{
	int sport;					//Source Port Number
	int dport;					//Destination Port Number
	int sbytes;					//Source bytes transferred
	int dbytes;					//Destination bytes transferred
	int protocol;					//Protocol Used
	int label;
};

struct data initial_data[100];				//For data
struct data mean[3];					//For mean
struct data old_mean[3];				//For comparing if old and new means same(Stopping condition)

//Defining clusters to store data
struct data cluster1[100];
struct data cluster2[100];
struct data cluster3[100];


int check();					//To compare old and new mean
void cluster();					//To print final cluster


//For reading file to container

void readData()
{
	i = 0;
	total_rows = 0;
	char location[20];
	scanf("%s",location);

	FILE* ptr = fopen(location,"r");
	if(ptr==NULL)
		{
			printf("no such file.");
			exit(0);
		}	

	while(fscanf(ptr,"%d %d %d %d %d",&initial_data[i].sport,&initial_data[i].dport,&initial_data[i].sbytes,&initial_data[i].dbytes,&initial_data[i].protocol)==5)
	{	
		total_rows = i++;
	}	

}

void readData2()
{
	i = 0;
	total_rows = 0;
	char location[20];
	scanf("%s",location);

	FILE* ptr = fopen(location,"r");
	if(ptr==NULL)
		{
			printf("no such file.");
			exit(0);
		}	

while(fscanf(ptr,"%d %d %d %d %d %d",&initial_data[i].sport,&initial_data[i].dport,&initial_data[i].sbytes,&initial_data[i].dbytes,&initial_data[i].protocol,&initial_data[i].label)==6)

	{	
		total_rows = i++;
	}

}


void initialize_mean()
{
	for(i=0;i<3;i++)
	{
	mean[i].sport=initial_data[i].sport;
  	mean[i].dport=initial_data[i].dport;
	mean[i].sbytes=initial_data[i].sbytes;
	mean[i].dbytes=initial_data[i].dbytes; 
	mean[i].protocol=initial_data[i].protocol;
	}
}


// For purpose of distance calculation n=cluster no, k= initial cluster value index

int result(struct data mydata[],int n,int k)
{
	return sqrt(pow((mean[n].sport-mydata[k].sport),2)+pow((mean[n].dport-mydata[k].dport),2)+pow((mean[n].sbytes-mydata[k].sbytes),2)+pow((mean[n].dbytes-mydata[k].dbytes),2)+pow((mean[n].protocol-mydata[k].protocol),2));
}


void distance(struct data *mydata,int number)
{
	int t1,t2,t3;
	if(flag == 0)
	{	
		t1=t2=t3=m=n=o=0;
	}
	for(j=0;j<=number;j++)
	{
		t1= result(mydata,0,j);
		t2= result(mydata,1,j);
		t3= result(mydata,2,j);
		
		// printf("t1=%d\n t2=%d\n t3=%d\n",t1,t2,t3);	

		// To get the minimum distance  	
	
		int min = ( t1<t2 ) ? ( t1<t3 ? t1 : t3 ) : ( t2<t3 ? t2 : t3 );    
	
		//Cluster assignment
	
		if(min == t1)
		{
			cluster_number = 0;	
			cluster1[m].sport=mydata[j].sport;
 		 	cluster1[m].dport=mydata[j].dport;
			cluster1[m].sbytes=mydata[j].sbytes;
			cluster1[m].dbytes=mydata[j].dbytes; 
			cluster1[m].protocol=mydata[j].protocol;
			cluster1[m].label=mydata[j].label;
			m++;
		}
		
		else if(min == t2)
		{
			cluster_number = 1;
			cluster2[n].sport=mydata[j].sport;
 		 	cluster2[n].dport=mydata[j].dport;
			cluster2[n].sbytes=mydata[j].sbytes;
			cluster2[n].dbytes=mydata[j].dbytes; 
			cluster2[n].protocol=mydata[j].protocol;	
			cluster2[n].label=mydata[j].label;
			n++;
		}

		else
		{
			cluster_number = 2;
			cluster3[o].sport=mydata[j].sport;
 		 	cluster3[o].dport=mydata[j].dport;
			cluster3[o].sbytes=mydata[j].sbytes;
			cluster3[o].dbytes=mydata[j].dbytes; 
			cluster3[o].protocol=mydata[j].protocol;	
			cluster3[o].label=mydata[j].label;
			o++;
		}	
	}
}


void each_mean(int k,int n)
{
		m1=sum1/k;
		m2=sum2/k;
		m3=sum3/k;
		m4=sum4/k;
		m5=sum5/k;

		mean[n].sport=m1;
		mean[n].dport=m2;
		mean[n].sbytes=m3;
		mean[n].dbytes=m4;
		mean[n].protocol=m5;					

}



void assign_old_mean()						//function to store old mean to compare with new mean
{
	for(i=0;i<3;i++)
	{
	old_mean[i].sport=mean[i].sport;
  	old_mean[i].dport=mean[i].dport;
	old_mean[i].sbytes=mean[i].sbytes;
	old_mean[i].dbytes=mean[i].dbytes; 
	old_mean[i].protocol=mean[i].protocol;
	}
}


void mean_calculations()					//Function to perform calculations related to means
{

	sum1=sum2=sum3=sum4=sum5=0;
	m1=m2=m3=m5=m4=0;		

	if(m!=0)
	{
		for(i=0;i<m;i++)
		{
			sum1+=cluster1[i].sport;
			sum2+=cluster1[i].dport;
			sum3+=cluster1[i].sbytes;
			sum4+=cluster1[i].dbytes;
			sum5+=cluster1[i].protocol;			
		}
		
		each_mean(m,0);					//Calculate and update mean 
	}

	sum1=sum2=sum3=sum4=sum5=0;				//Update the sum again for next cycle

	if(n!=0)
	{
		for(i=0;i<n;i++)
		{
			sum1+=cluster2[i].sport;
			sum2+=cluster2[i].dport;
			sum3+=cluster2[i].sbytes;
			sum4+=cluster2[i].dbytes;
			sum5+=cluster2[i].protocol;			
		}

	
		each_mean(n,1);					//Calculate and update mean 

	}

	sum1=sum2=sum3=sum4=sum5=0;				//Update the sum again for next cycle

	if(o!=0)
	{

		for(i=0;i<o;i++)
		{
			sum1+=cluster3[i].sport;
			sum2+=cluster3[i].dport;	
			sum3+=cluster3[i].sbytes;
			sum4+=cluster3[i].dbytes;
			sum5+=cluster3[i].protocol;			
		}

		
		each_mean(o,2);					//Calculate and update mean 

	}
}


void calculate_new_mean()
{
	
	/* For result verification purpose
	printf("m=%d n=%d o=%d",m,n,o);
	for(i=0;i<m;i++)
	{
		printf("\n%d %d %d %d %d",cluster1[i].sport,cluster1[i].dport,cluster1[i].sbytes,cluster1[i].dbytes,cluster1[i].protocol);			
	}

	for(i=0;i<n;i++)
	{
		printf("\n%d %d %d %d %d",cluster2[i].sport,cluster2[i].dport,cluster2[i].sbytes,cluster2[i].dbytes,cluster2[i].protocol);			
	}
	for(i=0;i<o;i++)
	{
		printf("\n%d %d %d %d %d",cluster3[i].sport,cluster3[i].dport,cluster3[i].sbytes,cluster3[i].dbytes,cluster3[i].protocol);			
	}*/

	do
	{
		assign_old_mean();				//Assigning old mean before calculating new mean	
		mean_calculations();
	
	}	while(check()!=1);

}

int check()
{
   for(i=0;i<3;i++)
    {
	if(old_mean[i].sport!=mean[i].sport)
	{
		distance(initial_data,total_rows);
		return 0;
	}
  	if(old_mean[i].dport!=mean[i].dport)
	{
		distance(initial_data,total_rows);
		return 0;
	}
	if(old_mean[i].sbytes!=mean[i].sbytes)
	{
		distance(initial_data,total_rows);
		return 0;
	}	
	if(old_mean[i].dbytes!=mean[i].dbytes)
	{
		distance(initial_data,total_rows);
		return 0;
	}
	if(old_mean[i].protocol!=mean[i].protocol)
	{
		distance(initial_data,total_rows);
		return 0;
	}
    }
	return 1;
	
}


void cluster_mean()
{
	 mean_calculations();
}


void cluster()
{
	for(i=0;i<m;i++)
	{
		printf("\n\nCluster1:%d %d %d %d %d %d",cluster1[i].sport,cluster1[i].dport,cluster1[i].sbytes,cluster1[i].dbytes,cluster1[i].protocol,cluster1[i].label);			
	}

	for(i=0;i<n;i++)
	{
		printf("\n\nCluster2:%d %d %d %d %d %d",cluster2[i].sport,cluster2[i].dport,cluster2[i].sbytes,cluster2[i].dbytes,cluster2[i].protocol,cluster2[i].label);			
	}
	for(i=0;i<o;i++)
	{
		printf("\n\nCluster3:%d %d %d %d %d %d",cluster3[i].sport,cluster3[i].dport,cluster3[i].sbytes,cluster3[i].dbytes,cluster3[i].protocol,cluster3[i].label);			
	}
}


void label()
{
//	int min = ( t1<t2 ) ? ( t1<t3 ? t1 : t3 ) : ( t2<t3 ? t2 : t3 );
	for(i=0;i<m;i++)
	{
		l1=l2=l3=0;
		cluster1[i].label==1 ? l1++ : cluster1[i].label==-1 ? l2++ :  l3++;
		
	}
	cluster_labels[0] = ( l1>l2 ) ? ( l1>l3 ? 1 : -2 ) : ( l2>l3 ? -1 : -2 );
	

	for(i=0;i<n;i++)
	{
		l1=l2=l3=0;
		cluster2[i].label==1 ? l1++ : cluster2[i].label==-1 ? l2++ :  l3++;
	}
	cluster_labels[1] = ( l1>l2 ) ? ( l1>l3 ? 1 : -2 ) : ( l2>l3 ? -1 : -2 );
	
	for(i=0;i<o;i++)
	{
		l1=l2=l3=0;
		cluster3[i].label==1 ? l1++ : cluster3[i].label==-1 ? l2++ :  l3++;
	}
	cluster_labels[2] = ( l1>l2 ) ? ( l1>l3 ?  : -2 ) : ( l2>l3 ? -1 : -2 );
	
}


void test()
{
	printf("\n\nEnter the location of test file to read:");
	readData2();
	distance(initial_data,total_rows);
	printf("\n\nCluster:");
	cluster();
	label();
	printf("\n\nLabels are:\n%d\n%d\n%d\n",cluster_labels[0],cluster_labels[1],cluster_labels[2]);
}


void train()
{
	printf("Enter the location of file to read:");	
	readData();
	initialize_mean();
	distance(initial_data,total_rows);
	calculate_new_mean();	
	cluster_mean();

	for(int i=0;i<3;i++)
	{
	printf("\n\n%d %d %d %d %d",mean[i].sport,mean[i].dport,mean[i].sbytes,mean[i].dbytes,mean[i].protocol);
	}

}

struct data test_value = {0, 0,137,40000, 1, -1};

int main()
{
	train();
	test();
	flag = 1;
	distance(&test_value,0);
	printf("\n\nCluster is:%d\n\nLabel is:%d",cluster_number+1,cluster_labels[cluster_number]);
	cluster();
	return 0;
}