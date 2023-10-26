#include "BigInteger.h"
node* createnode(int val) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    return temp;
}

node* createlist(char* s) {
    node* ptr = NULL;
    node* itr;
    int i = 0;
    while (*(s + i) != '\0') {
        itr = createnode((*(s + i) - '0'));
        itr->next = ptr;
        ptr = itr;
        i++;
    }
    return ptr;
}

BigInteger createBigInteger() {
    BigInteger temp;
    temp.list = NULL;
    temp.length = 0;
    temp.sign = '+';
    return temp;
}

BigInteger initialize(char* s) {
    BigInteger temp;
    temp.list = createlist(s);
    temp.length = strlen(s);
    temp.sign = '+';
    return temp;
}

node* reverse(node* head) {
    node* prev = NULL;
    node* next = NULL;
    node* itr = head;
    while (itr) {
        next = itr->next;
        itr->next = prev;
        prev = itr;
        itr = next;
    }
    return prev;
}

int length(node* ptr) {
    int len = 0;
    while (ptr) {
        ptr = ptr->next;
        len++;
    }
    return len;
}

BigInteger add(BigInteger a, BigInteger b) {
    node* n1 = a.list;
    node* n2 = b.list;
    node* prev = NULL;
    int len = 0;
    int carry = 0;
    while (n1 != NULL || n2 != NULL || carry != 0) {
        int x = n1 ? n1->data : 0;
        int y = n2 ? n2->data : 0;

        int sum = x + y + carry;
        carry = sum / 10;
        sum = sum % 10;

        node* res = createnode(sum);
        res->next = prev;
        prev = res;

        if (n1) n1 = n1->next;
        if (n2) n2 = n2->next;
        len++;
    }
    BigInteger result;
    result.list = prev;
    result.length = len;
    return result;
}

BigInteger sub(BigInteger a, BigInteger b) {
    node* n1 = a.list;
    node* n2 = b.list;
    node* prev = NULL;
    int borrow = 0;
    int l = 0;

    BigInteger result = createBigInteger();

    if (a.length < b.length) {
        node* temp = n2;
        n2 = n1;
        n1 = temp;
        result.sign = '-';
    } else if (a.length == b.length && n1->data < n2->data) {
        node* temp = n2;
        n2 = n1;
        n1 = temp;
        result.sign = '-';
    }

    while (n1 != NULL || n2 != NULL) {
        int x = (n1 != NULL) ? n1->data : 0;
        int y = (n2 != NULL) ? n2->data : 0;
        int diff = x - y - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        node* res = createnode(diff);
        res->next = prev;
        prev = res;

        if (n1 != NULL) n1 = n1->next;
        if (n2 != NULL) n2 = n2->next;
    }

    while (prev->next != NULL && prev->data == 0) {
        node* temp = prev;
        prev = prev->next;
        free(temp);
    }

    result.list = prev;
    result.length = length(prev);
    return result;
}

BigInteger multiply(BigInteger a, BigInteger b) {
    node* n1 = a.list;
    node* n2 = b.list;
    BigInteger result = createBigInteger();
    BigInteger lis = createBigInteger();
    node* tempPrev = NULL;
    int i = 0;

    while (n2) {
        int carry = 0;
        node* prev = NULL;
        while (n1) {
            int val = n1->data * n2->data + carry;
            carry = val / 10;
            val = val % 10;

            node* res = createnode(val);
            res->next = prev;
            prev = res;
            n1 = n1->next;
        }
        while (carry) {
            int val = carry % 10;
            carry = carry / 10;

            node* res = createnode(val);
            res->next = prev;
            prev = res;
        }

        prev = reverse(prev);
        for (int j = 0; j < i; ++j) {
            node* temp = createnode(0);
            temp->next = prev;
            prev = temp;
        }

        n2 = n2->next;
        n1 = a.list;
        lis.list = prev;
        result = add(result, lis);
        result.list = reverse(result.list);
        i++;
    }
    result.list = reverse(result.list);
    result.length = length(result.list);
    return result;
}

