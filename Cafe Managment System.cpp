#include <iostream>
using namespace std;

struct Item {
    int id;
    string name;
    double price;
    int stock;
};

const int MAX_ITEMS = 6;
Item menu[MAX_ITEMS] = 
{
    {1, "Burger", 150, 10},
    {2, "Pizza", 200, 5},
    {3, "Salad", 100, 8},
    {4, "Sandwich", 120, 12},
    {5, "Fries", 80, 15},
    {6,"Shawarma",350,11}
};


/* ===== Sales Tracking Variables ===== */
int totalOrdersServed = 0;
int totalItemsSold = 0;
double totalRevenue = 0;
int itemSoldCount[MAX_ITEMS] = {0};

void showMenu() {
    cout << "\nMenu:\n";
    for (int i = 0; i < MAX_ITEMS; i++) {
        cout << menu[i].id << ". " << menu[i].name
             << " - Rs " << menu[i].price
             << " (" << menu[i].stock << " left)\n";
    }
}

void ShowCurrentInventory() {
    cout << "\nCurrent Inventory:\n";
    for (int i = 0; i <MAX_ITEMS ; i++) {
        cout << menu[i].id << ". " << menu[i].name
             << " (" << menu[i].stock << " left)\n";
    }
}

void takeOrder(int order[], int &orderSize) {
    orderSize = 0;
    int id, qty;char conf;

    while (true) {
        cout << "Enter item ID (0 to finish): ";
        cin >> id;
        if (id == 0) 
		{
			break;
		}
		if(id<0)
		{
			cout<<"\nInvalid ID\n";
			continue;
		}
		do
		{
			cout << "\nEnter quantity: ";
        	cin >> qty;
        	if(qty<=0)
        	{
        		cout<<"\nQuantity can't be 0 or less than 0";
        		continue;
			}
			break;
		}while(true);
        
        
        bool found = false;
        for (int i = 0; i < MAX_ITEMS; i++) {
            if (menu[i].id == id) {
                if (menu[i].stock >= qty)
				{
                    order[orderSize++] = id * 100 + qty;
                    found = true;
                } 
				else 
				{
                    cout << "Not enough stock!\n";
                    found = true;
                }
                break;
            }
        }
        if (!found) cout << "Invalid ID!\n";
    }
    do{
	cout<<"\nDo you want to Confirm Order Or Not (y/n):";
	cin>>conf;
	if(conf=='Y'||conf=='y')
	{
	if (orderSize > 0)
        {
        	totalOrdersServed++;
        	return;
		}
	}
	else if(conf=='N'||conf=='n')
	{
	
    orderSize = 0; 
    cout << "Order cancelled.\n";
    return; 
	}
	else
	{
		cout<<"\n You entered Wrong Alphabet:";
		continue;
	}
	}while(true);
}

void billing(int order[], int orderSize) {
    double total = 0;
    cout << "\nBill:\n";
	
    for (int i = 0; i < orderSize; i++) {
        int id = order[i] / 100;
        int qty = order[i] % 100;

        for (int j = 0; j <MAX_ITEMS; j++) {
            if (menu[j].id == id) {
                double cost = menu[j].price * qty;
                total += cost;
                cout << menu[j].name << " x " << qty
                     << " = Rs " << cost << endl;
            }
        }
    }

    int discount_percentage = 0;
    do{
    cout << "\nEnter discount percentage from 1-100 % (0 if none): ";
    cin >> discount_percentage;
    if(discount_percentage<0 || discount_percentage>100)
    {
    	cout << "Invalid discount! Must be 0 – 100.\n";
    	continue;
	}
	else
	{
		break;
	}
	}while (true);
	
    double discountAmount = (total * discount_percentage) / 100;
    double finalTotal = total - discountAmount;

    cout << "Total Amount: Rs " << total << endl;
    cout << "Discount: Rs " << discountAmount << endl;
    cout << "Final Bill: Rs " << finalTotal << endl;

    totalRevenue += finalTotal;
}

void updateInventory(int order[], int orderSize) {
    for (int i = 0; i < orderSize; i++) 
	{
        int id = order[i] / 100;
        int qty = order[i] % 100;

        for (int j = 0; j < MAX_ITEMS; j++)
		{
            if (menu[j].id == id) 
			{
                menu[j].stock -= qty;
                itemSoldCount[j] += qty;
                totalItemsSold += qty;
            }
        }
    }
}

void salesSummary() {
    cout << "\n===== Sales Summary (End-of-Session) =====\n";
    cout << "Total orders served: " << totalOrdersServed << endl;
    cout << "Total items sold: " << totalItemsSold << endl;

    int maxIndex = 0;
    for (int i = 1; i < MAX_ITEMS; i++) {
        if (itemSoldCount[i] > itemSoldCount[maxIndex]) {
            maxIndex = i;
        }
    }

    if (totalItemsSold > 0) {
        cout << "Most popular item: "
             << menu[maxIndex].name
             << " (" << itemSoldCount[maxIndex] << " sold)\n";
    } else {
        cout << "Most popular item: None\n";
    }

    cout << "Total revenue: Rs " << totalRevenue << endl;
    cout << "=========================================\n";
}

int main() {
    int check_statement = 1;
    int order[MAX_ITEMS], orderSize;

    while (check_statement != 0) 
	{
        int check_menu;
        cout << "Welcome to Maria Cafe\n";
        cout << "1. New Order\n";
        cout << "2. Show Current Inventory\n";
        cout << "3. Exit & Show Sales Summary\n";
        cout << "Enter your choice: ";
        cin >> check_menu;

        if (check_menu == 1) 
		{
            showMenu();
            takeOrder(order, orderSize);
            if(orderSize > 0) 
			{
    			billing(order, orderSize);
    			updateInventory(order, orderSize);
			} 
			else 
			{
    			cout << "Order cancelled.\n";
			}
        }
        else if (check_menu == 2) {
            ShowCurrentInventory();
        }
        else if (check_menu == 3) {
            check_statement = 0;
            salesSummary();
        }
        else {
            cout << "Invalid Choice\n";
        }
    }
    return 0;
}

