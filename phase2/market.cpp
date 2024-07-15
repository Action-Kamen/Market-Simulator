#include "market.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#define MAX 1000000
using namespace std;
struct data {
    string brokername;
    int price;
    int quantity;
    int exptime;
    data(string brokername,int price,int quantity,int exptime) : brokername(brokername),price(price),quantity(quantity),exptime(exptime) {}
};
struct node  
{  
    struct data data;    // Lower values indicate  
    // higher priority  
    int priority;  
  
    struct node* next;  
    node() : data("", 0, 0, 0), priority(0), next(nullptr) {}

    node(struct data pd, int p) : data(pd), priority(p), next(nullptr) {}
};  
  
// Function to create a new node  
node* newNode(struct data d, int p)  
{  
    //cout<<"ma choda bhsdk"<<endl;
    node* temp = new node;  
    // cout<<"ma choda bhsdk*"<<endl;
    temp->data = d; 
    // cout<<"ma choda bhsdk 1"<<endl; 
    temp->priority = p; 
     //cout<<"ma choda bhsdk 2"<<endl; 
    temp->next = NULL;  
  // cout<<"ma choda bhsdk"<<endl;
    return temp;  
}  
// Return the value at head  
struct data peek(node** head)  
{  
    return (*head)->data;  
}  
// Removes the element with the  
// highest priority  from the list  
void pop(node** head)  
{  
    node* temp = *head;  
    (*head) = (*head)->next;  
    free(temp);  
}  

// Function to push according to priority  
void push(node** head, struct data d, int p)  
{  
    node* start = (*head);  
    node* temp = newNode(d, p);  
    if ((*head)->priority > p)  
    {  
        temp->next = *head;  
        (*head) = temp;  
    }  
    else
    {
        while (start->next != NULL &&  
            start->next->priority < p)  
        {  
            start = start->next;  
        }  
        temp->next = start->next;  
        start->next = temp;  
    }  
}  
// Function to check is list is empty  
int isEmpty(node** head)  
{  
    return (*head) == NULL;  
} 
class Map {
private:
    Map* iterator(const string& first) {
        Map* temp = root;
        while (temp != nullptr && temp->first != first) {
            if (first < temp->first) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        return temp;
    }

    const Map* iterator(const string& first) const {
        Map* temp = root;
        while (temp != nullptr && temp->first != first) {
            if (first < temp->first) {
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }
        return temp;
    }

    const struct node* search(const string& first) const {
        const Map* temp = iterator(first);
        if (temp != nullptr) {
            return temp->second;
        }
        return (nullptr);
    }

    Map* create(const string& first) {
        Map* newnode = new Map;
        newnode->first = first;
        newnode->second = 0;
        newnode->left = nullptr;
        newnode->right = nullptr;
        newnode->par = nullptr;
        newnode->depth = 1;
        return newnode;
    }

    void right_rotation(Map* x) {
        Map* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->par = x;
        }
        if (x->par != nullptr && x->par->right == x) {
            x->par->right = y;
        }
        else if (x->par != nullptr && x->par->left == x) {
            x->par->left = y;
        }
        y->par = x->par;
        y->right = x;
        x->par = y;
    }

    void left_rotation(Map* x) {
        Map* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->par = x;
        }
        if (x->par != nullptr && x->par->left == x) {
            x->par->left = y;
        }
        else if (x->par != nullptr && x->par->right == x) {
            x->par->right = y;
        }
        y->par = x->par;
        y->left = x;
        x->par = y;
    }

    void helper(Map* node) {
        if (depthf(node->left) - depthf(node->right) > 1) {
            if (depthf(node->left->left) > depthf(node->left->right)) {
                node->depth = max(depthf(node->right) + 1, depthf(node->left->right) + 1);
                node->left->depth = max(depthf(node->left->left) + 1, depthf(node) + 1);
                right_rotation(node);
            }
            else {
                node->left->depth = max(depthf(node->left->left) + 1, depthf(node->left->right->left) + 1);
                node->depth = max(depthf(node->right) + 1, depthf(node->left->right->right) + 1);
                node->left->right->depth = max(depthf(node) + 1, depthf(node->left) + 1);
                left_rotation(node->left);
                right_rotation(node);
            }
        }
        else if (depthf(node->left) - depthf(node->right) < -1) {
            if (depthf(node->right->right) > depthf(node->right->left)) {
                node->depth = max(depthf(node->left) + 1, depthf(node->right->left) + 1);
                node->right->depth = max(depthf(node->right->right) + 1, depthf(node) + 1);
                left_rotation(node);
            }
            else {
                node->right->depth = max(depthf(node->right->right) + 1, depthf(node->right->left->right) + 1);
                node->depth = max(depthf(node->left) + 1, depthf(node->right->left->left) + 1);
                node->right->left->depth = max(depthf(node) + 1, depthf(node->right) + 1);
                right_rotation(node->right);
                left_rotation(node);
            }
        }
    }