int cmplist(node* a,node* b){
    // 1 for a > b
    // 0 for a = b
    // -1 for a < b
    if(length(a)>length(b))
        return 1;
    if(length(a)<length(b))
        return -1;
    if(length(a) == length(b)){
        while (a != NULL && b != NULL) {
            if (a->data < b->data) {
                return -1;
            } else if (a->data > b->data) {
                return 1;
            }
            a = a->next;
            b = b->next;
        }
    }
    return 0;
}
void dump(struct BigInteger c)
{
    struct node *temp;
    while(c.list)
    {
        temp=c.list;
        c.list=c.list->next;

        free(temp);
    }
    c.list=0;
}



struct BigInteger div1(struct BigInteger a , struct BigInteger b )
{
    struct BigInteger tmp ={0 , 0 , 0};
    if(!b.list || !a.list)
    {
        printf("Invalid input\n");
        return tmp;
    }
    if(compare(a,b) == -1)
    {
        return tmp;
    }
    else
    {
        if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
        {
            
            return division(a,b,1,1);
            
        }
        else
        {
            return division(a,b,-1,1);
        }
    }
}

struct node *duplicate(struct node *head)
{
    struct node *h1=0,*iter, *temp;
    while(head)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return h1;
        }
        temp->data=head->data;
        temp->next=0;
        if(!h1)
        {
            h1=temp;
            iter=temp;
        }
        else
        {
            iter->next=temp;
            iter=temp;
        }
        head=head->next;
    }
    return h1;
}

void tnct(struct BigInteger tmp)
{
    struct node *tfront=0,*iter=tmp.list;
    if(!tmp.list)
        return;
    while(iter->next)
    {
        if(iter->next->data==0 && tfront==0)
        {
            tfront=iter;
            iter=iter->next;
            continue;
        }
        if(iter->data!=0 && tfront)
        {
            tfront=0;
        }  
        iter=iter->next;
    }
    if(iter->data!=0)
    {
        tfront=0;
    }

    if(tfront)
    {
        iter=tfront;
        tfront=tfront->next;
        iter->next=0;
        while(tfront)
        {
            iter=tfront;
            tfront=tfront->next;
            free(iter);
            tmp.length -=1;
        }
    }
    
}

struct BigInteger division(struct BigInteger a , struct BigInteger b , int sign , int choice)
{
    struct BigInteger tmp;
    tmp.list=0;
    tmp.length=0;
    tmp.sign=sign;
    int comp,length=b.length;
    struct node *head=0,*iter,*temp ,*p2=b.list, *h_quot=(struct node *) malloc(sizeof(struct node));
    if(!h_quot)
    {
        printf("memory aloocation failed\n");
        return tmp;
    }
    
    if((comp=compare(a,b))<1)
    {
        if(comp==0)
        {
            if(choice==0)
            {
                tmp.list=duplicate(a.list);
                return tmp;
            }
            h_quot->data=1;
            h_quot->next=0;
            tmp.list=h_quot;
            tmp.length=1;
            return tmp;
        }
        if(choice ==0)
        {
            tmp.list=duplicate(a.list);
            return tmp;
        }
        return tmp;
    }
 
    head=duplicate(p2);

    h_quot->data=1;
    h_quot->next=0;
    tmp.length=1;
    while(a.length>=length+1)
    {
        iter=(struct node *) malloc(sizeof(struct node));
        temp=(struct node *) malloc(sizeof(struct node));
        if(!temp && !iter)
        {
            printf("Memory allocation failed\n");
            return tmp;
        }
        temp->data=iter->data=0;
        temp->next=head;
        head=temp;
        iter->next=h_quot;
        h_quot=iter;
        length+=1;
    }

