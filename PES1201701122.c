#include "intal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1005

static int min(int a, int b)
{
    return (a<b)?a:b;
}

static void reverse(char* s, int n)
{
    for(int i=0; i<n/2; i++)
    {
        char temp = s[i];
        s[i] = s[n-1-i];
        s[n-1-i] = temp;
    }
}

static char* intal_create(unsigned int n)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    unsigned int i = 0;
    while(n)
    {
        res[i++] = n%10+'0';
        n /=10;
    }
    res[i] = '\0';
    return res;
}

char* intal_add(const char* intal1, const char* intal2)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    if(strcmp(intal1,"0")==0)
    {
        strcpy(res,intal2);
    }
    else if(strcmp(intal2,"0")==0)
    {
        strcpy(res,intal1);
    }
    else
    {
        char* num1 = (char*)malloc(MAX*sizeof(char));
        char* num2 = (char*)malloc(MAX*sizeof(char));
        strcpy(num1,intal1);
        strcpy(num2,intal2);
        int n = strlen(num1), m = strlen(num2);
        reverse(num1,n);
        reverse(num2,m);
        int c = 0, i = 0, j = 0, k = 0;
        while(i<n && j<m)
        {
            int total = (num1[i++]-'0')+(num2[j++]-'0')+c;
            res[k++] = total%10+'0';
            c = total/10;
        }
        while(i<n)
        {
            int total = (num1[i++]-'0')+c;
            res[k++] = total%10+'0';
            c = total/10;
        }
        while(j<m)
        {
            int total = (num2[j++]-'0')+c;
            res[k++] = total%10+'0';
            c = total/10;
        }
        if(c!=0)
            res[k++] = c+'0';
        res[k] = '\0';
        free(num1);
        free(num2);
        reverse(res,k);
    }
    return res; 
}

int intal_compare(const char* intal1, const char* intal2)
{
    int n = strlen(intal1), m = strlen(intal2);
    if(n>m)
        return 1;
    else if(n<m)
        return -1;
    else
    {
        for(int i=0; i<n; i++)
        {
            if(intal1[i]>intal2[i])
                return 1;
            else if(intal1[i]<intal2[i])
                return -1;
        }
        return 0;
    }

}

char* intal_diff(const char* intal1, const char* intal2)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    if(strcmp(intal1,"0")==0)
    {
        strcpy(res,intal2);
    }
    else if(strcmp(intal2,"0")==0)
    {
        strcpy(res,intal1);
    }
    else
    {
        int ans = intal_compare(intal1,intal2);
        if(ans==0)
        {
            strcpy(res,"0");
        }
        else
        {
            char* num1 = (char*)malloc(MAX*sizeof(char));
            char* num2 = (char*)malloc(MAX*sizeof(char));
            if(ans==-1)
            {
                strcpy(num1,intal2);
                strcpy(num2,intal1);
            }
            else
            {
                strcpy(num1,intal1);
                strcpy(num2,intal2);
            }
            int n = strlen(num1), m = strlen(num2), i = 0, j = 0, k = 0;
            reverse(num1,n);
            reverse(num2,m);
            while(i<n && j<m)
            {
                if(num1[i]=='-' || num1[i]<num2[j])
                {
                    int num = (num1[i]=='-'?-1:num1[i]-'0');
                    num1[i+1] = (num1[i+1]=='0'?'-':((num1[i+1]-'0')-1)+'0');
                    res[k++] = ((10+num)-(num2[j++]-'0'))+'0';
                    i++;
                }   
                else
                {
                    res[k++] = ((num1[i++]-'0')-(num2[j++]-'0'))+'0';
                } 
            }
            while(i<n)
            {
                res[k++] = num1[i++];
            }
            while(k-1>=0 && res[k-1]=='0')
                k--;
            res[k] = '\0';
            reverse(res,k);
            free(num1);
            free(num2);
        }
    }
    return res;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
    int n = strlen(intal1), m = strlen(intal2);
    char* res = (char*)malloc(sizeof(char)*MAX);
    if(strcmp(intal1,"0")==0 || strcmp(intal2,"0")==0)
    {
        strcpy(res,"0");
    }
    else
    {
        memset(res,'0',MAX*sizeof(char));
        int i_n1 = 0, i_n2 = 0;
        for(int i=n-1; i>=0; i--)
        {
            int carry = 0;
            int n1 = intal1[i]-'0';
            i_n2 = 0;
            for(int j = m-1; j>=0; j--)
            {
                int n2 = intal2[j]-'0';
                int sum = n1*n2 + res[i_n1+i_n2]-'0' + carry;
                carry = sum/10;
                res[i_n1+i_n2] = sum%10+'0';
                i_n2++;
            }
            if(carry>0)
                res[i_n1+i_n2] = carry+'0';
            i_n1++;
        }
        int i=n+m-1;
        while(i>=0 && res[i]=='0')
            i--;
        res[i+1] = '\0';
        reverse(res,i+1);    
    }
    return res;

}