    void balance(Map* node) {
        while (node != root) {
            int d = node->depth;
            node = node->par;
            if (node->depth < d + 1) {
                node->depth = d + 1;
            }
            if (node == root && depthf(node->left) - depthf(node->right) > 1) {
                if (depthf(node->left->left) > depthf(node->left->right)) {
                    root = node->left;
                }
                else {
                    root = node->left->right;
                }
                helper(node);
                break;
            }
            else if (node == root && depthf(node->left) - depthf(node->right) < -1) {
                if (depthf(node->right->right) > depthf(node->right->left)) {
                    root = node->right;
                }
                else {
                    root = node->right->left;
                }
                helper(node);
                break;
            }
            helper(node);
        }
    }

    int depthf(Map* node) {
        if (node == nullptr)
            return 0;
        return node->depth;
    }

    Map* insert(const string& first) {
        cnt++;
        Map* newnode = create(first);
        if (root == nullptr) {
            root = newnode;
            return root;
        }
        Map* temp = root, *prev = nullptr;
        while (temp != nullptr) {
            prev = temp;
            if (first < temp->first) {
                temp = temp->left;
            }
            else if (first > temp->first) {
                temp = temp->right;
            }
            else {
                delete newnode;
                cnt--;
                return temp;
            }
        }
        if (first < prev->first) {
            prev->left = newnode;
        }
        else {
            prev->right = newnode;
        }
        newnode->par = prev;
        balance(newnode);
        return newnode;
    }

    Map* inorderPredecessor(Map* head) {
        if (head == nullptr)
            return head;
        while (head->right != nullptr) {
            head = head->right;
        }
        return head;
    }

    Map* inorderSuccessor(Map* head) {
        if (head == nullptr)
            return head;
        while (head->left != nullptr) {
            head = head->left;
        }
        return head;
    }

public:
    class Map* root;
    int cnt;

    Map* left, *right, *par;
    string first;
    struct node* second;int depth;
    Map(){
        root = NULL;
        cnt = 0;
    }

    struct node*& operator[](const string& key) {
        return insert(key)->second;
    }

    const struct node* operator[](const string& key) const {
        return search(key);
    }

    int count(const string& key) {
        Map* temp = iterator(key);
        if (temp != nullptr) {
            return 1;
        }
        return 0;
    }

    int size(void) {
        return cnt;
    }

