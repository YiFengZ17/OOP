#include <iostream>
#include <map>
using namespace std;

int main( ) {
    
    map<string, float> price; 
    price["snapple"] = 0.75;
    price["coke"] = 0.50;  
    string item;
    double total=0;  
    while ( cin >> item )
    {
        if (item != "end")
        {
            if (price.count(item))
                total += price[item];
            else
                cout << "No such item" <<endl; 
        }
        else
            break;
    }
        
    cout << total << endl;
      
    /*
    map<long, int>	root;  
    root[4]	=	2;
    root[1000000]	=	1000;
    long l;  
    cin >> l;
    if	(root.count(l))	
        cout<<root[l];
    else 
        cout<<"Not perfect square";
    */  
   
    return 0;
}