    tmp.list=head;
    tmp.length=length;
    if((comp=compare(a,tmp))==-1)
    {
        temp=head;
        head=head->next;
        free(temp);
        temp=h_quot;
        h_quot=h_quot->next;
        free(temp);
        length-=1;
    }
    while(a.length>length)
        div_add(head,b.list,h_quot,&length);

    tmp.list=head;
    tmp.length=length;
    while((comp=compare(a,tmp))!=-1 && comp != 0)
    {
        div_add(head,b.list,h_quot,&tmp.length);
    }

    if(comp==0)
    {
        if(choice==0)
        {
            tmp.list=h_quot;
            dump(tmp);
            tmp.list=head;
            tmp.length=a.length;
            return tmp;
        }
        tmp.list=head;
        dump(tmp);
        tmp.list=h_quot;
        tmp.length=length;
        return tmp;
    }
    if(compare(a,tmp)==-1)
    {
        div_sub(head,b.list,h_quot);
        
        tnct(tmp);
    }
    if(choice == 0)
    {
        tmp.list=h_quot;
        dump(tmp);
        tmp.list=head;
        tmp.length=a.length;
        tnct(tmp);
        return tmp;
    }
    tmp.list=head;
    dump(tmp);
    tmp.list=h_quot;
    tnct(tmp);
    return tmp;
}

int compare(struct BigInteger h1 , struct BigInteger h2)
{
    if(h1.length < h2.length)
        return -1;
    else if(h1.length > h2.length)
        return 1;
    else
    return compare_sub(h1.list,h2.list);
}


int compare_sub(struct node *h1 , struct node *h2)
{
    static int x;
    x=0;

    
    if(!h1 && !h2)
    {
        return x;
    }
    compare_sub(h1->next,h2->next);
    
    if(x==-1)
        return x;
    else if(h1->data>h2->data)
    {
        x=1;
    }
    else if(h1->data<h2->data && x==0)
    {
        x=-1;
    }
    
    return x;

}


void div_add(struct node *p1 ,struct node *p2 ,struct node *p3 , int *l)
{
    struct node *temp=0 ,*ptr;
    int num,carry=0;
    while(p2)
    {

        p1->data=p1->data+p2->data+carry;
        carry=(p1->data)/10;
        p1->data=(p1->data)%10;

        if(p1->next==0)
        {
            ptr=p1;
        }
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        if(p1->next==0)
        {
            ptr=p1;
        }
        p1->data=p1->data+carry;
        carry=(p1->data)/10;
        p1->data=(p1->data)%10;
       
        if(carry==0)
        {
            break;
        }
        p1=p1->next; 
    }
    if(carry!=0)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return;
        }
        ptr->next=temp;
        temp->data=carry;
        temp->next=0;
        *l+=1;
    }
    carry=1;
    while(p3)
    {
        p3->data=p3->data+carry;
        carry=(p3->data)/10;
        p3->data=(p3->data)%10;
        p3=p3->next;
        if(carry==0)
        {
            return;
        }
        if(p3->next==0)
        {
            ptr=p3;
        }
    }
    if(carry!=0)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return;
        }
        ptr->next=temp;
        temp->data=carry;
        temp->next=0;
        *l+=1;
    }
    
}

void revsign(struct node *head)
{
    if(head==0)return;
    head->data *= -1;
    revsign(head->next);
}


