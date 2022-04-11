#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int d;
int t;
class node{
public:

    vector<int> data_sep;
    //int d;
    node  * left;
    node * right;
    node * parent;

    bool isdata;


    //vector<int> separators;
    vector<node *> children;
    //int t;



    node(bool as){
        if(as==0){
            left = nullptr;
            right = nullptr;
            isdata = 0; //yes data is there
            parent = nullptr;

        }
        else{
            isdata = 1;
            parent = nullptr;

        }

    }
};

class btree{
public:
    btree();
    void insertt(int val);
    void split(node* prevnode,node * extranode,int extraval,node * parent);
    void show();
    void link(node * ptr,node * newdata);
    void printrange();

private:
    node * root;
    node * firstdata;
    int countindex;
    int countdata;
};

btree::btree(){
        firstdata = nullptr;
        root = nullptr;
        countindex = 0;
        countdata =0;
}
void btree::link(node * ptr,node * newdata){
    newdata->left = ptr;
    newdata->right = ptr->right;
    if(ptr->right !=nullptr){
        (ptr->right)->left = newdata;


    }
    ptr->right = newdata;

}
void btree::printrange(){
    if(firstdata!=nullptr){
        node * ptr = firstdata;
        while(ptr!=nullptr){
            int m=ptr->data_sep.size();
            for(int i=0;i<m;i++){
                cout<<ptr->data_sep[i]<<" ";
            }
            cout<<endl;
            ptr = ptr->right;
        }
    }
}

void btree::insertt(int val){
    if(root==nullptr){
        root = new node(0);
        firstdata = root;
        (root->data_sep).push_back(val);
        countdata++;

    }
    else{
        node * ptr = root;
        while(ptr->isdata!=0){
            int pos =0;
            while(pos<ptr->data_sep.size() && ptr->data_sep[pos]< val ){
                pos++;
            }
            ptr = ptr->children[pos];
        }
        //got the leaf data node!!


        if(ptr->data_sep.size()<2*d){
            int pos=0;
            while(pos < ptr->data_sep.size() && ptr->data_sep[pos]<val){
                pos++;
            }
            (ptr->data_sep).insert((ptr->data_sep).begin()+pos,val);

        }
        else{
            int pos=0;
            while(pos < ptr->data_sep.size() && ptr->data_sep[pos]<val){
                pos++;
            }
            (ptr->data_sep).insert((ptr->data_sep).begin()+pos,val);
                //no space in leaf node
            //(ptr->data_sep).push_back(val);
            //sort((ptr->data_sep).begin(),(ptr->data_sep).end());
            node * newdata = new node(0);


            link(ptr,newdata);

           // ptr->right = newdata;
            countdata++;
            for(int j=d;j<2*d+1;j++){
                int entrytonewnode = ptr->data_sep[j];
                (newdata->data_sep).push_back(entrytonewnode);
            }
            for(int j=d;j<2*d+1;j++){
                ptr->data_sep.pop_back();
            }
        //done with the new data node
            split(ptr,newdata,(newdata->data_sep)[0],ptr->parent);


        }


    }

}
void btree::split(node* prevnode,node * extranode,int extraval,node * parent){
    if(parent==nullptr){
        node * newroot = new node(1);
        countindex++;
        newroot->data_sep.push_back(extraval);
        newroot->children.push_back(prevnode);
        newroot->children.push_back(extranode);
        prevnode->parent = newroot;
        extranode->parent = newroot;
        root = newroot;
    }
    else if(parent->data_sep.size()< 2*t +1){
            //parent has space
        int pos=0;
        while(pos < parent->data_sep.size()  &&  parent->data_sep[pos]< extraval){
            pos++;
        }
        (parent->data_sep).insert((parent->data_sep).begin()+pos,extraval);
        (parent->children).insert((parent->children).begin() + pos+1,extranode);
        extranode->parent = parent;

    }
    else{

            //parent has no space
        node * newindex = new node(1);
        countindex++;
        int pos=0;
        while(pos < parent->data_sep.size()  &&  parent->data_sep[pos]< extraval){
            pos++;
        }
        parent->data_sep.insert((parent->data_sep).begin()+pos,extraval);
        parent->children.insert((parent->children).begin() + pos+1,extranode);
        //sorted order all keys
        for(int i=t+1;i<2*t+2;i++){
                int sep = parent->data_sep[i];
            newindex->data_sep.push_back(sep);
        }
        for(int i=t+1;i<2*t+3;i++){
            node * tmp = parent->children[i];
            newindex->children.push_back(tmp);
            tmp->parent = newindex;
        }
        int newextraval = parent->data_sep[t];
        node *  newextraptr = newindex;

        for(int i=t;i<2*t+2;i++){
            parent->data_sep.pop_back();
            parent->children.pop_back();
        }
        //parent->children.pop_back();
        split(parent,newextraptr,newextraval,parent->parent);

    }

}

//check
void btree::show(){
    cout<<countindex<<" "<<countdata;
    if(root!=nullptr){
        int m=root->data_sep.size();
        for(int i=0;i<m;i++){
            cout<<" "<<root->data_sep[i];
        }
    }
    cout<<endl;


}


//check
int main(){
    btree btn;
    cin>>d;
    cin>>t;
    int opcode;
    cin>>opcode;
    while(opcode !=4){
        if(opcode == 1){
            int val;
            cin>>val;
            btn.insertt(val);

        }
        else if(opcode ==2){
            btn.show();
        }
        else if(opcode ==3){
            btn.printrange();
        }
        cin>>opcode;
    }


}