static char* division(char* number, int divisor)
{
    char* ans = (char*)malloc(MAX*sizeof(char)); 
    
    int idx = 0, i = 0, n = strlen(number); 
    int temp = number[idx] - '0'; 
    while (temp < divisor) 
       temp = temp * 10 + (number[++idx] - '0'); 
      
    while (n > idx) 
    {  
        ans[i++] = (temp / divisor) + '0'; 
          
        temp = (temp % divisor) * 10 + number[++idx] - '0'; 
    } 
    
    ans[i] = '\0';
     
    if (i == 0) 
        return "0"; 
      
    return ans;
}

char* intal_mod(const char* intal1, const char* intal2)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    if(intal_compare(intal1,intal2)==-1)
    {
        strcpy(res,intal1);
    }
    else if(intal_compare(intal1,intal2)==0)
    {
        strcpy(res,"0");
    }
    else
    {
        char* left = (char*)malloc(MAX*sizeof(char)),*right = (char*)malloc(MAX*sizeof(char));
        strcpy(left,"0");
        strcpy(right,intal1);
        while(intal_compare(left,right)==-1)
        {
            char* temp = intal_add(left,right);
            char* m = division(temp,2);
            free(temp);
            temp = intal_multiply(m,intal2);
            int ans;
            if(intal_compare(intal1,temp)==-1)
            {
                ans = -1;
            }
            else
            {
                char* temp1 = intal_diff(intal1,temp);
                ans = intal_compare(temp1,intal2);
                free(temp1);
            }
            free(temp);
            if(ans!=-1)
            {
                temp = intal_add(m,"1");
                strcpy(left,temp);
                free(temp);
            }    
            else
            {
                strcpy(right,m);
            }
        }
        char* temp = intal_multiply(left,intal2);
        char* temp1 = intal_diff(intal1,temp);
        strcpy(res,temp1);
        free(temp);
        free(temp1);
    }
    return res;
}

char* intal_pow(const char* intal1, unsigned int n)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    if(intal_compare(intal1,"0")==0)
    {
        strcpy(res,"0");
    }
    else if(n==0)
    {
        strcpy(res,"1");
    }
    else
    {
        char* temp = intal_pow(intal1,n/2);
        if(n%2==0)
        {
            char* temp1 = intal_multiply(temp,temp);
            strcpy(res,temp1);
            free(temp1);
        }
        else
        {
            char* temp1 = intal_multiply(temp,temp);
            char* temp2 = intal_multiply(intal1,temp1);
            strcpy(res,temp2);
            free(temp1);
            free(temp2);
        }
        free(temp);
    }
    return res;
}

char* intal_gcd(const char* intal1, const char* intal2)
{
    if(strcmp(intal2,"0")==0)
    {
        char* res = (char*)malloc(MAX*sizeof(char));
        strcpy(res,intal1);
        return res;
    }
    char* temp = intal_mod(intal1,intal2);
    char* res = intal_gcd(intal2,temp);
    free(temp);
    return res;
}

char* intal_fibonacci(unsigned int n)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    if(n==0)
    {
        strcpy(res,"0");
    }
    else if(n==1)
    {
        strcpy(res,"1");
    }
    else
    {
        char* a = (char*)malloc(MAX*sizeof(char)), *b = (char*)malloc(MAX*sizeof(char));
        strcpy(a,"0");
        strcpy(b,"1");
        for(int i=2; i<=n; i++)
        {
            char* temp = intal_add(a,b);
            strcpy(a,b);
            strcpy(b,temp);
        }
        strcpy(res,b);
        free(a);
        free(b);
    }
    return res;
}