void div_sub(struct node *p1 ,struct node *p2 ,struct node *p3 )
{
    struct node *ptr=p2;
    int num,carry=0;
    revsign(p2);
    
    while(p2)
    {
        p1->data=p1->data+p2->data+carry;
        
        if(p1->data<0)
        {
            p1->data=p1->data+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        p1->data=p1->data+carry;
        if(p1->data<0)
        {
            p1->data=p1->data+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        if(carry==0)
        {
            break;
        }
        p1=p1->next;
         
    }
    revsign(ptr);

    carry=-1;
    while(p3)
    {
        p3->data=p3->data+carry;
        if(p3->data<0)
        {
            p3->data+=10;
            carry=-1;
        }
        else 
        {
            carry=0;
        }
        if(carry==0)
        {
            return;
        }
        p3=p3->next;
    }
}

/*BigInteger div1(BigInteger a, BigInteger b) {
    node* n1 = a.list;
    node* n2 = b.list;
    while(cmplist(n1,n2) == 1){
        int count = 1;
        
    }

    
    BigInteger result = createBigInteger();
    return result;
}*/

void display(BigInteger n1) {
    node* itr = n1.list;
    if (!itr) {
        printf("List is empty \n");
        return;
    }
    printf("\n");
    while (itr != NULL) {
        printf("%d  ", itr->data);
        itr = itr->next;
    }
}

struct BigInteger mod(struct BigInteger a , struct BigInteger b)
{
    struct BigInteger tmp ={0 , 0 , 0};
    if(!b.list || !a.list)
    {
        printf("Invalid input\n");
        return tmp;
    }
    if(compare(a,b)== -1)
    {
        tmp.list=duplicate(a.list);
        tmp.length=a.length;
        return tmp;
    }
    else
    {
        if(a.sign == 1 && b.sign == 1 || a.sign == -1 && b.sign == -1)
        {
            
            tmp = division(a,b,1,0);
            
        }
        else
        {
            tmp = division(a,b,-1,0);
        }
    }
    if(compare(a,tmp)==0)
    
    {
        tmp.list=duplicate(a.list);
        tmp.length=a.length;
        return tmp;
    }
    return addminus(a,tmp,1);
}

struct BigInteger addminus(struct BigInteger a, struct BigInteger b,int sign)
{
    struct BigInteger tmp;
    tmp.sign=sign;
    tmp.list=0;
    tmp.length=a.length;
    struct node *head=0 , *p1=a.list , *p2=b.list ,*temp , *iter;
    int num,carry=0;
    revsign(p2);
   
    while(p2)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return tmp;
        }

        num=p1->data+p2->data+carry;
        
        if(num<0)
        {
            temp->data=num+10;
            carry=-1;
        }
        else
        {
            temp->data=num;
            carry=0;
        }
        
        temp->next=0;
        if(!head)
        {
            head=temp;
            iter=head;
        }
        else
        {
            iter->next=temp;
            iter=temp;
        }
        p1=p1->next;
        p2=p2->next;
    }
    while(p1)
    {
        temp=(struct node *)malloc (sizeof(struct node));
        if(!temp)
        {
            printf("Memory alloction failed. Unable to add\n");
            return tmp;
        }
        temp->data=p1->data+carry;
        if(temp->data<0)
        {
            temp->data=temp->data+10;
            carry=-1;
        }
        else
        {
            carry=0;
        }
        
        temp->next=0;
        if(!head)
        {
            iter=head=temp;
        }
  
        iter->next=temp;
        iter=temp;
        p1=p1->next; 
    }
    tmp.list=head;
    revsign(b.list);
    tnct(tmp);
    return tmp;
}


int main() {
    char a[200];
    char b[200];
    printf("Enter first number : ");
    scanf("%s", a);
    printf("Enter second number : ");
    scanf("%s", b);
    struct BigInteger no1 = initialize(a);
    struct BigInteger no2 = initialize(b);
    // struct BigInteger resadd = add(no1, no2);
    // struct BigInteger ressub = sub(no1, no2);
    // struct BigInteger respro = multiply(no1, no2);
    struct BigInteger resdiv = div1(no1,no2);
    // display(no1);
    // display(no2);
    // display(resadd);
    // display(ressub);
    // display(resdiv.quotient);
    // display(resdiv.remainder);
    // printf("%c", resadd.sign);
    // printf("%c", ressub.sign);
    // printf("%c", respro.sign);

    printf("\n");
    // printf("%d", resadd.length);
    // printf("%d", ressub.length);
    // printf("%d", respro.length);

    return 0;
}