    void erase(const string& key) {
        Map* prev = nullptr;
        Map* temp = root;
        cnt--;
        while (temp != nullptr && temp->first != key) {
            prev = temp;
            if (key < temp->first) {
                temp = temp->left;
            }
            else if (key > temp->first) {
                temp = temp->right;
            }
        }
        if (temp == nullptr) {
            cnt++;
            return;
        }
        if (cnt == 0 && temp == root) {
            delete temp;
            root = nullptr;
            return;
        }
        Map* l = inorderPredecessor(temp->left);
        Map* r = inorderSuccessor(temp->right);
        if (l == nullptr && r == nullptr) {
            if (prev == nullptr) {
                root = nullptr;
            }
            else {
                if (prev->left == temp) {
                    prev->left = nullptr;
                }
                else {
                    prev->right = nullptr;
                }
                delete temp;
                balance(prev);
            }
            return;
        }
        Map* start;
        if (l != nullptr) {
            if (l == temp->left) {
                l->right = temp->right;
                if (l->right != nullptr) {
                    l->right->par = l;
                }
                start = l;
            }
            else {
                if (l->left != nullptr) {
                    l->left->par = l->par;
                }
                start = l->par;
                l->par->right = l->left;
                l->right = temp->right;
                l->par = nullptr;
                if (l->right != nullptr) {
                    l->right->par = l;
                }
                l->left = temp->left;
                temp->left->par = l;
            }
            if (prev == nullptr) {
                root = l;
            }
            else {
                if (prev->left == temp) {
                    prev->left = l;
                    l->par = prev;
                }
                else {
                    prev->right = l;
                    l->par = prev;
                }
                delete temp;
            }
            balance(start);
            return;
        }
        else {
            if (r == temp->right) {
                r->left = temp->left;
                if (r->left != nullptr) {
                    r->left->par = r;
                }
                start = r;
            }
            else {
                if (r->right != nullptr) {
                    r->right->par = r->par;
                }
                start = r->par;
                r->par->left = r->right;
                r->left = temp->left;
                r->par = nullptr;
                if (r->left != nullptr) {
                    r->left->par = r;
                }
                r->right = temp->right;
                temp->right->par = r;
            }
            if (prev == nullptr) {
                root = r;
            }
            else {
                if (prev->right == temp) {
                    prev->right = r;
                    r->par = prev;
                }
                else {
                    prev->left = r;
                    r->par = prev;
                }
                delete temp;
            }
            balance(start);
            return;
        }
    }
    Map* getIthElement(int i) {
    return getIthElementUtil(Minimum(root), i);
}

Map* getIthElementUtil(Map* node, int &i) {
    if (node == nullptr)
        return nullptr;

    int position=i;
    if(position==0)return node;
    else{
        return getIthElementUtil(Successor(node),--position);
    }
}   
    Map* Minimum(Map* node) 
    {
        if (node == nullptr)
            return nullptr;

        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Map* Successor(Map* node)
     {
            if (node == nullptr)
                return nullptr;
            if (node->right != nullptr) {
                node = node->right;
                while (node->left != nullptr) {
                    node = node->left;
                }
                return node;
            }
            Map* parent = node->par;
            while (parent != nullptr && node == parent->right) {
                node = parent;
                parent = parent->par;
            }

        return parent;
    }
    bool empty(void) {
        if (root == nullptr)
            return true;
        return false;
    }

    void update(const string& key, struct node* value) {
        Map* temp = iterator(key);
        if (temp != nullptr) {
            temp->second = value;
        }
    }

    void clear(void) {
        while (root != nullptr) {
            erase(root->first);
        }
    }
    void iterate(){
        iterate2(root);
    }
    void iterate2(Map* head) {
        if (root == nullptr)
            return;
        if (head->left != nullptr) {
            iterate2(head->left);
        }
        cout << "Key: " << head->first << ", Value: " << head->second << ' ';
        if (head->right != nullptr) {
            iterate2(head->right);
        }
    }

    Map* find(const string& key) {
        return iterator(key);
    }

    void insert(const string& key, struct node* value) {
        Map* temp = iterator(key);
        if (temp == nullptr) {
            insert(key)->second = value;
        }
        else {
            temp->second = value;
        }
    }
};
int stringToInt(string str) {
    int result = 0;
    int sign = 1;
    if (!str.empty() && str[0] == '-') {
        sign = -1;
        str = str.substr(1); 
    }

    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
        }
    }
    return result * sign;
}



std::vector<std::string> input;
market::market(int argc, char** argv)
{
	std::ifstream inputFile ("output.txt");
    std::string line;
    while (std::getline(inputFile,line)) {
        if (line.compare("TL") == 0) {
            continue;
        }
        if (line.compare("!@") == 0 || line.compare("Successfully Initiated!") == 0) {
            break;
        }
       // cout<<line<<endl;
        input.push_back(line);
    }
}