char* intal_factorial(unsigned int n)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    strcpy(res,"1");
    char* it = intal_create(2);
    for(int i=2; i<=n; i++)
    {
        char* temp = intal_multiply(it,res);
        strcpy(res,temp);
        free(temp);
        char* nw = intal_add(it,"1");
        strcpy(it,nw);
        free(nw);
    }
    free(it);
    return res;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    if(n==k || k==0)
    {
        strcpy(res,"1");
    }
    else
    {
        char* arr[k+1];
        for(int i=0; i<=k; i++)
        {
            arr[i] = (char*)malloc(MAX*sizeof(char));
            strcpy(arr[i],"0");
        }
        strcpy(arr[0],"1");
        for(int i=1; i<=n; i++)
        {
            for(int j=min(i,k); j>0; j--)
            {
                char* temp = intal_add(arr[j],arr[j-1]);
                strcpy(arr[j],temp);
                free(temp); 
            }
        }
        strcpy(res,arr[k]);
    }
    return res;
}

int intal_max(char **arr, int n)
{
    char* temp = (char*)malloc(MAX*sizeof(char));
    strcpy(temp,arr[0]);
    int maxIndex = 0;
    for(int i=1; i<n; i++)
    {
        if(intal_compare(temp,arr[i])==-1)
        {
            strcpy(temp,arr[i]);
            maxIndex = i;
        }
    }
    free(temp);
    return maxIndex;
}

int intal_min(char **arr, int n)
{
    char* temp = (char*)malloc(MAX*sizeof(char));
    strcpy(temp,arr[0]);
    int minIndex = 0;
    for(int i=1; i<n; i++)
    {
        if(intal_compare(temp,arr[i])==1)
        {
            strcpy(temp,arr[i]);
            minIndex = i;
        }
    }
    free(temp);
    return minIndex;
}

int intal_search(char **arr, int n, const char* key)
{
    for(int i=0; i<n; i++)
    {
        if(intal_compare(arr[i],key)==0)
            return i;
    }
    return -1;
}

int intal_binsearch(char **arr, int n, const char* key)
{
    int l = 0, r = n-1;
    while(l<r)
    {
        int mid = l+(r-l)/2;
        if(intal_compare(arr[mid],key)>-1)
            r = mid;
        else
            l = mid+1;
    }
    return intal_compare(arr[l],key)==0?l:-1;
}

static void swap(char** a, char** b)
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}

static int partition(char** arr, int low, int high)
{
    char* pivot = arr[high];
    int pivotIndex = low;
    for(int i=low; i<high; i++)
    {
        if(intal_compare(arr[i],pivot)!=1)
        {
            swap(&arr[i],&arr[pivotIndex]);
            pivotIndex++;
        }
    } 
    swap(&arr[high],&arr[pivotIndex]);
    return pivotIndex;
}

static void sort(char** arr, int low, int high)
{
    if(low<high)
    {
        int pivot = partition(arr,low,high);
        sort(arr,low,pivot-1);
        sort(arr,pivot+1,high);
    }
}

void intal_sort(char **arr, int n)
{
    if(n<=1)
        return;
    sort(arr,0,n-1);
}

char* coin_row_problem(char **arr, int n)
{
    char* res = (char*)malloc(MAX*sizeof(char));
    if(n==1)
    {
        strcpy(res,arr[0]);
    }
    else if(n==2)
    {
        if(intal_compare(arr[0],arr[1])==1)
            strcpy(res,arr[0]);
        else
            strcpy(res,arr[1]);
    }
    else
    {
        char* a = (char*)malloc(MAX*sizeof(char)), *b = (char*)malloc(MAX*sizeof(char));
        strcpy(a,arr[0]);
        if(intal_compare(arr[0],arr[1])==1)
            strcpy(b,arr[0]);
        else
            strcpy(b,arr[1]);
        for(int i=2; i<n; i++)
        {
            char* temp = intal_add(arr[i],a);
            strcpy(a,b);
            if(intal_compare(temp,b)==1)
            {
                strcpy(b,temp);
            }
            free(temp);
        }
        strcpy(res,b);
    }
    return res;
}