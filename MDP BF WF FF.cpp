#include<bits/stdc++.h>
#include<iostream>
using namespace::std;
void firstfit()
{
    int blockSize[] = {100, 500, 200, 300, 600};
	int processSize[] = {212, 417, 112, 426};
	int m = sizeof(blockSize) / sizeof(blockSize[0]);
	int n = sizeof(processSize) / sizeof(processSize[0]);
	int allocation[n];
	memset(allocation, -1, sizeof(allocation));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				allocation[i] = j;
				blockSize[j] -= processSize[i];
				break;
			}
		}
	}
	cout << "\nProcess No.\tProcess Size\tBlock no.\n";
	for (int i = 0; i < n; i++)
	{
		cout << " " << i+1 << "\t\t"
			<< processSize[i] << "\t\t";
		if (allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << endl;
	}
}


int bestfit()
{
	int fragment[20],b[20],p[20],i,j,nb,np,temp,lowest=9999;
	static int barray[20],parray[20];
	cout<<"\nEnter the number of blocks:";
	cin>>nb;
	cout<<"Enter the number of processes:";
	cin>>np;
	cout<<"\nEnter the size of the blocks:-\n";
	for(i=1;i<=nb;i++)
    {
        cout<<"Block no."<<i<<":";
        cin>>b[i];
    }
	cout<<"\nEnter the size of the processes :-\n";
	for(i=1;i<=np;i++)
    {
        cout<<"Process no. "<<i<<":";
        cin>>p[i];
    }
	for(i=1;i<=np;i++)
	{
		for(j=1;j<=nb;j++)
		{
			if(barray[j]!=1)
			{
				temp=b[j]-p[i];
				if(temp>=0)
					if(lowest>temp)
					{
						parray[i]=j;
						lowest=temp;
					}
			}
		}
		fragment[i]=lowest;
		barray[parray[i]]=1;
		lowest=10000;
	}
	cout<<"\nProcess_no\tProcess_size\tBlock_no\tBlock_size\tFragment";
	for(i=1;i<=np && parray[i]!=0;i++)
		cout<<"\n"<<i<<"\t\t"<<p[i]<<"\t\t"<<parray[i]<<"\t\t"<<b[parray[i]]<<"\t\t"<<fragment[i];
	return 0;
}



void worstfit()
{
	int blockSize[] = {100, 500, 200, 300, 600};
	int processSize[] = {212, 417, 112, 426};
	int m = sizeof(blockSize)/sizeof(blockSize[0]);
	int n = sizeof(processSize)/sizeof(processSize[0]);
	int allocation[n];
	memset(allocation, -1, sizeof(allocation));
	for (int i=0; i<n; i++)
	{
		int wstIdx = -1;
		for (int j=0; j<m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				if (wstIdx == -1)
					wstIdx = j;
				else if (blockSize[wstIdx] < blockSize[j])
					wstIdx = j;
			}
		}
		if (wstIdx != -1)
		{
			allocation[i] = wstIdx;
			blockSize[wstIdx] -= processSize[i];
		}
	}
	cout << "\nProcess No.\tProcess Size\tBlock no.\n";
	for (int i = 0; i < n; i++)
	{
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t";
		if (allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << endl;
	}
}
int main()
{
    float result;
    int choice, num;
    printf("Press 1 for FIRSTFIT\n");
    printf("Press 2 for BESTFI\n");
    printf("Press 3 for WORSTFIT\n");
    printf("Enter your choice:\n");
    cin >> choice;
    switch (choice) {
    case 1: {
        firstfit();
        break;
    }
    case 2: {
        bestfit();
        break;
    }
    case 3: {
        worstfit();
        break;
    default:
        printf("wrong Input\n");
    }
    return 0;
    }
}