void market::start()
 {
    Map buyheap;
    Map sellheap;
    int trades=0;
    int moneyt=0;
    int sharedtra=0;
    Map buytrans;
    Map selltrans;
    Map netrans;

    for(int i=0;i<input.size();i++)
    {
        std::istringstream linestream(input[i]);
        int startt;
        std::string brokern, action, stock;
        char currency;
        int price;
        char specialChar;
        int quant, exp;
        vector<string> t;
        while(linestream){
            std::string a;
            linestream>>a;
            t.push_back(a);
        }
        startt = stoi(t[0]);
        brokern = t[1];
        action = t[2];
        Map jalu;
        for(int h=3;h<t.size()-3;h=h+2){
            node* a = new node();
            jalu[t[h]] = a;
            if(t[h+1][0]-'0'<0 || t[h+1][0]-'0'>9){
                a->priority = 1;
                h--;
            }
            else
            {
                a->priority = std::stoi(t[h+1]);
            }
        }

        int an = 1;
        std::string f;
        while(jalu.getIthElement(an)!=nullptr){
            std::string x = jalu.getIthElement(an)->first;
            int y = jalu.getIthElement(an)->second->priority;
            f.append(x);
            if(y==1){
                f.append("");
            }
            else{
                f.append(" ");
                f.append(std::to_string(y));
                f.append(" ");
            }
            an++;
        }
        stock=f;
         price  = stoi(t[t.size()-4].substr(1,t[t.size()-4].size()-1));
         quant = stoi(t[t.size()-3].substr(1,(t[t.size()-3]).size()-1));
         exp = stoi(t[t.size()-2]);
        if(action.compare("BUY")==0)
        {
            bool insinbuy=false;
            while(true)
            {
                if(sellheap.count(stock) && !isEmpty(&sellheap[stock]) && price>=peek(&sellheap[stock]).price)
                {
                    bool possible=false;
                    while(!isEmpty(&sellheap[stock]))
                    {
                        if(possible)break;
                        if(sellheap.count(stock) && !isEmpty(&sellheap[stock]) && price>=peek(&sellheap[stock]).price)
                        {
                            possible=false;
                            if(startt<=peek(&sellheap[stock]).exptime)
                            {
                            
                                if(quant<peek(&sellheap[stock]).quantity)
                                { 
                                    possible=true;
                                    int y=peek(&sellheap[stock]).quantity-quant;
                                    string broke=peek(&sellheap[stock]).brokername;
                                    int p=peek(&sellheap[stock]).price;
                                    int expiryt=peek(&sellheap[stock]).exptime;
                                    struct data stemp(broke,p,y,expiryt);
                                    trades++;
                                    sharedtra=sharedtra+quant;
                                                                if(!buytrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,quant,0);
                                                                    node* btq=newNode(transb,quant);
                                                                    buytrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&buytrans[brokern]).quantity;
                                                                    int quanti=quant+thodab;
                                                                    pop(&buytrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    buytrans[brokern]=bttq;
                                                                }   
                                                                if(!selltrans.count(peek(&sellheap[stock]).brokername))
                                                                {
                                                                    struct data transs(peek(&sellheap[stock]).brokername,0,quant,0);
                                                                    node* btq=newNode(transs,quant);
                                                                    selltrans[peek(&sellheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&selltrans[peek(&sellheap[stock]).brokername]).quantity;
                                                                    int quanti=quant+thodab;
                                                                    pop(&selltrans[peek(&sellheap[stock]).brokername]);
                                                                    struct data tras(peek(&sellheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(tras,quanti);
                                                                    selltrans[peek(&sellheap[stock]).brokername]=bttq;
                                                                }
                                                                if(!netrans.count(brokern))
                                                                {
                                                                    struct data transx(brokern,0,-1*quant*peek(&sellheap[stock]).price,0);
                                                                    node* btq=newNode(transx,-1*quant*peek(&sellheap[stock]).price);
                                                                    netrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[brokern]).quantity;
                                                                    int quanti=-1*quant*peek(&sellheap[stock]).price+thodab;
                                                                    pop(&netrans[brokern]);
                                                                    struct data trax(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trax,quanti);
                                                                    netrans[brokern]=bttq;
                                                                } 
                                                                if(!netrans.count(peek(&sellheap[stock]).brokername))
                                                                {
                                                                    struct data transx(peek(&sellheap[stock]).brokername,0,quant*peek(&sellheap[stock]).price,0);
                                                                    node* btq=newNode(transx,quant*peek(&sellheap[stock]).price);
                                                                    netrans[peek(&sellheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[peek(&sellheap[stock]).brokername]).quantity;
                                                                    int quanti=quant*peek(&sellheap[stock]).price+thodab;
                                                                    pop(&netrans[peek(&sellheap[stock]).brokername]);
                                                                    struct data trax(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trax,quanti);
                                                                    netrans[peek(&sellheap[stock]).brokername]=bttq;
                                                                } 
                                    cout<<brokern<<" purchased "<<quant<<" share of "<<stock<<" from "<<peek(&sellheap[stock]).brokername<<" for $"<<peek(&sellheap[stock]).price<<"/share"<<endl;
                                    moneyt=moneyt+quant*peek(&sellheap[stock]).price;
                                                                 
                                    pop(&sellheap[stock]);
                                    
                                    if(isEmpty(&sellheap[stock]))
                                    {
                                        node* sq=newNode(stemp,p);
                                        sellheap[stock]=sq;
                                    }
                                    else
                                    {
                                        push(&sellheap[stock],stemp,p);
                                    }
                                    possible=true;
                                    
                                    break;
                                }
                                
                                else if (quant>peek(&sellheap[stock]).quantity)
                                {
                                    trades++;
                                    sharedtra=sharedtra+peek(&sellheap[stock]).quantity;
                                                                if(!buytrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,peek(&sellheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,peek(&sellheap[stock]).quantity);
                                                                    buytrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab= peek(&buytrans[brokern]).quantity;
                                                                    int quanti=peek(&sellheap[stock]).quantity+thodab;
                                                                    pop(&buytrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    buytrans[brokern]=bttq;
                                                                }
                                                                if(!selltrans.count(peek(&sellheap[stock]).brokername) )
                                                                {
                                                                    struct data transs(peek(&sellheap[stock]).brokername,0,peek(&sellheap[stock]).quantity,0);
                                                                    node* btq=newNode(transs,peek(&sellheap[stock]).quantity);
                                                                    selltrans[peek(&sellheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&selltrans[peek(&sellheap[stock]).brokername]).quantity;
                                                                    int quanti=peek(&sellheap[stock]).quantity+thodab;
                                                                    pop(&selltrans[peek(&sellheap[stock]).brokername]);
                                                                    struct data tras(peek(&sellheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(tras,quanti);
                                                                    selltrans[peek(&sellheap[stock]).brokername]=bttq;
                                                                }
                                                                if(!netrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,-1*peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price,0);
                                                                    node* btq=newNode(transb,-1*peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price);
                                                                    netrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab= peek(&netrans[brokern]).quantity;
                                                                    int quanti=-1*peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price+thodab;
                                                                    pop(&netrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[brokern]=bttq;
                                                                }
                                                                if(!netrans.count(peek(&sellheap[stock]).brokername) )
                                                                {
                                                                    struct data transs(peek(&sellheap[stock]).brokername,0,peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price,0);
                                                                    node* btq=newNode(transs,peek(&sellheap[stock]).quantity);
                                                                    netrans[peek(&sellheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[peek(&sellheap[stock]).brokername]).quantity;
                                                                    int quanti=peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price+thodab;
                                                                    pop(&netrans[peek(&sellheap[stock]).brokername]);
                                                                    struct data tras(peek(&sellheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(tras,quanti);
                                                                    netrans[peek(&sellheap[stock]).brokername]=bttq;
                                                                }
                                    cout<<brokern<<" purchased "<<peek(&sellheap[stock]).quantity<<" share of "<<stock<<" from "<<peek(&sellheap[stock]).brokername<<" for $"<<peek(&sellheap[stock]).price<<"/share"<<endl;
                                    moneyt=moneyt+peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price;
                                    quant=quant-peek(&sellheap[stock]).quantity;
                                    pop(&sellheap[stock]);
                                    break;
                                }
                                
                                else
                                {
                                    possible=true;
                                    trades++;
                                    sharedtra=sharedtra+peek(&sellheap[stock]).quantity;
                                                                 if(!buytrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,peek(&sellheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,peek(&sellheap[stock]).quantity);
                                                                    buytrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&buytrans[brokern]).quantity;
                                                                    int quanti=peek(&sellheap[stock]).quantity+thodab;
                                                                    pop(&buytrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    buytrans[brokern]=bttq;
                                                                }
                                                                if(!selltrans.count(peek(&sellheap[stock]).brokername))
                                                                {
                                                                    struct data transb(peek(&sellheap[stock]).brokername,0,peek(&sellheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,peek(&sellheap[stock]).quantity);
                                                                    selltrans[peek(&sellheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&selltrans[peek(&sellheap[stock]).brokername]).quantity;
                                                                    int quanti=peek(&sellheap[stock]).quantity+thodab;
                                                                    pop(&selltrans[peek(&sellheap[stock]).brokername]);
                                                                    struct data trab(peek(&sellheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    selltrans[peek(&sellheap[stock]).brokername]=bttq;
                                                                }
                                                                 if(!netrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,-1*peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price,0);
                                                                    node* btq=newNode(transb,-1*peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price);
                                                                    netrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[brokern]).quantity;
                                                                    int quanti=-1*peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price+thodab;
                                                                    pop(&netrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[brokern]=bttq;
                                                                }
                                                                if(!netrans.count(peek(&sellheap[stock]).brokername))
                                                                {
                                                                    struct data transb(peek(&sellheap[stock]).brokername,0,peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price,0);
                                                                    node* btq=newNode(transb,peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price);
                                                                    netrans[peek(&sellheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[peek(&sellheap[stock]).brokername]).quantity;
                                                                    int quanti=peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price+thodab;
                                                                    pop(&netrans[peek(&sellheap[stock]).brokername]);
                                                                    struct data trab(peek(&sellheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[peek(&sellheap[stock]).brokername]=bttq;
                                                                }
                                    cout<<brokern<<" purchased "<<peek(&sellheap[stock]).quantity<<" share of "<<stock<<" from "<<peek(&sellheap[stock]).brokername<<" for $"<<peek(&sellheap[stock]).price<<"/share"<<endl;
                                    moneyt=moneyt+peek(&sellheap[stock]).quantity*peek(&sellheap[stock]).price;
                                    pop(&sellheap[stock]);
                                                                
                                    break;
                                }
                            }
                            
                            else
                            {
                                pop(&sellheap[stock]);
                            }
                        }
                        else{
                            break;
                        }
                    }
                    if(possible)break;

                }
                else
                {

                    insinbuy=true;
                    break;
                }
            }
            if(insinbuy)
            {
                if(!buyheap.count(stock))
                {
                    if(exp==-1){exp=MAX;}
                    struct data btemp(brokern,price,quant,startt+exp);
                    node* bq=newNode(btemp,-1*price);
                    buyheap[stock]=bq;
                }
                else
                {
                   if(isEmpty(&buyheap[stock]))
                    {
                        if(exp==-1){exp=MAX;}
                        struct data btemp(brokern,price,quant,startt+exp);
                        node* bq=newNode(btemp,-1*price);
                        buyheap[stock]=bq;
                    }
                    else
                    {
                        if(exp==-1){exp=MAX;}
                        struct data btemp(brokern,price,quant,startt+exp);
                        push(&buyheap[stock],btemp,-1*price);
                    }
                }
            }
        }
        else if(action.compare("SELL")==0)
        {
            bool isinsell=false;
            while(true)
            {
                if(buyheap.count(stock) && !isEmpty(&buyheap[stock]) && price<=peek(&buyheap[stock]).price)
                {
                    bool possible=false;
                    while(!isEmpty(&buyheap[stock]))
                    {
                        if(buyheap.count(stock) && !isEmpty(&buyheap[stock]) && price<=peek(&buyheap[stock]).price)
                        {
                            possible=false;
                            if(startt<=peek(&buyheap[stock]).exptime)
                        {
                            if(quant<peek(&buyheap[stock]).quantity)
                            { 
                                possible=true;
                                int y=peek(&buyheap[stock]).quantity-quant;
                                string broke=peek(&buyheap[stock]).brokername;
                                int p=peek(&buyheap[stock]).price;
                                int expiryt=peek(&buyheap[stock]).exptime;
                                struct data btemp(broke,p,y,expiryt);
                                pop(&buyheap[stock]);
                                    if(isEmpty(&buyheap[stock]))
                                    {
                                        node* bq=newNode(btemp,-1*p);
                                        buyheap[stock]=bq;
                                    }
                                    else
                                    {
                                        push(&buyheap[stock],btemp,-1*p);
                                    }
                                    trades++;
                                    sharedtra=sharedtra+quant;
                                                                if(!buytrans.count(peek(&buyheap[stock]).brokername))
                                                                {
                                                                    struct data transb(peek(&buyheap[stock]).brokername,0,quant,0);
                                                                    node* btq=newNode(transb,quant);
                                                                    buytrans[peek(&buyheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&buytrans[peek(&buyheap[stock]).brokername]).quantity;
                                                                    int quanti=quant+thodab;
                                                                    pop(&buytrans[peek(&buyheap[stock]).brokername]);
                                                                    struct data trab(peek(&buyheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    buytrans[peek(&buyheap[stock]).brokername]=bttq;
                                                                }
                                                                if(!selltrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,quant,0);
                                                                    node* btq=newNode(transb,quant);
                                                                    selltrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&selltrans[brokern]).quantity;
                                                                    int quanti=quant+thodab;
                                                                    pop(&selltrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    selltrans[brokern]=bttq;
                                                                }
                                                                if(!netrans.count(peek(&buyheap[stock]).brokername))
                                                                {
                                                                    struct data transb(peek(&buyheap[stock]).brokername,0,-1*quant*peek(&buyheap[stock]).price,0);
                                                                    node* btq=newNode(transb,-1*quant*peek(&buyheap[stock]).price);
                                                                    netrans[peek(&buyheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[peek(&buyheap[stock]).brokername]).quantity;
                                                                    int quanti=-1*quant*peek(&buyheap[stock]).price+thodab;
                                                                    pop(&netrans[peek(&buyheap[stock]).brokername]);
                                                                    struct data trab(peek(&buyheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[peek(&buyheap[stock]).brokername]=bttq;
                                                                }
                                                                if(!netrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,quant*peek(&buyheap[stock]).price,0);
                                                                    node* btq=newNode(transb,quant*peek(&buyheap[stock]).price);
                                                                    netrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[brokern]).quantity;
                                                                    int quanti=quant*peek(&buyheap[stock]).price+thodab;
                                                                    pop(&netrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[brokern]=bttq;
                                                                }
                                cout<<peek(&buyheap[stock]).brokername<<" purchased "<<quant<<" share of "<<stock<<" from "<<brokern<<" for $"<<peek(&buyheap[stock]).price<<"/share"<<endl;
                                moneyt=moneyt+quant*peek(&buyheap[stock]).price;
                                                                
                                break;
                            }
                            else if (quant>peek(&buyheap[stock]).quantity)
                            {
                                trades++;
                                sharedtra=sharedtra+peek(&buyheap[stock]).quantity;
                                                                if(!buytrans.count(peek(&buyheap[stock]).brokername) )
                                                                {
                                                                    struct data transb(peek(&buyheap[stock]).brokername,0,peek(&buyheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,peek(&buyheap[stock]).quantity);
                                                                    buytrans[peek(&buyheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&buytrans[peek(&buyheap[stock]).brokername]).quantity;
                                                                    int quanti=peek(&buyheap[stock]).quantity+thodab;
                                                                    pop(&buytrans[peek(&buyheap[stock]).brokername]);
                                                                    struct data trab(peek(&buyheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    buytrans[peek(&buyheap[stock]).brokername]=bttq;
                                                                }
                                                                if(!selltrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,peek(&buyheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,peek(&buyheap[stock]).quantity);
                                                                    selltrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab= peek(&selltrans[brokern]).quantity;
                                                                    int quanti=peek(&buyheap[stock]).quantity+thodab;
                                                                    pop(&selltrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    selltrans[brokern]=bttq;
                                                                }
                                                                if(!netrans.count(peek(&buyheap[stock]).brokername) )
                                                                {
                                                                   // cout<<"A"<<endl;
                                                                    struct data transb(peek(&buyheap[stock]).brokername,0,-1*peek(&buyheap[stock]).price*peek(&buyheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,-1*peek(&buyheap[stock]).price*peek(&buyheap[stock]).quantity);
                                                                    netrans[peek(&buyheap[stock]).brokername]=btq;
                                                               }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[peek(&buyheap[stock]).brokername]).quantity;
                                                                    int quanti=-1*peek(&buyheap[stock]).price*peek(&buyheap[stock]).quantity+thodab;
                                                                    pop(&netrans[peek(&buyheap[stock]).brokername]);
                                                                    struct data trab(peek(&buyheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[peek(&buyheap[stock]).brokername]=bttq;
                                                                }
                                                                if(!netrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,peek(&buyheap[stock]).quantity*peek(&buyheap[stock]).price,0);
                                                                    node* btq=newNode(transb,peek(&buyheap[stock]).quantity*peek(&buyheap[stock]).price);
                                                                    netrans[brokern]=btq;
                                                                }
                                                                else
                                                                 {
                                                                    int thodab= peek(&netrans[brokern]).quantity;
                                                                    int quanti=peek(&buyheap[stock]).quantity*peek(&buyheap[stock]).price+thodab;
                                                                    pop(&netrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[brokern]=bttq;
                                                                }
                                cout<<peek(&buyheap[stock]).brokername<<" purchased "<<peek(&buyheap[stock]).quantity<<" share of "<<stock<<" from "<<brokern<<" for $"<<peek(&buyheap[stock]).price<<"/share"<<endl;
                                moneyt=moneyt+peek(&buyheap[stock]).quantity*peek(&buyheap[stock]).price;
                                quant=quant-peek(&buyheap[stock]).quantity;
                                pop(&buyheap[stock]);
                                break;
                            }
                            else
                            {
                                possible=true;
                                trades++;
                                sharedtra=sharedtra+peek(&buyheap[stock]).quantity;
                                                                if(!buytrans.count(peek(&buyheap[stock]).brokername))
                                                                {
                                                                    struct data transb(peek(&buyheap[stock]).brokername,0,peek(&buyheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,peek(&buyheap[stock]).quantity);
                                                                    buytrans[peek(&buyheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&buytrans[peek(&buyheap[stock]).brokername]).quantity;
                                                                    int quanti=peek(&buyheap[stock]).quantity+thodab;
                                                                    pop(&buytrans[peek(&buyheap[stock]).brokername]);
                                                                    struct data trab(peek(&buyheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    buytrans[peek(&buyheap[stock]).brokername]=bttq;
                                                                }
                                                                if(!selltrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,peek(&buyheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,peek(&buyheap[stock]).quantity);
                                                                    selltrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&selltrans[brokern]).quantity;
                                                                    int quanti=peek(&buyheap[stock]).quantity+thodab;
                                                                    pop(&selltrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    selltrans[brokern]=bttq;
                                                                }
                                                                if(!netrans.count(peek(&buyheap[stock]).brokername))
                                                                {
                                                                    struct data transb(peek(&buyheap[stock]).brokername,0,-1*peek(&buyheap[stock]).price*peek(&buyheap[stock]).quantity,0);
                                                                    node* btq=newNode(transb,-1*peek(&buyheap[stock]).price*peek(&buyheap[stock]).quantity);
                                                                    netrans[peek(&buyheap[stock]).brokername]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[peek(&buyheap[stock]).brokername]).quantity;
                                                                    int quanti=-1*peek(&buyheap[stock]).price*peek(&buyheap[stock]).quantity+thodab;
                                                                    pop(&netrans[peek(&buyheap[stock]).brokername]);
                                                                    struct data trab(peek(&buyheap[stock]).brokername,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[peek(&buyheap[stock]).brokername]=bttq;
                                                                }
                                                                 if(!netrans.count(brokern))
                                                                {
                                                                    struct data transb(brokern,0,peek(&sellheap[stock]).quantity*peek(&buyheap[stock]).price,0);
                                                                    node* btq=newNode(transb,peek(&buyheap[stock]).quantity*peek(&buyheap[stock]).price);
                                                                    netrans[brokern]=btq;
                                                                }
                                                                else
                                                                {
                                                                    int thodab=  peek(&netrans[brokern]).quantity;
                                                                    int quanti=peek(&buyheap[stock]).quantity*peek(&buyheap[stock]).price+thodab;
                                                                    pop(&netrans[brokern]);
                                                                    struct data trab(brokern,0,quanti,0);
                                                                    node* bttq=newNode(trab,quanti);
                                                                    netrans[brokern]=bttq;
                                                                }
                                cout<<peek(&buyheap[stock]).brokername<<" purchased "<<peek(&buyheap[stock]).quantity<<" share of "<<stock<<" from "<<brokern<<" for $"<<peek(&buyheap[stock]).price<<"/share"<<endl;
                                moneyt=moneyt+peek(&buyheap[stock]).quantity*peek(&buyheap[stock]).price;
                                pop(&buyheap[stock]);
                                break;
                            }
                        }
                        else
                        {
                            pop(&buyheap[stock]);
                        }
                        }
                        else
                        {
                            break;
                        }
                    }
                    if(possible)break;
                }
                else
                {
                    isinsell=true;
                    break;
                }
            }
            if(isinsell)
            {
                if(!sellheap.count(stock))
                {
                   if(exp==-1){exp=MAX;}
                    struct data stemp(brokern,price,quant,startt+exp);
                    node* sq=newNode(stemp,price);
                    sellheap[stock]=sq;
                }
                else
                {
                    if(isEmpty(&sellheap[stock]))
                    {
                        if(exp==-1){exp=MAX;}
                        struct data stemp(brokern,price,quant,startt+exp);
                        node* sq=newNode(stemp,price);
                        sellheap[stock]=sq;
                    }
                    else
                    {
                        if(exp==-1){exp=MAX;}
                        struct data stemp(brokern,price,quant,startt+exp);
                        push(&sellheap[stock],stemp,price);
                    }
                    
                }
            }
            
        }
      
    }
   cout<<endl;
   cout<<"---End of Day---"<<endl;
   cout<<"Total Amount of Money Transferred: $"<<moneyt<<endl;
   cout<<"Number of Completed Trades: "<<trades<<endl;
   cout<<"Number of Shares Traded: "<<sharedtra<<endl;
   int j=0;
    while(netrans.getIthElement(j)!=nullptr)
    {
        int b=0;
        if(buytrans.count(netrans.getIthElement(j)->first)){b=peek(&buytrans[netrans.getIthElement(j)->first]).quantity;}
        int s=0;
        if(selltrans.count(netrans.getIthElement(j)->first)){s=peek(&selltrans[netrans.getIthElement(j)->first]).quantity;}
        int n=peek(&netrans[netrans.getIthElement(j)->first]).quantity;
        cout<<netrans.getIthElement(j)->first<<" bought "<<b<<" and sold "<<s<<" for a net transfer of "<<"$"<<n<<endl;
        j++;
    }
}
